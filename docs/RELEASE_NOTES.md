# cocos2d-x v4.0 Release Notes #
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
- [v4.0alpha1](#v40alpha1)
  - [Notes](#notes)
  - [Highlights](#highlights)
  - [Details](#details)
    - [Windows image components(WIC)](#windows-image-componentswic)
    - [Remove extension in cocos2d-x repo](#remove-extension-in-cocos2d-x-repo)
- [v4.0alpha0](#v40alpha0)
  - [Notes](#notes-1)
  - [Highlights](#highlights-1)
  - [Details](#details-1)
    - [Rendering: Draw call migrated to VertexData](#rendering-draw-call-migrated-to-vertexdata)
    - [Merge JSB](#merge-jsb)
    - [Deprecated function version](#deprecated-function-version)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v4-develop/CHANGELOG)
* v4.0 Release Notes can be found here: [v4.0 Release Notes](https://github.com/cocos2d/cocos2d-x/blob/v4-develop/docs/RELEASE_NOTES.md)

# Requirements

## Runtime Requirements

* Android 2.3 or newer
* iOS 5.0 or newer
* OS X 10.7 or newer
* Windows 7 or newer
* Windows Phone 8.1 or newer
* Linux Ubuntu 14.04 or newer

## Compiler Requirements

* Xcode 5.1 or newer for iOS or Mac
* gcc 4.9 or newer for Linux
* ndk-r10c for Android
* Visual Studio 2013  or newer for Windows (win32)
* Visual Studio 2013  or newer for Windows Phone 8.1

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

#v4.0alpha1
##Notes
* Extensions `Cocostudio, Cocosbuilder and Spine` have been removed from cocos2d-x repo. It will be provided as a package in `Cocos Package Manager`.
* MoveTo::reverse() function has been disabled.

##Highlights
* Using Window image components(WIC) to replace png, jpg and tiff lib on windows universal.
* Upgrade 3rd libs: libcurl, chipmunk, openssl, png and freetype.
* Fix memory leak in AutoReleasePool.

##Details
###Windows image components(WIC)
Libpng, libjpeg and libtiff has beened used in cocos2d-x for read various image files. These functions has been provided in Windows Universal by WIC. By using this functions, we can remove the dependence on libpng,libjpeg and libtiff, which make game smaller. The interface of CCImages and CCTextures is kept the same as before.

###Remove extension in cocos2d-x repo
We have Extensions such as `Cocostudio`, `Cocosbuilder` and `Spine` in cocos2d-x repo, which make the time spent for building game project much more slowly, and it is useless if we do not use it in our game.

In v3.x version, we have provided `Cocos package manager`, which is a framework for extensions based on cocos2d-x. It will make game engine more modularized. We are going to add these extension by it. 

We have start the first step, removing the extensions source code. The next step will be adding them as packages. The usage will be very straightforward, taken `GAF` lib as an example:

* create a project: `cocos new -l cpp`
* download and install: `cocos package install gaf`
* enter the game directory
* add extensions: `cocos framework add gaf`

# v4.0alpha0
##Notes
* Visual studio 2012 has been removed, Visual studio 2013 solution file is used instead, it provide better c++11 features.
* Windows Phone 8.0 support has been removed.
* Functions and classes which is deprecated in v2.x has been removed.

##Highlights
* Merge JSB
* Rendering: Draw call migrated to VertexData
* Deprecated function version
* Add Romanian language support
* Other bugs fix

##Details
###Rendering: Draw call migrated to VertexData
Rendering is improving, VertexBuffer, IndexBuffer and VertexData has been enhanced to support more primitive types, and it will support draw directly.

Taking TextureAtlas as example, VertexData could be used as this:

* create a VertexBuffer and an optional IndexBuffer:
	
	```
	_vbAtlas = VertexBuffer::create(sizeof(V3F_C4B_T2F), 4 * capacity, VertexBuffer::ArrayType::All, VertexBuffer::ArrayMode::Dynamic);
	_ibAtlas = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, 6 * capacity, IndexBuffer::ArrayType::All);
	```
* create a VertexData, specify vertexStreams and set indexBuffer

	```
	_vdAtlas->addStream(_vbAtlas, VertexAttribute(offsetof(V3F_C4B_T2F, vertices),  GLProgram::VERTEX_ATTRIB_POSITION,  DataType::Float, 3));
	_vdAtlas->addStream(_vbAtlas, VertexAttribute(offsetof(V3F_C4B_T2F, colors),    GLProgram::VERTEX_ATTRIB_COLOR,     DataType::UByte, 4, true));
	_vdAtlas->addStream(_vbAtlas, VertexAttribute(offsetof(V3F_C4B_T2F, texCoords), GLProgram::VERTEX_ATTRIB_TEX_COORD, DataType::Float, 2));
	_vdAtlas->setIndexBuffer(_ibAtlas);
	```
* when drawing, draw all or a part of data

	```
	_vdAtlas->draw(start, numberOfQuads);
	```

### Merge JSB
JSBindings and test cases for JSB have been merged into cocos2d-x repo, most functions work well, in future versions, there could be some bugs fix and improvements.

###Deprecated function version
There are many deprecated functions in cocos2d-x, since v4.x, a version string will be contained in deprecated function.

Deprecated function will be deleted two versions later after it is deprecated, eg, functions and classes deprecated in v2.x will be removed in version 4.x.