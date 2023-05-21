#!/bin/bash

./build.sh || exit

arduino-cli upload -p $ARDUINO_TTY --fqbn $ARDUINO_BOARD  src/
