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

* Full Changelog: https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.4beta0/CHANGELOG
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

### Frustum culling

Frustum culling means only the stuff that is inside the frustum is sent to the graphics hardware. It can potentially improve the performance of the application since only the vertices that are part of the visible part of the 3D world are kept on the graphics card memory.

Frustum culling is a property of camera, it is enabled by default. And you can use the following to enable or disable the frustum culling,

```c++
//the first parameter is enable frustum culling or not, the second means that frustum culling using near and far plan or not.
camera->enableFrustumCulling(true, true);
```

Note that when you can make sure that all the stuff is inside the frustum you can turn off the frustum culling.

For more infomation please reffer to the cpptests/CameraTest

### Use less resources to create  ui::CheckBox and ui::Slider 

Now we could use less resources to create  ui::CheckBox and ui::Slider.

To create an ui::CheckBox, we could simply pass the normal state box and active texture.

```cpp
CheckBox* checkBox2 = CheckBox::create("cocosui/check_box_normal.png",
                                              "cocosui/check_box_active.png");
```

To create an ui::Slider, we could only pass the slider bar texture and normal ball texture.

```cpp
Slider* sliderScale9 = Slider::create("cocosui/slidbar.png", "cocosui/sliderballnormal.png");
```

If the selected state texture is missing, when user press the widget, the normal texture will scale.

If the disable state texture is missing, when the widget is in disable state, we use gray shader to turn the normal state texture to gray.

The original ui::Button also support the gray shader enhancement.
