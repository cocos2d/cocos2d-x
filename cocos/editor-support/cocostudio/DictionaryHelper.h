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
    * @~english Gets the static instance of DictionaryHelper.
    * @~chinese 获取DictionaryHelper的静态实例.
    */
    static DictionaryHelper* getInstance();
    /**
    * @~english Destroy DictionaryHelper static instance.
    * @~chinese 释放DictionaryHelper的静态实例.
    */
    static void destroyInstance();
    
    /**
    * @~english Get a child json item from the root node.
    * @~chinese 获取根节点下的一个子json节点.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~chinese key of child json item @~chinese 子json条目的键值
    *
    * @return @~english child json item @~chinese 子json项
    */
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, const char* key);
    /**
    * @~english Get a child json item from the root node.
    * @~chinese 获取根节点下的一个子json节点.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~english key of child json item @~chinese 子json条目的键值
    *
    * @parame idx    @~english index of child json item in root[key] @~chinese 子json在root[key]数组中的索引值
    *
    * @return @~english child json item @~chinese 子json项
    */
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, const char* key, int idx);
    /**
    * @~english Get a child json item from the root node.
    * @~chinese 获取根节点下的一个子json节点.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame idx    @~english index of child json item @~chinese 子json在数组中的索引值
    *
    * @return @~english child json item @~chinese 子json项
    */
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, int idx);

    /**
    * @~english Get the integer value of a child json item from the root node.
    * @~chinese 获取root下一个子节点的整形数值.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~english key of child json item @~chinese 子json条目的键值
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese 如果子节点不存在返回的默认值
    *
    * @return @~english integer value of item @~chinese 子节点的整型数值
    */
    int   getIntValue_json(const rapidjson::Value& root, const char* key, int def = 0);
    /**
    * @~english Get the float value of a child json item from the root node.
    * @~chinese 获取root下一个子节点的浮点数值.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~english key of child json item @~chinese 子json条目的键值
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese 如果子节点不存在返回的默认值
    *
    * @return @~english float value of item @~chinese 子节点的浮点数值
    */
    float getFloatValue_json(const rapidjson::Value& root, const char* key, float def = 0.0f);
    /**
    * @~english Get the boolean value of a child json item from the root node.
    * @~chinese 获取root下一个子节点的布尔型值.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~english key of child json item @~chinese 子json条目的键值
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese 如果子节点不存在返回的默认值
    *
    * @return @~english boolean value of item @~chinese 子节点的布尔型值
    */
    bool  getBooleanValue_json(const rapidjson::Value& root, const char* key, bool def = false);
    /**
    * @~english Get the string value of a child json item from the root node.
    * @~chinese 获取root下一个子节点的布尔型值.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~english key of child json item @~chinese 子json条目的键值
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese 如果子节点不存在返回的默认值
    *
    * @return @~english string value of item @~chinese 子节点的字符串类型值
    */
    const char* getStringValue_json(const rapidjson::Value& root, const char* key, const char *def = NULL);
    /**
    * @~english Get the size of a child json array from the root node.
    * @~chinese 获取根节点下一个数组型子节点的数组大小.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~english key of child json item @~chinese 子json条目的键值
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese 如果子节点不存在返回的默认值
    *
    * @return @~english size of child json array @~chinese 子json数组的大小
    */
    int   getArrayCount_json(const rapidjson::Value& root, const char* key, int def = 0);

    /**
    * @~english Get the integer value at desired index of a child array item from the root node.
    * @~chinese 获取一个子json数组中指定位置节点的整型值.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~english key of child json item @~chinese 子json条目的键值
    *
    * @parame idx    @~english index of item in child json @~chinese 目标对象在子json数组中的索引值
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese 如果子节点不存在返回的默认值
    *
    * @return @~english integer value of item @~chinese 目标项的整型值
    */
    int   getIntValueFromArray_json(const rapidjson::Value& root, const char* arrayKey, int idx, int def = 0);
    /**
    * @~english Get the float value at desired index of a child array item from the root node.
    * @~chinese 获取一个子json数组中指定位置节点的浮点型值.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~english key of child json item @~chinese 子json条目的键值
    *
    * @parame idx    @~english index of item in child json @~chinese 目标对象在子json数组中的索引值
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese 如果子节点不存在返回的默认值
    *
    * @return @~english float value of item @~chinese 目标项的浮点型值
    */
    float getFloatValueFromArray_json(const rapidjson::Value& root, const char* arrayKey, int idx, float def = 0.0f);
    /**
    * @~english Get the boolean value at desired index of a child array item from the root node.
    * @~chinese 获取一个子json数组中指定位置节点的布尔型值.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~english key of child json item @~chinese 子json条目的键值
    *
    * @parame idx    @~english index of item in child json @~chinese 目标对象在子json数组中的索引值
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese 如果子节点不存在返回的默认值
    *
    * @return @~english boolean value of item @~chinese 目标项的布尔型值
    */
    bool  getBoolValueFromArray_json(const rapidjson::Value& root, const char* arrayKey, int idx, bool def = false);
    /**
    * @~english Get the string value at desired index of a child array item from the root node.
    * @~chinese 获取一个子json数组中指定位置节点的字符串值.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~english key of child json item @~chinese 子json条目的键值
    *
    * @parame idx    @~english index of item in child json @~chinese 目标对象在子json数组中的索引值
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese 如果子节点不存在返回的默认值
    *
    * @return @~english string value of item @~chinese 目标项的字符串值
    */
    const char* getStringValueFromArray_json(const rapidjson::Value& root, const char* arrayKey, int idx, const char *def = NULL);
    /**
    * @~english Get the child json item at desired index of a child array item from the root node.
    * @~chinese 获取一个json数组中指定位置的json项.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~english key of child json item @~chinese 子json条目的键值
    *
    * @parame idx    @~english index of item in child json @~chinese 目标对象在子json数组中的索引值
    *
    * @return @~english child json item @~chinese 子json项
    */
    const rapidjson::Value &getDictionaryFromArray_json(const rapidjson::Value &root, const char* key, int idx);

    /**
    * @~english Check whether a json item is valid or not.
    * @~chinese 检测json项是否有效.
    *
    * @parame root   @~english json node to be check @~chinese  待检测的json项
    *
    * @return @~english if the item is valid @~chinese 待检测项是否有效
    */
    bool checkObjectExist_json(const rapidjson::Value &root);
    /**
    * @~english Check whether a json item is valid or not.
    * @~chinese 检测json项是否有效.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame key    @~english key of child json item @~chinese 子节点键值
    *
    * @return @~english if the item is valid @~chinese 待检测项是否有效
    */
    bool checkObjectExist_json(const rapidjson::Value &root, const char* key);
    /**
    * @~english Check whether a json item is valid or not.
    * @~chinese 检测json项是否有效.
    *
    * @parame root   @~english root node of json @~chinese json根节点
    *
    * @parame idx    @~english index of child item @~chinese 子节点索引
    *
    * @return @~english if the item is valid @~chinese 待检测项是否有效
    */
    bool checkObjectExist_json(const rapidjson::Value &root, int index);
};

}

#endif /* defined(__CocoGUI__DictionaryHelper__) */
