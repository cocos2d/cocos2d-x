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
#include "../BaseClasses/UIWidget.h"

NS_CC_BEGIN

namespace ui {

/**
 *  @lua NA
 */
class TouchGroup : public CCLayer
{
    
public:
    /**
     * Default constructor
     * @js ctor
     */
    TouchGroup();
    
    /**
     * Default destructor
     * @js NA
     */
    virtual ~TouchGroup();
    
    /**
     * Allocates and initializes a widget.
     */
    static TouchGroup *create(void);
    
    //initializes state of uilayer.
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    /**
     * Add a widget to UILayer, for drawing.
     *
     * @param widget.
     */
    void addWidget(Widget* widget);
    
    /**
     * Remove a widget from UILayer.
     *
     * @param widget.
     *
     * @param cleanup true if all running actions on all children widgets should be cleanup, false otherwise.
     */
    void removeWidget(Widget* widget);
    
    /**
     * Finds a widget whose tag is equal tag param from widget tree.
     *
     * @param tag.
     */
    Widget* getWidgetByTag(int tag);
    
    /**
     * Seek a widget whose name is equal name param from widget tree.
     *
     * @param name.
     */
    Widget* getWidgetByName(const char* name);
    
    /**
     * Remove and clean up all of UILayer's widget.
     */
    virtual void clear();
    
    /**
     * Gets root widget of UILayer.
     *
     * @return UIRootWidget, "UIRootWidget" is the root widget of UILayer.
     */
    Widget* getRootWidget();
protected:
    bool checkEventWidget(CCTouch* touch, CCEvent *pEvent);
    bool checkTouchEvent(Widget* root, CCTouch* touch, CCEvent* pEvent);
protected:
    Widget* m_pRootWidget;
    CCPoint touchBeganedPoint;
    CCPoint touchMovedPoint;
    CCPoint touchEndedPoint;
    CCPoint touchCanceledPoint;
    CCArray* m_pSelectedWidgets;
};
    
}

NS_CC_END



#endif /* defined(__UILAYER_H__) */
