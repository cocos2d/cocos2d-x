<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x v3.8 Release Notes](#cocos2d-x-v38-release-notes)
- [Misc Information](#misc-information)
- [Requirements](#requirements)
  - [Runtime Requirements](#runtime-requirements)
  - [Compiler Requirements](#compiler-requirements)
  - [How to run tests](#how-to-run-tests)
    - [Cocos Console](#cocos-console)
    - [Mac OSX & iOS](#mac-osx-&-ios)
    - [Android](#android)
    - [Windows](#windows)
    - [Linux](#linux)
  - [How to start a new game](#how-to-start-a-new-game)
- [v3.8](#v38)
  - [Highlights and API changes of v3.8](#highlights-and-api-changes-of-v38)
  - [Download](#download)
  - [The main features in detail:](#the-main-features-in-detail)
    - [3D Module](#3d-module)
    - [UI System](#ui-system)
    - [AudioEngine](#audioengine)
    - [FileUtils](#fileutils)
    - [Others](#others)
  - [Other changes](#other-changes)
  - [New APIs](#new-apis)
- [The Next Step](#the-next-step)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x v3.8 Release Notes #

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# Requirements

## Runtime Requirements

* Android 2.3 or newer
* iOS 5.0 or newer
* OS X 10.7 or newer
* Windows 7 or newer
* Windows Phone 8.1
* Windows 10 UWP
* Linux Ubuntu 14.04 or newer
* Mordern browsers and IE 9+ (On mobile platforms, only iOS and Android 5 activated WebGL support)

## Compiler Requirements

* Xcode 5.1 or newer for iOS or Mac
* gcc 4.9 or newer for Linux
* ndk-r10c for Android
* Visual Studio 2013 or newer for Windows (win32)
* Visual Studio 2013 update4 or newer for Windows 8.1 universal Apps
* Visual Studio 2015 RC or newer and Windows 10.0 (build 10074 or higher) for Windows 10.0 UWP Apps

## How to run tests

### Cocos Console

You can use [Cocos Console](www.cocos2d-x.org/wiki/Cocos2d-console) command line tool to run the test cases on almost all supported platforms.

In console application:
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

For example, if you want to run cpp test in release mode on Android, you can use the following command:

```
cocos run -p android -m release
```

### Mac OSX & iOS

* Enter `cocos2d-x/build` folder, open `cocos2d_test.xcodeproj`
* Select `cpp-tests`, `lua-tests`, `js-tests` for `iOS` or `OS X` target in scheme toolbar
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

* For win32 project, enter `cocos2d-x/build`, and open `cocos2d-win32.sln`
* For win 8.1 project, enter `cocos2d-x/build`, and open `cocos2d-win8.1-universal.sln`
* For win 10 project, enter `cocos2d-x/build`, and open `cocos2d-win10.sln`
* Select running target
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

Use Cocos Console to create a new game:

```
cocos new -l cpp|js|lua MyNewGame
```

# v3.8

## Highlights and API changes of v3.8

As promised, Cocos2d-x v3.8 have greatly improved the stability and API friendliness. On one side, we continue to improve 3D capacity by providing 3D physics collider, skybox background brush and key frame event callback in Animate3D. On another side, we have refined several core modules, including UI system, AudioEngine, FileUtils, Bindings Generator, etc.

Here is some highlighted improvments and API changes:

1. 3D Module
    - Added 3D physics collider
    - Supported setting camera background brushes with color/depth/skybox 
    - Added key frame event Callback in Animate3D
    - Added light map support in Terrain
2. UI System
    - Reimplemented and enhanced EditBox on Android
    - Added ScrollViewBar for displaying a scroll bar at the side of ScrollView (JSB/Lua ready)
    - Added RadioButton widget (JSB/Lua ready)
    - Added HANYI FullType font support
3. AudioEngine
    - AudioEngine supported audio preloading
    - Bound new AudioEngine in JSB
4. FileUtils
    - Added a set of file writing APIs: writeStringToFile, writeDataToFile, writeValueMapToFile, writeValueVectorToFile
5. Others
    - Improved Bindings Generator tool
    - Merged JSB test project into cocos2d test project
    - framework: Support generate prebuilt libs of engine with debug mode
    - console: Supported new portrait projects from templates

## Download

[Cocos2d-x v3.8](http://www.cocos2d-x.org/filedown/cocos2d-x-3.8.zip) including : C++, Lua & JS

## The main features in detail:

### 3D Module

1. 3D physics collider

    3D physics collider is a new type of physics object. It can be used as both trigger and collider. 

    Trigger is a region defined by physics shapes and  can get callback when other physics objects enter or leave. Its usage is described in the following code:
    
    ```cpp
    //create a collider using colliderDes
    Physics3DColliderDes colliderDes;
    colliderDes.shape = Physics3DShape::createSphere(10.0f);
    colliderDes.isTrigger = true;
    auto collider = Physics3DCollider::create(&colliderDes);
    auto component = Physics3DComponent::create(collider);
    auto node = Node::create();
    addChild(node);
    node->addComponent(component);

    collider->onTriggerEnter = [=](Physics3DObject *otherObject){
      //some body entering
    };
    collider->onTriggerExit = [=](Physics3DObject *otherObject){
      //some one leaving
    }; 
    ```

    Collider is similar to rigid body, it can give force to the rigid body that collides with it. However, it is static and has better performance than rigid body. It is proper to represent a static scene or objects using collider and dynamic part using rigid body. You can set colliderDes.isTrigger to false when you want to make it collider.

2. Camera background brushes

    Different with previous versions, in v3.8, developers can choose to erase the camera’s background with 4 types of brush: none, color, depth, skybox. None brush means do nothing; Color brush erases background using given color and depth; depth brush erases background using given depth; skybox brush erases background using given skybox with 6 texture faces. The default brush is depth brush. The usage of brushes is showing below:

    ```cpp
    // Using none brush
    _camera->setBackgroundBrush(CameraBackgroundBrush::createNoneBrush());
    // Using depth brush, clear depth with 1.0
    _camera->setBackgroundBrush(CameraBackgroundBrush::createDepthBrush(1.f));
    // Using color brush, clear color is (1,0,0,1), depth is 1
    _camera->setBackgroundBrush(CameraBackgroundBrush::createColorBrush(Color4F(1.f, 0.f, 0.f, 1.f), 1.f));
    // SkyBox brush
    _camera->setBackgroundBrush(CameraBackgroundBrush::createSkyboxBrush("Sprite3DTest/skybox/left.jpg", "Sprite3DTest/skybox/right.jpg","Sprite3DTest/skybox/top.jpg", "Sprite3DTest/skybox/bottom.jpg","Sprite3DTest/skybox/front.jpg", "Sprite3DTest/skybox/back.jpg"));
    ```

3. Animate3D key frame event callback

    Similar to 2d AnimationFrame callback, frame event callback is supported in Animated3D now. It allows developer to set a callback to be invoked when specific frame is played. Sample code:

    ```cpp
    auto animation = Animation3D::create(“XX.c3b”);
    auto animate = Animate3D::create(animation);
    ValueMap valuemap0;//you can add some user data here, it can be used in the frame event callback
    //add a callback when frame 275 is played
    animate->setKeyFrameUserInfo(275, valuemap0);
            
    auto listener = EventListenerCustom::create(Animate3DDisplayedNotification, [&](EventCustom* event)
    {
        auto info = (Animate3D::Animate3DDisplayedEventInfo*)event->getUserData();
        
        //frame 275 is played, you can add some code here
        cocos2d::log(“frame %d”, info->frame);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, -1);
    ```

4. Light map support in Terrain

    Terrain with light map is supported in v3.8, which means you can add a light map texture baked from other tools to the terrain. The light map texture contains light info, so that the terrain seems to be lighted with several lights. Terrain with light map can be created like this,

    ```cpp
    //create a normal terrain as before
    Terrain::DetailMap r(“TerrainTest/dirt.jpg”),g(“TerrainTest/Grass2.jpg”),b(“TerrainTest/road.jpg”),a(“TerrainTest/GreenSkin.jpg”);
    Terrain::TerrainData data(“TerrainTest/heightmap16.jpg”,”TerrainTest/alphamap.png”,r,g,b,a);
    _terrain = Terrain::create(data,Terrain::CrackFixedType::SKIRT);
    _terrain->setLODDistance(3.2f,6.4f,9.6f);
    _terrain->setMaxDetailMapAmount(4);
    _terrain->setDrawWire(false);
    //set light map for the terrain
    _terrain->setLightMap(“TerrainTest/Lightmap.png”);
    ```

### UI System

1. Reimplemented EditBox

    The usage of EditBox is the same as before, but we have reimplemented it for Android platform. The use experience is highly improved, important improvements are: 

    - Display cursor in EditBox
    - Support copy, cut, paste and select actions in EditBox
    - Support multi-line input, you should set InputMode to `ANY` to enable multi-line input
    - EditBox won't be masked by the keyboard UI anymore

2. ScrollViewBar
    
    In the previous versions, the ScrollView doesn't have any visual notification for the current location in view. In v3.8, we have added a scroll bar attached to the ScrollView. You could tweak the the opacity, color, width and the duration for auto hiding the scroll bar. Speical thanks to @neokim.

    Usage:

    ```cpp
    ui::ScrollView* scrollView = ui::ScrollView::create();
    scrollView->setScrollBarWidth(4);
    scrollView->setScrollBarPositionFromCorner(Vec2(2, 2));
    scrollView->setScrollBarColor(Color3B::WHITE);
    this->addChild(scrollView);
    ```

3. RadioButton widget

    RadioButton is a specific type of two-states button that is similar to CheckBox.

    Additionally, it can be used together with RadioButtonGroup to interact with other radio buttons.

    There is only one RadioButton in checked state at the same time within a RadioButtonGroup. Special thanks to @neokim who have contributed the implementation of this new widget.

    Usage: 

    ```cpp
    //create a RadioButtonGroup
    auto radioButtonGroup = RadioButtonGroup::create();
    this->addChild(radioButtonGroup);

    //create a RadioButton
    RadioButton* radioButton1 = RadioButton::create("radio_button_off.png", "radio_button_on.png");
    radioButton1->setPosition(Vec2(100,100);
    this->addChild(radioButton1);

    //create another RadioButton
    RadioButton* radioButton2 = RadioButton::create("radio_button_off.png", "radio_button_on.png");
    radioButton2->setPosition(Vec2(100,100);
    this->addChild(radioButton2);

    //add the RadioButtons into RadioButtonGroup
    radioButtonGroup->addRadioButton(radioButton1);
    radioButtonGroup->addRadioButton(radioButton2);
    ```

### AudioEngine

1. Audio preloading

    AudioEngine now supports preload audio files before playing it. For some large audio file, this feature can smooth the audio playing experience in user's games. Sample code: 

    ```cpp
    //Use it with callback
    AudioEngine::preload("audio1.mp3",[](bool isSuccess){
        //...
    });
    //Use it without callback
    AudioEngine::preload("audio2.mp3");
    ```

2. JSB new AudioEngine

    In JSB, the default audio engine was SimpleAudioEngine (renamed to cc.audioEngine). It was the old audio engine provided since v2, and it have some inconvenience like delay time, no event support, etc. So we decided to provide new AudioEngine in JSB, the API remains the same as C++ API, and its usage can be found in [its test case](https://github.com/cocos2d/cocos2d-x/blob/v3/tests/js-tests/src/NativeTest/AudioEngineTest.js).

### FileUtils

1. New file writing APIs

    In v3.8, we have provided a bunch of file writing APIs in FileUtils. Now you can use very simple APIs to write string, binary data, value map, and value vector into a file in user's file system. Each API is demonstrated in the following sample code:

    ```cpp
    std::string writablePath = FileUtils::getInstance()->getWritablePath();

    // FileUtils::writeStringToFile
    std::string writeDataStr = "the string data will be write into a file";
    std::string fullPath = writablePath + "writeStringTest.txt";
    FileUtils::getInstance()->writeStringToFile(writeDataStr, fullPath.c_str());

    // FileUtils::writeDataToFile
    std::string writeDataStr = "the binary data will be write into a file";
    Data writeData;
    writeData.copy((unsigned char *)writeDataStr.c_str(), writeDataStr.size());
    std::string fullPath = writablePath + "writeDataTest.txt";
    FileUtils::getInstance()->writeDataToFile(writeData, fullPath.c_str()));

    // FileUtils::writeValueMapToFile
    std::string fullPath = writablePath + "testWriteValueMap.plist";
    FileUtils::getInstance()->writeValueMapToFile(valueMap, fullPath.c_str());

    // FileUtils::writeValueVectorToFile
    std::string fullPath = writablePath + "testWriteValueVector.plist";
    FileUtils::getInstance()->writeValueVectorToFile(valueVector, fullPath.c_str());
    ```

    Besides, you can retrieve the extension (in lower case) of a file with `FileUtils::getFileExtension` API.

### Others

1. Bindings Generator

    In v3.8, we also improved our bindings generator tool, now it's even more powerful and be able to bind almost all kind of C++ APIs to script. Here is a detailed list about improvement in bindings generator.

    - Supported generating auto bindings code for public member variables
    - Avoid memory leak of non-Ref classes instance by controlling C++ object memory with JS object
    - Made JSB classes automatically extendable if configured in classes_need_extend list
    - Improved support for Lambda functions in JS auto bindings

2. JSB test project

    In v3.8, JSB test project have been merged into C++ test project. That means cocos2d_js_tests.xcodeproj, cocos2d-js-win32.sln, cocos2d-js-win8.1-universal.sln have been removed. You can find jsb test targets in cocos2d_test.xcodeproj, cocos2d-win32.sln and cocos2d-win8.1-universal.sln.

3. Compile custom framework in debug mode

    From v3.7, you was able to generate customized Cocos Framework from cocos2d-x. We have improved this ability in v3.8, now  you will be able to generate framework in debug mode. Here is the some documentation about it:

    - [Framework compile documentation](http://www.cocos2d-x.org/wiki/Cocos_gen-libs).
    - [How to customize Cocos Framework](http://www.cocos2d-x.org/docs/manual/studio/v4/chapter3/HowToCode/CustomizeFramework-v3.8/en)
    - [How to generate Cocos Simulator](http://www.cocos2d-x.org/wiki/Cocos_gen-simulator)

4. Portrait projects support

    From v3.8, you can generate portrait oriented games with Cocos Console:

    ```
    cocos new -l cpp|lua|js --portrait MyPortraitGame
    ```

    More details can be found in [Cocos new command](http://www.cocos2d-x.org/wiki/Cocos_new) and [Cocos Console general documentation](http://www.cocos2d-x.org/wiki/Cocos2d-console)

## Other changes

- [NEW]           UI: Enhanced ScrollView with easing out scrolling
- [NEW]           UI: Added PageView vertical scroll support
- [NEW]           UI: Added PageView::JumpToPage API
- [NEW]           UI: Added a setter for line width in DrawNode
- [NEW]           Action: Permitted setting bitwise flags to action
- [NEW]           Animate: Added Animate's getCurrentFrameIndex function
- [NEW]           FileUtils: Added FileUtils::getFileExtension for getting file's extension name
- [NEW]           Device: Added vibrate support to enable vibration for a duration
- [NEW]           UserDefault: Supported removing key pairs from UserDefault
- [NEW]           spine: Supported Spine runtime 2.3 (Both native and web engine)
- [NEW]           console: Moved the framework-compile tools into cocos2d-console
- [NEW]           network: Upgrade SocketIO support to v1.x

- [REFINE]        3D: Supported composite 2D/3D scene by moving UI and camera far away
- [REFINE]        3D: Improved Particle3D performance
- [REFINE]        Label: Supported adding child nodes in Label
- [REFINE]        UI: Improved Slider's precision
- [REFINE]        UI: Refined scroll event dispatching for ScrollView
- [REFINE]        UI: Improved event handling in TextField
- [REFINE]        Label: Supported auto batch with bitmap font or char map
- [REFINE]        studio: Added BlendFrame support to Skeleton Animation
- [REFINE]        studio: Enabled blendfunc cascade to the skin of BoneNode
- [REFINE]        utils: Made utils::captureScreen saving file in another thread to improve the performance
- [REFINE]        3rd party: Update Nibiru SDK to 2.6
- [REFINE]        JS: Supported new construction for 3d classes in JS
- [REFINE]        JS: Refine performance for Cocos Studio JSON parser for 2.x
- [REFINE]        web: Avoid re-bake the content when the parent node's position get changed
- [REFINE]        web: Solved repeat loading same resource issue when parsing cocos studio project
- [REFINE]        web: Optimized resources automatic loading in JSON parser
- [REFINE]        web: Avoid cc.loader resource loading being terminated while encounter errors
- [REFINE]        web: Suspended the video player when the browser is minimized

You can also take a look at [the full changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

## New APIs

In the above changes, there are some new APIs introduced in v3.8, they are listed here:

1. PageView vertical scroll support

    ```
    PageView* pageView = PageView::create();
    pageView->setContentSize(Size(240.0f, 130.0f));
    pageView->setDirection(ui::PageView::Direction::VERTICAL);
    ```

2. Setter for line width in DrawNode

    ```
    DrawNode* drawNode = DrawNode::create();
    drawNode->setLineWidth(5.0f);
    ```

3. Bitwise flags of action

    ```
    enum Flags {
        FRAME = 1,
        COLOR = 2,
        OPACITY = 4,
        POSITION = 8,
        SCALE = 16,
        ROTATION = 32,
        SKEW = 64
    };

    auto action = RepeatForever::create(Sequence::create(FadeTo::create( 0.1f, 155), TintTo::create(0.1f, 255,0,0), nullptr));
    // Since opacity and color will be modified in this action, it can be flagged as opacity and color action
    action->setFlags(Flags::OPACITY|Flags::COLOR);

    auto action2 = RepeatForever::create(Sequence::create(MoveBy::create(0.3f, Vec2(5, 0)), nullptr));
    // Since position will be modified in this action, it can be flagged as position action
    action->setFlags(Flags::POSITION);
    ```

4. Get current frame index in animation

    ```
    auto action = RepeatForever::create( Animate::create(animation);
    sprite->runAction(action);
    sprite->scheduleOnce([=](float){
        int index = action->getCurrentFrameIndex();
        // ...
    }, 1.0f, "get-current-frame");
    
    ```

5. File's extension name getter

    ```
    std::string extension = FileUtils::getInstance()->getFileExtension("grossini.png");
    ```

6. Vibration support

    ```
    // Virate the device for 0.5 second
    Device::vibrate(0.5f);
    ```

7. Remove key pairs from UserDefault

    ```
    // Remove value referenced by "some key"
    UserDefault::getInstance()->deleteValueForKey("some key");
    ```

# The Next Step

In v3.9, we will continue to improve our framework, several important tasks are: 

1. We are about to provide a script based component system.
2. Improve ScrollView, ListView performance in both native and web engine.
3. Improve 2D particle system performance.
4. Improve web engine renderer logic and performance.
5. Support Action inheritance in JSB.
6. Remove libcurl dependency on iOS and Android.

[The v3.9 milestone tasks](https://github.com/cocos2d/cocos2d-x/milestones/v3.9) (It's still being reviewing and will be updated)
