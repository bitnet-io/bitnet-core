#!/bin/sh
while :
do
./bitnet-cli getblockchaininfo | grep blocks
sleep 1s
done
