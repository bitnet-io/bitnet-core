# how to build bitnet-qt with 12 cores (change -j12 to your number of cpu cores -j4 for 4 cores -j8 for 8 cores for a faster build)

```
git clone https://github.com/bitnet-io/bitnet-core
cd bitnet-core/depends
make -j12 HOST=x86_64-pc-linux-gnu
cd ..
./autogen.sh
CONFIG_SITE=$PWD/depends/x86_64-pc-linux-gnu/share/config.site ./configure
make -j12
make -j12 install
```


# 12-01-2023
# we now have an offical QR code for the bitnet-io.org website
![s1](https://github.com/bitnet-io/bitnet-core/releases/download/QR/bitnet-io-QR.png)

<br>
<br>
<br>
<br>
<br>

# 12-01-2023
# We are now listed on nonkyc.io 
# nonkyc.io doesnt require any ID any they have unlimited depost and withdrawals
![s1](https://github.com/bitnet-io/bitnet-core/releases/download/exchanges/GASVKhTXsAAcWyd.jpg)

<br>
<br>
<br>
<br>
<br>

# 11-27-2023
# binaries have been updated to fork at block height 150,000 for coin rewards of 100 BIT per block to preserve the network for 30 years
* this is a mandatory update for pools and solo miners

```
this introduces protocol version 70020 of bitnet-qt and bitnetd which kicks in at block height 150,000
 at block height 150,000 the 10,000 coins will be over and the new rewards will be 100 BIT per block
 this will ensure that the network can run for 30 years and still distribute 100 coins per block
```

<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>

# 10-24-2023
# binaries have been updated to linux-95000 and windows-95000
* this is a mandatory update for pools and solo miners
```
this introduces protocol version 70018 of bitnet-qt and bitnetd which kicks in at block height 95000
 has adjustments for DGW to increase the average calculation from 24 blocks
 to 60 blocks thus increasing the time window and causing smoother difficulty changes
```

<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>

# https://bitnet-io.org

# 04-18-2023
# we are now listed on bimex.live which is a new exchange getting off the ground
# https://bimex.live/trade/index/market/bit_usdt/
![s1](https://github.com/bitnet-io/bitnet-core/releases/download/exchanges/bimex.png)


# 03-21-2023 continued
# DarkGravityWave is stable and it kicked in @11625 as a result our blockchain difficulty has drastically 
# decreased and miners are happy
# we dropped down from 1,250,000,000 difficulty to around 100,000,000 difficulty and miners sure are pleased.


# 03-21-2023
# please update to the changes from 03-21-2023 and -reindex
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
  addnode=bitnet-io.org:8333
  addnode=38.242.200.177:8333
  addnode=149.50.96.167:20029



  ```
author dhweinberg
