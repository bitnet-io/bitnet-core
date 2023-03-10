# 03-10-2023
# we are now offically listed on AtomicDEX Desktop and Mobile offical releases. trade for KMD token or any other asset

# please update to the sha256 version with segwit as of 03-01-2023 we are on a fresh blockchain

* 03-02-2023
check releases for the recent electrum-android version of Bitnet

https://github.com/bitnet-io/bitnet-core/releases

* 03-01-2023 (we offically relaunched and are done with blockchain changes all changes now are only wallet based themes, functionality of the wallet, and general improvements

* 02-27-23 project had blockchain reset to 0 to add segwit support paper wallet removed for now

* 02-26-23
* the project will ONLY SUPPORT BOOST 1.67 now...the entire project was rebased to support segwit using litecoin's source code to rebuild the project
```
wget https://boostorg.jfrog.io/artifactory/main/release/1.67.0/source/boost_1_67_0.tar.gz
tar -xvf boost_1_67_0.tar.gz
sh bootstrap.sh --prefix=/usr
./b2 -j8 (for number of processing cores)
./bjam install

```
* ironing out bugs

* 02-05-2023 check the releases tab for binary updates
* https://github.com/bitnet-io/bitnet-core/releases

# bitnet-core
Bitnet-Core based off of radiocoin with improvements
* 2,000,000,000 total supply (down from 100 B)
* network retargets difficulty every 24 hours (instead of 14 days bitcoin)
* blocks readjust every 3.5 minutes
* paper wallet to backup funds


* 02-08-2023
* this wallet is a completely different chain using deposit addresses with "B" not for radiocoin or ravencoin only for bitnet-core


* add these lines to your bitnet.conf if you have trouble finding peers on the network altcoinbuilders.com are permanent seeds
```
  addnode=bitexplorer.io:8333
  addnode=23.244.172.101:8333
  addnode=bitnet.caldera.network  
  addnode=us.mining4people.com:18333
  addnode=fi.mining4people.com:18333
  addnode=au.mining4people.com:18333
  addnode=br.mining4people.com:18333
  addnode=de.mining4people.com:18333
  addnode=in.mining4people.com:18333


  ```
# this project is compiled with boost-175 if you have trouble building or installing the debian or rpm packages use the scripts in this folder to build dependencies build-deps.sh and check doc/build-unix or doc/build-windows etc.
# check periodically in this directory for bitnet.conf for new "addnodes"
