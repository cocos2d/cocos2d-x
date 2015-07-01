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

class CC_GUI_DLL ScrollViewBar : public ProtectedNode
{

public:
    ScrollViewBar(ScrollView* parent, ScrollView::Direction direction);
    
    virtual ~ScrollViewBar();
    
    static ScrollViewBar* create(ScrollView* parent, ScrollView::Direction direction);
    
    void setMargin(float margin);
    float getMargin() const;
    
    void setAutoHideEnabled(bool autoHideEnabled);
    bool isAutoHideEnabled() const;
    
    virtual void onScrolled(const Vec2& outOfBoundary);
    
    virtual void onEnter() override;
    virtual void update(float deltaTime) override;
    
    void onTouchBegan();
    void onTouchEnded();
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
private:
    float updateLength(float innerContainerMeasure, float scrollViewMeasure, float outOfBoundaryValue);
    void updatePosition(float innerContainerMeasure, float scrollViewMeasure, float innerContainerPosition, float outOfBoundaryValue, float actualLength);
    
    void setLength(float length);
    
    ScrollView* _parent;
    ScrollView::Direction _direction;
    Sprite* _upperHalfCircle;
    Sprite* _lowerHalfCircle;
    Sprite* _body;
    float _margin;
    
    bool _touching;
    
    bool _autoHideEnabled;
    float _autoHideRemainingTime;
	
};

}
// end of ui group
/// @}
NS_CC_END

#endif /* defined(__UISCROLLVIEWBAR_H__) */
