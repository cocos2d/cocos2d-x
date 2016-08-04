<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.12 Release Notes](#cocos2d-x-312-release-notes)
- [Misc Information](#misc-information)
- [Requirements](#requirements)
  - [Runtime Requirements](#runtime-requirements)
  - [Compiler Requirements](#compiler-requirements)
  - [How to run tests](#how-to-run-tests)
    - [Cocos Console](#cocos-console)
    - [Mac OSX & iOS](#mac-osx-&-ios)
    - [Android](#android)
    - [Windows](#windows)
    - [Linux](#linux)
  - [How to start a new game](#how-to-start-a-new-game)
- [v3.12](#v312)
  - [Highlights](#highlights)
  - [The main features in detail of Cocos2d-x v3.12](#the-main-features-in-detail-of-cocos2d-x-v312)
    - [VR support](#vr-support)
    - [Tizen support](#tizen-support)
    - [improve Android performance](#improve-android-performance)
    - [improve web engine performance in WebGL mode](#improve-web-engine-performance-in-webgl-mode)
    - [Use clang on Android](#use-clang-on-android)
  - [Other changes](#other-changes)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.13 Release Notes #

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# Requirements

## Runtime Requirements

* Android 2.3.3+
* iOS 5.0 or newer
* OS X 10.7 or newer
* Windows 7 or newer
* Windows Phone 8.1
* Windows 10 UWP
* Linux Ubuntu 14.04 or newer
* Modern browsers and IE 9+ (On mobile platforms, only iOS and Android 5 activated WebGL support)

## Compiler Requirements

* Xcode 7+ for iOS or Mac
* gcc 4.9+ for Linux
* ndk-r11+ and API level 19 for Android
* Visual Studio 2013 or newer for Windows (win32)
* Visual Studio 2013 update4 or newer for Windows 8.1 universal Apps
* Visual Studio 2015 or newer and Windows 10.0 (build 10074 or higher) for Windows 10.0 UWP Apps

## How to run tests

### Cocos Console

You can use [Cocos Console](www.cocos2d-x.org/wiki/Cocos2d-console) command line tool to run the test cases on almost all supported platforms.

In console application:
```
// Enter cpp test folder
cd tests/cpp-tests
// Or enter js test folder
cd tests/js-tests
// Or enter lua test folder
cd tests/lua-tests

// Compile or run test case
cocos compile -p ios|mac|android|win32|win8_1|metro|web -m debug|release
cocos run -p ios|mac|android|win32|win8_1|metro|web -m debug|release
```

For example, if you want to run cpp test in release mode on Android, you can use the following command:

```
cocos run -p android -m release
```

### Mac OSX & iOS
You can run the samples by:

* Open __cocos2d-x/build__ folder, open __cocos2d_test.xcodeproj__
* Select `cpp-tests`, `lua-tests`, `js-tests` for __iOS__ or __OS X__ target in scheme toolbar
* Click __run__ button

### Android
You can run the samples by either using the command-line or Eclipse:

**Using command line:**
Perform the following steps:

    $ cd cocos2d-x
    $ ./setup.py
    $ cd build
    $ ./android-build.py cpp-empty-test -p 10
    $ adb install cocos2d-x/tests/cpp-empty-test/proj.android/bin/CppEmptyTest-debug.apk

Then click item on Android device to run tests. Available value of `-p` is the API level, Cocos2d-x supports from level 10.

**Using Eclipse:**
Perform the following steps:

    $ cd cocos2d-x
    $ ./setup.py
    $ cd build
    $ ./android-build.py cpp-empty-test -p 10

Next:

* Import Cocos2d-x Android project into Eclipse, the path used to import is __cocos/2d/platform/android__
* Import `cpp-empty-test` Android project into Eclipse, the path used to import is __tests/cpp-empty-test/proj.android__
* Build `cpp-empty-test` Android project and run

### Windows
You can run the samples by:

* For win32 project, enter __cocos2d-x/build__, and open __cocos2d-win32.sln__
* For win 8.1 project, enter __cocos2d-x/build__, and open __cocos2d-win8.1-universal.sln__
* For win 10 project, enter __cocos2d-x/build__, and open __cocos2d-win10.sln__
* Select running target
* Click run button

### Linux
You can run the samples by:

    $ cd cocos2d-x/build
    $ ./install-deps-linux.sh
    $ cd ../..

Next:

    $ mkdir build
    $ cd build
    $ cmake ../cocos2d-x
    $ make -j4

Then run:

    $ cd bin/cpp-empty-test
    $ ./cpp-empty-test

## How to start a new game
Use the __cocos__ console app to create a new game:

```
cocos new -l cpp|js|lua MyNewGame
```

# v3.13

## Highlights

* add VR plugin
* support ETC1 alpha channel
* fix AudioEngine performance for Android 4.2+
* add Andorid arm-64 support
* switch to use gcc 4.9
* upgrade CURL to 7.50.0
* upgrade Spine to 3.4
* update glfw to 3.2

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

### Android arm-64 support

Now we provide arm-64 bit 3rd party libraries, which means can build 64-bit apps on Android. You can use the command to build 64-bit apps:
```
cocos run -p android --app-abi arm64-v8a
```

### Switch to use gcc 4.9

cocos2d-x switch to use clang in `v3.12`, but developers reported [some crash issue](https://github.com/cocos2d/cocos2d-x/issues/16244) that caused by using `clang+gnustl_static`, so we switch to use gcc 4.9. We will change to use `clang+c++_static` when `c++_static` is stable.

### Upgrade CURL to 7.50.0

Because CURL has [a bug about connect to IPV4 numerical IP address in NAT64 environment](https://github.com/curl/curl/issues/863), and it is fixed in v7.50.0, so we upgrade to this version when v7.50.0 is released.