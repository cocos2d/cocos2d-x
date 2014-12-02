/*
 *
 * Copyright (c) 2014 Nguyen Thai Duong
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
 */

#ifndef __cocos2d_libs__CCLayoutBox__
#define __cocos2d_libs__CCLayoutBox__

#include "cocos2d.h"
#include "CCLayout.h"
NS_CC_BEGIN

typedef enum {
    /// The children will be layout out in a horizontal line.
    CCLayoutBoxDirectionHorizontal,
    
    /// The children will be layout out in a vertical line.
    CCLayoutBoxDirectionVertical,
} CCLayoutBoxDirection;

class CC_DLL LayoutBox : public Layout {
public:
    static LayoutBox* create();
    LayoutBox();
    void setDirection(CCLayoutBoxDirection direction);
    CCLayoutBoxDirection getDirection();
    
    void setSpacing(float spacing);
    float getSpacing();
    virtual void removeChild(Node* child, bool cleanup = true);
    virtual void layout();
protected:
    CCLayoutBoxDirection m_eDirection;
    float           m_nSpacing;
};
NS_CC_END
#endif /* defined(__cocos2d_libs__CCLayoutBox__) */
