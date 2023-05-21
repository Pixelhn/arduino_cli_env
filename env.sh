#!/bin/bash

export PATH=$PATH:$(pwd)/bin

ARDUINO_TTY=$(arduino-cli board list | grep arduino)
arr=($ARDUINO_TTY)
IFS=' '

echo ARDUINO_TTY ${arr[0]}

export ARDUINO_TTY=${arr[0]}