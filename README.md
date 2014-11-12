Title: quick-cocos2d-x v3 README

quick-cocos2d-x v3
==================

quick-cocos2d-x v3 是在 cocos2dx 3.x 的最新版本基础之上，移植了原来 quick-cocos2d-x 的核心框架、强大的 player 、丰富的示例等，并增加更多新的功能。

> 当前版本为RC版

RC 版本是正式发布 Release 版本之前的准备版本。与正式版本相比，主要区别在于部分功能可能会在正式版中有所调整。但所有核心功能和主要 API 都已经稳定。

~

## 使用指南

### 下载与安装

quick 在每一个主要版本发布时提供两种版本：

-   安装包（含源代码）
    
    安装包可以快速完成一些基本设置，并包含编译好的 player 执行文件，简化了安装配置步骤。只需要下载 quick 安装包后，按照安装程序的提示进行操作即可。如果是 Mac 系统，建议先安装好 Xcode 开发工具。

    访问 [http://cn.cocos2d-x.org/](http://cn.cocos2d-x.org/) 下载安装包。

-   源码包

    下载解压缩后，运行 setup_mac.sh 或者 setup_win.bat 配置环境。需要开发者自行编译 player 执行文件。

    访问 [https://github.com/dualface/v3quick/releases](https://github.com/dualface/v3quick/releases) 下载源码包。

    访问 [https://github.com/dualface/v3quick](https://github.com/dualface/v3quick) 查看 quick 源代码仓库。

~

### 快速开始

quick-cocos2d-x 中带有一个名为 player 的工具。

![](docs/res/player.png)

这个工具不但是一个功能完善的模拟器，可以在 Mac/Windows 桌面运行开发者的游戏，还是一个功能齐备的开发工具入口。

开发者启动 player 后，将可以完成下列任务：

-   创建项目
-   打开项目
-   查看示例

未来，我们还将增加更多功能。

现在就下载安装 quick，然后启动 player3.app 或 player3.exe 查看 quick 中那些精彩的示例程序吧。

~

### 使用指南

-    [player 使用说明](docs/howto/player-user-manual/zh.md)
-    [在 Code IDE 中调试 quick 工程](docs/howto/use-codeide/zh.md)
-    [用 CCSLoader 读取 Cocos Studio 输出的场景/UI 文件](docs/howto/use-ccsloader/zh.md)
-    [在 Windows Phone 8 中运行 quick](docs/howto/run-on-wp8/zh.md)
-    [编译 player 执行文件](docs/howto/compile-player/zh.md)
-    [编译 Android 工程](docs/howto/compile-android/zh.md)
-    [升级到 quick-cocos2d-x 最新版](docs/howto/upgrade/zh.md)

~

### 参考手册

-    [quick 中的事件](docs/manual/events/zh.md)
-    [quick 中的触摸事件](docs/manual/touch-events/zh.md)
-    [API 文档](docs/api/index.md)

~

### 历史版本

beta 版本各主要功能已经完成，其中包括新的纯 lua 滚动控件、ccsloader、对 Cocos Code IDE 的支持、模块裁减等。API 已经稳定，相关文档正在补充。同时正在清理可能的 BUG。

alpha3 版提供了 3D 精灵示例；新增了几个滚动组件，已在 UI 示例中加入了相关的展示；另外还有一些功能的修改与补充，以及脚本绑定工具的整合等。

alpha2 版合并了 cocos2d-x3.2 版本核心引擎；完善了单点及多点触摸机制，并提供了相应的示例；为 Anysdk 封装了 Lua 接口，并提供了相应的示例；修改了1版中 player 的一些问题；增补和修改了一些框架接口及底层功能。

alpha1 版已经完成了大部分基本框架的移植工作；提供了 MAC 版本的 player；已经有多个完整的示例，可以在 player 中直接运行和调试；创建自己的工程，将游戏快速布署到 IOS 及 Android 设备上。
