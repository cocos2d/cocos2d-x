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

#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#include "UIButton.h"

NS_CC_EXT_BEGIN

typedef void (cocos2d::CCObject::*SEL_PercentChangedEvent)(cocos2d::CCObject*);
#define coco_percentchangedselector(_SELECTOR) (cs::SEL_PercentChangedEvent)(&_SELECTOR)
class UISlider : public UIWidget
{
public:
    UISlider();
    virtual ~UISlider();
    static UISlider* create();
    void setBarTexture(const char* fileName,bool useSpriteFrame = false);
    void setBarTextureScale9(const char* fileName,float x,float y,float width,float height,bool useSpriteFrame = false);
    void setBarTextureScale9Enable(bool able);
    void setSlidBallTextures(const char* normal,const char* pressed,const char* disabled,bool useSpriteFrame = false);
    void setSlidBallNormalTexture(const char* normal,bool useSpriteFrame = false);
    void setSlidBallPressedTexture(const char* pressed,bool useSpriteFrame = false);
    void setSlidBallDisabledTexture(const char* disabled,bool useSpriteFrame = false);
    void setBarLength(float length);
    void setShowProgressBar(bool show);
    void setProgressBarTextureScale9(const char* fileName,float x,float y,float width,float height,bool useSpriteFrame = false);
    void setProgressBarScale(int percent);
    void setSlidBallPercent(int percent);
    virtual bool pointAtSelfBody(cocos2d::CCPoint &pt);
    virtual cocos2d::CCNode* getValidNode();
    virtual void addPercentChangedEvent(cocos2d::CCObject* target,SEL_PushEvent selector);
    int getPercent();
    virtual void onTouchBegan(cocos2d::CCPoint &touchPoint);
    virtual void onTouchMoved(cocos2d::CCPoint &touchPoint);
    virtual void onTouchEnded(cocos2d::CCPoint &touchPoint);
    virtual void onTouchCancelled(cocos2d::CCPoint &touchPoint);
protected:
    virtual bool init();
    int getClickPercent(float location);
    void checkSlidBoundary();
    float getPercentWithBallPos(float px,float py);
    void percentChangedEvent();
protected:
    cocos2d::CCNode*  m_pBarNode;
    float m_fMinLength;
    float m_fBarLength;
    int m_nDirection;
    int m_nBarPercent;
    UIButton* m_pSlidBall;
    float m_fBarNodeScaleValue;
    float m_fTouchMoveStartLocation;
    bool m_bBarScale9Enable;
    bool m_bShowProgressBar;
    cocos2d::CCNode* m_pProgressBarNode;
    cocos2d::CCObject*       m_pPercentListener;
    SEL_PushEvent    m_pfnPercentSelector;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UISlider__) */
