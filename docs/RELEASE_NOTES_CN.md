<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.17 Release Notes](#cocos2d-x-317-release-notes)
  - [改动列表](#%E6%94%B9%E5%8A%A8%E5%88%97%E8%A1%A8)
  - [测试环境](#%E6%B5%8B%E8%AF%95%E7%8E%AF%E5%A2%83)
  - [版本特性](#%E7%89%88%E6%9C%AC%E7%89%B9%E6%80%A7)
  - [详细介绍](#%E8%AF%A6%E7%BB%86%E4%BB%8B%E7%BB%8D)
    - [支持 iPhone X](#%E6%94%AF%E6%8C%81-iphone-x)
    - [支持 Android Studio 3.0](#%E6%94%AF%E6%8C%81-android-studio-30)
    - [CMake 支持全平台](#cmake-%E6%94%AF%E6%8C%81%E5%85%A8%E5%B9%B3%E5%8F%B0)
    - [升级第三方库](#%E5%8D%87%E7%BA%A7%E7%AC%AC%E4%B8%89%E6%96%B9%E5%BA%93)
    - [移除过时的内容](#%E7%A7%BB%E9%99%A4%E8%BF%87%E6%97%B6%E7%9A%84%E5%86%85%E5%AE%B9)
    - [Bugs 修复，提高稳定性](#bugs-%E4%BF%AE%E5%A4%8D%E6%8F%90%E9%AB%98%E7%A8%B3%E5%AE%9A%E6%80%A7)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.17 Release Notes #

## 改动列表

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

## 测试环境

Android 

- Android Studio 3.0
- NDK r16

Linux

- Ubuntu 16.04

Windows

- Visual Studio 2015

## 版本特性

- 支持 iPhone X
- 支持 Android Studio 3.0
- CMake 支持全平台，支持预编译引擎库
- 升级 Spine runtime 至 v3.6.39
- 升级 GLFW 至 3.2.1，并提供预编译库
- 更新 Box2D，并提供预编译库
- 去除 Android 的 ant 工程
- 去除 Visual Studio 2013 的支持

## 详细介绍

### 支持 iPhone X

自 iPhone X 流行，使用引擎的 iOS 开发者存在升级支持 iPhone X 的需求，该版本为开发者解决了这个问题。支持 iPhone X 全屏，启动屏幕改用 Storyboard，增加了一个获取 safe area 的接口，支持自动隐藏 Home 指示器。

在开发支持 iPhone X 的应用时，最需要注意的一点就是 safe area：

![safe area](https://developer.apple.com/ios/human-interface-guidelines/images/OV_LayoutGuides_Landscape.svg)

开发者可以简单的通过 `Rect safeArea = Director::getInstance()->getSafeAreaRect();`  获取 safe area 区域。

### 支持 Android Studio 3.0

Android Studio 是一个成熟的，同时是 Google 官方支持的 Android 开发 IDE，引擎跟进支持。在支持 3.0 的过程中，同时将支持的 NDK 版本从 r14 升级到 r16。Gradle 工程配置方面，简化 Gradle 变量 PROP_*；将依赖声明中弃用的 compile 改为新的 implementation；增加用以削减 Release 包体积的 Proguard 配置。

### CMake 支持全平台

扩展 CMake 构建支持至全平台，包括 iOS、Android、macOS、Linux、Windows（VC++ compiler）。支持将引擎部分预编译，并在新的构建过程中重用预编译的引擎库。通过使用预编译库，可以极大的缩短工程的构建时间。

详细的使用方法请参考 [这个文档](https://github.com/cocos2d/cocos2d-x/blob/v3/cmake/README.md)

### 升级第三方库

Spine 骨骼动画在使用 Cocos2d-x 开发的游戏中被广泛使用，使用新版的 Spine 导出的素材在老版本的 runtime 上运行存在一些兼容性问题，升级 Spine Runtime 至 3.6.39，解决这些问题。

原 GLFW 版本是 3.2.0，在使用 GLFW 支持游戏手柄时存在问题，升级 GLFW 至 3.2.1 后解决，同时提供 GLFW 预编译库。

原 Box2D 版本 2.3.1，2014 年发布的版本，截至 2018 年初新的版本一直未发布，但 GitHub 已经有一些 bugs 修复，根据社区的建议，升级 Box2D 至最新提交 f655c603ba9d83，同时提供 Box2D 的预编译库。

每一次版本发布，都会附带着特定某个版本的第三方库，如果由于项目需要想升级第三方库，并且提供对应的预编译库，请参考: [这个文档](https://github.com/cocos2d/cocos2d-x-3rd-party-libs-src/blob/v3/README.md)

### 移除过时的内容

由于 Google 官方自 [Android SDK Tools 25.3.0](http://tools.android.com/recent/androidsdktoolsrevision2530feb2017) 就已放弃 ant 支持，另一方面 Android Studio 已经足够完善，于是决定移除旧有的 ant 工程 `proj.android`，重命名原 Android Studio 工程 `proj.android-studio` 为 `proj.android`。Google 决定在 [NDK r16](https://developer.android.com/ndk/guides/abis) 弃用 armeabi，引擎跟进弃用，默认的 Android 工程编译架构从 armeabi 改为 armeabi-v7a。

Visual Studio 2013 已经有一些历史了，移除支持。现存的工程配置适合于 Visual Studio 2015 ，如果需要使用 2017，可打开 2015 的工程配置文件，修改部分配置，或使用 CMake 的构建方式。

### Bugs 修复，提高稳定性

该版本包含 51 项 bugs 修复，33 项小改进，不再一一列举，详细请参考 [Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)。

