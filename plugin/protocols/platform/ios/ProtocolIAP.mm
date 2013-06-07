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
#include "ProtocolIAP.h"
#include "PluginUtilsIOS.h"
#import "InterfaceIAP.h"

namespace cocos2d { namespace plugin {

bool ProtocolIAP::m_bPaying = false;

ProtocolIAP::ProtocolIAP()
: m_pListener(NULL)
{
}

ProtocolIAP::~ProtocolIAP()
{
    PluginUtilsIOS::erasePluginOCData(this);
}

void ProtocolIAP::configDeveloperInfo(TIAPDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtilsIOS::outputLog("The developer info is empty for %s!", this->getPluginName());
        return;
    }
    else
    {
        PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
        assert(pData != NULL);
        
        id ocObj = pData->obj;
        if ([ocObj conformsToProtocol:@protocol(InterfaceIAP)]) {
            NSObject<InterfaceIAP>* curObj = ocObj;
            NSMutableDictionary* pDict = PluginUtilsIOS::createDictFromMap(&devInfo);
            [curObj configDeveloperInfo:pDict];
        }
    }
}

void ProtocolIAP::payForProduct(TProductInfo info)
{
    if (m_bPaying)
    {
        PluginUtilsIOS::outputLog("Now is paying");
        return;
    }

    if (info.empty())
    {
        if (NULL != m_pListener)
        {
            onPayResult(kPayFail, "Product info error");
        }
        PluginUtilsIOS::outputLog("The product info is empty for %s!", this->getPluginName());
        return;
    }
    else
    {
        m_bPaying = true;
        m_curInfo = info;
        
        PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
        assert(pData != NULL);
        
        id ocObj = pData->obj;
        if ([ocObj conformsToProtocol:@protocol(InterfaceIAP)]) {
            NSObject<InterfaceIAP>* curObj = ocObj;
            NSMutableDictionary* dict = PluginUtilsIOS::createDictFromMap(&info);
            [curObj payForProduct:dict];
        }
    }
}

void ProtocolIAP::setResultListener(PayResultListener* pListener)
{
    m_pListener = pListener;
}

void ProtocolIAP::onPayResult(PayResultCode ret, const char* msg)
{
    m_bPaying = false;
    if (m_pListener)
    {
        m_pListener->onPayResult(ret, msg, m_curInfo);
    }
    else
    {
        PluginUtilsIOS::outputLog("Pay result listener of %s is null!", this->getPluginName());
    }

    m_curInfo.clear();
    PluginUtilsIOS::outputLog("Pay result of %s is : %d(%s)", this->getPluginName(), (int) ret, msg);
}

}} //namespace cocos2d { namespace plugin {
