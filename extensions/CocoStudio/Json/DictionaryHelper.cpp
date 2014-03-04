/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "DictionaryHelper.h"

NS_CC_EXT_BEGIN
    
static DictionaryHelper* sharedHelper = NULL;

DictionaryHelper::DictionaryHelper()
{
    
}

DictionaryHelper::~DictionaryHelper()
{
    
}

DictionaryHelper* DictionaryHelper::shareHelper()
{
    if (!sharedHelper) {
        sharedHelper = new DictionaryHelper();
    }
    return sharedHelper;
}

void DictionaryHelper::purgeDictionaryHelper()
{
	 CC_SAFE_DELETE(sharedHelper);
}

cocos2d::CCDictionary* DictionaryHelper::getSubDictionary(cocos2d::CCDictionary* root,const char* key)
{
    if (!root) {
        return NULL;
    }
    cocos2d::CCObject* obj = root->objectForKey(key);
    if (!obj) {
        return NULL;
    }
    return (cocos2d::CCDictionary*)(obj);
}

int DictionaryHelper::getIntValue(cocos2d::CCDictionary* root,const char* key)
{
    if (!root) {
        return 0;
    }
    cocos2d::CCObject* obj = root->objectForKey(key);
    if (!obj) {
        return 0;
    }
    
    cocos2d::CCString* cstr = (cocos2d::CCString*)(obj);
    return cstr->intValue();
}

float DictionaryHelper::getFloatValue(cocos2d::CCDictionary* root,const char* key)
{
    if (!root) {
        return 0.0;
    }
    cocos2d::CCObject* obj = root->objectForKey(key);
    if (!obj) {
        return 0.0f;
    }
    cocos2d::CCString* cstr = (cocos2d::CCString*)(obj);
    return cstr->floatValue();
}

const char* DictionaryHelper::getStringValue(cocos2d::CCDictionary* root,const char* key)
{
    if (!root) {
        return NULL;
    }
    cocos2d::CCObject* obj = root->objectForKey(key);
    if (!obj) {
        return NULL;
    }
    cocos2d::CCString* cstr = (cocos2d::CCString*)(obj);
    return cstr->m_sString.c_str();
}

bool DictionaryHelper::getBooleanValue(cocos2d::CCDictionary* root,const char* key)
{
    return 0 == this->getIntValue(root, key) ? false : true;
}

cocos2d::CCArray* DictionaryHelper::getArrayValue(cocos2d::CCDictionary *root, const char *key)
{
    if (!root) {
        return NULL;
    }
    cocos2d::CCObject* obj = root->objectForKey(key);
    if (!obj) {
        return NULL;
    }
    cocos2d::CCArray* array = (cocos2d::CCArray*)(obj);
    return array;
}

cocos2d::CCObject* DictionaryHelper::checkObjectExist(cocos2d::CCDictionary *root, const char *key)
{
    if (!root) {
        return NULL;
    }
    return root->objectForKey(key);
}

int DictionaryHelper::objectToIntValue(cocos2d::CCObject *obj)
{
    if (!obj)
    {
        return 0;
    }
    cocos2d::CCString* cstr = (cocos2d::CCString*)(obj);
    return cstr->intValue();
}

float DictionaryHelper::objectToFloatValue(cocos2d::CCObject *obj)
{
    if (!obj)
    {
        return 0.0f;
    }
    cocos2d::CCString* cstr = (cocos2d::CCString*)(obj);
    return cstr->floatValue();
}

const char* DictionaryHelper::objectToStringValue(cocos2d::CCObject *obj)
{
    if (!obj)
    {
        return NULL;
    }
    cocos2d::CCString* cstr = (cocos2d::CCString*)(obj);
    return cstr->m_sString.c_str();
}

bool DictionaryHelper::objectToBooleanValue(cocos2d::CCObject *obj)
{
    if (!obj)
    {
        return 0;
    }
    return this->objectToIntValue(obj) != 0? true:false;
}

cocos2d::CCArray* DictionaryHelper::objectToCCArray(cocos2d::CCObject *obj)
{
    if (!obj)
    {
        return NULL;
    }
    cocos2d::CCArray* array = (cocos2d::CCArray*)(obj);
    return array;
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

NS_CC_EXT_END