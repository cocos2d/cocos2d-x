/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Valentin Milea
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
CopyRight (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __ACTION_CCACTION_MANAGER_H__
#define __ACTION_CCACTION_MANAGER_H__

#include "2d/CCAction.h"
#include "base/CCVector.h"
#include "base/CCRef.h"

NS_CC_BEGIN

struct _hashElement;

/**
 * @addtogroup actions
 * @{
 */

/** 
 @brief ActionManager is a singleton that manages all the actions.
 Normally you won't need to use this singleton directly. 99% of the cases you will use the Node interface,
 which uses this singleton.
 But there are some cases where you might need to use this singleton.
 Examples:
    - When you want to run an action where the target is different from a Node. 
    - When you want to pause / resume the actions
 
 @since v0.8
 */
class CC_DLL ActionManager : public Ref
{
public:
    /**
     * @js ctor
     */
    ActionManager(void);
    /**
     * @js NA
     * @lua NA
     */
    ~ActionManager(void);

    // actions
    
     /** 为一个目标添加动作。
	 如果目标已经存在，动作将被加在已经存在的目标上。
     	 如果目标不存在，将会创建这个目标的新对象，这个动作将被添加在这个新创建出来的对象上
     	 当目标动作被暂停，动作队列的顺序也不会乱。
     */
    void addAction(Action *action, Node *target, bool paused);

    /** 移除所有动作。
    */
    void removeAllActions();

     /** 移除某一个Node身上的所有动作。
	 所有属于这个Node身上的动作都将被移除。
    */
    void removeAllActionsFromTarget(Node *target);

    /** 移除一个指定的动作
    */
    void removeAction(Action *action);

    /** 通过指定tag移除目标动作 */
    void removeActionByTag(int tag, Node *target);

     /** 通过指定tag得到目标动作
	 @return the Action the with the given tag
    */
    Action* getActionByTag(int tag, const Node *target) const;

    /** 返回指定目标执行动作的个数
     *   组合动作算1个动作。例如：
     * - 如果你执行一个包含7个动作的Sequence，返回值为1。
     * - 如果你执行7个动作的Sequence，每个包含2个动作，返回值为7。
     */
    ssize_t getNumberOfRunningActionsInTarget(const Node *target) const;

    /** @deprecated use getNumberOfRunningActionsInTarget() instead*/
    CC_DEPRECATED_ATTRIBUTE inline ssize_t numberOfRunningActionsInTarget(Node *target) const { return getNumberOfRunningActionsInTarget(target); }

    /** 暂停目标动作：所有正在该目标执行的动作或者新加入的动作都将被暂停。
   */
    void pauseTarget(Node *target);

    /** 恢复目标动作。所有的动作都将被恢复。
    */
    void resumeTarget(Node *target);
    
     /** 暂停所有正在执行的动作，返回所有被暂停动作的Node的并且把所有Node装到Vector里。
     */
    Vector<Node*> pauseAllRunningActions();
    
     /** 恢复一个目标的动作（这个目标是pauseAllRunningActions返回值里的一个Node）
     */
    void resumeTargets(const Vector<Node*>& targetsToResume);

    void update(float dt);
    
protected:
    // declared in ActionManager.m

    void removeActionAtIndex(ssize_t index, struct _hashElement *element);
    void deleteHashElement(struct _hashElement *element);
    void actionAllocWithHashElement(struct _hashElement *element);

protected:
    struct _hashElement    *_targets;
    struct _hashElement    *_currentTarget;
    bool            _currentTargetSalvaged;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCACTION_MANAGER_H__
