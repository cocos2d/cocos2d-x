#!/bin/sh
# This script should be called by create-android-project.bat
# or should be runned in linux shell. It can not be runned under
# cygwin.
# Don't modify the script until you know what you do.

# set environment paramters
NDK_ROOT="/home/zhangxm/bin/android-ndk-r6b"
ANDROID_SDK_ROOT="/home/zhangxm/bin/android-sdk-linux_x86"
COCOS2DX_ROOT="/home/zhangxm/cocos2d-x"

# check if it was called by .bat file
if [ $# -eq 5 ];then
    if [ $5 = "windows" ];then
        # called by .bat file
        sh $1/template/linux/copy_files.sh $1 $2 $3 $4
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
#check_path(){
#    if [ ! -f create-android-project.sh ];then
#        echo Error!!!
#        echo Please run in cocos2dx root
#        exit 
#    fi
#}

create_android_project(){
    echo "Input package path. For example: org.cocos2dx.example"
    read PACKAGE_PATH
    echo "Now cocos2d-x suppurts Android 2.1-update1, 2.2, 2.3 & 3.0"
    echo "Other versions have not tested."
    $ANDROID_SDK_ROOT/tools/android list targets
    echo "input target id:"
    read TARGET_ID
    echo "input your project name:"
    read PROJECT_NAME
    PROJECT_DIR=`pwd`/$PROJECT_NAME
    PROREAL_DIR=$PROJECT_NAME
    PROJECT_NAME=An$PROJECT_NAME

    $ANDROID_SDK_ROOT/tools/android create project -n $PROJECT_NAME -t $TARGET_ID -k $PACKAGE_PATH -a $PROJECT_NAME -p $PROJECT_DIR
}

#check_path
create_android_project

# invoke template/android/copy_files.sh
sh $COCOS2DX_ROOT/template/linux/mycopy_files.sh $COCOS2DX_ROOT $PROJECT_NAME $NDK_ROOT $PACKAGE_PATH $PROREAL_DIR
