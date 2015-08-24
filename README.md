<img src="http://www.cocos2d-x.org/attachments/801/cocos2dx_portrait.png" width=200>


cocos2d-x
=========

|  |iOS|Mac|Linux|Win32|Android|Win8.1-Universal|
| ----|----|----- | ---|----|------|---|
|v3|[![Build Status](http://45.56.80.45:8080/buildStatus/icon?job=daily-build-v3/node=ios)](http://45.56.80.45:8080/job/daily-build-v3/node=ios)|[![Build Status](http://45.56.80.45:8080/buildStatus/icon?job=daily-build-v3/node=mac)](http://45.56.80.45:8080/job/daily-build-v3/node=mac)|[![Build Status](http://45.56.80.45:8080/buildStatus/icon?job=daily-build-v3/node=linux)](http://45.56.80.45:8080/job/daily-build-v3/node=linux)|[![Build Status](http://45.56.80.45:8080/buildStatus/icon?job=daily-build-v3/node=win32)](http://45.56.80.45:8080/job/daily-build-v3/node=win32)|[![Build Status](http://45.56.80.45:8080/buildStatus/icon?job=daily-build-v3/node=android)](http://45.56.80.45:8080/job/daily-build-v3/node=android)|[![Build Status](http://45.56.80.45:8080/buildStatus/icon?job=daily-build-v3/node=windows-universal)](http://45.56.80.45:8080/job/daily-build-v3/node=windows-universal)|
|v4|[![Build Status](http://45.56.80.45:8080/buildStatus/icon?job=daily-build-v4/node=ios)](http://45.56.80.45:8080/job/daily-build-v4/node=ios)|[![Build Status](http://45.56.80.45:8080/buildStatus/icon?job=daily-build-v4/node=mac)](http://45.56.80.45:8080/job/daily-build-v4/node=mac)|[![Build Status](http://45.56.80.45:8080/buildStatus/icon?job=daily-build-v4/node=linux)](http://45.56.80.45:8080/job/daily-build-v4/node=linux)|[![Build Status](http://45.56.80.45:8080/buildStatus/icon?job=daily-build-v4/node=win32)](http://45.56.80.45:8080/job/daily-build-v4/node=win32)|[![Build Status](http://45.56.80.45:8080/buildStatus/icon?job=daily-build-v4/node=android)](http://45.56.80.45:8080/job/daily-build-v4/node=android)|[![Build Status](http://45.56.80.45:8080/buildStatus/icon?job=daily-build-v4/node=windows-universal)](http://45.56.80.45:8080/job/daily-build-v4/node=windows-universal)|



[cocos2d-x][1] is a multi-platform framework for building 2d games, interactive books, demos and other graphical applications.
It is based on [cocos2d-iphone][2], but instead of using Objective-C, it uses C++.
It works on iOS, Android, Windows Phone and Store Apps, OS X, Windows, Linux and Web platforms.

**Cocos2d-x Framework Architecture**:

![](docs/framework_architecture.jpg "")

cocos2d-x is:

  * Fast
  * Free
  * Easy to use
  * Community Supported

Git user attention
-----------------------

1. Clone the repo from GitHub.

         $ git clone https://github.com/cocos2d/cocos2d-x.git

2. After cloning the repo, please execute `download-deps.py` to download and install dependencies.

         $ cd cocos2d-x
         cocos2d-x $ python download-deps.py

3. After running `download-deps.py`.

         cocos2d-x $ git submodule update --init

Download stable versions
-----------------------

* [Cocos2d-x stable versions](http://www.cocos2d-x.org/download)
* [Cocos2d-JS Lite version](http://www.cocos2d-x.org/filecenter/jsbuilder)

How to start a new game
-----------------------

1. Download the code from [cocos2d download site][4]
2. Run `setup.py`
3. Run the `cocos` script

Example:

    $ cd cocos2d-x
    $ ./setup.py
    $ source FILE_TO_SAVE_SYSTEM_VARIABLE
    $ cocos new MyGame -p com.your_company.mygame -l cpp -d NEW_PROJECTS_DIR
    $ cd NEW_PROJECTS_DIR/MyGame

You can also create a JS project or Lua project with `-l js` or `-l lua`.

### Build and run a new project for Android ###

    $ cocos run -p android -j 4

### Build and run a new project for iOS ###

    $ cocos run -p ios

### Build and run a new project for OSX ###

    $ cocos run -p mac

### Build and run a new project for Linux ###

If you never run cocos2d-x on Linux, you need to install all dependencies by the
script in **cocos2d/build/install-deps-linux.sh**

    $ cd cocos2d-x/build
    $ ./install-deps-linux.sh

Then

    $ cd NEW_PROJECTS_DIR/MyGame
    $ cocos run -p linux

Run

    $ bin/MyGame

### Build and run new project for win32 ###

    $ cocos run -p win32

### Build and run new project for Windows 8.1/10.0 and Windows Phone 8.1/10.0 ###

    $ cocos new MyGame -p com.your_company.mygame -l cpp -d projects

* Visual Studio 2013 Update 4 or later is required for Windows 8.1 Universal Apps

* Visual Studio 2015 (Release version) and Windows 10.0 (Release version) are required for Windows 10.0 Universal Windows Platform (UWP) Apps. RC versions of Visual Studio and Window 10 are no longer supported.

Starting with Cocos2d-x v3.3, you can create Windows 8.1 Universal Apps (Windows Store and Windows Phone 8.1).
Starting with Cocos2d-x v3.8 you can create Windows 10.0 UWP Apps (Windows Store and Windows Phone 10.0).
Starting with Cocos2d-x v3.6 there will no longer be support for Windows Phone 8.0.

See more info on How to install and Create games on Windows RT (Windows and Windows Phone 8.1) at http://msopentech.github.io/cocos2d-x/

### Build and run new project for web ###

Only JS project can be published to web platforms, so you will need to create a JS project first:

    $ cocos new -l js WebGame

Then you can run your game in a web browser:

    $ cocos run -p web

Or you can publish your game to `publish/html5/` folder:

    $ cocos run -p web -m release [--advanced]

Documentations and samples
-------------

* [Online API Reference](http://cocos2d-x.org/wiki/Reference) _Note that Cocos2d-x and Cocos2d-JS have different API set_
* [Programmers Guide](http://cocos2d-x.org/programmersguide/)
* [Temporary Cocos2d-JS documents](http://cocos2d-x.org/docs/manual/framework/html5/en)
* [Latest Release Note](https://github.com/cocos2d/cocos2d-x/blob/v3/docs/RELEASE_NOTES.md)
* [Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)
* [Cocos2d sample games](https://github.com/cocos2d/cocos2d-x-samples) _More samples will be added in v3.8_

Main features
-------------
   * Scene management (workflow)
   * Transitions between scenes
   * Sprites and Sprite Sheets
   * Effects: Lens, Ripple, Waves, Liquid, etc.
   * Actions (behaviours):
     * Trasformation Actions: Move, Rotate, Scale, Fade, Tint, etc.
     * Composable actions: Sequence, Spawn, Repeat, Reverse
     * Ease Actions: Exp, Sin, Cubic, Elastic, etc.
     * Misc actions: CallFunc, OrbitCamera, Follow, Tween
   * Basic menus and buttons
   * Integrated with physics engines: [Box2d][5] and [Chipmunk][6]
   * Particle system
   * Skeleton Animations: [Spine][7] and Armature support
   * Fonts:
     * Fast font rendering using Fixed and Variable width fonts
     * Support for .ttf fonts
   * Tile Map support: Orthogonal, Isometric and Hexagonal
   * Parallax scrolling
   * Motion Streak
   * Render To Texture
   * Touch/Accelerometer on mobile devices
   * Touch/Mouse/Keyboard on desktop
   * Sound Engine support (CocosDenshion library) based on OpenAL
   * Integrated Slow motion/Fast forward
   * Fast and compressed textures: PVR compressed and uncompressed textures, ETC1 compressed textures, and more
   * Resolution Independent
   * Language: C++, with Lua and JavaScript bindings
   * Open Source Commercial Friendly(MIT): Compatible with open and closed source projects
   * OpenGL ES 2.0 (mobile) / OpenGL 2.1 (desktop) based

Build Requirements
------------------

* Mac OS X 10.7+, Xcode 5.1+
* or Ubuntu 12.10+, CMake 2.6+
* or Windows 7+, VS 2013+
* Python 2.7.5
* NDK r10c+ is required to build Android games
* Windows Phone/Store 8.1 VS 2013 Update 4+ or VS 2015
* Windows Phone/Store 10.0 VS 2015
* JRE or JDK 1.6+ is required for web publishing

Runtime Requirements
--------------------
  * iOS 5.0+ for iPhone / iPad games
  * Android 2.3+ for Android games
  * Windows 8.1 or Windows 10.0 for Windows Phone/Store 8.1 games
  * Windows 10.0 for Windows Phone/Store 10.0  games
  * OS X v10.6+ for Mac games
  * Windows 7+ for Win games
  * Modern browsers and IE 9+ for web games

Running Tests
--------------------

Select the test you want from Xcode Scheme chooser.

* Cocos Console

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

* For OS X / iOS

```
$ cd cocos2d-x/build
$ open cocos2d_tests.xcodeproj
```

* For Linux

```
$ cd cocos2d-x/build
$ ./install-deps-linux.sh
$ cmake ..
$ make
```

Run Samples

```
$ bin/cpp-empty-test/cpp-empty-test
or
$ bin/lua-empty-test/lua-empty-test
```

      You may meet building errors when building libGLFW.so. It is because libGL.so directs to an error target,
      you should make it to direct to a correct one. `install-deps-linux.sh` only has to be run once.

* For Windows

Open the `cocos2d-x/build/cocos2d-win32.sln`

* For Windows 8.1 Universal Apps (Phone and Store)

Open the `cocos2d-x/build/cocos2d-win8.1-universal.sln`

* For Windows 10.0 Universal Windows Platform (UWP) Apps (Phone and Store)

Open the `cocos2d-x/build/cocos2d-win10.sln`

* For Android

```
$ cd cocos2d-x/build
$ python ./android-build.py cpp-empty-test -p 10
$ adb install ../tests/cpp-empty-test/proj.android/bin/CppEmptyTest-debug.apk
```

Then click item on Android device to run tests. Available value of `-p` is the API level, cocos2d-x supports from level 10.


Contributing to the Project
--------------------------------

Did you find a bug? Do you have feature request? Do you want to merge a feature?

  * [contributing to cocos2d-x][8]


Contact us
----------

   * Forum: [http://forum.cocos2d-x.org][9]
   * Twitter: [http://www.twitter.com/cocos2dx][10]
   * Weibo: [http://t.sina.com.cn/cocos2dx][11]
   * IRC: [https://webchat.freenode.net/][12] (#cocos2d and #cocos2d-x channels)

[1]: http://www.cocos2d-x.org "cocos2d-x"
[2]: http://www.cocos2d-iphone.org "cocos2d for iPhone"
[3]: http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Download
[4]: http://www.cocos2d-x.org/download/version#Cocos2d-x
[5]: http://www.box2d.org "Box2D"
[6]: http://www.chipmunk-physics.net "Chipmunk2D"
[7]: http://esotericsoftware.com/ "http://esotericsoftware.com/"
[8]: https://github.com/cocos2d/cocos2d-x/blob/v3/docs/CONTRIBUTE.md
[9]: http://forum.cocos2d-x.org "http://forum.cocos2d-x.org"
[10]: http://www.twitter.com/cocos2dx "http://www.twitter.com/cocos2dx"
[11]: http://t.sina.com.cn/cocos2dx "http://t.sina.com.cn/cocos2dx"
[12]: https://webchat.freenode.net/ "https://webchat.freenode.net/"
