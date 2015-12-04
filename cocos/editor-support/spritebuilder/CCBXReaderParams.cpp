#include "CCBXReaderParams.h"
#include "platform/CCFileUtils.h"
#include "platform/CCApplication.h"
#include "base/CCDirector.h"
#include "2d/CCSpriteFrameCache.h"
#include <unordered_set>
#include "json/document.h"

NS_CC_BEGIN

namespace spritebuilder {
    
CCBReaderParams *CCBReaderParams::create(const std::string &path)
{
    CCBReaderParams *ret = new CCBReaderParams();
    if (ret && ret->initWithPath(path))
        ret->autorelease();
    else
        CC_SAFE_RELEASE_NULL(ret);
    return ret;
}
    
CCBReaderParams::CCBReaderParams():_curentLanguage(Application::getInstance()->getCurrentLanguageCode()) {
}

CCBReaderParams::~CCBReaderParams() {
}
    
std::vector<std::string> CCBReaderParams::getLanguagesList() const
{
    std::vector<std::string> ret;
    ret.reserve(_languages.size());
    for(const auto &pair: _languages)
    {
        ret.push_back(pair.first);
    }
    return ret;
}
    
bool CCBReaderParams::initWithPath(const std::string &path)
{
    if(!loadParams(path))
    {
        log("CCBXReader: can't read config file");
        return false;
    }
    loadLocalization(path);
    FileUtils::getInstance()->loadFilenameLookupDictionaryFromFile(path+"fileLookup.plist");
    SpriteFrameCache::getInstance()->loadSpriteFrameLookupDictionaryFromFile(path+"spriteFrameFileList.plist");
    return true;
}
    
bool CCBReaderParams::loadParams(const std::string &path)
{
    std::string fullConfigPath = FileUtils::getInstance()->fullPathForFilename(path+"configCocos2d.plist");
    ValueMap configDict = FileUtils::getInstance()->getValueMapFromFile(fullConfigPath);
    
    if(configDict.empty())
        return false;
    
    auto scale = configDict.find("CCSetupDesignResourceScale");
    if (scale != configDict.end())
        _designResolutionscale = scale->second.asDouble();
    else
        _designResolutionscale = 1.0f;
    
    auto height = configDict.find("CCSetupDesignSizeHeight");
    if (height != configDict.end())
        _designResolution.height = height->second.asInt();
    else
        _designResolution.height = Director::getInstance()->getWinSize().height;
    
    auto width = configDict.find("CCSetupDesignSizeWidth");
    if (width != configDict.end())
        _designResolution.width = width->second.asInt();
    else
        _designResolution.width = Director::getInstance()->getWinSize().width;
    
    return true;
}
    

bool CCBReaderParams::loadLocalization(const std::string &path)
{
    std::string fullTranslationPath = FileUtils::getInstance()->fullPathForFilename(path+"Strings.json");
    
    bool loaded = false;
    if(FileUtils::getInstance()->isFileExist(fullTranslationPath))
    {
        std::string jsonData = FileUtils::getInstance()->getStringFromFile(fullTranslationPath);
        rapidjson::Document parser;
        parser.Parse<rapidjson::kParseDefaultFlags>(jsonData.c_str());
        const auto &fileVersionValue = parser["fileVersion"];
        if(fileVersionValue.IsInt())
        {
            if(fileVersionValue.GetInt() == 1)
            {
                const auto &activeLanguagesValue = parser["activeLanguages"];
                if(activeLanguagesValue.IsArray())
                {
                    std::unordered_set<std::string> languages;
                    for(int i=0;i<activeLanguagesValue.Size();++i)
                    {
                        languages.insert(activeLanguagesValue[i].GetString());
                    }
                    if(languages.find(_curentLanguage) == languages.end())
                        _curentLanguage = activeLanguagesValue[0].GetString();
                    
                    const auto &translationsValue = parser["translations"];
                    if(translationsValue.IsArray())
                    {
                        for(int i=0;i<translationsValue.Size();++i)
                        {
                            auto member =  translationsValue[i].FindMember("key");
                            if (member != translationsValue[i].MemberEnd())
                            {
                                const char *key = member->value.GetString();
                                if(key)
                                {
                                    const auto &translationsInternalValue = translationsValue[i]["translations"];
                                    for(auto it=translationsInternalValue.MemberBegin();it!=translationsInternalValue.MemberEnd();++it)
                                    {
                                        if(it->name.GetString())
                                            _languages[it->name.GetString()][key] = it->value.GetString()?it->value.GetString():"";
                                    }
                                }
                            }
                        }
                        loaded = true;
                    }
                }
            }
        }
    }
    
    if(loaded)
        return true;
    
    fullTranslationPath = FileUtils::getInstance()->fullPathForFilename(path+"Strings.ccbLang");
    ValueMap translationDict = FileUtils::getInstance()->getValueMapFromFile(fullTranslationPath);
    
    auto fileVersion = translationDict.find("fileVersion");
    if(fileVersion ==translationDict.end() )
        return false;
    if(fileVersion->second.asInt() != 1)
        return false;
    auto activeLanguages = translationDict.find("activeLanguages");
    if (activeLanguages != translationDict.end()) {
        std::unordered_set<std::string> languages;
        for(const auto &language : activeLanguages->second.asValueVector())
            languages.insert(language.asString());
        if(languages.find(_curentLanguage) == languages.end())
            _curentLanguage = activeLanguages->second.asValueVector()[0].asString();
    }
    auto translations = translationDict.find("translations");
    if (translations != translationDict.end()) {
        const ValueVector &valueVector = translations->second.asValueVector();
        for(const auto &value: valueVector)
        {
            const ValueMap &valueMap = value.asValueMap();
            auto key = valueMap.find("key");
            if(key!= valueMap.end())
            {
                auto strings = valueMap.find("translations");
                for(const auto &localizedString : strings->second.asValueMap())
                {
                    _languages[localizedString.first][key->second.asString()] = localizedString.second.asString();
                }
            }
        }
    }
    return true;
}
    
void CCBReaderParams::setLanguage(const std::string &language)
{
    _curentLanguage = language;
}
const std::string &CCBReaderParams::getLanguage() const
{
    return _curentLanguage;
}
    
const std::string &CCBReaderParams::getLocalizedString(const std::string &key) const
{
    auto language = _languages.find(_curentLanguage);
    if(language == _languages.end())
        return key;
    auto recordIt = language->second.find(key);
    if(recordIt == language->second.end())
        return key;
    return recordIt->second;
}
    
}

NS_CC_END