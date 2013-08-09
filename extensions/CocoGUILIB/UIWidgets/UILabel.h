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

#ifndef __UILABEL_H__
#define __UILABEL_H__

#include "../BaseClasses/UIWidget.h"

NS_CC_EXT_BEGIN

typedef enum
{
    LabelGravityNone = -1,
    LabelGravityCenter,
    LabelGravityLelf,
    LabelGravityRight,
    
}LabelGravity;

class UILabel : public UIWidget
{
public:
    UILabel();
    virtual ~UILabel();
    static UILabel* create();
    void setText(const char* text);
    const char* getStringValue();
    int getStringLength();
    void setFontSize(int size);
    void setFontName(const char* name);
    void setTouchScaleChangeAble(bool able);
    bool getTouchScaleChangeAble();
    void clickScale(float scale);
    virtual void setFlipX(bool flipX);
    virtual void setFlipY(bool flipY);
    virtual bool isFlipX();
    virtual bool isFlipY();
    void setGravity(LabelGravity gravity);
    virtual void adaptSize(float xProportion,float yProportion);
    virtual CCNode* getValidNode();
    virtual void setAnchorPoint(const CCPoint &pt);
protected:
    virtual bool init();
    virtual void initNodes();
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();
protected:
    bool m_bTouchScaleChangeAble;
    float m_fNormalScaleValue;
    LabelGravity m_nGravity;
    std::string m_sFontName;
    int m_nFontSize;
    float m_fOnSelectedScaleOffset;
    CCLabelTTF* m_pRenderLabel;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__Label__) */
