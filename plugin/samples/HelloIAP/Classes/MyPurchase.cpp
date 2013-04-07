#include "MyPurchase.h"
#include "PluginManager.h"
#include "cocos2d.h"

using namespace cocos2d::plugin;
using namespace cocos2d;

MyPurchase* MyPurchase::s_pPurchase = NULL;

MyPurchase::MyPurchase()
: s_pAlipay(NULL)
, s_pRetListener(NULL)
, s_pNd91(NULL)
{

}

MyPurchase::~MyPurchase()
{
	unloadIAPPlugin();
	if (s_pRetListener)
	{
		delete s_pRetListener;
	}
}

MyPurchase* MyPurchase::sharedPurchase()
{
	if (s_pPurchase == NULL) {
		s_pPurchase = new MyPurchase();
	}
	return s_pPurchase;
}

void MyPurchase::purgePurchase()
{
	if (s_pPurchase)
	{
		delete s_pPurchase;
	}
}

void MyPurchase::loadIAPPlugin()
{
	{
		// init alipay plugin
		s_pAlipay = dynamic_cast<IAPAlipay*>(PluginManager::getInstance()->loadPlugin("IAPAlipay"));
		TDeveloperInfo pAlipayInfo;
		if (pAlipayInfo.empty())
		{
			char msg[256] = { 0 };
			sprintf(msg, "Developer info is empty. PLZ fill your alipay info in %s(nearby line %d)", __FILE__, __LINE__);
			CCMessageBox(msg, "Alipay Warning");
		}
		s_pAlipay->setDebugMode(true);
		s_pAlipay->initDeveloperInfo(pAlipayInfo);
	}

	{
		TDeveloperInfo pNdInfo;
		pNdInfo["Nd91AppId"] = "100010";
		pNdInfo["Nd91AppKey"] = "C28454605B9312157C2F76F27A9BCA2349434E546A6E9C75";
		pNdInfo["Nd91Orientation"] = "landscape";
		if (pNdInfo.empty()) {
			char msg[256] = { 0 };
			sprintf(msg, "Developer info is empty. PLZ fill your Nd91 info in %s(nearby line %d)", __FILE__, __LINE__);
			CCMessageBox(msg, "Nd91 Warning");
		}
		s_pNd91 = dynamic_cast<IAPNd91*>(PluginManager::getInstance()->loadPlugin("IAPNd91"));
		s_pNd91->setDebugMode(true);
		s_pNd91->initDeveloperInfo(pNdInfo);
	}

	if (s_pRetListener == NULL)
	{
		s_pRetListener = new MyPurchaseResult();
		ProtocolIAP::setResultListener(s_pRetListener);
	}
}

void MyPurchase::unloadIAPPlugin()
{
	if (s_pAlipay)
	{
		PluginManager::getInstance()->unloadPlugin("IAPAlipay");
		s_pAlipay = NULL;
	}

	if (s_pNd91)
	{
		PluginManager::getInstance()->unloadPlugin("IAPNd91");
		s_pNd91 = NULL;
	}
}

void MyPurchase::payByMode(TProductInfo info, MyPayMode mode)
{
	ProtocolIAP* pIAP = NULL;
	switch(mode)
	{
	case eAlipay:
		pIAP = s_pAlipay;
		break;
	case eND91:
		pIAP = s_pNd91;
		break;
	default:
		break;
	}

	if (pIAP) {
		pIAP->payForProduct(info);
	}
}

void MyPurchaseResult::payResult(EPayResult ret, const char* msg, TProductInfo info)
{
	char goodInfo[1024] = { 0 };
	sprintf(goodInfo, "商品名称:%s\n商品价格:%s\n商品描述:%s",
			info.find("productName")->second.c_str(),
			info.find("productPrice")->second.c_str(),
			info.find("productDesc")->second.c_str());
	CCMessageBox(goodInfo , msg);
}
