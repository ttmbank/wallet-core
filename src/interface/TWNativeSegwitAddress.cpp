// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "../Bitcoin/NativeSegwitAddress.h"

#include <TrezorCrypto/ecdsa.h>
#include <TrustWalletCore/TWNativeSegwitAddress.h>
#include <TrustWalletCore/TWHash.h>
#include <TrustWalletCore/TWHRP.h>
#include <TrustWalletCore/TWPublicKey.h>

using namespace TW;
using namespace TW::Bitcoin;

bool TWNativeSegwitAddressEqual(struct TWNativeSegwitAddress *_Nonnull lhs, struct TWNativeSegwitAddress *_Nonnull rhs) {
   return lhs->impl == rhs->impl;
}

bool TWNativeSegwitAddressIsValidString(TWString *_Nonnull string) {
    auto s = reinterpret_cast<const std::string*>(string);
    return NativeSegwitAddress::isValid(*s);
}

struct TWNativeSegwitAddress *_Nullable TWNativeSegwitAddressCreateWithString(TWString *_Nonnull string) {
    auto s = reinterpret_cast<const std::string*>(string);
    auto dec = NativeSegwitAddress::decode(*s);
    if (!dec.second) {
        return nullptr;
    }

    return new TWNativeSegwitAddress{ std::move(dec.first) };
}

struct TWNativeSegwitAddress *_Nonnull TWNativeSegwitAddressCreateWithPublicKey(enum TWHRP hrp, struct TWPublicKey *_Nonnull publicKey) {
    const auto address = NativeSegwitAddress(publicKey->impl, 0);
    return new TWNativeSegwitAddress{ std::move(address) };
}

void TWNativeSegwitAddressDelete(struct TWNativeSegwitAddress *_Nonnull address) {
    delete address;
}

TWString *_Nonnull TWNativeSegwitAddressDescription(struct TWNativeSegwitAddress *_Nonnull address) {
    const auto string = address->impl.string();
    return TWStringCreateWithUTF8Bytes(string.c_str());
}


TWData *_Nonnull TWNativeSegwitAddressWitnessProgram(struct TWNativeSegwitAddress *_Nonnull address) {
    return TWDataCreateWithBytes(address->impl.witnessProgram.data(), address->impl.witnessProgram.size());
}
