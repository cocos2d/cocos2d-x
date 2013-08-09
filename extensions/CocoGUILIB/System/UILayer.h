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


#ifndef __UILAYER_H__
#define __UILAYER_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "../BaseClasses/UIRootWidget.h"
#include "../System/UIInputManager.h"

NS_CC_EXT_BEGIN

//typedef enum
//{
//    UILAYER_SCENE,
//    UILAYER_MODEL
//}GUITYPE;


class UILayer : public CCLayer
{
    
public:
    UILayer();
    virtual ~UILayer();
    virtual bool init();
    
    static UILayer *create(void);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    
    void addWidget(UIWidget* widget);
    void removeWidgetAndCleanUp(UIWidget* widget,bool cleanup);
    virtual void setVisible(bool visible);
    void update(float dt);
    void addUpdateEnableWidget(UIWidget* widget);
    void removeUpdateEnableWidget(UIWidget* widget);
    UIWidget* getWidgetByTag(int tag);
    UIWidget* getWidgetByName(const char* name);
    UIInputManager* getInputManager();
    virtual void clear();
    virtual void dispose();
    UIRootWidget* getRootWidget();
    
//    void setUIType(GUITYPE type);
    
protected:

//    GUITYPE m_UIType;
    UIRootWidget* m_pRootWidget;
    UIInputManager* m_pInputManager;
    CCArray* m_updateEnableWidget;
};

NS_CC_EXT_END



#endif /* defined(__UILAYER_H__) */
