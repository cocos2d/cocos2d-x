# cocos2d-x v3.4 Release Notes #
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
- [v3.4rc1](#v34rc1)
  - [Highlights of v3.4rc1](#highlights-of-v34rc1)
  - [Features in detail](#features-in-detail)
    - [3D rendering support for 2D objects](#3d-rendering-support-for-2d-objects)
    - [Culling is now an options by CC_USE_CULLING macro](#culling-is-now-an-options-by-cc_use_culling-macro)
  - [Bugs fixed in v3.4rc1](#bugs-fixed-in-v34rc1)
- [v3.4rc0](#v34rc0)
  - [Bugs fixed in v3.4rc0](#bugs-fixed-in-v34rc0)
- [v3.4beta0](#v34beta0)
  - [Highlights of v3.4beta0](#highlights-of-v34beta0)
  - [Features in detail](#features-in-detail-1)
    - [Create Sprite3D asynchronously](#create-sprite3d-asynchronously)
    - [Frustum culling](#frustum-culling)
    - [Use less resources to create  ui::CheckBox and ui::Slider](#use-less-resources-to-create--uicheckbox-and-uislider)
    - [Custom Allocators](#custom-allocators)
      - [Default Allocator](#default-allocator)
      - [General Allocator](#general-allocator)
      - [Fixed Block Allocator](#fixed-block-allocator)
      - [Pool Allocator](#pool-allocator)
    - [Implementing Custom Allocators for Objects](#implementing-custom-allocators-for-objects)
    - [Console (allocator command, tags, counts etc)](#console-allocator-command-tags-counts-etc)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Misc Information

* Full Changelog: https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.4rc0/CHANGELOG
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

# v3.4rc1

##Highlights of v3.4rc1
* C++: added CC_USE_CULLING macro to control if enable auto culling or not
* FileUtils::fullPathForFilename will return empty string when file can not be found
* VertexBuffer&IndexBuffer: allow setting usage(GL_STATIC_DRAW or GL_DYNAMIC_DRAW) in create method
* Renderer: 3D rendering support for 2d objects

##Features in detail
###3D rendering support for 2D objects
This feature enables Sprite, Label, Particle to be rendered in 3D space by adding them as children of Sprite3D or Billboard. You can achieve effects like blob shadow, 3D particle, Visual damage number popups
```c++
auto billboard = Billboard::create();
auto label = Label::create();
label->setString("+100");
billboard->addChild(label);
```
###Culling is now an options by CC_USE_CULLING macro
Culling is an important features in cocos2d-x v3.x, but some developer may not want to use culling when all of the scene exist in one screen. A macro `CC_USE_CULLING` in `CCConfig.h` can be used to enable or disable culling.

##Bugs fixed in v3.4rc1
* DrawNode: fix random crash because of init opengl buffer wrongly
* DrawNode: drawPoints() can not set ponit size
* EventDispatcher: crash if adding/removing event listeners and dispatching event in event callback function
* GLProgramState: may cause GL_INVALID_VALUE error at start up on Android
* LUA: 0x80000000 can not be converted by lua_tonumber correctly on some devices
* PhysicsBody: can't get correct position in the same frame of adding PhysicsBody to PhysicsWorld
* UI: fix crash when navigation controller is null

# v3.4rc0
##Bugs fixed in v3.4rc0
* FileUtils::GetData() can not get data on windows
* FileUtils::GetData() memory leaks when file size is 0 on windows
* Crash if GLProgram log compile or link error info on windows
* Assert error exist because of outdated uniforms and attributes in GLProgramState when app come to foreground on android
* GL_INVALID_OPERATION error because VAO and VBO is not reset when app come to foreground on android
* Update Luajit to v2.0.3, it fix some crash problems on windows
* Update libcurl to new version v7.39.0
* More bugs fixed

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

Frustum culling means only the stuff that is inside the frustum is sent to the graphics hardware. To find out more information, please visit [Wikipedia](http://en.wikipedia.org/wiki/Frustum). It can potentially improve the performance of the application since only the vertices that are part of the visible part of the 3D world are kept on the graphics card memory.

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

### Custom Allocators

in ccConfig.h you can control the custom allocator system with the following defines.

```c++
#define CC_ENABLE_ALLOCATOR 1
#define CC_ENABLE_ALLOCATOR_DIAGNOSTICS CC_ENABLE_ALLOCATOR
#define CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE 0

#define CC_ALLOCATOR_GLOBAL cocos2d::allocator::AllocatorStrategyDefault
#define CC_ALLOCATOR_GLOBAL_NEW_DELETE cocos2d::allocator::AllocatorStrategyGlobalSmallBlock
```

__CC_ENABLE_ALLOCATOR__ turns everything on or off. When set to 0, everything should still build, but all custom allocator code is disabled or removed. This is handled mainly through macros, but if you implement new allocator strategies, you should be aware of, and respect this preprocessor directive.

__CC_ENABLE_ALLOCATOR_DIAGNOSTICS__ defaults to the same value as __CC_ENABLE_ALLOCATOR__, but setting this to 0 will disable allocator diagnostics via the control panel. Diagnostics have significant overhead, so you definitely want to disable them for production builds.

__CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE__ enables overriding of the global __new__ and __delete__ operators. The allocator strategy used can be selected by setting the __CC_ALLOCATOR_GLOBAL_NEW_DELETE__ define.

__CC_ALLOCATOR_GLOBAL__ defines the allocator strategy to use for global allocations. All memory needed by other allocators will use this global allocator, as well as the macros __CC_MALLOC__, __CC_FREE__ etc.

Third party libraries that use malloc/free will continue to use the original malloc/free so their memory usage will not be tracked.

Calls to new/delete from shared libraries should work ok provided the library is loaded after the allocator has initialized, which should be the case, unless you load a shared library from a static variable initialization.

#### Default Allocator

The default allocator wraps malloc and free and provides an allocator interface that anyone can use to allocate blocks of memory. Tracking is not currently enabled here, but can be added in the future.

#### General Allocator

The general allocator provides a series of fixed sized allocators from the smallest allocation size of 4 bytes up to some threshold which currently defaults to 8 Kbytes. Anything larger than this threshold will fallback to the default allocator. See fixed allocators for more details.

#### Fixed Block Allocator

Fixed block allocators provide a memory pool of blocks of fixed size. They are extremely fast since no searching for best fit is required, they can simply pop the first block off a list and return that. Similarly, freeing memory is also extremely fast since they just push the block on the front of the list. Memory is not actually freed, it is kept allocated and track on a free list. It will be possible to reduce the allocated memory by freeing up unused pages of memory from the list.

#### Pool Allocator

Implements a custom fixed block allocator for a specific type. You can override local new/delete for types that are classes or structs using __CC_USE_ALLOCATOR_POOL(pool)__. Additionally, these allocators are configurable in terms of the initial size.

### Implementing Custom Allocators for Objects
Simply add a static instance of the pool allocator to your class, and use the __CC_USE_ALLOCATOR_POOL__ macro to implement operators __new__ and __delete__ for your class.

```c++
    class SomeClass
    {
    public:

        cocos2d::allocator::AllocatorStrategyPool<SomeClass> _allocator;
        CC_USE_ALLOCATOR_POOL(SomeClass, _allocator);
    };
```

### Console (allocator command, tags, counts etc)

You can connect to the running app using the console. I.e. __telnet localhost 5678__ and issue the __allocator__ command to dump out all allocator diagnostic information. One of the useful pieces of information is the highest count for pool allocators. You can plug this value back into the initial size for the allocator to preallocate this number of objects when starting, improving startup speed significantly.
