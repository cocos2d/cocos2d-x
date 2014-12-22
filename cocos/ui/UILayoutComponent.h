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

#ifndef __cocos2d_libs__LayoutComponent__
#define __cocos2d_libs__LayoutComponent__
#include "2d/CCComponent.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN

namespace ui {
    class CC_GUI_DLL LayoutComponent : public Component
    {
    public:
        LayoutComponent();
        ~LayoutComponent();
        virtual bool init()override;
        CREATE_FUNC(LayoutComponent);

        static LayoutComponent* boundingLayoutForNode(Node* node);

        enum class HorizontalEage
        {
            None,
            Left,
            Right,
            Center
        };
        enum class VerticalEage
        {
            None,
            Bottom,
            Top,
            Center
        };

        // OldVersion
        virtual void setUsingPercentContentSize(bool isUsed);
        virtual bool getUsingPercentContentSize()const;

        virtual void setPercentContentSize(const Vec2 &percent);
        virtual Vec2 getPercentContentSize()const;

        // Position & Margin
        virtual const Point& getAnchorPosition()const;
        virtual void setAnchorPosition(const Point& point);

        virtual const Point& getPosition()const;
        virtual void setPosition(const Point& position);

        virtual bool isUsingPositionPercentX()const;
        virtual void setPositionPercentXEnabled(bool isUsed);

        virtual float getPositionPercentX()const;
        virtual void setPositionPercentX(float percentMargin);

        virtual bool isUsingPositionPercentY()const;
        virtual void setPositionPercentYEnabled(bool isUsed);

        virtual float getPositionPercentY()const;
        virtual void setPositionPercentY(float percentMargin);

        virtual HorizontalEage getHorizontalEage()const;
        virtual void setHorizontalEage(HorizontalEage hEage);

        virtual VerticalEage getVerticalEage()const;
        virtual void setVerticalEage(VerticalEage vEage);

        virtual float getLeftMargin()const;
        virtual void setLeftMargin(float margin);

        virtual float getRightMargin()const;
        virtual void setRightMargin(float margin);

        virtual float getTopMargin()const;
        virtual void setTopMargin(float margin);

        virtual float getButtomMargin()const;
        virtual void setButtomMargin(float margin);

        // Size & Percent
        virtual const Size& getSize()const;
        virtual void setSize(const Size& _size);

        virtual bool isUsingPercentWidth()const;
        virtual void setPercentWidthEnabled(bool isUsed);

        virtual float getSizeWidth()const;
        virtual void setSizeWidth(float width);

        virtual float getPercentWidth()const;
        virtual void setPercentWidth(float percentWidth);

        virtual bool isUsingPercentHeight()const;
        virtual void setPercentHeightEnabled(bool isUsed);

        virtual float getSizeHeight()const;
        virtual void setSizeHeight(float height);

        virtual float getPercentHeight()const;
        virtual void setPercentHeight(float percentHeight);

        virtual bool isUsingStretchWidth()const;
        virtual void setStretchWidthEnabled(bool isUsed);

        virtual bool isUsingStretchHeight()const;
        virtual void setStretchHeightEnabled(bool isUsed);

        virtual void setActiveEnable(bool enable);
        virtual void refreshLayout();

    protected:
        Node* getOwnerParent();
        virtual void refreshHorizontalMargin();
        virtual void refreshVerticalMargin();
    protected:
        HorizontalEage  _horizontalEage;
        VerticalEage    _verticalEage;

        float           _leftMargin;
        float           _rightMargin;
        float           _buttomMargin;
        float           _topMargin;

        bool            _usingPositionPercentX;
        float           _positionPercentX;
        bool            _usingPositionPercentY;
        float           _positionPercentY;

        bool            _usingStretchWidth;
        bool            _usingStretchHeight;

        float           _percentWidth;
        bool            _usingPercentWidth;
        
        float           _percentHeight;
        bool            _usingPercentHeight;

        bool _actived;
    };
}

NS_CC_END
#endif /* defined(__cocos2d_libs__LayoutComponent__) */
