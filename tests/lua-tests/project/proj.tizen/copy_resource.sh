#!/bin/bash

cp ../../../res/* ../res/ -r -u
cp ../../../src/ ../res/ -r -u
mkdir ../res/src/cocos/
cp ../../../../../cocos/scripting/lua-bindings/script/* ../res/src/cocos/ -r -u
cp ../../../../cpp-tests/Resources/* ../res/ -r -u

