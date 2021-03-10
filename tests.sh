echo "#### Testing... ####"
export CK_TIMEOUT_MULTIPLIER=4
build/trezor-crypto/crypto/tests/TrezorCryptoTests

ROOT="`dirname \"$0\"`"
TESTS_ROOT="`(cd \"$ROOT/tests\" && pwd)`"
build/tests/tests "$TESTS_ROOT"
