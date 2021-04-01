/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "2d/CCClippingRectangleNode.h"
#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"
#include "math/Vec2.h"
#include "platform/CCGLView.h"

NS_CC_BEGIN

ClippingRectangleNode* ClippingRectangleNode::create(const Rect& clippingRegion)
{
    ClippingRectangleNode* node = new (std::nothrow) ClippingRectangleNode();
    if (node && node->init())
    {
        node->setClippingRegion(clippingRegion);
        node->autorelease();
    } else
        CC_SAFE_DELETE(node);

    return node;
}

ClippingRectangleNode* ClippingRectangleNode::create()
{
    ClippingRectangleNode* node = new (std::nothrow) ClippingRectangleNode();
    if (node && node->init())
        node->autorelease();
    else
        CC_SAFE_DELETE(node);

    return node;
}

void ClippingRectangleNode::setClippingRegion(const Rect &clippingRegion)
{
    _clippingRegion = clippingRegion;
}

void ClippingRectangleNode::onBeforeVisitScissor()
{
    if (_clippingEnabled)
    {
        auto renderer = Director::getInstance()->getRenderer();
        _oldScissorTest = renderer->getScissorTest();
        renderer->setScissorTest(true);

        float scaleX = _scaleX;
        float scaleY = _scaleY;
        Node *parent = this->getParent();
        while (parent) {
            scaleX *= parent->getScaleX();
            scaleY *= parent->getScaleY();
            parent = parent->getParent();
        }
        
        const Point pos = convertToWorldSpace(Point(_clippingRegion.origin.x, _clippingRegion.origin.y));
        GLView* glView = Director::getInstance()->getOpenGLView();
        glView->setScissorInPoints(pos.x,
                                   pos.y,
                                   _clippingRegion.size.width * scaleX,
                                   _clippingRegion.size.height * scaleY);
    }
}

void ClippingRectangleNode::onAfterVisitScissor()
{
    if (_clippingEnabled)
        Director::getInstance()->getRenderer()->setScissorTest(_oldScissorTest);
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
