#!/bin/bash

arduino-cli update
arduino-cli upgrade

arduino-cli board list

arduino-cli core install arduino:avr

arduino-cli completion bash > arduino-cli.sh 

sudo mv arduino-cli.sh /etc/bash_completion.d/

ln -s $(pwd)/.arduino15 ~/.arduino15