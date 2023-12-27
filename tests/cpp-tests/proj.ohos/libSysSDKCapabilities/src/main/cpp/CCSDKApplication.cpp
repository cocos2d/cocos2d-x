#include <unistd.h>
#include "napi/helper/Js_Cocos2dxHelper.h"
#include "napi/helper/NapiHelper.h"
#include "CCSDKApplication.h"
#include "CCSDKLogOhos.h"
#include <string>

std::string cocos2d::SDKApplication::loginSDKResult="";
std::string cocos2d::SDKApplication::paySDKResult="";
cocos2d::SDKApplication *cocos2d::SDKApplication::sm_pSharedApplication = nullptr;
cocos2d::SDKApplication::SDKApplication() {
    sm_pSharedApplication = this;
}

cocos2d::SDKApplication::~SDKApplication() {
    sm_pSharedApplication = nullptr;
}

cocos2d::SDKApplication *cocos2d::SDKApplication::getInstance() {
    return sm_pSharedApplication;
}
std::string cocos2d::SDKApplication::getLginSDKResult() { return loginSDKResult; }

std::string cocos2d::SDKApplication::authorization()
{
    JSFunction::getFunction("LoginSDK.authorization").invoke<std::string>();
    OHOS_LOGD( "==========authorization executeLoginSDKCallback1 is [%{public}s] =========", loginSDKResult.c_str());
    return loginSDKResult;
}

std::string cocos2d::SDKApplication::loginInit()
{
    JSFunction::getFunction("LoginSDK.loginInit").invoke<std::string>();
    OHOS_LOGD( "==========loginInit executeLoginSDKCallback1 is [%{public}s] =========", loginSDKResult.c_str());
    return loginSDKResult;
}
std::string cocos2d::SDKApplication::getPlayerInfo()
{
    JSFunction::getFunction("LoginSDK.getPlayerInfo").invoke<std::string>();
    OHOS_LOGD( "==========getPlayerInfo executeLoginSDKCallback1 is [%{public}s] =========", loginSDKResult.c_str());
    return loginSDKResult;
}
std::string cocos2d::SDKApplication::reportPlayerInfo()
{
    JSFunction::getFunction("LoginSDK.reportPlayerInfo").invoke<std::string>();
    OHOS_LOGD( "==========reportPlayerInfo executeLoginSDKCallback1 is [%{public}s] =========", loginSDKResult.c_str());
    return loginSDKResult;
}
std::string cocos2d::SDKApplication::executeLoginSDKCallback(const char * result)
{
    loginSDKResult = std::string(result);
    OHOS_LOGD("==========pullSDK executeLoginSDKCallback2 is [%{public}s] =========",loginSDKResult.c_str());
    return loginSDKResult;
}

std::string cocos2d::SDKApplication::checkPayEnv()
{
    JSFunction::getFunction("PaySDK.checkPayEnv").invoke<std::string>();
    return "";
}
std::string cocos2d::SDKApplication::queryConsumProdts()
{
    JSFunction::getFunction("PaySDK.queryConsumProdts").invoke<std::string>();
    return "";
}
std::string cocos2d::SDKApplication::buy()
{
    JSFunction::getFunction("PaySDK.buy").invoke<std::string>();
    return "";
}
std::string cocos2d::SDKApplication::consume()
{
    JSFunction::getFunction("PaySDK.consume").invoke<std::string>();
    return "";
}

std::string cocos2d::SDKApplication::queryNoConsumableGoods()
{
    JSFunction::getFunction("PaySDK.queryNoConsumableGoods").invoke<std::string>();
    return "";
}
std::string cocos2d::SDKApplication::purchaseOfNonConsumableGoods()
{
    JSFunction::getFunction("PaySDK.purchaseOfNonConsumableGoods").invoke<std::string>();
    return "";
}
std::string cocos2d::SDKApplication::disposableGoodsOrderQuery()
{
    JSFunction::getFunction("PaySDK.disposableGoodsOrderQuery").invoke<std::string>();
    return "";
}
std::string cocos2d::SDKApplication::nonConsumableProductsRecords()
{
    JSFunction::getFunction("PaySDK.nonConsumableProductsRecords").invoke<std::string>();
    return "";
}
std::string cocos2d::SDKApplication::consumableProductsRecords()
{
    JSFunction::getFunction("PaySDK.consumableProductsRecords").invoke<std::string>();
    return "";
}
std::string cocos2d::SDKApplication::executePaySDKCallback(const char * result)
{
    paySDKResult = std::string(result);
    OHOS_LOGD("==========pullSDK executePaySDKCallback2 is [%{public}s] =========",paySDKResult.c_str());
    return paySDKResult;
}
std::string cocos2d::SDKApplication::getPaySDKResult() { return paySDKResult; }