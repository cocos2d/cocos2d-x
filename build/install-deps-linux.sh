#!/bin/bash

# Change directory to the location of this script
echo "This Shell Script will install dependencies for cocos2d-x" 
echo "if you execute this shell more than once it will get errors when building libGLFW.so"
echo -n "Are you continue? (y/n) "
read answer
if echo "$answer" | grep -iq "^y" ;then
    echo "It will take few minutes"
else
    exit
fi

cd $(dirname ${BASH_SOURCE[0]})

if [ ! $(command -v apt-get) ]; then
  echo "Not a .deb package system. Please install dependencies manually"
  exit 0
fi

apt-get update
apt-get install -y libstdc++6 g++ libgdk-pixbuf2.0-dev python-pip cmake libx11-dev libxmu-dev libglu1-mesa-dev libgl2ps-dev libxi-dev libzip-dev libpng-dev libcurl4-gnutls-dev libfontconfig1-dev libsqlite3-dev libglew-dev libssl-dev libgtk-3-dev libglfw3 libglfw3-dev xorg-dev

echo "Cocos uses GCC Version: `gcc --version`"
echo "Cocos uses G++ Version: `g++ --version`"
echo "Cocos uses ld Version: `ld --version`"
echo "Cocos uses /usr/bin/ld Version: `/usr/bin/ld --version`"

