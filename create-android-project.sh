#!/bin/sh
# This script should be called by create-android-project.bat
# or should be runned in linux shell. It can not be runned under
# cygwin.
# Don't modify the script until you know what you do.

# check it was runned in cocos2d-x root
check_path(){
    if [ ! -f create-android-project.sh ];then
        echo Error!!!
        echo Please run in cocos2dx root
        exit -1
    fi
}

check_path

if [ $4 == "windows" ];then
    # called by .bat file
    sh $1/template/android/copy_files.sh $1 $2 $3
    exit 0
fi


# the bash file should not be called by cygwin
UNIX_NAME=`uname -o`
if [ $UNIX_NAME == "Cygwin" ];then
    echo "Error!!!"
    echo "Don't run in cygwin. You should run corresponding bat."
    exit -1
fi

# ok, it was run under linux
