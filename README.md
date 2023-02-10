* building the project
* (linux systems require boost, qt5, libdb-cxx-5.3-dev and a few other packages provided by the (build-deps.sh scripts)

* ubuntu/debian systems with either 1.65 or 1.67 boost installed (pulled from the build-deps.sh script)
```
git clone https://github.com/bitnet-io/bitnet-core
cd bitnet-core
sh build-debian-deps.sh 
sh autogen.sh
sh build-configure.sh
make -j8 clean
make -j8
make -j8 install
finally copy bitnet.conf to your /home/user/.bitnet or /root/.bitnet folder after running bitnet-qt or bitnetd which should be in your system path
```

* fedora 34/rhel 9 systems with boost 1.75 installed
```
git clone https://github.com/bitnet-io/bitnet-core
cd bitnet-core
sh build-deps-fedora.sh 
sh autogen.sh
sh build-configure.sh
make -j8 clean
make -j8
make -j8 install
finally copy bitnet.conf to your /home/user/.bitnet or /root/.bitnet folder after running bitnet-qt or bitnetd which should be in your system path
```
# windows 10/11 builds (requires docker or ubuntu 22.04)
see doc/build-windows.md for the process of building on windows platforms



# project updates below

* 02-09-2023
* work in progress ANDROID-wallet for bitnet in releases sweep wallet import is offline right now

* bitnet coin explorer is live
http://bitexplorer.io/


* 02-08-2023 some pools to connect to
* https://mining4people.com/pool/bitnet-pplns
* https://zeusminingpool.com/


* 02-05-2023 check the releases tab for binary updates
* https://github.com/bitnet-io/bitnet-core/releases

# bitnet-core
Bitnet-Core based off of radiocoin with improvements
* 2,000,000,000 total supply (down from 100 B)
* network retargets difficulty every seven days (instead of 14 days bitcoin)
* blocks readjust every 10 minutes
* paper wallet to backup funds

* what happens after the 10,000 coin blocks run out since the supply is moving fast possibly under a year from launch?
```
the maximum total supply of Bitnet is 2 billion coins with 10,000 coins per block as a PoW scrypt based coin
The number of Bitnet coins issued will likely never reach 2 billion completely due to the use of rounding operators in the Bitnet codebase.
When the Bitcoin supply reaches its upper limit, no additional bitcoins will be generated. Bitcoin miners will likely earn income only from transaction fees. We believe the transaction fee rewards for miners after the 10,000 coins per block reward runs out will be around 10-100 BIT per block instead of 10,000 BIT per block thus making a scarcity of BIT coins to be passed around but will keep the interest of our users to buy sell and trade coins for their own uses. (We might reach values of anywhere from 0.10 cents to $1.00 estimated per 1 BIT share from the Bitnet wallet where a 100 BIT shares in a users wallet would be estimated to be around $20-$80 USD)
```




# please update to 1.5.5 to fix invalid headers with sync or build this code from scratch with today's (02-08-2023) changes

* if you have trouble connecting to a node use updated bitnet.conf (check back time to time as we grow)

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
* this project is compiled with boost-175 if you have trouble building or installing the debian or rpm packages use the scripts in this folder to build dependencies build-deps.sh and check doc/build-unix or doc/build-windows etc.
* check periodically in this directory for bitnet.conf for new "addnodes"
* since this project isnt using DNS you must manually addnodes with addnodes=ip:port for connectivity

# List of Exchanges 
* https://github.com/bitnet-io/bitnet-core/blob/main/doc/Exchange.md
