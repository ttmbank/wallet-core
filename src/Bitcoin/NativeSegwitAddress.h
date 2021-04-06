// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "../PublicKey.h"

#include <cstdint>
#include <string>

namespace TW::Bitcoin {

/// A Segwit address.
/// Note: Similar to Bech32Address, but it differs enough so that reuse makes no sense.
class NativeSegwitAddress {
    public:

        /// Witness program version.
        byte prefix;

        /// Witness program.
        std::vector<uint8_t> witnessProgram;

        /// Determines whether a string makes a valid Bech32 address.
        static bool isValid(const std::string& string);

        /// Determines whether a string makes a valid Bech32 address, and the HRP
        /// matches.
        static bool isValid(const std::string& string, const std::string& hrp);

        /// Initializes a Bech32 address with a human-readable part, a witness
        /// version, and a witness program.
        NativeSegwitAddress(byte prefix, std::vector<uint8_t> witprog)
                : prefix(prefix), witnessProgram(std::move(witprog)) {}

        /// Initializes a Bech32 address with a public key and a HRP prefix.
        NativeSegwitAddress(const PublicKey& publicKey, byte prefix);


        /// Encodes the SegWit address.
        ///
        /// \returns encoded address string, or empty string on failure.
        std::string string() const;

        /// Initializes a Bech32 address with raw data.
        static std::pair<NativeSegwitAddress, bool> fromRaw(const byte prefix,
                                                      const std::vector<uint8_t>& data);

        bool operator==(const NativeSegwitAddress& rhs) const {
            return prefix == rhs.prefix &&
                   witnessProgram == rhs.witnessProgram;
        }
        /// Decodes a SegWit address.
        ///
        /// \returns a pair with the address and a success flag.
        static std::pair<NativeSegwitAddress, bool> decode(const std::string& addr);

    private:
        NativeSegwitAddress() = default;
    };

} // namespace TW::Bitcoin

/// Wrapper for C interface.
struct TWNativeSegwitAddress {
    TW::Bitcoin::NativeSegwitAddress impl;
};
