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
/**
 * @addtogroup ui
 * @{
 */

namespace ui {

    /**
     * @brief @~english A component class used for layout.
     * The LayoutComponent holds all the data for layouting.
     * @~chinese 用于layout的组件类。
     * LayoutComponent保存的所有用于布局的数据。
     */
    class CC_GUI_DLL LayoutComponent : public Component
    {
    public:

        /**
         * @~english
         * Default constructor
         *
         * @~chinese 
         * 默认构造函数
         * 
         * @lua new
         */
        LayoutComponent();

        /**
         * @~english
         * Default destructor
         *
         * @~chinese 
         * 默认的析构函数
         * 
         * @lua NA
         */
        ~LayoutComponent();

        virtual bool init()override;

        /**
         * @~english
         * Create a LayoutComponent instance with default settings.
         * @~chinese 
         * 用默认设置创建一个LayoutComponent实例。
         */
        CREATE_FUNC(LayoutComponent);

        /**
         * @~english
         * Bind a LayoutComponent to a specified node.
         * If the node has already binded a LayoutComponent named __LAYOUT_COMPONENT_NAME, just return the LayoutComponent.
         * Otherwise, create a new LayoutComponent and bind the LayoutComponent to the node.
         * @~chinese 
         * 将LayoutComponent绑定到一个指定的节点。
         * 如果节点已经绑定一个名叫__LAYOUT_COMPONENT_NAME的LayoutComponent,则只返回LayoutComponent。
         * 否则，创建一个新的LayoutComponent并绑定LayoutComponent到节点。
         * @param node @~english A Node* instance pointer.
         * @~chinese 一个节点指针
         * @return @~english The binded LayoutComponent instance pointer.
         * @~chinese 绑定LayoutComponent实例的指针。
         */
        static LayoutComponent* bindLayoutComponent(Node* node);

        /**
         * @~english
         * Horizontal dock position type.
         * @~chinese 
         * 水平停靠位置类型。
         */
        enum class HorizontalEdge
        {
            None,
            Left,
            Right,
            Center
        };

        /**
         * @~english
         * Vertical dock position type.
         * @~chinese 
         * 垂直停靠位置类型。
         */
        enum class VerticalEdge
        {
            None,
            Bottom,
            Top,
            Center
        };

        /**
         * @~english
         * Percent content size is used to adapt node's content size based on parent's content size.
         * If set to true then node's content size will be changed based on the value setted by @see setPercentContentSize
         * @~chinese 
         * 根据父节点的内容大小按百分比调整节点的内容大小。
         * 如果设置为true，则基于父节点来改变自身的大小，@see setPercentContentSize
         *
         * @param isUsed @~english True to enable percent content size, false otherwise.
         * @~chinese 启用则返回true，未启用则返回false。
         */
        void setUsingPercentContentSize(bool isUsed);

        /**
         * @~english
         * Query whether use percent content size or not.
         * @~chinese 
         * 查询是否开启了百分比控制内容大小。
         * @return @~english True if using percent content size, false otherwise.
         * @~chinese 如果开启了百分比控制大小则返回true,否则返回false。
         */
        bool getUsingPercentContentSize()const;

        /**
         * @~english
         * Set percent content size.
         * The value should be [0-1], 0 means the child's content size will be 0
         * and 1 means the child's content size is the same as its parents.
         * @~chinese 
         * 设置百分比大小。
         * 值应该在0 - 1之间, 0意味着子节点的内容大小为0
         * 1意味着子节点的内容大小和其父节点一样。
         * @param percent @~english The percent (x,y) of the node in [0-1] scope.
         * @~chinese 百分比(x,y)，在(0 - 1)范围内。
         */
        void setPercentContentSize(const Vec2 &percent);

        /**
         * @~english
         * Query the percent content size value.
         * @~chinese 
         * 查询内容大小百分比值。
         * @return @~english Percet (x,y) in Vec2.
         * @~chinese Vec2类型的百分比数据(x,y)。
         */
        Vec2 getPercentContentSize()const;

