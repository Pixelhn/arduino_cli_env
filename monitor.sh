#!/bin/bash

BAUDRATE=

if [ $1 ]; then
    BAUDRATE="--config $1"
fi

while [ 1 ]
do 
    if [ -c $ARDUINO_TTY ]; then
        arduino-cli monitor -p $ARDUINO_TTY  $BAUDRATE
        echo disconnect $ARDUINO_TTY
    else
        echo do not find $ARDUINO_TTY
    fi
    sleep 1
done
