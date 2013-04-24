#!/bin/bash

LIBS_DIR=$(cd "$(dirname $0)"; pwd)

TARGET_DIR=target
if [ -n "$1" ]; then
    TARGET_DIR=$1
fi

if [ ! -d "${TARGET_DIR}" ]; then
    mkdir -p ${TARGET_DIR}
fi

if [ ! -n "$2" ]; then

rm -rf "/tmp/cocostmp"
cp -r "${LIBS_DIR}/" "/tmp/cocostmp" && \
find "/tmp/cocostmp" -type d -iname "*.xcodeproj" -delete && \
find "/tmp/cocostmp" -type f ! -iname "*.h" -delete && \
mv "/tmp/cocostmp/"* "${TARGET_DIR}" && \
rmdir "/tmp/cocostmp" && \
\
mv "${TARGET_DIR}/CocosDenshion/include/"* "${TARGET_DIR}" && \
rm -rf "${TARGET_DIR}/CocosDenshion" && \
\
rm -rf "${TARGET_DIR}/extensions/proj."* && \
mv "${TARGET_DIR}/extensions/"* "${TARGET_DIR}" && \
rm -rf "${TARGET_DIR}/extensions" && \
\
mv "${TARGET_DIR}/external/"* "${TARGET_DIR}" && \
rm -rf "${TARGET_DIR}/external" && \
\
mv "${TARGET_DIR}/cocos2dx/kazmath/include/"* "${TARGET_DIR}" && \
rm -rf "${TARGET_DIR}/cocos2dx/kazmath" && \
\
rm -rf "${TARGET_DIR}/cocos2dx/platform/third_party" && \
\
mv "${TARGET_DIR}/cocos2dx/include/"* "${TARGET_DIR}" && \
\
rm -rf "${TARGET_DIR}/cocos2dx/proj."* && \
mv -f "${TARGET_DIR}/cocos2dx/"* "${TARGET_DIR}" && \
rm -rf "${TARGET_DIR}/cocos2dx" && \
\
find "${TARGET_DIR}" -type d -empty | xargs rmdir && \
find "${TARGET_DIR}" -type d -empty | xargs rmdir && \
find "${TARGET_DIR}" -type d -empty | xargs rmdir && \
find "${TARGET_DIR}" -type d -empty | xargs rmdir && \
find "${TARGET_DIR}" -type d -empty | xargs rmdir

elif [ $2 = "ios" ]; then

rm -rf "/tmp/cocostmp"  && \
mkdir "/tmp/cocostmp" && \
\
cp -r "${LIBS_DIR}/cocos2dx/platform/third_party/ios/"* "/tmp/cocostmp" && \
cp -r "${LIBS_DIR}/cocos2dx/platform/ios/"* "/tmp/cocostmp" && \
\
find "/tmp/cocostmp" -type d -iname "*.xcodeproj" -delete && \
find "/tmp/cocostmp" -type f ! -iname "*.h" -delete && \
\
find "/tmp/cocostmp" -type d -empty | xargs rmdir && \
find "/tmp/cocostmp" -type d -empty | xargs rmdir && \
find "/tmp/cocostmp" -type d -empty | xargs rmdir && \
find "/tmp/cocostmp" -type d -empty | xargs rmdir && \
find "/tmp/cocostmp" -type d -empty | xargs rmdir && \
find "/tmp/cocostmp" -type d -empty | xargs rmdir && \
\
cp -rf "/tmp/cocostmp/"* "${TARGET_DIR}" && \
rm -rf "/tmp/cocostmp"

elif [ $2 = "android" ]; then

rm -rf "/tmp/cocostmp"  && \
mkdir "/tmp/cocostmp" && \
\
cp -r "${LIBS_DIR}/cocos2dx/platform/third_party/android/prebuilt/"* "/tmp/cocostmp" && \
cp -r "${LIBS_DIR}/cocos2dx/platform/android/"* "/tmp/cocostmp" && \
\
find "/tmp/cocostmp" -type d -iname "*.xcodeproj" -delete && \
find "/tmp/cocostmp" -type f ! -iname "*.h" -delete && \
\
find "/tmp/cocostmp" -type d -empty | xargs rmdir && \
find "/tmp/cocostmp" -type d -empty | xargs rmdir && \
find "/tmp/cocostmp" -type d -empty | xargs rmdir && \
find "/tmp/cocostmp" -type d -empty | xargs rmdir && \
find "/tmp/cocostmp" -type d -empty | xargs rmdir && \
find "/tmp/cocostmp" -type d -empty | xargs rmdir && \
\
cp -rf "/tmp/cocostmp/"* "${TARGET_DIR}" && \
rm -rf "/tmp/cocostmp"

fi
