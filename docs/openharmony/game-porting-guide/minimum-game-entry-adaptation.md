# 引擎最小化移植思路

​游戏引擎最小化移植目标主要是需要将引擎自带的最简单的demo可以在OpenHarmony平台运行起来, 比如 cocos 的helloworld 工程demo,为了实现这一目标，可以分离为一下几步

1. 解决编译问题
2. 最小化平台依赖接口适配
3. 图像渲染适配

## 引擎C++代码编译

一般游戏引擎都是C++编写所以我们需要将游戏引擎的C++代码能够编译起来，Openharmony 提供的NDK支持Cmake进行编译，可以参考 **使用NDK编译一个Cmake C/C++工程文档** https://gitee.com/openharmony/docs/pulls/18759



## 最小化平台依赖接口适配

游戏引擎最小化平台接口主要涉及到 log系统，和文件访问系统的对接

- log系统的对接参考: https://gitee.com/openharmony-sig/cocos2dx/blob/cocos2d-x-3.17.2-ohos/docs/game-porting-guide/log-collection.md
- 日志访问系统的对接参考: https://gitee.com/openharmony-sig/cocos2dx/blob/cocos2d-x-3.17.2-ohos/docs/game-porting-guide/file-operation.md



## 图像渲染适配

图像渲染适配可以参考 https://gitee.com/openharmony-sig/cocos2dx/blob/cocos2d-x-3.17.2-ohos/docs/game-porting-guide/image-rendering.md