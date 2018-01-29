/****************************************************************************
Copyright (c) 2009      Sindesso Pty Ltd http://www.sindesso.com/
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

/** @class TransitionPageTurn
* @brief A transition which peels back the bottom right hand corner of a scene
to transition to the scene beneath it simulating a page turn.

This uses a 3DAction so it's strongly recommended that depth buffering
is turned on in Director using:

 Director::getInstance()->setDepthBufferFormat(kDepthBuffer16);

 @since v0.8.2
*/
class CC_DLL TransitionPageTurn : public TransitionScene
{
public:
    /**
     * Creates a base transition with duration and incoming scene.
     * If back is true then the effect is reversed to appear as if the incoming
     * scene is being turned from left over the outgoing scene.
     *
     * @param t Duration time, in seconds.
     * @param scene A given scene.
     * @param backwards If back is true then the effect is reversed to appear as if the incoming scene is being turned from left over the outgoing scene.
     * @return An autoreleased TransitionPageTurn object.
     */
    static TransitionPageTurn* create(float t,Scene* scene,bool backwards);
    
    //
    // Overrides
    // @js NA
    //
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    /**
     * Creates a base transition with duration and incoming scene.
     * If back is true then the effect is reversed to appear as if the incoming
     * scene is being turned from left over the outgoing scene.
     *
     * @param t Duration time, in seconds.
     * @param scene A given scene.
     * @param backwards If back is true then the effect is reversed to appear as if the incoming scene is being turned from left over the outgoing scene.
     * @return True if initialize success.
     */
    bool initWithDuration(float t,Scene* scene,bool backwards);

    /** Returns the action that will be performed with size.
     *
     * @param vector A given size.
     * @return The action that will be performed.
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