        /**
         * @~english
         * Query the anchor position.
         * @~chinese 
         * 查询锚点的位置。
         * @return @~english Anchor position to it's parent
         * @~chinese 锚点的位置
         */
        const Point& getAnchorPosition()const;

        /**
         * @~english
         * Change the anchor position to it's parent.
         * @~chinese 
         * 设置锚点的位置
         * @param point @~english A value in (x,y) format.
         * @~chinese 一个(x,y)格式的值。
         */
        void setAnchorPosition(const Point& point);

        /**
         * @~english
         * Query the owner's position.
         * @~chinese 
         * 查询这个component所有者的位置。
         * @return @~english The owner's position.
         * @~chinese 位置数据
         */
        const Point& getPosition()const;

        /**
         * @~english
         * Change the position of component owner.
         * @~chinese 
         * 更改component所有者的位置
         * @param position @~english A position in (x,y)
         * @~chinese 位置数据(x,y)
         */ 
        void setPosition(const Point& position);

        /**
         * @~english
         * Whether position percentX is enabled or not. 
         * @~chinese 
         * 是否启用percentX来计算位置。
         * @return @~english True if position percertX is enable, false otherwise.
         * @~chinese 如果启用则返回true，否则返回false。
         */
        bool isPositionPercentXEnabled()const;
        
        /**
         * @~english
         * Toggle position percentX enabled.
         * @~chinese 
         * percentX百分比定位开关。
         * @param isUsed  @~english True if enable position percentX, false otherwise.
         * @~chinese 如果传入true则开启，传入false关闭。
         */
        void setPositionPercentXEnabled(bool isUsed);

        /**
         * @~english
         * Query the position percent X value.
         * @~chinese 
         * 查询x轴的百分比定位信息
         *@return @~english Position percent X value in float.
         * @~chinese 一个百分比的x浮点值
         */
        float getPositionPercentX()const;

        /**
         * @~english
         * Change position percent X value.
         * @~chinese 
         * 改变x轴上的百分比定位值
         * @param percentMargin @~english Margin in float.
         * @~chinese 一个浮点数
         */
        void setPositionPercentX(float percentMargin);

        /**
         * @~english
         * Whether position percentY is enabled or not.
         * @~chinese 
         * 是否开启percentY，y轴的百分比定位
         * @see `setPositionPercentYEnabled`
         * @return @~english True if position percentY is enabled, false otherwise.
         * @~chinese 如果启用则返回true，否则返回false
         */
        bool isPositionPercentYEnabled()const;

        /**
         * @~english
         * Toggle position percentY enabled.
         * @~chinese 
         * y轴百分比定位percentY启用开关
         * @param isUsed @~english True if position percentY is enabled, false otherwise.
         * @~chinese 如果传入true则开启y轴的百分比定位，传入false则关闭
         */
        void setPositionPercentYEnabled(bool isUsed);

        /**
         * @~english
         * Query the position percentY Y value.
         * @~chinese 
         * 查询y轴的百分比定位值percentY
         * @return @~english Position percent Y value in float.
         * @~chinese y轴的百分比定位浮点值
         */
        float getPositionPercentY()const;

        /**
         * @~english
         * Change position percentY value.
         * @~chinese 
         * 改变y轴的百分比定位信息percentY
         * @param percentMargin @~english Margin in float.
         * @~chinese 一个浮点值
         */
        void setPositionPercentY(float percentMargin);

        /**
         * @~english
         * Query element horizontal dock type.
         * @~chinese 
         * 查询元素水平对齐的类型。
         * @return @~english Horizontal dock type.
         * @~chinese 水平对齐类型。
         */
        HorizontalEdge getHorizontalEdge()const;

        /**
         * @~english
         * Change element's horizontal dock type.
         * @~chinese 
         * 更改元素的水平对齐类型
         * @param hEage @~english Horizontal dock type @see `HorizontalEdge`
         * @~chinese 水平对齐类型
         */
        void setHorizontalEdge(HorizontalEdge hEage);

        /**
         * @~english
         * Query element vertical dock type.
         * @~chinese 
         * 查询元素垂直定位类型。
         *@return @~english Vertical dock type.
         * @~chinese 垂直定位类型。
         */
        VerticalEdge getVerticalEdge()const;

