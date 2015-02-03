#!/bin/sh

#try to grab the doxygen version modified by me
#TODO: if the doxygen is not correct, we should install it manually


sed -i .bak '/CC_DEPRECATED_ATTRIBUTE CC_DLL/,/NS_CC_END/d' ../../cocos/base/ccUTF8.h
# git diff > doc-patch.patch
# mv doc-patch.patch docs
#we need to generate the patch automatically and remove it after applying
# patch -fp1 < docs/doc-patch.patch


version=`grep -e 'return' ../../cocos/cocos2d.cpp | awk '{print substr($3,0,length($3)-2)}'`
echo $version
cd ../../docs
#we should  read cocos2d.cpp and retrieve the version number
sed -i .bak "s/3\.0/${version}/g" doxygen.config

rm doxygen.config.bak 

doxygen doxygen.config 

git checkout . ../cocos/base/ccUTF8.h 

rm debug.txt
