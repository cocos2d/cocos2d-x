<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.17 Release Notes](#cocos2d-x-317-release-notes)
  - [测试环境](#%E6%B5%8B%E8%AF%95%E7%8E%AF%E5%A2%83)
  - [版本特性](#%E7%89%88%E6%9C%AC%E7%89%B9%E6%80%A7)
  - [详细介绍](#%E8%AF%A6%E7%BB%86%E4%BB%8B%E7%BB%8D)
    - [支持 iPhone X](#%E6%94%AF%E6%8C%81-iphone-x)
    - [支持 Android Studio 3.0+](#%E6%94%AF%E6%8C%81-android-studio-30)
    - [CMake 支持全平台](#cmake-%E6%94%AF%E6%8C%81%E5%85%A8%E5%B9%B3%E5%8F%B0)
    - [升级第三方库](#%E5%8D%87%E7%BA%A7%E7%AC%AC%E4%B8%89%E6%96%B9%E5%BA%93)
    - [移除过时的内容](#%E7%A7%BB%E9%99%A4%E8%BF%87%E6%97%B6%E7%9A%84%E5%86%85%E5%AE%B9)
    - [Bugs 修复，提高稳定性](#bugs-%E4%BF%AE%E5%A4%8D%E6%8F%90%E9%AB%98%E7%A8%B3%E5%AE%9A%E6%80%A7)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.17 Release Notes #

Cocos2d-x 3.17 版本着重于工具链的更新，和稳定性的增强。

## 测试环境

 Android 平台使用 Android Studio (3.0, 3.1, 3.1.1) 和 NDK r16 进行测试。

## 版本特性

- 支持 iPhone X
- 支持 Android Studio 3.0+
- CMake 支持全平台，支持预编译引擎库
- 升级 Spine runtime 至 v3.6.39
- 升级 GLFW 至 3.2.1，并提供预编译库
- 更新 Box2D，并提供预编译库
- 去除 Android 的 ant 工程
- 去除 Visual Studio 2013 的支持

## 详细介绍

### 支持 iPhone X

3.17 带来对 iPhone X 的支持，包含支持全屏模式，支持自动隐藏 Home 指示器，改用 Storyboard 作为启动屏幕，和增加获取 Safe Area 的接口。在开发支持 iPhone X 的应用时，最需要了解清楚的就是 Safe Area：

<p align="center">
  <img width="400" src="https://raw.githubusercontent.com/cocos2d/cocos2d-x-docs/master/en/installation/iOS-img/iPhoneXSafeArea.png">
</p>

开发者可以通过调用 `Director::getSafeAreaRect()` 来获取 Safe Area 区域。

### 支持 Android Studio 3.0+

Android Studio 是 Google 官方唯一支持的 Android 开发 IDE。

该版本增加了对 Android Studio 3.0+ 的支持。在支持的过程中，同时将 NDK 版本从 r14 升级到 r16。对 Gradle 工程配置也进行了诸多改进，包括简化 Gradle 变量 PROP_*，将依赖声明中弃用的 `compile` 改为新的 `implementation`，增加用以削减 Release 包体积的 Proguard 文件。

### CMake 支持全平台

扩展 CMake 构建支持至全平台，包括 Android (NDK)、iOS、macOS、Linux、Windows（VC++ compiler）。支持将引擎部分进行预编译，并在新的构建过程中重用预编译的引擎库。通过使用预编译库，可以极大的缩短工程构建时间。

详细的使用方法请参考 [CMake 文档](https://github.com/cocos2d/cocos2d-x/blob/v3/cmake/README.md)

### 升级第三方库

Spine 骨骼动画广泛用于 Cocos2d-x 开发的游戏，引擎跟进 Spine 的升级，升级 Runtime 至 3.6.39。

升级 GLFW 至 3.2.1 以修复支持游戏手柄时存在的问题，同时提供 GLFW 预编译库。

社区希望引擎升级 Box2D，可 Box2D 的新版本迟迟未发布，根据反馈 GitHub 提交 f655c603ba9d83 是稳定的，升级 Box2D 至该提交，同时提供 Box2D 的预编译库。

每一次版本发布，都会附带特定版本的第三方预编译库，如果由于项目需要想对第三方库进行定制，请参考: [第三方库文档](https://github.com/cocos2d/cocos2d-x-3rd-party-libs-src/blob/v3/README.md)

### 移除过时的内容

由于 Google 官方自 [Android SDK Tools 25.3.0](http://tools.android.com/recent/androidsdktoolsrevision2530feb2017) 就已放弃 ant 支持。移除旧有的 `proj.android` ant 工程，新的 `proj.android` 是 Android Studio 工程。[NDK r16](https://developer.android.com/ndk/guides/abis) 弃用了 armeabi，引擎调整默认的编译架构从 armeabi 为 armeabi-v7a。

在 win32 平台，越来越多的开发者已经使用 Visual Studio 2015/2017 进行开发，移除对年代久远的 2013 的支持。现存的工程配置适合于 2015 ，如果需要使用 2017，可打开现有的 sln 文件，调整配置，或使用 CMake。

### Bugs 修复，提高稳定性

改版本包含 51 项 bugs 修复和 33 项小改进，不再列举，请参考 [Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)。

