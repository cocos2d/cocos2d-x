Title: 编译 player 执行文件

编译 player 执行文件
==================

如果开发者有需要，可以自行编译 player 执行文件。

~

## 在 Mac 下编译 player 执行文件

在编译前，请检查下列准备工作已经完成：

-   安装了最新版 Xcode，并在启动 Xcode 后完成了附加组件的安装
-   运行 setup_mac.sh 完成了环境配置

完成上述准备工作后：

1.  用 Xcode 打开 quick/player/proj.mac/player3.xcodeproj 工程文件
2.  编译
3.  编译成功后，在 Project Navigator 中展开 `Products`，右键点击 `player.app` 选择菜单 `Show in Finder` 即可看到编译好的 player 执行文件。

~

## 在 Windows 下编译 player 执行文件

在编译前，请检查下列准备工作已经完成：

-   安装了 Visual Studio 2012 或 Visual Studio 2013 版（强烈推荐 2013，编译速度明显提升）
-   运行 setup_win.bat 完成了环境配置

完成上述准备工作后：

1.  用 Visual Studio 打开 quick/player/proj.win32/player3.sln 工程文件
2.  编译
3.  编译成功后，在 `quick/player/proj.win32/Debug` 目录中即可看到编译好的 player 执行文件。
