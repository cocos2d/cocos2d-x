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
