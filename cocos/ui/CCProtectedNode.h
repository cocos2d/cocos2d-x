/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2009      Valentin Milea
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
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

#ifndef __CPROTECTEDCNODE_H__
#define __CPROTECTEDCNODE_H__


#include "2d/CCNode.h"

NS_CC_BEGIN

class CC_DLL ProtectedNode : public Node
{
public:
    static ProtectedNode * create(void);
    
    /// @{
    /// @name Children and Parent
    
    /**
     * 添加一个z-order为0的child到容器中。
     *
     * 如果child被添加到一个“运行中(running)”的node，那么"onEnter"和"onEnterTransitionDidFinish"将被立即调用。
     *
     * @param child  一个子节点(child node)。
     */
    virtual void addProtectedChild(Node * child);
    /**
     * 添加一个child(定义localZOrder)到容器中。
     *
     * 如果child被添加到一个“运行中(running)”的node，那么"onEnter"和"onEnterTransitionDidFinish"将被立即调用。
     *
     * @param child     一个子节点(child node)。
     * @param zOrder    z-order决定绘制的优先级。 请参照 `setLocalZOrder(int)`
     */
    virtual void addProtectedChild(Node * child, int localZOrder);
    /**
     * 添加一个child(定义localZOrder，定义tag)到容器中。
     *
     * 如果child被添加到一个“运行中(running)”的node，那么"onEnter"和"onEnterTransitionDidFinish"将被立即调用。
     *
     * @param child     一个子节点(child node)。
     * @param zOrder    z-order决定绘制的优先级。 请参照 `setLocalZOrder(int)`
     * @param tag       tag指定node的id。一般为整数。 请参照 `setTag(int)`
     */
    virtual void addProtectedChild(Node* child, int localZOrder, int tag);
    /**
     * 从容器中获取child及其tag
     *
     * @param tag   tag指定子节点(child)的id
     *
     * @返回一个Node对象，此Node的tag等于键入的参数。
     */
    virtual Node * getProtectedChildByTag(int tag);
    
    ////// REMOVES //////
    
    /**
     * 从容器中删除一个child。它也将清除所有运行中的动作(取决于cleanup的参数)。
     *
     * @param child     将被删除的子节点(child)。
     * @param cleanup   参数为true 子节点(child)上所有运行的动作及回调函数将被清理，为false 时则不会。
     */
    virtual void removeProtectedChild(Node* child, bool cleanup = true);
    
    /**
     * 根据tag的值(value)来删除child。它也将清除所有运行中的动作(取决于cleanup的参数)。
     *
     * @param tag       tag指定子节点(child)的id，一般为整数。
     * @param cleanup   参数为true 子节点(child)上所有运行的动作及回调函数将被清理，为false 时则不会。
     */
    virtual void removeProtectedChildByTag(int tag, bool cleanup = true);
    /**
     * 删除容器中所有child。
     *
     * @see `removeAllChildrenWithCleanup(bool)`
     */
    virtual void removeAllProtectedChildren();
    /**
     * 删除容器中所有child，并清理所有运行中的动作(取决于cleanup的参数)。
     *
     * @param cleanup   参数为true 子节点(child)上所有运行的动作及回调函数将被清理，为false 时则不会。
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllProtectedChildrenWithCleanup(bool cleanup);
    
    /**
     * 重新赋予一个child新z值(z vlaue)。(此z值应为localZOrder的值，原文简写为z value。译者注)
     *
     * @param child     一个已经添加的子节点(child)。必须是已经被添加的。
     * @param localZOrder  z-order决定绘制的优先级。 请参照 `setLocalZOrder(int)`
     */
    virtual void reorderProtectedChild(Node * child, int localZOrder);
    
    /**
     * 在绘制之前整理子节点数组(children array)，而不是每次子节点(child)被添加或重新排序(reordered)时。
     * 此方法可以大大提高性能。
     * @note 不要手动调用此方法，除非一个已被添加的child需要从同一帧(frame)中删除。
     */
    virtual void sortAllProtectedChildren();
    
    /// @} end of Children and Parent
    
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool transformUpdated) override;
    
    virtual void cleanup() override;
    
    virtual void onEnter() override;
    
    /**
     * 当Node进入“stage”时，事件回调被调用。
     * 如果Node进入‘stage’并开始变换(transition)，此事件将在变换(transition)完成后被调用。
     * 如果你 override onEnterTransitionDidFinish, 你应该调用其父节点的此方法, 例如： Node::onEnterTransitionDidFinish()
     * @js NA
     * @lua NA
     */
    virtual void onEnterTransitionDidFinish() override;
    
    /**
     * 事件回调在每次Node离开“stage”时被调用。
     * 如果Node离开‘stage’并开始变换(transition)，此事件将在变换(transition)完成后被调用。
     * 在 onExit执行期间你不能访问兄弟节点(sibling node)。
     * 如果你 override onExit, 你应该调用其父节点的此方法， 例如, Node::onExit().
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;
    
    /**
     * 事件回调在每次Node离开“stage”时被调用。
     * 如果Node离开‘stage’并开始变换(transition)，此事件将在变换(transition)开始时被调用。
     * @js NA
     * @lua NA
     */
    virtual void onExitTransitionDidStart() override;

    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;
    virtual void disableCascadeColor() override;
CC_CONSTRUCTOR_ACCESS:
    ProtectedNode();
    virtual ~ProtectedNode();
    
protected:
    
    /// helper重新排序一个child
    void insertProtectedChild(Node* child, int z);
    
    Vector<Node*> _protectedChildren;        ///< 子节点(children nodes)数组
    bool _reorderProtectedChildDirty;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProtectedNode);
};


NS_CC_END

#endif // __CPROTECTEDCNODE_H__