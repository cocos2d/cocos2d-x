<img src="http://www.cocos2d-x.org/attachments/801/cocos2dx_portrait.png" width=200>


cocos2d-x
=========

[![Build Status](https://travis-ci.org/cocos2d/cocos2d-x.png?branch=master)](https://travis-ci.org/cocos2d/cocos2d-x)

[cocos2d-x][1] is a multi-platform framework for building 2d games, interactive books, demos and other graphical applications.
It is based on [cocos2d-iphone][2], but instead of using Objective-C, it uses C++.
It works on iOS, Android, Windows Phone, OS X, Windows and Linux.

cocos2d-x is:

  * Fast
  * Free
  * Easy to use
  * Community Supported



How to start a new game
-----------------------

1. Download the code from [cocos2d download site][4]
2. Run `setup.py`
3. Run the `cocos` script

Example:

    $ cd cocos2d-x
    $ ./setup.py
    $ source FILE_TO_SAVE_SYSTEM_VARIABLE
    $ cocos new MyGame -p com.your_company.mygame -l cpp -d /home
    $ cd /home/MyGame

### Build and run new project for android ###

    $ cocos run -p android -j 4

### Build and run new project for iOS ###

    $ cocos run -p ios
    
### Build and run new project for OSX ###

    $ cocos run -p mac

### Build and run new project for linux ###

if you never run cocos2d-x on linux, you need to install all dependences by the
script in **cocos2d/build/install-deps-linux.sh**

    $ cd cocos2d-x/build
    $ ./install-deps-linux.sh

Then

    $ cd /home/MyGame
    $ cocos run -p linux
    
Run

    $ bin/MyGame

### Build and run new project for win32 ###

    $ cocos run -p win32


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
   * Resolution Independence
   * Language: C++, with Lua and JavaScript bindings
   * Open Source Commercial Friendly: Compatible with open and closed source projects
   * OpenGL ES 2.0 (mobile) / OpenGL 2.1 (desktop) based

Build Requirements
------------------

* Mac OS X 10.7+, Xcode 4.6+
* or Ubuntu 12.10+, CMake 2.6+
* or Windows 7+, VS 2012+
* Python 2.7.5


Runtime Requirements
--------------------
  * iOS 5.0+ for iPhone / iPad games
  * Android 2.3+ for Android games
  * Windows Phone 8+ for Windows Phone games
  * OS X v10.6+ for Mac games
  * Windows 7+ for Win games


Running Tests
--------------------

Select the test you want from Xcode Scheme chooser.

* For OS X / iOS

```
$ cd cocos2d-x/build
$ open cocos_tests.xcodeproj
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

Open the `cocos2d-x/build/cocos2d-win32.vc2012.sln`

* For Android

```
$ cd cocos2d-x/build
$ python ./android-build.py cpp-empty-test -p 10
$ adb install ../tests/cpp-empty-tst/proj.android/bin/CppEmptyTest-debug.apk
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
[8]: http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Contribution
[9]: http://forum.cocos2d-x.org "http://forum.cocos2d-x.org"
[10]: http://www.twitter.com/cocos2dx "http://www.twitter.com/cocos2dx"
[11]: http://t.sina.com.cn/cocos2dx "http://t.sina.com.cn/cocos2dx"
[12]: https://webchat.freenode.net/ "https://webchat.freenode.net/"
