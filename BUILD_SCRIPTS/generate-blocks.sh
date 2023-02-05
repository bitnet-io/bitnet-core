# Script to generate a new block every minute
# Put this script at the root of your unpacked folder
#!/bin/bash

echo "Generating a block every minute. Press [CTRL+C] to stop.."


while :
do
        echo "Generate a new block `date '+%d/%m/%Y %H:%M:%S'`"
        bitnet-cli generate 1
done
