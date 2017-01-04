<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [v3.14](#v314)
  - [新特性](#%E6%96%B0%E7%89%B9%E6%80%A7)
  - [特性详细介绍](#%E7%89%B9%E6%80%A7%E8%AF%A6%E7%BB%86%E4%BB%8B%E7%BB%8D)
    - [所有平台使用luajit 2.10-beta2](#%E6%89%80%E6%9C%89%E5%B9%B3%E5%8F%B0%E4%BD%BF%E7%94%A8luajit-210-beta2)
    - [Sprite支持九宫格特性](#sprite%E6%94%AF%E6%8C%81%E4%B9%9D%E5%AE%AB%E6%A0%BC%E7%89%B9%E6%80%A7)
    - [支持Spine二进制格式](#%E6%94%AF%E6%8C%81spine%E4%BA%8C%E8%BF%9B%E5%88%B6%E6%A0%BC%E5%BC%8F)
    - [新增加动作类](#%E6%96%B0%E5%A2%9E%E5%8A%A0%E5%8A%A8%E4%BD%9C%E7%B1%BB)
  - [已知问题](#%E5%B7%B2%E7%9F%A5%E9%97%AE%E9%A2%98)
  - [其他](#%E5%85%B6%E4%BB%96)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# v3.14

## 新特性

* 支持Spine二进制格式
* 所有平台使用luajit 2.10-beta2
* 新增动作类：`ResizeBy`和`ResizeTo`
* Android模拟支持关闭多点触摸
* Sprite支持九宫格特性
* 动作类新增功能，可以根据tag查询某一节点正在运行的动作数量
* Button类可以设置title内容
* EditBox支持文本水平对齐
* 支持Mac平台手柄

## 特性详细介绍

### 所有平台使用luajit 2.10-beta2

之前的luajit版本无法在PC上方便地编译出arm64的字节码，需要用真机（比如iPhone6真机)编译，因此在之前的版本，iOS 64位使用的是lua，iOS 32位使用的是luajit。

luajit 2.10-beta2版本，可以方便地在PC平台编译出arm64位的字节码，因此我们在各平台都使用了luajit，这样能够提升性能。如果使用cocos命令编译、打包的话，那么cocos命令会自动编译出对应平台的字节码，如果有生成64位字节码的话，那么会把这些字节码放到`64-bit`目录下。当然你也可以通过`cocos luacompile`自己编译字节码，具体的使用方式可以参考`cocos luacompile -h`输出的帮助信息。

通过cocos命令编译、打包生成的字节码时各平台的情况如下：

平台 | 生成32位字节码 | 生成64位字节码 |
---|---|---
iOS | 是 | 是
Android | 是，如果APP\_ABI的内容不是只包含64位架构(`APP_ABI := arm64-v8a`) | 是，如果APP\_ABI包含了64位架构，比如`APP_ABI := arm64-v8a ...`
Mac | 否 | 是
Windows | 是 | 否
Linux | 否 |否

### Sprite支持九宫格特性

Sprite现在支持九宫格特性了，使用方式如下

```c++
auto sprite = Sprite::create(...);
// set center rect
// the origin is top-left
sprite->setCenterRectNormalized(Rect(x, y, width, heigh));
```

详细信息可以参考`Sprite::setCenterNormalized()`的注释。

![sprite-slice](https://raw.githubusercontent.com/minggo/Pictures/master/sprite-slice.png)

### 支持Spine二进制格式

使用方式没有改变，只是文件格式变成了二进制格式。这样的好处就是解析效率更高，文件更小。具体的使用方法如下：

```c++
skeletonNode = SkeletonAnimation::createWithBinaryFile("spine/spineboy.skel", "spine/spineboy.atlas", 0.6f);

...
```

![spine-binary](https://raw.githubusercontent.com/minggo/Pictures/master/spine-binary.png)

### 新增加动作类

新增加两个动作类：`ResizeBy`和`ResizeTo`。和`ScaleBy`、`ScaleTo`不同的是，`ResizeBy`和`ResizeTo`改变的是节点的content size的大小。这种动作对于支持九宫格特性的节点的缩放效果比`ScaleBy`和`ScaleTo`好，因为`ScaleBy`和`ScaleTo`是对节点做整体缩放。效果对比如下：

![resize-action-effect](https://raw.githubusercontent.com/minggo/Pictures/master/resize-action-effect.png)

## 已知问题

如果使用Xcode 8.2，那么lua工程会在iOS模拟器上崩溃。通过调试发现崩溃在`lua_open`函数的调用上。如果使用Xcode 8.1或一下版本，那么没有问题。我们怀疑这是Xcode的bug，在v3.14无法解决。使用lua的开发者在位iOS平台开发时有两个选择：

* 使用Xcode 8.1或者一下版本
* 使用Xcode 8.2，在Mac或者iOS真机开发、调试

该问题的进展可以跟踪[这个issue](https://github.com/cocos2d/cocos2d-x/issues/17043)。

## 其他

[详细的改动内容](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)。