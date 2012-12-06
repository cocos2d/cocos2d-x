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
    CC_SYNTHESIZE(CCPoint, m_tRatio, Ratio)
    CC_SYNTHESIZE(CCPoint, m_tOffset, Offset)
    CC_SYNTHESIZE(CCNode *,m_pChild, Child)    // weak ref

    static CCPointObject * pointWithCCPoint(CCPoint ratio, CCPoint offset)
    {
        CCPointObject *pRet = new CCPointObject();
        pRet->initWithCCPoint(ratio, offset);
        pRet->autorelease();
        return pRet;
    }
    bool initWithCCPoint(CCPoint ratio, CCPoint offset)
    {
        m_tRatio = ratio;
        m_tOffset = offset;
        m_pChild = NULL;
        return true;
    }
};

CCParallaxNode::CCParallaxNode()
{
    m_pParallaxArray = ccArrayNew(5);        
    m_tLastPosition = CCPointMake(-100,-100);
}
CCParallaxNode::~CCParallaxNode()
{
    if( m_pParallaxArray )
    {
        ccArrayFree(m_pParallaxArray);
        m_pParallaxArray = NULL;
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
    ccArrayAppendObjectWithResize(m_pParallaxArray, (CCObject*)obj);

    CCPoint pos = m_obPosition;
    pos.x = pos.x * ratio.x + offset.x;
    pos.y = pos.y * ratio.y + offset.y;
    child->setPosition(pos);

    CCNode::addChild(child, z, child->getTag());
}
void CCParallaxNode::removeChild(CCNode* child, bool cleanup)
{
    for( unsigned int i=0;i < m_pParallaxArray->num;i++)
    {
        CCPointObject *point = (CCPointObject*)m_pParallaxArray->arr[i];
        if( point->getChild()->isEqual(child)) 
        {
            ccArrayRemoveObjectAtIndex(m_pParallaxArray, i, true);
            break;
        }
    }
    CCNode::removeChild(child, cleanup);
}
void CCParallaxNode::removeAllChildrenWithCleanup(bool cleanup)
{
    ccArrayRemoveAllObjects(m_pParallaxArray);
    CCNode::removeAllChildrenWithCleanup(cleanup);
}
CCPoint CCParallaxNode::absolutePosition()
{
    CCPoint ret = m_obPosition;
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
    if( ! pos.equals(m_tLastPosition) )
    {
        for(unsigned int i=0; i < m_pParallaxArray->num; i++ ) 
        {
            CCPointObject *point = (CCPointObject*)m_pParallaxArray->arr[i];
            float x = -pos.x + pos.x * point->getRatio().x + point->getOffset().x;
            float y = -pos.y + pos.y * point->getRatio().y + point->getOffset().y;            
            point->getChild()->setPosition(ccp(x,y));
        }
        m_tLastPosition = pos;
    }
    CCNode::visit();
}

NS_CC_END
