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
#include "UIPageView.h"
#include "UILayoutComponent.h"
#include "2d/CCNode.h"
#include "GUIDefine.h"
#include "UIHelper.h"

NS_CC_BEGIN

namespace ui {
    LayoutComponent::LayoutComponent()
        :_horizontalEdge(HorizontalEdge::None)
        , _verticalEdge(VerticalEdge::None)
        , _leftMargin(0)
        , _rightMargin(0)
        , _bottomMargin(0)
        , _topMargin(0)
        , _usingPositionPercentX(false)
        , _positionPercentX(0)
        , _usingPositionPercentY(false)
        , _positionPercentY(0)
        , _usingStretchWidth(false)
        , _usingStretchHeight(false)
        , _percentWidth(0)
        , _usingPercentWidth(false)
        , _percentHeight(0)
        , _usingPercentHeight(false)
        , _actived(true)
        , _isPercentOnly(false)
    {
        _name = __LAYOUT_COMPONENT_NAME;
    }

    LayoutComponent::~LayoutComponent()
    {

    }

    LayoutComponent* LayoutComponent::bindLayoutComponent(Node* node)
    {
        LayoutComponent * layout = (LayoutComponent*)node->getComponent(__LAYOUT_COMPONENT_NAME);
        if (layout != nullptr)
            return layout;

        layout = new (std::nothrow) LayoutComponent();
        if (layout && layout->init())
        {
            layout->autorelease();
            node->addComponent(layout);
            return layout;
        }
        CC_SAFE_DELETE(layout);
        return nullptr;
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

            //put layout component initialized code here

        } while (0);
        return ret;
    }

    Node* LayoutComponent::getOwnerParent()
    {
        Node* parent = _owner->getParent();
        return parent;
    }
    void LayoutComponent::refreshHorizontalMargin()
    {
        Node* parent = this->getOwnerParent();
        if (parent == nullptr)
            return;

        const Point& ownerPoint = _owner->getPosition();
        const Point& ownerAnchor = _owner->getAnchorPoint();
        const Size& ownerSize = _owner->getContentSize();
        const Size& parentSize = parent->getContentSize();

        _leftMargin = ownerPoint.x - ownerAnchor.x * ownerSize.width;
        _rightMargin = parentSize.width - (ownerPoint.x + (1 - ownerAnchor.x) * ownerSize.width);
    }
    void LayoutComponent::refreshVerticalMargin()
    {
        Node* parent = this->getOwnerParent();
        if (parent == nullptr)
            return;

        const Point& ownerPoint = _owner->getPosition();
        const Point& ownerAnchor = _owner->getAnchorPoint();
        const Size& ownerSize = _owner->getContentSize();
        const Size& parentSize = parent->getContentSize();

        _bottomMargin = ownerPoint.y - ownerAnchor.y * ownerSize.height;
        _topMargin = parentSize.height - (ownerPoint.y + (1 - ownerAnchor.y) * ownerSize.height);
    }

    //OldVersion
    void LayoutComponent::setUsingPercentContentSize(bool isUsed)
    {
        _usingPercentWidth = _usingPercentHeight = isUsed;
    }
    bool LayoutComponent::getUsingPercentContentSize()const
    {
        return _usingPercentWidth && _usingPercentHeight;
    }

    void LayoutComponent::setPercentContentSize(const Vec2 &percent)
    {
        this->setPercentWidth(percent.x);
        this->setPercentHeight(percent.y);
    }
    Vec2 LayoutComponent::getPercentContentSize()const
    {
        Vec2 vec2=Vec2(_percentWidth,_percentHeight);
        return vec2;
    }

    //Position & Margin
    const Point& LayoutComponent::getAnchorPosition()const
    {
        return _owner->getAnchorPoint();
    }
    void LayoutComponent::setAnchorPosition(const Point& point)
    {
        Rect oldRect = _owner->getBoundingBox();
        _owner->setAnchorPoint(point);
        Rect newRect = _owner->getBoundingBox();
        float offSetX = oldRect.origin.x - newRect.origin.x;
        float offSetY = oldRect.origin.y - newRect.origin.y;

        Point ownerPosition = _owner->getPosition();
        ownerPosition.x += offSetX;
        ownerPosition.y += offSetY;

        this->setPosition(ownerPosition);
    }

    const Point& LayoutComponent::getPosition()const
    {
        return _owner->getPosition();
    }
    void LayoutComponent::setPosition(const Point& position)
    {
        Node* parent = this->getOwnerParent();
        if (parent != nullptr)
        {
            Point ownerPoint = position;
            const Size& parentSize = parent->getContentSize();

            if (parentSize.width != 0)
                _positionPercentX = ownerPoint.x / parentSize.width;
            else
            {
                _positionPercentX = 0;
                if (_usingPositionPercentX || _horizontalEdge == HorizontalEdge::Center)
                    ownerPoint.x = 0;
            }

            if (parentSize.height != 0)
                _positionPercentY = ownerPoint.y / parentSize.height;
            else
            {
                _positionPercentY = 0;
                if (_usingPositionPercentY || _verticalEdge == VerticalEdge::Center)
                    ownerPoint.y = 0;
            }

            _owner->setPosition(ownerPoint);

            this->refreshHorizontalMargin();
            this->refreshVerticalMargin();
        }
        else
            _owner->setPosition(position);
    }

    bool LayoutComponent::isPositionPercentXEnabled()const
    {
        return _usingPositionPercentX;
    }
    void LayoutComponent::setPositionPercentXEnabled(bool isUsed)
    {
        _usingPositionPercentX = isUsed;
        if (_usingPositionPercentX)
        {
            _horizontalEdge = HorizontalEdge::None;
        }
    }

    float LayoutComponent::getPositionPercentX()const
    {
        return _positionPercentX;
    }
    void LayoutComponent::setPositionPercentX(float percentMargin)
    {
        _positionPercentX = percentMargin;

        if (_usingPositionPercentX || _horizontalEdge == HorizontalEdge::Center)
        {
            Node* parent = this->getOwnerParent();
            if (parent != nullptr)
            {
                _owner->setPositionX(parent->getContentSize().width * _positionPercentX);
                this->refreshHorizontalMargin();
            }
        }
    }

    bool LayoutComponent::isPositionPercentYEnabled()const
    {
        return _usingPositionPercentY;
    }
    void LayoutComponent::setPositionPercentYEnabled(bool isUsed)
    {
        _usingPositionPercentY = isUsed;
        if (_usingPositionPercentY)
        {
            _verticalEdge = VerticalEdge::None;
        }
    }

    float LayoutComponent::getPositionPercentY()const
    {
        return _positionPercentY;
    }
    void LayoutComponent::setPositionPercentY(float percentMargin)
    {
        _positionPercentY = percentMargin;

        if (_usingPositionPercentY || _verticalEdge == VerticalEdge::Center)
        {
            Node* parent = this->getOwnerParent();
            if (parent != nullptr)
            {
                _owner->setPositionY(parent->getContentSize().height * _positionPercentY);
                this->refreshVerticalMargin();
            }
        }
    }

    LayoutComponent::HorizontalEdge LayoutComponent::getHorizontalEdge()const
    {
        return _horizontalEdge;
    }
    void LayoutComponent::setHorizontalEdge(HorizontalEdge hEage)
    {
        _horizontalEdge = hEage;
        if (_horizontalEdge != HorizontalEdge::None)
        {
            _usingPositionPercentX = false;
        }
    }

    LayoutComponent::VerticalEdge LayoutComponent::getVerticalEdge()const
    {
        return _verticalEdge;
    }
    void LayoutComponent::setVerticalEdge(VerticalEdge vEage)
    {
        _verticalEdge = vEage;
        if (_verticalEdge != VerticalEdge::None)
        {
            _usingPositionPercentY = false;
        }
    }

    float LayoutComponent::getLeftMargin()const
    {
        return _leftMargin;
    }
    void LayoutComponent::setLeftMargin(float margin)
    {
        _leftMargin = margin;
    }

    float LayoutComponent::getRightMargin()const
    {
        return _rightMargin;
    }
    void LayoutComponent::setRightMargin(float margin)
    {
        _rightMargin = margin;
    }

    float LayoutComponent::getTopMargin()const
    {
        return _topMargin;
    }
    void LayoutComponent::setTopMargin(float margin)
    {
        _topMargin = margin;
    }

    float LayoutComponent::getBottomMargin()const
    {
        return _bottomMargin;
    }
    void LayoutComponent::setBottomMargin(float margin)
    {
        _bottomMargin = margin;
    }

    //Size & Percent
    const Size& LayoutComponent::getSize()const
    {
        return this->getOwner()->getContentSize();
    }
    void LayoutComponent::setSize(const Size& size)
    {
        Node* parent = this->getOwnerParent();
        if (parent != nullptr)
        {
            Size ownerSize = size;
            const Size& parentSize = parent->getContentSize();

            if (parentSize.width != 0)
                _percentWidth = ownerSize.width / parentSize.width;
            else
            {
                _percentWidth = 0;
                if (_usingPercentWidth || (this->_horizontalEdge != HorizontalEdge::Center && this->_usingStretchWidth))
                    ownerSize.width = 0;
            }

            if (parentSize.height != 0)
                _percentHeight = ownerSize.height / parentSize.height;
            else
            {
                _percentHeight = 0;
                if (_usingPercentHeight || (this->_verticalEdge != VerticalEdge::Center && this->_usingStretchHeight))
                    ownerSize.height = 0;
            }

            _owner->setContentSize(ownerSize);

            this->refreshHorizontalMargin();
            this->refreshVerticalMargin();
        }
        else
            _owner->setContentSize(size);
    }

    bool LayoutComponent::isPercentWidthEnabled()const
    {
        return _usingPercentWidth;
    }
    void LayoutComponent::setPercentWidthEnabled(bool isUsed)
    {
        _usingPercentWidth = isUsed;
        if (_usingPercentWidth)
        {
            _usingStretchWidth = false;
        }
    }

    float LayoutComponent::getSizeWidth()const
    {
        return _owner->getContentSize().width;
    }
    void LayoutComponent::setSizeWidth(float width)
    {
        Size ownerSize = _owner->getContentSize();
        ownerSize.width = width;

        Node* parent = this->getOwnerParent();
        if (parent != nullptr)
        {
            const Size& parentSize = parent->getContentSize();
            if (parentSize.width != 0)
                _percentWidth = ownerSize.width / parentSize.width;
            else
            {
                _percentWidth = 0;
                if (_usingPercentWidth)
                    ownerSize.width = 0;
            }
            _owner->setContentSize(ownerSize);
            this->refreshHorizontalMargin();
        }
        else
            _owner->setContentSize(ownerSize);
    }

    float LayoutComponent::getPercentWidth()const
    {
        return _percentWidth;
    }
    void LayoutComponent::setPercentWidth(float percentWidth)
    {
        _percentWidth = percentWidth;

        if (_usingPercentWidth)
        {
            Node* parent = this->getOwnerParent();
            if (parent != nullptr)
            {
                Size ownerSize = _owner->getContentSize();
                ownerSize.width = parent->getContentSize().width * _percentWidth;
                _owner->setContentSize(ownerSize);

                this->refreshHorizontalMargin();
            }
        }
    }

    bool LayoutComponent::isPercentHeightEnabled()const
    {
        return _usingPercentHeight;
    }
    void LayoutComponent::setPercentHeightEnabled(bool isUsed)
    {
        _usingPercentHeight = isUsed;
        if (_usingPercentHeight)
        {
            _usingStretchHeight = false;
        }
    }

    float LayoutComponent::getSizeHeight()const
    {
        return _owner->getContentSize().height;
    }
    void LayoutComponent::setSizeHeight(float height)
    {
        Size ownerSize = _owner->getContentSize();
        ownerSize.height = height;

        Node* parent = this->getOwnerParent();
        if (parent != nullptr)
        {
            const Size& parentSize = parent->getContentSize();
            if (parentSize.height != 0)
                _percentHeight = ownerSize.height / parentSize.height;
            else
            {
                _percentHeight = 0;
                if (_usingPercentHeight)
                    ownerSize.height = 0;
            }
            _owner->setContentSize(ownerSize);
            this->refreshVerticalMargin();
        }
        else
            _owner->setContentSize(ownerSize);
    }

    float LayoutComponent::getPercentHeight()const
    {
        return _percentHeight;
    }
    void LayoutComponent::setPercentHeight(float percentHeight)
    {
        _percentHeight = percentHeight;

        if (_usingPercentHeight)
        {
            Node* parent = this->getOwnerParent();
            if (parent != nullptr)
            {
                Size ownerSize = _owner->getContentSize();
                ownerSize.height = parent->getContentSize().height * _percentHeight;
                _owner->setContentSize(ownerSize);

                this->refreshVerticalMargin();
            }
        }
    }

    bool LayoutComponent::isStretchWidthEnabled()const
    {
        return _usingStretchWidth;
    }
    void LayoutComponent::setStretchWidthEnabled(bool isUsed)
    {
        _usingStretchWidth = isUsed;
        if (_usingStretchWidth)
        {
            _usingPercentWidth = false;
        }
    }

    bool LayoutComponent::isStretchHeightEnabled()const
    {
        return _usingStretchHeight;
    }
    void LayoutComponent::setStretchHeightEnabled(bool isUsed)
    {
        _usingStretchHeight = isUsed;
        if (_usingStretchHeight)
        {
            _usingPercentHeight = false;
        }
    }

    void LayoutComponent::refreshLayout()
    {
        if (!_actived)
            return;
        
        Node* parent = this->getOwnerParent();
        if (parent == nullptr)
            return;

        const Size& parentSize = parent->getContentSize();
        const Point& ownerAnchor = _owner->getAnchorPoint();
        Size ownerSize = _owner->getContentSize();
        Point ownerPosition = _owner->getPosition();

        switch (this->_horizontalEdge)
        {
        case HorizontalEdge::None:
            if (_usingStretchWidth && !_isPercentOnly)
            {
                ownerSize.width = parentSize.width * _percentWidth;
                ownerPosition.x = _leftMargin + ownerAnchor.x * ownerSize.width;
            }
            else
            {
                if (_usingPositionPercentX)
                    ownerPosition.x = parentSize.width * _positionPercentX;
                if (_usingPercentWidth)
                    ownerSize.width = parentSize.width * _percentWidth;
            }
            break;
        case HorizontalEdge::Left:
            if (_isPercentOnly)
                break;
            if (_usingPercentWidth || _usingStretchWidth)
                ownerSize.width = parentSize.width * _percentWidth;
            ownerPosition.x = _leftMargin + ownerAnchor.x * ownerSize.width;
            break;
        case HorizontalEdge::Right:
            if (_isPercentOnly)
                break;
            if (_usingPercentWidth || _usingStretchWidth)
                ownerSize.width = parentSize.width * _percentWidth;
            ownerPosition.x = parentSize.width - (_rightMargin + (1 - ownerAnchor.x) * ownerSize.width);
            break;
        case HorizontalEdge::Center:
            if (_isPercentOnly)
                break;
            if (_usingStretchWidth)
            {
                ownerSize.width = parentSize.width - _leftMargin - _rightMargin;
                if (ownerSize.width < 0)
                    ownerSize.width = 0;
                ownerPosition.x = _leftMargin + ownerAnchor.x * ownerSize.width;
            }
            else
            {
                if (_usingPercentWidth)
                    ownerSize.width = parentSize.width * _percentWidth;
                ownerPosition.x = parentSize.width * _positionPercentX;
            }
            break;
        default:
            break;
        }

        switch (this->_verticalEdge)
        {
        case VerticalEdge::None:
            if (_usingStretchHeight && !_isPercentOnly)
            {
                ownerSize.height = parentSize.height * _percentHeight;
                ownerPosition.y = _bottomMargin + ownerAnchor.y * ownerSize.height;
            }
            else
            {
                if (_usingPositionPercentY)
                    ownerPosition.y = parentSize.height * _positionPercentY;
                if (_usingPercentHeight)
                    ownerSize.height = parentSize.height * _percentHeight;
            }
            break;
        case VerticalEdge::Bottom:
            if (_isPercentOnly)
                break;
            if (_usingPercentHeight || _usingStretchHeight)
                ownerSize.height = parentSize.height * _percentHeight;
            ownerPosition.y = _bottomMargin + ownerAnchor.y * ownerSize.height;
            break;
        case VerticalEdge::Top:
            if (_isPercentOnly)
                break;
            if (_usingPercentHeight || _usingStretchHeight)
                ownerSize.height = parentSize.height * _percentHeight;
            ownerPosition.y = parentSize.height - (_topMargin + (1 - ownerAnchor.y) * ownerSize.height);
            break;
        case VerticalEdge::Center:
            if (_isPercentOnly)
                break;
            if (_usingStretchHeight)
            {
                ownerSize.height = parentSize.height - _topMargin - _bottomMargin;
                if (ownerSize.height < 0)
                    ownerSize.height = 0;
                ownerPosition.y = _bottomMargin + ownerAnchor.y * ownerSize.height;
            }
            else
            {
                if (_usingPercentHeight)
                    ownerSize.height = parentSize.height * _percentHeight;
                ownerPosition.y = parentSize.height* _positionPercentY;
            }
            break;
        default:
            break;
        }

        _owner->setPosition(ownerPosition);
        _owner->setContentSize(ownerSize);

        if (typeid(*_owner) == typeid(PageView))
        {
            PageView* page = static_cast<PageView*>(_owner);
            page->forceDoLayout();

            Vector<Widget*> _widgetVector = page->getItems();
            for(auto& item : _widgetVector)
            {
                ui::Helper::doLayout(item);
            }
        }
        else
        {
            ui::Helper::doLayout(_owner);
        }
    }

    void LayoutComponent::setActiveEnabled(bool enable)
    {
        _actived = enable;
    }

    void LayoutComponent::setPercentOnlyEnabled(bool enable)
    {
        _isPercentOnly = enable;
    }
}

NS_CC_END