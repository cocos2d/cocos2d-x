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
	
/**
 * @addtogroup _2d
 * @{
 */

/**
 *@brief @~english A inner node type mainly used for UI module.
 * It is useful for composing complex node type and it's children are protected.
 * @~chinese 主要用于UI模块的内部节点类型。
 * 用于组合出复杂的节点类型。所有的子节点都为 protected 成员数据。
 */
class  CC_DLL ProtectedNode : public Node
{
public:
    /**@~english
     * Creates a ProtectedNode with no argument.
     * @~chinese 
     * 不使用参数创建一个ProtectedNode。
     *@return @~english A instance of ProtectedNode.
     * @~chinese ProtectedNode的实例。
     */
    static ProtectedNode * create(void);
    
    /// @{
    /// @name Children and Parent
    
    /**@~english
     * Adds a child to the container with z-order as 0.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @~chinese 
     * 以z值为0添加一个子节点。
     * 
     * 如果当前节点正在运行，那么 'onEnter' 和 'onEnterTransitionDidFinish' 会被立即调用。
     * 
     * @param child @~english A child node
     * @~chinese 一个子节点
     */
    virtual void addProtectedChild(Node * child);
    /**@~english
     * Adds a child to the container with a local z-order.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @~chinese 
     * 添加了与当前节点 z 值一致的子节点。
     * 
     * 如果当前节点正在运行，那么 'onEnter' 和 'onEnterTransitionDidFinish' 会被立即调用。
     * 
     * @param child     @~english A child node
     * @~chinese 一个子节点
     * @param localZOrder    @~english Z order for drawing priority. Please refer to `setLocalZOrder(int)`
     * @~chinese 用于控制绘制顺序的 z 值。请参阅`setLocalZOrder(int)`
     */
    virtual void addProtectedChild(Node * child, int localZOrder);
    /**@~english
     * Adds a child to the container with z order and tag.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @~chinese 
     * 指定 z 值和 tag 添加子节点
     * 
     * 如果当前节点正在运行，那么 'onEnter' 和 'onEnterTransitionDidFinish' 会被立即调用。
     * 
     * @param child     @~english A child node
     * @~chinese 一个子节点
     * @param localZOrder    @~english Z order for drawing priority. Please refer to `setLocalZOrder(int)`
     * @~chinese 用于控制绘制顺序的 z 值。请参阅`setLocalZOrder(int)`
     * @param tag       @~english An integer to identify the node easily. Please refer to `setTag(int)`
     * @~chinese 一个用于标识节点的整数。请参阅`setTag(int)`
     */
    virtual void addProtectedChild(Node* child, int localZOrder, int tag);
    /**@~english
     * Gets a child from the container with its tag.
     *
     * @~chinese 
     * 通过 tag 值获取一个子节点。
     * 
     * @param tag   @~english An identifier to find the child node.
     *
     * @~chinese 一个用于标识节点的整数。
     * 
     * @return @~english a Node object whose tag equals to the input parameter.
     * @~chinese tag 值与参数相同的子节点实例。
     */
    virtual Node * getProtectedChildByTag(int tag);
    
    ////// REMOVES //////
    
    /**@~english
     * Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
     *
     * @~chinese 
     * 删除一个子节点。可以通过设置 cleanup 的参数值清理所有正在运行的 action。
     * 
     * @param child     @~english The child node which will be removed.
     * @~chinese 将被删除的子节点。
     * @param cleanup   @~english true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     * @~chinese 如果为 true，将清理子节点相关的 action 和回调。
     */
    virtual void removeProtectedChild(Node* child, bool cleanup = true);
    
    /**@~english
     * Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter.
     *
     * @~chinese 
     * 通过 tag 值来删除子节点。可以通过设置 cleanup 的参数值清理所有正在运行的 action。
     * 
     * @param tag       @~english An interger number that identifies a child node.
     * @~chinese 用于标识子节点的 tag 值。
     * @param cleanup   @~english true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     * @~chinese 如果为 true，将清理子节点相关的 action 和回调。
     */
    virtual void removeProtectedChildByTag(int tag, bool cleanup = true);
    
    /**@~english
     * Removes all children from the container with a cleanup.
     *
     * @~chinese 
     * 移除所有子节点。
     * 
     * @see `removeAllChildrenWithCleanup(bool)`.
     */
    virtual void removeAllProtectedChildren();
    /**@~english
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @~chinese 
     * 移除所有子节点，并清理所有节点相关的操作。
     * 
     * @param cleanup   @~english true if all running actions on all children nodes should be cleanup, false oterwise.
     * @~chinese 如果为 true，将清理子节点相关的 action 和回调。
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllProtectedChildrenWithCleanup(bool cleanup);
    
    /**@~english
     * Reorders a child according to a new z value.
     *
     * @~chinese 
     * 为一个子节点设置新的 z 值并重新排序。
     * 
     * @param child     @~english An already added child node. It MUST be already added.
     * @~chinese 一个已经存在的子节点。
     * @param localZOrder @~english Z order for drawing priority. Please refer to `setLocalZOrder(int)`
     * @~chinese 用于控制绘制顺序的 z 值。请参阅 `setLocalZOrder(int)`
     */
    virtual void reorderProtectedChild(Node * child, int localZOrder);
    
    /**@~english
     * Sorts the children array once before drawing, instead of every time when a child is added or reordered.
     * This approach can improves the performance massively.
     * @~chinese 
     * 在绘制之前对所有子节点进行一次排序。相对于每添加一个节点就排序一次，可以大大提高性能。
     * @note @~english Don't call this manually unless a child added needs to be removed in the same frame
     * @~chinese 不要手动调用此函数，除非一个子节点需要在当前帧删除。
     */
    virtual void sortAllProtectedChildren();
    
    /// @} end of Children and Parent
    
    /**
     * @js NA
     */
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    
    virtual void cleanup() override;
    
    virtual void onEnter() override;

    virtual void onEnterTransitionDidFinish() override;
    
    virtual void onExit() override;
    
    virtual void onExitTransitionDidStart() override;

    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;
    virtual void disableCascadeColor() override;
    virtual void disableCascadeOpacity()override;
    virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;
CC_CONSTRUCTOR_ACCESS:
    ProtectedNode();
    virtual ~ProtectedNode();
    
protected:
    
    /// helper that reorder a child
    void insertProtectedChild(Node* child, int z);
    
    Vector<Node*> _protectedChildren;        ///< array of children nodes
    bool _reorderProtectedChildDirty;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProtectedNode);
};

// end of 2d group
/// @}

NS_CC_END

#endif // __CPROTECTEDCNODE_H__
