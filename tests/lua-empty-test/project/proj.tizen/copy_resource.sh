#!/bin/bash

cp -r ../../../res/* ../res/
cp -r ../../../src/ ../res/
mkdir -p ../res/src/cocos/
cp -r ../../../../../cocos/scripting/lua-bindings/script/* ../res/src/cocos/

