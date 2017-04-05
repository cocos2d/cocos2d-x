#!/bin/bash

# Change directory to the location of this script
cd $(dirname ${BASH_SOURCE[0]})

if [ ! $(command -v apt-get) ]; then
  echo "Not a .deb package system. Please install dependencies manually"
  exit 0
fi

#install g++-4.9
sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y > /dev/null
sudo apt-get update

DEPENDS='libx11-dev'
DEPENDS+=' libxmu-dev'
DEPENDS+=' libglu1-mesa-dev'
DEPENDS+=' libgl2ps-dev'
DEPENDS+=' libxi-dev'
DEPENDS+=' gcc-4.9'
DEPENDS+=' g++-4.9'
DEPENDS+=' libzip-dev'
DEPENDS+=' libpng12-dev'
DEPENDS+=' libcurl4-gnutls-dev'
DEPENDS+=' libfontconfig1-dev'
DEPENDS+=' libsqlite3-dev'
DEPENDS+=' libglew-dev'
DEPENDS+=' libssl-dev'
DEPENDS+=' libgtk-3-dev'
DEPENDS+=' binutils'

MISSING=
echo "Checking for missing packages ..."
for i in $DEPENDS; do
    if ! dpkg-query -W --showformat='${Status}\n' $i | grep "install ok installed" > /dev/null; then
        MISSING+="$i "
    fi
done

if [ -n "$MISSING" ]; then
    TXTCOLOR_DEFAULT="\033[0;m"
    TXTCOLOR_GREEN="\033[0;32m"
    echo -e $TXTCOLOR_GREEN"Missing packages: $MISSING.\nYou may be asked for your password for package installation."$TXTCOLOR_DEFAULT
    sudo apt-get --force-yes --yes install $MISSING > /dev/null
fi

sudo update-alternatives --remove-all gcc
sudo update-alternatives --remove-all g++

sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 60

echo "Cocos uses GCC Version: `gcc --version`"
echo "Cocos uses G++ Version: `g++ --version`"
echo "Cocos uses ld Version: `ld --version`"
echo "Cocos uses /usr/bin/ld Version: `/usr/bin/ld --version`"
# install glfw
../tools/travis-scripts/install_glfw.sh

