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
 @类名 ComAttribute
 @主题 自定义属性组件
 @细节 以key-value键值对方式存储与获取数据, 配合解析cocos studio 1.x场景编辑器导出的数据
 @组 组件
 */
class CC_STUDIO_DLL ComAttribute : public cocos2d::Component
{
    DECLARE_CLASS_COMPONENT_INFO
public:
    /**
     * @js ctor
     */
    /**
    @主题 自定义属性组建构造函数
    */
    ComAttribute(void);
    /**
     * @js NA
     * @lua NA
     */
    /**
    @主题 自定义属性析构函数
    */
    virtual ~ComAttribute(void);
    
public:
   /**
    @主题 创建属性组件
    @返回 属性组件指针
    */
    static ComAttribute* create(void);
    /**
    @主题 初始化属性组件
    @返回 true 初始化成功，否则false
    */
    virtual bool init() override;
    /**
    @主题 反序列化cocos studio 1.x 场景编辑器导出的数据
    @参数 r SerData对象指针
    @返回 true 反序列化成功，否则false
    */
    virtual bool serialize(void* r) override;
    /**
    @主题 设置属性名为为key，类型为int的数值。
    @参数 key 属性名称
    @参数 value 类型为int的数值
    @返回 无
    */
    void setInt(const std::string& key, int value);
    /**
    @主题 设置属性名为为key，类型为float的数值。
    @参数 key 属性名称
    @参数 value 类型为float的数值
    @返回 无
    */
    void setFloat(const std::string& key, float value);
    /**
    @主题 设置属性名为为key，类型为bool的数值。
    @参数 key 属性名称
    @参数 value 类型为bool的数值
    @返回 无
    */
    void setBool(const std::string& key, bool value);
    /**
    @主题 设置属性名为为key，类型为std::string的数值。
    @参数 key 属性名称
    @参数 value 类型为std::string的数值
    @返回 无
    */
    void setString(const std::string& key, const std::string& value);
    /**
    @主题 返回属性名为为key，类型为int的数值
    @参数 key 属性名称
    @参数 def 类型为int的数值，默认为0
    @返回 如果找到返回对应的数值，否则返回def 
    */
    int getInt(const std::string& key, int def = 0) const;
    /**
    @主题 返回属性名为为key，类型为float的数值
    @参数 key 属性名称
    @参数 def 类型为float的数值，默认为0
    @返回 如果找到返回对应的数值，否则返回def 
    */
    float getFloat(const std::string& key, float def = 0.0f) const;
    /**
    @主题 返回属性名为为key，类型为bool的数值
    @参数 key 属性名称
    @参数 def 类型为bool的数值，默认为0
    @返回 如果找到返回对应的数值，否则返回def 
    */
    bool getBool(const std::string& key, bool def = false) const;
    /**
    @主题 返回属性名为为key，类型为std::string的数值
    @参数 key 属性名称
    @参数 def 类型为std::string的数值，默认为空字符串
    @返回 如果找到返回对应的数值，否则返回def 
    */
    std::string getString(const std::string& key, const std::string& def = "") const;
     /**
    @主题 当cocos studio 1.x 场景编辑器导出json数据的时候，判断json的有效性，解析json，给_doc赋值
    @参数 jsonFile cocos studio 1.x 场景编辑器导出的json路径
    @返回 true 解析成功，否则false
    */
    bool parse(const std::string &jsonFile);
private:
   cocos2d::ValueMap _dict;
   rapidjson::Document _doc;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
