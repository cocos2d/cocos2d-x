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
    Vec2 LayoutComponent::getOwnerContentSize()const
    {
        return this->getOwner()->getContentSize();
    }
    void LayoutComponent::setOwnerContentSize(const Vec2& size)
    {
        this->getOwner()->setContentSize(Size(size.x,size.y));

        Node* parentNode = this->getOwner()->getParent();
        if (parentNode != NULL && _actived)
        {
            Size parentSize = parentNode->getContentSize();

            if (parentSize.width != 0 && parentSize.height != 0)
            {
                _percentContentSize = Point(size.x/parentSize.width,size.y/parentSize.height);
            }
            else
            {
                _percentContentSize = Point(0,0);
            }
        }
    }

    const Vec2& LayoutComponent::getPercentContentSize()const
    {
        return _percentContentSize;
    }
    
    void LayoutComponent::setPercentContentSize(const Vec2& percent)
    {
        _percentContentSize = percent;

        Node* parentNode = this->getOwner()->getParent();
        if (parentNode != NULL && _actived)
        {
            Size parentSize = parentNode->getContentSize();
            if (_usingPercentContentSize)
            {
                this->getOwner()->setContentSize(Size(percent.x*parentSize.width,percent.y*parentSize.height));
            }
        }
    }
    
    bool LayoutComponent::isUsingPercentContentSize()
    {
        return _usingPercentContentSize;
    }

    void LayoutComponent::setUsingPercentContentSize(bool flag)
    {
        _usingPercentContentSize = flag;

        Node* parentNode = this->getOwner()->getParent();
        if (parentNode != NULL && _actived)
        {
            Size parentSize = parentNode->getContentSize();
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

        Node* parentNode = this->getOwner()->getParent();
        if (parentNode != NULL && _actived)
        {
            Size parentSize = parentNode->getContentSize();

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

            Point inversePoint = this->converPointWithReferencePointAndSize(_relativePosition,parentSize);
            this->getOwner()->setPosition(inversePoint);
        }
    }

    const Vec2& LayoutComponent::getPercentPosition()
    {
        return _percentPosition;
    }
    void LayoutComponent::setPercentPosition(const Vec2& percent)
    {
        _percentPosition = percent;

        Node* parentNode = this->getOwner()->getParent();
        if (parentNode != NULL && _actived)
        {
            Size parentSize = parentNode->getContentSize();
            _relativePosition = Point(_percentPosition.x*parentSize.width,_percentPosition.y*parentSize.height);
            Point inversePoint = this->converPointWithReferencePointAndSize(_relativePosition,parentSize);
            this->getOwner()->setPosition(inversePoint);
        }
    }

    const Vec2& LayoutComponent::getOwnerPosition()const
    {
        return this->getOwner()->getPosition();
    }
    void LayoutComponent::setOwnerPosition(const Vec2& point)
    {
        Node* parentNode = this->getOwner()->getParent();
        if (parentNode != NULL && _actived)
        {
            Size parentSize = parentNode->getContentSize();

            Point inversePoint = this->converPointWithReferencePointAndSize(point,parentSize);
            this->getOwner()->setPosition(point);
            _relativePosition = inversePoint;
            if (parentSize.width != 0 && parentSize.height != 0)
            {
                _percentPosition = Point(_relativePosition.x/parentSize.width,_relativePosition.y/parentSize.height);
            }
            else
            {
                _percentPosition = Point(0,0);
            }
        }
        else
        {
            this->getOwner()->setPosition(point);
            if (_referencePoint == ReferencePoint::BOTTOM_LEFT)
            {
                _relativePosition = point;
            }
        }

    }

    const Vec2& LayoutComponent::getRelativePosition()
    {
        return _relativePosition;
    }
    void LayoutComponent::setRelativePosition(const Vec2& position)
    {
        _relativePosition = position;

        Node* parentNode = this->getOwner()->getParent();
        if (parentNode != NULL && _actived)
        {
            Size parentSize = parentNode->getContentSize();

            Point inversePoint = this->converPointWithReferencePointAndSize(_relativePosition,parentSize);
            this->getOwner()->setPosition(inversePoint);
            if (parentSize.width != 0 && parentSize.height != 0)
            {
                _percentPosition = Point(_relativePosition.x/parentSize.width,_relativePosition.y/parentSize.height);
            }
            else
            {
                _percentPosition = Point(0,0);
            }
        }
    }

    LayoutComponent::ReferencePoint LayoutComponent::getReferencePoint()
    {
        return _referencePoint;
    }
    void LayoutComponent::setReferencePoint(ReferencePoint point)
    {
        _referencePoint = point;
        this->setRelativePosition(_relativePosition);
    }

    void LayoutComponent::setActiveEnable(bool enable)
    {
        _actived = enable;
    }

    Vec2 LayoutComponent::converPointWithReferencePointAndSize(const Vec2& point,const Size& size)
    {
        Point inversePoint = point;
        switch (_referencePoint)
        {
        case ReferencePoint::TOP_LEFT:
            inversePoint.y = size.height - inversePoint.y;
            break;
        case ReferencePoint::BOTTOM_RIGHT:
            inversePoint.x = size.width - inversePoint.x;
            break;
        case ReferencePoint::TOP_RIGHT:
            inversePoint.x = size.width - inversePoint.x;
            inversePoint.y = size.height - inversePoint.y;
            break;
        default:
            break;
        }
        return inversePoint;
    }
}

NS_CC_END