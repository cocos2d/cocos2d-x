# 三方SDK导入

三方SDK的实现依赖于npm，因此您需要了解和掌握npm的基础功能和机制，可通过[npm官方文档](https://docs.npmjs.com/about-npm)进行了解。

引用npm三方包，包括从npm仓库进行安装和从本地npm模块中进行安装两种方式。

- 引用npm仓中的包，首先需要设置npm三方包的仓库信息，请在DevEco Studio的Terminal窗口执行如下命令进行设置：

  ```
  npm config set @ohos:registry=https://repo.harmonyos.com/npm/
  ```

  然后通过如下两种方式设置npm三方包依赖信息：

  - 方式一：在Terminal窗口中，执行如下命令安装npm三方包，DevEco Studio会自动在工程的package.json中自动添加三方包依赖。

    ```
    npm install @ohos/vcard --save
    ```

  - 方式二：在工程的package.json中设置npm三方包依赖，配置示例如下：

    ```
    "dependencies": {  "@ohos/vcard": "^2.1.0"}
    ```

    依赖设置完成后，需要执行npm install命令安装依赖包，依赖包会存储在工程的node_modules目录下。

    ```
    npm install
    ```

- 引用本地npm模块的文件和资源，有如下两种方式：

  - 方式一：在Terminal窗口中，执行如下命令进行安装，并会在package.json中自动添加依赖。

    ```
    npm install ../library --save
    ```

  - 方式二：在工程的package.json中设置npm三方包依赖，配置示例如下：

    ```
    "dependencies": {  "@ohos/library": "file:../library"}
    ```

    依赖设置完成后，需要执行**npm install**命令安装依赖包，依赖包会存储在工程的node_modules目录下。

    ```
    npm install
    ```

在引用npm包时，请注意以下事项：

- 当前只支持在模块和工程下的package.json文件中声明dependencies依赖，才会被当做OpenHarmony依赖使用，并在编译构建过程中进行相应的处理。
- 引用的模块的compileSdkVersion不能低于其依赖的npm三方包（可在node_modules目录下，找到引用的npm包的src > main > module.json5 中查看）。