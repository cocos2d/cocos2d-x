<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.17.1 Release Notes](#cocos2d-x-3171-release-notes)
  - [版本变动](#%E7%89%88%E6%9C%AC%E5%8F%98%E5%8A%A8)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.17.1 Release Notes #

Cocos2d-x 3.17.1 修复BUG,提升了稳定性,增强了CMake的易用性。

## 版本变动

- Renderer减少glClear调用次数，可以减少电量消耗
- CMake脚本优化，解决部分链接问题
- Android默认启用CMake方式编译
- Android升级gradle到4.6, sdk 28, android gradle plugin 3.1.0 
- 升级luajit到2.1.0-beta3，减少3.17的闪退问题
- 升级libwebsocket到2.4.2
- FileUtils内部加锁，增加线程安全，完善接口实现
- 限制Label长度为，避免绘制错误
- 增加Downloader的LUA绑定

当前版本包含43项bugs修复和34项小改进，不再列举，请参考[ChangeLog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)。
