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
#include "../BaseClasses/UIWidget.h"

NS_CC_EXT_BEGIN

class UIInputManager
{
public:
    UIInputManager();
    ~UIInputManager();
    void registWidget(UIWidget* widget);
    void uiSceneHasChanged();
    void sortWidgets(UIWidget* widget);
    void sortRootWidgets(UIWidget* root);
    void removeManageredWidget(UIWidget* widget);
    UIWidget* checkEventWidget(const CCPoint &touchPoint);
    void addCheckedDoubleClickWidget(UIWidget* widget);
    void update(float dt);
    bool onTouchBegan(CCTouch* touch);
    bool onTouchMoved(CCTouch* touch);
    bool onTouchEnd(CCTouch* touch);
    bool onTouchCancelled(CCTouch* touch);
    
    void setRootWidget(UIWidget* root);
    UIWidget* getRootWidget();
    
protected:
    CCArray* m_manageredWidget;
    UIWidget* m_pCurSelectedWidget;
    CCPoint touchBeganedPoint;
    CCPoint touchMovedPoint;
    CCPoint touchEndedPoint;
    CCPoint touchCanceledPoint;
    bool m_bWidgetBeSorted;
    bool m_bTouchDown;
    float m_fLongClickTime;
    float m_fLongClickRecordTime;
    CCArray* checkedDoubleClickWidget;
    UIWidget* m_pRootWidget;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UIInputManager__) */
