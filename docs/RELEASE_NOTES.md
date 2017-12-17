<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.16 Release Notes](#cocos2d-x-316-release-notes)
- [Misc Information](#misc-information)
- [v3.16](#v316)
  - [Highlights](#highlights)
  - [Highlights in detail](#highlights-in-detail)
    - [Better support [`creator_to_cocos2dx`][1]](#better-support-creator_to_cocos2dx1)
    - [LayerRaidalGradient](#layerraidalgradient)
    - [Lua app crashed on iOS simulator with Xcode 8.0+](#lua-app-crashed-on-ios-simulator-with-xcode-80)
    - [Cocos Studio](#cocos-studio)
    - [Improve compiling speed](#improve-compiling-speed)
    - [Remove some platforms support](#remove-some-platforms-support)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.16 Release Notes #

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# v3.16

Android tool version tested in this version:

- Android Studio 2.3.3
- NDK r14

## Highlights

- better support [`creator_to_cocos2dx`][1] creator plugin
- add __LayerRadiaGradientLayer__
- update to support Android Studio 2.3.3
- fix the issue that lua projects will crash on iOS simulator with Xcode 8.0+
- revert CocosStudio reader and flatbuffer
- fix compling error with iOS 11
- use prebuit bullet to improve compiling speed
- remove supporting of Windows 10 metro, Windows Phones and Tizen
- update to Spine v3.5.35 and support skeleton batching in web engine

## Highlights in detail

### Better support [`creator_to_cocos2dx`][1]

[`creator_to_cocos2dx`][1] is a [Cocos Creator][2] plugin that will export Scene information created by [Cocos Creator][2] for cocos2d-x C++/Lua projects. We mention it as __plugin__ following.

With this plugin, you can use [Cocos Creator][2] as Scene editor for cocos2d-x. Curretly, the plugin supports [these features](3), and will continue to add more features. As you can see, RichText img tag support only works in cocos2d-x v3.16+ because of cocos2d-x's limitation. So cocos2d-x will continue to be improved to support more [Cocos Creator][2] features.

More detail information and usage please refer to plugin's [the README][1]. You are appreciated if you can use it and give feedback.

![][4]
__Scene effect in cocos creator__

![][5]
__Scene effect in cocos2d-x__

### LayerRaidalGradient

LayerRadialGradient is similar to LayerColor, but will only draw color in a circle.

![][6]

### Lua app crashed on iOS simulator with Xcode 8.0+

After updating to Xcode 8.0+, lua projects will crash on iOS simulator. It is a bug of luagit. In this version, the bug it is fixed. You can just update [luajit][7] if you don't want to update cocos2d-x.

### Fix compiling error with iOS 11

Before cocos2d-x v3.16, `CCFileUtils` uses `system()` to remove a directory. iOS 11 remove `system`, so will cause compiling error with iOS 11. This version fixes this issue. The corresponding PR for this issue is [here](https://github.com/cocos2d/cocos2d-x/pull/17921), you can apply this PR to fix it if you don't want to upgrade to v3.16.

### Cocos Studio

coocs2d-x v3.15 updates flatbuffer, which breaks compatibility of Cocos Studio. In this version, we revert flatbuffer and Cocos Studio reader.

If you don't want to update cocos2d-x, you can replace flatbuffer and Cocos Studio reader shift in this version.

### Improve compiling speed

As bullet is not needed for most developers, so we use prebuilt bullet. It will speed up compiling speed, and we will continue to use more prebuilt 3rd party libraries, such as 3d particles, Box2D and so on to speed up compiling speed.

We also fix many warnings too in this version. As some warnings are imported by 3rd party libaries, so we can not treat warnings as error, but we will continue to achieve it.

### Remove some platforms support

As we are lack of human resources, so we remove some platforms.

MS maintians Win10 related platform, but it doesn't continue to maintain it. So we remove it. Which means cocos2d-x based games can not run on Win10 metro mode and Windows Phones, but you can run it in Win32 mode.

Tizen platform is removed too because of huaman resources.


[1]: https://github.com/cocos2d/creator_to_cocos2dx
[2]: http://cocos2d-x.org/creator
[3]: https://github.com/cocos2d/creator_to_cocos2dx#limitations
[4]: https://raw.githubusercontent.com/minggo/Pictures/master/creator-ui-effect.png
[5]: https://raw.githubusercontent.com/minggo/Pictures/master/cocos2dx-ui-effect.png
[6]: https://raw.githubusercontent.com/minggo/Pictures/master/layerradialgradient.png
[7]: https://github.com/cocos2d/cocos2d-x-3rd-party-libs-bin/tree/v3/lua/luajit/prebuilt/ios "luajit.a"
