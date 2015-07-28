<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x v3.7 Release Notes](#cocos2d-x-v37-release-notes)
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
- [v3.7](#v37)
  - [Highlights of v3.7](#highlights-of-v37)
  - [Download](#download)
  - [The main features in detail:](#the-main-features-in-detail)
    - [3D Physics](#3d-physics)
    - [3D Navigation mesh](#3d-navigation-mesh)
    - [Material system](#material-system)
    - [All in one Cocos2d-x](#all-in-one-cocos2d-x)
    - [Enhanced Polygon Sprite](#enhanced-polygon-sprite)
    - [WebView and VideoPlayer in JS (native and web)](#webview-and-videoplayer-in-js-native-and-web)
    - [Nine Patch format support](#nine-patch-format-support)
    - [Android Studio support](#android-studio-support)
    - [Samsung Enhanced API support](#samsung-enhanced-api-support)
    - [SDKBOX](#sdkbox)
  - [The Next Step](#the-next-step)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x v3.7 Release Notes #

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# Requirements

## Runtime Requirements

* Android 2.3 or newer
* iOS 5.0 or newer
* OS X 10.7 or newer
* Windows 7 or newer
* Windows Phone 8.1
* Linux Ubuntu 14.04 or newer
* Mordern browsers and IE 9+ (On mobile platforms, only iOS and Android 5 activated WebGL support)

## Compiler Requirements

* Xcode 5.1 or newer for iOS or Mac
* gcc 4.9 or newer for Linux
* ndk-r10c for Android
* Visual Studio 2013 or newer for Windows (win32)
* Visual Studio 2013 update4 or newer for Windows Phone 8

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

* Enter `cocos2d-x/build` folder, open `cocos2d_test.xcodeproj` or `cocos2d_js_tests.xcodeproj` (For JS test, we will merge these two project in v3.8)
* Select `iOS` or `OS X` target in scheme toolbar
* Click `run` button

### Android

You can run the samples...

**Using command line:**

    $ cd cocos2d-x
    $ ./setup.py
    $ cd build
    $ ./android-build.py cpp-empty-test -p 10
    $ adb install cocos2d-x/tests/cpp-empty-test/proj.android/bin/CppEmptyTest-debug.apk

Then click item on Android device to run tests. Available value of `-p` is the API level, cocos2d-x supports from level 10.

**Using Eclipse:**

    $ cd cocos2d-x
    $ ./setup.py
    $ cd build
    $ ./android-build.py cpp-empty-test -p 10

Then

* Import cocos2d-x Android project into Eclipse, the path used to import is `cocos/2d/platform/android`
* Import `cpp-empty-test` Android project into Eclipse, the path used to import is `tests/cpp-empty-test/proj.android`
* Build `cpp-empty-test` Android project and run

### Windows

* For win32 project, enter `cocos2d-x/build`, and open `cocos2d-win32.sln` or `cocos2d-js-win32.sln`
* For win 8.1 project, enter `cocos2d-x/build`, and open `cocos2d-win8.1-universal.sln` or `cocos2d-js-win8.1-universal.sln`
* Select running target
* Click run button

### Linux

    $ cd cocos2d-x/build
    $ ./install-deps-linux.sh
    $ cd ../..

Then

    $ mkdir build
    $ cd build
    $ cmake ../cocos2d-x
    $ make -j4

Run

    $ cd bin/cpp-empty-test
    $ ./cpp-empty-test

## How to start a new game

Use Cocos Console to create a new game:

```
cocos new -l cpp|js|lua MyGame
```

# v3.7

## Highlights of v3.7

1. Cocos2d-x will only publish the final versions publicly in the future, all alpha, beta, rc versions will be exclusively published in the community. By that I mean in the English and Chinese forum, in developers QQ groups, by the github tags. The final versions will be published with the all in one Cocos.

2. Cocos2d-JS is merged into Cocos2d-x in v3.7, from now on, developers won't get confused about which product they should use. With Cocos2d-x, you can work with C++/Lua/JS and publish to Windows/WP8.1/Android/Mac/iOS/Linux and Web if you use JS. For a smooth transition, we will still announce two products in v3.7, Cocos2d-x v3.7 and Cocos2d-JS v3.7, but they share exactly the same package. In the future versions, there will be only one package. For reference, this have been discussed in [another thread](http://discuss.cocos2d-x.org/t/discuss-the-next-step-of-cocos2d-x/21182/)

* 3d: Added Physics3d support (JS/Lua ready)
* 3d: Added NavMesh support (JS/Lua ready)
* core: Added Material system (JS/Lua ready)
* sprite: Supportted polygon sprite with AutoPolygon generator (JS/Lua ready)
* Scale9Sprite: Added Android 9-patch image support (JS/Lua ready)
* platform: Added Windows 10.0 Universal App(UWP) support
* platform: Add Samsung Enhanced API on Android for cocos
* C++: Added Android Studio support
* JS: Merged JSB and web engine into Cocos2d-x for a All-in-one engine
* JS: Added `ccui.VideoPlayer` and `ccui.WebView` for iOS/Android/Web
* console: Supported build & run Android Studio project with cocos console
* SDKBOX: super EASY way to integrate 3rd party SDKs into cocos2d-x

## Download

[Cocos2d-x v3.7](http://www.cocos2d-x.org/filedown/cocos2d-x-3.7.zip) including : C++, Lua & JS

## The main features in detail:

### 3D Physics

It's the physics engine we provided for providing 3D physics game capability, it works great with our current 3D modules, like 3D sprites, 3D Terrain, etc. We used [bullet](http://bulletphysics.org/wordpress/) library as base of 3D physics, encapsulate it into our Cocos 3D physics APIs. You can refer to Physics3DTest test case for its API and usage, we will add documentation into [programmers guide](http://cocos2d-x.org/programmersguide) lately.

![](http://cdn.cocimg.com/bbs/attachment/Fid_41/41_300874_348f31ee628da2b.png)

### 3D Navigation mesh

The navigation mesh system provides simple to use API to find path in a complexe 3D world, you can add mesh with a triangles list, add obstacles. Then you will add agents which can perform a path finding task and move your 3D sprites to a certain place following the path. You can refer to NavmeshTest test case for its API and usage, we will add documentation into [programmers guide](http://cocos2d-x.org/programmersguide) lately.

![](http://cdn.cocimg.com/bbs/attachment/Fid_41/41_300874_6589cbf376a639b.png)

### Material system

Material system is an advanced system which defines all visual informations (it may contain aural or physical informations in the future) of an object. Instead of just plain an simple texture, you can have more than one texture, and much more features like multi-pass rendering. Refer to [the documentation](https://github.com/chukong/programmers-guide/blob/v3.7/chapters/14.md#shaders-and-materials) for more details.

![](http://cdn.cocimg.com/bbs/attachment/Fid_41/41_300874_a94a91aeeaf401d.png)

### All in one Cocos2d-x

After merged Cocos2d-JS into Cocos2d-x, nothing have changed for C++ and Lua developers, but the engine structure may look very strange to JS developers. Don't worry, the upgrade is still very simple, because the project structure remains the same as before. Refer to [this discussion](http://discuss.cocos2d-x.org/t/cocos2d-js-v3-6-1-hot-fix-for-remote-debugger/21524/2) for more informations.

### Enhanced Polygon Sprite

As it's not very easy to used in the previous version, we have refactored the API for Polygon Sprite. It's now becoming a internal feature of 2d Sprite, you can use AutoPolygon to generate polygons for a sprite, then use it to create the sprite directly, very simple to use.

```
auto pinfo = AutoPolygon::generatePolygon("filename.png");
auto spp = Sprite::create(pinfo);
```

Although it do takes time to generate the polygons information, you can cache and reuse it, we also plan to support the polygons information generation in the editor in the future.

![](http://cdn.cocimg.com/bbs/attachment/Fid_41/41_300874_7b5ef9b52f054f3.png)

### WebView and VideoPlayer in JS (native and web)

The WebView and VideoPlayer have finally been ported to JS, and it supports iOS, Android and Web browsers. You can refer to its usage in the test case: [WebViewTest](https://github.com/cocos2d/cocos2d-x/blob/v3/tests/js-tests/src/GUITest/UIWebViewTest/UIWebViewTest.js) and [VideoPlayerTest](https://github.com/cocos2d/cocos2d-x/blob/v3/tests/js-tests/src/GUITest/UIVideoPlayerTest/UIVideoPlayerTest.js).

### Nine Patch format support

The Nine Patch image is a stretchable bitmap image which can be used as the texture of Scale9Sprite. Now Cocos2d-x support creating the Scale9Sprite node directly with a Nine Patch file. More informations about the [Nine Patch format](http://developer.android.com/guide/topics/graphics/2d-graphics.html#nine-patch) and [its tool](http://developer.android.com/tools/help/draw9patch.html). You can also refer to our test case for its usage: [C++](https://github.com/cocos2d/cocos2d-x/blob/v3/tests/cpp-tests/Classes/UITest/CocoStudioGUITest/UIScale9SpriteTest.cpp#L857), [Lua](https://github.com/cocos2d/cocos2d-x/blob/v3/tests/lua-tests/src/CocoStudioTest/CocoStudioGUITest/CocoStudioGUITest.lua#L4020), [JS](https://github.com/cocos2d/cocos2d-x/blob/v3/tests/js-tests/src/GUITest/UIS9NinePatchTest/UIS9NinePatchTest.js)

### Android Studio support

Cocos console now supports compilation and package with Android Studio 1.2, use it with a `--android-studio` flag

```
cocos run/compile -p android --android-studio
```

### Samsung Enhanced API support

Samsung have provided a series of Enhanced API to optimize Cocos2d-x games for Samsung products with Android 5.0+ system. It include some very cool features like: Boost Up API, Power Saving Mode API, Dynamic FPS API, etc. The current API can be found in [this header file](https://github.com/cocos2d/cocos2d-x/blob/v3/cocos/platform/android/CCEnhanceAPI-android.h), we will provide a detailed documentation later.

### Win32 platform resource name become case sensitive

In the previous versions, the resources file name's case is ignored on win32 platform, but not ignored in other platforms. This will lead to some unexpected issues, especially when user develop with win32 platform and pulish to other platforms like Android. In win32, the file name may be found without matching the case, but on other platforms it won't be found. So we decided to make win32 platform's resources case sensitive. Please make sure you are using the correct file name for your resources.

### SDKBOX

SDKBOX is a project that's built by part of the cocos2d-x team, in order to makes integrating 3rd party SDKs super EASY.
With SDKBOX you can integrate services like In App Purchase with one command

```
sdkbox import -b iap
```

Currently supported service including

* [Tune](http://cocos2d-x.org/sdkbox/tune)
* [In App Purchase](http://cocos2d-x.org/sdkbox/iap)
* [AdColony](http://cocos2d-x.org/sdkbox/adcolony)
* [Vungle](http://cocos2d-x.org/sdkbox/vungle)
* [Chartboost](http://cocos2d-x.org/sdkbox/chartboost)
* [Kochava](http://cocos2d-x.org/sdkbox/kochava)
* [Google Analytics](http://cocos2d-x.org/sdkbox/googleanalytics)
* [Flurry Analytics](http://cocos2d-x.org/sdkbox/flurryanalytics)

## The Next Step

As you can see, in v3.7, we have enhanced our 2d rendering with material system and integrated polygon sprite. More importantly, our 3d features become more and more complete, 3d Physics and Navigation Mesh with the previous Camera, 3d Sprite, 3d Particle System, 3d Light, 3d Terrain, Skybox, now you can really start to use Cocos to make a 3d game.

In v3.8, we won't do much more features, but we'd like to slow down and refine our current 3D and 2D modules.

[The v3.8 milestone tasks](https://github.com/cocos2d/cocos2d-x/milestones/v3.8)
