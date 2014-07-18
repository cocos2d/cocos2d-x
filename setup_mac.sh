#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BASENAME=`basename "$DIR"`
if [ "$BASENAME" = "Resources" ]; then
    DIR=`dirname "$DIR"`
    DIR=`dirname "$DIR"`
    DIR=`dirname "$DIR"`
elif [ "$BASENAME" = "bin" ]; then
    DIR=`dirname "$DIR"`
fi

if [ "$2" != "" ]; then
    CALL_BY_PKG=YES
    DIR=$2
fi;

QUICK_V3_ROOT="$DIR"

echo ""
echo "QUICK_V3_ROOT = \"$QUICK_V3_ROOT\""
echo ""

# set Xcode
defaults write com.apple.dt.Xcode IDEApplicationwideBuildSettings -dict-add QUICK_V3_ROOT "$QUICK_V3_ROOT"
defaults write com.apple.dt.Xcode IDESourceTreeDisplayNames -dict-add QUICK_V3_ROOT QUICK_V3_ROOT
IDEApplicationwideBuildSettings=`defaults read com.apple.dt.Xcode IDEApplicationwideBuildSettings`
IDESourceTreeDisplayNames=`defaults read com.apple.dt.Xcode IDESourceTreeDisplayNames`

echo "> Xcode settings updated."

# set quick player
defaults write org.cocos.quick.player QUICK_V3_ROOT "$QUICK_V3_ROOT"
echo "> quick player settings updated."

# set .bash_profile or .profile
if [ -f ~/.bash_profile ]; then
PROFILE_NAME=~/.bash_profile
else
PROFILE_NAME=~/.profile
fi

sed -e '/QUICK_V3_ROOT/d' $PROFILE_NAME | sed -e '/add by quick-cocos2d-x setup/d' > $PROFILE_NAME.tmp

DATE=`date "+DATE: %Y-%m-%d TIME: %H:%M:%S"`
echo "# add by quick-cocos2d-x setup, $DATE" >> $PROFILE_NAME.tmp
echo "export QUICK_V3_ROOT=\`cat ~/.QUICK_V3_ROOT\`" >> $PROFILE_NAME.tmp

DATE=`date "+%Y-%m-%d-%H%M%S"`
cp $PROFILE_NAME $PROFILE_NAME-$DATE.bak
cp $PROFILE_NAME.tmp $PROFILE_NAME
rm $PROFILE_NAME.tmp

echo "> $PROFILE_NAME updated."
echo "$QUICK_V3_ROOT" > ~/.QUICK_V3_ROOT
echo "> ~/.QUICK_V3_ROOT updated."
echo ""

if [ "$CALL_BY_PKG" != "" ]; then

    $QUICK_V3_ROOT/quick/bin/install_luajit.sh
    ln -s $QUICK_V3_ROOT/quick/player/mac/player.app $QUICK_V3_ROOT/quick/player.app

else

    while true; do
        read -p "Do you wish to install LuaJIT (Y/N) ? " yn
        case $yn in
            [Yy]* ) echo ""; $QUICK_V3_ROOT/quick/bin/install_luajit.sh; break;;
            [Nn]* ) exit;;
            * ) echo "Please answer yes or no.";;
        esac
    done

fi;

echo ""
echo ""

echo "done."
echo ""

