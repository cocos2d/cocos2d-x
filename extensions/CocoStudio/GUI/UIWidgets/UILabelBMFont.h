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

#ifndef __UILABELBMFONT_H__
#define __UILABELBMFONT_H__

#include "../BaseClasses/UIWidget.h"

NS_CC_BEGIN

namespace ui {
    
/**
*   @js NA
*   @lua NA
*/    
class CC_EX_DLL LabelBMFont : public Widget
{
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Default constructor
     */
    LabelBMFont();
    
    /**
     * Default destructor
     */
    virtual ~LabelBMFont();
    
    /**
     * Allocates and initializes.
     */
    static LabelBMFont* create();
    
    /** init a bitmap font atlas with an initial string and the FNT file */
    void setFntFile(const char* fileName);
    
    /** set string value for labelbmfont*/
    void setText(const char* value);
    
    /** get string value for labelbmfont*/
    const char* getStringValue();
    virtual void setAnchorPoint(const CCPoint &pt);
    virtual const CCSize& getContentSize() const;
    virtual CCNode* getVirtualRenderer();
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const;
protected:
    virtual void initRenderer();
    virtual void onSizeChanged();
    virtual void updateTextureColor();
    virtual void updateTextureOpacity();
    virtual void updateTextureRGBA();
    void labelBMFontScaleChangedWithSize();
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
protected:
    cocos2d::CCLabelBMFont* _labelBMFontRenderer;
    bool _fntFileHasInit;
    std::string _fntFileName;
    std::string _stringValue;
};
    
}
NS_CC_END

#endif /* defined(__LabelBMFont__) */
