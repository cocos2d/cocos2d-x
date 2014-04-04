/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __UILABELBMFONT_H__
#define __UILABELBMFONT_H__

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {
    
/**
*   @js NA
*   @lua NA
*/    
class TextBMFont : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Default constructor
     */
    TextBMFont();
    
    /**
     * Default destructor
     */
    virtual ~TextBMFont();
    
    /**
     * Allocates and initializes.
     */
    static TextBMFont* create();
    
    /** init a bitmap font atlas with an initial string and the FNT file */
    void setFntFile(const char* fileName);
    
    /** set string value for labelbmfont*/
    void setText(const char* value);
    
    /** get string value for labelbmfont*/
    const char* getStringValue();
    virtual void setAnchorPoint(const Point &pt) override;
    virtual const Size& getContentSize() const override;
    virtual Node* getVirtualRenderer() override;
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    void labelBMFontScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
protected:
    cocos2d::Label* _labelBMFontRenderer;
    bool _fntFileHasInit;
    std::string _fntFileName;
    std::string _stringValue;
};
    
}
NS_CC_END

#endif /* defined(__LabelBMFont__) */
