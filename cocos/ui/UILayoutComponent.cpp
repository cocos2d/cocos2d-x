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
#include "GUIDefine.h"


NS_CC_BEGIN

namespace ui {
    LayoutComponent::LayoutComponent()
    :_actived(true)
    ,_usingPercentContentSize(false)
    ,_usingPercentPosition(false)
    ,_referencePoint(ReferencePoint::BOTTOM_LEFT)
    {
        _name = __LAYOUT_COMPONENT_NAME;
    }
    
    LayoutComponent::~LayoutComponent()
    {
        
    }
    
    bool LayoutComponent::init()
    {
        bool ret = true;
        do
        {
            if (!Component::init())
            {
                ret = false;
                break;
            }
            
            //put layout component initalized code here
            
        } while (0);
        return ret;
    }
    
    //Size
    const Vec2& LayoutComponent::getOwnerContentSize()const
    {
        return this->getOwner()->getContentSize();
    }
    void LayoutComponent::setOwnerContentSize(const Vec2& percent)
    {
        this->RefreshLayoutSize(SizeType::Size,percent);
    }

    const Vec2& LayoutComponent::getPercentContentSize()const
    {
        return _percentContentSize;
    }
    
    void LayoutComponent::setPercentContentSize(const Vec2& percent)
    {
        this->RefreshLayoutSize(SizeType::PreSize,percent);
    }
    
    bool LayoutComponent::isUsingPercentContentSize()
    {
        return _usingPercentContentSize;
    }

    void LayoutComponent::setUsingPercentContentSize(bool flag)
    {
        _usingPercentContentSize = flag;
        this->RefreshLayoutSize(SizeType::PreSizeEnable,Vec2(0,0));
    }

    void LayoutComponent::RefreshLayoutSize(SizeType sType, const Vec2& size)
    {
        Node* parentNode = this->getOwner()->getParent();
        if (parentNode != NULL && _actived)
        {
            Size parentSize = parentNode->getContentSize();

            switch (sType)
            {
            case SizeType::Size:
                if (parentSize.width != 0 && parentSize.height != 0)
                {
                    _percentContentSize = Point(size.x/parentSize.width,size.y/parentSize.height);
                }
                else
                {
                    _percentContentSize = Point(0,0);
                }
                this->getOwner()->setContentSize(Size(size.x,size.y));
                break;
            case SizeType::PreSize:
                _percentContentSize = size;
                if (_usingPercentContentSize)
                {
                    this->getOwner()->setContentSize(Size(size.x*parentSize.width,size.y*parentSize.height));
                }
                break;
            case SizeType::PreSizeEnable:
                if (_usingPercentContentSize)
                {
                    Size baseSize = this->getOwner()->getContentSize();
                    if (parentSize.width != 0)
                    {
                        _percentContentSize.x = baseSize.width/parentSize.width;
                    }
                    else
                    {
                        _percentContentSize.x = 0;
                        baseSize.width = 0;
                    }

                    if (parentSize.height != 0)
                    {
                        _percentContentSize.y = baseSize.height/parentSize.height;
                    }
                    else
                    {
                        _percentContentSize.y = 0;
                        baseSize.height = 0;
                    }

                    this->getOwner()->setContentSize(baseSize);
                }
                break;
            default:
                break;
            }
        }
        else
        {
            switch (sType)
            {
            case SizeType::Size:
                this->getOwner()->setContentSize(Size(size.x,size.y));
                break;
            case SizeType::PreSize:
                _percentContentSize = size;
                break;
            default:
                break;
            }
        }
    }

    //Position
    bool LayoutComponent::isUsingPercentPosition()
    {
        return _usingPercentPosition;
    }
    void LayoutComponent::setUsingPercentPosition(bool flag)
    {
        _usingPercentPosition = flag;
        this->RefreshLayoutPosition(PositionType::PreRelativePositionEnable,Vec2(0,0));
    }

    const Vec2& LayoutComponent::getPercentPosition()
    {
        return _percentPosition;
    }
    void LayoutComponent::setPercentPosition(const Vec2& percent)
    {
        this->RefreshLayoutPosition(PositionType::PreRelativePosition,percent);
    }

