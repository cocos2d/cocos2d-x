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
