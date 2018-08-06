/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "DeviceEx.h"

#import "openudid/OpenUDIDMac.h"

using namespace std;
PLAYER_NS_BEGIN

DeviceEx *DeviceEx::getInstance()
{
    static DeviceEx *instance = NULL;
    if (!instance)
    {
        instance = new DeviceEx();
        instance->init();
    }
    return instance;
}

std::string DeviceEx::getCurrentUILangName()
{
    return _uiLangName;
}

std::string DeviceEx::getUserGUID()
{
    return _userGUID;
}


//////////  private  //////////

DeviceEx::DeviceEx()
    : _uiLangName("en")
{

}

void DeviceEx::init()
{
    makeUILangName();
    makeUserGUID();
}

void DeviceEx::makeUILangName()
{
    NSUserDefaults *defs = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defs objectForKey:@"AppleLanguages"];
    if ([languages count] > 0)
    {
        NSString *lang = [languages objectAtIndex:0];
        _uiLangName = lang.UTF8String;
    }
}

std::string DeviceEx::makeUserGUID()
{
    if (_userGUID.length() <= 0)
    {
        _userGUID = string([[OpenUDIDMac value] cStringUsingEncoding:NSUTF8StringEncoding]);
        
        if (_userGUID.length() <= 0)
        {
            _userGUID = "guid-fixed-1234567890";
        }
    }

    return _userGUID;
}

PLAYER_NS_END
