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

#ifndef __CC_EXTENTIONS_CCCOMCONTROLLER_H__
#define __CC_EXTENTIONS_CCCOMCONTROLLER_H__

#include "CCComBase.h"
#include "cocostudio/CCInputDelegate.h"
#include "cocostudio/CocosStudioExport.h"
#include "2d/CCComponent.h"

namespace cocostudio {
/** 
 * @class ComController
 * @brief @~english ComController.
 * @~chinese 逻辑组件.
 * @details @~english you can get input and calling each frame when attach ComController component.
 * @~chinese 实现对象逻辑的组件，可以获取输入以及每帧调用.
*/
class CC_STUDIO_DLL ComController : public cocos2d::Component, public InputDelegate
{

    DECLARE_CLASS_COMPONENT_INFO
public:
    /**
     * @brief @~english ComController constructor.
     * @~chinese 逻辑组件构造函数。
     * @js ctor
     */
    ComController(void);
    
public:
    /**
     * @brief @~english ComController destructor.
     * @~chinese 逻辑组件析构函数。
     * @js NA
     * @lua NA
     */
    virtual ~ComController(void);

    /**
     * @brief @~english Initialize a ComController.
     * @~chinese 初始化逻辑组件。
     * @return @~english true initialize successfully false failed to initialize.
     * @~chinese true 初始化成功，否则false。
     */
    virtual bool init() override;

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
     * @~english Schedules the "update" method.
     *
     * It will use the order number 0. This method will be called every frame.
     * Scheduled methods with a lower order value will be called before the ones that have a higher order value.
     * Only one "update" method could be scheduled per node.
     * @~chinese 调度"update"方法。
     *
     * 它的优先级将会是0，这个方法将会在每一帧都被调用。
     * 拥有较小优先数值的调度方法将会在有拥用较大优先数值的方法之前被调用。
     * 每一个节点只有一"update"能够被调度(你不能够有2个“update”选择器)。
     * @lua NA
     */
    virtual void update(float delta) override;

    /** 
     * @brief @~english Returns whether or not the ComAudio is enabled.
     * @~chinese 返回声音组件是否被启用。
     * @return @~english Whether or not the ComAudio is enabled. 
     * @~chinese 声音组件是否被启用。
     */
    virtual bool isEnabled() const override;

    /**  
     * @brief @~english Enables or disables the ComAudio.
     * @~chinese 启用或禁用声音组件。
     * @param enabled @~english true enable the ComAudio, false disabled the ComAudio. 
     * @~chinese true，启用声音组件 false，禁用声音组件。
     */
    virtual void setEnabled(bool b) override;

    /**
     * @brief @~english Allocates and initializes a create.
     * @~chinese 分配并且初始化逻辑组件。
     * @return @~english A initialized ComController which is marked as "autorelease".
     * @~chinese 一个初始化的逻辑组件，该节点会自动被标记为“autorelease”(自动释放)。
     */
    static ComController* create(void);
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
