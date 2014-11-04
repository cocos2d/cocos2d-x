#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BASENAME=`basename "$DIR"`

if [ "$BASENAME" = "Resources" ]; then
    DIR=`dirname "$DIR"`
    DIR=`dirname "$DIR"`
    DIR=`dirname "$DIR"`
    export CALL_BY_CONTAINER=APP
fi

if [ ! "$2" == "" ]; then
    DIR=$2
    export CALL_BY_CONTAINER=PKG
fi;

VERSION=`cat $DIR/VERSION`

if [ "$CALL_BY_CONTAINER" == "PKG" ]; then
    LOG_FILENAME="/tmp/quick-cocos2d-x-${VERSION}-setup.log"
fi

if [ "$CALL_BY_CONTAINER" == "PKG" ]; then
    echo "quick-cocos2d-x-${VERSION} setup log" > "$LOG_FILENAME"
    echo "================================" >> "$LOG_FILENAME"
fi

QUICK_V3_ROOT="$DIR"

echo ""
echo "QUICK_V3_ROOT = \"$QUICK_V3_ROOT\""
echo ""

if [ "$CALL_BY_CONTAINER" == "PKG" ]; then
    echo "" >> "$LOG_FILENAME"
    echo "QUICK_V3_ROOT = \"$QUICK_V3_ROOT\"" >> "$LOG_FILENAME"
    echo "" >> "$LOG_FILENAME"
fi

# set Xcode
defaults write com.apple.dt.Xcode IDEApplicationwideBuildSettings -dict-add QUICK_V3_ROOT "$QUICK_V3_ROOT"
defaults write com.apple.dt.Xcode IDESourceTreeDisplayNames -dict-add QUICK_V3_ROOT QUICK_V3_ROOT
IDEApplicationwideBuildSettings=`defaults read com.apple.dt.Xcode IDEApplicationwideBuildSettings`
IDESourceTreeDisplayNames=`defaults read com.apple.dt.Xcode IDESourceTreeDisplayNames`

echo "> Xcode settings updated." 

# set quick player
defaults write org.cocos.quick.player QUICK_V3_ROOT "$QUICK_V3_ROOT"
echo "> quick player settings updated."

if [ "$CALL_BY_CONTAINER" == "PKG" ]; then
    echo "> Xcode settings updated." >> "$LOG_FILENAME"
    echo "> quick player settings updated." >> "$LOG_FILENAME"
fi

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

if [ "$CALL_BY_CONTAINER" == "PKG" ]; then
    echo "> $PROFILE_NAME updated." >> "$LOG_FILENAME"
    echo "> ~/.QUICK_V3_ROOT updated." >> "$LOG_FILENAME"
    echo "" >> "$LOG_FILENAME"
fi

export QUICK_V3_ROOT=`cat ~/.QUICK_V3_ROOT`

# echo "INSTALLING QUICK FRAMEWORK"
# $QUICK_V3_ROOT/quick/bin/make_framework_package.sh

# echo ""
# echo ""

# echo "INSTALLING QUICK TEMPLATE TO COCOS"
# if [ "$CALL_BY_CONTAINER" == "PKG" ]; then
#     echo "> check coscos version...." >> "$LOG_FILENAME"
#     source $PROFILE_NAME
#     echo "> COCOS_CONSOLE_ROOT=$COCOS_CONSOLE_ROOT" >> "$LOG_FILENAME"
#     $QUICK_V3_ROOT/quick/bin/install_to_cocos.sh >> "$LOG_FILENAME"
# else
#     $QUICK_V3_ROOT/quick/bin/install_to_cocos.sh
# fi

echo ""
echo ""

echo "done."
echo ""

if [ "$CALL_BY_CONTAINER" == "APP" ]; then

    /usr/bin/osascript -e 'tell app "System Events" to display dialog "Setup completed." default button 1 buttons {"OK"}'
    open -g -R "$QUICK_V3_ROOT/player3.app"

elif [ "$CALL_BY_CONTAINER" == "PKG" ]; then

    echo "" >> "$LOG_FILENAME"
    echo "done." >> "$LOG_FILENAME"
    echo "" >> "$LOG_FILENAME"

    open -g "$QUICK_V3_ROOT/README.html"
    open -R "$QUICK_V3_ROOT/player3.app"
fi
