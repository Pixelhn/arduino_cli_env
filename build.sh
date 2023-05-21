#!/bin/bash

arduino-cli compile --fqbn $ARDUINO_BOARD src/ || exit -1