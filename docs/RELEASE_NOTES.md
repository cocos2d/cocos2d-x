<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.10 Release Notes](#cocos2d-x-310-release-notes)
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
- [v](#v310)
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

1. UI System:
    - Reimplemented Scale9Sprite and improve the scale9sprite performance and reduce memory consumption.
    - Changed PageView to derived from ListView.
    - Added PageView indicator. 
    - Added three Overflow type to new label. 
    - RichText supported new line element.
2. AudioEngine
    - AudioEngine on Linux replace the original SimpleAudioEngine with a new version of FMOD, now AudioEngine support all platforms.
3. Others: 
    - Added Application::getVersion() to get the app version.
    - Set focus to Widget when touched.
    - Improved JS bindings with more secured memory management.


## The main features in detail of Cocos2d-x v3.10:

### UI System

1.  Reimplemented Scale9Sprite and improve the scale9sprite performance and reduce memory consumption.

    - Now the Slice sprite uses 16 vertices and 54 indices instead of the old 9 sprite way.

    - The memory consumption is much lower than the previous implementation. And it is also more time efficient.

    - Add RenderingType to slice sprite. When Scale9Enable is true, then we have two rendering type here.

    - In Simple mode, the 4 borders are all 0 and the whole sprite will scale horizontally and vertically. In this mode only 1 quad is used to rendering.

    - In Slice mode, it will use 18 triangles to rendering the slice 9 sprite. If the 4 borders are 0, there still be 18 triangles computed. So choose your RenderingType wisely.

2. Changed PageView to derived from ListView.

    PageView was derived from Layout and it implemented the features of scrolling and item arrangement from scratch. But the features are already there in ListView. So remove those duplicated implementations from PageView and make it subclass from ListView.

    By this, PageView becomes more simplified and maintainable because it considers only paging implementation. 

3. Added PageView indicator
    
    PageView now has a page indicator which is represented as a list of small circles.

4. Added three Overflow type to new label. 

    Add three different type of Overflow to Label.

        enum class Overflow
        {
            //for keep back compatibility
            NORMAL,
            /**
             * In SHRINK mode, the font size will change dynamically to adapt the content size.
            */
            SHRINK,
            /**
             *In CLAMP mode, when label content goes out of the bounding box, it will be clipped.
            */
            CLAMP,
            /**
             *In RESIZE_HEIGHT mode, you can only change the width of label and the height is changed automatically.
            */
            RESIZE_HEIGHT
        };

    Limitations:

     Currently the System font doesn't support these Overflow feature and Char Map font doesn't support Shrink feature.

5.  RichText supported new line element.
   
    Added new "NEWLINE" type of RichElement to RichText. You can add new line to RichText.



### AudioEngine
    
1.  AudioEngine on Linux replace the original SimpleAudioEngine with a new version of FMOD, now AudioEngine support all platforms.

### Others

1. Added Application::getVersion() to get the app version.

    Added a method to the Application class to get the version of the app on iOS/Mac/Android/Win8, on the remaining platforms that don't have app versions it should return an empty string.

    The feature has been requested in this discussion thread: http://discuss.cocos2d-x.org/t/check-app-version/6294/5

2. Set focus to Widget when touched.

    Automatically set focus for widgets if focus enabled.


3. Improved JS bindings with more secured memory management.

    Improvement covered both auto bindings and manual bindings.
    All changes follow Generational GC style.

    The background of this feature: [http://blogs.msdn.com/b/abhinaba/archive/2009/03/02/back-to-basics-generational-garbage-collection.aspx](http://blogs.msdn.com/b/abhinaba/archive/2009/03/02/back-to-basics-generational-garbage-collection.aspx "http://blogs.msdn.com/b/abhinaba/archive/2009/03/02/back-to-basics-generational-garbage-collection.aspx")

    This requires to adopt the new GC coding style in all JSB code.

    The new GC coding style can be verified with this tool: [https://github.com/joshuastray/RootAnalysis](https://github.com/joshuastray/RootAnalysis "https://github.com/joshuastray/RootAnalysis")

## Other changes
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

You can also take a l
ook at the [full changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG).


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

    Added adjustNoneScale9ImagePosition, configureSimpleModeRendering, calculateUV, calculateVertices, calculateTriangles, setRenderingType, getRenderingType.

7. CWin32InputBox

    Added GetMsgProc, onWin32InputBoxClose.

8. FontAtlas

    Added scaleFontLetterDefinition.

9. FontFNT

    Added setFontSize, getOriginalFontSize.

10. Label

    Added setBMFontSize, getBMFontSize, enableWrap, isWrapEnabled, setOverflow, getOverflow, multilineTextWrap, shrinkLabelToContentSize, isHorizontalClamp, isVerticalClamp, getRenderingFontSize, rescaleWithOriginalFontSize, updateBMFontScale, scaleFontSizeDown, setTTFConfigInternal, setBMFontSizeInternal, restoreFontSize, updateLetterSpriteScale, initWithTTF, isShadowEnabled, getShadowOffset, getShadowBlurRadius, getShadowColor, getOutlineSize, getLabelEffectType, getEffectColor.

11. AudioEngineImpl

    Added AudioEngineImpl to implement FMOD.

12. JS Module

    Added luaval_to_node, node_to_luaval, js_cocos2dx_ComponentJS_create.


13. Widget_mac.h

    Added getCurAppName.


14. Text

    Added isShadowEnabled, getShadowOffset, getShadowBlurRadius, getShadowColor,  getOutlineSize, getLabelEffectType, getEffectColor.

15. UITextTest_Clone 

    Added UITextTest_Clone class.
    