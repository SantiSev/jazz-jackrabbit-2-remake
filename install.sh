#!/bin/bash

sudo apt-get update > /dev/null

echo "Installing dependencies"
sudo apt install -y libsdl2-dev > /dev/null
echo "libsdl2-dev installed"

sudo apt install -y libsdl2-image-dev > /dev/null
echo "libsdl2-image-dev installed"

sudo apt install -y libsdl2-ttf-dev > /dev/null
echo "libsdl2-ttf-dev installed"

sudo apt install -y libsdl2-mixer-dev > /dev/null
echo "libsdl2-mixer-dev installed"
