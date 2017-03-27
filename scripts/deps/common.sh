#!/bin/bash

sudo apt-get update
sudo apt-get install vim git tmux tcpdump python-pip python-wstool ca-certificates apt-transport-https
pio --version || sudo python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"
