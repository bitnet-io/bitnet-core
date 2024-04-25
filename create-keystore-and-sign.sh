echo "requires running java11"
echo ' 
yum install nodejs -y
npm -g install randomstring'
randomstring
rm -rf my-release-key.jks
keytool -genkey -v -keystore my-release-key.jks -alias alias_name -keyalg RSA -keysize 2048 -validity 10000

# to copy unsigned apk here to this directory rename wallet-prod-release-unsigned.apk to "apk-to-sign.apk" with  --out Android-signed.apk as signed apk name
#cp -rf wallet/build/outputs/apk/prod/release/wallet-prod-release-unsigned.apk .
/home/c4pt000/Android/Sdk/build-tools/34.0.0/apksigner sign --ks my-release-key.jks --out Bitnet-QT-70032-arm64-v8a-signed.apk android-debug.apk
rm -rf my-release-key.jks 
