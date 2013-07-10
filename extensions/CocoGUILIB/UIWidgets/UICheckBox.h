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

#ifndef __UICHECKBOX_H__
#define __UICHECKBOX_H__

#include "../BaseClasses/UIWidget.h"

NS_CC_EXT_BEGIN

typedef void (cocos2d::CCObject::*SEL_SelectEvent)(cocos2d::CCObject*);
typedef void (cocos2d::CCObject::*SEL_UnSelectEvent)(cocos2d::CCObject*);
#define coco_selectselector(_SELECTOR) (cocos2d::extension::SEL_SelectEvent)(&_SELECTOR)
#define coco_unselectselector(_SELECTOR) (cocos2d::extension::SEL_UnSelectEvent)(&_SELECTOR)
class UICheckBox : public UIWidget
{
public:
    UICheckBox();
    virtual ~UICheckBox();
    static UICheckBox* create();
    void setTextures(const char* backGround,const char* backGroundSelected,const char* cross,const char* backGroundDisabled,const char* frontCrossDisabled,bool useSpriteFrame = false);
    void setBackGroundTexture(const char* backGround,bool useSpriteFrame = false);
    void setBackGroundSelectedTexture(const char* backGroundSelected,bool useSpriteFrame = false);
    void setFrontCrossTexture(const char* cross,bool useSpriteFrame = false);
    void setBackGroundDisabledTexture(const char* backGroundDisabled,bool useSpriteFrame = false);
    void setFrontCrossDisabledTexture(const char* frontCrossDisabled,bool useSpriteFrame = false);
    void setSelectedState(bool selected);
    bool getSelectedState();
    virtual cocos2d::CCNode* getValidNode();
    virtual void setAnchorPoint(const cocos2d::CCPoint &pt);
    virtual void addSelectEvent(cocos2d::CCObject* target,SEL_SelectEvent selector);
    virtual void addUnSelectEvent(cocos2d::CCObject* target,SEL_UnSelectEvent selector);
    virtual void setFlipX(bool flipX);
    virtual void setFlipY(bool flipY);
    virtual bool isFlipX();
    virtual bool isFlipY();
    virtual void onTouchEnded(cocos2d::CCPoint &touchPoint);
protected:
    virtual bool init();
    virtual void initNodes();
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();
    void selectedEvent();
    void unSelectedEvent();
protected:
    cocos2d::CCSprite* m_pBackGroundBox;
    cocos2d::CCSprite* m_pBackGroundSelectedBox;
    cocos2d::CCSprite* m_pFrontCross;
    cocos2d::CCSprite* m_pBackGroundBoxDisabled;
    cocos2d::CCSprite* m_pFrontCrossDisabled;
    bool m_bIsSelected;
    cocos2d::CCObject*       m_pSelectListener;
    SEL_SelectEvent    m_pfnSelectSelector;
    cocos2d::CCObject*       m_pUnSelectListener;
    SEL_UnSelectEvent    m_pfnUnSelectSelector;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UICheckBox__) */
