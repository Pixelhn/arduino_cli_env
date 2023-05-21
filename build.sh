#!/bin/bash

if [ $ARDUINO_BOARD ]; then
    arduino-cli compile --fqbn $ARDUINO_BOARD src/ || exit -1
fi
