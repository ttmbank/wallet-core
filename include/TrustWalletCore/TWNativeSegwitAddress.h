// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "TWBase.h"
#include "TWString.h"
#include "TWData.h"
#include "TWHRP.h"

TW_EXTERN_C_BEGIN

struct TWPublicKey;

/// Represents a BIP 0173 address.
TW_EXPORT_CLASS
struct TWNativeSegwitAddress;

/// Compares two addresses for equality.
TW_EXPORT_STATIC_METHOD
bool TWNativeSegwitAddressEqual(struct TWNativeSegwitAddress *_Nonnull lhs, struct TWNativeSegwitAddress *_Nonnull rhs);

/// Determines if the string is a valid Bech32 address.
TW_EXPORT_STATIC_METHOD
bool TWNativeSegwitAddressIsValidString(TWString *_Nonnull string);

/// Creates an address from a string representaion.
TW_EXPORT_STATIC_METHOD
struct TWNativeSegwitAddress *_Nullable TWNativeSegwitAddressCreateWithString(TWString *_Nonnull string);

/// Creates an address from a public key.
TW_EXPORT_STATIC_METHOD
struct TWNativeSegwitAddress *_Nonnull TWNativeSegwitAddressCreateWithPublicKey(enum TWHRP hrp, struct TWPublicKey *_Nonnull publicKey);

TW_EXPORT_METHOD
void TWNativeSegwitAddressDelete(struct TWNativeSegwitAddress *_Nonnull address);

/// Returns the address string representation.
TW_EXPORT_PROPERTY
TWString *_Nonnull TWNativeSegwitAddressDescription(struct TWNativeSegwitAddress *_Nonnull address);

/// Returns the human-readable part.
TW_EXPORT_PROPERTY
enum TWHRP TWNativeSegwitAddressHRP(struct TWNativeSegwitAddress *_Nonnull address);

/// Returns the witness program
TW_EXPORT_PROPERTY
TWData *_Nonnull TWNativeSegwitAddressWitnessProgram(struct TWNativeSegwitAddress *_Nonnull address);

TW_EXTERN_C_END
