#!/bin/bash

./build.sh || exit

if [ $ARDUINO_TTY ]; then
    arduino-cli upload -p $ARDUINO_TTY --fqbn $ARDUINO_BOARD  src/
    ./monitor.sh
else
    echo do not find tty $ARDUINO_TTY
fi
