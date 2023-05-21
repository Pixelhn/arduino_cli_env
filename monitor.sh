#!/bin/bash

BAUDRATE=

if [ $1 ]; then
    BAUDRATE="--config $1"
fi

arduino-cli monitor -p $ARDUINO_TTY  $BAUDRATE