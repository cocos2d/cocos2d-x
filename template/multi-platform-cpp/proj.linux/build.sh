#!/bin/bash

SCRIPT_DIR=$(dirname ${BASH_SOURCE})

cd ${SCRIPT_DIR}

COCOS_ROOT=../../..

# Make cocos2dx libs
make -j5 -C $COCOS_ROOT DEBUG=1

# Make app
make -j5 DEBUG=1
