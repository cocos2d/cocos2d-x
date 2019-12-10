<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x v4 Release Notes](#cocos2d-x-v4-release-notes)
  - [版本特性](#%E7%89%88%E6%9C%AC%E7%89%B9%E6%80%A7)
  - [文档](#%E6%96%87%E6%A1%A3)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x v4 Release Notes #

## 版本特性

- iOS/macOS 支持 metal
- 使用 CMake，删除各平台的工程文件
- 升级 GLFW 到 3.3
- 升级 minizip 到 1.2
- 删除废弃函数
- 删除 h5 引擎和 Javascript 绑定
- 删除 tiff
- 删除 `SimpleAudioEngine`
- 删除 `experimental` 名字空间
- 修复 macOS 15 系统字体绘制问题
- 适配 iOS13
  - UIWebView 使用 WKWebView 实现
  - VideoPlayer 使用 AVPlayerController 实现
- 修复 lua 工程在 64 位设备的崩溃问题

## 文档

编写了一些文档方便开发者升级到 v4:
- [如何运行测试例子，如何新建工程并运行](https://docs.cocos2d-x.org/cocos2d-x/v4/zn/installation)
- [v4 升级指南](https://docs.cocos2d-x.org/cocos2d-x/v4/zh/installation/)
