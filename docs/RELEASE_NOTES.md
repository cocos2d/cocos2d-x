# Cocos2d-x 3.17 Release Notes #

## Misc Information

- [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

## Tested

Our test team have tested 3.17 release using: 

Android 

- Android Studio 3.0
- NDK r16

Linux

- Ubuntu 16.04

Windows

- Visual Studio 2015

iOS/macOS

- Xcode 9, iOS Device

## Highlights

- added support for iPhone X
- added support Android Studio 3.0+ 
- CMake is now supported on all platforms
- upgraded Spine runtime to v3.6.39 
- upgraded GLFW to 3.2.1
- misc bugs fix and stability improvements

## Highlights in detail

### added support for iPhone X

With iPhone X popular, iOS developers using the engine need to upgrade his game for support iPhone X. Cocos2d-x 3.17 gives the solution for developers, including support iPhone X full screen, use Storyboard at launch screen, added a API to access to Safe Area, support auto hide Home indicator.

When developing applications that support iPhone X, the most important thing to note is the Safe Area when when do layout, which is the light blue area in the image:

<p align="center">
  <img width="400" src="https://raw.githubusercontent.com/cocos2d/cocos2d-x-docs/master/en/installation/iOS-img/iPhoneXSafeArea.png">
</p>

Developers can get the Safe Area easily through the interface `Director::getSafeAreaRect()` provided by the engine.

### added support Android Studio 3.0+ 

Android Studio is the only official IDE for Google's Android operating system, and 3.0 have been released in last year, so engine add follow-up support Android Studio 3.0. In the process of support 3.0, we upgrade the supported NDK version from r14 to r16, and update Gradle project configuration, including simplify the Gradle PROP_* valuse, change the deprecated `compile` in the dependency declaration to the new `implementation`, added the Proguard configuration to reduce the Release package size.

### CMake is now supported on all platforms

CMake is now supported on all platforms, including iOS, Android(NDK), macOS, Linux, Windows (VC++ compiler). Supports precompile libraries of engines, and reuse the precompiled engine libraries in new builds. You can greatly shorten the project's build time by using precompiled libraries.

For detailed usage, please refer to [CMake Documentation](https://github.com/cocos2d/cocos2d-x/blob/v3/cmake/README.md)

### Upgrade 3rd-party libraries

Spine skeletal animation is widely used in games developed using Cocos2d-x. Runing the material exported by the newer Spine on older versions of the runtime existed some compatibility problems. Upgrade Spine runtime to 3.6.39 to solve these problems.

The GLFW had problems when using the GLFW to support the joystick before the GLFW was upgraded to 3.2.1, so upgrade it, and provide GLFW precompiled library. The older Box2D version is 2.3.1, which was released in 2014. The new version has not been released, even the beginning of 2018, another side the official repository has been updated with some bugs fixed. According to the community's suggestion, we upgrade the Box2D to the latest commit f655c603ba9d83, and provide the precompiled Library.

Each release comes with a specific version of third-party libraries. If you want to upgrade third-party libraries due to your project needs, please refer to: [3rd-party Documentation](https://github.com/cocos2d/cocos2d-x-3rd-party-libs-src/blob/v3/README.md)

### Remove Outdated

Since Google officially deprecated ant build support from [Android SDK Tools 25.3.0](http://tools.android.com/recent/androidsdktoolsrevision2530feb2017), on the other hand Android Studio is stable enough to let us remove the old ant project `proj.android` and rename the original Android Studio project `proj.android-studio` to `proj.android`, Another changes, [armeabi](https://developer.android.com/ndk/guides/abis) have been deprecated at [NDK r16], and will be removed in NDK r17, so engine follows. The default Android project build architecture is changed from `armeabi` to `armeabi-v7a`.

Visual Studio 2013 has had some history, just remove support. The existing win32 project files is suitable for Visual Studio 2015. If you need to use 2017, you can open the 2015 project file, and modify some of the configuration, or use the CMake build.

### stability improvements

This release contains more than 51 bugs fixed, 33 misc improvements, please refer to [Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)
