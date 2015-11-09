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

#ifndef __CC_EXTENTIONS_CCCOMATTRIBUTE_H__
#define __CC_EXTENTIONS_CCCOMATTRIBUTE_H__

#include "CCComBase.h"
#include "2d/CCComponent.h"
#include "base/CCValue.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

/** 
 * @class ComAttribute
 * @brief @~english ComAttribute.
 * @~chinese 自定义属性组件.
 * @details @~english Store and access data by key-value, and load exporting data of cocos studio 1.x Scene Editor.
 * @~chinese 以key-value键值对方式存储与获取数据, 解析cocos studio 1.x场景编辑器导出的数据.
*/
class CC_STUDIO_DLL ComAttribute : public cocos2d::Component
{
    DECLARE_CLASS_COMPONENT_INFO
public:
    /**
     * @brief @~english ComAttribute constructor.
     * @~chinese 自定义属性构造函数。
     * @js ctor
     */
    ComAttribute(void);
    /**
     * @brief @~english ComAttribute destructor.
     * @~chinese 自定义属性析构函数。
     * @js NA
     * @lua NA
     */
    virtual ~ComAttribute(void);
    
public:
    const static std::string COMPONENT_NAME;

    /**
     * @brief @~english Allocates and initializes a ComAttribute.
     * @~chinese 分配并且初始化自定义组件。
     * @return @~english A initialized ComAttribute which is marked as "autorelease".
     * @~chinese 一个初始化的自定义组件，该节点会自动被标记为“autorelease”(自动释放)。
     */
    static ComAttribute* create(void);

    /**
     * @brief @~english Initialize a ComAttribute.
     * @~chinese 初始化自定义组件。
     * @return @~english true initialize successfully false failed to initialize.
     * @~chinese true 初始化成功，否则false。
     */
    virtual bool init() override;

    /**
     * @brief @~english Deserialization export data of cocos studio 1.x scene editor.
     * @~chinese 反序列化cocos studio 1.x 场景编辑器导出的数据。
     * @param r @~english SerData object point.
     * @~chinese SerData对象指针。
     * @return @~english true deserialize successfully false failed to deserialize.
     * @~chinese true 反序列化成功，否则false。
     */
    virtual bool serialize(void* r) override;

    /**
     * @brief @~english Set int value for key.
     * @~chinese 设置属性名为为key，类型为int的数值。
     * @param key @~english The key to set.
     * @~chinese 需要设置的key。
     * @param value @~english A int value to set to the key.
     * @~chinese 类型为int的数值。
     */
    void setInt(const std::string& key, int value);

    /**
     * @brief @~english Set float value for key.
     * @~chinese 设置属性名为为key，类型为float的数值。
     * @param key @~english The key to set.
     * @~chinese 需要设置的key。
     * @param value @~english A float value to set to the key.
     * @~chinese 类型为float的数值。
     */
    void setFloat(const std::string& key, float value);

    /**
     * @brief @~english Set bool value for key.
     * @~chinese 设置属性名为为key，类型为bool的数值。
     * @param key @~english The key to set.
     * @~chinese 需要设置的key。
     * @param value @~english A bool value to set to the key.
     * @~chinese 类型为bool的数值。
     */
    void setBool(const std::string& key, bool value);

    /**
     * @brief @~english Set string value for key.
     * @~chinese 设置属性名为为key，类型为string的数值。
     * @param key @~english The key to set.
     * @~chinese 需要设置的key。
     * @param value @~english A string value to set to the key.
     * @~chinese 类型为string的数值。
     */
    void setString(const std::string& key, const std::string& value);

    /**
     * @brief @~english Get int value by key, if the key doesn't exist, will return passed default value.
     * @~chinese 获取指定 key 的整型值，如果 key 不存在，则返回指定的 def。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的key。
     * @param def @~english The default value to return if the key doesn't exist.
     * @~chinese 返回的默认值。如果key不存在，则返回此值。
     * @return @~english Int value of the key.
     * @~chinese key的整型值。
     */
    int getInt(const std::string& key, int def = 0) const;

    /**
     * @brief @~english Get float value by key, if the key doesn't exist, will return passed default value.
     * @~chinese 获取指定 key 的字符串，如果 key 不存在，则返回指定的 def。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的key。
     * @param def @~english The default value to return if the key doesn't exist.
     * @~chinese 返回的默认值。如果key不存在，则返回此值。
     * @return @~english Float value of the key.
     * @~chinese key的float值。
     */
    float getFloat(const std::string& key, float def = 0.0f) const;

    /**
     * @brief @~english Get bool value by key, if the key doesn't exist, will return passed default value.
     * @~chinese 获取指定 key 的字符串，如果 key 不存在，则返回指定的 def。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的key。
     * @param def @~english The default value to return if the key doesn't exist.
     * @~chinese 返回的默认值。如果key不存在，则返回此值。
     * @return @~english Bool value of the key.
     * @~chinese key的bool值。
     */
    bool getBool(const std::string& key, bool def = false) const;

    /**
     * @brief @~english Get string value by key, if the key doesn't exist, will return passed default value.
     * @~chinese 获取指定 key 的字符串，如果 key 不存在，则返回指定的 def。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的key。
     * @param def @~english The default value to return if the key doesn't exist.
     * @~chinese 返回的默认值。如果key不存在，则返回此值。
     * @return @~english String value of the key.
     * @~chinese key的string值。
     */
    std::string getString(const std::string& key, const std::string& def = "") const;

     /**
     * @brief @~english Parse export json data of cocos studio 1.x Scene Editor and assign to _doc.
     * @~chinese 解析cocos studio 1.x 场景编辑器导出json数据，判断json的有效性，给json对象_doc赋值。
     * @param jsonFile @~english Json file path.
     * @~chinese json路径。
     * @return @~english true parse successfully, false failed to parse.
     * @~chinese true 解析成功，否则false。
     */
    bool parse(const std::string &jsonFile);
private:
   cocos2d::ValueMap _dict;
   rapidjson::Document _doc;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
