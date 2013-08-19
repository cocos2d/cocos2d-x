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

#ifndef __UILOADINGBAR_H__
#define __UILOADINGBAR_H__

#include "../BaseClasses/UIWidget.h"

NS_CC_EXT_BEGIN

typedef enum
{
    LoadingBarTypeLeft,
    LoadingBarTypeRight
}LoadingBarType;

class UILoadingBar : public UIWidget
{
public:
    UILoadingBar();
    virtual ~UILoadingBar();
    static UILoadingBar* create();
    void setDirection(LoadingBarType dir);
    int getDirection();
    void setTexture(const char* texture,TextureResType texType = UI_TEX_TYPE_LOCAL);
    /* gui mark */
    void setScale9Enable(bool able);
    void setCapInsets(const CCRect &capInsets);
    void setScale9Size(const CCSize &size);
    /**/
    void setPercent(int percent);
    int getPercent();
    float getTotalWidth();
    float getTotalHeight();
    virtual CCNode* getValidNode();
protected:
    virtual void initNodes();
    void setScale9Scale();
protected:
    LoadingBarType m_nBarType;
    int m_nPercent;
    float m_fTotalLength;
    float m_fBarHeight;
    /* gui mark */
    bool m_bScale9Enable;
    CCRect m_capInsets;
    CCSize m_scale9Size;
    std::string m_strTextureFile;
    /**/
    /* gui mark */
    CCNode* m_pRenderBar;
    // before
//    CCSprite* m_pRenderBar;
    /**/
    TextureResType m_eRenderBarTexType;
//    bool m_bUseSpriteFrame;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UILoadingBar__) */
