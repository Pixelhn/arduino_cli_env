#!/bin/bash

export PATH=$PATH:$(pwd)/bin

arduino-cli version

if [ $? -ne 0 ]; then
    cd bin
    arduino-cli_install.sh || exit
fi


ARDUINO_TTY=$(arduino-cli board list | grep arduino)
arr=($ARDUINO_TTY)
IFS=' '

echo ARDUINO_TTY ${arr[0]}

export ARDUINO_TTY=${arr[0]}