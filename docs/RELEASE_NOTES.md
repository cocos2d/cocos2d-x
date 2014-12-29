# cocos2d-x v3.4 Release Notes #

**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [cocos2d-x v3.4 Release Notes](#)
- [Misc Information](#)
- [Requirements](#)
	- [Runtime Requirements](#)
	- [Compiler Requirements](#)
	- [How to run tests](#)
		- [Mac OSX & iOS](#)
		- [Android](#)
		- [Windows](#)
		- [Linux](#)
	- [How to start a new game](#)
- [v3.4beta0](#)
	- [Highlights of v3.4beta0](#)
	- [Features in detail](#)

# Misc Information

* Full Changelog: https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.3/CHANGELOG
* v3.0 Release Notes can be found here: [v3.0 Release Notes](https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.0/docs/RELEASE_NOTES.md)

# Requirements

## Runtime Requirements

* Android 2.3 or newer
* iOS 5.0 or newer
* OS X 10.7 or newer
* Windows 7 or newer
* Windows Phone 8 or newer
* Linux Ubuntu 14.04 or newer

## Compiler Requirements

* Xcode 5.1 or newer for iOS or Mac
* gcc 4.9 or newer for Linux
* ndk-r10c for Android
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


# v3.4beta0

## Highlights of v3.4beta0



## Features in detail

### Create Sprite3D asynchronously

It allows to load Sprite3D in another thread so that you can process more logic in the main thread. And it notifies you using a custom callback after creating is finished.

`modelPath` is the file to be loaded, `AsyncLoadSprite3DTest::asyncLoad_Callback` is the user's callback function, `userParam` is the parameter that the callback function is wanted.

```c++
Sprite3D::createAsync(modelPath, CC_CALLBACK_2(AsyncLoadSprite3DTest::asyncLoad_Callback, this), (void*)userParam);
```

The callback function is called after loading Sprite3D, the callback function can be something like this,

```c++
void AsyncLoadSprite3DTest::asyncLoad_Callback(Sprite3D* sprite, void* param)
{
    //sprite is the loaded sprite
    sprite->setPosition(point);
    addChild(sprite);
}
```

