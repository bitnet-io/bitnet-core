# 03-21-2023
# please update to the changes from 03-21-2023
# we had an issue at block 11622 please update to the latest changes as we brace for DGW at block 11625

# 03-18-2023
# DarkGravityWave has now replaced pow.cpp to protect miners with the updated algorithm in the github source 
# updated binaries also

# 03-14-2023
# we are now listed on Xeggex exchange
![s1](https://github.com/bitnet-io/bitnet-core/releases/download/exchanges/bitnet-listing.png)

# 03-12-2023
changes to validation.cpp for halving it is advised everyone running a full node as a pool or an exchange should update to the latest changes of src/validation.cpp in the code (we are trying to change from 10,000 blocks to 100,000 blocks for halving)

# 03-11-2023
# we are now offically listed on https://bitxonex.com after we tested for a few hours to iron out bugs
![s1](https://github.com/bitnet-io/bitnet-core/releases/download/exchanges/listing-bitxonex.com.png)
![s1](https://github.com/bitnet-io/bitnet-core/releases/download/exchanges/deposit-address.png)

# 03-10-2023
# we are now offically listed on AtomicDEX Desktop and Mobile offical releases. trade for KMD token or any other asset
![s1](https://github.com/bitnet-io/bitnet-core/releases/download/exchanges/komodo.png)

# exchanges 
https://github.com/bitnet-io/bitnet-core/releases/tag/exchanges

# pools
https://github.com/bitnet-io/bitnet-core/releases/tag/pools

# please update to the sha256 version with segwit as of 03-01-2023 we are on a fresh blockchain
(no support to build this with ubuntu 18.04 if you are on ubuntu 18.04 please update to ubuntu 22.04)

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

