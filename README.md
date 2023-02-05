# bitnet-core
Bitnet-Core based off of radiocoin with improvements
* 20,000,000,000 total supply (down from 100 B)
* network retargets difficulty every 3 hours (instead of 14 days bitcoin)
* blocks readjust every 2.5 minutes
* paper wallet to backup funds

* copy bitnet-data-dir-01-24-2023.tar.gz to your /home folder for the data dir and tar -xvf for a basic blockchain if you have trouble connecting to a node use updated bitnet.conf (check back time to time as we grow)

* this wallet is a completely different chain using deposit addresses with "R" not for radiocoin or ravencoin only for bitnet-core

# this project is compiled with boost-175 if you have trouble building or installing the debian or rpm packages use the scripts in this folder to build dependencies build-deps.sh
# check periodically in this directory for bitnet.conf for new "addnodes"
# since this project isnt using DNS you must manually addnodes with addnodes=ip:port for connectivity
