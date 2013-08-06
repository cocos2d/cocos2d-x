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

#ifndef __UIBUTTON_H__
#define __UIBUTTON_H__

#include "../BaseClasses/UIWidget.h"

NS_CC_EXT_BEGIN

class UIButton : public UIWidget
{
public:
    UIButton();
    virtual ~UIButton();
    static UIButton* create();
    virtual void initPressState(WidgetState state);
    virtual void setTextures(const char* normal,const char* selected,const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setNormalTexture(const char* normal, TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setPressedTexture(const char* selected, TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setDisabledTexture(const char* disabled, TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setCapInsets(const CCRect &capInsets);
    virtual CCNode* getValidNode();
    virtual void setAnchorPoint(const CCPoint &pt);
    virtual void setScale9Enable(bool able);
    virtual void setScale9Size(const CCSize &size);
    virtual void setFlipX(bool flipX);
    virtual void setFlipY(bool flipY);
    virtual bool isFlipX();
    virtual bool isFlipY();
    virtual void setNormalSpriteFrame(CCSpriteFrame* frame);
    virtual void setPressedSpriteFrame(CCSpriteFrame* frame);
    virtual void setDisabledSpriteFrame(CCSpriteFrame* frame);
protected:
    virtual bool init();
    virtual void initNodes();
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();
protected:
    CCNode* m_pButtonNormal;
    CCNode* m_pButtonClicked;
    CCNode* m_pButtonDisable;
    std::string m_strNormalFileName;
    std::string m_strClickedFileName;
    std::string m_strDisabledFileName;
    bool m_bScale9Enable;
    CCRect m_capInsets;
    CCSize m_scale9Size;
    TextureResType m_eNormalTexType;
    TextureResType m_ePressedTexType;
    TextureResType m_eDisabledTexType;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UIButton__) */
