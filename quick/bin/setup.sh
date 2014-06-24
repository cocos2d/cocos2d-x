#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BASENAME=`basename $DIR`

if [ "$BASENAME" = "Resources" ]; then
    DIR=`dirname $DIR`
    DIR=`dirname $DIR`
    DIR=`dirname $DIR`
elif [ "$BASENAME" = "bin" ]; then
    DIR=`dirname $DIR`
fi

QUICK_COCOS2DX_ROOT="$DIR"

echo ""
echo "QUICK_COCOS2DX_ROOT = \"$QUICK_COCOS2DX_ROOT\""
echo ""

# set Xcode
defaults write com.apple.dt.Xcode IDEApplicationwideBuildSettings -dict-add QUICK_COCOS2DX_ROOT "$QUICK_COCOS2DX_ROOT"

defaults write com.apple.dt.Xcode IDESourceTreeDisplayNames -dict-add QUICK_COCOS2DX_ROOT QUICK_COCOS2DX_ROOT

IDEApplicationwideBuildSettings=`defaults read com.apple.dt.Xcode IDEApplicationwideBuildSettings`
IDESourceTreeDisplayNames=`defaults read com.apple.dt.Xcode IDESourceTreeDisplayNames`

echo "> Xcode settings updated."

# set quick-x-player
defaults write com.qeeplay.apps.quick-x-player QUICK_COCOS2DX_ROOT "$QUICK_COCOS2DX_ROOT"
echo "> quick-x-player settings updated."

# set .bash_profile or .profile
if [ -f ~/.bash_profile ]; then
PROFILE_NAME=~/.bash_profile
else
PROFILE_NAME=~/.profile
fi

sed -e '/QUICK_COCOS2DX_ROOT/d' $PROFILE_NAME | sed -e '/add by quick-cocos2d-x setup/d' > $PROFILE_NAME.tmp

DATE=`date "+DATE: %Y-%m-%d TIME: %H:%M:%S"`
echo "# add by quick-cocos2d-x setup, $DATE" >> $PROFILE_NAME.tmp
echo "export QUICK_COCOS2DX_ROOT=\"$QUICK_COCOS2DX_ROOT\"" >> $PROFILE_NAME.tmp

DATE=`date "+%Y-%m-%d-%H%M%S"`
cp $PROFILE_NAME $PROFILE_NAME-$DATE.bak
cp $PROFILE_NAME.tmp $PROFILE_NAME
rm $PROFILE_NAME.tmp

echo "> $PROFILE_NAME updated."
echo ""
echo "done."
echo ""
