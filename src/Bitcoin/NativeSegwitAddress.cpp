// Copyright © 2017 Pieter Wuille
// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "NativeSegwitAddress.h"
#include "Script.h"
#include "../Bech32.h"
#include "../Base58.h"

#include <TrezorCrypto/ecdsa.h>
#include <TrustWalletCore/TWHRP.h>

using namespace TW::Bitcoin;

bool NativeSegwitAddress::isValid(const std::string& string) {

    return true;
}

bool NativeSegwitAddress::isValid(const std::string& string, const std::string& hrp) {

    return true;
}

NativeSegwitAddress::NativeSegwitAddress(const PublicKey& publicKey, byte prefix)
        :  prefix(prefix), witnessProgram() {
    if (publicKey.type != TWPublicKeyTypeSECP256k1) {
        throw std::invalid_argument("SegwitAddress needs a compressed SECP256k1 public key.");
    }
    if (publicKey.bytes.size() == 33 || publicKey.bytes.size() == 65) {
        Data enc;
        enc.reserve(20);
        witnessProgram.push_back(static_cast<uint8_t>(0));
        witnessProgram.push_back(static_cast<uint8_t>(0x14));
        ecdsa_get_pubkeyhash(publicKey.compressed().bytes.data(), HASHER_SHA2_RIPEMD,
                             enc.data());
        witnessProgram.insert(witnessProgram.end(), std::begin(enc),std::end(enc));
    } else if (publicKey.bytes.size() == 66) {
        witnessProgram.push_back(static_cast<uint8_t>(0));
        witnessProgram.push_back(static_cast<uint8_t>(1));
        witnessProgram.insert(witnessProgram.end(), std::begin(publicKey.bytes),std::end(publicKey.bytes));
        witnessProgram.push_back(static_cast<uint8_t>(2));
        witnessProgram.push_back(static_cast<uint8_t>(OP_CHECKMULTISIG));
    } else {
        throw std::invalid_argument("Length invalid");

    }
}


std::string NativeSegwitAddress::string() const {
    auto script = Script(witnessProgram);
    auto scriptHash = script.hash();
    auto result = Data();
    result.reserve(1 + scriptHash.size());
    append(result, 0x5);
    append(result, scriptHash);
    auto b58 = Base58::bitcoin.encodeCheck(result);
    return b58;
}

std::pair<NativeSegwitAddress, bool> NativeSegwitAddress::fromRaw(const byte prefix,
                                                      const std::vector<uint8_t>& data) {
    Data conv;
    if (!Bech32::convertBits<5, 8, false>(conv, Data(data.begin() + 1, data.end())) ||
        conv.size() < 2 || conv.size() > 40 || data[0] > 16 ||
        (data[0] == 0 && conv.size() != 20 && conv.size() != 32)) {
        return std::make_pair(NativeSegwitAddress(), false);
    }

    return std::make_pair(NativeSegwitAddress(data[0], conv), true);
}
