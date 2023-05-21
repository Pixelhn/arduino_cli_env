#!/bin/bash


arduino-cli compile --fqbn arduino:avr:uno src/ || exit

arduino-cli upload -p $ARDUINO_TTY --fqbn arduino:avr:uno  src/

arduino-cli monitor -p $ARDUINO_TTY  --config 115200