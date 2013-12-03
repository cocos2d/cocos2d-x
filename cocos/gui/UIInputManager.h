/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __UIINPUTMANAGER_H__
#define __UIINPUTMANAGER_H__

#include "cocos2d.h"
#include "gui/UILayout.h"

namespace gui {
/**
 *  @js NA
 *  @lua NA
 */
class UIInputManager
{
public:
    /**
     * Default constructor
     */
    UIInputManager();
    
    /**
     * Default destructor
     */
    virtual ~UIInputManager();
    
    /**
     * Regist a widget to input manager.
     *
     * @param widget    registed widget can be touched.
     */
    void registWidget(UIWidget* widget);
        
    /**
     * Remove a registed widget from input manager.
     *
     * @param widget    widget which will be removed.
     */
    void removeManageredWidget(UIWidget* widget);
    
    /**
     * Finds a widget which is selected and call it's "onTouchBegan" method.
     *
     * @param touch point.
     *
     * @return true that find a widget selected, false otherwise.
     */
    bool checkEventWidget(const cocos2d::Point &touchPoint);
    
    
    void update(float dt);
    bool onTouchBegan(cocos2d::Touch* touch);
    void onTouchMoved(cocos2d::Touch* touch);
    void onTouchEnd(cocos2d::Touch* touch);
    void onTouchCancelled(cocos2d::Touch* touch);
    
    void setRootWidget(UIWidget* root);
    UIWidget* getRootWidget();
    void addCheckedDoubleClickWidget(UIWidget* widget);
protected:
    bool checkTouchEvent(UIWidget* root, const cocos2d::Point& touchPoint);
protected:
    cocos2d::Array* _manageredWidget;
    cocos2d::Array* _selectedWidgets;
    cocos2d::Point _touchBeganedPoint;
    cocos2d::Point _touchMovedPoint;
    cocos2d::Point _touchEndedPoint;
    cocos2d::Point _touchCanceledPoint;
    bool _touchDown;
    float _longClickTime;
    float _longClickRecordTime;
    cocos2d::Array* _checkedDoubleClickWidget;
    UIWidget* _rootWidget;
};

}

#endif /* defined(__CocoGUI__UIInputManager__) */
