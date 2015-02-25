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

class Action;

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
    
    /** Adds an action with a target. 
     If the target is already present, then the action will be added to the existing target.
     If the target is not present, a new instance of this target will be created either paused or not, and the action will be added to the newly created target.
     When the target is paused, the queued actions won't be 'ticked'.
     */
    void addAction(Action *action, Node *target, bool paused);

    /** Removes all actions from all the targets.
    */
    void removeAllActions();

    /** Removes all actions from a certain target.
     All the actions that belongs to the target will be removed.
     */
    void removeAllActionsFromTarget(Node *target);

    /** Removes an action given an action reference.
    */
    void removeAction(Action *action);

    /** Removes an action given its tag and the target */
    void removeActionByTag(int tag, Node *target);
    
    /** Removes all actions given its tag and the target */
    void removeAllActionsByTag(int tag, Node *target);

    /** Gets an action given its tag an a target
     @return the Action the with the given tag
     */
    Action* getActionByTag(int tag, const Node *target) const;

    /** Returns the numbers of actions that are running in a certain target. 
     * Composable actions are counted as 1 action. Example:
     * - If you are running 1 Sequence of 7 actions, it will return 1.
     * - If you are running 7 Sequences of 2 actions, it will return 7.
     */
    ssize_t getNumberOfRunningActionsInTarget(const Node *target) const;

    /** @deprecated use getNumberOfRunningActionsInTarget() instead */
    CC_DEPRECATED_ATTRIBUTE inline ssize_t numberOfRunningActionsInTarget(Node *target) const { return getNumberOfRunningActionsInTarget(target); }

    /** Pauses the target: all running actions and newly added actions will be paused.
    */
    void pauseTarget(Node *target);

    /** Resumes the target. All queued actions will be resumed.
    */
    void resumeTarget(Node *target);
    
    /** Pauses all running actions, returning a list of targets whose actions were paused.
     */
    Vector<Node*> pauseAllRunningActions();
    
    /** Resume a set of targets (convenience function to reverse a pauseAllRunningActions call)
     */
    void resumeTargets(const Vector<Node*>& targetsToResume);
    /**
     * @param dt in seconds
     */
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
