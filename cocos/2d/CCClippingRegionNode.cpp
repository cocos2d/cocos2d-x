
#include "CCClippingRegionNode.h"
#include "base/CCDirector.h"
#include "2d/CCDrawNode.h"
#include "math/Vec2.h"
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
    DrawNode *node = DrawNode::create();
    Vec2 vec2Points[4] = {};
    vec2Points[0] = Vec2(clippingRegion.origin);
    vec2Points[1] = Vec2(clippingRegion.origin.x + clippingRegion.size.width, clippingRegion.origin.y);
    vec2Points[2] = Vec2(clippingRegion.origin.x + clippingRegion.size.width,
                         clippingRegion.origin.y + clippingRegion.size.height);
    vec2Points[3] = Vec2(clippingRegion.origin.x, clippingRegion.origin.y + clippingRegion.size.height);
    node->drawPolygon(vec2Points, 4, Color4F(1, 1, 1, 1), 1, Color4F(1,1,1,1));
    setStencil(node);
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
