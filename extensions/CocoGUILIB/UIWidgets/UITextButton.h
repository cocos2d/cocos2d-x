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

#ifndef __UITEXTBUTTON_H__
#define __UITEXTBUTTON_H__

#include "UIButton.h"

NS_CC_EXT_BEGIN

class UITextButton : public UIButton
{
public:
    /**
     * Default constructor
     */
    UITextButton();
    
    /**
     * Default destructor
     */
    virtual ~UITextButton();
    
    /**
     * Allocates and initializes.
     */
    static UITextButton* create();
    
    /**
     * Changes string value of button's title.
     *
     * @param text   string value of button's title.
     */
    void setText(const char* text);
    
    /**
     * Changes color of button's title.
     *
     * @param color   color of button's title.
     */
    void setTextColor(int r,int g,int b);
    
    /**
     * Changes font size of button's title.
     *
     * @param font size   font size of button's title.
     */
    void setFontSize(int size);
    
    /**
     * Changes font name of button's title.
     *
     * @param font name   font name of button's title.
     */
    void setFontName(const char* fontName);
    
    //override "setFlipX" method of widget.
    virtual void setFlipX(bool flipX);
    
    //override "setFlipY" method of widget.
    virtual void setFlipY(bool flipY);
    
    //override "setAnchorPoint" method of widget.
    virtual void setAnchorPoint(const CCPoint &pt);
protected:
    virtual bool init();
protected:
    CCLabelTTF* m_pTextLableRenderer;
    
};

NS_CC_EXT_END

#endif /* defined(__TextButton__) */
