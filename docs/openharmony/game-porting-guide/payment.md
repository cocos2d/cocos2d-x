# 应用内支付

## 业务简介
IAP SDK JS ForHarmony是适配OpenHarmony应用的SDK，为App提供便捷的应用内支付体验和简便的接入流程。您的App通过集成IAP SDK，再调用IAP SDK接口启动IAP收银台，即可实现应用内支付。

## 开发环境

- JDK 1.8及以上
- 安装HUAWEI DevEco Studio 3.0.0.901及以上
- HarmonyOS SDK API Version 9
- 测试设备：HarmonyOS手机


## 开发流程
| 开发步骤  |说明   |
|---|---|
| 准备开发环境  |在开发HarmonyOS应用前，需要准备HarmonyOS应用的开发环境。 |
|配置AppGallery Connect  |在AppGallery Connect中创建HarmonyOS应用、开通推送服务并且设置数据处理位置。   |
| 配置应用签名信息  | HarmonyOS通过数字证书和Profile文件来对应用进行管控，您需要生成证书文件并且在AppGallery Connect上配置HarmonyOS应用的SHA256指纹。 |
| 集成HMS Core SDK | 在DevEco Studio中添加配置文件，集成应用内支付SDK。 |
| 配置商品信息 | 在AppGallery Connect中录入商品信息  |
| 商品购买 | 通过调用应用内支付接口进行商品购买  |

## 应用开发

#### 配置商品信息

您需要在AppGallery Connect中提前录入商品信息（包括商品ID、商品类型、不同国家的商品定价、商品名称等），在您的客户端调用购买接口时，只需传入此处配置的商品ID和商品类型，IAP会根据用户当前的帐号服务地展示对应国家/地区的商品信息（包括定价、商品名称等），而无需您自行管理商品价格。


#### 商品购买

- 消耗型商品购买流程
- 非消耗型商品购买流程
