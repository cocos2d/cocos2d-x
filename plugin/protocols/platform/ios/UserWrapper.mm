/****************************************************************************
Copyright (c) 2012+2013 cocos2d+x.org

http://www.cocos2d+x.org

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

#import "UserWrapper.h"
#include "PluginUtilsIOS.h"
#include "ProtocolUser.h"
#include "FacebookAgent.h"
using namespace cocos2d::plugin;

@implementation UserWrapper

+ (void) onActionResult:(id) obj withRet:(UserActionResult) ret withMsg:(NSString*) msg
{
    PluginProtocol* pPlugin = PluginUtilsIOS::getPluginPtr(obj);
    ProtocolUser* pUser = dynamic_cast<ProtocolUser*>(pPlugin);
    if (pUser) {
        UserActionListener* listener = pUser->getActionListener();
        ProtocolUser::ProtocolUserCallback callback = pUser->getCallback();
        const char* chMsg = [msg UTF8String];
        if (NULL != listener)
        {
            listener->onActionResult(pUser, (UserActionResultCode) ret, chMsg);
        }else if(callback){
            std::string stdmsg(chMsg);
            callback((UserActionResultCode) ret, stdmsg);
        }else{
            PluginUtilsIOS::outputLog("Can't find the listener of plugin %s", pPlugin->getPluginName());
        }
    } else {
        PluginUtilsIOS::outputLog("Can't find the C++ object of the User plugin");
    }
}
+ (void) onGraphResult:(id)obj withRet:(GraphResult)ret withMsg:(NSString *)msg withCallback:(int)cbid{
    const char* chMsg = [msg UTF8String];
    FacebookAgent::FBCallback callback = FacebookAgent::getInstance()->getRequestCallback(cbid);
    if(callback){
        std::string stdmsg(chMsg);
        callback((GraphResult) ret, stdmsg);
    }else{
        PluginUtilsIOS::outputLog("an't find the C++ object of the requestCallback");
    }
}
+ (void) onPermissionsResult:(id)obj withRet:(int)ret withMsg:(NSString *)msg{
    PluginProtocol* pPlugin = PluginUtilsIOS::getPluginPtr(obj);
    ProtocolUser* pUser = dynamic_cast<ProtocolUser*>(pPlugin);
    if (pUser) {
        ProtocolUser::ProtocolUserCallback callback = pUser->getCallback();
        const char* chMsg = [msg UTF8String];
        if(callback){
            std::string stdmsg(chMsg);
            callback(ret, stdmsg);
        }else{
            PluginUtilsIOS::outputLog("Can't find the listener of plugin %s", pPlugin->getPluginName());
        }
    } else {
        PluginUtilsIOS::outputLog("Can't find the C++ object of the User plugin");
    }
}
+ (void)onPermissionListResult:(id)obj withRet:(PermissionListResult )ret withMsg:(NSString *)msg{
    PluginProtocol* pPlugin = PluginUtilsIOS::getPluginPtr(obj);
    ProtocolUser* pUser = dynamic_cast<ProtocolUser*>(pPlugin);
    if (pUser) {
        ProtocolUser::ProtocolUserCallback callback = pUser->getCallback();
        const char* chMsg = [msg UTF8String];
        if(callback){
            std::string stdmsg(chMsg);
            callback(ret, stdmsg);
        }else{
            PluginUtilsIOS::outputLog("Can't find the listener of plugin %s", pPlugin->getPluginName());
        }
    } else {
        PluginUtilsIOS::outputLog("Can't find the C++ object of the User plugin");
    }
}
@end
