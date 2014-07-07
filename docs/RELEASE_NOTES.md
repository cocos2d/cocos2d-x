# cocos2d-x v3.2rc0 Release Notes #

**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [cocos2d-x v3.2rc0 Release Notes](#user-content-cocos2d-x-v32rc0-release-notes)
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
- [Highlights of v3.2rc0](#user-content-highlights-of-v32rc0)
- [Toolchain requirement changed](#user-content-toolchain-requirement-changed)
- [Features in detail](#user-content-features-in-detail)
	- [Sprite3d](#user-content-sprite3d)
		- [fbx-conv usage](#user-content-fbx-conv-usage)
	- [Controller support](#user-content-controller-support)
	- [Fast tilemap](#user-content-fast-tilemap)
	- [Node::enumerateChildren](#user-content-nodeenumeratechildren)
	- [utils::findChildren](#user-content-utilsfindchildren)

# Misc Information

* Download: http://cdn.cocos2d-x.org/cocos2d-x-3.2rc0.zip
* Full Changelog: https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.2rc0/CHANGELOG
* API Reference: http://www.cocos2d-x.org/reference/native-cpp/V3.2beta0/index.html
* v3.0 Release Notes can be found here: [v3.0 Release Notes](https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.0/docs/RELEASE_NOTES.md)

# Requirements

## Runtime Requirements

* Android 2.3 or newer
* iOS 5.0 or newer
* OS X 10.7 or newer
* Windows 7 or newer
* Windows Phone 8 or newer
* Linux Ubuntu 14.04 or newer
* ~~Browsers via Emscripten~~ N/A for the moment

## Compiler Requirements

* Xcode 4.6 or newer for iOS or Mac
* gcc 4.9 or newer for Linux
* ndk-r9d or newer for Android
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

# Highlights of v3.2rc0

* `fbx-conv` support generating binary format, and `Sprite3D` support it, and about 
* about 20% performance improved in `Sprite3D`
* game controller support
* fast tilemap support, it is faster for static tilemap
* physics body supports scale and rotation
* added Node::enumearteChildren(), and support c++ 11 regular expression

# Toolchain requirement changed

`Node::enumerateChildren()` uses `std::regex` which will cause crash using gcc v4.8 or lower version. So

* NDK r9d or newer version is required for Android building
* gcc 4.9 is required for linux building


# Features in detail

## Sprite3d

Sample code to use binary version
```c++
auto sprite3d = Sprite3D::create("filename.c3b");
addChild(sprite3d);
```


### `fbx-conv` usage

* Mac OS X

```
$ cd COCOS2DX_ROOT/tools/fbx-conv/mac
$ ./fbx-conv [-a|-b|-t] FBXFile
```

* Windows

```
cd COCOS2DX_ROOT/tools/fbx-conv/windows
fbx-conv [-a|-b|-t] FBXFile
```

Options:

* -a: export both text and binary format
* -b: export binary format
* -t: export text format

## Controller support

Supported controller type:

* amazon tv
* OUYA
* Moga
* Nibiru
* iOS standard controllers

In order to use controller on Android, you should refer to this Android project(`COCOS2DX_ROOT/cocos/platform/android/ControllerManualAdapter`).

Full demo please refer to `COCOS2DX_ROOT/tests/game-controler-test`.

## Fast tilemap

Fast tilemap has the same API as `TMXTiledMap` without deprecated functions.

Sample code
```c++
auto tilemap = FastTMXTiledMap::create("MyFile.tmx");
addChild(tilemap);
```

Full demo please refer to `COCOS2DX_ROOT/tests/cpp-tests/Classes/TileMapTest/TileMapTest2.cpp`.

## Node::enumerateChildren

This functions is used to enumerate children of a `Node` recursively. It supports c++ 11 regular expression.

```c++
// Find nodes whose name is 'nameToFind' and end with digits.
node->enumerateChildren("nameToFind[[:digit:]]+", [](Node* node) -> bool {
    ...
    return false; // return true to stop at first match
});
```

Full test please refer to `NodeNameTest` in `COCOS2DX_ROOT/tests/cpp-tests/NodeTest/NodeTest.cpp`.

Because this function uses `std::regex` which is not supported well in gcc 4.8 or lower version. So we use `clang` and `stdc++` instead for Android building. This lead to the result that `NDK r9d` or newer is required. And `gcc 4.9` is required on linux.

## utils::findChildren

This is a helper function to find children of a `Node` share a name. The implementation of this function bases on `Node::enumerateChildren`.

```c++
auto children = utils::findChildren(node, "nameToFind");

...
```
