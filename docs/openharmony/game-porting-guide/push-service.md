# 推送服务

## 业务简介
推送服务（Push Kit）是华为提供的消息推送平台，建立了从云端到终端的消息推送通道。您通过集成推送服务，可以向客户端应用实时推送消息，构筑良好的用户关系，提升用户的感知度和活跃度。

推送服务OpenHarmony SDK为您的应用开发提供推送消息相关的接口，适用于OpenHarmony手机。主要包含根据多种受众用户推送通知栏消息等功能。

## 开发环境

- JDK 1.8及以上

- 安装合适版本HUAWEI DevEco Studio

- HarmonyOS SDK API Version 9




## 开发流程
| 开发步骤  |说明   |
|---|---|
| 准备开发环境  |在开发HarmonyOS应用前，需要准备HarmonyOS应用的开发环境。 |
|配置AppGallery Connect  |在AppGallery Connect中创建HarmonyOS应用、开通推送服务并且设置数据处理位置。   |
| 配置应用签名信息  | HarmonyOS通过数字证书和Profile文件来对应用进行管控，您需要生成证书文件并且在AppGallery Connect上配置HarmonyOS应用的SHA256指纹。 |
| 集成HMS Core SDK | 在DevEco Studio中添加配置文件，集成推送服务SDK。 |
| 获取Token | 获取接入推送服务的Token。  |
| 发送消息  | 您可以通过服务端API向OpenHarmonyOS应用推送消息。  |



## 应用开发

#### 获取Push Token

Token是推送令牌，每个设备上的每个应用的Token都是唯一存在的，客户端调用getToken方法向Push服务端请求应用的Token，您可以根据Push服务端返回的Token向应用推送消息。


#### 自定义点击消息动作
您可以自定义点击通知栏消息的动作，例如：打开应用首页和打开应用自定义页面。
