#!/bin/bash

echo 'https://github.com/c4pt000/cpuminer'
echo 'setup two nodes connected to each other locally with addnode=127.0.0.1:8333 in one bitnet.conf and the other bitnet.conf in a different user dir with and port=8334 rpcport=9334 and rpcuser=rpcuser rpcpassword=rpcpassword mine for coins solo use your receiving address to get mined coins'


echo ' ./minerd -o http://127.0.0.1:9334 -u rpcuser -p rpcpassword --coinbase-addr=RMFtPQPdVDM-your-address-here-from-the-wallet'


