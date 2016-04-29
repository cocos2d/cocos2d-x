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
: _listener(NULL)
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
    
void ProtocolSocial::submitScore(const char* leadboardID, long score)
{
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    assert(pData != NULL);

    id ocObj = pData->obj;
    if ([ocObj conformsToProtocol:@protocol(InterfaceSocial)]) {
        NSObject<InterfaceSocial>* curObj = ocObj;
        
        NSString* pID = [NSString stringWithUTF8String:leadboardID];
        [curObj submitScore:pID withScore:score];
    }
}
    void ProtocolSocial::submitScore(const char* leadboardID, long score, ProtocolSocialCallback callback)
    {
        PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
        assert(pData != NULL);
        setCallback(callback);
        id ocObj = pData->obj;
        if ([ocObj conformsToProtocol:@protocol(InterfaceSocial)]) {
            NSObject<InterfaceSocial>* curObj = ocObj;
            
            NSString* pID = [NSString stringWithUTF8String:leadboardID];
            [curObj submitScore:pID withScore:score];
        }
    }

void ProtocolSocial::showLeaderboard(const char* leaderboardID)
{
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    assert(pData != NULL);
    
    id ocObj = pData->obj;
    if ([ocObj conformsToProtocol:@protocol(InterfaceSocial)]) {
        NSObject<InterfaceSocial>* curObj = ocObj;
        
        NSString* pID = [NSString stringWithUTF8String:leaderboardID];
        [curObj showLeaderboard:pID];
    }
}

void ProtocolSocial::unlockAchievement(TAchievementInfo achInfo)
{
    if (achInfo.empty())
    {
        PluginUtilsIOS::outputLog("ProtocolSocial", "The achievement info is empty!");
        return;
    }
    else
    {
        PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
        assert(pData != NULL);
        
        id ocObj = pData->obj;
        if ([ocObj conformsToProtocol:@protocol(InterfaceSocial)]) {
            NSObject<InterfaceSocial>* curObj = ocObj;
            
            NSMutableDictionary* pDict = PluginUtilsIOS::createDictFromMap(&achInfo);
            [curObj unlockAchievement:pDict];
        }
    }
}
    void ProtocolSocial::unlockAchievement(TAchievementInfo achInfo,ProtocolSocialCallback callback)
    {
        if (achInfo.empty())
        {
            PluginUtilsIOS::outputLog("ProtocolSocial", "The achievement info is empty!");
            return;
        }
        else
        {
            PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
            assert(pData != NULL);
            setCallback(callback);
            id ocObj = pData->obj;
            if ([ocObj conformsToProtocol:@protocol(InterfaceSocial)]) {
                NSObject<InterfaceSocial>* curObj = ocObj;
                
                NSMutableDictionary* pDict = PluginUtilsIOS::createDictFromMap(&achInfo);
                [curObj unlockAchievement:pDict];
            }
        }
    }

void ProtocolSocial::showAchievements()
{
    PluginUtilsIOS::callOCFunctionWithName(this, "showAchievements");
}

}} // namespace cocos2d { namespace plugin {
