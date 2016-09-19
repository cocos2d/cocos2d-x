/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.

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
/**
 * @addtogroup ui
 * @{
 */

namespace ui {
    /**
     *@brief A component class used for layout.
     * The LayoutComponent holds all the data for layouting.
     */
    class CC_GUI_DLL LayoutComponent : public Component
    {
    public:
        /**
         * Default constructor
         *
         * @lua new
         */
        LayoutComponent();

        /**
         * Default destructor
         *
         * @lua NA
         */
        ~LayoutComponent();

        virtual bool init()override;

        /**
         * Create a LayoutComponent instance with default settings.
         */
        CREATE_FUNC(LayoutComponent);

        /**
         * Bind a LayoutComponent to a specified node.
         * If the node has already binded a LayoutComponent named __LAYOUT_COMPONENT_NAME, just return the LayoutComponent.
         * Otherwise, create a new LayoutComponent and bind the LayoutComponent to the node.
         *@param node A Node* instance pointer.
         *@return The binded LayoutComponent instance pointer.
         */
        static LayoutComponent* bindLayoutComponent(Node* node);

        /**
         * Horizontal dock position type.
         */
        enum class HorizontalEdge
        {
            None,
            Left,
            Right,
            Center
        };

        /**
         * Vertical dock position type.
         */
        enum class VerticalEdge
        {
            None,
            Bottom,
            Top,
            Center
        };

        /**
         * Percent content size is used to adapt node's content size based on parent's content size.
         * If set to true then node's content size will be changed based on the value set by @see setPercentContentSize
         *@param isUsed True to enable percent content size, false otherwise.
         */
        void setUsingPercentContentSize(bool isUsed);

        /**
         * Query whether use percent content size or not.
         *@return True if using percent content size, false otherwise.
         */
        bool getUsingPercentContentSize()const;

        /**
         * Set percent content size.
         * The value should be [0-1], 0 means the child's content size will be 0
         * and 1 means the child's content size is the same as its parents.
         *@param percent The percent (x,y) of the node in [0-1] scope.
         */
        void setPercentContentSize(const Vec2 &percent);

        /**
         * Query the percent content size value.
         *@return Percent (x,y) in Vec2.
         */
        Vec2 getPercentContentSize()const;

        /**
         * Query the anchor position.
         *@return Anchor position to it's parent
         */
        const Point& getAnchorPosition()const;

        /**
         * Change the anchor position to it's parent.
         *@param point A value in (x,y) format.
         */
        void setAnchorPosition(const Point& point);

        /**
         * Query the owner's position.
         *@return The owner's position.
         */
        const Point& getPosition()const;

        /**
         * Change the position of component owner.
         * @param position A position in (x,y)
         */ 
        void setPosition(const Point& position);

        /**
         * Whether position percentX is enabled or not. 
         *@return True if position percentX is enable, false otherwise.
         */
        bool isPositionPercentXEnabled()const;
        
        /**
         * Toggle position percentX enabled.
         *@param isUsed  True if enable position percentX, false otherwise.
         */
        void setPositionPercentXEnabled(bool isUsed);

        /**
         * Query the position percent X value.
         *@return Position percent X value in float.
         */
        float getPositionPercentX()const;

        /**
         * Change position percent X value.
         *@param percentMargin Margin in float.
         */
        void setPositionPercentX(float percentMargin);

        /**
         * Whether position percentY is enabled or not.
         *@see `setPositionPercentYEnabled`
         *@return True if position percentY is enabled, false otherwise.
         */
        bool isPositionPercentYEnabled()const;

        /**
         * Toggle position percentY enabled.
         *@param isUsed True if position percentY is enabled, false otherwise.
         */
        void setPositionPercentYEnabled(bool isUsed);

        /**
         * Query the position percentY Y value.
         *@return Position percent Y value in float.
         */
        float getPositionPercentY()const;

        /**
         * Change position percentY value.
         *@param percentMargin Margin in float.
         */
        void setPositionPercentY(float percentMargin);

        /**
         * Query element horizontal dock type.
         *@return Horizontal dock type.
         */
        HorizontalEdge getHorizontalEdge()const;

        /**
         * Change element's horizontal dock type.
         *@param hEage Horizontal dock type @see `HorizontalEdge`
         */
        void setHorizontalEdge(HorizontalEdge hEage);

