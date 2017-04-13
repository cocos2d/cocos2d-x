<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.15 Release Notes](#cocos2d-x-315-release-notes)
- [Misc Information](#misc-information)
- [v3.15](#v315)
  - [Highlights](#highlights)
  - [Feature in detail](#feature-in-detail)
    - [Full Android Studio supports](#full-android-studio-supports)
    - [Audio engine improve on Android](#audio-engine-improve-on-android)
    - [Remove support for Windows 8.1 store and phone](#remove-support-for-windows-81-store-and-phone)
    - [Remove linux 32-bit support](#remove-linux-32-bit-support)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.15 Release Notes #

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# v3.15

## Highlights

* full __Android Studio__ supports: include editing, compiling and debugging c++ codes: [doc](https://github.com/chukong/cocos-docs/blob/v3-unified-documentation/installation/Android-Studio.md)
* audio engine uses [tremolo](http://wss.co.uk/pinknoise/tremolo/) and __MP3 Decoder Library__ to decode audio files on Android: high performance and more adaptable to different Android devices
* __WebSockets__ and __SocketIO__ supports SSL
* AssetsManagerEx is more stable
* update __Spine runtime__ to v3.5.35
* update __flatbuffer__ to v1.5
* remove support for Windows 8.1 store and phone
* update __OpenSSL__ to v1.1.0
* remove linux 32-bit support

## Feature in detail

### Full Android Studio supports

Since v3.15, can use Android Studio 2.3+ to edit, compile and debug c++ codes. What you need to do is just use Android Studio to open `proj.android-studio`(such as `tests/cpp-empty-test/proj.android-studio`), then click run menu button to run on Android devices or simulators.

Please refer to [this doc](https://github.com/chukong/cocos-docs/blob/v3-unified-documentation/installation/Android-Studio.md) for detail usage.

### Audio engine improved on Android

Before v3.15, new Audio engine uses OpenSL ES to decode and play audio files. But many Android device manufacturers modify OpenSL ES decoding codes which cause issues. [This thread](http://discuss.cocos2d-x.org/t/android-audio-decoding-issues-discussion/34610) lists many issues caused by it.

In order to fix these issues, we decide to use 3rd party audio decoding libraries [tremolo](http://wss.co.uk/pinknoise/tremolo/) and __MP3 Decoder Library__, which are used by Android have good performance and stability. What's exciting is what, after using `tremolo`, the audio engine's performance is highly improved too.

![audio performance](https://raw.githubusercontent.com/minggo/Pictures/master/AudioDecodingPerfTest.png)  

### Remove support for Windows 8.1 store and phone

MS guys maintain Windows 8.1. They think there is not need to support it, so they remove the support.

### Remove linux 32-bit support

Most PC are 64-bit, so we decide to remove linux 32-bit support. By remove 32-bit linux support, cocos2d-x zip file is more less, and we can have more resource on more important things.

If you need linux 32-bit support, you can build the 3rd party libraries through [cocos2d-x-3rd-party-libs-src repo](https://github.com/cocos2d/cocos2d-x-3rd-party-libs-src) by yourself.

## misc

[Android SDK Tools 25.3.0+](http://tools.android.com/recent/androidsdktoolsrevision2530feb2017) removes __ant script__ and __android tool__, which leads to that cocos command can not generate apk files with Eclipse projects(proj.android). Currently, cocos command will do nothing if using SDK Tools 25.3.0+, you can use these two methods to fix it:

* copy `tools` folder from old Android SDK version
* use Android Studio to build the app

It seems google doesn't want developers continue to use Eclipse to develope Android applications, so i suggest to switch to use Android Studio.
