//
//  AppLang.cpp
//  Simulator
//

#include "AppLang.h"

USING_NS_CC;

AppLang::AppLang()
    : _hasInit(false),
    _localizationFileName("lang")
{
}

void AppLang::readLocalizationFile()
{
    if (!_hasInit)
    {
        _hasInit = true;
        
        auto fileUtils = FileUtils::getInstance();
        
        if (!fileUtils->isFileExist(_localizationFileName))
        {
            cocos2d::log("[WARNING]:not find %s", _localizationFileName.c_str());
            return;
        }
        auto fullFilePath = fileUtils->fullPathForFilename(_localizationFileName);
        std::string fileContent = FileUtils::getInstance()->getStringFromFile(fullFilePath);
        if(fileContent.empty())
            return;
        
        if (_docRootjson.Parse<0>(fileContent.c_str()).HasParseError())
        {
            cocos2d::log("[WARNING]:read json file %s failed because of %d", _localizationFileName.c_str(), _docRootjson.GetParseError());
            return;
        }
    }
}

AppLang* AppLang::getInstance()
{
    static AppLang *lang = nullptr;
    if (!lang)
    {
        lang = new AppLang;
        lang->readLocalizationFile();
    }
    return lang;
}

std::string AppLang::getString(const std::string &lang, const std::string &key)
{
    std::string tmpKey = key;
    const char *ckey = tmpKey.c_str();

    std::string tmpLang = lang;
    const char *langKey = tmpLang.c_str();
    
    if (!_docRootjson.IsObject())
    {
        return key;
    }
    
    if (_docRootjson.HasMember(langKey))
    {
        const rapidjson::Value& v = _docRootjson[langKey];
        if (v.HasMember(ckey))
        {
            return v[ckey].GetString();
        }
    }
    return key;
}
