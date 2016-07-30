<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [v3.12](#v312)
  - [新特性](#%E6%96%B0%E7%89%B9%E6%80%A7)
  - [主要特性的详细介绍](#%E4%B8%BB%E8%A6%81%E7%89%B9%E6%80%A7%E7%9A%84%E8%AF%A6%E7%BB%86%E4%BB%8B%E7%BB%8D)
    - [VR支持](#vr%E6%94%AF%E6%8C%81)
    - [Tizen支持](#tizen%E6%94%AF%E6%8C%81)
    - [提高Android渲染效率](#%E6%8F%90%E9%AB%98android%E6%B8%B2%E6%9F%93%E6%95%88%E7%8E%87)
    - [提升Cocos2d-html5引擎WebGL模式下的性能](#%E6%8F%90%E5%8D%87cocos2d-html5%E5%BC%95%E6%93%8Ewebgl%E6%A8%A1%E5%BC%8F%E4%B8%8B%E7%9A%84%E6%80%A7%E8%83%BD)
    - [Android使用clang编译器](#android%E4%BD%BF%E7%94%A8clang%E7%BC%96%E8%AF%91%E5%99%A8)
  - [其他改动](#%E5%85%B6%E4%BB%96%E6%94%B9%E5%8A%A8)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# v3.12

## 新特性

* 支持VR，目前还处于测试阶段
* 支持Tizen平台
* 提升引擎在Android平台的渲染效率
* 提升Cocos2d-html5 WebGL模式的性能
* 支持Android的OBB扩展格式
* Android平台使用clang编译器，使用NDK r11+

## 主要特性的详细介绍

### VR支持

该版本添加了VR支持，不过还处于测试阶段。目前支持的设备有__Google Cardboard__，__Oculus Rift__，__Samsung Gear__和__Deepoon E2__。关于如何使用、测试VR功能，请参考[Programming Guide](http://cocos2d-x.org/docs/programmers-guide/vr/index.html)。

### Tizen支持

该版本添加了Tizen平台的支持。支持的TizenSDK版本是__2.4__。开发Tizen平台应用时，需要使用Tizen平台有自己的IDE和模拟器。请参考[这篇文档](http://cocos2d-x.org/docs/installation/Tizen/)了解如何搭建Tizen应用开发环境。

### 提高Android渲染效率

这里要多谢社区的开发者帮忙在各种Android设备上测试、验证性能问题。这个问题的原因是因为引擎默认创建了一个比较大的map buffer，实际需要传到该map buffer的数据并没有那么多。但是在有些Android设备，不管实际数据大小是多少，每次都传输和map buffer大小一样多的数据。

通过代码解释如下：

```c++
// 初始化map buffer
glBindBuffer(GL_ARRAY_BUFFER, BUFFER_ID);
glBufferData(GL_ARRAY_BUFFER, 65536, xxx , GL_DYNAMIC_DRAW);
```

具体使用map buffer的代码是

```c++
// 实际使用map buffer
glBindBuffer(GL_ARRAY_BUFFER, BUFFER_ID);
// 虽然只需要传输100个元素，但是在某些Android机器上仍然传输65536个元素
glBufferData(GL_ARRAY_BUFFER, 100, xxx , GL_DYNAMIC_DRAW);
```

详细的讨论可以参考[这个github issue](https://github.com/cocos2d/cocos2d-x/issues/15652)。

### 提升Cocos2d-html5引擎WebGL模式下的性能

该版本大幅提升了Cocos2d-html5引擎在WebGL模式下的性能。引擎的渲染性能、CPU使用量和内存大小都有提升。

![rendering peformance](https://raw.githubusercontent.com/minggo/Pictures/master/web-performance-improve/adverage-time-per-frame.png)

![cpu-usage](https://raw.githubusercontent.com/minggo/Pictures/master/web-performance-improve/cpu-usage.png)

![memory-usage](https://raw.githubusercontent.com/minggo/Pictures/master/web-performance-improve/memory-usage.png)

### Android使用clang编译器

[从NDK r11开始Google弃用了gcc](https://developer.android.com/ndk/downloads/revision_history.html)，所以cocos2d-x也切换到clang编译器。

建议使用NDK r11c。在测试过程中发现，如果使用NDK r10c + clang的话，`Node::enumerateChildren()`会崩溃。

## 其他改动
更完整的改动列表可以阅读[full changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)。
