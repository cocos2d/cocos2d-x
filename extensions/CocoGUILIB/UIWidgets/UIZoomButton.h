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

#ifndef __UIZOOMBUTTON_H__
#define __UIZOOMBUTTON_H__

#include "cocos2d.h"
#include "../../GUI/CCControlExtension/CCScale9Sprite.h"
#include "../BaseClasses/UIWidget.h"


NS_CC_EXT_BEGIN

class UIZoomButton : public UIWidget
{
public:
    UIZoomButton();
    virtual ~UIZoomButton();
    static UIZoomButton* create();
    void setTextures(const char* backgroundNormal,const char* backgroundPressed,const char* backgroundDisabled);
    void setTitle(const char* titleNormal,const char* titlePressed,const char* titleDisabled);
    virtual CCNode* getValidNode();
    virtual void setAnchorPoint(const CCPoint &pt);
    virtual void setFlipX(bool flipX);
    virtual void setFlipY(bool flipY);
    virtual bool isFlipX();
    virtual bool isFlipY();
    void setNormalTitle(const char* title);
    void setPressedTitle(const char* title);
    void setDisabledTitle(const char* title);
    void setNormalFontName(const char* name);
    void setPressedFontName(const char* name);
    void setDisabledFontName(const char* name);
    void setNormalFontSize(float size);
    void setPressedFontSize(float size);
    void setDisabledFontSize(float size);
    void setNormalFontColor(const ccColor3B& color);
    void setPressedFontColor(const ccColor3B& color);
    void setDisalbedFontColor(const ccColor3B& color);
    void setLabelAnchorPoint(const CCPoint& labelAnchorPoint);
    void setPreferredSize(const CCSize& size);
    void setNormalBackgroundSpriteFrame(CCSpriteFrame * spriteFrame);
    void setPressedBackgroundSpriteFrame(CCSpriteFrame * spriteFrame);
    void setDisabledBackgroundSpriteFrame(CCSpriteFrame * spriteFrame);
    void setZoomOnTouchDown(bool zoom);
    bool getZoomOnTouchDown();
protected:
    virtual bool init();
    virtual void initNodes();
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();
    bool m_bZoomOnTouchDown;
protected:
    CCScale9Sprite* m_pNormalBackGround;
    CCScale9Sprite* m_pPressedBackGround;
    CCScale9Sprite* m_pDisabledBackGround;
    CCLabelTTF* m_pNormalTitle;
    CCLabelTTF* m_pPressedTitle;
    CCLabelTTF* m_pDisabledTitle;
    CCSize m_preferredSize;        
};

NS_CC_EXT_END


#endif /* defined(__Test__UIZoomButton__) */
