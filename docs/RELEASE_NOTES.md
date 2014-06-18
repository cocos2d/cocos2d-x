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

* Download: http://cdn.cocos2d-x.org/cocos2d-x-3.2alpha0.zip
* Full Changelog: https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.2alpha0/CHANGELOG
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

* `Animation3D`/`Animate3d`, new nodes for 3d animation. lua-binding and WP8 is not supported now.
* Updated libcurl.a to use OpenSSL v1.0.1h, [news](http://cocos2d-x.org/news/286) for it
* Added `utils::captureScreen` to take screeshot


# Features in detail

## Animation3D

Animation3D is skeletal animation in 3D Game. It allows the artist animate a 3D model using bone in 3D modeling tools. Then export the model file and use it in the game.

Work flow

* Artist produce 3D models in modeling tools and then export it to FBX file
* Use `fbx-conv` convert FBX file to c3t file
* Load c3t file in the game

Note

* The API may change in final version
* binary format of c3t will be added in final version
* the bones in the FBX file should not be more than 50.

### `fbx-conv` usage

* windows

```
cd COCOS2DX_ROOT/tools/fbx-convert/win32
fbx-conv FBXFile
```
* mac os x

```
cd COCOS2DX_ROOT/tools/fbx-convert/mac
./fbx-conv FBXFile
```


### Sample code

```c++
//load Sprite3D
auto sprite = Sprite3D::create("girl.c3t");
addChild(sprite);
sprite->setPosition(Vec2( 0, 0));

//load animation and play it
auto animation = Animation3D::getOrCreate("girl.c3t");
if (animation)
{
   auto animate = Animate3D::create(animation);
   sprite->runAction(RepeatForever::create(animate));       
}
```

Full sample please refer to [Sprite3D test](https://github.com/cocos2d/cocos2d-x/blob/v3/tests/cpp-tests/Classes/Sprite3DTest/Sprite3DTest.cpp).

## captureScreen

Please refer to [here](https://github.com/cocos2d/cocos2d-x/blob/v3/tests/cpp-tests/Classes/NewRendererTest/NewRendererTest.cpp) for usage.
