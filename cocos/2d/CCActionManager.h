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

/** @class ActionManager
 @brief @~english ActionManager is a singleton that manages all the actions.
 Normally you won't need to use this singleton directly. 99% of the cases you will use the Node interface,
 which uses this singleton.
 But there are some cases where you might need to use this singleton.
 Examples:
    - When you want to run an action where the target is different from a Node. 
    - When you want to pause / resume the actions.
 
 * @~chinese ActionManager是一个单例类，管理的所有动作。
 * 通常你不需要直接使用这个类。99%的情况下，你将使用Node的接口，它提供了更友好的封装
 * 但也有一些情况下，你可能需要使用这个单例。
 * 例子:
 * - 当你想要运行一个动作，但目标不是节点类型。
 * - 当你想要暂停/恢复动作。
 * 
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
    
    /** @~english Adds an action with a target. 
     If the target is already present in the hash map, then the action will be added to the existing target's hash element.
     If the target is not present in the hash map, a new hash map element of this target will be created, either paused or not, and the action will be added to newly created hash element.
     When the target is paused, the queued actions won't be 'ticked'.
     *
     * @~chinese 增加一个动作，同时还需要提供动作的目标对象，目标对象是否暂停作为参数。
     * 如果目标已经在节点哈希表中存在，动作将会被直接添加到节点的哈希表元素中。
     * 如果目标不存在于节点哈希表中，将为这一目标创建一个新的元素，动作将被添加进去。
     * 当目标状态`paused`为`true`，动作将不会被执行。
     * 
     * @param action    @~english An action to be added.
     * @~chinese 需要被添加的动作。
     * @param target    @~english The target which need to be added an action.
     * @~chinese 动作的目标对象。
     * @param paused    @~english Is the target paused or not.
     * @~chinese 目标对象是否暂停。
     */
    void addAction(Action *action, Node *target, bool paused);

    /** @~english Removes all actions from all the targets.
     * @~chinese 删除所有目标对象的所有动作。
     */
    void removeAllActions();

    /** @~english Removes all actions from a certain target.
     All the actions that belongs to the target will be removed.
     *
     * @~chinese 从一个特定的目标删除所有动作。
     * 属于该目标的所有的行动将被删除。
     * 
     * @param target    @~english A certain target.
     * @~chinese 一个特定的目标。
     */
    void removeAllActionsFromTarget(Node *target);

    /** @~english Removes an action given an action reference.
     *
     * @~chinese 删除一个动作。
     * 
     * @param action    @~english A certain action.
     * @~chinese 一个特定的动作。
     */
    void removeAction(Action *action);

    /** @~english Removes an action given its tag and the target.
     *
     * @~chinese 删除目标对象下特定标签标记的一个动作，将删除首个匹配到的动作。
     * 
     * @param tag       @~english The action's tag.
     * @~chinese 动作的标签。
     * @param target    @~english A certain target.
     * @~chinese 一个特定的目标。
     */
    void removeActionByTag(int tag, Node *target);
    
    /** @~english Removes all actions given its tag and the target.
     *
     * @~chinese 删除目标对象下特定标签标记的所有动作。
     * 
     * @param tag       @~english The actions' tag.
     * @~chinese 动作的标签。
     * @param target    @~english A certain target.
     * @~chinese 一个特定的目标。
     * @js NA
     */
    void removeAllActionsByTag(int tag, Node *target);

    /** @~english Gets an action given its tag an a target.
     *
     * @~chinese 通过目标对象和标签获取一个动作。
     * 
     * @param tag       @~english The action's tag.
     * @~chinese 动作的标签。
     * @param target    @~english A certain target.
     * @~chinese 一个特定的目标。
     * @return @~english  The Action the with the given tag.
     * @~chinese 符合标签的动作。
     */
    Action* getActionByTag(int tag, const Node *target) const;

    /** @~english Returns the numbers of actions that are running in a certain target. 
     * Composable actions are counted as 1 action. Example:
     * - If you are running 1 Sequence of 7 actions, it will return 1.
     * - If you are running 7 Sequences of 2 actions, it will return 7.
     *
     * @~chinese 返回指定目标下所有正在运行的动作数量。
     * 组合动作被算作一个动作。例子:
     * - 如果您正在运行7个动作组成的序列动作（Sequence），这个函数将返回1。
     * - 如果你正在运行2个序列动作（Sequence）和5个普通动作，这个函数将返回7。
     * 
     * @param target    @~english A certain target.
     * @~chinese 一个特定的目标。
     * @return @~english  The numbers of actions that are running in a certain target.
     * @~chinese 指定目标下所有正在运行的动作数量。
     * @js NA
     */
    ssize_t getNumberOfRunningActionsInTarget(const Node *target) const;

    /** @deprecated @~english Use getNumberOfRunningActionsInTarget() instead. @~chinese 使用`getNumberOfRunningActionsInTarget`替代
     */
    CC_DEPRECATED_ATTRIBUTE inline ssize_t numberOfRunningActionsInTarget(Node *target) const { return getNumberOfRunningActionsInTarget(target); }

    /** @~english Pauses the target: all running actions and newly added actions will be paused.
     *
     * @~chinese 暂停目标对象：所有正在运行的动作和新添加的动作都将会暂停。
     * 
     * @param target    @~english A certain target.
     * @~chinese 一个特定的目标。
     */
    void pauseTarget(Node *target);

    /** @~english Resumes the target. All queued actions will be resumed.
     *
     * @~chinese 让目标对象恢复运行。在执行序列中所有被暂停的动作将重新恢复运行。
     * 
     * @param target    @~english A certain target.
     * @~chinese 一个特定的目标。
     */
    void resumeTarget(Node *target);
    
    /** @~english Pauses all running actions, returning a list of targets whose actions were paused.
     *
     * @~chinese 暂停所有正在运行的动作，返回一个动作被暂停的目标对象列表。
     * 
     * @return @~english  A list of targets whose actions were paused.
     * @~chinese 动作被暂停的目标对象列表。
     */
    Vector<Node*> pauseAllRunningActions();
    
    /** @~english Resume a set of targets (convenience function to reverse a pauseAllRunningActions call).
     *
     * @~chinese 让一组目标对象恢复运行（用来逆转`pauseAllRunningActions`效果的便捷函数）。
     * 
     * @param targetsToResume   @~english A set of targets need to be resumed.
     * @~chinese 一组需要恢复运行的目标对象。
     * @see `pauseAllRunningActions`
     */
    void resumeTargets(const Vector<Node*>& targetsToResume);
    
    /** @~english Main loop of ActionManager.
     * @~chinese ActionManager主循环。
     * @param dt    @~english Interval in seconds.
     * @~chinese 以秒为单位的时间间隔（从上一次调用开始到本次调用）。
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
