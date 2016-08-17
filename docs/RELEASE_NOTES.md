<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.13 Release Notes](#cocos2d-x-313-release-notes)
- [Misc Information](#misc-information)
- [v3.13](#v313)
  - [Highlights](#highlights)
  - [The main features in detail of Cocos2d-x v3.13](#the-main-features-in-detail-of-cocos2d-x-v313)
    - [Add VR plugin](#add-vr-plugin)
    - [Support ETC1 alpha channel](#support-etc1-alpha-channel)
    - [AudioEngine performance for Android 4.2+](#audioengine-performance-for-android-42)
    - [Android arm-64 support](#android-arm-64-support)
    - [Switch to use gcc 4.9](#switch-to-use-gcc-49)
    - [Upgrade CURL to 7.50.0](#upgrade-curl-to-7500)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.13 Release Notes #

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# v3.13

## Highlights

* add VR plugin
* support ETC1 alpha channel
* fix AudioEngine performance for Android 4.2+
* improve canvas renderer performance with dirty region 
* add Andorid arm-64 support
* switch to use gcc 4.9
* upgrade CURL to 7.50.0
* upgrade Spine to 3.4
* upgrade GLFW to 3.2

## The main features in detail of Cocos2d-x v3.13

### Add VR plugin

TBD: add link of PG

### Support ETC1 alpha channel

Thanks [halx99](https://github.com/halx99)'s contribution, now cocos2d-x supports ETC1 alpha channel by default.

If want to use ETC1 alpha chaneel, you should put `xxx.pkm` and `xxx.pkm@alpha` in the same folder, and use it like this:

```c++
auto sprite = Sprite::create("xxx.pkm");
```

`xxx.pkm@alpha` is the resource for alpha channel. `@alpha` subfix is required by engine to load alpha texture automatically.

More detail usage can refer to the implementation of `Sprite1ETC1Alpha` in `tests/cpp-tests/Classes/SpriteTest/SpriteTest.cpp`.

### AudioEngine performance for Android 4.2+

AudioEngine uses [OpenSL ES](https://developer.android.com/ndk/guides/audio/opensl-for-android.html) on Android, and it supports decoding audio source file to PCM data in codes since Android 4.2. Now AudioEngine uses this feature to fix the performance issue. The performane is the same as before if running on Android 4.1 or lower version.

### Dirty region in canvas renderer

In v3.12, we improved WebGL renderer in the web engine, this version have brought the dirty region algorithm to improve canvas renderer performance. Basically, it detect every region that have been changed between frames, then only render these parts instead of refresh the whole canvas. This technique is beneficial for many games in which the dynamic region is often limited, it can improve frame rate and reduce CPU usage, power consumation. It's desactivated by default, to activate it, you can do the following:

```
// Enable dirty region algorithm
if (cc._renderType === cc.game.RENDER_TYPE_CANVAS) {
    cc.renderer.enableDirtyRegion(true);
    // Maximum dirty region count to activate the partial rendering process
    cc.renderer.setDirtyRegionCountThreshold(6);
}
// Detect if dirty is enabled
var enabled = isDirtyRegionEnabled();
```

### Android arm-64 support

Now we provide arm-64 bit 3rd party libraries, which means can build 64-bit apps on Android. You can use the command to build 64-bit apps:
```
cocos run -p android --app-abi arm64-v8a
```

### Switch to use gcc 4.9 on Android

cocos2d-x switch to use clang in `v3.12`, but developers reported [some crash issue](https://github.com/cocos2d/cocos2d-x/issues/16244) that caused by using `clang+gnustl_static`, so we switch to use gcc 4.9. We will change to use `clang+c++_static` when `c++_static` is stable.

### Upgrade CURL to 7.50.0

Because CURL has [a bug about connect to IPV4 numerical IP address in NAT64 environment](https://github.com/curl/curl/issues/863), and it is fixed in v7.50.0, so we upgrade to this version when v7.50.0 is released.