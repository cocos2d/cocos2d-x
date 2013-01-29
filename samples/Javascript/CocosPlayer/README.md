# CocosPlayer
CocosPlayer JS is an Android implementation of CocosPlayer for Javascript based CocosBuilder projects. It is a wireless sync tool that works in conjunction with CocosBuilder. Using this, you can publish your CocosBuilder JS project and run them wirelessly. The system uses bonjour/zeroconf protocol for network discovery and connection.

NOTE: Right now for iOS equivalent, use CocosPlayer JS for cocos2d-iphone.

## Minimum Requirements

Currently CocosPlayer for Android only works with OS version >= 4.1. API level >= 16. This is because zeroconf has only been implemented in API level 16.

## Supported Devices

Currently CocosPlayer is supported on the following devices. NOTE: This is not an exaustive list. It only contains devices that CocosPlayer for Android has been tested on.

Google Nexus 4, Google Nexus 10, Google Nexus 7, Samsung Galaxy Nexus, Samsung Galaxy Note, Samsung Galaxy Note 2, Samsung Galaxy SIII.

## Build Instructions

1. cd samples/Javascript/CocosPlayer/proj.android
2. ./build_native.sh (assumes you have the path to NDK and SDK set correctly)
3. ant debug install


## How to use

1. Start the CocosPlayer application.  
2. On CocosBuilder, Publish and run project
3. Set the pairing code. By default it is set as Auto on CocosPlayer - corresponding to empty pairing code on CocosBuilder. Only numbers are supported as pairing codes.
4. It will show connected, and should automatically run the CocosBuilder JS project after a short delay.
5. Next time you close and open the app. The *run* and *reset* buttons will be enabled, allowing you to run the last cached CocosBuilder project and clean the last cached CocosBuilder project respectively.

