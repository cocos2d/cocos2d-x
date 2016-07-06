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

# Cocos2d-x 3.12 Release Notes #

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
* Mordern browsers and IE 9+ (On mobile platforms, only iOS and Android 5 activated WebGL support)

## Compiler Requirements

* Xcode 5.1 or newer for iOS or Mac
* gcc 4.9 or newer for Linux
* ndk-r11+ for Android
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

# v3.12

## Highlights

* add VR support in experimental
* add Tizen support
* improve Android performance issue
* improve web engine performance in WebGL mode
* support Android obb extension
* use clang instead of gcc on Android, use NDK r11+

## The main features in detail of Cocos2d-x v3.12

### VR support
VR Support is now available! Currently there is support for __Google Cardboard__, __Oculus Rift__, __Samsung Gear__ and __Deepoon E2__. Also provided is a *generic* __VR__ renderer to help with testing. It should not be used to trust deploying a production __VR__ game. In usual Cocos2d-x fashion it is very easy to get started with an easy to understand API. Read our chapter in the [Programmers Guide](http://cocos2d-x.org/docs/programmers-guide/vr/index.html) for more information.

### Tizen support
You can now develop for the __Tizen__ mobile platform. The latest __2.4__ SDK is supported. Tizen development uses it's own uniqie IDE as well as a simulator for testing applications. For setup instructions please read our [documentation](http://cocos2d-x.org/docs/installation/Tizen/).

### Improve Android performance

Thank you to our users for helping diagnose performance issues on some Android devices. It is because Cocos2d-x creates a big map buffer by default and fills the map buffer with actual data, which is less than the map buffer size. On some Android devices, it will transfer as much data as the map buffer size which causes performance issue.

More detail information and discussion can refer to [the issue](https://github.com/cocos2d/cocos2d-x/issues/15652).

### Improve web engine performance in WebGL mode

The web engine is receiving a big performance upgrade. The WebGL renderer have been completely refactored from the ground up. This means improved rendering and a reduced memory footprint.

![rendering peformance](https://raw.githubusercontent.com/minggo/Pictures/master/web-performance-improve/adverage-time-per-frame.png)

![cpu-usage](https://raw.githubusercontent.com/minggo/Pictures/master/web-performance-improve/cpu-usage.png)

![memory-usage](https://raw.githubusercontent.com/minggo/Pictures/master/web-performance-improve/memory-usage.png)

### Use clang on Android
[Google deprecated gcc starting in NDK r11](https://developer.android.com/ndk/downloads/revision_history.html), Cocos2d-x now uses clang. We suggest using the NDK r11c.

We found an issue that, if using NDKr 10c + clang, then `Node::enumerateChildren()` will crash on Android.

## Other changes
View our [full changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG).
