<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.17 Release Notes](#cocos2d-x-317-release-notes)
  - [Misc Information](#misc-information)
  - [Tested](#tested)
  - [Highlights](#highlights)
  - [Highlights in detail](#highlights-in-detail)
    - [added support for iPhone X](#added-support-for-iphone-x)
    - [added support Android Studio 3.0+](#added-support-android-studio-30)
    - [CMake is now supported on all platforms](#cmake-is-now-supported-on-all-platforms)
    - [upgrade 3rd-party libraries](#upgrade-3rd-party-libraries)
    - [remove outdated](#remove-outdated)
    - [misc bugs fix and stability improvements](#misc-bugs-fix-and-stability-improvements)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.17 Release Notes #

## Misc Information

- [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

## Tested

Tested this release using Android tools:

- Android Studio 3.0
- NDK r16

## Highlights

- added support for iPhone X
- added support Android Studio 3.0+ 
- CMake is now supported on all platforms
- upgraded Spine runtime to v3.6.39 
- upgraded GLFW to 3.2.1
- misc bugs fix and stability improvements

## Highlights in detail

### added support for iPhone X

With iPhone X popular, iOS developers using engine need to upgrade game for supporting it. 3.17 release gives the solution to developers, including support full screen, use Storyboard in launch screen, added a API to access to Safe Area, support auto hide Home indicator. The most important thing to note is safe area when do layout, which is the light blue area in image below:

<p align="center">
  <img width="400" src="https://raw.githubusercontent.com/cocos2d/cocos2d-x-docs/master/en/installation/iOS-img/iPhoneXSafeArea.png">
</p>

Developers can get the safe area easily through function `Director::getSafeAreaRect()` provided by engine.

### added support Android Studio 3.0+ 

Android Studio is the only official IDE for Google's Android operating system, and 3.0 have been released in last year, so engine add follow-up support. In the process of support 3.0, we upgrade supported NDK version from r14 to r16, and update Gradle project configuration, including simplify Gradle PROP_* valuse, change the deprecated `compile` to the new `implementation`in dependency declaration, added Proguard configuration to reduce Release package size.

### CMake is now supported on all platforms

CMake is now supported on all platforms, including Android(NDK), iOS, macOS, Windows (VC++ compiler), Linux. Supports precompile libraries for engine, and reuse precompiled libraries in new build process. You can greatly shorten project's build time by this way. For detailed usage, please refer to [CMake Doc](https://github.com/cocos2d/cocos2d-x/blob/v3/cmake/README.md)

### upgrade 3rd-party libraries

Spine skeleton animation is widely used in games developed by Cocos2d-x, runing the material exported by newer Spine on older runtime existed some compatibility issues. Upgrade Spine runtime to 3.6.39 to solve these issues.

GLFW had issues when using GLFW to support joystick before GLFW was upgraded to 3.2.1, so upgrade it, and provide GLFW precompiled library. The older Box2D version is 2.3.1, which was released in 2014. and newer version has not been released, even the beginning of 2018, another side the official repository has been updated with some bugs fixed. According to the community's suggestion, we upgrade Box2D to the latest commit f655c603ba9d83, and provide precompiled Library.

Each release comes with a specific version of third-party libraries. If you want to upgrade third-party libraries due to your project needs, please refer to: [3rd-party Doc](https://github.com/cocos2d/cocos2d-x-3rd-party-libs-src/blob/v3/README.md)

### remove outdated

Google officially deprecated ant build support since [Android SDK Tools 25.3.0](http://tools.android.com/recent/androidsdktoolsrevision2530feb2017), on the other hand Android Studio is stable enough to let us remove the old ant build project `proj.android`, then we renamed the original Android Studio project `proj.android-studio` to `proj.android`, Another change, [armeabi](https://developer.android.com/ndk/guides/abis) have been deprecated at NDK r16, and will be removed in NDK r17, so engine follows. The default architecture is changed from `armeabi` to `armeabi-v7a`.

Visual Studio 2015/2017 has served for a long time, just remove 2013 support. The existing win32 project files is quite suitable for 2015. If you hope to use 2017, you can open 2015 project file, and modify some of configurations, or use CMake build.

### misc bugs fix and stability improvements

This release contains more than 51 bugs fixed, 33 misc improvements, please refer to [Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)
