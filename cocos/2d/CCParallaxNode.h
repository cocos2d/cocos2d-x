/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
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
#ifndef __CCPARALLAX_NODE_H__
#define __CCPARALLAX_NODE_H__

#include "2d/CCNode.h"

NS_CC_BEGIN

struct _ccArray;

/**
 * @addtogroup _2d
 * @{
 */

/** @class ParallaxNode
 * @brief @~english ParallaxNode: A node that simulates a parallax scroller.
 * The children will be moved faster / slower than the parent according the the parallax ratio.
 *
 * @~chinese ParallaxNode:一个模拟视差移动效果的节点。
 * 孩子节点移动的快慢依据视差比例而定。
 */
class CC_DLL ParallaxNode : public Node
{
public:
    /** @~english Create a Parallax node. 
     *
     * @~chinese 创建一个视差节点。
     * 
     * @return @~english A initialized ParallaxNode object which is marked as "autorelease".
     * @~chinese 一个初始化的ParallaxNode对象，该对象会自动被标记为“autorelease”(自动释放).
     */
    static ParallaxNode * create();

    using Node::addChild;

    /** @~english Adds a child to the container with a local z-order, parallax ratio and position offset.
     *
     * @~chinese 添加一个子节点到视差节点中。
     * 
     * @param child @~english A child node.
     * @~chinese 一个子节点。
     * @param z @~english Z order for drawing priority.
     * @~chinese Z轴顺序。
     * @param parallaxRatio @~english A given parallax ratio.
     * @~chinese 一个给定的视差比率。
     * @param positionOffset @~english A given position offset.
     * @~chinese 一个给定的位置偏移量。
     */
    void addChild(Node * child, int z, const Vec2& parallaxRatio, const Vec2& positionOffset);

    void setParallaxArray( struct _ccArray *parallaxArray) { _parallaxArray = parallaxArray; }
    struct _ccArray* getParallaxArray() { return _parallaxArray; }
    const struct _ccArray* getParallaxArray() const { return _parallaxArray; }

    //
    // Overrides
    //
    virtual void addChild(Node * child, int zOrder, int tag) override;
    virtual void addChild(Node * child, int zOrder, const std::string &name) override;
    virtual void removeChild(Node* child, bool cleanup) override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

CC_CONSTRUCTOR_ACCESS:
    ParallaxNode();
    virtual ~ParallaxNode();

protected:
    Vec2 absolutePosition();

    Vec2    _lastPosition;
    struct _ccArray* _parallaxArray;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParallaxNode);
};

// end of _2d group
/// @}

NS_CC_END

#endif //__CCPARALLAX_NODE_H__


