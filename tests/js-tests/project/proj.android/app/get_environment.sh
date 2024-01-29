#!/bin/bash

if [ -f $HOME/.bashrc ]; then
    source $HOME/.bashrc
fi

if [ -f $HOME/.bash_profile ]; then
    source $HOME/.bash_profile
fi

echo $COCOS_CONSOLE_ROOT
