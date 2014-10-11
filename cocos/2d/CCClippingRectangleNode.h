/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 * cocos2d-x: http://www.cocos2d-x.org
 *
 * Copyright (c) 2012 Pierre-David Bélanger
 * Copyright (c) 2012 cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef __MISCNODE_CCCLIPPING_RECTANGLE_NODE_H__
#define __MISCNODE_CCCLIPPING_RECTANGLE_NODE_H__

#include "2d/CCNode.h"
#include "renderer/CCCustomCommand.h"
#include "platform/CCGL.h"

NS_CC_BEGIN

class CC_DLL ClippingRectangleNode : public Node
{    
public:
    static ClippingRectangleNode* create(const Rect& clippingRegion);
    static ClippingRectangleNode* create();
    
    const Rect& getClippingRegion() const {
        return _clippingRegion;
    }
    void setClippingRegion(const Rect& clippingRegion);
    
    const bool isClippingEnabled() const {
        return _clippingEnabled;
    }
    void setClippingEnabled(bool enabled) {
        _clippingEnabled = enabled;
    }

    //virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags) override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

protected:
    ClippingRectangleNode()
    : _clippingEnabled(true)
    {
    }
    
    void onBeforeVisitScissor();
    void onAfterVisitScissor();
    
    Rect _clippingRegion;
    bool _clippingEnabled;
    
    CustomCommand _beforeVisitCmdScissor;
    CustomCommand _afterVisitCmdScissor;
};

NS_CC_END

#endif

