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

#include "editor-support/cocostudio/LocalizationManager.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCFileUtils.h"
#include "editor-support/cocostudio/CSLanguageDataBinary_generated.h"

using namespace cocostudio;
using namespace cocos2d;

static JsonLocalizationManager* _sharedJsonLocalizationManager = nullptr;

ILocalizationManager* JsonLocalizationManager::getInstance()
{
    if (!_sharedJsonLocalizationManager)
    {
        _sharedJsonLocalizationManager = new (std::nothrow) JsonLocalizationManager();
    }

    return _sharedJsonLocalizationManager;
}

void JsonLocalizationManager::destroyInstance()
{
    if (_sharedJsonLocalizationManager != nullptr)
    {
        delete _sharedJsonLocalizationManager;
        _sharedJsonLocalizationManager = nullptr;
    }
}

JsonLocalizationManager::JsonLocalizationManager()
    :languageData(nullptr)
{
}

JsonLocalizationManager::~JsonLocalizationManager()
{
    CC_SAFE_DELETE(languageData);
}

bool JsonLocalizationManager::initLanguageData(std::string file)
{
    bool result = false;

    std::string data = FileUtils::getInstance()->getStringFromFile(file);
    if (!data.empty())
    {
        if (!languageData)
            languageData = new rapidjson::Document;
        languageData->Parse(data.c_str());
        if (languageData->IsObject())
            result = true;
        else
            CC_SAFE_DELETE(languageData);
    }

    return result;
}

std::string JsonLocalizationManager::getLocalizationString(std::string key)
{
    std::string result = key;

    if (languageData && languageData->HasMember(key.c_str()) &&
        (*languageData)[key.c_str()].IsString())
        result = (*languageData)[key.c_str()].GetString();

    return result;
}



static BinLocalizationManager* _sharedBinLocalizationManager = nullptr;

ILocalizationManager* BinLocalizationManager::getInstance()
{
    if (!_sharedBinLocalizationManager)
    {
        _sharedBinLocalizationManager = new (std::nothrow) BinLocalizationManager();
    }

    return _sharedBinLocalizationManager;
}

void BinLocalizationManager::destroyInstance()
{
    if (_sharedBinLocalizationManager != nullptr)
    {
        delete _sharedBinLocalizationManager;
        _sharedBinLocalizationManager = nullptr;
    }
}

BinLocalizationManager::BinLocalizationManager()
{
}

BinLocalizationManager::~BinLocalizationManager()
{
}

bool BinLocalizationManager::initLanguageData(std::string file)
{
    bool result = false;
    languageData.clear();

    Data buf = FileUtils::getInstance()->getDataFromFile(file);
    if (!buf.isNull())
    {
        auto lanSet = flatbuffers::GetLanguageSet(buf.getBytes());
        if (lanSet && lanSet->languageItems()->size() > 0)
        {
            result = true;
            auto items = lanSet->languageItems();
            int count = items->size();
            for (int i = 0; i < count; i++)
            {
                auto it = items->Get(i);
                std::string key = it->key()->c_str();
                std::string value = it->value()->c_str();
                if (!key.empty())
                    languageData[key] = value;
            }
        }
    }

    return result;
}

std::string BinLocalizationManager::getLocalizationString(std::string key)
{
    std::string result = key;

    if (!languageData.empty())
    {
        auto it = languageData.find(key);
        if (it != languageData.end())
            result = it->second;
    }

    return result;
}



static bool isCurrentBinManager = true;
static ILocalizationManager* _sharedLocalizationManager = nullptr;

ILocalizationManager* LocalizationHelper::getCurrentManager()
{
    if (!_sharedLocalizationManager)
    {
        _sharedLocalizationManager = BinLocalizationManager::getInstance();
        isCurrentBinManager = true;
    }
    
    return _sharedLocalizationManager;
}

void LocalizationHelper::setCurrentManager(ILocalizationManager* manager, bool isBinary)
{
    _sharedLocalizationManager = manager;
    isCurrentBinManager = isBinary;
}

bool LocalizationHelper::isBinManager()
{
    return isCurrentBinManager;
}