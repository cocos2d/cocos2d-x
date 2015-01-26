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

        static LayoutComponent* bindLayoutComponent(Node* node);

        enum class HorizontalEdge
        {
            None,
            Left,
            Right,
            Center
        };
        enum class VerticalEdge
        {
            None,
            Bottom,
            Top,
            Center
        };

        // OldVersion
        void setUsingPercentContentSize(bool isUsed);
        bool getUsingPercentContentSize()const;

        void setPercentContentSize(const Vec2 &percent);
        Vec2 getPercentContentSize()const;

        // Position & Margin
        const Point& getAnchorPosition()const;
        void setAnchorPosition(const Point& point);

        const Point& getPosition()const;
        void setPosition(const Point& position);

        bool isPositionPercentXEnabled()const;
        void setPositionPercentXEnabled(bool isUsed);

        float getPositionPercentX()const;
        void setPositionPercentX(float percentMargin);

        bool isPositionPercentYEnabled()const;
        void setPositionPercentYEnabled(bool isUsed);

        float getPositionPercentY()const;
        void setPositionPercentY(float percentMargin);

        HorizontalEdge getHorizontalEdge()const;
        void setHorizontalEdge(HorizontalEdge hEage);

        VerticalEdge getVerticalEdge()const;
        void setVerticalEdge(VerticalEdge vEage);

        float getLeftMargin()const;
        void setLeftMargin(float margin);

        float getRightMargin()const;
        void setRightMargin(float margin);

        float getTopMargin()const;
        void setTopMargin(float margin);

        float getBottomMargin()const;
        void setBottomMargin(float margin);

        // Size & Percent
        const Size& getSize()const;
        void setSize(const Size& size);

        bool isPercentWidthEnabled()const;
        void setPercentWidthEnabled(bool isUsed);

        float getSizeWidth()const;
        void setSizeWidth(float width);

        float getPercentWidth()const;
        void setPercentWidth(float percentWidth);

        bool isPercentHeightEnabled()const;
        void setPercentHeightEnabled(bool isUsed);

        float getSizeHeight()const;
        void setSizeHeight(float height);

        float getPercentHeight()const;
        void setPercentHeight(float percentHeight);

        bool isStretchWidthEnabled()const;
        void setStretchWidthEnabled(bool isUsed);

        bool isStretchHeightEnabled()const;
        void setStretchHeightEnabled(bool isUsed);

        void setPercentOnlyEnabled(bool enable);
        void setActiveEnabled(bool enable);
        void refreshLayout();

    protected:
        Node* getOwnerParent();
        void refreshHorizontalMargin();
        void refreshVerticalMargin();
    protected:
        HorizontalEdge  _horizontalEdge;
        VerticalEdge    _verticalEdge;

        float           _leftMargin;
        float           _rightMargin;
        float           _bottomMargin;
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

        bool            _actived;
        bool            _isPercentOnly;
    };
}

NS_CC_END
#endif /* defined(__cocos2d_libs__LayoutComponent__) */
