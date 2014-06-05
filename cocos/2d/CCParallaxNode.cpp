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
#include "CCParallaxNode.h"
#include "base/ccCArray.h"

NS_CC_BEGIN

class PointObject : public Ref
{
public:
    static PointObject * create(Vec2 ratio, Vec2 offset)
    {
        PointObject *ret = new PointObject();
        ret->initWithPoint(ratio, offset);
        ret->autorelease();
        return ret;
    }
    
    bool initWithPoint(Vec2 ratio, Vec2 offset)
    {
        _ratio = ratio;
        _offset = offset;
        _child = nullptr;
        return true;
    }
    
    inline const Vec2& getRatio() const { return _ratio; };
    inline void setRatio(const Vec2& ratio) { _ratio = ratio; };

    inline const Vec2& getOffset() const { return _offset; };
    inline void setOffset(const Vec2& offset) { _offset = offset; };
    
    inline Node* getChild() const { return _child; };
    inline void setChild(Node* child) { _child = child; };
    
private:
    Vec2 _ratio;
    Vec2 _offset;
    Node *_child; // weak ref
};

ParallaxNode::ParallaxNode()
{
    _parallaxArray = ccArrayNew(5);        
    _lastPosition = Vec2(-100,-100);
}

ParallaxNode::~ParallaxNode()
{
    if( _parallaxArray )
    {
        ccArrayFree(_parallaxArray);
        _parallaxArray = nullptr;
    }
}

void ParallaxNode::addChild(Node * child, int zOrder, int tag)
{
    CC_UNUSED_PARAM(zOrder);
    CC_UNUSED_PARAM(child);
    CC_UNUSED_PARAM(tag);
    CCASSERT(0,"ParallaxNode: use addChild:z:parallaxRatio:positionOffset instead");
}

void ParallaxNode::addChild(Node *child, int z, const Vec2& ratio, const Vec2& offset)
{
    CCASSERT( child != nullptr, "Argument must be non-nil");
    PointObject *obj = PointObject::create(ratio, offset);
    obj->setChild(child);
    ccArrayAppendObjectWithResize(_parallaxArray, (Ref*)obj);

    Node::addChild(child, z, child->getTag());
}

void ParallaxNode::removeChild(Node* child, bool cleanup)
{
    for( int i=0;i < _parallaxArray->num;i++)
    {
        PointObject *point = (PointObject*)_parallaxArray->arr[i];
        if (point->getChild() == child)
        {
            ccArrayRemoveObjectAtIndex(_parallaxArray, i, true);
            break;
        }
    }
    Node::removeChild(child, cleanup);
}

void ParallaxNode::removeAllChildrenWithCleanup(bool cleanup)
{
    ccArrayRemoveAllObjects(_parallaxArray);
    Node::removeAllChildrenWithCleanup(cleanup);
}

/*
The positions are updated at visit because:
- using a timer is not guaranteed that it will called after all the positions were updated
- overriding "draw" will only precise if the children have a z > 0
*/
void ParallaxNode::visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated)
{
    Vec2 pos = parallaxPosition;

    if (!pos.equals(_lastPosition)) {
        for( int i=0; i < _parallaxArray->num; i++ ) {
            PointObject *point = (PointObject*)_parallaxArray->arr[i];
            float x = pos.x * point->getRatio().x + point->getOffset().x;
            float y = pos.y * point->getRatio().y + point->getOffset().y;
            point->getChild()->setPosition({x, y});
        }
        _lastPosition = pos;
    }
    Node::visit(renderer, parentTransform, parentTransformUpdated);
}

NS_CC_END
