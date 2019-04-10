<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.17.1 Release Notes](#cocos2d-x-3171-release-notes)
  - [版本变动](#%E7%89%88%E6%9C%AC%E5%8F%98%E5%8A%A8)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.17.1 Release Notes #

Cocos2d-x 3.17.1 侧重于稳定性的提升, 已有问题的修复。

## 版本变动

- 修复 3.17 引入的 Lua 加载性能下降的 BUG
- 减少渲染中 glClear 的调用次数，降低电量消耗
- CMake 脚本优化，解决存在的链接问题
- Android 默认启用 CMake 方式编译
- Android 升级 Gradle 到 4.6, SDK 28, plugin 3.1.0 
- 升级 LuaJIT 到 2.1.0-beta3，修复 3.17 Lua 项目的闪退问题
- 升级 libwebsockets 到 2.4.2
- FileUtils 内部加锁，增加线程安全，完善接口实现
- 限制 Label 长度，避免绘制错误
- 增加 Downloader 的 Lua 绑定

当前版本包含 45 项 bugs 修复和 34 项小改进，不再列举，请参考 [ChangeLog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)。
