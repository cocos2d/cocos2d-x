#!/bin/sh
ARG_NUM=$#

# check it was run in cocos2dx path
check_run_path(){
    if [ ! -f create-android-project.sh ];then
        echo Error!!!
        echo Please run in cocos2dx root
        exit -1
    fi
}

if [ $3 == "windows" ];then
    # called by .bat file
    sh $1/template/android/copy_files.sh $1 $2
    exit 0
fi

# the bash file should not be called by cygwin
UNIX_NAME=`uname -o`
if [ $UNIX_NAME == "Cygwin" ];then
    echo "Error!!!"
    echo "don't run in cygwin"
    exit -1
fi
    
check_run_path