        /**
         * @~english
         * Change element's vertical dock type.
         * @~chinese 
         * 改变元素的垂直定位类型。
         * @param vEage @~english Vertical dock type @see `VerticalEdge`.
         * @~chinese 垂直定位类型
         */
        void setVerticalEdge(VerticalEdge vEage);

        /**
         * @~english
         * Query left margin of owner relative to its parent.
         * @~chinese 
         * 获取所有者的左边距
         * @return @~english Left margin in float.
         * @~chinese 左边距浮点数
         */
        float getLeftMargin()const;

        /**
         * @~english
         * Change left margin of owner relative to its parent.
         * @~chinese 
         * 设置所有者的左边距
         * @param margin @~english Margin in float.
         * @~chinese 左边距浮点数
         */
        void setLeftMargin(float margin);

        /**
         * @~english
         * Query the right margin of owner relative to its parent.
         * @~chinese 
         * 获取所有者的右边距
         * @return @~english Right margin in float.
         * @~chinese 右边距浮点数
         */
        float getRightMargin()const;

        /**
         * @~english
         * Change right margin of owner relative to its parent.
         * @~chinese 
         * 设置所有者的右边距
         * @param margin @~english Margin in float.
         * @~chinese 右边距浮点数
         */
        void setRightMargin(float margin);

        /**
         * @~english
         * Query the top margin of owner relative to its parent.
         * @~chinese 
         * 获取所有者的上边距
         * @return @~english Top margin in float.
         * @~chinese 上边距浮点数
         */
        float getTopMargin()const;

        /**
         * @~english
         * Change the top margin of owner relative to its parent.
         * @~chinese 
         * 设置所有者的上边距
         * @param margin @~english Margin in float.
         * @~chinese 上边距浮点数
         */
        void setTopMargin(float margin);

        /**
         * @~english
         * Query the bottom margin of owner relative to its parent.
         * @~chinese 
         * 获取所有者的下边距
         * @return @~english Bottom margin in float.
         * @~chinese 下边距浮点数
         */
        float getBottomMargin()const;

        /**
         * @~english
         * Change the bottom margin of owner relative to its parent.
         * @~chinese 
         * 设置所有者的下边距
         * @param margin @~english in float.
         * @~chinese 下边距浮点数
         */
        void setBottomMargin(float margin);

        /**
         * @~english
         * Query owner's content size.
         * @~chinese 
         * 获取所有者内容的尺寸
         * @return @~english Owner's content size.
         * @~chinese 所有者的内容尺寸
         */
        const Size& getSize()const;

        /**
         * @~english
         * Change the content size of owner.
         * @~chinese 
         * 更改所有者的内容尺寸
         * @param size @~english Content size in @see `Size`.
         * @~chinese 内容尺寸
         */
        void setSize(const Size& size);

        /**
         * @~english
         * Query whether percent width is enabled or not.
         * @~chinese 
         * 查询是否启用了百分比控制宽度
         * @return @~english True if percent width is enabled, false, otherwise.
         * @~chinese 如果启用则返回true，否则返回false
         */
        bool isPercentWidthEnabled()const;

        /**
         * @~english
         * Toggle enable percent width.
         * @~chinese 
         * 百分比控制宽度的开关
         * @param isUsed @~english True if percent width is enabled, false otherwise.
         * @~chinese 如果传入true则开启百分比控制宽度，传入false则为关闭
         */
        void setPercentWidthEnabled(bool isUsed);

        /**
         * @~english
         * Query content size width of owner.
         * @~chinese 
         * 查询所有者的内容宽度。
         * @return @~english Content size width in float.
         * @~chinese 内容宽度浮点数。
         */
        float getSizeWidth()const;

        /**
         * @~english
         * Change content size width of owner.
         * @~chinese 
         * 设置所有者的内容宽度
         * @param width @~english Content size width in float.
         * @~chinese 内容宽度浮点数
         */
        void setSizeWidth(float width);

