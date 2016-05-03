#!/bin/bash

# This script is based on https://gist.github.com/rehos/7856163

if [ -z "$1" ]; then
  echo
  echo "usage: $0 <project.xcodeproj> [<scheme>]"
  echo
  exit
fi

if [ ! -d "$1" ]; then
  echo
  echo "Error: $1 does not exist"
  echo
  exit
fi

MY_PROJECT="$1"
MY_PROJECT_NAME=$(basename "$1")

if [ -z "$2" ]; then
	MY_SCHEME=${MY_PROJECT_NAME%.*}
else
	MY_SCHEME="$2"
fi

MY_STATIC_LIB="${MY_SCHEME}.a"
MY_BUILD_PATH=`mktemp -d -t "build"`
MY_SDK_VERSION=`xcrun --sdk iphoneos --show-sdk-version`

# armv7, armv7s
MY_ARM_BUILD_PATH="${MY_BUILD_PATH}/build-arm"
MY_CURRENT_BUILD_PATH="${MY_ARM_BUILD_PATH}"
xcodebuild -project "${MY_PROJECT}" -scheme "${MY_SCHEME}" -configuration 'Release' -sdk "iphoneos${MY_SDK_VERSION}" clean build ARCHS='armv7 armv7s' VALID_ARCHS='armv7 armv7s' IPHONEOS_DEPLOYMENT_TARGET='5.0' TARGET_BUILD_DIR="${MY_CURRENT_BUILD_PATH}" BUILT_PRODUCTS_DIR="${MY_CURRENT_BUILD_PATH}" OBJROOT="${MY_CURRENT_BUILD_PATH}" SYMROOT="${MY_CURRENT_BUILD_PATH}"

# arm64
MY_ARM64_BUILD_PATH="${MY_BUILD_PATH}/build-arm64"
MY_CURRENT_BUILD_PATH="${MY_ARM64_BUILD_PATH}"
xcodebuild -project "${MY_PROJECT}" -scheme "${MY_SCHEME}" -configuration 'Release' -sdk "iphoneos${MY_SDK_VERSION}" clean build ARCHS='arm64' VALID_ARCHS='arm64' IPHONEOS_DEPLOYMENT_TARGET='7.0' TARGET_BUILD_DIR="${MY_CURRENT_BUILD_PATH}" BUILT_PRODUCTS_DIR="${MY_CURRENT_BUILD_PATH}" OBJROOT="${MY_CURRENT_BUILD_PATH}" SYMROOT="${MY_CURRENT_BUILD_PATH}"

# i386
MY_I386_BUILD_PATH="${MY_BUILD_PATH}/build-i386"
MY_CURRENT_BUILD_PATH="${MY_I386_BUILD_PATH}"
xcodebuild -project "${MY_PROJECT}" -scheme "${MY_SCHEME}" -configuration 'Release' -sdk "iphonesimulator${MY_SDK_VERSION}" clean build ARCHS='i386' VALID_ARCHS='i386' IPHONEOS_DEPLOYMENT_TARGET='5.0' TARGET_BUILD_DIR="${MY_CURRENT_BUILD_PATH}" BUILT_PRODUCTS_DIR="${MY_CURRENT_BUILD_PATH}" OBJROOT="${MY_CURRENT_BUILD_PATH}" SYMROOT="${MY_CURRENT_BUILD_PATH}"

# x86_64
MY_X86_64_BUILD_PATH="${MY_BUILD_PATH}/build-x86_64"
MY_CURRENT_BUILD_PATH="${MY_X86_64_BUILD_PATH}"
xcodebuild -project "${MY_PROJECT}" -scheme "${MY_SCHEME}" -configuration 'Release' -sdk "iphonesimulator${MY_SDK_VERSION}" clean build ARCHS='x86_64' VALID_ARCHS='x86_64' IPHONEOS_DEPLOYMENT_TARGET='7.0' TARGET_BUILD_DIR="${MY_CURRENT_BUILD_PATH}" BUILT_PRODUCTS_DIR="${MY_CURRENT_BUILD_PATH}" OBJROOT="${MY_CURRENT_BUILD_PATH}" SYMROOT="${MY_CURRENT_BUILD_PATH}"

lipo -create "${MY_ARM_BUILD_PATH}/${MY_STATIC_LIB}" "${MY_ARM64_BUILD_PATH}/${MY_STATIC_LIB}" "${MY_I386_BUILD_PATH}/${MY_STATIC_LIB}" "${MY_X86_64_BUILD_PATH}/${MY_STATIC_LIB}" -output "${MY_STATIC_LIB}"

rm -rf "${MY_BUILD_PATH}"