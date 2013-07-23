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

#ifndef __UICLIPABLELAYERCOLOR_H__
#define __UICLIPABLELAYERCOLOR_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

typedef enum
{
    UL_C_NONE,
    UL_C_COLOR,
    UL_C_GRADIENT
}UILayerColorType;
    
class UIClippingLayer : public cocos2d::LayerRGBA
{
public:
    UIClippingLayer();
    virtual ~UIClippingLayer();
    static UIClippingLayer* create();
    virtual void visit();
    void setClippingEnable(bool able);
    bool isClippingEnable();
    void setColorType(UILayerColorType type);
    bool getColorType();
    void setClipRect(const cocos2d::Rect &rect);
    const Rect& getClippingRect();
    virtual void setPosition(const Point &pos);
    void setBGColor(const Color3B &color);
    void setBGStartColor(const Color3B &color);
    void setBGEndColor(const Color3B &color);
    void setBGVector(const Point &vector);
    void setBGColorOpacity(int opacity);
    virtual void onEnter();
    virtual void onExit();
    void checkClippingOption();
    void updateChildrenClippingOptions();
    virtual void setContentSize(const Size &size);
protected:

//    void checkNodeClippingOption(CCNode* node);
protected:
    bool m_bClippingEnable;
    float m_fScissorX;
    float m_fScissorY;
    bool m_bEnableCustomArea;
    bool m_bHandleScissor;
    Point m_loacationInWorld;
    Rect m_clippingRect;
    UIClippingLayer* m_pClippingParent;
    LayerColor* m_pColorRender;
    LayerGradient* m_pGradientRender;
    UILayerColorType m_colorType;
    Color3B m_cColor;
    Color3B m_gStartColor;
    Color3B m_gEndColor;
    Point m_AlongVector;
    int m_nCOpacity;
    Rect m_parentClippingRect;
};

NS_CC_EXT_END

#endif
