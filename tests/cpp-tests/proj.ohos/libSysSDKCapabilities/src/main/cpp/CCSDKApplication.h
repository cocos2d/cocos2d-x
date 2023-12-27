#ifndef __CC_APPLICATION_OHOS_SDK_H__
#define __CC_APPLICATION_OHOS_SDK_H__
#include <string>
#include "CCSDKPlatformDefine.h"
namespace cocos2d {
    class CC_DLL SDKApplication
    {
    public:
        SDKApplication();
        virtual ~SDKApplication();
        static SDKApplication *getInstance();

        static std::string authorization();
        static std::string loginInit();
        static std::string getPlayerInfo();
        static std::string reportPlayerInfo();
        static std::string executeLoginSDKCallback(const char *result);
        static std::string getLginSDKResult();
        static std::string loginSDKResult;
        static std::string checkPayEnv();
        static std::string executePaySDKCallback(const char *result);
        static std::string queryConsumProdts();
        static std::string buy();
        static std::string consume();
        static std::string queryNoConsumableGoods();
        static std::string purchaseOfNonConsumableGoods();
        static std::string disposableGoodsOrderQuery();
        static std::string nonConsumableProductsRecords();
        static std::string consumableProductsRecords();
        static std::string getPaySDKResult();
        static std::string paySDKResult;
    protected:
        static SDKApplication *sm_pSharedApplication;
    };
}
#endif  
