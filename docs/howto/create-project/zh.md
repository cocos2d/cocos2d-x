
#创建工程

======

### 通过 `Player` 创建工程:

1. 运行 `Player` ,点击 `新建工程`
2. 选择新工程的参数, 点击 `Create Project` ,会弹出一个命令窗口来创建

 ![](res/create_project.png)


### 通过命令窗口创建工程:

1. 打开命令窗口
2. 进到 `quick/bin` 目录
3. 输出 `./create_project.sh -p com.quick.quickTest` 创建一个包名为 `com.quick.quickTest` 的工程
4. `create_project.sh` 的更多参数可以输出 `./create_project.sh -h` 来了解

`create_project.sh` 的参数:
I
- -h show help
- -p package name
- -o project path (default is "current_dir/last_package_name")
- -r screen orientation (default is "portrait")
- -np dont create project files for platform
- -op only create project files
- -f overwrite exists files
- -c load options from config file
- -q quiet
- -t template dir
- -e extra cmd for cocos


##### windows的用法相似,把 `XXX.sh` 替换为 `XXX.bat`




