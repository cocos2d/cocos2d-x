<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [v3.14.1](#v3141)
  - [修复的问题](#%E4%BF%AE%E5%A4%8D%E7%9A%84%E9%97%AE%E9%A2%98)
  - [其他](#%E5%85%B6%E4%BB%96)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# v3.14.1

## 修复的问题

* 如果创建物理场景但是没有设置3d物理的摄像机，那么程序会崩溃
* 由于glfw版本冲突，在linux平台可能会有链接错误
* 通过带有多边形信息的sprite frame创建的Sprite效果不对
* VS2015编译Lua工程时有链接错误
* 通过`cocos compile/run -p android --android-studio`命令编译Android工程时会有编译错误

## 其他

通过查看[3.14.1版本信息](https://github.com/cocos2d/cocos2d-x/milestone/36?closed=1)了解所有的问题或者代码改动。