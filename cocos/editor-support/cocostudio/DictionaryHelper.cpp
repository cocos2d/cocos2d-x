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

#include "platform/CCPlatformMacros.h"
#include "cocostudio/DictionaryHelper.h"

namespace cocostudio {
    
static DictionaryHelper* sharedHelper = nullptr;

DictionaryHelper::DictionaryHelper()
{
    
}

DictionaryHelper::~DictionaryHelper()
{
    
}

DictionaryHelper* DictionaryHelper::getInstance()
{
    if (!sharedHelper) {
        sharedHelper = new (std::nothrow) DictionaryHelper();
    }
    return sharedHelper;
}

void DictionaryHelper::destroyInstance()
{
	 CC_SAFE_DELETE(sharedHelper);
}

const rapidjson::Value& DictionaryHelper::getSubDictionary_json(const rapidjson::Value &root, const char* key)
{
	return root[key];
}

const rapidjson::Value& DictionaryHelper::getSubDictionary_json(const rapidjson::Value &root, const char* key, int idx)
{
    return root[key][idx];
}

const rapidjson::Value& DictionaryHelper::getSubDictionary_json(const rapidjson::Value &root, int idx)
{
    return root[idx];
}

int DictionaryHelper::getIntValue_json(const rapidjson::Value& root, const char* key, int def)
{
    int nRet = def;
    do {
        CC_BREAK_IF(root.IsNull());
        CC_BREAK_IF(root[key].IsNull());
        nRet = root[key].GetInt();
    } while (0);
    
    return nRet;
}


float DictionaryHelper::getFloatValue_json(const rapidjson::Value& root,const char* key, float def)
{
	float fRet = def;
    do {
        CC_BREAK_IF(root.IsNull());
        CC_BREAK_IF(root[key].IsNull());
        fRet = (float)root[key].GetDouble();
    } while (0);
    
    return fRet;
}

bool DictionaryHelper::getBooleanValue_json(const rapidjson::Value& root,const char* key, bool def)
{
    bool bRet = def;
    do {
        CC_BREAK_IF(root.IsNull());
        CC_BREAK_IF(root[key].IsNull());
        bRet = root[key].GetBool();
    } while (0);
    
    return bRet;
}

const char* DictionaryHelper::getStringValue_json(const rapidjson::Value& root,const char* key, const char *def)
{
    const char* sRet = def;
    do {
        CC_BREAK_IF(root.IsNull());
        CC_BREAK_IF(root[key].IsNull());
        sRet = root[key].GetString();
    } while (0);
    
    return sRet;
}



int DictionaryHelper::getArrayCount_json(const rapidjson::Value& root, const char* key, int def)
{
    int nRet = def;
    do {
        CC_BREAK_IF(root.IsNull());
        CC_BREAK_IF(root[key].IsNull());
        nRet = (int)(root[key].Size());
    } while (0);
    
    return nRet;
}


int DictionaryHelper::getIntValueFromArray_json(const rapidjson::Value& root,const char* arrayKey,int idx, int def)
{
    int nRet = def;
    do {
        CC_BREAK_IF(root.IsNull());
        CC_BREAK_IF(root[arrayKey].IsNull());
        CC_BREAK_IF(root[arrayKey][idx].IsNull());
        nRet = root[arrayKey][idx].GetInt();
    } while (0);
    
    return nRet;
}


float DictionaryHelper::getFloatValueFromArray_json(const rapidjson::Value& root,const char* arrayKey,int idx, float def)
{
    float fRet = def;
    do {
        CC_BREAK_IF(root.IsNull());
        CC_BREAK_IF(root[arrayKey].IsNull());
        CC_BREAK_IF(root[arrayKey][idx].IsNull());
        fRet = (float)root[arrayKey][idx].GetDouble();
    } while (0);
    
    return fRet;
}

bool DictionaryHelper::getBoolValueFromArray_json(const rapidjson::Value& root,const char* arrayKey,int idx, bool def)
{
	bool bRet = def;
    do {
        CC_BREAK_IF(root.IsNull());
        CC_BREAK_IF(root[arrayKey].IsNull());
        CC_BREAK_IF(root[arrayKey][idx].IsNull());
        bRet = root[arrayKey][idx].GetBool();
    } while (0);
    
    return bRet;
}

const char* DictionaryHelper::getStringValueFromArray_json(const rapidjson::Value& root,const char* arrayKey,int idx, const char *def)
{
    const char *sRet = def;
    do {
        CC_BREAK_IF(root.IsNull());
        CC_BREAK_IF(root[arrayKey].IsNull());
        CC_BREAK_IF(root[arrayKey][idx].IsNull());
        sRet = root[arrayKey][idx].GetString();
    } while (0);
    
    return sRet;
}

const rapidjson::Value &DictionaryHelper::getDictionaryFromArray_json(const rapidjson::Value &root, const char* key,int idx)
{
	return root[key][idx];
}

bool DictionaryHelper::checkObjectExist_json(const rapidjson::Value &root)
{
    bool bRet = false;
    do {
        CC_BREAK_IF(root.IsNull());
        bRet = true;
    } while (0);
    
    return bRet;
}

bool DictionaryHelper::checkObjectExist_json(const rapidjson::Value &root,const char* key)
{
    bool bRet = false;
    do {
        CC_BREAK_IF(root.IsNull());
        bRet = root.HasMember(key);
    } while (0);
    
    return bRet;
}

bool DictionaryHelper::checkObjectExist_json(const rapidjson::Value &root, int index)
{
    bool bRet = false;
    do {   
        CC_BREAK_IF(root.IsNull());
        CC_BREAK_IF(!root.IsArray());
        CC_BREAK_IF(index < 0 || root.Size() <= (unsigned int )index);
        bRet = true;
    } while (0);

    return bRet;
}

}
