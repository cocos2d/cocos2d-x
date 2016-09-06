<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [v3.13](#v313)
  - [新特性](#%E6%96%B0%E7%89%B9%E6%80%A7)
  - [主要特性的详细介绍](#%E4%B8%BB%E8%A6%81%E7%89%B9%E6%80%A7%E7%9A%84%E8%AF%A6%E7%BB%86%E4%BB%8B%E7%BB%8D)
    - [增加VR插件](#%E5%A2%9E%E5%8A%A0vr%E6%8F%92%E4%BB%B6)
    - [支持ETC1 alpha通道](#%E6%94%AF%E6%8C%81etc1-alpha%E9%80%9A%E9%81%93)
    - [AudioEngin性能提升](#audioengin%E6%80%A7%E8%83%BD%E6%8F%90%E5%8D%87)
    - [脏矩形算法](#%E8%84%8F%E7%9F%A9%E5%BD%A2%E7%AE%97%E6%B3%95)
    - [支持Android 64位应用](#%E6%94%AF%E6%8C%81android-64%E4%BD%8D%E5%BA%94%E7%94%A8)
    - [Android切换回gcc 4.9](#android%E5%88%87%E6%8D%A2%E5%9B%9Egcc-49)
    - [CURL升级到7.50.0](#curl%E5%8D%87%E7%BA%A7%E5%88%B07500)
  - [其他改动](#%E5%85%B6%E4%BB%96%E6%94%B9%E5%8A%A8)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# v3.13

## 新特性

* 增加了VR插件，包括**GearVR**、**GVR(Cardboard和Daydream)**、**DeepoonVR**和**OculusVR**
* 支持ETC1 alpha通道
* 解决了AudioEngin的性能问题，在Android 4.2+有效
* 通过脏矩形算法提升Canvas渲染器性能
* 支持Android 64位应用
* 集成[AnySDK][1]
* Android切换回gcc 4.9
* CURL升级到7.50.0
* Spine升级到3.4
* GLFW升级到3.2

## 主要特性的详细介绍

### 增加VR插件

支持了Gear、Deepon、Google Cardboard和Oculus插件。具体的使用方法可以参考[Programmers Guide](http://www.cocos2d-x.org/docs/programmers-guide/vr/index.html)。

### 支持ETC1 alpha通道

感谢[halx99](https://github.com/halx99)的贡献，cocos2d-x支持ETC1 alpha通道。

要想使用ETC1 alpha通道，必须在相同目录下提供`xxx.pkm`和`xxx.pkm@alpha`，代码使用方法如下：

```c++
auto sprite = Sprite::create("xxx.pkm");
```

引擎会自动去加载`xxx.pkm@alpha`作为alpha通道数据。更详细的使用方式请参考`tests/cpp-tests/Classes/SpriteTest/SpriteTest.cpp`里的`Sprite1ETC1Alpha `测试例子。

![](https://raw.githubusercontent.com/minggo/Pictures/master/etc1-alpha.png)

图中蓝色部分就是带alpha通道的ETC1图片。

### AudioEngin性能提升

Android平台下，AudioEngine使用[OpenSL ES](https://developer.android.com/ndk/guides/audio/opensl-for-android.html)播放声音。从Android 4.2开始，OpenSL ES支持解码声音文件为PCM数据，引擎正是利用这个以特性来缓存解码后数据以提升性能。因此，该性能提升只在Android 4.2及以上版本有效。**需要先preload，否则第一次播放性能没有很大提升**。


![](https://raw.githubusercontent.com/minggo/Pictures/master/audio/audio-performance1.png)

![](https://raw.githubusercontent.com/minggo/Pictures/master/audio/audio-performance2.png)

![](https://raw.githubusercontent.com/minggo/Pictures/master/audio/audio-performance3.png)

### 集成[AnySDK][1]

[AnySDK][1]为CP商提供一套第三方SDK接入解决方案，整个接入过程，不改变任何SDK的功能、特性、参数等，对于最终玩家而言是完全透明无感知的。支持的第三方SDK包括**渠道SDK**、**用户系统**、**支付系统**、**广告系统**、**统计系统**、**分享系统**等。

可以通过如下方法集成[AnySDK][1]

```
cocos package import anysdk -p PROJECT_PATH --anysdk
```

`PROJECT_PATH`是游戏工程的根目录，比如`COCOS2DX_ROOT/tests/cpp-empty-test`。

通过上面命令后，[AnySDK][1]框架就集成到了游戏项目中，可以在代码里调用AnySDK接口接入各种第三方SDK了。[AnySDK][1]的详细介绍和使用方法请参考[AnySDK][1]官网。

### 脏矩形算法

在v3.12中我们通过重构WebGL渲染器大幅度提升了Web引擎的性能，在这个版本中，我们又实现了脏矩形算法来提升Canvas渲染器的性能。脏矩形算法允许引擎只渲染当前帧中和前一帧不同的区域，而不是渲染整个画布，大大降低填充率，可以同时带来渲染效率的提升以及CPU使用率和耗电量的降低。对于相对静态的游戏画面来说，非常有效。这个功能默认是关闭的，开启它可以通过下面的代码：

```
// 开启脏矩形算法
if (cc._renderType === cc.game.RENDER_TYPE_CANVAS) {
    cc.renderer.enableDirtyRegion(true);
    // 设置允许用脏矩形算法进行局部渲染的最高脏矩形数量
    cc.renderer.setDirtyRegionCountThreshold(6);
}
// 检查脏矩形算法是否开启
var enabled = isDirtyRegionEnabled();
```

### 支持Android 64位应用

该版本提供了Android 64位的第三方库，因此可以编译出64位的Android应用。可以使用如下命令编译、运行64位Android程序：

```
cocos run -p android --app-abi arm64-v8a
```

### Android切换回gcc 4.9

cocos2d-x 3.12时使用了clang编译器，结果发现了[崩溃问题](https://github.com/cocos2d/cocos2d-x/issues/16244)。通过测试发现该问题是由于使用`clang + gnustl_static`造成的，因此该版本切换回使用gcc 4.9。当`c++_static`稳定后再切换成clang。

### CURL升级到7.50.0

CURL 7.50.0解决了[在NAT64环境连接IPV4地址格式的IP地址错误](https://github.com/curl/curl/issues/863)问题，因此引擎及时升级了CURL版本。

## 其他改动
更完整的改动列表可以阅读[full changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)。

[1]: http://www.anysdk.com/
