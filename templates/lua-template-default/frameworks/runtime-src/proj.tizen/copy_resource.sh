#!/bin/bash

cp -r ../../../../res/* ../res/
cp -r ../../../../src/* ../res/src/
mkdir -p ../res/src/cocos/
cp -r ../../../cocos2d-x/cocos/scripting/lua-bindings/script/* ../res/src/cocos/
