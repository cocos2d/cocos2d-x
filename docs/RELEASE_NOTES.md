<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.10 Release Notes](#cocos2d-x-
- -release-notes)
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
- [v3.10](#v310)
  - [Highlights features, improvements and API updates of v3.10](#highlights-features-improvements-and-api-updates-of-v310)
  - [The main features in detail of Cocos2d-x v3.10:](#the-main-features-in-detail-of-cocos2d-x-v310)
    - [UI System](#ui-system)
    - [AudioEngine](#audioengine)
    - [Others](#others)
  - [Other changes](#other-changes)
  - [NEW APIS](#new-apis)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.10 Release Notes #

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

# v3.10

## Highlights features, improvements and API updates of v3.10

We are happy to announce the release of Cocos2d-x v3.10. Following are the highlighted features, improvements and API updates in this version. 

1. Provides a unified setup for both Cocos2d-x and Cocos. This allows you to stay up to date with the latest Cocos2d-x releases. This includes using precompiled binaries and source code, in a single place. As always the source code is available from [GitHub](https://github.com/cocos2d/cocos2d-x) but, there is no longer a `.zip` file available containing the source code. 
2. New __Cocos Launcher__ tool! __Cocos Launcher__ allows:
  * One step to create a new project with the engine, by using precompiled libraries or source code.
  * Easy integration with SDKBOX for 3rd party services: Facebook, IAP and many more.
  * Developers to provide feedback and get support, directly within __Cocos Launcher__, making it simple to contact the engine team for help.　
3. UI System:
  * Reimplemented `Scale9Sprite` to improve performance and reduce memory consumption.
  * Changed `PageView` to derive from `ListView`. `PageView` can add any widget as a child.
  * Added three new *overflow types* to `Label`: **CLAMP**，**SHRINK**, **RESIZE_HEIGHT**.
  * Fixed a bug in `ClippingNode` that corrects its behavior when being set as a child.
4. Improved **JavaScript Bindings**: follows [SpiderMonkey GC best practices](https://developer.mozilla.org/en-US/docs/Mozilla/Projects/SpiderMonkey/GC_Rooting_Guide) making it more robust.

## The main features in detail of Cocos2d-x v3.10:

### UI System

1. Reimplemented `Scale9Sprite` and improve the scale9sprite performance and reduce memory consumption.
    
    Reimplemented ui::Scale9Sprite, now the Slice sprite uses 16 vertices and 54 indices instead of the old 9 sprites way, The memory consumption is much lower than the previous implementation, and it is also more efficient.

    In SIMPLE mode, the 4 borders are all 0 and the whole sprite will scale horizontally and vertically. In this mode only 1 quad is used for rendering, for example:

        auto blocks = ui::Scale9Sprite::createWithSpriteFrameName("blocks9c.png");
        //When setting to SIMPLE, only 4 vertexes is used to rendering.
        blocks->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);

    In SLICE mode, it will use 18 triangles to rendering the slice 9 sprite. If the 4 borders are 0, there still be 18 triangles computed. So choose your RenderingType wisely, for example:

		auto sprite = ui::Scale9Sprite::createWithSpriteFrameName("blocks9c.png");
        //When setting to SLICE, 16 vertexes will be used to rendering.
        sprite->setRenderingType(Scale9Sprite::RenderingType::SLICE);
    
2. Changed `PageView` to derived from ListView, PageView can add any type of widget as child.

    PageView was derived from Layout and it implemented the features of scrolling and item arrangement from scratch. But the features are already there in ListView. So remove those duplicated implementations from PageView and make it inherit from ListView.

    By consequence, PageView becomes simpler and easier to maintain because it considers only paging implementation. for example:

        // Create the page view
        Size size(240, 130);
        PageView* pageView = PageView::create();
        pageView->setDirection(PageView::Direction::HORIZONTAL);
        pageView->setContentSize(size);
        Size backgroundSize = background->getContentSize();
        //"removeAllPages" is changed to "removeAllItems"
        pageView->removeAllItems();
        pageView->setIndicatorEnabled(true);

        int pageCount = 4;
        for (int i = 0; i < pageCount; ++i)
        {
            Layout* layout = Layout::create();
            layout->setContentSize(size);
            
            ImageView* imageView = ImageView::create("cocosui/scrollviewbg.png");
            imageView->setScale9Enabled(true);
            imageView->setContentSize(size);
            imageView->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
            layout->addChild(imageView);
            
            Text* label = Text::create(StringUtils::format("page %d",(i+1)), "fonts/Marker Felt.ttf", 30);
            label->setColor(Color3B(192, 192, 192));
            label->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
            layout->addChild(label);
            //"insertPage" is changed to "insertCustomItem"
            pageView->insertCustomItem(layout, i);
        }
        //"removePageAtIndex" is changed to "removeItem"
        pageView->removeItem(0);
        //"scrollToPage" is changed to "scrollToItem"
        pageView->scrollToItem(pageCount - 2);

     More detail usage please refer to: tests/cpp-tests/Classes/UITest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest.cpp.
    
   
3. Added three overflow type to new label: CLAMP, SHRINK, RESIZE_HEIGHT.
  
     Overflow type is used to control label overflow result, In SHRINK mode, the font size will change dynamically to adapt the content size. In CLAMP mode, when label content goes out of the bounding box, it will be clipped, In RESIZE_HEIGHT mode, you can only change the width of label and the height is changed automatically. For example:
       
        //Change the label's Overflow type
        label->setOverflow(Label::Overflow::RESIZE_HEIGHT);

     More detail usage please refer to: tests/cpp-tests/Classes/LabelTest/LabelTestNew.cpp.

     Limitations:


     currently only TTF and BMFont support all the valid Overflow type. Char Map font supports all the Overflow type except for SHRINK, because we can't measure its font size. System font only support Overflow::Normal and Overflow::RESIZE_HEIGHT.

## Other changes
[NEW]           RichText supported new line element.

[NEW]           UIText::clone supports clone the text effect.

[NEW]           UI: Added methods to query label effect state.
    
[REFINE]        IOS: Added virtual keyword for some render related function.

[REFINE]        UI: Fixed boring deprecated warning in HttpRequest.

[REFINE]        Network: Fixed Downloader bug on iOS & Android platform.

[REFINE]        Studio: Fixed deprecation warning in SkeletonRenderer.

[REFINE]        JS: Added js test case for fix, improve template.

[REFINE]        Network: Permit http access to cocos2d-x.org in test projects on iOS.

[REFINE]        Network: Crash when removing a remotely downloaded image from texture 
cache in js-binding.

[REFINE]        Win10: WinRT project update version to v3.10.

[REFINE]        Console: Added quiet option for Cocos Toolkit.

[REFINE]        JS: New GC model for js-binding.

[REFINE]        Doc: Fixed typos in documentation and comments.

[REFINE]        UI: Updated controlButton size calculate with new Scale9Sprite logic.

[REFINE]        Win10: Added missing _USRJSSTATIC preprocessor define for ARM builds.

[REFINE]        JS: Added ccvector_to / ccmap_to converted to new js-binding API.

[REFINE]        UI: Slider misprint fix.

[FIX]           Core: Fixed premultiplyAlpha for mipmaps and compressed textures.

[FIX]           UI: Fixed Scale9sprite rendering error when content size smaller than the sum of leftInset and rightInset.

[FIX]           Win32: Fixed EditBox crash when removing an EditBox in a scheduler.

[FIX]           Android: Fixed cannot add view to mFrameLayout when extends Cocos2dxActivity.

[FIX]           2D: Fixed actionNode set at wrong position bug.

[FIX]           3D: Fixed the movement of PUParticle lags one frame.

[FIX]           UI: Fixed the wront argument of setPlaceholderFontName in EditBox.

[FIX]           UI: Fixed EditBox editBoxEditingDidEnd may use the original text after change the text of EditBox in user script.

[FIX]           Audio: Fixed `FinishCallback` never be called in Windows.

[FIX]           UI: Fixed Layout stencil clipping nested with Clipping Node rendering issue.

[FIX]           UI: Keyboard doesn't hide when click the screen outside of EditBox on iOS platform.

[FIX]           UI: Fixed a fatal bug in EditBox implement on Windows platform.

[FIX]           UI: Fixed edit box setPlaceholderFontName and scale font size issue.

[FIX]           Core: Fixed memory leak when initWithImage() failed.

[FIX]           Network: CCDownloader on iOS is broken in v3.9 js-binding.

[FIX]           JS: Bindings fixes for Menu, Sprite and Label.

[FIX]           Studio: Removed weak reference in ActionNode.

[FIX]           UI: shouldStartLoading method should return value to js in js-binding.

[FIX]           UI: Fixed scrollview render error.

[FIX]           JS: Fixed win32 js project crash issue.

[FIX]           UI: Button touch doesn't work with scale9 enabled.

[FIX]           JS: Fixed evalString doesn't return result issue.

[FIX]           JS: Fixed ComponentJS proxy management issue in JSB.

[FIX]           Android: Fixed include in cocos network module.

[FIX]           Network: Fixed web socket crash.

[FIX]           UI: Fixed TextField missing default password style text setting.

[TEST]          S9SpriteTest: Scale9Sprite fade actions with cascade opacity.

[TEST]          Web: Removed default focus block from UIFocusTestVertical.

[TEST]          Lua: Fixed pageViewTest Horizontal scroll won't work in Lua-test.

You can also take a look at the [full changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG).

## NEW APIS

1. RichText

    Added RichElementNewLine class to create new RichText Element.

    For more information: [https://github.com/cocos2d/cocos2d-x/pull/14033](https://github.com/cocos2d/cocos2d-x/pull/14033 "https://github.com/cocos2d/cocos2d-x/pull/14033")

2. PageViewIndicator

    Added PageViewIndicator class to create PageViewIndicator.

    For more information: [https://github.com/cocos2d/cocos2d-x/blob/v3/cocos/ui/UIPageViewIndicator.h](https://github.com/cocos2d/cocos2d-x/blob/v3/cocos/ui/UIPageViewIndicator.h "https://github.com/cocos2d/cocos2d-x/blob/v3/cocos/ui/UIPageViewIndicator.h")

3. PageView 

    Changed PageView to derived from ListView.
    For more information: [https://github.com/cocos2d/cocos2d-x/pull/14252](https://github.com/cocos2d/cocos2d-x/pull/14252 "https://github.com/cocos2d/cocos2d-x/pull/14252")

4. ApplicationProtocol

    Added the API getVersion.


5. PolygonInfo

    Added the API setTriangles.

6. Scale9Sprite

    Added setRenderingType, getRenderingType.

9. FontFNT

    Added setFontSize, getOriginalFontSize.

10. Label

    Added setBMFontSize, getBMFontSize, enableWrap, isWrapEnabled, setOverflow, getOverflow, initWithTTF, isShadowEnabled, getShadowOffset, getShadowBlurRadius, getShadowColor, getOutlineSize, getLabelEffectType, getEffectColor.

11. AudioEngineImpl

    Added AudioEngineImpl to implement FMOD.

12. Lua Module

    Added luaval_to_node, node_to_luaval.

13. JS Module

    Added js_cocos2dx_ComponentJS_create

14. ui::Text

    Added isShadowEnabled, getShadowOffset, getShadowBlurRadius, getShadowColor,  getOutlineSize, getLabelEffectType, getEffectColor.

15. UITextTest_Clone 

    Added UITextTest_Clone class.
    