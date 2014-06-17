
#include "CCClippingRegionNode.h"
#include "CCDirector.h"
//#include "CCEGLView.h"

NS_CC_BEGIN

ClippingRegionNode* ClippingRegionNode::create(const Rect& clippingRegion)
{
    ClippingRegionNode* node = new ClippingRegionNode();
    node->setClippingRegion(clippingRegion);
    node->autorelease();
    return node;
}

ClippingRegionNode* ClippingRegionNode::create(void)
{
    ClippingRegionNode* node = new ClippingRegionNode();
    node->autorelease();
    return node;
}

void ClippingRegionNode::setClippingRegion(const Rect &clippingRegion)
{
    m_clippingRegion = clippingRegion;
    setContentSize(clippingRegion.size);
}

//void ClippingRegionNode::visit()
//{
//    if (m_clippingEnabled)
//    {
//        glEnable(GL_SCISSOR_TEST);
//        
//        float scaleX = m_fScaleX;
//        float scaleY = m_fScaleY;
//        CCNode *parent = this->getParent();
//        while (parent) {
//            scaleX *= parent->getScaleX();
//            scaleY *= parent->getScaleY();
//            parent = parent->getParent();
//        }
//        
//        const Point pos = convertToWorldSpace(CCPoint(m_clippingRegion.origin.x, m_clippingRegion.origin.y));
//        Director::getInstance()->getOpenGLView()->setScissorInPoints(pos.x * m_fScaleX,
//                                                                          pos.y * m_fScaleX,
//                                                                          m_clippingRegion.size.width * scaleX,
//                                                                          m_clippingRegion.size.height * scaleY);
//    }
//    
//    Node::visit();
//    
//    if (m_clippingEnabled)
//    {
//        glDisable(GL_SCISSOR_TEST);
//    }
//}

NS_CC_END
