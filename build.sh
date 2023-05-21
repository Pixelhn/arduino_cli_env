#!/bin/bash


arduino-cli compile --fqbn $ARDUINO_BOARD src/ || exit

arduino-cli upload -p $ARDUINO_TTY --fqbn $ARDUINO_BOARD  src/

arduino-cli monitor -p $ARDUINO_TTY  --config 115200