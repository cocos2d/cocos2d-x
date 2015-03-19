# cocos2d-x v3.5 Release Notes #
<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Misc Information](#misc-information)
- [Requirements](#requirements)
  - [Runtime Requirements](#runtime-requirements)
  - [Compiler Requirements](#compiler-requirements)
  - [How to run tests](#how-to-run-tests)
    - [Mac OSX & iOS](#mac-osx-&-ios)
    - [Android](#android)
    - [Windows](#windows)
    - [Linux](#linux)
  - [How to start a new game](#how-to-start-a-new-game)
- [v3.5](#v35)
- [v3.5rc0](#v35rc0)
  - [Highlights of v3.5rc0](#highlights-of-v35rc0)
  - [Features in detail](#features-in-detail)
    - [More 3D particle features of (PU) supported](#more-3d-particle-features-of-pu-supported)
- [v3.5beta0](#v35beta0)
  - [Highlights of v3.5beta0](#highlights-of-v35beta0)
  - [Features in detail](#features-in-detail-1)
    - [3D Particles](#3d-particles)
      - [Supported PU features](#supported-pu-features)
      - [Particle usage](#particle-usage)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)
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
# v3.5
There are only some minor changes and bug fixes in this verison.

* EditBox: Color4B font color is supported
* Fix memory leak in AutoReleasePool
* Fix FileUtils:getWritablePath() return wrong path on Mac&Windows

# v3.5rc0
## Highlights of v3.5rc0
* More features of Particle(PU) is supported
* Disable reverse of MoveTo
* CsLoader: add callback when loading a CSB file
* Fix transparent Billboard and Sprite3D rendering error
* Fix Motionstreak does not work with MoveTo and MoveBy
* More bugs fixed

## Features in detail
###More 3D particle features of (PU) supported
* Observer: On Count Observer, On Emission Observer, On Expire Observer, On Position observer, On Clear Observer, On Time Observer, On Quota Observer, On Velocity Observer, On Collision Observer, On Event Flag Observer, On Random Observer.

* Event Handler: Do Enable Component Event Handler, Do Expire Event Handler, Do Placement Particle Event Handler, Do Stop System Event Handler, Do Affector Event Handler, Do Freeze Event Handler, Do Scale Event Handler.

* Behavior: Slave Behavior

Observer and Event Handler allow you to listen to the particle system and trigger some events. The Event handler can do something when the event happens. For example, there is a observer on the particle system, and it listens to the particle number when the number is greater than 100, it tirggers an event to stop the particle system. This allows you to create more complex particles. For more details, please refer to the Particle Universe User's Guide.

# v3.5beta0

## Highlights of v3.5beta0
## Features in detail

### 3D Particles

#### Supported PU features

* Render: Billboard Renderer, Box Renderer, Sphere Renderer, Entity Renderer, Ribbon Trail Renderer.

* Emitter: Point Emitter, Box Emitter, Sphere Surface Emitter, Line Emitter, Circle Emitter, Position Emitter, Slave Emitter.

* Affector: Gravity Affector, Linear Force Affector, Scale Affector, Sine Force Affector, Color Affector, Randomiser, Line Affector, Align Affector, Jet Affector, Vortex Affector, Geometry Rotator, Texture Rotator, Texture Animator, Particle Follower, Sphere Collider, Plane Collider, box Collider, Path Follower, Flock Centering Affector, Velocity Matching Affector.

#### Particle usage

It allows to import particles from Particle Universe (http://www.fxpression.com). The usage of particles is as follow,

Option 1, create 3D particle with particle (.pu) file and material file

```c++
auto rootps = PUParticleSystem3D::create("lineStreak.pu", "pu_mediapack_01.material");
addChild(rootps);
rootps->startParticleSystem();
```

Option 2, you can also create 3d particle with particle (.pu) file only, it will load all the material files in the material path
```c++
auto rootps = PUParticleSystem3D::create("advancedLodSystem.pu");
addChild(rootps);
rootps->startParticleSystem();
```

For more information, please refer to `cpp-tests/Particle3DTest`
