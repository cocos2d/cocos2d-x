<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.9 Release Notes](#cocos2d-x-39-release-notes)
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
- [v3.9](#v39)
  - [Highlights features, improvements and API updates of v3.9](#highlights-features-improvements-and-api-updates-of-v39)
  - [The main features in detail of Cocos2d-x v3.9:](#the-main-features-in-detail-of-cocos2d-x-v39)
    - [3D Module](#3d-module)
    - [2D Module](#2d-module)
    - [Others](#others)
  - [Other changes](#other-changes)
  - [NEW APIS](#new-apis)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.9 Release Notes #

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

* Enter `cocos2d-x/build` folder, open `cocos2d_test.xcodeproj`
* Select `cpp-tests`, `lua-tests`, `js-tests` for `iOS` or `OS X` target in scheme toolbar
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

* For win32 project, enter `cocos2d-x/build`, and open `cocos2d-win32.sln`
* For win 8.1 project, enter `cocos2d-x/build`, and open `cocos2d-win8.1-universal.sln`
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
cocos new -l cpp|js|lua MyNewGame
```

# v3.9

## Highlights features, improvements and API updates of v3.9

We are happy to announce the release of Cocos2d-x v3.9. Following are the highlighted features, improvements and API updates in this version. 

1. 3D Module: 
    - Added 3D MotionStreak to support streak effect. 
    - Refined Sprite3D to support material system. 
2. 2D Module:
    - Added frame callback function and animation callback function. 
    - Added script component system. 
    - Reconstruction of 2D physics with Component. 
    - Improved EditBox implemention on iOS and Win32 platform.
    - Removed dependence of libcurl on AssetsManager, AssetsManagerEx and Downloader (iOS & Android).
    - Improved particle performance. 
3. Others: 
    - Supported Action inheritance, update function overwriting in JSB. 
    - Improved ScrollView performance in Web engine. 
    - Improved Scale9Sprite performance in Web engine. 
    - Decoupled Sprite's setTexture and updateColor in Web engine.
    - Added support for debugging and release on real devices with Xcode7 and iOS9.

## The main features in detail of Cocos2d-x v3.9:

### 3D Module

1. 3D MotionStreak
    
    In this version, 3D MotionStreak is added to support streak effect. Check the testcase: [Sprite3DTest](https://github.com/cocos2d/cocos2d-x/blob/v3/tests/cpp-tests/Classes/Sprite3DTest/Sprite3DTest.cpp#L2472) to see how to use it.

2. Sprite3D

    Added Sprite3D material class. It will be easy and convenient to create internal material. 

### 2D Module

1. Frame callback function and animation callback function

    Three interfaces are added in ActionTimelineData class, which are addFrameEndCallFunc, removeFrameEndCall and clearFrameEndCalls. It will be easy to add or remove specific frame event. 

2. Script Component 

    Script component is used to extend c++ Nodes. You can add a script component to a Node, then the script component will receive onEnter,onExit and update events. For example:

    ```c++ 
    // create a sprite and add a lua component auto player =
    Sprite::create("player.png");
    
    auto luaComponent = ComponentLua::create("player.lua");
    player->addComponent(luaComponent);
    ```
    
    ```lua
    // player.lua
    local player = { 
        onEnter = function(self)
        -- do some things in onEnter 
        end
        
        onExit = function(slef) 
        -- do some things in onExit 
        end
        
        update = function(self)
        -- do some things every frame 
        end
    }
    
    -- it is needed to return player to let c++ nodes know it 
    return player 
    ```
    
    Javascript can work as the same way, just use ComponentJS instead of ComponentLua. 
    
    There are some differences between lua component and Javascript component:
    
    Should return the object in lua component, in Javascript, you only have to extend cc.ComponentJS, and ensure the result of the last statement is the class of Component.
    
    Lua component can only be used in lua projects, Javascript component can only be used in Javascript projects.
    
    More detail usage please refer to: `tests/lua-tests/src/ComponentTest` and `tests/js-tests/src/ComponentTest`


3. 2D Physics

    Before v3.9, there are many physics related codes in Node, such as Node::setPhysicsBody(). Since v3.9, we move these codes into physics component.

    After using physics component, the way to use physics is changed. Before v3.9, you can use physics like this:
    
    ```
    auto node = Node::create(); 
    node->setPhysicsBody(PhysicsBody::createEdgeBox(...));
    ```
    
    Since v3.9 you should use like this:
    
    ```
    auto node = Node::create();
    node->addComponent(PhysicsBody::createEdgeBox(...));

    ```

4. EditBox implemention on iOS and Win32 platform

    - Specify the maximum number of characters in the dialog box. 
    - Support password input. 
    - Games will continue when the dialogue box pops up. 
    - Sync the content in dialogue box. 

5. Remove dependence of curl on AssetsManager, AssetsManagerEx and Downloader (iOS & Android)

    From v3.9, iOS and Android version will not depend on libcurl, which make
    the game package smaller and solve some bugs caused by libcurl. Stability has
    been improved with the updated iOS and Android system. 

6. Improved particle performance. 

### Others

1. Supported Action inheritance, update function overwriting in JSB

    In previous version of JSB, developers cannot inherit Action class in JS script, such as Action / ActionInterval / ActionInstant, for their update function will not be called. In v3.9, developers can create subclass of Action and make extensions. More detail usage please refer to the textcase in ActionTest / ActionCustomTest.

2. ScrollView performance on Web engine

    ScrollView and ListView are the popular UI controls in Web engine. Their
    performance is not perfect in previous versions, especially when there are multiple sub-controls. In v3.9, we have improved its rendering performance. They only act on the contents displayed on the current screen. Test
    date shows that, comparing with v3.8, rendering efficiency of v3.9 have been improved for twice to four times in different devices and browsers. 

3. Scale9Sprite performance on Web engine

    In this version, we have changed the way to construct 9-slice sprite. The engine uses 9 rendering commands instead of the 9 nodes in previous versions. This helps to reduce memory usage and improve rendering performance. 

4. Decoupled Sprite's setTexture and updateColor in Web engine.

    - Organized the rendering logic in Sprite. UpdateColor is accomplished by texture instead of the Sprite. 
    - Fixed a bug about image with alpha channel that when the image is set to black, there is color difference between previous and current version. 
    - Improved texture update logic to reduce texture updates when changing colors.
    - Improved the logic about the rendering function in SpriteCanvasRenderCmd.
    - Removed some duplicate codes about updateColor.

5. Support for debugging and release on real devices with Xcode7 and iOS9

    In v3.8.1, we have made it possible to debug on Xcode7. However, there was a bug with iOS9 real device debuging, and in v3.9, we have fixed the bug.


## Other changes

[NEW]           Label: Added line spacing/leading feature to Label.

[NEW]           ListView: Added APIs to scroll to specific item in list.

[NEW]           ListView: Added APIs to get an item in specific position like center, leftmost, rightmost, topmost and bottommost.

[NEW]           ListView: Added a feature for magnetic scrolling.

[NEW]           Animate: Added ActionTimeline::setAnimationEndCallBack and ActionTimeline::addFrameEndCallFunc.

[NEW]           Animate: Added CSLoader::createNodeWithVisibleSize, CSLoader::createNodeWithVisibleSize and moved "ui::Helper::DoLayout" into them.

[NEW]           Stuio: Added support for Cocos Studio Light3D.

[NEW]           Platform: Added the missing CURL support to the Windows 10 UWP version.

[NEW]           Platform: Added UIEditBox support on linux platform.

[REFINE]        3D: Added non-null checks in PUScriptCompiler::visit before dereferencing.

[REFINE]        3D: Refined SkyboxBrush by making the shader parameter take effect at once.

[REFINE]        Label: Changed label font size type to float to support high precision when font size is small.

[REFINE]        ListView: Fixed an issue that list view's Magnetic::CENTER is not working well when non-bounceable.

[REFINE]        ListView: Added feature of jumping to a specific item in list view.

[REFINE]        Sprite: Added a "unsupport image format!" log when creating a sprite in CCImage.cpp.

[REFINE]        ScrollView: Merge logics of Scroll View for scroll by inertia and auto scroll into one.

[REFINE]        Animate: Moved initialization of image to an appropriate location, because it always called twice in 
SpriteFrameCache::addSpriteFramesWithFile().

[REFINE]        Simulator: Changed the size of startFlag to 13.

[REFINE]        Simulator: Show Node and Skeleton in the middle of the simulator.

[REFINE]        Simulator: Removed screen direction check in simulator to avoid render error.

[REFINE]        Pysics: Refined components to improve physics performance.

[REFINE]        UI: Refined ComponentContainer to improve performance.

[REFINE]        UI: EventListenerMouse will dispatch EventMouse events.

[REFINE]        OpenGL: Added check for glfwCreateWindow.

[REFINE]        Platform: Fixed a crash on xiaomi2 if Cocos2d-x is built as a dynamic library.

[REFINE]        Platform: Updated libcococs2d name to v3.9 on WinRT platforms.

[REFINE]        Platform: Added some support for mouse on WinRT. Include: Show/Hide mouse cursor; Mouse event 
implemented similar Desktop version; Left button send mouse event and touch; Support other mouse button and scroll 
wheel.

[REFINE]        Platform: Correct the convertion between unicode and utf8 on WinRT.

[REFINE]        Platform: Improved EditBox implement on Win32 platform.

[REFINE]        JS: Add jsb.fileUtils.writeDataToFile().

[REFINE]        JS: Set js templates Mac target platform from null to 10.7.

[REFINE]        JS: Removed the static define of variable in headfile of ScriptingCore.

[REFINE]        Lua: Added AssetsManagerEx constants UPDATE_FAILED and ERROR_DECOMPRESS in Lua.

[REFINE]        Lua / JS: Refined lua/js binding tool.

[REFINE]        I/O: Refined AssetsManagerEx unzipping by using async.

[REFINE]        Web: Improved logic of jsb_boot.js to sync with the web engine behavior.

[REFINE]        Web: Sync with CCBoot for web.

[REFINE]        Build: Fixed various compiler warnings on Xcode 7.

[REFINE]        Build: Fixed Wformat-security warning on Xcode.

[REFINE]        Build: Fixed a compile error in __LayerRGBA.

[REFINE]        Tool: Added tools for generating documents automatically.

[REFINE]        Doc: Clean up the code of setRect() function.

[REFINE]        Doc: Fixed a minor typo and renamed INTIAL_CAPS_ALL_CHARACTERS to INITIAL_CAPS_ALL_CHARACTERS 
in UIEditBox.

You can also take a look at the [full changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG).


## NEW APIS

1. JSB Module

    Added jsb.fileUtils.writeDataToFile

2. Sprite3D

    Added Sprite3Dmaterial class to make it easy to create innate material. 

3. ActionTimelineData 

    Three interfaces are added in ActionTimelineData class, which are addFrameEndCallFunc, removeFrameEndCall and clearFrameEndCalls.

4. ActionTimeline::removeFrameEndCallFunc 

5. Improvements for ListView

    - Add APIs to scroll to specific item in list.
    - Add APIs to get an item in specific position like center, leftmost, rightmost, topmost and bottommost.
    - Add a feature for magnetic scrolling.

    For more information: https://github.com/cocos2d/cocos2d-x/pull/13723

6. Node

    Added the missing API getChildByTag

7. Label

    Added setLineSpacing, getLineSpacing

8. CSLoader

    Added createNodeWithVisibleSize, createNodeWithVisibleSize
9. ComponentContainer

    Removed isEmpty

10. Sprite

    Removed debugDraw(bool on)
