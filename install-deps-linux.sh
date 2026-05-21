#!/bin/bash

echo "This Shell Script will install dependencies for cocos2d-x" 
echo -n "Are you continue? (y/n) "
read answer
if echo "$answer" | grep -iq "^y" ;then
    echo "It will take few minutes"
else
    exit
fi

sudo apt-get update

# run 32bit applicatio: needed for lua relase mode as luajit has 32bit version
# https://askubuntu.com/questions/454253/how-to-run-32-bit-app-in-ubuntu-64-bit
sudo dpkg --add-architecture i386
# DEPENDS='libc6:i386 libncurses5:i386 libstdc++6:i386'
 

DEPENDS+=' libx11-dev'
DEPENDS+=' libxmu-dev'
DEPENDS+=' libglu1-mesa-dev'
DEPENDS+=' libgl2ps-dev'
DEPENDS+=' libxi-dev'
DEPENDS+=' libzip-dev'
DEPENDS+=' libpng-dev'
DEPENDS+=' libcurl4-gnutls-dev'
DEPENDS+=' libfontconfig1-dev'
DEPENDS+=' libsqlite3-dev'
DEPENDS+=' libglew-dev'
DEPENDS+=' libssl-dev'
DEPENDS+=' libgtk-3-dev'
DEPENDS+=' binutils'

sudo apt-get install --force-yes --yes $DEPENDS > /dev/null
