/*
 *
 * Copyright (c) 2014 Nguyen Thai Duong
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "CCBLocalizationManager.h"

USING_NS_CC;
namespace spritebuilder {
#define LOCALIZATION_FILE "Strings.ccbLang"

std::string strEmpty = "";

static CCBLocalizationManager *_instance;

CCBLocalizationManager::CCBLocalizationManager() {
    loadStringFile(LOCALIZATION_FILE);
}

CCBLocalizationManager* CCBLocalizationManager::sharedManager() {
    if (_instance == NULL)
        _instance = new CCBLocalizationManager();
    
    return _instance;
}

std::string& CCBLocalizationManager::localizedStringForKey(const char* key) {
    std::map<std::string, std::string>::iterator it = mTranslation.find(key);
    if (it != mTranslation.end())
        return (*it).second;
    
    return strEmpty;
}

void CCBLocalizationManager::loadStringFile(const char* file) {
    
    ValueMap map = FileUtils::getInstance()->getValueMapFromFile(file);
    
    ValueMap::iterator it = map.find("fileType");

    CCASSERT(it != map.end() && it->second.asString() == "SpriteBuilderTranslations", "Invalid file format for SpriteBuilder localizations");
    
    it = map.find("fileVersion");
    CCASSERT(it != map.end() && it->second.asInt() == 1, "Translation file version is incompatible with this reader");
    
    ValueVector languages = map["activeLanguages"].asValueVector();
    
    std::string userLanguage;
    std::string preferredLangs = Application::getInstance()->getCurrentLanguageCode();
    
    for (ValueVector::iterator _it = languages.begin(); _it != languages.end(); _it++) {
        if (_it->asString() == preferredLangs) {
            userLanguage = _it->asString();
            break;
        }
    }
    
    mTranslation.clear();
    if (userLanguage != "") {
        ValueVector tranList = map["translations"].asValueVector();
        for (ValueVector::iterator _it = tranList.begin(); _it != tranList.end(); _it++) {
            ValueMap dic = _it->asValueMap();
            
            mTranslation[dic["key"].asString()] = dic["translations"].asValueMap()[userLanguage].asString();
        }
    }
}
}