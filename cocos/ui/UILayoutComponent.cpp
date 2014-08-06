/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#include "UILayoutComponent.h"
#include "2d/CCNode.h"


NS_CC_BEGIN

namespace ui {
    LayoutComponent::LayoutComponent()
    :_referencePoint(ReferencePoint::LEFT_BOTTOM),
    _dirtyFlag(0)
    {
        _name = "__ui_layout";
    }
    
    LayoutComponent::~LayoutComponent()
    {
        
    }
    
    bool LayoutComponent::init()
    {
        bool ret = true;
        do {
            if (!Component::init()) {
                ret = false;
                break;
            }
            
            //put layout component initalized code here
            
        } while (0);
        return ret;
    }
    
    uint32_t LayoutComponent::getDirtyFlag()const
    {
        return _dirtyFlag;
    }
    
    void LayoutComponent::setDirtyFlag(uint32_t flag)
    {
        _dirtyFlag = _dirtyFlag | flag;
    }
    
    const Vec2& LayoutComponent::getPercentPosition()const
    {
        return _percentPosition;
    }
    
    void LayoutComponent::setPercentPosition(const Vec2& percent)
    {
        _percentPosition = percent;
        this->setDirtyFlag(DIRTY_FLAG_PERCENT_POSITION);
//        this->changeOwnerNormalizedPosition();
    }
    
    const Vec2& LayoutComponent::getPercentContentSize()const
    {
        return _percentPosition;
    }
    
    void LayoutComponent::setPercentContentSize(const Vec2& percent)
    {
        _percentContentSize = percent;
        this->setDirtyFlag(DIRTY_FLAG_PERCENT_CONTENT_SIZE);
    }
    
    void LayoutComponent::setReferencePoint(ReferencePoint point)
    {
        _referencePoint = point;
    }
    
    LayoutComponent::ReferencePoint LayoutComponent::getReferencePoint()
    {
        return _referencePoint;
    }
    
    void LayoutComponent::onEnter()
    {
        Component::onEnter();
        if (_owner) {
            _owner->scheduleUpdate();
        }
//        this->changeOwnerNormalizedPosition();
    }
    
    void LayoutComponent::changeOwnerNormalizedPosition()
    {
        if (nullptr != _owner) {
            if (_dirtyFlag & DIRTY_FLAG_PERCENT_POSITION) {
                CCLOG("changeOwnerNormalizedPosition");
                _owner->setNormalizedPosition(_percentPosition);
//                Size oldSize = _owner->getContentSize();
//                _owner->setContentSize(Size::ZERO);
//                _owner->setContentSize(oldSize);
                _dirtyFlag = _dirtyFlag & ~DIRTY_FLAG_PERCENT_POSITION;
            }
        }
    }
    
    void LayoutComponent::onExit()
    {
        Component::onExit();
    }
    
    void LayoutComponent::update(float delta)
    {
        Component::update(delta);
        this->changeOwnerNormalizedPosition();
    }

    

}

NS_CC_END