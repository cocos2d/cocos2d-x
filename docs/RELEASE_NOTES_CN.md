<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.17.2 Release Notes](#cocos2d-x-3172-release-notes)
  - [版本变动](#%E7%89%88%E6%9C%AC%E5%8F%98%E5%8A%A8)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.17.2 Release Notes #

Cocos2d-x 3.17.2 侧重于稳定性的提升, 已有问题的修复和针对 OPPO 手机的性能优化。

## 版本变动

- 针对 OPPO 手机的性能优化
- 修复 bug：在安卓设备，当文件路径开头为 `assets/` 时， `FileUtils::listFiles()` 无法正常工作
- 修复了 Audio 在 iOS 设备上的崩溃问题
- 修复了在安卓设备， `VideoPlayer` 无法播放 OBB 包里的视频文件的问题

详细的改动请参考 [ChangeLog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)。
