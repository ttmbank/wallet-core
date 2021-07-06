#! /bin/bash

xcodebuild archive -workspace "TrustWalletCore.xcworkspace" -scheme WalletCore -destination="iOS" -archivePath build/ios.xcarchive -sdk iphoneos SKIP_INSTALL=NO BUILD_LIBRARIES_FOR_DISTRIBUTION=YES
xcodebuild archive -workspace "TrustWalletCore.xcworkspace" -scheme WalletCore -destination="iOS Simulator" -archivePath build/iossimulator.xcarchive -derivedDataPath /tmp/iphoneos -sdk iphonesimulator SKIP_INSTALL=NO BUILD_LIBRARIES_FOR_DISTRIBUTION=YES

xcodebuild -create-xcframework -framework build/ios.xcarchive/Products/Library/Frameworks/WalletCore.framework -framework build/iossimulator.xcarchive/Products/Library/Frameworks/WalletCore.framework -output build/WalletCore.xcframework


cp build/ios.xcarchive/Products/usr/local/lib/* build/

rm -rf build/ios.xcarchive
rm -rf build/iossimulator.xcarchive
