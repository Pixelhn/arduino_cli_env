#!/bin/bash

ARC=$(uname -m)

if ( [ $ARC == "x86_64" ] ); then
    echo x86
    wget https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Linux_64bit.tar.gz
    gzip -d arduino-cli_latest_Linux_64bit.tar.gz
    tar -xf arduino-cli_latest_Linux_64bit.tar
    rm arduino-cli_latest_Linux_64bit.tar
elif ( [ $ARC == "aarch64" ] ); then
    echo arm64
    wget https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Linux_ARM64.tar.gz
    gzip -d arduino-cli_latest_Linux_ARM64.tar.gz
    tar -xf arduino-cli_latest_Linux_ARM64.tar
    rm arduino-cli_latest_Linux_ARM64.tar
elif ( [ $ARC == "armv7l" ] ); then
    echo armv7l

fi

cd ..
PWD=$(pwd)

sed 's|'"PWD"'|'"${PWD}"'|g' .arduino15/.arduino-cli.yaml > .arduino15/arduino-cli.yaml

ln -s -f $(pwd)/.arduino15 ~/.arduino15

cd -

./arduino-cli completion bash > arduino-cli.sh
sudo mv arduino-cli.sh /etc/bash_completion.d/

./arduino-cli update
./arduino-cli upgrade
./arduino-cli core install arduino:avr

./arduino-cli version > ver