    const Vec2& LayoutComponent::getOwnerPosition()const
    {
        return this->getOwner()->getPosition();
    }
    void LayoutComponent::setOwnerPosition(const Vec2& point)
    {
        this->RefreshLayoutPosition(PositionType::Position,point);
    }

    const Vec2& LayoutComponent::getRelativePosition()
    {
        return _relativePosition;
    }
    void LayoutComponent::setRelativePosition(const Vec2& position)
    {
        this->RefreshLayoutPosition(PositionType::RelativePosition,position);
    }

    LayoutComponent::ReferencePoint LayoutComponent::getReferencePoint()
    {
        return _referencePoint;
    }
    void LayoutComponent::setReferencePoint(ReferencePoint point)
    {
        _referencePoint = point;
        this->RefreshLayoutPosition(PositionType::RelativePosition,_relativePosition);
    }

    void LayoutComponent::RefreshLayoutPosition(PositionType pType,const Vec2& point)
    {
        Node* parentNode = this->getOwner()->getParent();
        Point basePoint = point;
        if (parentNode != NULL && _actived)
        {
            Size parentSize = parentNode->getContentSize();
            
            if ( pType == PositionType::PreRelativePosition)
            {
                _percentPosition = point;
                basePoint = Point(_percentPosition.x*parentSize.width,_percentPosition.y*parentSize.height);
            }
            else if(pType == PositionType::PreRelativePositionEnable)
            {
                if (_usingPercentPosition)
                {
                    if (parentSize.width != 0)
                    {
                        _percentPosition.x = _relativePosition.x/parentSize.width;
                    }
                    else
                    {
                        _percentPosition.x = 0;
                        _relativePosition.x = 0;
                    }

                    if (parentSize.height != 0)
                    {
                        _percentPosition.y = _relativePosition.y/parentSize.height;
                    }
                    else
                    {
                        _percentPosition.y = 0;
                        _relativePosition.y = 0;
                    }
                }
                basePoint = _relativePosition;
            }
            
            Point inversePoint = basePoint;
            switch (_referencePoint)
            {
            case ReferencePoint::TOP_LEFT:
                inversePoint.y = parentSize.height - inversePoint.y;
                break;
            case ReferencePoint::BOTTOM_RIGHT:
                inversePoint.x = parentSize.width - inversePoint.x;
                break;
            case ReferencePoint::TOP_RIGHT:
                inversePoint.x = parentSize.width - inversePoint.x;
                inversePoint.y = parentSize.height - inversePoint.y;
                break;
            default:
                break;
            }

            switch (pType)
            {
            case PositionType::Position:
                this->getOwner()->setPosition(basePoint);
                _relativePosition = inversePoint;
                if (parentSize.width != 0 && parentSize.height != 0)
                {
                    _percentPosition = Point(_relativePosition.x/parentSize.width,_relativePosition.y/parentSize.height);
                }
                else
                {
                    _percentPosition = Point(0,0);
                }
                break;
            case PositionType::RelativePosition:
                this->getOwner()->setPosition(inversePoint);
                _relativePosition = basePoint;
                if (parentSize.width != 0 && parentSize.height != 0)
                {
                    _percentPosition = Point(_relativePosition.x/parentSize.width,_relativePosition.y/parentSize.height);
                }
                else
                {
                    _percentPosition = Point(0,0);
                }
                break;
            case PositionType::PreRelativePosition:
                this->getOwner()->setPosition(inversePoint);
                _relativePosition = basePoint;
                break;
            case PositionType::PreRelativePositionEnable:
                this->getOwner()->setPosition(inversePoint);
                _relativePosition = basePoint;
                break;
            default:
                break;
            }
        }
        else
        {
            switch (pType)
            {
            case PositionType::Position:
                this->getOwner()->setPosition(basePoint);
                if (_referencePoint == ReferencePoint::BOTTOM_LEFT)
                {
                    _relativePosition = basePoint;
                }
                break;
            case PositionType::RelativePosition:
                _relativePosition = basePoint;
                break;
            case PositionType::PreRelativePosition:
                _percentPosition = basePoint;
                break;
            default:
                break;
            }
        }
    }

    void LayoutComponent::SetActiveEnable(bool enable)
    {
        _actived = enable;
    }
}

NS_CC_END