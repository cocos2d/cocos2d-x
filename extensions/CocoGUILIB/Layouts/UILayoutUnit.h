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

#ifndef __UILayoutUnit_H__
#define __UILayoutUnit_H__

#include "UILayoutDefine.h"

NS_CC_EXT_BEGIN

class UILayoutUnit
{
public:
    UILayoutUnit();
    virtual ~UILayoutUnit();
    //layout
    void setMargin(const UIMargin& margin);
    const UIMargin& getMargin() const;
    void setLinearGravity(UILinearGravity gravity);
    UILinearGravity getLinearGravity() const;
    
    void setRelativeAlign(UIRelativeAlign align);
    UIRelativeAlign getRelativeAlign() const;
    
    void setRelativeAlignWidget(UIRelativeAlignWidget align);
    UIRelativeAlignWidget getRelativeAlignWidget() const;
    
    void setRelativeWidgetName(const char* name);
    const char* getRelativeWidgetName() const;
    
    void setRelativeLayoutName(const char* name);
    const char* getRelativeLayoutName() const;
protected:
    //layout
    UIMargin m_margin;
    //linear
    UILinearGravity m_eLinearGravity;
    //relative
    UIRelativeAlign m_eRelativeAlign;
    UIRelativeAlignWidget m_eRelativeAlignWidget;
    std::string m_strRelativeWidgetName;
    std::string m_strRelativeLayoutName;
};

NS_CC_EXT_END

#endif /* defined(__UILayoutUnit__) */
