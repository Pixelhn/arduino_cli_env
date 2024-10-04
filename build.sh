#!/bin/bash

if [ $ARDUINO_BOARD ]; then
    arduino-cli compile --fqbn $ARDUINO_BOARD src/ || exit -1
fi
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 src/esp01_dht22/

arduino-cli upload -p /dev/ttyUSB0 --fqbn esp8266:esp8266:nodemcuv2 src/esp01_dht22/

arduino-cli lib install --git-url