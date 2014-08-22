# cocos2d-x v3.3alpha0 Release Notes #

**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [cocos2d-x v3.2 Release Notes](#user-content-cocos2d-x-v32-release-notes)
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
- [Highlights of v3.2](#user-content-highlights-of-v32)
- [Documents](#user-content-documents)
- [Toolchain requirement changed](#user-content-toolchain-requirement-changed)
- [atof issue on Android](#user-content-atof-issue-on-android)
- [Features in detail](#user-content-features-in-detail)
	- [Sprite3D & Animation3D](#user-content-sprite3d--animation3d)
		- [fbx-conv usage](#user-content-fbx-conv-usage)
	- [Game controller](#user-content-game-controller)
	- [Fast tilemap](#user-content-fast-tilemap)
	- [Node::enumerateChildren](#user-content-nodeenumeratechildren)
	- [utils::findChildren](#user-content-utilsfindchildren)
	- [Node::setNormalizedPosition](#user-content-nodesetnormalizedposition)

# Misc Information

* Full Changelog: https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.3alpha0/CHANGELOG
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

* Xcode 5.1 or newer for iOS or Mac
* gcc 4.9 or newer for Linux
* ndk-r9d for Android
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

# Highlights of v3.3alpha0

* 3d: `Camera`, `AABB`, `OBB` and `Ray`
* ui: added `Scale9Sprite`
* FileUitls: added `isDirectoryExist()`, `createDirectory()`, `removeDirectory()`, `removeFile()`, `renameFile()` and `getFileSize()`
* Device: added `setKeepScreenOn()` on iOS and Android 
* Added c++11 random support
* RenderTexture: added a call back function for `saveToFile()`
* SpriteFrameCache: support loading from plist file content data
* Many other small features added and many bugs fixed

# Features in detail

## Camera

This version of camera is powerful then previous one. And you can add it as a child anywhere. If you want to let a Node to be visited by a camera, Node's camera mask should include Camera's flag:

```c++
// let sprite to be visited by a camera
auto sprite = Sprite::create("myFile.png");
sprite->setCameraMask(CameraFlag::USER1);
auto camera = Camera::createPerspective(60, winSize.width/winSize.height, 1, 1000);
camera->setCameraFlag(CameraFlag::USER1);
scene->addChild(camera);
```

If you have many Nodes that want to be visited by a camera, there is a convenient way:

```c++
auto layer = Layer::create();
auto sprite1 = Sprite::create();
auto sprite2 = Sprite::create();
layer->addChild(sprite1);
layer->addChild(sprite2);
// it will set camera mask for all its children
layer->setCameraMask(CameraFlg::USER1); 

auto camera = Camera::createPerspective();
camera->setCameraFlag(CameraFlag::USER1);
scene->addChild(camera);
```

Full test case please  refer to `tests/cpp-tests/res/Camera3DTest/Camera3DTest.cpp`.

## AABB, OBB and Ray

TBD

## ui::Scale9Sprite

TBD

## c++11 random support

Since `rand()` is not good(refer to [this document](http://c-faq.com/lib/randrange.html)), we use c++11 random library to do generate random number, and provide a function to easily using:

```c++
int randInt = cocos2d::random(1, 10);
float randFloat = cocos2d::random(1.f, 10.f);
```

## RenderTexture save function

`RenderTexture::saveToFile()` will not save rendertexture when the function returns, because it just send render command to renderer. The file will be saved after render command is executed. It is not convenient if you want to use the saved file to do some work. So we added a parameter in `RenderTexture::saveToFile()` to set a call back function when the file is saved.

```c++
renderTexture->begin();
...
renderTexture->end();

renderTexture->saveToFile("myFile.png", true, callback);

```

