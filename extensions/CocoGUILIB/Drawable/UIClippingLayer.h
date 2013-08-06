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
    
class UIClippingLayer : public CCLayerRGBA
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
    void setClipRect(const CCRect &rect);
    const CCRect& getClippingRect();
    virtual void setPosition(const CCPoint &pos);
    void setBGColor(const ccColor3B &color);
    void setBGStartColor(const ccColor3B &color);
    void setBGEndColor(const ccColor3B &color);
    void setBGVector(const CCPoint &vector);
    void setBGColorOpacity(int opacity);
    virtual void onEnter();
    virtual void onExit();
    void checkClippingOption();
    void updateChildrenClippingOptions();
    virtual void setContentSize(const CCSize &size);
protected:

//    void checkNodeClippingOption(CCNode* node);
protected:
    bool m_bClippingEnable;
    float m_fScissorX;
    float m_fScissorY;
    bool m_bEnableCustomArea;
    bool m_bHandleScissor;
    CCPoint m_loacationInWorld;
    CCRect m_clippingRect;
    UIClippingLayer* m_pClippingParent;
    CCLayerColor* m_pColorRender;
    CCLayerGradient* m_pGradientRender;
    UILayerColorType m_colorType;
    ccColor3B m_cColor;
    ccColor3B m_gStartColor;
    ccColor3B m_gEndColor;
    CCPoint m_AlongVector;
    int m_nCOpacity;
    CCRect m_parentClippingRect;
};

NS_CC_EXT_END

#endif
