/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __DICTIONARYHELPER_H__
#define __DICTIONARYHELPER_H__

#include "json/document.h"
#include "editor-support/cocostudio/CocosStudioExport.h"

#define DICTOOL DictionaryHelper::getInstance()

namespace cocostudio {
/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL DictionaryHelper
{
public:
    DictionaryHelper();
    ~DictionaryHelper();
    static DictionaryHelper* getInstance();
	static void destroyInstance();
    
	const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, const char* key);
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, const char* key, int idx);
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, int idx);
    
	int   getIntValue_json(const rapidjson::Value& root, const char* key, int def = 0);
	float getFloatValue_json(const rapidjson::Value& root,const char* key, float def = 0.0f);
    bool  getBooleanValue_json(const rapidjson::Value& root,const char* key, bool def = false);
    const char* getStringValue_json(const rapidjson::Value& root,const char* key, const char *def = NULL);
    int   getArrayCount_json(const rapidjson::Value& root,const char* key, int def = 0);
	
    int   getIntValueFromArray_json(const rapidjson::Value& root,const char* arrayKey,int idx, int def = 0);
	float getFloatValueFromArray_json(const rapidjson::Value& root,const char* arrayKey,int idx, float def = 0.0f);
	bool  getBoolValueFromArray_json(const rapidjson::Value& root,const char* arrayKey,int idx, bool def = false);
	const char* getStringValueFromArray_json(const rapidjson::Value& root,const char* arrayKey,int idx, const char *def = NULL);
	const rapidjson::Value &getDictionaryFromArray_json(const rapidjson::Value &root, const char* key,int idx);
	bool checkObjectExist_json(const rapidjson::Value &root);
    bool checkObjectExist_json(const rapidjson::Value &root, const char* key);
    bool checkObjectExist_json(const rapidjson::Value &root, int index);
};

}

#endif /* defined(__CocoGUI__DictionaryHelper__) */
