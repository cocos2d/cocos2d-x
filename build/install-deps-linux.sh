#!/bin/bash

# Change directory to the location of this script
cd $(dirname ${BASH_SOURCE[0]})

DEPENDS='libx11-dev'
DEPENDS+=' libxmu-dev'
DEPENDS+=' libglu1-mesa-dev'
DEPENDS+=' libgl2ps-dev'
DEPENDS+=' libxi-dev'
DEPENDS+=' g++'
DEPENDS+=' libzip-dev'
DEPENDS+=' libpng12-dev'
DEPENDS+=' libcurl4-gnutls-dev'
DEPENDS+=' libfontconfig1-dev'
DEPENDS+=' libsqlite3-dev'
DEPENDS+=' libglew*-dev'

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
    sudo apt-get --force-yes --yes install $MISSING
fi

# install glfw
../tools/travis-scripts/install_glfw.sh

