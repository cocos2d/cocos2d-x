<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [v3.13.1](#v3131)
  - [Bug修复](#bug%E4%BF%AE%E5%A4%8D)
  - [Cocos命令的改动](#cocos%E5%91%BD%E4%BB%A4%E7%9A%84%E6%94%B9%E5%8A%A8)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# v3.13.1

## Bug修复

* Label的颜色错误问题
* 如果没有设置`design resolution`，应用程序在debug模式下会崩溃
* 在Android系统，如果通过点击应用图标从后台推前台，可能导致崩溃
* 在Android系统，如果音乐或音效资源不在APK包里，会导致无法播放
* 在Android系统，AudioEngine::stop()会回调`finish`回调函数
* 使用`SimpleAudioEngine`或者`AudioEngine`播放音效或者背景音乐，在Android 2.3.x会崩溃
* JSB中，如果传入object.setString()的参数类型是数字，没有任何效果

对应的github issue可以从[这里](https://github.com/cocos2d/cocos2d-x/milestone/33)找到。

## Cocos命令的改动

之前的版本，在Android平台下，cocos命令编译代码时会找大于等于指定的API级别的Android SDK，比如`APP_ROOT/proj.android/project.properties`的内容是这样的

```
target=android-13 // Android API级别
android.library.reference.1=../../../cocos/platform/android/java
```
那么cocos命令会在`ANDROID_SDK_ROOT/platforms`目录下找`android-13`，如果找不到就会找`android-14`，如果找不到的话会找`android-15`直到找到一个合适的级别。

该算法有个问题，假设你只下载了`android-21`，虽然`APP_ROOT/proj.android/project.properties`指定是要使用`android-13`，最终也会使用`android-21`编译。编译出来的程序如果跑在Android 4.0的设备，那么就可能会崩溃。使用高版本Android SDK编译的程序不能保证能在低版本的Andoid系统上运行，就好比用iOS 9编译的程序不能保证运行在iOS 8一样。

从3.13.1开始，cocos命令如果找不到指定的API级别会立即停止。想用指定的API级别编译的话需要使用命令行参数指定：

```
cocos compile -p android --ap android-19
```
注意的事，一旦该命令运行后，那么`APP_ROOT/proj.android/project.properties`的内容就会改动，变成

```
target=android-19 // Android API级别
android.library.reference.1=../../../cocos/platform/android/java
```

Android API级别和Android系统版本间存在对应的映射关系，可以参看[该文档](https://developer.android.com/guide/topics/manifest/uses-sdk-element.html)获取详细的内容。