#!/bin/bash

cp -r ../../../res/* ../res/
mkdir -p ../res/src/
cp -r ../../../src/* ../res/src/
mkdir -p ../res/src/cocos/
cp -r ../../../../../cocos/scripting/lua-bindings/script/* ../res/src/cocos/
cp -r ../../../../cpp-tests/Resources/* ../res/

