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
#include "ProtocolUser.h"
#include "PluginUtilsIOS.h"
#import "InterfaceUser.h"

namespace cocos2d { namespace plugin {

ProtocolUser::ProtocolUser()
: _listener(NULL)
{
}

ProtocolUser::~ProtocolUser()
{
}

void ProtocolUser::configDeveloperInfo(TUserDeveloperInfo devInfo)
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
        if ([ocObj conformsToProtocol:@protocol(InterfaceUser)]) {
            NSObject<InterfaceUser>* curObj = ocObj;
            NSMutableDictionary* pDict = PluginUtilsIOS::createDictFromMap(&devInfo);
            [curObj configDeveloperInfo:pDict];
        }
    }
}

void ProtocolUser::login()
{
    PluginUtilsIOS::callOCFunctionWithName(this, "login");
}
    
void ProtocolUser::logout()
{
    PluginUtilsIOS::callOCFunctionWithName(this, "logout");
}
    
bool ProtocolUser::isLogined()
{
    return PluginUtilsIOS::callOCBoolFunctionWithName(this, "isLogined");
}

std::string ProtocolUser::getSessionID()
{
    return PluginUtilsIOS::callOCStringFunctionWithName(this, "getSessionID");
}

}} // namespace cocos2d { namespace plugin {
