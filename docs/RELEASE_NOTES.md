<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.17 Release Notes](#cocos2d-x-317-release-notes)
  - [Android requirements](#android-requirements)
  - [Highlights](#highlights)
    - [added support for iPhone X](#added-support-for-iphone-x)
    - [added support Android Studio 3.0+](#added-support-android-studio-30)
    - [CMake is now supported on all platforms](#cmake-is-now-supported-on-all-platforms)
    - [upgrade 3rd-party libraries](#upgrade-3rd-party-libraries)
    - [remove outdated](#remove-outdated)
    - [misc bugs fix and stability improvements](#misc-bugs-fix-and-stability-improvements)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.17 Release Notes #
The 3.17 release focuses on stability and increased performance with some under the hood enhancements that will make cross-platform development easier.

## Android requirements

v3.17 has been tested using Android Studio (3.0, 3.1, 3.1.1) with NDK r16

## Highlights

- added support for iPhone X
- added support Android Studio 3.0+ 
- CMake is now supported on all platforms
- upgraded Spine runtime to v3.6.39 
- upgraded GLFW to 3.2.1
- misc bugs fix and stability improvements

### added support for iPhone X

3.17 brings support for iPhone X including supporting full screen mode, using Storyboards for launch images, __safe area__ API and support for auto hiding the Home indicator. It is important to note exactly what and where the safe area is: 

<p align="center">
  <img width="400" src="https://raw.githubusercontent.com/cocos2d/cocos2d-x-docs/master/en/installation/iOS-img/iPhoneXSafeArea.png">
</p>

Developers can get the safe area easily by calling: `Director::getSafeAreaRect()`.

### added support Android Studio 3.0+ 

Android Studio is the only official IDE for Google's Android operating system.
Cocos2d-x supports Android Studio using NDK version r16 to r16. Gradle configurations have been updated, including simplifying Gradle PROP_* values, changing the deprecated `compile` to the new `implementation`in dependency declaration, and added Proguard configuration to reduce Release package size.

### CMake is now supported on all platforms

CMake is now supported on all platforms, including Android(NDK), iOS, macOS, Windows (VC++ compiler), Linux. Supports precompile libraries for engine, and reusing precompiled libraries in the new build process. Your projects build time will be greatly reduced. For detailed usage, please refer to [CMake Doc](https://github.com/cocos2d/cocos2d-x/blob/v3/cmake/README.md)

### upgrade 3rd-party libraries

Spine skeleton animation is widely used in games developed by Cocos2d-x. Spine runtime has been upgraded to 3.6.39 to keep current.

GLFW has been upgraded to 3.2.1 to help fix joystick issues. You can also now use GLFW as a precompiled library.

Box2D hasn't been updated in quite some time. A new production version has yet to be released so far in 2018. We felt GitHub commit f655c603ba9d83 was stable. You can also now use Box2D as a precompiled library.

Each Cocos2d-x release comes with a specific version of third-party libraries. If you want to upgrade third-party libraries due to your projects needs, please refer to: [3rd-party Doc](https://github.com/cocos2d/cocos2d-x-3rd-party-libs-src/blob/v3/README.md)

### remove outdated

Google officially deprecated ant build support starting in [Android SDK Tools 25.3.0](http://tools.android.com/recent/androidsdktoolsrevision2530feb2017). The old ant based `proj.android` and been dropped and now `proj.android` is an Android Studio project. The default architecture is changed from `armeabi` to `armeabi-v7a`.

Visual Studio 2013 support has been dropped. Visual Studio 2015/2017 are still currently supported. The existing win32 project files is quite suitable for 2015. To use 2017, you can open a 2015 project file, modify the configuration to suit your needs, or use CMake (See above).

### misc bugs fix and stability improvements

This release contains more than 51 bugs fixed and 33 misc improvements, please refer to [Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)
