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
#include "ProtocolSocial.h"
#include "PluginUtilsIOS.h"
#import "InterfaceSocial.h"

namespace cocos2d { namespace plugin {

ProtocolSocial::ProtocolSocial()
: m_pListener(NULL)
{
}

ProtocolSocial::~ProtocolSocial()
{
}

void ProtocolSocial::configDeveloperInfo(TSocialDeveloperInfo devInfo)
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
        if ([ocObj conformsToProtocol:@protocol(InterfaceSocial)]) {
            NSObject<InterfaceSocial>* curObj = ocObj;
            NSMutableDictionary* pDict = PluginUtilsIOS::createDictFromMap(&devInfo);
            [curObj configDeveloperInfo:pDict];
        }
    }
}

void ProtocolSocial::share(TShareInfo info)
{
    if (info.empty())
    {
        if (NULL != m_pListener)
        {
            onShareResult(kShareFail, "Share info error");
        }
        PluginUtilsIOS::outputLog("The Share info of %s is empty!", this->getPluginName());
        return;
    }
    else
    {
        PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
        assert(pData != NULL);
        
        id ocObj = pData->obj;
        if ([ocObj conformsToProtocol:@protocol(InterfaceSocial)]) {
            NSObject<InterfaceSocial>* curObj = ocObj;
            NSMutableDictionary* pDict = PluginUtilsIOS::createDictFromMap(&info);
            [curObj share:pDict];
        }
    }
}

void ProtocolSocial::setResultListener(ShareResultListener* pListener)
{
	m_pListener = pListener;
}

void ProtocolSocial::onShareResult(ShareResultCode ret, const char* msg)
{
    if (m_pListener)
    {
    	m_pListener->onShareResult(ret, msg);
    }
    else
    {
        PluginUtilsIOS::outputLog("Share result listener of %s is null!", this->getPluginName());
    }
    PluginUtilsIOS::outputLog("Share result of %s is : %d(%s)", this->getPluginName(), (int) ret, msg);
}

}} // namespace cocos2d { namespace plugin {
