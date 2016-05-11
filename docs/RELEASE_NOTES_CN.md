# v3.11

## 新特性

* Chipmunk升级到v7.0.1
* JSB使用新的内存模型，在JS脚本不需要关心对象的生命周期，该特性默认关闭
* CURL升级到v7.48
* OpenSSL升级到v1.0.2g
* 可以使用VSCode或者新版本的Firefox调试JSB程序

## 主要特性的详细介绍

### JSB的新内存模型

使用新的内存模型后，开发者不需要关心对象的声明周期。这就意味着不需要在JS代码里手动调用`retain/release`函数。

不过该内存模型默认是关闭的。虽然我们已经做了很多的测试，但是还是无法保证它没有任何问题，所以你需要手动开启该功能，开启的方法是在`base/ccConfig.h`里把`CC_ENABLE_GC_FOR_NATIVE`的值改为1：

```c++
#ifdef CC_ENABLE_SCRIPT_BINDING
  #ifndef CC_ENABLE_GC_FOR_NATIVE_OBJECTS
  #define CC_ENABLE_GC_FOR_NATIVE_OBJECTS 1 // change to 1
  #endif
#endif
```

### OpenSSL
Cocos2d-x已经把__OpenSSL__升级到__1.0.2.g__。

从__2016年7月11__日开始，Google Play将不再接受使用低版本的__OpenSSL__的新应用程序或者应用程序更新。更新程序中使用的__OpenSSL__版本变得十分重要。更详细的信息可以参考[这个帖子](http://discuss.cocos2d-x.org/t/openssl-problem-again/28270)。

如果你使用的是v2.x或者低版本的v3.x引擎，那么你可以只更新__CURL__和__OpenSSL__，具体步骤如下：

* 修改__Cocos2d-x root/external/config.json__文件中的`version`字段。如果是v3.x的话，那么`version`字段的值改为`v3-dpes-92`，如果是v2.x的话，那么值是`v2-deps-5`
* 在Cocos2d-x根目录下执行__download-deps.py__脚本

```sh
(jtsm @ 15 ~) $ cd cocos2d-x

(jtsm @ 15 ~/cocos2d-x) $ ./download-deps.py

=======================================================
==> Prepare to download external libraries!
==> Ready to download 'v3-deps-92.zip' from 'https://github.com/cocos2d/cocos2d-x-3rd-party-libs-bin/archive/v3-deps-92.zip'
==> WARNING: Couldnt grab the file size from remote, use 'zip_file_size' section in '/Users/jtsm/Chukong-Inc/cocos2d-x/external/config.json'
==> Start to download, please wait ...
==> Downloading finished!
==> Extracting files, please wait ...
==> Extraction done! ==> Copying files...
==> Cleaning...
```
有任何问题可以在引擎的[中文论坛](http://forum.cocos.com/)上发帖反馈。

### Cocos2d-x JSB程序调试

v3.11版本之前，不能使用Firefox 30+版本来调试cocos2d-x JSB程序。这个版本修复了该问题，同时支持了web console功能。如果你不了解如何使用Firefox调试cocos2d-x JSB程序，可以参考[这篇文档](This documentation](http://www.cocos2d-x.org/wiki/Javascript_Remote_Debugging)。

当然你也可以使用[VSCode](https://code.visualstudio.com/)来调试，具体的使用方法参考[这篇文档](http://discuss.cocos2d-x.org/t/use-vscode-to-debug-cocos2d-x-jsb-programs/27588)。

## 其他改动
更完整的改动列表可以阅读[full changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)。
