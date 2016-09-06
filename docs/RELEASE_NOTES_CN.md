<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [v3.13.1](#v3131)
  - [Bug修复](#bug%E4%BF%AE%E5%A4%8D)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# v3.13.1

## Bug修复

* Label的颜色错误问题
* 在Android系统，如果通过点击应用图标从后台推前台，可能导致崩溃
* 在Android系统，如果音乐或音效资源不在APK包里，会导致无法播放
* 在Android系统，AudioEngine::stop()会回调`finish`回调函数
* JSB中，如果传入object.setString()的参数类型是数字，没有任何效果

对应的github issue可以从[这里](https://github.com/cocos2d/cocos2d-x/milestone/33)找到
