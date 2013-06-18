/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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
#include "support/CCPointExtension.h"
#include "support/data_support/ccCArray.h"

NS_CC_BEGIN

class CCPointObject : CCObject
{
    CC_SYNTHESIZE(CCPoint, _ratio, Ratio)
    CC_SYNTHESIZE(CCPoint, _offset, Offset)
    CC_SYNTHESIZE(CCNode *,_child, Child)    // weak ref

public:
    static CCPointObject * pointWithCCPoint(CCPoint ratio, CCPoint offset)
    {
        CCPointObject *pRet = new CCPointObject();
        pRet->initWithCCPoint(ratio, offset);
        pRet->autorelease();
        return pRet;
    }
    bool initWithCCPoint(CCPoint ratio, CCPoint offset)
    {
        _ratio = ratio;
        _offset = offset;
        _child = NULL;
        return true;
    }
};

CCParallaxNode::CCParallaxNode()
{
    _parallaxArray = ccArrayNew(5);        
    _lastPosition = CCPointMake(-100,-100);
}
CCParallaxNode::~CCParallaxNode()
{
    if( _parallaxArray )
    {
        ccArrayFree(_parallaxArray);
        _parallaxArray = NULL;
    }
}

CCParallaxNode * CCParallaxNode::create()
{
    CCParallaxNode *pRet = new CCParallaxNode();
    pRet->autorelease();
    return pRet;
}

void CCParallaxNode::addChild(CCNode * child, unsigned int zOrder, int tag)
{
    CC_UNUSED_PARAM(zOrder);
    CC_UNUSED_PARAM(child);
    CC_UNUSED_PARAM(tag);
    CCAssert(0,"ParallaxNode: use addChild:z:parallaxRatio:positionOffset instead");
}
void CCParallaxNode::addChild(CCNode *child, unsigned int z, const CCPoint& ratio, const CCPoint& offset)
{
    CCAssert( child != NULL, "Argument must be non-nil");
    CCPointObject *obj = CCPointObject::pointWithCCPoint(ratio, offset);
    obj->setChild(child);
    ccArrayAppendObjectWithResize(_parallaxArray, (CCObject*)obj);

    CCPoint pos = _position;
    pos.x = pos.x * ratio.x + offset.x;
    pos.y = pos.y * ratio.y + offset.y;
    child->setPosition(pos);

    CCNode::addChild(child, z, child->getTag());
}
void CCParallaxNode::removeChild(CCNode* child, bool cleanup)
{
    for( unsigned int i=0;i < _parallaxArray->num;i++)
    {
        CCPointObject *point = (CCPointObject*)_parallaxArray->arr[i];
        if( point->getChild()->isEqual(child)) 
        {
            ccArrayRemoveObjectAtIndex(_parallaxArray, i, true);
            break;
        }
    }
    CCNode::removeChild(child, cleanup);
}
void CCParallaxNode::removeAllChildrenWithCleanup(bool cleanup)
{
    ccArrayRemoveAllObjects(_parallaxArray);
    CCNode::removeAllChildrenWithCleanup(cleanup);
}
CCPoint CCParallaxNode::absolutePosition()
{
    CCPoint ret = _position;
    CCNode *cn = this;
    while (cn->getParent() != NULL)
    {
        cn = cn->getParent();
        ret = ccpAdd( ret,  cn->getPosition());
    }
    return ret;
}

/*
The positions are updated at visit because:
- using a timer is not guaranteed that it will called after all the positions were updated
- overriding "draw" will only precise if the children have a z > 0
*/
void CCParallaxNode::visit()
{
    //    CCPoint pos = position_;
    //    CCPoint    pos = [self convertToWorldSpace:CCPointZero];
    CCPoint pos = this->absolutePosition();
    if( ! pos.equals(_lastPosition) )
    {
        for(unsigned int i=0; i < _parallaxArray->num; i++ ) 
        {
            CCPointObject *point = (CCPointObject*)_parallaxArray->arr[i];
            float x = -pos.x + pos.x * point->getRatio().x + point->getOffset().x;
            float y = -pos.y + pos.y * point->getRatio().y + point->getOffset().y;            
            point->getChild()->setPosition(ccp(x,y));
        }
        _lastPosition = pos;
    }
    CCNode::visit();
}

NS_CC_END
