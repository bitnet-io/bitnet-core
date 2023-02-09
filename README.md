

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

# List of Exchanges (this is a work in progress to get listed since we are a new coin as of 02-08-2023 some things to consider)
* https://github.com/bitnet-io/bitnet-core/blob/main/doc/Exchange.md
