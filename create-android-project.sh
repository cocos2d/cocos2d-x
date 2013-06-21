#!/bin/bash
# parameters passed to script
# This script should be called by create-android-project.bat
# or should be runned in linux shell. It can not be runned under cygwin.
# Don't modify the script until you know what you do.
PARAMS=$@

# you can set the environment here and uncomment them if you haven't set them in .bashrc
#export NDK_ROOT=
#export ANDROID_SDK_ROOT=
#export COCOS2DX_ROOT=

# set environment paramters
if [ "x${NDK_ROOT}" == "x" ] ; then
    NDK_ROOT="/opt/android-ndk"
fi

if [ "x${ANDROID_SDK_ROOT}" == "x" ] ; then
    ANDROID_SDK_ROOT="/opt/android-sdk-update-manager"
fi
ANDROID_CMD="${ANDROID_SDK_ROOT}/tools/android"

if [ "x${COCOS2DX_ROOT}" == "x" ] ; then
    COCOS2DX_ROOT="${HOME}/cocos2d-x"
    if [ ! -d $COCOS2DX_ROOT ] ; then
        COCOS2DX_ROOT=`pwd`
    fi
fi

if [ ! -d ${NDK_ROOT} -o ! -d ${ANDROID_SDK_ROOT} -o ! -x ${ANDROID_CMD} ] ; then
    echo "Please set the environment at first"
fi

USE_BOX2D=false
USE_CHIPMUNK=false
USE_LUA=false

print_usage(){
    echo "usage:"
    echo "$0 [-b|--box2d] [-c|--chipmunk] [-l|--lua]"
}

check_param(){
    for param in ${PARAMS[@]} 
    do
        case $param in
            -b | --box2d)
                echo using box2d
                USE_BOX2D=true
                ;;
            -c | --chipmunk)
                echo using chipmunk
                USE_CHIPMUNK=true
                ;;
            -l | --lua)
                echo using lua
                USE_LUA=true
                ;;
            -linux)
                // skip it
                ;;
            *)
                print_usage
                exit 1
        esac
    done

    if [ $USE_BOX2D == "true" -a $USE_CHIPMUNK == "true" ] ; then 
        echo '[WARN] Using box2d and chipmunk together!'
    fi
}

# check if it was called by .bat file
if [ $# -ge 5 -a "x$5" == "xwindows" ] ; then
    # should be called by .bat file
    length=`expr $# - 5`
    PARAMS=${@:6:$length}
    check_param
    ANDROID_SDK_ROOT=$ANDROID_SDK_ROOT COCOS2DX_ROOT=$COCOS2DX_ROOT sh $COCOS2DX_ROOT/template/android/copy_files.sh $1 $2 $3 $4 $USE_BOX2D $USE_CHIPMUNK $USE_LUA
    exit
fi

# the bash file should not be called by cygwin
KERNEL_NAME=`uname -s | grep "CYGWIN*"`
if [ "x$KERNEL_NAME" != "x" ] ; then
    echo "[ERROR] Don't run in cygwin. You should run .bat file"
    exit
fi

# ok, it was run under linux

create_android_project(){
    DEFAULT_PACKAGE_PATH='org.cocos2dx.demo'
    DEFAULT_TARGET_ID='1'
    DEFAULT_PROJECT_NAME="Hello"

    echo -n "Input package path [${DEFAULT_PACKAGE_PATH}]:"
    read PACKAGE_PATH
    if [ "x${PACKAGE_PATH}" == "x" ] ; then
        PACKAGE_PATH=${DEFAULT_PACKAGE_PATH}
    fi

    ${ANDROID_CMD} list targets
    echo -n "Input target id [${DEFAULT_TARGET_ID}]:"
    read TARGET_ID
    if [ "x${TARGET_ID}" == "x" ] ; then
        TARGET_ID=${DEFAULT_TARGET_ID}
    fi

    echo -n "Input your project name [${DEFAULT_PROJECT_NAME}]:"
    read PROJECT_NAME
    if [ "x${PROJECT_NAME}" == "x" ] ; then
        PROJECT_NAME=${DEFAULT_PROJECT_NAME}
    fi
    PROJECT_DIR=`pwd`/${PROJECT_NAME}

    # check if PROJECT_DIR is exist
    if [ -d $PROJECT_DIR ] ; then
        echo "$PROJECT_DIR already exist, please use another name"
        exit
    fi

    # Make project directory
    mkdir $PROJECT_DIR
    # Create Android project inside proj.android
    $ANDROID_CMD create project -n $PROJECT_NAME -t $TARGET_ID -k $PACKAGE_PATH -a $PROJECT_NAME -p $PROJECT_DIR/proj.android
    $ANDROID_CMD update project -l ${COCOS2DX_ROOT}/cocos2dx/platform/android/java -p $PROJECT_DIR/proj.android
}

check_param
create_android_project

if [ $0 = "linux" ]; then
    # invoked by create-linux-android-project.sh
    ANDROID_SDK_ROOT=$ANDROID_SDK_ROOT COCOS2DX_ROOT=$COCOS2DX_ROOT sh $COCOS2DX_ROOT/template/linux/mycopy_files.sh $COCOS2DX_ROOT $PROJECT_NAME $NDK_ROOT $PACKAGE_PATH $USE_BOX2D $USE_CHIPMUNK $USE_LUA
else
    # invoke template/android/copy_files.sh
    ANDROID_SDK_ROOT=$ANDROID_SDK_ROOT COCOS2DX_ROOT=$COCOS2DX_ROOT sh $COCOS2DX_ROOT/template/android/copy_files.sh $COCOS2DX_ROOT $PROJECT_DIR $PACKAGE_PATH $USE_BOX2D $USE_CHIPMUNK $USE_LUA
fi

