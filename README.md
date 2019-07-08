<img src="http://www.cocos2d-x.org/attachments/801/cocos2dx_portrait.png" width=200>


cocos2d-x
=========

|Win32|Others|
| ----|------|
[![Build status](https://ci.appveyor.com/api/projects/status/nlgirox464j6ldg5/branch/v3?svg=true)](https://ci.appveyor.com/project/minggo/cocos2d-x/branch/v3)|[![Build Status](https://travis-ci.org/cocos2d/cocos2d-x.svg?branch=v3)](https://travis-ci.org/cocos2d/cocos2d-x)


[cocos2d-x][1] is a multi-platform framework for building 2d games, interactive books, demos and other graphical applications.
It is based on [cocos2d-iphone][2], but instead of using Objective-C, it uses C++.
It works on iOS, Android, OS X, Windows and Linux.

**Cocos2d-x Framework Architecture**:

![](docs/framework_architecture_v4.png "")

cocos2d-x is:

  * Fast
  * Free
  * Easy to use
  * Community supported

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

Documentations and samples
-------------
* [All Docs in a single place!](http://cocos2d-x.org/docs/)
* [Online API Reference](http://cocos2d-x.org/docs/api-ref/index.html) _Note that Cocos2d-x and Cocos Creator have different API set_
* [Programmers Guide](http://cocos2d-x.org/docs/programmers-guide/2/index.html)
* [Latest Release Note](https://github.com/cocos2d/cocos2d-x/blob/v3/docs/RELEASE_NOTES.md)
* [Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

Main features
-------------
   * Scene management (workflow)
   * Transitions between scenes
   * Sprites and Sprite Sheets
   * Effects: Lens, Ripple, Waves, Liquid, etc.
   * Actions (behaviours):
     * Transformation Actions: Move, Rotate, Scale, Fade, Tint, etc.
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
   * Sound Engine support
   * Integrated Slow motion/Fast forward
   * Fast and compressed textures: PVR compressed and uncompressed textures, ETC1 compressed textures, and more
   * Resolution Independent
   * Language: C++, with Lua and JavaScript bindings
   * Open Source Commercial Friendly(MIT): Compatible with open and closed source projects
   * OpenGL ES 2.0 (mobile) / OpenGL 2.1 (desktop) / metal(macos and iOS) based

Build Requirements
------------------

* Mac OS X 10.7+, Xcode 8+
* or Ubuntu 14.04+, CMake 3.1+
* or Windows 7+, VS 2015
* Python 2.7.5+(NOT Python 3)
* NDK r16+ is required to build Android games
* Android Studio 3.0.0+ to build Android games(tested with 3.0.0)
* JRE or JDK 1.6+ is required for web publishing

Runtime Requirements
--------------------
  * iOS 8.0+ for iPhone / iPad games
  * Android 3.0.0+ for Android
  * OS X v10.9+ for Mac games
  * Windows 7+ for Win games

Environment Setup
--------------------

Should set up environment before starting a new game or running tests

```
$ cd cocos2d-x
$ ./setup.py
$ source FILE_TO_SAVE_SYSTEM_VARIABLE

```

Should invoke this script if using linux system

```
$ cd cocos2d-x
$ ./install-linux-deps.sh
```

Running Tests
--------------------

```
$ cd cocos2d-x
$ mkdir build
$ cd build
$ cocos run --proj-dir .. -p [mac|windows|android|linux|ios]
```

How to start a new game
-----------------------

    $ cd cocos2d-x
    $ ./setup.py
    $ source FILE_TO_SAVE_SYSTEM_VARIABLE
    $ cocos new MyGame -p com.your_company.mygame -l cpp -d NEW_PROJECTS_DIR
    $ cd NEW_PROJECTS_DIR/MyGame
    $ mkdir build
    $ cd build
    $ cocos run --proj-dir .. -p [mac|windows|android|linux|ios]

You can also create a Lua project with `-l lua`.

Using IDE
----------------------------

If need to debug program, then it is more convinent to use IDE to run and debug it. All platforms other than Android can use CMake to generate corresponding project file. Can refer to [Detail CMake Guide](cmake/README.md) for detail information.

For Android, the Android Studio project file lies in `PROJECT_DIR/proj.android`. Can just use Android Studio to import the exsting project file.

Learning Resources
--------------------------------

* [Programmers Guide](http://cocos2d-x.org/docs/programmers-guide/2/index.html)
* [Sonar Systems Videos](https://www.youtube.com/user/sonarsystemslimited/search?query=cocos2d-x)
* [Android Fundamentals](https://developer.android.com/guide/components/fundamentals.html)
* [Make School Tutorials](https://www.makeschool.com/tutorials/)
* [Games From Scratch](http://www.gamefromscratch.com/page/Cocos2d-x-CPP-Game-Programming-Tutorial-Series.aspx)
* [Cocos2d sample games](https://github.com/cocos2d/cocos2d-x-samples)

Spreading the word!
--------------------------------
You can help us spread the word about cocos2d-x! We would surely appreciate it!

* Talk about us on Facebook! Our [Facebook Page](https://www.facebook.com/cocos2dx/)
* Tweet, Tweet! Our [Twitter](https://twitter.com/cocos2dx)
* Read our [Blog](http://blog.cocos2d-x.org/) and promote it on your social media.
* Become a [Regional Coordinator](http://discuss.cocos2d-x.org/t/we-need-regional-coordinators/24104)

See what we are planning!
--------------------------------
You can see exactly what we are planning to do with the Cocos family of products.

* [Cocos2d-x roadmap](https://trello.com/b/Np6obnuE/cocos2d-x-roadmap)

Where to get help
--------------------------------

* [English Forums](http://discuss.cocos2d-x.org)
* [中文社区](http://forum.cocos.com/c/cocos2d-x)
* [Bug Tracker](https://github.com/cocos2d/cocos2d-x/issues)
* [API Reference](http://cocos2d-x.org/docs/api-ref/index.html).
* [Latest Release Note](https://github.com/cocos2d/cocos2d-x/blob/v3/docs/RELEASE_NOTES.md)
* [Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)
* IRC. We are in [Freenode](https://webchat.freenode.net/) in the _#cocos2d_ channel
* `cpp-tests` project. This project is our basis for testing. Use this project to
learn how we implement the functionality of the engine. This project is located in
__cocos2d-x_root/build.__

Contributing to the Project
--------------------------------

Cocos2d-x is licensed under the [MIT License](https://opensource.org/licenses/MIT). We welcome participation!

Did you find a bug? Do you have feature request? Do you want to merge a feature?

  * [contributing to cocos2d-x][8]

Contact us
----------

   * Forum: [http://discuss.cocos2d-x.org][9]
   * Twitter: [http://www.twitter.com/cocos2dx][10]
   * Weibo: [http://t.sina.com.cn/cocos2dx][11]

[1]: http://www.cocos2d-x.org "cocos2d-x"
[2]: http://www.cocos2d-iphone.org "cocos2d for iPhone"
[3]: http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Download
[4]: http://www.cocos2d-x.org/download/version#Cocos2d-x
[5]: http://www.box2d.org "Box2D"
[6]: http://www.chipmunk-physics.net "Chipmunk2D"
[7]: http://esotericsoftware.com/ "http://esotericsoftware.com/"
[8]: https://github.com/cocos2d/cocos2d-x/blob/v3/CONTRIBUTING.md
[9]: http://discuss.cocos2d-x.org "http://discuss.cocos2d-x.org"
[10]: http://www.twitter.com/cocos2dx "http://www.twitter.com/cocos2dx"
[11]: http://t.sina.com.cn/cocos2dx "http://t.sina.com.cn/cocos2dx"
