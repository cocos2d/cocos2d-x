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

#ifndef __UITEXTAREA_H__
#define __UITEXTAREA_H__

#include "../BaseClasses/UIWidget.h"


NS_CC_EXT_BEGIN

class UITextArea : public UIWidget
{
public:
    UITextArea();
    virtual ~UITextArea();
    static UITextArea* create();
    virtual void initNodes();
    void setText(const char* text);
    void setTextAreaSize(const CCSize &size);
    void setTextHorizontalAlignment(CCTextAlignment alignment);
    void setTextVerticalAlignment(CCVerticalTextAlignment alignment);
    int getStringLength();
    const char* getStringValue();
    void setTextColor(int r,int g,int b);
    void setFontSize(int size);
    void setFontName(const char* fontName);
    virtual void setFlipX(bool flipX);
    virtual void setFlipY(bool flipY);
    virtual bool isFlipX();
    virtual bool isFlipY();
    virtual CCNode* getValidNode();
    virtual void setAnchorPoint(const CCPoint &pt);
protected:
    CCLabelTTF* m_pRenderLabel;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UITextArea__) */
