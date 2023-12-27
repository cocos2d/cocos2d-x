# 网络

以cocos-2dx 3.17.2 版本为参考：
整个网络相关核心代码在cocos/network目录下。
首先需要完成对应版本curl，websocket 等三方库的编译。
然后检查cocos/network/cmakelists.txt,保证编译时走非android，非apple分支。
最终在鸿蒙上使用的是curl库的网络能力。代码基本上不需要额外修改。
