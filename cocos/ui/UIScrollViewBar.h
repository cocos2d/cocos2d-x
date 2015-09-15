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

/**
 * Scroll bar being attached to ScrollView layout container.
 */
class CC_GUI_DLL ScrollViewBar : public ProtectedNode
{

public:
    /**
     * Default constructor
     * @js ctor
     * @lua new
     */
    ScrollViewBar(ScrollView* parent, ScrollView::Direction direction);
    
    /**
     * Default destructor
     * @js NA
     * @lua NA
     */
    virtual ~ScrollViewBar();
    
    /**
     * Create a ScrollView with its parent ScrollView and direction.
     * @return A ScrollViewBar instance.
     */
    static ScrollViewBar* create(ScrollView* parent, ScrollView::Direction direction);
    
    /**
     * @brief Set the scroll bar position from the left-bottom corner (horizontal) or right-top corner (vertical).
     *
     * @param positionFromCorner The position from the left-bottom corner (horizontal) or right-top corner (vertical).
     */
    void setPositionFromCorner(const Vec2& positionFromCorner);
    
    /**
     * @brief Get the scroll bar position from the left-bottom corner (horizontal) or right-top corner (vertical).
     *
     * @return positionFromCorner
     */
    Vec2 getPositionFromCorner() const;
    
    /**
     * @brief Set the scroll bar's width
     *
     * @param width The scroll bar's width
     */
    void setWidth(float width);
    
    /**
     * @brief Get the scroll bar's width
     *
     * @return the scroll bar's width
     */
    float getWidth() const;
    
    /**
     * @brief Set scroll bar auto hide state
     *
     * @param scroll bar auto hide state
     */
    void setAutoHideEnabled(bool autoHideEnabled);
    
    /**
     * @brief Query scroll bar auto hide state
     *
     * @return True if scroll bar auto hide is enabled, false otherwise.
     */
    bool isAutoHideEnabled() const { return _autoHideEnabled; }
    
    /**
     * @brief Set scroll bar auto hide time
     *
     * @param scroll bar auto hide time
     */
    void setAutoHideTime(float autoHideTime) { _autoHideTime = autoHideTime; }
    
    /**
     * @brief Get the scroll bar's auto hide time
     *
     * @return the scroll bar's auto hide time
     */
    float getAutoHideTime() const { return _autoHideTime; }
    
    /**
     * @brief This is called by parent ScrollView when the parent is scrolled. Don't call this directly.
     *
     * @param amount how much the inner container of ScrollView is out of boundary
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
     * @brief This is called by parent ScrollView when a touch is began. Don't call this directly.
     */
    void onTouchBegan();
    
    /**
     * @brief This is called by parent ScrollView when a touch is ended. Don't call this directly.
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
