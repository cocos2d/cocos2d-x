#!/bin/bash
#
# ./download-deps.sh
#
# Download Cocos2D-X resources from github (https://github.com/minggo/cocos2d-x-resources) and extract from ZIP
#
# Helps prevent repo bloat due to large binary files since they can
# be hosted separately.
#

# exit this script if any commmand fails
set -e

prefix=https://codeload.github.com/minggo/cocos2d-x-resources/zip
filename=cocos2d-x-deps-v3-1
extracted_folder_name=cocos2d-x-resources-$filename

echo Downloading $filename.zip from $prefix...
curl -# $prefix/$filename -o $filename.zip

echo Extracting $filename.zip... please standby...
unzip -q $filename.zip
cp -R $extracted_folder_name/* .
echo Cleaning up...
rm $filename.zip
rm -rf $extracted_folder_name
echo Done.
