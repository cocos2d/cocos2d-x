#!/bin/sh
# This script should be called by create-android-project.bat
# or should be runned in linux shell. It can not be runned under
# cygwin.
# Don't modify the script until you know what you do.

# set environment paramters
NDK_ROOT="/workspace/android-dev/android-ndk-r5"
ANDROID_SDK_ROOT="/workspace/android-dev/android-sdk-mac_86"

# check if it was called by .bat file
if [ $# -eq 4 ];then
    if [ $4 = "windows" ];then
        # called by .bat file
        sh $1/template/android/copy_files.sh $1 $2 $3
        exit
    fi
fi


# the bash file should not be called by cygwin
UNIX_NAME=`uname -o`
if [ $UNIX_NAME = "Cygwin" ];then
    echo "Error!!!"
    echo "Don't run in cygwin. You should run corresponding bat."
    exit 
fi

# ok, it was run under linux

# check it was runned in cocos2d-x root
check_path(){
    if [ ! -f create-android-project.sh ];then
        echo Error!!!
        echo Please run in cocos2dx root
        exit 
    fi
}

# check the environment viriables
check_environment_variable(){
    if [ -z $NDK_ROOT ];then
        echo "Environment variable NDK_ROOT is not set."
        exit
    fi

    if [ -z $ANDROID_SDK_ROOT ];then
        echo "Environment variable ANDROID_SDK_ROOT is not set."
        exit
    fi
}

create_android_project(){
    echo "Now cocos2d-x suppurts Android 2.1-update1 and Android 2.2"
    echo "Other versions have not tested."
    $ANDROID_SDK_ROOT/tools/android list targets
    echo "input target id:"
    read TARGET_ID
    PACHAGE_PATH="org.cocos2dx.application"
    echo "input your project name:"
    read PROJECT_NAME
    PROJECT_DIR=`pwd`/$PROJECT_NAME

    $ANDROID_SDK_ROOT/tools/android create project -n $PROJECT_NAME -t $TARGET_ID -k $PACHAGE_PATH -a $PROJECT_NAME -p $PROJECT_DIR
}

check_path
check_environment_variable
create_android_project

# invoke template/android/copy_files.sh
sh `pwd`/template/android/copy_files.sh `pwd` $PROJECT_NAME $NDK_ROOT