#!/bin/sh
# This script should be called by create-android-project.bat
# or should be runned in linux shell. It can not be runned under
# cygwin.
# Don't modify the script until you know what you do.

# set environment paramters
NDK_ROOT_LOCAL="/home/laschweinski/android/android-ndk-r5"
ANDROID_SDK_ROOT_LOCAL="/home/laschweinski/android/android-sdk-linux_86"

# try to get global variable
if [ $NDK_ROOT"aaa" != "aaa" ]; then
    echo "use global definition of NDK_ROOT: $NDK_ROOT"
    NDK_ROOT_LOCAL=$NDK_ROOT
fi

if [ $ANDROID_SDK_ROOT"aaa" != "aaa" ]; then
    echo "use global definition of ANDROID_SDK_ROOT: $ANDROID_SDK_ROOT"
    ANDROID_SDK_ROOT_LOCAL=$ANDROID_SDK_ROOT
fi

# check if it was called by .bat file
if [ $# -eq 5 ];then
    if [ $5 = "windows" ];then
        # called by .bat file
        sh $1/template/android/copy_files.sh $1 $2 $3 $4
        exit
    fi
fi


# the bash file should not be called by cygwin
KERNEL_NAME=`uname -s | grep "CYGWIN*"`
if [ $KERNEL_NAME"hi" != "hi" ]; then
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

create_android_project(){
    echo "Input package path. For example: org.cocos2dx.example"
    read PACKAGE_PATH
    echo "Now cocos2d-x supports Android 2.1-update1, 2.2, 2.3 & 3.0"
    echo "Other versions have not tested."
    $ANDROID_SDK_ROOT_LOCAL/tools/android list targets
    echo "input target id:"
    read TARGET_ID
    echo "input your project name:"
    read PROJECT_NAME
    PROJECT_DIR=`pwd`/$PROJECT_NAME
    
    # check if PROJECT_DIR is exist
    if [ -d $PROJECT_DIR ]; then
        echo "$PROJECT_DIR is exist, please use another name"
        exit
    fi

    $ANDROID_SDK_ROOT_LOCAL/tools/android create project -n $PROJECT_NAME -t $TARGET_ID -k $PACKAGE_PATH -a $PROJECT_NAME -p $PROJECT_DIR
}

check_path
create_android_project

if [ $# -eq 1 ]; then
    # invoked by create-linux-android-project.sh
    sh `pwd`/template/linux/mycopy_files.sh `pwd` $PROJECT_NAME $NDK_ROOT_LOCAL $PACKAGE_PATH 
else
    # invoke template/android/copy_files.sh
    sh `pwd`/template/android/copy_files.sh `pwd` $PROJECT_NAME $NDK_ROOT_LOCAL $PACKAGE_PATH
fi

