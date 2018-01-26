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