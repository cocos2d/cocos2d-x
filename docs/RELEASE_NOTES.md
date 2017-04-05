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

* full Android Studio supports: include editing, compiling and debugging c++ codes
* use [tremolo](http://wss.co.uk/pinknoise/tremolo/) to decode audio files on Android: high performance and more adaptable to different Android devices
* WebSockets and SocketIO supports SSL
* AssetsManagerEx is more stable
* update Spine runtime to v3.5.35
* update flatbuffer to v1.5
* remove support for Windows 8.1 store and phone
* update OpenSSL to v1.1.0
* remove linux 32-bit support

## Feature in detail

### Full Android Studio supports

Since v3.15, can use Android Studio 2.3+ to edit, compile and debug c++ codes. What you need to do is just use Android Studio to open `proj.android-studio`(such as `tests/cpp-empty-test/proj.android-studio`), then click run menu button to run on Android devices or simulators.

![android-studio-support.png](todo)

### Audio engine improve on Android

Before v3.15, new Audio engine uses OpenSL ES to decode and play audio files. But many Android device manufacturers modify OpenSL ES decoding codes which cause issues. [This thread](http://discuss.cocos2d-x.org/t/android-audio-decoding-issues-discussion/34610) lists many issues caused by it.

In order to fix these issues, we decide to use a 3rd party audio decoding library. [tremolo](http://wss.co.uk/pinknoise/tremolo/) which is used by Android have good performance and stability. We finally choose to use it. What's exciting is what, after using `tremolo`, the audio engine's performance is highly improved too.

![audio performance](https://raw.githubusercontent.com/minggo/Pictures/master/AudioDecodingPerfTest.png)  

### Remove support for Windows 8.1 store and phone

MS guys maintain Windows 8.1. They think there is not need to support it, so they remove the support.

### Remove linux 32-bit support

Most PC are 64-bit, so we decide to remove linux 32-bit support. By remove 32-bit linux support, cocos2d-x zip file is more less, and we can have more resource on more important things.

If you need linux 32-bit support, you can build the 3rd party libraries through [cocos2d-x-3rd-party-libs-src repo](https://github.com/cocos2d/cocos2d-x-3rd-party-libs-src) by yourself.

## misc

[Android SDK Tools 25.3.0+](http://tools.android.com/recent/androidsdktoolsrevision2530feb2017) remove ant scripts and `android` tool, this leads to that cant not use cocos command to generate apk files. Currently, cocos command will do nothing if using SDK Tools 25.3.0+. We may remove eclipse project support in future as Google focus on Android Studio.