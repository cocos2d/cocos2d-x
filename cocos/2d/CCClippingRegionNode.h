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

#ifndef __MISCNODE_CCCLIPPING_REGION_NODE_H__
#define __MISCNODE_CCCLIPPING_REGION_NODE_H__

#include "2d/CCNode.h"
#include "2d/CCClippingNode.h"
#include "CCGL.h"

NS_CC_BEGIN

class CC_DLL ClippingRegionNode : public ClippingNode
{    
public:
    static ClippingRegionNode* create(const Rect& clippingRegion);
    static ClippingRegionNode* create(void);
    
    const Rect getClippingRegion(void) {
        return m_clippingRegion;
    }
    void setClippingRegion(const Rect& clippingRegion);
    
    bool isClippingEnabled(void) {
        return m_clippingEnabled;
    }
    void setClippingEnabled(bool enabled) {
        m_clippingEnabled = enabled;
    }

    //virtual void visit(void);
    
protected:
    ClippingRegionNode(void)
    : m_clippingEnabled(true)
    {
    }
    
    Rect m_clippingRegion;
    bool m_clippingEnabled;
};

NS_CC_END

#endif

