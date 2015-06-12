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
 * @class ComRender
 * @brief @~english ComRender.
 * @~chinese 渲染组件.
 * @details @~english Package render the target object of cocos2d-x, to ensure consistency component implementation.
 * @~chinese 渲染组件 包装挂载到对象的渲染对象,确保组件实现的一致性.
*/
class CC_STUDIO_DLL ComRender : public cocos2d::Component
{
    DECLARE_CLASS_COMPONENT_INFO
CC_CONSTRUCTOR_ACCESS:
    /**
     * @brief @~english ComRender constructor.
     * @~chinese 渲染组件构造函数。
     * @js ctor
     */
    ComRender(void);

    /**
    @主题 渲染组件构造函数
    @参数 node 包装渲染对象指针
    @参数 comName 渲染组件名称
    */
    /**
     * @brief @~english ComRender constructor.
     * @~chinese 渲染组件构造函数。
     * @param node @~english Node point 
     * @~chinese 渲染对象指针
     * @param comName @~english component name 
     * @~chinese 组件名称
     * @js ctor
     */
    ComRender(cocos2d::Node *node, const char *comName);

    /**
     * @brief @~english ComRender destructor.
     * @~chinese 渲染组件析构函数。
     * @js NA
     * @lua NA
     */
    virtual ~ComRender(void);
    
public:
    /**
     * @brief @~english Event callback that is invoked every time when Node enters the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition starts.
     * During onEnter you can't access a "sister/brother" node.
     * If you override onEnter, you shall call its parent's one, e.g., Node::onEnter().
     * @~chinese 每次当Node进入“stage”时才调用事件回调。
     * 如果Node进入“stage”状态时伴随着一个转换（transition）,那么事件将会在这个转换开始的时候被调用。
     * 在onEnter过程中，你不能够接入“sister/brother”兄妹节点。
     * 如果你重写了onEnter方法，你应该调用它的父类，e.g., Node::onEnter().
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;

    /**
     * @brief @~english Event callback that is invoked every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
     * During onExit you can't access a sibling node.
     * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
     * @~chinese 每次当Node离开“stage”时才调用事件回调。
     * 如果Node离开“stage”状态时伴随着一个转换（transition）, 那么事件将会在这个转换结束的时候被调用。
     * 在onEnter过程中中你不能够接入一个兄妹节点。
     * 如果你重写onExit, 你应该调用它的父类, e.g., Node::onExit().
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;

    /**
     * @brief @~english deserialization export data of cocos studio 1.x scene editor.
     * @~chinese 反序列化cocos studio 1.x 场景编辑器导出的数据。
     * @param r @~english SerData object point.
     * @~chinese SerData对象指针。
     * @return @~english true deserialize successfully false failed to deserialize.
     * @~chinese true 反序列化成功，否则false。
     */
    virtual bool serialize(void* r) override;

    /**
     * @brief @~english get Node point.
     * @~chinese 获取渲染对象指针。
     */
    virtual cocos2d::Node* getNode();

    /**
     * @brief @~english set Node point.
     * @~chinese 设置渲染组件包装的渲染对象指针。
     */
    virtual void setNode(cocos2d::Node *node);

    /**
     * @brief @~english Allocates and initializes a ComRender.
     * @~chinese 分配并且初始化渲染组件。
     * @return @~english A initialized ComRender which is marked as "autorelease".
     * @~chinese 一个初始化的自定义组件，该节点会自动被标记为“autorelease”(自动释放)。
     */
    static ComRender* create(void);

    /**
     * @brief @~english Allocates and initializes a ComRender.
     * @~chinese 分配并且初始化渲染组件。
     * @param node @~english Node point 
     * @~chinese 渲染对象指针
     * @param comName @~english component name 
     * @~chinese 组件名称
     * @return @~english A initialized ComRender which is marked as "autorelease".
     * @~chinese 一个初始化的自定义组件，该节点会自动被标记为“autorelease”(自动释放)。
     */
    static ComRender* create(cocos2d::Node *node, const char *comName);
private:
     /**
     * @brief @~english Parse export json data of cocos studio 1.x Scene Editor and assign to doc.
     * @~chinese 解析cocos studio 1.x 场景编辑器导出json数据，判断json的有效性，给json对象doc赋值。
     * @param fileName @~english json file path.
     * @~chinese json路径。
     * @param doc @~english json data object
     * @~chinese json数据对象。
     * @return @~english true parse successfully, false failed to parse.
     * @~chinese true 解析成功，否则false。
     */
    bool readJson(const std::string &fileName, rapidjson::Document &doc);

private:
    cocos2d::Node *_render;
};

}
#endif  // __FUNDATION__CCCOMPONENT_H__