        /**
         * Query element vertical dock type.
         *@return Vertical dock type.
         */
        VerticalEdge getVerticalEdge()const;

        /**
         * Change element's vertical dock type.
         *@param vEage Vertical dock type @see `VerticalEdge`.
         */
        void setVerticalEdge(VerticalEdge vEage);

        /**
         * Query left margin of owner relative to its parent.
         *@return Left margin in float.
         */
        float getLeftMargin()const;

        /**
         * Change left margin of owner relative to its parent.
         *@param margin Margin in float.
         */
        void setLeftMargin(float margin);

        /**
         * Query the right margin of owner relative to its parent.
         *@return Right margin in float.
         */
        float getRightMargin()const;

        /**
         * Change right margin of owner relative to its parent.
         *@param margin Margin in float.
         */
        void setRightMargin(float margin);

        /**
         * Query the top margin of owner relative to its parent.
         *@return Top margin in float.
         */
        float getTopMargin()const;

        /**
         * Change the top margin of owner relative to its parent.
         *@param margin Margin in float.
         */
        void setTopMargin(float margin);

        /**
         * Query the bottom margin of owner relative to its parent.
         *@return Bottom margin in float.
         */
        float getBottomMargin()const;

        /**
         * Change the bottom margin of owner relative to its parent.
         *@param margin in float.
         */
        void setBottomMargin(float margin);

        /**
         * Query owner's content size.
         *@return Owner's content size.
         */
        const Size& getSize()const;

        /**
         * Change the content size of owner.
         *@param size Content size in @see `Size`.
         */
        void setSize(const Size& size);

        /**
         * Query whether percent width is enabled or not.
         *@return True if percent width is enabled, false, otherwise.
         */
        bool isPercentWidthEnabled()const;

        /**
         * Toggle enable percent width.
         *@param isUsed True if percent width is enabled, false otherwise.
         */
        void setPercentWidthEnabled(bool isUsed);

        /**
         * Query content size width of owner.
         *@return Content size width in float.
         */
        float getSizeWidth()const;

        /**
         * Change content size width of owner.
         *@param width Content size width in float.
         */
        void setSizeWidth(float width);

        /**
         * Query percent width of owner.
         *@return percent width in float.
         */
        float getPercentWidth()const;

        /**
         * Change percent width of owner.
         *@param percentWidth Percent Width in float.
         */
        void setPercentWidth(float percentWidth);

        /**
         * Query whether percent height is enabled or not.
         *@return True if percent height is enabled, false otherwise.
         */
        bool isPercentHeightEnabled()const;

        /**
         * Toggle enable percent height.
         *@param isUsed True if percent height is enabled, false otherwise.
         */
        void setPercentHeightEnabled(bool isUsed);

        /**
         * Query size height of owner.
         *@return Size height in float.
         */
        float getSizeHeight()const;

        /**
         * Change size height of owner.
         *@param height Size height in float.
         */
        void setSizeHeight(float height);

        /**
         * Query percent height of owner.         
         *@return Percent height in float.
         */
        float getPercentHeight()const;

        /**
         * Change percent height value of owner.
         *@param percentHeight Percent height in float.
         */
        void setPercentHeight(float percentHeight);

        /**
         * Query whether stretch width is enabled or not.
         *@return True if stretch width is enabled, false otherwise.
         */
        bool isStretchWidthEnabled()const;

        /**
         * Toggle enable stretch width.
         *@param isUsed True if enable stretch width, false otherwise.
         */
        void setStretchWidthEnabled(bool isUsed);

        /**
         * Query whether stretch height is enabled or not.
         *@return True if stretch height is enabled, false otherwise.
         */
        bool isStretchHeightEnabled()const;

        /**
         * Toggle enable stretch height.
         *@param isUsed True if stretch height is enabled, false otherwise.
         */
        void setStretchHeightEnabled(bool isUsed);
        
        /**
         * Toggle enable percent only.
         *@param enable True if percent only is enabled, false otherwise.
         */
        void setPercentOnlyEnabled(bool enable);

        /**
         * Toggle active enabled of LayoutComponent's owner.
         *@param enable True if active layout component, false otherwise.
         */
        void setActiveEnabled(bool enable);

        /**
         * Refresh layout of the owner.
         */
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

// end of ui group
/// @}
NS_CC_END
#endif /* defined(__cocos2d_libs__LayoutComponent__) */
