* 02-26-23
* the project will ONLY SUPPORT BOOST 1.67 now...the entire project was rebased to support segwit using viacoin's source code to rebuild the project
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
* 20,000,000,000 total supply (down from 100 B)
* network retargets difficulty every seven days (instead of 14 days bitcoin)
* blocks readjust every 10 minutes
* paper wallet to backup funds

* copy bitnet-data-dir-02-04-2023.tar.gz to your /home/user folder for the data dir and tar -xvf for a basic blockchain if you have trouble connecting to a node use updated bitnet.conf (check back time to time as we grow)

* 02-08-2023
* this wallet is a completely different chain using deposit addresses with "B" not for radiocoin or ravencoin only for bitnet-core


* add these lines to your bitnet.conf if you have trouble finding peers on the network altcoinbuilders.com are permanent seeds
```
addnode=170.187.167.146:8333
  addnode=149.28.51.213:8333
  addnode=108.61.149.178:8333
  addnode=45.77.77.239:8333
  addnode=seed01.altcoinbuilders.com:8333
  addnode=seed02.altcoinbuilders.com:8333
  addnode=seed03.altcoinbuilders.com:8333
  addnode=seed04.altcoinbuilders.com:8333
  addnode=[2600:3c03::f03c:93ff:fefc:ed9c]:8333
  ```
# this project is compiled with boost-175 if you have trouble building or installing the debian or rpm packages use the scripts in this folder to build dependencies build-deps.sh and check doc/build-unix or doc/build-windows etc.
# check periodically in this directory for bitnet.conf for new "addnodes"
# since this project isnt using DNS you must manually addnodes with addnodes=ip:port for connectivity
