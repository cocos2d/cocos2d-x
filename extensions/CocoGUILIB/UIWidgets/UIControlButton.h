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

#ifndef __UICONTROLBUTTON_H__
#define __UICONTROLBUTTON_H__

#include "cocos2d.h"
#include "../../GUI/CCControlExtension/CCScale9Sprite.h"
#include "../BaseClasses/UIWidget.h"


NS_CC_EXT_BEGIN

class UIControlButton : public UIWidget
{
public:
    UIControlButton();
    virtual ~UIControlButton();
    static UIControlButton* create();
    void setTextures(const char* backgroundNormal,const char* backgroundPressed,const char* backgroundDisabled);
    void setTitle(const char* titleNormal,const char* titlePressed,const char* titleDisabled);
    virtual cocos2d::CCNode* getValidNode();
    virtual void setAnchorPoint(const cocos2d::CCPoint &pt);
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
    void setNormalFontColor(const cocos2d::ccColor3B& color);
    void setPressedFontColor(const cocos2d::ccColor3B& color);
    void setDisalbedFontColor(const cocos2d::ccColor3B& color);
    void setLabelAnchorPoint(const cocos2d::CCPoint& labelAnchorPoint);
    void setPreferredSize(const cocos2d::CCSize& size);
    void setNormalBackgroundSpriteFrame(cocos2d::CCSpriteFrame * spriteFrame);
    void setPressedBackgroundSpriteFrame(cocos2d::CCSpriteFrame * spriteFrame);
    void setDisabledBackgroundSpriteFrame(cocos2d::CCSpriteFrame * spriteFrame);
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
    cocos2d::extension::CCScale9Sprite* m_pNormalBackGround;
    cocos2d::extension::CCScale9Sprite* m_pPressedBackGround;
    cocos2d::extension::CCScale9Sprite* m_pDisabledBackGround;
    cocos2d::CCLabelTTF* m_pNormalTitle;
    cocos2d::CCLabelTTF* m_pPressedTitle;
    cocos2d::CCLabelTTF* m_pDisabledTitle;
    cocos2d::CCSize m_preferredSize;        
};

NS_CC_EXT_END


#endif /* defined(__Test__UIControlButton__) */
