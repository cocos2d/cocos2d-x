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
#include "cocostudio/CocosStudioExport.h"

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

    /**
    * Gets the static instance of DictionaryHelper.
    */
    static DictionaryHelper* getInstance();
    /**
    * Destroy DictionaryHelper instance.
    */
    static void destroyInstance();
    
    /**
    * Get a child json item from the root node.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @return child json item
    */
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, const char* key);
    /**
    * Get a child json item from the root node.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @parame idx    index of child json item in root[key]
    *
    * @return child json item
    */
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, const char* key, int idx);
    /**
    * Get a child json item from the root node.
    *
    * @parame root   root node of json
    *
    * @parame idx    index of child json item
    *
    * @return child json item
    */
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, int idx);
    
    /**
    * Get the integer value of a child json item from the root node.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @parame def    default value to be returned if child not found
    *
    * @return integer value of item
    */
    int   getIntValue_json(const rapidjson::Value& root, const char* key, int def = 0);
    /**
    * Get the float value of a child json item from the root node.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @parame def    default value to be returned if child not found
    *
    * @return float value of item
    */
    float getFloatValue_json(const rapidjson::Value& root, const char* key, float def = 0.0f);
    /**
    * Get the boolean value of a child json item from the root node.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @parame def    default value to be returned if child not found
    *
    * @return boolean value of item
    */
    bool  getBooleanValue_json(const rapidjson::Value& root, const char* key, bool def = false);
    /**
    * Get the string value of a child json item from the root node.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @parame def    default value to be returned if child not found
    *
    * @return string value of item
    */
    const char* getStringValue_json(const rapidjson::Value& root, const char* key, const char *def = NULL);
    /**
    * Get the size of a child json array from the root node.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @parame def    default value to be returned if child not found
    *
    * @return size of child json array
    */
    int   getArrayCount_json(const rapidjson::Value& root, const char* key, int def = 0);

    /**
    * Get the integer value at desired index of a child array item from the root node.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @parame idx    index of item in child json
    *
    * @parame def    default value to be returned if child not found
    *
    * @return integer value of item
    */
    int   getIntValueFromArray_json(const rapidjson::Value& root, const char* arrayKey, int idx, int def = 0);
    /**
    * Get the float value at desired index of a child array item from the root node.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @parame idx    index of item in child json
    *
    * @parame def    default value to be returned if child not found
    *
    * @return float value of item
    */
    float getFloatValueFromArray_json(const rapidjson::Value& root, const char* arrayKey, int idx, float def = 0.0f);
    /**
    * Get the boolean value at desired index of a child array item from the root node.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @parame idx    index of item in child json
    *
    * @parame def    default value to be returned if child not found
    *
    * @return boolean value of item
    */
    bool  getBoolValueFromArray_json(const rapidjson::Value& root, const char* arrayKey, int idx, bool def = false);
    /**
    * Get the string value at desired index of a child array item from the root node.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @parame idx    index of item in child json
    *
    * @parame def    default value to be returned if child not found
    *
    * @return string value of item
    */
    const char* getStringValueFromArray_json(const rapidjson::Value& root, const char* arrayKey, int idx, const char *def = NULL);
    /**
    * Get the child json item at desired index of a child array item from the root node.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @parame idx    index of item in child json
    *
    * @return child json item
    */
    const rapidjson::Value &getDictionaryFromArray_json(const rapidjson::Value &root, const char* key, int idx);

    /**
    * Check whether a json item is valid or not.
    *
    * @parame root   root node of json
    *
    * @return if the item is valid return true
    */
    bool checkObjectExist_json(const rapidjson::Value &root);
    /**
    * Check whether a json item is valid or not.
    *
    * @parame root   root node of json
    *
    * @parame key    key of child json item
    *
    * @return if the item is valid return true
    */
    bool checkObjectExist_json(const rapidjson::Value &root, const char* key);
    /**
    * Check whether a json item is valid or not.
    *
    * @parame root   root node of json
    *
    * @parame idx    index of child item
    *
    * @return if the item is valid return true
    */
    bool checkObjectExist_json(const rapidjson::Value &root, int index);
};

}

#endif /* defined(__CocoGUI__DictionaryHelper__) */
