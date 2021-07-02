package main

// #cgo CFLAGS: -I../../include
// #cgo LDFLAGS: -L../../build -L../../build/trezor-crypto -lTrustWalletCore -lprotobuf -lTrezorCrypto -lc++ -lm
// #include <TrustWalletCore/TWHDWallet.h>
// #include <TrustWalletCore/TWPrivateKey.h>
// #include <TrustWalletCore/TWPublicKey.h>
// #include <TrustWalletCore/TWBitcoinScript.h>
// #include <TrustWalletCore/TWAnySigner.h>
import "C"

import (
	"encoding/hex"
	"fmt"
	"tw/protos/bitcoin"
	"tw/types"

	"github.com/golang/protobuf/proto"
)

func reverse(numbers []byte) []byte {
	for i, j := 0, len(numbers)-1; i < j; i, j = i+1, j-1 {
		numbers[i], numbers[j] = numbers[j], numbers[i]
	}
	return numbers
}

func main() {
	fmt.Println("==> calling wallet core from go")
	str := types.TWStringCreateWithGoString("trial sing wear crumble monkey survey immense awake title announce shoe soldier")
	emtpy := types.TWStringCreateWithGoString("")
	defer C.TWStringDelete(str)
	defer C.TWStringDelete(emtpy)

	fmt.Println("==> mnemonic is valid: ", C.TWHDWalletIsValid(str))

	wallet := C.TWHDWalletCreateWithMnemonic(str, emtpy)
	defer C.TWHDWalletDelete(wallet)

	coinType := uint32(C.TWCoinTypeBitcoinTest)

	key := C.TWHDWalletGetKeyForCoin(wallet, coinType)
	keyData := C.TWPrivateKeyData(key)
	defer C.TWDataDelete(keyData)

	fmt.Println("<== bitcoin private key: ", types.TWDataHexString(keyData))

	// pubKey, _ := hex.DecodeString("0288be7586c41a0498c1f931a0aaf08c15811ee2651a5fe0fa213167dcaba59ae8")
	// pubKeyData := types.TWDataCreateWithGoBytes(pubKey)
	// defer C.TWDataDelete(pubKeyData)
	// fmt.Println("==> bitcoin public key is valid: ", C.TWPublicKeyIsValid(pubKeyData, C.TWPublicKeyTypeSECP256k1))

	address := C.TWHDWalletGetAddressForCoin(wallet, coinType)
	defer C.TWStringDelete(address)
	fmt.Println("<== bitcoin address: ", types.TWStringGoString(address))

	script := C.TWBitcoinScriptLockScriptForAddress(address, coinType)
	scriptData := C.TWBitcoinScriptData(script)
	defer C.TWBitcoinScriptDelete(script)
	defer C.TWDataDelete(scriptData)
	fmt.Println("<== bitcoin address lock script: ", types.TWDataHexString(scriptData))

	/*
		utxoHash, _ := hex.DecodeString("357979fe568db13e0cb314f11097af77572026a822125e69fe4d4c5e5576a120")
		utxo := bitcoin.UnspentTransaction{
			OutPoint: &bitcoin.OutPoint{
				Hash:     utxoHash,
				Index:    0,
				Sequence: 4294967295,
			},
			Amount: 1759405,
			Script: types.TWDataGoBytes(scriptData),
		}*/

	utxoHash0, _ := hex.DecodeString("c00e4d0a2b6b8d5a39aed9bb3f1773f8f3126b9f10fdcd7944d15a620e71bf7a")
	utxoHash0 = reverse(utxoHash0)
	utxo0 := bitcoin.UnspentTransaction{
		OutPoint: &bitcoin.OutPoint{
			Hash:     utxoHash0,
			Index:    0,
			Sequence: 0,
		},
		Amount: 5000,
		Script: types.TWDataGoBytes(scriptData),
	}

	/*
		utxoHash1, _ := hex.DecodeString("58d271e249968abfb4eb4d0ef0ff85f931878885358a67a1b556aa69859b9d11")
		utxoHash1 = reverse(utxoHash1)
		utxo1 := bitcoin.UnspentTransaction{
			OutPoint: &bitcoin.OutPoint{
				Hash:     utxoHash1,
				Index:    1,
				Sequence: 0,
			},
			Amount:  226975,
			Script: types.TWDataGoBytes(scriptData),
		}

	*/
	/*
		utxoHash2, _ := hex.DecodeString("be6632bda1aec98e01808d3afc1a96b2ef814732080ee0770d95c46eb484a59e")
		utxoHash2 = reverse(utxoHash2)
		utxo2 := bitcoin.UnspentTransaction{
			OutPoint: &bitcoin.OutPoint{
				Hash:     utxoHash2,
				Index:    0,
				Sequence: 0,
			},
			Amount:  487900,
			Script: types.TWDataGoBytes(scriptData),
		}

	*/

	/*utxoHash3, _ := hex.DecodeString("c00e4d0a2b6b8d5a39aed9bb3f1773f8f3126b9f10fdcd7944d15a620e71bf7a")
	utxoHash3 = reverse(utxoHash3)
	utxo3 := bitcoin.UnspentTransaction{
		OutPoint: &bitcoin.OutPoint{
			Hash:     utxoHash3,
			Index:    1,
			Sequence: 0,
		},
		Amount:  462980,
		Script: types.TWDataGoBytes(scriptData),
	}

	*/

	utxoHash4, _ := hex.DecodeString("2b0a61e429bf4acb580310118db94f27a8a6a51d3b4a1152f25fdb76057c62d1")
	utxoHash4 = reverse(utxoHash4)
	utxo4 := bitcoin.UnspentTransaction{
		OutPoint: &bitcoin.OutPoint{
			Hash:     utxoHash4,
			Index:    1,
			Sequence: 0,
		},
		Amount: 1000,
		Script: types.TWDataGoBytes(scriptData),
	}

	utxoHash5, _ := hex.DecodeString("6cc82a0a689c2a39803ff8a07a25c6ea022ac01182c5773f17b185f8a25dba30")
	utxoHash5 = reverse(utxoHash5)
	utxo5 := bitcoin.UnspentTransaction{
		OutPoint: &bitcoin.OutPoint{
			Hash:     utxoHash5,
			Index:    1,
			Sequence: 0,
		},
		Amount: 175085,
		Script: types.TWDataGoBytes(scriptData),
	}

	utxoHash6, _ := hex.DecodeString("6cc82a0a689c2a39803ff8a07a25c6ea022ac01182c5773f17b185f8a25dba30")
	utxoHash6 = reverse(utxoHash6)
	utxo6 := bitcoin.UnspentTransaction{
		OutPoint: &bitcoin.OutPoint{
			Hash:     utxoHash6,
			Index:    0,
			Sequence: 0,
		},
		Amount: 1000000,
		Script: types.TWDataGoBytes(scriptData),
	}

	input := bitcoin.SigningInput{
		HashType:      1, // TWBitcoinSigHashTypeAll
		Amount:        1000000,
		ByteFee:       10,
		ToAddress:     types.TWStringGoString(address),
		ChangeAddress: types.TWStringGoString(address),
		//PrivateKey:    [][]byte{/*types.TWDataGoBytes(keyData),*/types.TWDataGoBytes(keyData),types.TWDataGoBytes(keyData),types.TWDataGoBytes(keyData),types.TWDataGoBytes(keyData)},
		PrivateKey: [][]byte{},
		Utxo:       []*bitcoin.UnspentTransaction{&utxo0 /*&utxo1, &utxo2, &utxo3,*/, &utxo4, &utxo5, &utxo6},
		CoinType:   coinType, // TWCoinTypeBitcoinTest
	}

	inputBytes, _ := proto.Marshal(&input)
	inputData := types.TWDataCreateWithGoBytes(inputBytes)
	defer C.TWDataDelete(inputData)

	var outputPlan bitcoin.TransactionPlan
	outputPlanData := C.TWAnySignerPlan(inputData, coinType)
	defer C.TWDataDelete(outputPlanData)

	_ = proto.Unmarshal(types.TWDataGoBytes(outputPlanData), &outputPlan)
	fmt.Println("<== bitcoin plan: ", outputPlan)
	fmt.Println("<== bitcoin plan: ", outputPlan.String())
	input.Plan = &outputPlan

	fmt.Println("<== bitcoin uxto0: ", outputPlan.Utxos[0].String())

	outputData := C.TWAnySignerSign(inputData, coinType)
	defer C.TWDataDelete(outputData)

	input.PrivateKey = [][]byte{types.TWDataGoBytes(keyData), types.TWDataGoBytes(keyData), types.TWDataGoBytes(keyData), types.TWDataGoBytes(keyData)}
	inputBytes2, _ := proto.Marshal(&input)
	inputData2 := types.TWDataCreateWithGoBytes(inputBytes2)
	defer C.TWDataDelete(inputData2)

	outputData2 := C.TWAnySignerSign(inputData2, coinType)
	defer C.TWDataDelete(outputData2)

	var output bitcoin.SigningOutput
	_ = proto.Unmarshal(types.TWDataGoBytes(outputData), &output)
	var output2 bitcoin.SigningOutput
	_ = proto.Unmarshal(types.TWDataGoBytes(outputData2), &output2)
	fmt.Println("<== bitcoin signed tx          : ", hex.EncodeToString(output.Encoded))
	fmt.Println("<== bitcoin signed tx with keys: ", hex.EncodeToString(output2.Encoded))
}
