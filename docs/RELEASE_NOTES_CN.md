<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.16 Release Notes](#cocos2d-x-316-release-notes)
- [改动列表](#%E6%94%B9%E5%8A%A8%E5%88%97%E8%A1%A8)
- [v3.16](#v316)
  - [特性](#%E7%89%B9%E6%80%A7)
  - [特性介绍](#%E7%89%B9%E6%80%A7%E4%BB%8B%E7%BB%8D)
    - [更好地支持 [`creator_to_cocos2dx`][1]](#%E6%9B%B4%E5%A5%BD%E5%9C%B0%E6%94%AF%E6%8C%81-creator_to_cocos2dx1)
    - [LayerRaidalGradient](#layerraidalgradient)
    - [Lua工程在Xcode 8.0+模拟器崩溃问题](#lua%E5%B7%A5%E7%A8%8B%E5%9C%A8xcode-80%E6%A8%A1%E6%8B%9F%E5%99%A8%E5%B4%A9%E6%BA%83%E9%97%AE%E9%A2%98)
    - [修复iOS 11编译错误](#%E4%BF%AE%E5%A4%8Dios-11%E7%BC%96%E8%AF%91%E9%94%99%E8%AF%AF)
    - [Cocos Studio](#cocos-studio)
    - [提高编译速度](#%E6%8F%90%E9%AB%98%E7%BC%96%E8%AF%91%E9%80%9F%E5%BA%A6)
    - [去除支持一些平台](#%E5%8E%BB%E9%99%A4%E6%94%AF%E6%8C%81%E4%B8%80%E4%BA%9B%E5%B9%B3%E5%8F%B0)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.16 Release Notes #

# 改动列表

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# v3.16

该版本使用如下的Android工具链进行测试：

- Android Studio 2.3.3
- NDK r14

## 特性

- 更好地支持 [`creator_to_cocos2dx`][1] 这个Cocos Creator的插件
- 新增 __LayerRadiaGradientLayer__
- 支持 __Android Studio 2.3.3__
- 修复lua工程在Xcode 8.0+模拟器崩溃问题
- 回退CocosStudio的reader和flatbuffer
- 修复iOS 11编译错误
- 使用bullet的预编译库以加快编译速度
- 去除Windows 10 metor模式、Windows Phone和Tizen的支持
- Web引擎更新Spine runtime到v3.5.35

## 特性介绍

### 更好地支持 [`creator_to_cocos2dx`][1]

[`creator_to_cocos2dx`][1]是一个[Cocos Creator][2]的插件。该插件用于导出Creator创建的场景内容给cocos2d-x的C++/Lua工程使用。下文的 
 __插件__ 就是指这个插件。

通过使用该插件，可以把[Cocos Creator][2]当成cocos2d-x的场景编辑器。该插件目前支持[这些特性](3)，会持续支持其他新的特性。有些特性只在v3.16+版本支持，比如RichText img标签。

插件的详细使用方法可以参考插件仓库的[the READE][1]，欢迎使用并给与反馈。

![][4]
__Scene effect in cocos creator__

![][5]
__Scene effect in cocos2d-x__

### LayerRaidalGradient

LayerRadialGradien和LayerColor类似，它会在制定的圆里绘制颜色，效果如下：

![][6]

### Lua工程在Xcode 8.0+模拟器崩溃问题

v3.16版本之前，Lua工程在Xcode 8.0+模拟器会崩溃。这是luajit本身的一个bug，v3.16版本修复了这个问题。如果不想更新引擎，也可以直接更新[luajit][7]。

### 修复iOS 11编译错误

v3.16版本之前，`CCFileUtils`使用`system()`函数来删除目录。iOS 11删除了`system`，因此导致了编译错误。改版本修复了这个问题。对应的PR链接在[这里](https://github.com/cocos2d/cocos2d-x/pull/17921)，如果不想更新引擎的话，可以参考该PR的改动合并以修复这个问题。

### Cocos Studio

v3.15更新了flatbuffer，破坏了Cocos Studio reader的兼容性。该版本回退了flatbuffer和Cocos Studio的reader。

如果不想更新引擎的话，可以手动从改版本或者v3.15之前的版本拷贝flatbuffer和Cocos Studio的reader。

### 提高编译速度

大部分的项目不需要bullet，因此这个版本使用bullet的预编译库以加快编译速度。后续还会继续使用更多预编译库，比如Box2D，3D粒子系统等以加快编译速度。

该版本同时修复了大量的warning，后续版本也会持续修复warning。

### 去除支持一些平台

由于人力资源问题，改版本删除了一些平台的支持。

Windows 10的metro模式和Windows Phone平台一直是微软的员工在负责维护了，但是他们决定不再继续维护了，而我们人力资源不足，因此去除支持这两个平台。不过在Windows 10仍然可以使用Win32工程。

同样由于人力资源问题，该版本去除了Tizen平台的支持。


[1]: https://github.com/cocos2d/creator_to_cocos2dx
[2]: http://cocos2d-x.org/creator
[3]: https://github.com/cocos2d/creator_to_cocos2dx#limitations
[4]: https://raw.githubusercontent.com/minggo/Pictures/master/creator-ui-effect.png
[5]: https://raw.githubusercontent.com/minggo/Pictures/master/cocos2dx-ui-effect.png
[6]: https://raw.githubusercontent.com/minggo/Pictures/master/layerradialgradient.png
[7]: https://github.com/cocos2d/cocos2d-x-3rd-party-libs-bin/tree/v3/lua/luajit/prebuilt/ios "luajit.a"
