quick-cocos2d-x-2048
====================

Copyright 涵曦

----

### 使用引擎quick-cocos2d-x

运行这个2048需要用到quick-cocos2d-x ， 直接把这个工程拷贝到quick的sample目录下就能用。

quick的地址 https://github.com/dualface/quick-cocos2d-x

### 关于logic.lua

2048游戏的逻辑实现，初始化游戏格子，上下左后四个操作。可以在lua控制台运行logic.lua，运行前找到最后一行取消注释。
```lua
-- main()
```
然后在控制台执行命令：

```
$ lua scripts/logic.lua
```

将会出现如下界面，即可在控制台玩游戏了，当初实现这一功能只是为了调试。
```
-------------------------------------
|   2    |        |   2    |        |
-------------------------------------
|        |        |        |        |
-------------------------------------
|        |        |        |   2    |
-------------------------------------
|        |        |        |        |
-------------------------------------
next step 'a'[←],'w'[↑],'s'[↓],'d'[→],'q'[exit] >>
```
### 关于MainScene.lua

#### cell的结构

1. 使用colorlayer画格子背景，保存为cell.background
2. 数字使用label，保存为cell.num

gridShow和grid一样，是一个二维数组，不同的是grid的元素存放的是数字2^n，gridShow存放的是cell结构。

#### onTouch处理用户触摸事件

将用户触摸事件转换为上下左右四个操作，然后调用logic.lua中的touch_op()函数。返回一个op_list用于转换gridShow。

只完成gridShow的setnum操作，最初预想的还有setpos和moveto两个操作可以让游戏更带感，但是没有实现。

### update.lua

更新脚本和资源模块，来自于：http://my.oschina.net/SunLightJuly/blog/180639

虽然它的功能主要是为了不重新下载安装包来更新游戏，但是还有一个很方便的功能：在调试安卓手机运行效果的时候很好用，如果每次只是修改了一两行lua代码就需要打包（或者用adt运行）那速度相当的慢，使用这个更新模块可以每次修改一点代码后需要查看运行效果，就重新启动一次资源更新服务器然后再重启客户端即可（内网传输一点点脚本总比用数据线传输一个apk快吧）。

如果想禁用update功能，只需要修改update.lua中的NEEDUPDATE为true
```
local NEEDUPDATE = true
```

### 资源更新服务pyhttp

因为暂时不需要考虑url中传参做到版本分发（update模块支持该功能），所以只是使用了python的SimpleHTTPServer来启动http服务。

如果要实现版本分发的更新服务器，请参考 https://github.com/hanxi/py_http

#### 使用方法：

1. 修改run.sh的第1条语句，将参数改为自己的相关目录即可。这是调用quick-cocos2d-x自带的打包工具，将scripts打包成update.zip

2. 第3条语句是启动http服务，端口可以改成自己想要的（记得和update.lua中的server变量同步）。

3. 执行下面的命令，第3个参数是版本号。每次更新后比更新之前大就行。
    ```
    $ sh run.sh 1.0.1
    ```

#### mkflist生成
update模块的作者用lua实现了一个，我感觉牵连的东西太多，就用python实现了。就是算出update.zip的md5然后用字符串拼一个flist出来。

计算md5之前需要将数据转成16进制的（不知道为何），所以实现了hexstr函数。

mkflist在run.sh的第2行被调用。
