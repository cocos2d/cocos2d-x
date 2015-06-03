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

#ifndef __CC_EXTENTIONS_CCCOMRENDER_H__
#define __CC_EXTENTIONS_CCCOMRENDER_H__

#include "CCComBase.h"
#include "2d/CCComponent.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

 /** 
 @类名 ComRender
 @主题 渲染组件 包装挂载到对象的渲染对象,确保组件实现的一致性
 @细节 实现获取对象的渲染对象
 @组 组件
 */
class CC_STUDIO_DLL ComRender : public cocos2d::Component
{
    DECLARE_CLASS_COMPONENT_INFO
CC_CONSTRUCTOR_ACCESS:
    /**
     *  @js ctor
     */
    /**
    @主题 渲染组件构造函数
    */
    ComRender(void);
    /**
    @主题 渲染组件构造函数
    @参数 node 包装渲染对象指针
    @参数 comName 渲染组件名称
    */
    ComRender(cocos2d::Node *node, const char *comName);
    /**
     * @js NA
     * @lua NA
     */
    /**
    @主题 渲染组件析构函数
    */
    virtual ~ComRender(void);
    
public:
    /**
     * @js NA
     * @lua NA
     */
    /**
    @主题 node调用onEnter的时候，会调用组件的onEnter
    @返回 无
    */
    virtual void onEnter() override;
    /**
     * @js NA
     * @lua NA
     */
    /**
    @主题 node调用onExit的时候，会调用组件的onExit
    @返回 无
    */
    virtual void onExit() override;
    /**
    @主题 根据cocos studio 1.x 场景编辑器导出的数据反序列化
    @参数 r SerData对象指针
    @返回 true 反序列化成功，false 反序列化失败
    */
    virtual bool serialize(void* r) override;
    /**
    @主题 获取渲染组件包装的渲染对象的指针
    @返回 渲染对象指针
    */
    virtual cocos2d::Node* getNode();
    /**
    @主题 设置渲染组件包装的渲染对象指针
    @参数 渲染对象指针
    @返回 无
    */
    virtual void setNode(cocos2d::Node *node);
   /**
    @主题 创建渲染组件
    @返回 渲染组件指针
    */
    static ComRender* create(void);
   /**
    @主题 根据渲染对象指针与组建名称创建渲染组件
    @参数 node 渲染对象指针
    @参数 comName 渲染组件名称
    @返回 渲染组件指针
    */
    static ComRender* create(cocos2d::Node *node, const char *comName);
private:
    /**
    @主题 解析cocos studio 1.x 场景编辑器导出的json数据，给doc赋值
    @参数 fileName cocos studio 1.x 场景编辑器导出的json路径
    @参数 doc json对象
    @返回 true 解析json成功，否则解析json失败
    */
    bool readJson(const std::string &fileName, rapidjson::Document &doc);

private:
    cocos2d::Node *_render;
};

}
#endif  // __FUNDATION__CCCOMPONENT_H__
