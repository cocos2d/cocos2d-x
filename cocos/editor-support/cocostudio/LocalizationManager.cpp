#include "LocalizationManager.h"
#include "CCPlatformMacros.h"
#include "platform/CCFileUtils.h"

using namespace cocostudio;
using namespace cocos2d;

LocalizationManager::LocalizationManager()
:languageData(nullptr)
{
}


LocalizationManager::~LocalizationManager()
{
    CC_SAFE_DELETE(languageData);
}

bool LocalizationManager::initLanguageData(std::string file)
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

std::string LocalizationManager::getLocalizationString(std::string key)
{
    std::string result = key;

    if (languageData && languageData->HasMember(key.c_str()) &&
        (*languageData)[key.c_str()].IsString())
        result = (*languageData)[key.c_str()].GetString();

    return result;
}
