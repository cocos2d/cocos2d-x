/****************************************************************************
Copyright (c) 2015 Neo Kim (neo.kim@neofect.com)

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

#ifndef __UISCROLLVIEWBAR_H__
#define __UISCROLLVIEWBAR_H__

#include "ui/UIScrollView.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

class Sprite;

namespace ui {

/**@~english
 * Scroll bar being attached to ScrollView layout container.
 * @~chinese 
 * 添加到ScrollView布局容器的滚动条。
 */
class CC_GUI_DLL ScrollViewBar : public ProtectedNode
{

public:
    /**@~english
     * Default constructor
     * @~chinese 
     * 默认构造函数
     * @js ctor
     * @lua new
     */
    ScrollViewBar(ScrollView* parent, ScrollView::Direction direction);
    
    /**@~english
     * Default destructor
     * @~chinese 
     * 默认的析构函数
     * @js NA
     * @lua NA
     */
    virtual ~ScrollViewBar();
    
    /**@~english
     * Create a ScrollViewBar with its parent ScrollView and direction.
     * @~chinese 
     * 通过一个ScrollView及其滚动方向创建一个ScrollViewBar
     * @return @~english A ScrollViewBar instance.
     * @~chinese 一个ScrollViewBar实例。
     */
    static ScrollViewBar* create(ScrollView* parent, ScrollView::Direction direction);
    
    /**
     * @brief @~english Set the scroll bar position from the left-bottom corner (horizontal) or right-top corner (vertical).
     *
     * @~chinese 设置滚动条的位置, 按照偏移水平方向左下角或垂直方向右上角的距离来设置
     * 
     * @param positionFromCorner @~english The position from the left-bottom corner (horizontal) or right-top corner (vertical).
     * @~chinese 偏移水平方向左下角或垂直方向右上角的距离
     */
    void setPositionFromCorner(const Vec2& positionFromCorner);
    
    /**
     * @brief @~english Get the scroll bar position from the left-bottom corner (horizontal) or right-top corner (vertical).
     *
     * @~chinese 获取偏移水平方向左下角或垂直方向右上角的距离
     * 
     * @return @~english A Vec2 struct.
     * @~chinese 一个点坐标.
     */
    Vec2 getPositionFromCorner() const;
    
    /**
     * @brief @~english Set the scroll bar's width
     *
     * @~chinese 设置滚动条的宽度
     * 
     * @param width @~english The scroll bar's width
     * @~chinese 滚动条的宽度
     */
    void setWidth(float width);
    
    /**
     * @brief @~english Get the scroll bar's width
     *
     * @~chinese 获取滚动条的宽度
     * 
     * @return @~english the scroll bar's width
     * @~chinese 滚动条的宽度
     */
    float getWidth() const;
    
    /**
     * @brief @~english Set scroll bar auto hide state
     *
     * @~chinese 设置滚动条自动隐藏状态
     * 
     * @param scroll @~english bar auto hide state
     * @~chinese 是否自动隐藏状态栏
     */
    void setAutoHideEnabled(bool autoHideEnabled);
    
    /**
     * @brief @~english Query scroll bar auto hide state
     *
     * @~chinese 查询滚动条自动隐藏状态
     * 
     * @return @~english True if scroll bar auto hide is enabled, false otherwise.
     * @~chinese 如果启用了滚动条自动隐藏,则返回真,否则返回假。
     */
    bool isAutoHideEnabled() const { return _autoHideEnabled; }
    
    /**
     * @brief @~english Set scroll bar auto hide time
     *
     * @~chinese 设置滚动条自动隐藏时间
     * 
     * @param scroll @~english bar auto hide time
     * @~chinese 滚动条自动隐藏的时间
     */
    void setAutoHideTime(float autoHideTime) { _autoHideTime = autoHideTime; }
    
    /**
     * @brief @~english Get the scroll bar's auto hide time
     *
     * @~chinese 获取滚动条的自动隐藏时间
     * 
     * @return @~english the scroll bar's auto hide time
     * @~chinese 滚动条的自动隐藏时间
     */
    float getAutoHideTime() const { return _autoHideTime; }
    
    /**
     * @brief @~english This is called by parent ScrollView when the parent is scrolled. Don't call this directly.
     *
     * @~chinese 当ScrollView滚动的时候会调用此方法来更新滚动条。开发者不需要直接调用这个。
     * 
     * @param amount @~english how much the inner container of ScrollView is out of boundary
     * @~chinese ScrollView的内部容器的超出了多少边界
     */
    virtual void onScrolled(const Vec2& outOfBoundary);
    
    /**
     * @lua NA
     */
    virtual void setOpacity(GLubyte opacity) override { _opacity = opacity; }
    virtual GLubyte getOpacity() const override { return _opacity; }
    virtual void onEnter() override;
    virtual void update(float deltaTime) override;
    
    /**
     * @brief @~english This is called by parent ScrollView when a touch is began. Don't call this directly.
     * @~chinese 当ScrollView的触摸事情开始的时候会调用此方法。开发者不需要直接调用这个。
     */
    void onTouchBegan();
    
    /**
     * @brief @~english This is called by parent ScrollView when a touch is ended. Don't call this directly.
     * @~chinese 当ScrollView的触摸事件结束的时候会调用此方法。开发者不需要直接调用这个。
     */
    void onTouchEnded();
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
private:
    float calculateLength(float innerContainerMeasure, float scrollViewMeasure, float outOfBoundaryValue);
    Vec2 calculatePosition(float innerContainerMeasure, float scrollViewMeasure, float innerContainerPosition, float outOfBoundaryValue, float actualLength);
    
    void updateLength(float length);
    void processAutoHide(float deltaTime);
    
    ScrollView* _parent;
    ScrollView::Direction _direction;
	
    Sprite* _upperHalfCircle;
    Sprite* _lowerHalfCircle;
    Sprite* _body;
    
    GLubyte _opacity;
	
    float _marginFromBoundary;
    float _marginForLength;

    bool _touching;
    
    bool _autoHideEnabled;
    float _autoHideTime;
    float _autoHideRemainingTime;
    
};

}
// end of ui group
/// @}
NS_CC_END

#endif /* defined(__UISCROLLVIEWBAR_H__) */