        /**
         * @~english
         * Query percent width of owner.
         * @~chinese 
         * 查询所有者的百分比宽度。
         * @return @~english percent width in float.
         * @~chinese 百分比宽度浮点数。
         */
        float getPercentWidth()const;

        /**
         * @~english
         * Change percent width of owner.
         * @~chinese 
         * 设置所有者的百分比宽度
         * @param percentWidth @~english Percent Width in float.
         * @~chinese 百分比宽度浮点数
         */
        void setPercentWidth(float percentWidth);

        /**
         * @~english
         * Query whether percent height is enabled or not.
         * @~chinese 
         * 查询是否启用百分比控制高度
         * @return @~english True if percent height is enabled, false otherwise.
         * @~chinese 如果启用则返回true，否则返回false
         */
        bool isPercentHeightEnabled()const;

        /**
         * @~english
         * Toggle enable percent height.
         * @~chinese 
         * 百分比控制高度的开关
         * @param isUsed @~english True if percent height is enabled, false otherwise.
         * @~chinese 传入true则开启百分比控制高度，否则为关闭
         */
        void setPercentHeightEnabled(bool isUsed);

        /**
         * @~english
         * Query size height of owner.
         * @~chinese 
         * 查询所有者的高度大小
         * @return @~english Size height in float.
         * @~chinese 高度浮点数
         */
        float getSizeHeight()const;

        /**
         * @~english
         * Change size height of owner.
         * @~chinese 
         * 改变所有者的高度
         * @param height @~english Size height in float.
         * @~chinese 高度(浮点数)
         */
        void setSizeHeight(float height);

        /**
         * @~english
         * Query percent height of owner.
         * @~chinese 
         * 获取所有者的百分比高度
         * @return @~english Percent height in float.
         * @~chinese 高度百分比(浮点数)
         */
        float getPercentHeight()const;

        /**
         * @~english
         * Change percent height value of owner.
         * @~chinese 
         * 设置高度百分比
         * @param percentHeight @~english Percent height in float.
         * @~chinese 高度百分比(浮点数)
         */
        void setPercentHeight(float percentHeight);

        /**
         * @~english
         * Query whether stretch width is enabled or not.
         * @~chinese 
         * 查询是否启用自动伸缩宽度。
         * @return @~english True if stretch width is enabled, false otherwise.
         * @~chinese 如果启用了则返回true，否则返回false
         */
        bool isStretchWidthEnabled()const;

        /**
         * @~english
         * Toggle enable stretch width.
         * @~chinese 
         * 启用关闭自动伸缩宽度的开关
         * @param isUsed @~english True if enable stretch width, false otherwise.
         * @~chinese 如果传入true则开启，传入false则关闭
         */
        void setStretchWidthEnabled(bool isUsed);

        /**
         * @~english
         * Query whether stretch height is enabled or not.
         * @~chinese 
         * 查询是否启用自动伸缩高度
         * @return @~english True if stretch height is enabled, false otherwise.
         * @~chinese 如果启用了则返回true，否则返回false
         */
        bool isStretchHeightEnabled()const;

        /**
         * @~english
         * Toggle enable stretch height.
         * @~chinese 
         * 启用关闭自动伸缩高度的开关
         * @param isUsed @~english True if stretch height is enabled, false otherwise.
         * @~chinese 如果传入true则开启，传入false则关闭
         */
        void setStretchHeightEnabled(bool isUsed);
        
        /**
         * @~english
         * Toggle enable percent only.
         * @~chinese 
         * 仅仅使用百分比的开关
         * @param enable @~english True if percent only is enabled, false otherwise.
         * @~chinese 传入true则仅使用百分比数据，false则可使用点数据
         */
        void setPercentOnlyEnabled(bool enable);

        /**
         * @~english
         * Toggle active enabled of LayoutComponent's owner.
         * @~chinese 
         * LayoutComponent所有者是否激活的开关
         * @param enable @~english True if active layout component, false otherwise.
         * @~chinese 如果传入true则激活，否则关闭
         */
        void setActiveEnabled(bool enable);

        /**
         * @~english
         * Refresh layout of the owner.
         * @~chinese 
         * 刷新所有者的布局信息。
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
