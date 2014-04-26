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
/*#include "ccArray.h"*/

NS_CC_BEGIN

struct _ccArray;

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

/** @brief ParallaxNode: A node that simulates a parallax scroller

The children will be moved faster / slower than the parent according the the parallax ratio.

*/
class CC_DLL ParallaxNode : public Node
{
public:
    // Create a Parallax node
    static ParallaxNode * create();

    // prevents compiler warning: "Included function hides overloaded virtual functions"
    using Node::addChild;

    void addChild(Node * child, int z, const Vector2& parallaxRatio, const Vector2& positionOffset);

    /** Sets an array of layers for the Parallax node */
    void setParallaxArray( struct _ccArray *parallaxArray) { _parallaxArray = parallaxArray; }
    /** Returns the array of layers of the Parallax node */
    struct _ccArray* getParallaxArray() { return _parallaxArray; }
    const struct _ccArray* getParallaxArray() const { return _parallaxArray; }

    //
    // Overrides
    //
    virtual void addChild(Node * child, int zOrder, int tag) override;
    virtual void removeChild(Node* child, bool cleanup) override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void visit(Renderer *renderer, const Matrix &parentTransform, bool parentTransformUpdated) override;

protected:
    /** Adds a child to the container with a z-order, a parallax ratio and a position offset
     It returns self, so you can chain several addChilds.
     @since v0.8
     * @js ctor
     */
    ParallaxNode();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParallaxNode();

    Vector2 absolutePosition();

    Vector2    _lastPosition;
    struct _ccArray* _parallaxArray;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParallaxNode);
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCPARALLAX_NODE_H__


