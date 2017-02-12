#!/bin/bash

# Exit on error
set -e

# MISC
sudo apt-get update
sudo apt-get install vim git tmux tcpdump arduino python-pip
pip install wstool

sudo apt-get install ros-kinetic-rosserial-arduino ros-kinetic-rosserial
