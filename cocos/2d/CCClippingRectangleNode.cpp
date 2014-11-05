
#include "CCClippingRectangleNode.h"
#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"
#include "math/Vec2.h"
#include "CCGLView.h"

NS_CC_BEGIN

ClippingRectangleNode* ClippingRectangleNode::create(const Rect& clippingRegion)
{
    ClippingRectangleNode* node = new ClippingRectangleNode();
    if (node && node->init()) {
        node->setClippingRegion(clippingRegion);
        node->autorelease();
    } else {
        CC_SAFE_DELETE(node);
    }
    
    return node;
}

ClippingRectangleNode* ClippingRectangleNode::create()
{
    ClippingRectangleNode* node = new ClippingRectangleNode();
    if (node && node->init()) {
        node->autorelease();
    } else {
        CC_SAFE_DELETE(node);
    }
    
    return node;
}

void ClippingRectangleNode::setClippingRegion(const Rect &clippingRegion)
{
    _clippingRegion = clippingRegion;
}

Rect ClippingRectangleNode::intersectionRect(Rect& rect1, Rect& rect2)
{
    float top1    = rect1.getMaxY();
    float left1   = rect1.getMinX();
    float right1  = rect1.getMaxX();
    float bottom1 = rect1.getMinY();
    
    float top2    = rect2.getMaxY();
    float left2   = rect2.getMinX();
    float right2  = rect2.getMaxX();
    float bottom2 = rect2.getMinY();
    
    Rect rect;
    rect.origin.x = std::max(left1, left2);
    rect.origin.y = std::max(bottom1, bottom2);
    rect.size.width = std::min(right1, right2) - rect.origin.x;
    rect.size.height = std::min(top1, top2) - rect.origin.y;
    
    if (rect.size.width < 0 || rect.size.height < 0) {
        rect.size.width = 0;
        rect.size.height = 0;
    }
    
    rect.origin = convertToNodeSpace(rect.origin);
    
    return rect;
}

void ClippingRectangleNode::onBeforeVisitScissor()
{
    if (_clippingEnabled) {
        glEnable(GL_SCISSOR_TEST);
        
        Rect clippingRegion = Rect(_clippingRegion);
        
        float scaleX = _scaleX;
        float scaleY = _scaleY;
        Node *parent = this->getParent();
        ClippingRectangleNode* parentClip = nullptr;
        Rect parentClippingRegion;
        while (parent) {
            scaleX *= parent->getScaleX();
            scaleY *= parent->getScaleY();

            parentClip = dynamic_cast<ClippingRectangleNode*>(parent);
            if (parentClip) {
                if (parentClip->isClippingEnabled()) {
                    parentClippingRegion = parentClip->getClippingRegion();
                    parentClippingRegion.origin = parentClip->convertToWorldSpace(parentClippingRegion.origin);
                    clippingRegion.origin = convertToWorldSpace(clippingRegion.origin);
                    clippingRegion = this->intersectionRect(clippingRegion, parentClippingRegion);
                }
            }
            
            parent = parent->getParent();
        }
        
        const Point pos = convertToWorldSpace(Point(clippingRegion.origin.x, clippingRegion.origin.y));
        GLView* glView = Director::getInstance()->getOpenGLView();
        glView->setScissorInPoints(pos.x * scaleX,
                                   pos.y * scaleY,
                                   clippingRegion.size.width * scaleX,
                                   clippingRegion.size.height * scaleY);
    }
}

void ClippingRectangleNode::onAfterVisitScissor()
{
    if (_clippingEnabled)
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

void ClippingRectangleNode::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    _beforeVisitCmdScissor.init(_globalZOrder);
    _beforeVisitCmdScissor.func = CC_CALLBACK_0(ClippingRectangleNode::onBeforeVisitScissor, this);
    renderer->addCommand(&_beforeVisitCmdScissor);
    
    Node::visit(renderer, parentTransform, parentFlags);
    
    _afterVisitCmdScissor.init(_globalZOrder);
    _afterVisitCmdScissor.func = CC_CALLBACK_0(ClippingRectangleNode::onAfterVisitScissor, this);
    renderer->addCommand(&_afterVisitCmdScissor);
}

NS_CC_END
