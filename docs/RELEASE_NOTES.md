# cocos2d-x v3.2-alpha0 Release Notes #

**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [cocos2d-x v3.2-alpha0 Release Notes](#user-content-cocos2d-x-v32-alpha0-release-notes)
- [Misc Information](#user-content-misc-information)
- [Requirements](#user-content-requirements)
	- [Runtime Requirements](#user-content-runtime-requirements)
	- [Compiler Requirements](#user-content-compiler-requirements)
	- [How to run tests](#user-content-how-to-run-tests)
		- [Mac OSX & iOS](#user-content-mac-osx--ios)
		- [Android](#user-content-android)
		- [Windows](#user-content-windows)
		- [Linux](#user-content-linux)
	- [How to start a new game](#user-content-how-to-start-a-new-game)
- [Highlights of v3.2 alpha0](#user-content-highlights-of-v32-alpha0)
- [Features in detail](#user-content-features-in-detail)
	- [Animation3D](#user-content-animation3d)
		- [fbx-conv usage](#user-content-fbx-conv-usage)
		- [Sample code](#user-content-sample-code)
	- [captureScreen](#user-content-capturescreen)

# Misc Information

* Download: http://cdn.cocos2d-x.org/cocos2d-x-3.2beta0.zip
* Full Changelog: https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.2beta0/CHANGELOG
* ~~API Reference: http://www.cocos2d-x.org/reference/native-cpp/V3.0/index.html~~
* v3.0 Release Notes can be found here: [v3.0 Release Notes](https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.0/docs/RELEASE_NOTES.md)

# Requirements

## Runtime Requirements

* Android 2.3 or newer
* iOS 5.0 or newer
* OS X 10.7 or newer
* Windows 7 or newer
* Windows Phone 8 or newer
* Linux Ubuntu 12.04 or newer
* ~~Browsers via Emscripten~~ N/A for the moment

## Compiler Requirements

* Xcode 4.6 or newer for iOS or Mac
* gcc 4.7 or newer for Linux
* gcc 4.7 and ndk-r9 or newer for Android
* Visual Studio 2012  or newer for Windows (win32)
* Visual Studio 2012  or newer for Windows Phone 8

## How to run tests

### Mac OSX & iOS

* Enter `cocos2d-x/build` folder, open `cocos2d_test.xcodeproj`
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

* Enter `cocos2d-x/build`, and open `cocos2d-win32.vs2012.sln`
* Select `cpp-empty-test` as running target
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

Please refer to this document: [ReadMe](../README.md)

# Highlights of v3.2 alpha0

* Game controller support
* Fast tmx support
* `Sprite3D` supports binary format, and 20% performance improved
* Integrated physics engine supports scale and rotation
* Added `Node::getName`, `Node::setName`, `Node::enumerateChildren` and `utils::findChildren`
* `fbx-conv` can export binary format

# Features in detail

## Game controller support

There are many game controllers don't follow standard processes on Android. A Android device  wants to run a game supports this type of game controller should install en extra application offered by the game controller maker. `Moga` and `Nibiru` are this kind of game controller.

But don't be afraid, cocos2d-x do these things automatically for you. We put supported game controller applications in a server, engine will download application when it recognize a supported game controller. And install the application automatically.

```c++
auto gameControllerListener = EventListenerController::create();

// add call backs for listener and added into EventDispatcher
...


Controller::startDiscoveryController();

```

Full document will be ready in final version.

## Fast tmx support

It has the same API as `TMXTileMap` except deprecated functions.

```c++
auto map = FastTMXTiledMap::create("test.tmx");
addChild(map);
```

## fbx-conv


* Max OS X

    ```
    $ cd -a|-b|t [path of fbx-conv]
    $ ./fbx-conv [-a|-b|-t] FBXFile
    ```

* Windows

    ```
    cd [path of fbx-conv]
    fbx-conv -a|-b|t FBXFile
    ```

Options:

* -a export both c3t and c3b
* -b export c3b
* -t export c3t


`Note: the bones in the FBX file should not be more than 60.`


## Node::enumerateChildren
