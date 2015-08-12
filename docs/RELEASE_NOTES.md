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
- [v3.7.1](#v371)
  - [Highlights of v3.7.1](#highlights-of-v371)
  - [Download](#download)
  - [The main features in detail:](#the-main-features-in-detail)
    - [Skeleton Animation](#skeleton-animation)
    - [Get Node's transform to its ancestor](#get-nodes-transform-to-its-ancestor)
    - [Set background color for web engine](#set-background-color-for-web-engine)
    - [Widget's enable state and bright state](#widgets-enable-state-and-bright-state)
    - [Firefox remote debugger support](#firefox-remote-debugger-support)
- [v3.7](#v37)
  - [Highlights of v3.7](#highlights-of-v37)
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
* Visual Studio 2013 update4 or newer for Windows 8.1 universal Apps
* Visual Studio 2015 RC or newer and Windows 10.0 (build 10074 or higher) for Windows 10.0 UWP Apps

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
* For win 10 project, enter `cocos2d-x/build`, and open `cocos2d-win10.sln`
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

# v3.7.1

## Highlights of v3.7.1

Cocos2d-x v3.7.1 is a stable version based on v3.7. The most important update is that we added skeleton animation support for Cocos 2.3.2Beta.

* [NEW]     studio: Added new skeleton animation support and csb parser for cocos v2.3.2 beta
* [NEW]     studio: Added new skeleton animation support and JSON parser in the web engine
* [NEW]     studio: Added Skybox csb/JSON parser for cocos v2.3.2 beta
* [NEW]     studio: Parsed Touch/Click/Event callback in JSON parser
* [NEW]     Node: Added getNodeToParentTransform with selected ancestor
* [NEW]     web: Added cc.director.setClearColor and support transparent background
* [REFINE]  Widget: Synchronize enable state and bright state for Widget
* [REFINE]  studio: Optimized JSON parser's performance by removing audio play
* [REFINE]  JSB: Add Firefox remote debugger support in JS templates

## Download

[Cocos2d-x v3.7.1](http://www.cocos2d-x.org/filedown/cocos2d-x-3.7.1.zip) including : C++, Lua & JS

## The main features in detail:

### Skeleton Animation

In v3.7.1 and Cocos 2.3.2, we are providing a new skeleton animation system which is different from Armature. The reason is that we abstract ActionTimeline system to support all sort of animations but Armature doesn't support it. To benefit the timeline system and to make skeleton animation system much more compact, we have implemented the new skeleton animation system. From this version, you will be able to edit skeleton animations in Cocos v2.

New skeleton animation system contains `BoneNode`, `SkeletonNode`, `SkinNode`. SkeletonNode is a subclass of BoneNode and extended container functionalities, so it can contain BoneNode and nested SkeletonNode to construct a skeleton. 

Features provided: 

1. Playable skeleton animation
2. Nested skeleton
3. Skin replacement
4. Time scale control
5. Debug draw
6. Frame event callback

New skeleton animation is also supported by the web engine. We will keep enhancing it in the future versions.

![](https://raw.githubusercontent.com/minggo/Pictures/master/action-timeline.gif)

### Get Node's transform to its ancestor

We have added a new functionality in `getNodeToParentTransform` API of Node, in v3.7.1, you can pass a ancestor as a parameter to get the node's transform related to this specific ancestor. Here is an example:

```
auto parent2 = Node::create();
auto parent1 = Node::create();
auto node = Node::create();
parent2->addChild(parent1);
parent1->addChild(node);
// This will give you the transform of node in parent2's coordinate system
auto transform = node->getNodeToParentTransform(parent2);
```

This API is also usable in the web engine.

### Set background color for web engine

From v3.7.1, you can control the background of your game in the web engine easily. We have provided a new API: `cc.director.setClearColor()`. The color you passed can be non-transparent or with transparency. Note that if the clear color you want is not transparent, it's more efficient than creating a background layer. Take a look at the example:

```
// Solution1: Using colored background layer
var background = cc.LayerColor(cc.color(255, 0, 0));
background.width = cc.winSize.width;
background.height = cc.winSize.height;
// This will give you a red background
scene.addChild(background, 0);

// Solution2: Using setClearColor
// This will give you a red background and much more efficient than solution1
cc.director.setClearColor(cc.color(255, 0, 0));
```

Besides, you can make your background totally tranparent too.

### Widget's enable state and bright state

In the old Widget API design, `setEnabled` only controls whether the widget should respond to user input events, while `setBright` only controls whether the widget's display should be in gray state (which indicates disable) or bright state (which indicates enable). This is very frustrating for our developers. So from v3.7.1, we decided to synchronise bright state with enable state. That means, once your widghet is disabled via `setEnabled(false)`, its display will also change to gray state.

```
// In old version, you will do
widget->setEnabled(false);
widget->setBright(false);

// In v3.7.1, you only need to do
widget->setEnabled(false);
```

### Firefox remote debugger support

In v3.7.1, we have enabled Firefox remote debugger support for JSB projects. You only need to follow [this documentation](http://www.cocos2d-x.org/docs/manual/framework/native/v3/js-remote-debugger/en), and you can debug your JSB projects with your Firefox browser. Note that it permits you to debug JavaScript code in your JSB project, for native code debugging you should still use Xcode or Visual Studio.

![](https://raw.githubusercontent.com/minggo/Pictures/master/js-remote-debug.png)


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

# The Next Step

As you can see, in v3.7, we have enhanced our 2d rendering with material system and integrated polygon sprite. More importantly, our 3d features become more and more complete, 3d Physics and Navigation Mesh with the previous Camera, 3d Sprite, 3d Particle System, 3d Light, 3d Terrain, Skybox, now you can really start to use Cocos to make a 3d game.

In v3.8, we won't do much more features, but we'd like to slow down and refine our current 3D and 2D modules.

[The v3.8 milestone tasks](https://github.com/cocos2d/cocos2d-x/milestones/v3.8)
