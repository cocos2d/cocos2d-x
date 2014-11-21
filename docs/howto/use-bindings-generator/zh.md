
使用bindings-generator导出自定义C++类
================

> bindings-generator 是 cocos2d-x 3.x 提供的一套导出自定义C++类的工具。

Quick 能够直接使用bindings-generator工具，且使用方式和在cocos2d-x下使用的方式完全一样。

在使用之前，我们需要按照 tools/bindings-generator 目录下的 README.md 文件里的说明，配置好运行时需要的环境。

如果配置成功，运行 tools/tolua 目录下的 genbindings.py 将能够成功的重新生成 cocos/scripting/lua-bindings/auto 目录下的所有文件。

要导出自己定义的C++类，请参考以下文档：

[如何使用 bindings-generator 自动生成 lua绑定](http://cn.cocos2d-x.org/article/index?type=wiki&url=/doc/cocos-docs-master/manual/framework/native/wiki/how-to-use-bindings-generator/zh.md)
