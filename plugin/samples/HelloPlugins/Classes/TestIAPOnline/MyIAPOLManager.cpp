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
#include "MyIAPOLManager.h"
#include "PluginManager.h"
#include "cocos2d.h"

using namespace cocos2d::plugin;
using namespace cocos2d;

MyIAPOLManager* MyIAPOLManager::s_pIAPOnline = NULL;

MyIAPOLManager::MyIAPOLManager()
: s_pQH360(NULL)
, s_pRetListener(NULL)
, s_pNd91(NULL)
, s_pUC(NULL)
{

}

MyIAPOLManager::~MyIAPOLManager()
{
    unloadPlugins();
    if (s_pRetListener)
    {
        delete s_pRetListener;
        s_pRetListener = NULL;
    }
}

MyIAPOLManager* MyIAPOLManager::getInstance()
{
    if (s_pIAPOnline == NULL) {
        s_pIAPOnline = new MyIAPOLManager();
    }
    return s_pIAPOnline;
}

void MyIAPOLManager::purge()
{
    if (s_pIAPOnline)
    {
        delete s_pIAPOnline;
        s_pIAPOnline = NULL;
    }
    PluginManager::end();
}

void MyIAPOLManager::loadPlugins()
{
    if (s_pRetListener == NULL)
    {
        s_pRetListener = new MyIAPOnlineResult();
    }

    {
        // init qh360 plugin
        s_pQH360 = dynamic_cast<ProtocolIAP*>(PluginManager::getInstance()->loadPlugin("IAPOnlineQH360"));
        TIAPDeveloperInfo pQH360Info;
        pQH360Info["QHAppName"] = APP_NAME;
        pQH360Info["QHExchangeRate"] = QH360_EXCHANGE_RATE;

        s_pQH360->setDebugMode(true);
        s_pQH360->configDeveloperInfo(pQH360Info);
        s_pQH360->setResultListener(s_pRetListener);
    }

    {
        TIAPDeveloperInfo pNdInfo;
        pNdInfo["Nd91AppId"] = ND91_APPID;
        pNdInfo["Nd91AppKey"] = ND91_APPKEY;
        pNdInfo["Nd91Orientation"] = ND91_ORIENTATION;
        s_pNd91 = dynamic_cast<ProtocolIAP*>(PluginManager::getInstance()->loadPlugin("IAPOnlineNd91"));
        s_pNd91->setDebugMode(true);
        s_pNd91->configDeveloperInfo(pNdInfo);
        s_pNd91->setResultListener(s_pRetListener);
    }

#if TEST_UC
    {
        s_pUC = dynamic_cast<ProtocolIAP*>(PluginManager::getInstance()->loadPlugin("IAPOnlineUC"));
        if (NULL != s_pUC)
        {
            TIAPDeveloperInfo pUCInfo;
            pUCInfo["UCCpID"] = UC_CPID;
            pUCInfo["UCGameID"] = UC_GAME_ID;
            pUCInfo["UCServerID"] = UC_SERVER_ID;
            s_pUC->setDebugMode(true);
            s_pUC->configDeveloperInfo(pUCInfo);
            s_pUC->setResultListener(s_pRetListener);
        }
    }
#endif
}

void MyIAPOLManager::unloadPlugins()
{
    if (s_pQH360)
    {
        PluginManager::getInstance()->unloadPlugin("IAPOnlineQH360");
        s_pQH360 = NULL;
    }

    if (s_pNd91)
    {
        PluginManager::getInstance()->unloadPlugin("IAPOnlineNd91");
        s_pNd91 = NULL;
    }

    if (s_pUC)
    {
        PluginManager::getInstance()->unloadPlugin("IAPOnlineUC");
        s_pUC = NULL;
    }
}

void MyIAPOLManager::payByMode(TProductInfo info, MyPayMode mode)
{
    ProtocolIAP* pIAP = NULL;
    switch(mode)
    {
    case eQH360:
        pIAP = s_pQH360;
        break;
    case eND91:
        pIAP = s_pNd91;
        break;
#if TEST_UC
    case eUC:
        pIAP = s_pUC;
        break;
#endif
    default:
        break;
    }

    if (pIAP) {
        pIAP->payForProduct(info);
    }
}

void MyIAPOnlineResult::onPayResult(PayResultCode ret, const char* msg, TProductInfo info)
{
    char goodInfo[1024] = { 0 };
    sprintf(goodInfo, "商品名称:%s\n商品价格:%s\n商品描述:%s",
            info.find("productName")->second.c_str(),
            info.find("productPrice")->second.c_str(),
            info.find("productDesc")->second.c_str());
    MessageBox(goodInfo , msg);

    if (ret == kPaySuccess) {
        log("Pay success locally, should check the real result by game server!");
    }
}
