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

/**
 *  @js NA
 *  @lua NA
 */
class UILayer : public CCLayer
{
    
public:
    /**
     * Default constructor
     */
    UILayer();
    
    /**
     * Default destructor
     */
    virtual ~UILayer();
    
    /**
     * Allocates and initializes a widget.
     */
    static UILayer *create(void);
    
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
    void addWidget(UIWidget* widget);
    
    /**
     * Remove a widget from UILayer.
     *
     * @param widget.
     *
     * @param cleanup true if all running actions on all children widgets should be cleanup, false otherwise.
     */
    void removeWidget(UIWidget* widget);
    
    /**
     * Sets whether the UILayer is visible
     *
     * The default value is true, a UILayer is default to visible
     *
     * @param visible   true if the UILayer is visible, false if the UILayer is hidden.
     */
    virtual void setVisible(bool visible);
    
    /**
     * Finds a widget whose tag is equal tag param from widget tree.
     *
     * @param tag.
     */
    UIWidget* getWidgetByTag(int tag);
    
    /**
     * Seek a widget whose name is equal name param from widget tree.
     *
     * @param name.
     */
    UIWidget* getWidgetByName(const char* name);
    
    /**
     * Gets UIInputManager.
     *
     * UIInputManager is the touch manager of UILayer.
     *
     * @return UIInputManager.
     */
    UIInputManager* getInputManager();
    
    /**
     * Remove and clean up all of UILayer's widget.
     */
    virtual void clear();
    
    /**
     * Gets root widget of UILayer.
     *
     * @return UIRootWidget, "UIRootWidget" is the root widget of UILayer.
     */
    UIRootWidget* getRootWidget();
    
    /*compatible*/
    /**
     * These methods will be removed
     */
    virtual void dispose(){removeFromParentAndCleanup(true);};
    void removeWidgetAndCleanUp(UIWidget* widget,bool cleanup){removeWidget(widget);};
    /************/
protected:
    UIRootWidget* m_pRootWidget;
    UIInputManager* m_pInputManager;
};

NS_CC_EXT_END



#endif /* defined(__UILAYER_H__) */
