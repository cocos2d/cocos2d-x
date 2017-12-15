/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "MyPurchase.h"
#include "PluginManager.h"
#include "cocos2d.h"
#include "Configs.h"

using namespace cocos2d::plugin;
using namespace cocos2d;

MyPurchase* MyPurchase::s_pPurchase = NULL;

MyPurchase::MyPurchase()
: s_pRetListener(NULL)
, s_pGoogle(NULL)
{

}

MyPurchase::~MyPurchase()
{
	unloadIAPPlugin();
	if (s_pRetListener)
	{
		delete s_pRetListener;
		s_pRetListener = NULL;
	}
}

MyPurchase* MyPurchase::getInstance()
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
		s_pPurchase = NULL;
	}
	PluginManager::end();
}

void MyPurchase::loadIAPPlugin()
{
	if (s_pRetListener == NULL)
	{
		s_pRetListener = new MyPurchaseResult();
	}

	//Google IAP
	{
		TIAPDeveloperInfo pGoogleInfo;
		pGoogleInfo["GooglePlayAppKey"] = GOOGLE_APPKEY;

		if(pGoogleInfo.empty()) {
			char msg[256] = { 0 };
			sprintf(msg, "Google App Key info is empty. PLZ fill your Google App Key info in %s(nearby line %d)", __FILE__, __LINE__);
			MessageBox(msg, "Google IAP Warning");
		}
		s_pGoogle = dynamic_cast<ProtocolIAP*>(PluginManager::getInstance()->loadPlugin("IAPGooglePlay"));
		s_pGoogle->configDeveloperInfo(pGoogleInfo);
		s_pGoogle->setResultListener(s_pRetListener);
		s_pGoogle->setDebugMode(true);
	}
}

void MyPurchase::unloadIAPPlugin()
{
	if (s_pGoogle)
	{
		PluginManager::getInstance()->unloadPlugin("IAPGooglePlay");
		s_pGoogle = NULL;
	}
}

void MyPurchase::payByMode(TProductInfo info, MyPayMode mode)
{
	ProtocolIAP* pIAP = NULL;
	switch(mode)
	{
	case eGoogle:
		pIAP = s_pGoogle;
		break;
	default:
		CCLOG("Unsupported IAP");
		break;
	}

	if (pIAP) {
		pIAP->payForProduct(info);
	}
}

void MyPurchaseResult::onPayResult(PayResultCode ret, const char* msg, TProductInfo info)
{
	char goodInfo[1024] = { 0 };
	sprintf(goodInfo, "ProductID:%s\nPrice:%s\nDesc:%s",
			info.find("IAPId")->second.c_str(),
			info.find("IAPId")->second.c_str(),
			info.find("IAPId")->second.c_str());
	MessageBox(goodInfo , msg);
}
