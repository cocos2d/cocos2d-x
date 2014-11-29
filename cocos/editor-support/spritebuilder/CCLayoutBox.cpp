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

#include "CCLayoutBox.h"

NS_CC_BEGIN

static float roundUpToEven(float f)
{
    return ceilf(f/2.0f) * 2.0f;
}

LayoutBox* LayoutBox::create() {
    LayoutBox* ret = new LayoutBox();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    } else
        return NULL;
}
LayoutBox::LayoutBox() {
    m_eDirection = CCLayoutBoxDirectionHorizontal;
    m_nSpacing = 0;
}
void LayoutBox::layout() {
    Layout::layout();
    if (m_eDirection == CCLayoutBoxDirectionHorizontal)
    {
        // Get the maximum height
        float maxHeight = 0;

        for(auto it = _children.cbegin(); it != _children.cend(); ++it) {
            float height = (*it)->getContentSize().height;
            if (height > maxHeight) maxHeight = height;
        }
        
        // Position the nodes
        float width = 0;
        for(auto it = _children.cbegin(); it != _children.cend(); ++it) {
            
            Size childSize = (*it)->getContentSize();
            
            Point offset = (*it)->getAnchorPointInPoints();
            Point localPos(roundf(width), roundf((maxHeight-childSize.height)/2.0f));
            Point position = localPos + offset;
            
            (*it)->setPosition(position);
//            (*it)->setPositionType(CCPositionTypePoints);
            
            width += childSize.width;
            width += m_nSpacing;
        }
        
        // Account for last added increment
        width -= m_nSpacing;
        if (width < 0) width = 0;
        
        this->setContentSize(Size(roundUpToEven(width), roundUpToEven(maxHeight)));
    }
    else
    {
        // Get the maximum height
        float maxWidth = 0;
        
        for(auto it = _children.cbegin(); it != _children.cend(); ++it) {
            float width = (*it)->getContentSize().width;
            if (width > maxWidth) maxWidth = width;
        }
        
        // Position the nodes
        float height = 0;
        for(auto it = _children.cbegin(); it != _children.cend(); ++it) {
            
            Size childSize = (*it)->getContentSize();
            
            Point offset = (*it)->getAnchorPointInPoints();
            Point localPos(roundf((maxWidth-childSize.width)/2.0f), roundf(height));
            Point position = localPos + offset;
            
            (*it)->setPosition(position);
            //            (*it)->setPositionType(CCPositionTypePoints);
            
            height += childSize.height;
            height += m_nSpacing;
        }
        
        // Account for last added increment
        height -= m_nSpacing;
        if (height < 0) height = 0;
        
        
        this->setContentSize(Size(roundUpToEven(maxWidth), roundUpToEven(height)));
    }
}

void LayoutBox::setDirection(CCLayoutBoxDirection direction) {
    m_eDirection = direction;
    needLayout();
}
CCLayoutBoxDirection LayoutBox::getDirection() {
    return m_eDirection;
}

void LayoutBox::setSpacing(float spacing) {
    m_nSpacing = spacing;
    needLayout();
}

float LayoutBox::getSpacing() {
    return m_nSpacing;
}

void LayoutBox::removeChild(Node* child, bool cleanup) {
    Layout::removeChild(child, cleanup);
    needLayout();
}

NS_CC_END