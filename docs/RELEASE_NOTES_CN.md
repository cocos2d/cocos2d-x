<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [v3.15](#v315)
  - [新特性](#%E6%96%B0%E7%89%B9%E6%80%A7)
  - [新特性详细介绍](#%E6%96%B0%E7%89%B9%E6%80%A7%E8%AF%A6%E7%BB%86%E4%BB%8B%E7%BB%8D)
    - [全面支持Android Studio](#%E5%85%A8%E9%9D%A2%E6%94%AF%E6%8C%81android-studio)
    - [音频模块在Android平台的改进](#%E9%9F%B3%E9%A2%91%E6%A8%A1%E5%9D%97%E5%9C%A8android%E5%B9%B3%E5%8F%B0%E7%9A%84%E6%94%B9%E8%BF%9B)
    - [去除Windows 8.1的支持](#%E5%8E%BB%E9%99%A4windows-81%E7%9A%84%E6%94%AF%E6%8C%81)
    - [去除32位linux支持](#%E5%8E%BB%E9%99%A432%E4%BD%8Dlinux%E6%94%AF%E6%8C%81)
    - [其他](#%E5%85%B6%E4%BB%96)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# v3.15

## 新特性

* 全面支持 __Android Studio__，包括编译、代码编辑和调试C++代码：[使用文档](https://github.com/chukong/cocos-docs/blob/v3-unified-documentation/installation/Android-Studio.md)
* 音频模块在Android平台使用[tremolo](http://wss.co.uk/pinknoise/tremolo/)和 __MP3 Decoder Library__ 解码音频文件，使得音频模块效率更高，兼容更多的Android设备
* __WebSockets__ 和 __SocketIO__ 支持 __SSL__
* AssetsManagerEx更加稳定
* 更新 __Spine runtime__ 到v3.5.35
* 更新 __flatbuffer__ 到v1.5
* 升级 __OpenSSL__ 到v1.1.0
* 去除 __Windows 8.1__ 的支持
* 去除32位linux的支持


## 新特性详细介绍

### 全面支持Android Studio

从 __3.15__ 版本开始，可以使用Android Studio 2.3+ 编辑、编译和调试C++代码。只需要通过Android Studio打开 __proj.android-studio__ 文件夹（比如 __tests/cpp-empty-test/proj.android-studio__ ），然后点击 __run__ 按钮就可以在Android设备或者模拟器运行、调试了。

详细的使用方法请参考[这篇文档](https://github.com/chukong/cocos-docs/blob/v3-unified-documentation/installation/Android-Studio.md)。

### 音频模块在Android平台的改进

3.15版本之前，音频模块使用 __OpenSL ES__ 解码、播放音频文件，但是很多的Android设备厂商会修改这部分代码，导致音频模块在不同的Android设备上有兼容性问题。[该帖子](http://discuss.cocos2d-x.org/t/android-audio-decoding-issues-discussion/34610)就列出了许多音频模块的问题。

为了解决兼容性问题，我们引入了第三方的解码库[tremolo](http://wss.co.uk/pinknoise/tremolo/)和 __MP3 Decoder Library__ 。该解码库也是Android源码使用的解码库。使用该解码库除了能解决Android设备的兼容性问题，同时还带来了不少性能提升：

![audio performance](https://raw.githubusercontent.com/minggo/Pictures/master/AudioDecodingPerfTest.png)

引入该解码库会使最终的APK包增大100K左右，和带来的好处相比还是值得的。

### 去除Windows 8.1的支持

Windows 8.1的支持一直是微软的开发者在维护。因为市场占有率原因，微软觉得没必要继续支持Windows 8.1了。

### 去除32位linux支持

目前大部分的PC都是64位了，所以我们觉得去除对32位linux的支持。去除这个支持意味着第三方库去掉了对应的32位版本，这样可以减小发行包的大小，也减少引擎维护的工作。开发者如果想支持32位版本的话，可以使用[这个仓库](https://github.com/cocos2d/cocos2d-x-3rd-party-libs-src)自己编译32位版本的第三方库。

### 其他

[Android SDK Tools 25.3.0+](http://tools.android.com/recent/androidsdktoolsrevision2530feb2017)去除了 __ant脚本__ 和 __android命令__ ，使得cocos命令无法打包Android的Eclipse工程（proj.android）。为了不至于在最后生成APK时才报错，现在cocos命令检查到这个版本后直接返回错误。有两个方法可以解决这个问题：

* 从旧版本的Android SDK拷贝tools文件夹过来替换对应的目录
* 使用Android Studio工程编译打包

从Android工具删除ant脚本和android的行为来看，谷歌是不希望大家继续使用Eclipse工程，所以建议大家还是使用Android Studio来编译打包吧。旧版本引擎虽然不支持Android Studio调试C++代码功能，但是编译打包还是没问题的。
