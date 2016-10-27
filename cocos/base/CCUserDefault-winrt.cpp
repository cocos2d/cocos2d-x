/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.

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
#include "base/CCUserDefault.h"
#include "platform/CCCommon.h"
#include "base/base64.h"
#include "base/ccUtils.h"
#include "platform/CCFileUtils.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "platform/winrt/CCWinRTUtils.h"

using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace std;

#define XML_FILE_NAME "UserDefault.xml"

NS_CC_BEGIN


/**
 * WinRT implementation of UserDefault
 */

UserDefault* UserDefault::_userDefault = nullptr;
string UserDefault::_filePath = string("");
bool UserDefault::_isFilePathInitialized = false;

UserDefault::~UserDefault()
{
}

UserDefault::UserDefault()
{
}

Platform::Object^ getPlatformKeyValue(const char* pKey)
{
    // check key
    if (!pKey)
    {
        return nullptr;
    }

    ApplicationDataContainer^ localSettings = ApplicationData::Current->LocalSettings;
    auto key = PlatformStringFromString(pKey);
    auto values = localSettings->Values;

    if (values->HasKey(key))
    {
        return values->Lookup(key);
    }

    return nullptr;
}

void setPlatformKeyValue(const char* pKey, PropertyValue^ value)
{
    // check key
    if (!pKey)
    {
        return;
    }

    ApplicationDataContainer^ localSettings = ApplicationData::Current->LocalSettings;
    auto values = localSettings->Values;
    values->Insert(PlatformStringFromString(pKey), value);
}

bool UserDefault::getBoolForKey(const char* pKey)
{
    return getBoolForKey(pKey, false);
}

bool UserDefault::getBoolForKey(const char* pKey, bool defaultValue)
{
	bool ret = defaultValue;
    auto value = getPlatformKeyValue(pKey);
    if (value)
    {
        ret = safe_cast<bool>(value);
    }
	return ret;
}

int UserDefault::getIntegerForKey(const char* pKey)
{
    return getIntegerForKey(pKey, 0);
}

int UserDefault::getIntegerForKey(const char* pKey, int defaultValue)
{
    int ret = defaultValue;
    auto value = getPlatformKeyValue(pKey);
    if (value)
    {
        ret = safe_cast<int>(value);
    }
    return ret;
}

float UserDefault::getFloatForKey(const char* pKey)
{
    return getFloatForKey(pKey, 0.0f);
}

float UserDefault::getFloatForKey(const char* pKey, float defaultValue)
{
    float ret = (float)getDoubleForKey(pKey, (double)defaultValue);

    return ret;
}

double  UserDefault::getDoubleForKey(const char* pKey)
{
    return getDoubleForKey(pKey, 0.0);
}

double UserDefault::getDoubleForKey(const char* pKey, double defaultValue)
{
    double ret = defaultValue;
    auto value = getPlatformKeyValue(pKey);
    if (value)
    {
        ret = safe_cast<double>(value);
    }
    return ret;
}

std::string UserDefault::getStringForKey(const char* pKey)
{
    return getStringForKey(pKey, "");
}

string UserDefault::getStringForKey(const char* pKey, const std::string & defaultValue)
{
    string ret = defaultValue;
    auto value = getPlatformKeyValue(pKey);
    if (value)
    {
        auto result = safe_cast<Platform::String^>(value);
        ret = PlatformStringToString(result);
    }

    return ret;
}

Data UserDefault::getDataForKey(const char* pKey)
{
    return getDataForKey(pKey, Data::Null);
}

Data UserDefault::getDataForKey(const char* pKey, const Data& defaultValue)
{
    Data ret = defaultValue;
    std::string encodedData = getStringForKey(pKey,"");

    if (!encodedData.empty())
    {
        unsigned char* decodedData = nullptr;
        int decodedDataLen = base64Decode((unsigned char*) encodedData.c_str(), (unsigned int) encodedData.length(), &decodedData);
        if (decodedData && decodedDataLen > 0)
        {
            ret.fastSet(decodedData, decodedDataLen);
        }
    }

    return ret;
}

void UserDefault::setBoolForKey(const char* pKey, bool value)
{
    // check key
    if (!pKey)
    {
        return;
    }

    setPlatformKeyValue(pKey, dynamic_cast<PropertyValue^>(PropertyValue::CreateBoolean(value)));
}

void UserDefault::setIntegerForKey(const char* pKey, int value)
{
    // check key
    if (! pKey)
    {
        return;
    }

    setPlatformKeyValue(pKey, dynamic_cast<PropertyValue^>(PropertyValue::CreateInt32(value)));
}

void UserDefault::setFloatForKey(const char* pKey, float value)
{
    setDoubleForKey(pKey, value);
}

void UserDefault::setDoubleForKey(const char* pKey, double value)
{
    // check key
    if (! pKey)
    {
        return;
    }

    setPlatformKeyValue(pKey, dynamic_cast<PropertyValue^>(PropertyValue::CreateDouble(value)));
}

void UserDefault::setStringForKey(const char* pKey, const std::string & value)
{
    // check key
    if (! pKey)
    {
        return;
    }

    setPlatformKeyValue(pKey, dynamic_cast<PropertyValue^>(PropertyValue::CreateString(PlatformStringFromString(value))));
}

void UserDefault::setDataForKey(const char* pKey, const Data& value) {
    // check key
    if (! pKey)
    {
        return;
    }

    char *encodedData = nullptr;
    base64Encode(value.getBytes(), static_cast<unsigned int>(value.getSize()), &encodedData);

    setPlatformKeyValue(pKey, dynamic_cast<PropertyValue^>(PropertyValue::CreateString(PlatformStringFromString(encodedData))));

    if (encodedData)
        free(encodedData);
}

UserDefault* UserDefault::getInstance()
{
    if (!_userDefault)
    {
        initXMLFilePath();

        // only create xml file one time
        // the file exists after the program exit
        if ((!isXMLFileExist()) && (!createXMLFile()))
        {
            return nullptr;
        }

        _userDefault = new (std::nothrow) UserDefault();
    }

    return _userDefault;
}

void UserDefault::destroyInstance()
{
    CC_SAFE_DELETE(_userDefault);
}

void UserDefault::setDelegate(UserDefault *delegate)
{
    if (_userDefault)
        delete _userDefault;

    _userDefault = delegate;
}


// FIXME:: deprecated
UserDefault* UserDefault::sharedUserDefault()
{
    return UserDefault::getInstance();
}

// FIXME:: deprecated
void UserDefault::purgeSharedUserDefault()
{
    return UserDefault::destroyInstance();
}

bool UserDefault::isXMLFileExist()
{
    //return FileUtils::getInstance()->isFileExist(_filePath);
    return true;
}

void UserDefault::initXMLFilePath()
{
    if (! _isFilePathInitialized)
    {
        _filePath += FileUtils::getInstance()->getWritablePath() + XML_FILE_NAME;
        _isFilePathInitialized = true;
    }
}

// create new xml file
bool UserDefault::createXMLFile()
{
    return false;
}

const string& UserDefault::getXMLFilePath()
{
    return _filePath;
}

void UserDefault::flush()
{
}

void UserDefault::deleteValueForKey(const char* key)
{
    // check the params
    if (!key)
    {
        CCLOG("the key is invalid");
    }

    ApplicationDataContainer^ localSettings = ApplicationData::Current->LocalSettings;
    auto values = localSettings->Values;
    values->Remove(PlatformStringFromString(key));

    flush();
}

NS_CC_END

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
