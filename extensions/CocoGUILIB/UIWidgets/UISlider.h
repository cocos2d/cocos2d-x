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

typedef void (CCObject::*SEL_PercentChangedEvent)(CCObject*);
#define coco_percentchangedselector(_SELECTOR) (SEL_PercentChangedEvent)(&_SELECTOR)
class UISlider : public UIWidget
{
public:
    UISlider();
    virtual ~UISlider();
    static UISlider* create();
    void setBarTexture(const char* fileName,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setScale9Enable(bool able);
    void setCapInsets(const CCRect &capInsets);
    void setScale9Size(const CCSize &size);
    void setSlidBallTextures(const char* normal,const char* pressed,const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setSlidBallNormalTexture(const char* normal,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setSlidBallPressedTexture(const char* pressed,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setSlidBallDisabledTexture(const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setBarLength(float length);
    bool isProgressBarVisible();
    void setProgressBarVisible(bool show);
    void setProgressBarTexture(const char* fileName, TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setProgressBarScale();
    void setSlidBallPercent(int percent);
    virtual bool pointAtSelfBody(const CCPoint &pt);
    virtual CCNode* getValidNode();
    virtual void addPercentChangedEvent(CCObject* target,SEL_PushEvent selector);
    int getPercent();
    virtual void onTouchBegan(const CCPoint &touchPoint);
    virtual void onTouchMoved(const CCPoint &touchPoint);
    virtual void onTouchEnded(const CCPoint &touchPoint);
    virtual void onTouchCancelled(const CCPoint &touchPoint);
    
protected:
    virtual bool init();
    int getClickPercent(float location);
    void checkSlidBoundary();
    float getPercentWithBallPos(float px,float py);
    void percentChangedEvent();
protected:
    CCNode*  m_pBarNode;
    float m_fMinLength;
    float m_fBarLength;
    int m_nDirection;
    int m_nBarPercent;
    UIButton* m_pSlidBall;
    float m_fBarNodeScaleValue;
    float m_fTouchMoveStartLocation;
    bool m_bBarScale9Enable;
    std::string m_strTextureFile;
    CCRect m_capInsets;
    CCSize m_scale9Size;
    bool m_bProgressBarVisible;
    CCNode* m_pProgressBarNode;
    std::string m_strProgressTextureFile;
    CCObject*       m_pPercentListener;
    SEL_PushEvent    m_pfnPercentSelector;
    TextureResType m_eBarTexType;
    TextureResType m_eBarTexS9Type;
    TextureResType m_eBallNTexType;
    TextureResType m_eBallPTexType;
    TextureResType m_eBallDTexType;
	TextureResType m_eProgressBarTexType;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UISlider__) */
