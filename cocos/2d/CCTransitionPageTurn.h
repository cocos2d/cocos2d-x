/****************************************************************************
Copyright (c) 2009      Sindesso Pty Ltd http://www.sindesso.com/
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CCPAGE_TURN_TRANSITION_H__
#define __CCPAGE_TURN_TRANSITION_H__

#include "2d/CCTransition.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class NodeGrid;

/**
 * @addtogroup _2d
 * @{
 */


/** 
* @brief @~english A transition which peels back the bottom right hand corner of a scene
to transition to the scene beneath it simulating a page turn.

This uses a 3DAction so it's strongly recommended that depth buffering
is turned on in Director using:

 Director::getInstance()->setDepthBufferFormat(kDepthBuffer16);

 * @~chinese 一个场景过渡, 揭开场景的右下角过渡到下一个场景，模拟翻页效果。
 * 
 * 这将使用一个3DAction,所以强烈建议在Director中开启深度缓冲区
 * 用法：
 * 
 * Director::getInstance()->setDepthBufferFormat(kDepthBuffer16);
 * 
 @since v0.8.2
*/

class CC_DLL TransitionPageTurn : public TransitionScene
{
public:
    /**@~english
     * Creates a base transition with duration and incoming scene.
     * If back is true then the effect is reversed to appear as if the incoming
     * scene is being turned from left over the outgoing scene.
     *
     * @~chinese 
     * 使用 duration、传入的scene 创建一个翻页效果过渡.
     * If back is true then the effect is reversed to appear as if the incoming
     * 如果backwards为true，那么效果将采取反转
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @param backwards @~english If back is true then the effect is reversed to appear as if the incoming scene is being turned from left over the outgoing scene.
     * @~chinese 如果backwards为true，那么效果将采取反转，看起来好像是从传入的场景翻开到从切出的场景。
     * @return @~english An autoreleased TransitionPageTurn object.
     * @~chinese autoreleased TransitionPageTurn对象。
     */

    static TransitionPageTurn* create(float t,Scene* scene,bool backwards);
    
    //
    // Overrides
    // @js NA
    //
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    /**@~english
     * Creates a base transition with duration and incoming scene.
     * If back is true then the effect is reversed to appear as if the incoming
     * scene is being turned from left over the outgoing scene.
     *
     * @~chinese 
     * 使用 duration、传入的scene 初始化翻页效果过渡。
     * 如果backwards为true，那么效果将采取反转
     * 看起来好像是从传入的场景翻开到从切出的场景。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @param backwards @~english If back is true then the effect is reversed to appear as if the incoming scene is being turned from left over the outgoing scene.
     * @~chinese 如果backwards为true，那么效果将采取反转，看起来好像是从传入的场景翻开到从切出的场景。
     * @return @~english True if initialize success.
     * @~chinese 如果初始化成功则返回true。
     */

    bool initWithDuration(float t,Scene* scene,bool backwards);

    /** @~english Returns the action that will be performed with size.
     *
     * @~chinese 返回将要被执行的action。
     * 
     * @param vector @~english A given size.
     * @~chinese 一个给定的大小。
     * @return @~english The action that will be performed.
     * @~chinese 将要被执行的action。
     */

    ActionInterval* actionWithSize(const Size& vector);

    //
    // Overrides
    //
    virtual void onEnter() override;
    virtual void onExit() override;

CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */

    TransitionPageTurn();
    /**
     * @js NA
     * @lua NA
     */

    virtual ~TransitionPageTurn();

protected:
    virtual void sceneOrder() override;

protected:
    NodeGrid* _inSceneProxy;
    NodeGrid* _outSceneProxy;
    bool    _back;
};

// end of _2d group
/// @}

NS_CC_END

#endif // __CCPAGE_TURN_TRANSITION_H__

