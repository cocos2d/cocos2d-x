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

bool ProtocolIAP::init()
{
    return true;
}

void ProtocolIAP::configDeveloperInfo(TIAPDeveloperInfo devInfo)
{
}

void ProtocolIAP::payForProduct(TProductInfo info)
{
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

    m_curInfo.clear();
}

const char* ProtocolIAP::getSDKVersion()
{
    return "Subclass should override this interface";
}

void ProtocolIAP::setDebugMode(bool debug)
{
}

}} //namespace cocos2d { namespace plugin {
