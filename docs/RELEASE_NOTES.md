<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.11.1 Release Notes](#cocos2d-x-3111-release-notes)
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
- [v3.11.1](#v3111)
  - [Highlights features](#highlights-features)
  - [The main features in detail of Cocos2d-x v3.11.1](#the-main-features-in-detail-of-cocos2d-x-v3111)
    - [support IPv6-only network](#support-ipv6-only-network)
  - [Other changes](#other-changes)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.11.1 Release Notes #

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# Requirements

## Runtime Requirements

* Android 2.3 or newer
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
* ndk-r10c for Android
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

Then click item on Android device to run tests. Available value of `-p` is the API level, cocos2d-x supports from level 10.

**Using Eclipse:**
Perform the following steps:

    $ cd cocos2d-x
    $ ./setup.py
    $ cd build
    $ ./android-build.py cpp-empty-test -p 10

Next:

* Import cocos2d-x Android project into Eclipse, the path used to import is __cocos/2d/platform/android__
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

# v3.11.1

## Highlights features

* support IPv6-only network


## The main features in detail of Cocos2d-x v3.11.1

### support IPv6-only network
[Apple required to support IPv6-only Networks](https://developer.apple.com/news/?id=05042016a) since June 1, 2016. And this version supports IPv6-only network.

## Other changes
You can also take a look at the [full changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG).
