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

#include "cocostudio/DictionaryHelper.h"

namespace cocostudio {
    
static DictionaryHelper* sharedHelper = nullptr;

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

cocos2d::Dictionary* DictionaryHelper::getSubDictionary(cocos2d::Dictionary* root,const char* key)
{
    if (!root) {
        return nullptr;
    }
    cocos2d::Object* obj = root->objectForKey(key);
    if (!obj) {
        return nullptr;
    }
    return (cocos2d::Dictionary*)(obj);
}

int DictionaryHelper::getIntValue(cocos2d::Dictionary* root,const char* key)
{
    if (!root) {
        return 0;
    }
    cocos2d::Object* obj = root->objectForKey(key);
    if (!obj) {
        return 0;
    }
    
    cocos2d::String* cstr = (cocos2d::String*)(obj);
    return cstr->intValue();
}

float DictionaryHelper::getFloatValue(cocos2d::Dictionary* root,const char* key)
{
    if (!root) {
        return 0.0;
    }
    cocos2d::Object* obj = root->objectForKey(key);
    if (!obj) {
        return 0.0f;
    }
    cocos2d::String* cstr = (cocos2d::String*)(obj);
    return cstr->floatValue();
}

const char* DictionaryHelper::getStringValue(cocos2d::Dictionary* root,const char* key)
{
    if (!root) {
        return nullptr;
    }
    cocos2d::Object* obj = root->objectForKey(key);
    if (!obj) {
        return nullptr;
    }
    cocos2d::String* cstr = (cocos2d::String*)(obj);
    return cstr->_string.c_str();
}

bool DictionaryHelper::getBooleanValue(cocos2d::Dictionary* root,const char* key)
{
    return (getIntValue( root, key ) != 0);
}

cocos2d::Array* DictionaryHelper::getArrayValue(cocos2d::Dictionary *root, const char *key)
{
    if (!root) {
        return nullptr;
    }
    cocos2d::Object* obj = root->objectForKey(key);
    if (!obj) {
        return nullptr;
    }
    cocos2d::Array* array = (cocos2d::Array*)(obj);
    return array;
}

cocos2d::Object* DictionaryHelper::checkObjectExist(cocos2d::Dictionary *root, const char *key)
{
    if (!root) {
        return nullptr;
    }
    return root->objectForKey(key);
}

int DictionaryHelper::objectToIntValue(cocos2d::Object *obj)
{
    if (!obj)
    {
        return 0;
    }
    cocos2d::String* cstr = (cocos2d::String*)(obj);
    return cstr->intValue();
}

float DictionaryHelper::objectToFloatValue(cocos2d::Object *obj)
{
    if (!obj)
    {
        return 0.0f;
    }
    cocos2d::String* cstr = (cocos2d::String*)(obj);
    return cstr->floatValue();
}

const char* DictionaryHelper::objectToStringValue(cocos2d::Object *obj)
{
    if (!obj)
    {
        return nullptr;
    }
    cocos2d::String* cstr = (cocos2d::String*)(obj);
    return cstr->_string.c_str();
}

bool DictionaryHelper::objectToBooleanValue(cocos2d::Object *obj)
{
    if (!obj)
    {
        return false;
    }
    return (objectToIntValue( obj ) != 0);
}

cocos2d::Array* DictionaryHelper::objectToCCArray(cocos2d::Object *obj)
{
    if (!obj)
    {
        return nullptr;
    }
    cocos2d::Array* array = (cocos2d::Array*)(obj);
    return array;
}

JsonDictionary* DictionaryHelper::getSubDictionary_json(JsonDictionary* root,const char* key)
{
    if (!root)
    {
        return nullptr;
    }
    return root->getSubDictionary(key);
}

int DictionaryHelper::getIntValue_json(JsonDictionary* root,const char* key)
{
    if (!root)
    {
        return 0;
    }
    return root->getItemIntValue(key, 0);
}

float DictionaryHelper::getFloatValue_json(JsonDictionary* root,const char* key)
{
    if (!root)
    {
        return 0.0f;
    }
    return root->getItemFloatValue(key, 0.0);
}

const char* DictionaryHelper::getStringValue_json(JsonDictionary* root,const char* key)
{
    if (!root)
    {
        return nullptr;
    }
    return root->getItemStringValue(key);
}

bool DictionaryHelper::getBooleanValue_json(JsonDictionary* root,const char* key)
{
    if (!root)
    {
        return 0;
    }
    return root->getItemBoolvalue(key, false);
}

int DictionaryHelper::getArrayCount_json(JsonDictionary* root,const char* key)
{
    if (!root)
    {
        return 0;
    }
    return root->getArrayItemCount(key);
}

int DictionaryHelper::getIntValueFromArray_json(JsonDictionary* root,const char* arrayKey,int idx)
{
    if (!root)
    {
        return 0;
    }
    return root->getIntValueFromArray(arrayKey, idx, 0);
}

float DictionaryHelper::getFloatValueFromArray_json(JsonDictionary* root,const char* arrayKey,int idx)
{
    if (!root)
    {
        return 0.0f;
    }
    return root->getFloatValueFromArray(arrayKey, idx, 0.0);
}

bool DictionaryHelper::getBoolValueFromArray_json(JsonDictionary* root,const char* arrayKey,int idx)
{
    if (!root)
    {
        return false;
    }
    return root->getBoolValueFromArray(arrayKey, idx, false);
}

const char* DictionaryHelper::getStringValueFromArray_json(JsonDictionary *root, const char *arrayKey, int idx)
{
    if (!root)
    {
        return nullptr;
    }
    return root->getStringValueFromArray(arrayKey, idx);
}

JsonDictionary* DictionaryHelper::getDictionaryFromArray_json(JsonDictionary* root,const char* arrayKey,int idx)
{
    if (!root)
    {
        return nullptr;
    }
    return root->getSubItemFromArray(arrayKey, idx);
}

bool DictionaryHelper::checkObjectExist_json(JsonDictionary *root, const char *key)
{
    if (!root)
    {
        return false;
    }
    return root->isKeyValidate(key);
}

}