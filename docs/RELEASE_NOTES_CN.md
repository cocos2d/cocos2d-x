# Cocos2d-x 3.17 Release Notes #

# 改动列表

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# v3.17

该版本使用如下的 Android 工具链进行测试：

- Android Studio 3.0.0
- NDK r16

## 特性

- 支持 iPhone X
- 支持 Android Studio 3.0.0
- CMake 支持全平台，支持预编译引擎库
- 升级 Spine runtime 至 v3.6.39
- 升级 GLFW 至 3.2.1
- 更新 Box2d，并提供 Box2d 预编译库
- 去除 Android 的 ant 工程
- 去除 Visual Studio 2013 的支持

## 特性介绍

### 支持 iPhone X

自 iPhone X 流行，使用引擎的 iOS 开发者存在升级支持 iPhone X 的需求，本版本为开发者解决了这个问题。支持 iPhone X 全屏，启动屏幕改用 Storyboard，增加了一个获取 SafeArea 的接口，支持自动隐藏 Home 指示器。

### 支持 Android Studio 3.0.0

Android Studio 是一个成熟的，同时是 Google 官方支持的 Android 开发 IDE，引擎跟进支持。在支持 3.0 的过程中，同时将支持的 NDK 版本从 r14 升级到 r16。Gradle 工程配置方面，简化 Gradle 变量 PROP_*；将依赖声明中弃用的 compile，改为新的 implementation；增加用以削减 Release 包体积的 Proguard 配置。

### CMake 支持全平台，支持预编译引擎库

在进行跨平台的应用构建时，旧有的做法是为每个平台提供单独的构建工程，比如为 macOS/iOS 平台提供 XCode 工程，为 Windows 平台提供 Visual Studio 2013/2015 工程，使用这种方式，在进行跨平台开发时存在一些不便。而 CMake 作为一个跨平台的构建工具，与引擎的构建需求十分契合。

本版本改进引擎的工程构建方式，扩展 CMake 构建支持至全平台，包括 iOS、Android、macOS、Linux、Windows（VC++ compiler）。支持通过 CMake 将引擎部分预编译，并在新的构建过程中重用预编译的引擎库。通过使用预编译库，可以极大的缩短工程的构建时间。需要注意的是，在 3.17 版本旧有的提供工程文件的构建方式与 CMake 构建方式共存。

### 
