WIP** 
https://www.youtube.com/watch?v=U-IIKVaEhrA

* 05-29-2021 sync issues just built 8 nodes as a starting point check updated bitnet.conf

place bootstrap -> /root/.bitnet/
where /home/user/.bitnet
is your directory
early 140 block boostrap for nodes
restart bitnetd or bitnet-qt to load boostrap.dat

https://github.com/c4pt000/radioCOIN/raw/main/bootstrap.dat

where root is the current user 
```
cd /root/.bitnet
wget https://github.com/c4pt000/radioCOIN/raw/main/bootstrap.dat
killall bitnetd
bitnetd -daemon      or bitnet-qt
bitnet-cli getinfo
```

# RADIOACTIVE!!   ** STILL A WIP (android app / ios soon)

macOS,fedora/rhel, debian/ubuntu 

![s1](https://raw.githubusercontent.com/c4pt000/radioCOIN/main/ACTIVE-radio.png)

still a work in progress, trying to mint block 0 so the network can propegate,
made changes for DOGE, instead of litecoin source, added paper-wallet back, fixed the "about"


same DOGE block reward design but for bitnet (random between 0-1,000,000 RADC
```
Block 1 — 100,000: 0-1,000,000 bitnet(RADC)
Block 100,001 — 200,000: 0-500,000 bitnet(RADC)
Block 200,001 — 300,000: 0-250,000 bitnet(RADC)
Block 300,001 — 400,000: 0-125,000 bitnet(RADC)
Block 400,001 — 500,000: 0-62,500 bitnet(RADC)
Block 500,001 — 600,000: 0-31,250 bitnet(RADC)
Block 600,001+: 10,000 bitnet(RADC)
```
![s1](https://raw.githubusercontent.com/c4pt000/radioCOIN/main/block-reward-2.png)
![s1](https://raw.githubusercontent.com/c4pt000/radioCOIN/main/block-reward.png)



*NON-functional demo   semi functional stuck at block zer0   needs to mint block 0
<br> 
```
```
must use these nodes in the conf network just starting deploying in the last 2 or 3 days
addnode=45.56.81.243
addnode=104.237.145.126
addnode=109.237.25.123
addnode=139.162.123.199
addnode=194.195.117.160
addnode=172.105.77.251
addnode=194.195.250.123
addnode=172.104.167.106
addnode=162.216.17.71
```
https://raw.githubusercontent.com/c4pt000/radioCOIN/main/bitnet.conf
```
```
fedora/rhel

wget https://github.com/c4pt000/radioCOIN/releases/download/experimental/bitnet-2.1.4_exp_assert_check-2.x86_64.rpm

or for debian based systems

wget https://github.com/c4pt000/radioCOIN/releases/download/experimental/bitnet_2.1.4-exp-assert-check-1_amd64.deb

macOS

wget https://github.com/c4pt000/radioCOIN/releases/download/experimental/Bitnet-Qt.dmg
```
```
{
  "version": 1140300,
  "protocolversion": 70015,
  "walletversion": 130000,
  "balance": 0.00000000,
  "blocks": 0,
  "timeoffset": 0,
  "connections": 8,
  "proxy": "",
  "difficulty": 0.000244140625,
  "testnet": false,
  "keypoololdest": 1622318528,
  "keypoolsize": 100,
  "paytxfee": 0.00000000,
  "relayfee": 1.00000000,
  "errors": ""
}
```

  yum install bitnet-2.1.1_exp-2.x86_64.rpm -y
  

# RADIOCOIN POOL
![s1](https://raw.githubusercontent.com/c4pt000/radioCOIN/main/RADIOCOIN-POOL.png)

```
"chain": "main",
  "blocks": 0,
  "headers": 0,
  "bestblockhash": "000002e2e76fef07722c875e9a68b1ce32bd2964e2df8ce70d9d31ab263f5fd2",
  "difficulty": 0.000244140625,
  "mediantime": 1622171724,
  "verificationprogress": 1.330529405468109e-08,
  "initialblockdownload": true,
  "chainwork": "0000000000000000000000000000000000000000000000000000000000100010",
  "size_on_disk": 486,
  "pruned": false,
```

```
mkdir anodes

bitnetd -listen -upnp=1 -bind=127.0.0.1 -datadir=./anodes -addnode=172.104.72.150 -addnode=162.216.17.71 -addnode=127.0.0.1 -deprecatedrpc=generate -rpcpassword=radio -rpcuser=coin -rpcport=9334 -port=9335 --daemon --server
 
alias node1="bitnet-cli -rpcpassword=radio -rpcuser=coin -rpcport=9334"

 node1 getblockhash 0 
 node1 getblock 000008f3108b9b62492a71ff55f58f90678baf0ddeb75d11480f9355df6d1204 false
 
 010000000000000000000000000000000000000000000000000000000000000000000000f5247939a78482b7824f5f359ce35e78773216d4355b098b69fdfaed0b0df9d24c60b060f0ff0f1e714901000101000000010000000000000000000000000000000000000000000000000000000000000000ffffffff1e04f0ff0f1e010416526164696f436f696e206d757369632077616c6c6574ffffffff010058850c02000000434104770ee175cb5530e95cd615c061738719116d871ad9fcc9292ea6b0d396f7d270c12f351ff674b030299b537e9fa062511ac67b8bfc4d68cfcc2fd86158e0e6b3ac00000000


which becomes as an 80-byte header
010000000000000000000000000000000000000000000000000000000000000000000000f5247939a78482b7824f5f359ce35e78773216d4355b098b69fdfaed0b0df9d24c60b060f0ff0f1e71490100

mine block 0
cpp_miner mine 010000000000000000000000000000000000000000000000000000000000000000000000f5247939a78482b7824f5f359ce35e78773216d4355b098b69fdfaed0b0df9d24c60b060f0ff0f1e71490100 -v
Verbosity enabled.  Level is 1
target: 00000ffff0000000000000000000000000000000000000000000000000000000
block header: 010000000000000000000000000000000000000000000000000000000000000000000000f5247939a78482b7824f5f359ce35e78773216d4355b098b69fdfaed0b0df9d24c60b060f0ff0f1e71490100
nonce: 0x00014971
block hash: 000008f3108b9b62492a71ff55f58f90678baf0ddeb75d11480f9355df6d1204










https://jbaczuk.github.io/blockchain_fundamentals/2-Fundamentals/2.5-Mining.html

for lower powLimit 
----------------------
./sha256.py  010000000000000000000000000000000000000000000000000000000000000000000000f5247939a78482b7824f5f359ce35e78773216d4355b098b69fdfaed0b0df9d24c60b060f0ff0f1e714901000101000000010000000000000000000000000000000000000000000000000000000000000000ffffffff1e04f0ff0f1e010416526164696f436f696e206d757369632077616c6c6574ffffffff010058850c02000000434104770ee175cb5530e95cd615c061738719116d871ad9fcc9292ea6b0d396f7d270c12f351ff674b030299b537e9fa062511ac67b8bfc4d68cfcc2fd86158e0e6b3ac00000000


01cab59e0cea7ad08927afccb8a4bdf5a5e3946b135bc4e9024b3239e99e7f36

python2 reverse.endian.py 01cab59e0cea7ad08927afccb8a4bdf5a5e3946b135bc4e9024b3239e99e7f36

367f9ee939324b02e9c45b136b94e3a5f5bda4b8ccaf2789d07aea0c9eb5ca01

find bits of block 0 header
---------------------------
node1 getblock 000008f3108b9b62492a71ff55f58f90678baf0ddeb75d11480f9355df6d1204
{
  "hash": "000008f3108b9b62492a71ff55f58f90678baf0ddeb75d11480f9355df6d1204",
  "confirmations": 1,
  "strippedsize": 238,
  "size": 238,
  "weight": 952,
  "height": 0,
  "version": 1,
  "versionHex": "00000001",
  "merkleroot": "d2f90d0bedfafd698b095b35d4163277785ee39c355f4f82b78284a7397924f5",
  "tx": [
    "d2f90d0bedfafd698b095b35d4163277785ee39c355f4f82b78284a7397924f5"
  ],
  "time": 1622171724,
  "mediantime": 1622171724,
  "nonce": 84337,
  "bits": "1e0ffff0",
  "difficulty": 0.000244140625,
  "chainwork": "0000000000000000000000000000000000000000000000000000000000100010"
}


  "bits": "1e0ffff0",

python2 reverse.endian.py 1e0ffff0
f0ff0f1e

```


  
  or from source
  ```
  sh autogen.sh 
./configure --prefix=/usr --with-incompatible-bdb
make -j24
make -j24 install
checkinstall --install=no --exclude=/sys/fs/selinux
alien --scripts --to-rpm *.deb 
```
  
  ![s1](https://raw.githubusercontent.com/c4pt000/radioCOIN/main/PAPER-WALLET.png)
  ![s1](https://raw.githubusercontent.com/c4pt000/radioCOIN/main/bitnet-current.png)
  
  # MAINnet
  ```
  
  bitnet-qt -listen -upnp=1 -bind=127.0.0.1 -addnode=172.104.72.150 -addnode=162.216.17.71 -addnode=127.0.0.1 -deprecatedrpc=generate -rpcpassword=radio -rpcuser=coin --daemon 
  
 bitnetd -listen -upnp=1 -bind=127.0.0.1 -datadir=./nodes -addnode=172.104.72.150 -addnode=162.216.17.71 -addnode=127.0.0.1 -deprecatedrpc=generate -rpcpassword=radio -rpcuser=coin -rpcport=9334 -port=9335 --daemon --server


  
  alias node1="bitnet-cli -rpcpassword=radio -rpcuser=coin -rpcport=9334"
  node1 addnode "162.216.17.71:9334" "add"
  node1 addnode "127.0.0.1:9334" "add"
  node1 addnode "172.104.72.150:9334" "add"
  node1 getblockchaininfo
node1 generate 1
node1 getbalance

```
  
  
 ```
[root@localhost /]# node1 getbalance
2600.00000000
```





sample conf for running a node (not for an RPC connection)
/root/.bitnet/bitnet.conf 
----------------------------
```
#prune=2200

dbcache=100
maxorphantx=10
maxmempool=50
maxconnections=40
maxuploadtarget=5000


rpcuser=bitnet
rpcpassword=randompasshere
rpcport=9332
port=9333

addnode=45.56.81.243
addnode=104.237.145.126
addnode=109.237.25.123
addnode=139.162.123.199
addnode=194.195.117.160
addnode=172.105.77.251
addnode=194.195.250.123
addnode=172.104.167.106

connect=45.56.81.243
connect=104.237.145.126
connect=109.237.25.123
connect=139.162.123.199
connect=194.195.117.160
connect=172.105.77.251
connect=194.195.250.123
connect=172.104.167.106


whitelist=45.56.81.243/24
whitelist=104.237.145.126/24
whitelist=109.237.25.123/24
whitelist=139.162.123.199/24
whitelist=194.195.117.160/24
whitelist=172.105.77.251/24
whitelist=194.195.250.123/24
whitelist=172.104.167.106/24

# important to rebroadcast between peers
whitelistrelay=1
whitelistforcerelay=1
blocksonly=1

rpcconnect=0.0.0.0
rpcallowip=0.0.0.0/0
rpcbind=0.0.0.0
rpcallowport=9332


listen=1
upnp=1
dnsseed=1
dns=1

daemon=1
server=1





#bind=127.0.0.1
#maxconnections=10
#your ip or 0.0.0.0/24 for complete WAN access remote (treat as dangerous for to allow remote rpc)
#bind=127.0.0.1




```



# testing frontend through REGtest
![s1](https://raw.githubusercontent.com/c4pt000/radioCOIN/main/mined-minted.png)
```
bitnetd -regtest -port=1111 -datadir=./ -rpcport=1234 -deprecatedrpc=generate --daemon
bitnet-qt -regtest -port=2222 -datadir=./newreg -rpcport=5467 -deprecatedrpc=generate --daemon
```


 

todo:
https://stackoverflow.com/questions/47828172/encountering-readblockfromdisk-errors-in-block-header-at-cblockdiskposnfile-0/48606397#48606397

https://bitcoin.stackexchange.com/questions/67060/error-readblockfromdisk-errors-in-block-header-at-cblockdiskposnfile-0-npos



https://medium.com/@kay.odenthal_25114/create-a-private-bitcoin-network-with-simulated-mining-b35f5b03e534





todo: mine block 0 
https://github.com/c4pt000/cpp_miner
```
$ cpp_miner mine <blockHeader 80B-hex> OR <version 4B-hex> <hashPrevBlock 32B-hex> <merkleRoot 32B-hex> <time 4B-hex> <nBits 4B-hex> <nonce 4B-hex>
$ cpp_miner genesisgen <pubkey 65B-hex> "<coinbase-message 91B-string>" <value 8B-decimal> <time 4B-hex> <nBits 4B-hex> <nonce 4B-hex>



 cpp_miner mine 

<blockHeader 80B-hex> OR <version 4B-hex> <hashPrevBlock 32B-hex> <merkleRoot 32B-hex> <time 4B-hex> <nBits 4B-hex> <nonce 4B-hex>


genesis = CreateGenesisBlock(1621321415, 0x00000003, 545259519, 1, 1000000000 * COIN);
const char* pszTimestamp = "in music we trust";

04c671ae19bc3a3acf1bfec3930653029cf9fc5681376ea12e8593b76dbe8d85d611f09b4190c219f8ac38999a5ad0c431d70b72d21744513db6e2304b94d25bad

hash->("0x4f014ebd57f5d6342f8dfa723e08d3401f92a83464fc66a0ef732325659d756a")
merkle->	("0x7528171112285616586b9702910b8474013da81d2d37776ff56c881f45126b95")


 ParseHex("04c671ae19bc3a3acf1bfec3930653029cf9fc5681376ea12e8593b76dbe8d85d611f09b4190c219f8ac38999a5ad0c431d70b72d21744513db6e2304b94d25bad") << OP_CHECKSIG;



cpp_miner mine 	0x00000003  0x4f014ebd57f5d6342f8dfa723e08d3401f92a83464fc66a0ef732325659d756a 0x7528171112285616586b9702910b8474013da81d2d37776ff56c881f45126b95 1621321415 1000000000 545259519
```

# radioCOIN (needs nodes testing at block 0 genesis block might be configured wrong)

# to help the music industry secure money from the loss of recordable music and mp3 leaks, and to control noisy car radios with fees for playing the volume too loud at odd hours

requires requires boost-1.75

cat /root/.bitnet/debug.log
```
2021-05-21T05:57:47Z LoadBlockIndexDB: last block file = 0
2021-05-21T05:57:47Z LoadBlockIndexDB: last block file info: CBlockFileInfo(blocks=0, size=0, heights=0...0, time=1970-01-01...1970-01-01)
```
```
2021-05-21T05:57:47Z 
2021-05-21T05:57:47Z Bitnet Core version v0.18.1.0-e4beaa4-dirty (release build)
2021-05-21T05:57:47Z Assuming ancestors of block b34a457c601ef8ce3294116e3296078797be7ded1b0d12515395db9ab5e93ab8 have valid signatures.
2021-05-21T05:57:47Z Setting nMinimumChainWork=0000000000000000000000000000000000000000000002ee655bf00bf13b4cca
2021-05-21T05:57:47Z Using the 'sse4(1way),sse41(4way),avx2(8way)' SHA256 implementation
2021-05-21T05:57:47Z Using RdRand as an additional entropy source
2021-05-21T05:57:47Z Default data directory /root/.bitnet
2021-05-21T05:57:47Z Using data directory /root/.bitnet
2021-05-21T05:57:47Z Config file: /root/.bitnet/bitnet.conf (not found, skipping)
2021-05-21T05:57:47Z Using at most 125 automatic connections (1024 file descriptors available)
2021-05-21T05:57:47Z Using 16 MiB out of 32/2 requested for signature cache, able to store 524288 elements
2021-05-21T05:57:47Z Using 16 MiB out of 32/2 requested for script execution cache, able to store 524288 elements
2021-05-21T05:57:47Z Using 16 threads for script verification
2021-05-21T05:57:47Z scheduler thread start
2021-05-21T05:57:47Z Using wallet directory /root/.bitnet/wallets
2021-05-21T05:57:47Z init message: Verifying wallet(s)...
2021-05-21T05:57:47Z Using BerkeleyDB version Berkeley DB 5.3.28: (September  9, 2013)
2021-05-21T05:57:47Z Using wallet /root/.bitnet/wallets
2021-05-21T05:57:47Z BerkeleyEnvironment::Open: LogDir=/root/.bitnet/wallets/database ErrorFile=/root/.bitnet/wallets/db.log
2021-05-21T05:57:47Z init message: Loading banlist...
2021-05-21T05:57:47Z ERROR: DeserializeFileDB: Failed to open file /root/.bitnet/banlist.dat
2021-05-21T05:57:47Z Invalid or missing banlist.dat; recreating
2021-05-21T05:57:47Z Cache configuration:
2021-05-21T05:57:47Z * Using 2.0 MiB for block index database
2021-05-21T05:57:47Z * Using 8.0 MiB for chain state database
2021-05-21T05:57:47Z * Using 440.0 MiB for in-memory UTXO set (plus up to 286.1 MiB of unused mempool space)
2021-05-21T05:57:47Z init message: Loading block index...
2021-05-21T05:57:47Z Opening LevelDB in /root/.bitnet/blocks/index
2021-05-21T05:57:47Z Opened LevelDB successfully
2021-05-21T05:57:47Z Using obfuscation key for /root/.bitnet/blocks/index: 0000000000000000
2021-05-21T05:57:47Z LoadBlockIndexDB: last block file = 0
2021-05-21T05:57:47Z LoadBlockIndexDB: last block file info: CBlockFileInfo(blocks=0, size=0, heights=0...0, time=1970-01-01...1970-01-01)
2021-05-21T05:57:47Z Checking all blk files are present...
2021-05-21T05:57:47Z Initializing databases...
2021-05-21T05:57:47Z Pre-allocating up to position 0x1000000 in blk00000.dat
2021-05-21T05:57:47Z Opening LevelDB in /root/.bitnet/chainstate
2021-05-21T05:57:47Z Opened LevelDB successfully
2021-05-21T05:57:47Z Wrote new obfuscate key for /root/.bitnet/chainstate: 59cf85edd5d4ab5d
2021-05-21T05:57:47Z Using obfuscation key for /root/.bitnet/chainstate: 59cf85edd5d4ab5d
2021-05-21T05:57:47Z init message: Rewinding blocks...
2021-05-21T05:57:47Z  block index             245ms
2021-05-21T05:57:47Z init message: Loading wallet...
2021-05-21T05:57:47Z BerkeleyEnvironment::Open: LogDir=/root/.bitnet/wallets/database ErrorFile=/root/.bitnet/wallets/db.log
2021-05-21T05:57:48Z [default wallet] nFileVersion = 180100
2021-05-21T05:57:48Z [default wallet] Keys: 0 plaintext, 0 encrypted, 0 w/ metadata, 0 total. Unknown wallet records: 0
2021-05-21T05:57:48Z [default wallet] Performing wallet upgrade to 169900
2021-05-21T05:57:49Z [default wallet] keypool added 2000 keys (1000 internal), size=2000 (1000 internal)
2021-05-21T05:57:49Z [default wallet] Wallet completed loading in            1859ms
2021-05-21T05:57:49Z [default wallet] setKeyPool.size() = 2000
2021-05-21T05:57:49Z [default wallet] mapWallet.size() = 0
2021-05-21T05:57:49Z [default wallet] mapAddressBook.size() = 0
2021-05-21T05:57:49Z ERROR: ReadBlockFromDisk: Errors in block header at CDiskBlockPos(nFile=0, nPos=8)
2021-05-21T05:57:49Z *** Failed to read block
2021-05-21T05:57:49Z Error: Error: A fatal internal error occurred, see debug.log for details
```

```
optional ->  yum groupinstall "C Development Tools and Libraries" -y
yum install git-core libdb-cxx-devel libdb-cxx openssl-devel libevent-devel java-11-openjdk-devel cppzmq-devel  qrencode-devel qt5-qtbase-devel.x86_64 qt5-linguist-5.15.2-5.fc34.x86_64 protobuf-devel  cargo boost* boost-devel miniupnpc-devel.x86_64 diffutils qt-devel qt4-devel wget -y

wget https://github.com/c4pt000/radioCOIN/releases/download/1.1.0-fedora34-build-environment/bitnet-1.1.0_fedora34-2.x86_64.rpm
 
for selinux 4kb error
--------------------
cp -rf bitnet-1.1.0_fedora34-2.x86_64.rpm /
rpm2cpio bitnet-1.1.0_fedora34-2.x86_64.rpm | cpio -idmv
```
ubuntu 20.10 requires boost-1.75
```

apt-get install libzmq* boost* -y

wget https://boostorg.jfrog.io/artifactory/main/release/1.75.0/source/boost_1_75_0.tar.gz


```
![s1](https://raw.githubusercontent.com/c4pt000/radioCOIN/main/src/qt/res/icons/paper_wallet.png.back.png)
![s1](https://raw.githubusercontent.com/c4pt000/radioCOIN/main/src/qt/res/icons/paper_wallet.png.front.png)
* fedora 34
source build
```
 yum groupinstall "C Development Tools and Libraries" -y
 
 yum install git-core libdb-cxx-devel libdb-cxx openssl-devel libevent-devel java-11-openjdk-devel cppzmq-devel \
 qrencode-devel qt5-qtbase-devel.x86_64 qt5-linguist-5.15.2-5.fc34.x86_64 protobuf-devel opencv-devel.x86_64 \
 opencv-devel-4.5.2-1.fc34.x86_64 cargo boost* boost-devel miniupnpc-devel.x86_64 diffutils qt-devel qt4-devel -y
 
 ./autogen.sh

 ./configure --with-incompatible-bdb --prefix=/usr --enable-sse2
  
  make -j24
  make -j24 install
 
  optional to make deb package and or rpm package
  -----------------------------------------------
  checkinstall --install=no --exclude=/sys/fs/selinux
  alien --scripts --to-rpm radio*.deb

  
  bitnet-qt
  or bitnetd      (bitnet-cli getinfo)
```

Bitnet Core integration/staging tree
=====================================

[![Build Status](https://travis-ci.org/bitnet-project/bitnet.svg?branch=master)](https://travis-ci.org/bitnet-project/bitnet)

https://bitnet.org

What is Bitnet?
----------------

radioCOIN (needs nodes testing at block 0 genesis block might be configured wrong)
to help the music industry secure money from the loss of recordable music and mp3 leaks, and to control noisy car radios with fees for playing the volume too loud at odd hours

Bitnet is an experimental digital currency that enables instant payments to
anyone, anywhere in the world. Bitnet uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. Bitnet Core is the name of open source
software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the Bitnet Core software, see [https://bitnet.org](https://bitnet.org).

License
-------

Bitnet Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/bitnet-project/bitnet/tags) are created
regularly to indicate new official, stable release versions of Bitnet Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md)
and useful hints for developers can be found in [doc/developer-notes.md](doc/developer-notes.md).

The developer [mailing list](https://groups.google.com/forum/#!forum/bitnet-dev)
should be used to discuss complicated or controversial changes before working
on a patch set.

Developer IRC can be found on Freenode at #bitnet-dev.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/test) are installed) with: `test/functional/test_runner.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and macOS, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

Translations
------------

We only accept translation fixes that are submitted through [Bitcoin Core's Transifex page](https://www.transifex.com/projects/p/bitcoin/).
Translations are converted to Bitnet periodically.

Translations are periodically pulled from Transifex and merged into the git repository. See the
[translation process](doc/translation_process.md) for details on how this works.

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.
