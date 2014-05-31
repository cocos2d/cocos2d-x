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

#ifndef __UILABEL_H__
#define __UILABEL_H__

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {

/**
 *  For creating a system font or a TTF font Text
 *@js 
 *@lua NA
 */
class Text : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    enum class Type
    {
        SYSTEM,
        TTF
    };
    /**
     * Default constructor
     */
    Text();

    /**
     * Default destructor
     */
    virtual ~Text();

    /**
     * Allocates and initializes.
     */
    static Text* create();
    
    /**
     *  create a Text object with textContent, fontName and fontSize
     *  the fontName could be a system font name or a TTF file path.
     *  Usage:  Text *text = Text::create("Hello", "Arial", 20);  //create a system font UIText
     *          Text *text = Text::create("Hello", "xxx\xxx.ttf", 20); //create a TTF font UIText
     */
    static Text* create(const std::string& textContent,
                        const std::string& fontName,
                        int fontSize);

    /**
     * Changes the string value of label.
     *
     * @param text  string value.
     */
    CC_DEPRECATED_ATTRIBUTE void setText(const std::string& text){this->setString(text);}
    void setString(const std::string& text);

    /**
     * Gets the string value of label.
     *
     * @return string value.
     */
    CC_DEPRECATED_ATTRIBUTE const std::string& getStringValue(){ return this->getString();}
    const std::string& getString()const;

    /**
     * Gets the string length of the label.
     * Note: This length will be larger than the raw string length,
     * if you want to get the raw string length, you should call this->getString().size() instead
     *
     * @return  string length.
     */
    ssize_t getStringLength()const;

    /**
     * Sets the font size of label.
     *
     * @param size font size.
     */
    void setFontSize(int size);

    int getFontSize()const;

    /**
     * Sets the font name of label.
     *  If you are trying to use a system font, you could just pass a font name
     * If you are trying to use a TTF, you should pass a file path to the TTF file
     * Usage:  Text *text = Text::create("Hello", "Arial", 20);  //create a system font UIText
     *         text->setFontName("Marfelt");  // it will change the font  to  system font no matter the previous font type is TTF or system font
     *         text->setFontName("xxxx/xxx.ttf"); //it will change the font  to TTF font no matter the previous font type is TTF or system font
     * @param name font name.
     */
    void setFontName(const std::string& name);

    const std::string& getFontName()const;
    
    Type getType() const;

    /**
     * Sets the touch scale enabled of label.
     *
     * @param enabled touch scale enabled of label.
     */
    void setTouchScaleChangeEnabled(bool enabled);

    /**
     * Gets the touch scale enabled of label.
     *
     * @return  touch scale enabled of label.
     */
    bool isTouchScaleChangeEnabled()const;

    //override "getVirtualRendererSize" method of widget.
    virtual const Size& getVirtualRendererSize() const override;

    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;

    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;

    void setTextAreaSize(const Size &size);

    const Size& getTextAreaSize()const;

    void setTextHorizontalAlignment(TextHAlignment alignment);

    TextHAlignment getTextHorizontalAlignment()const;

    void setTextVerticalAlignment(TextVAlignment alignment);

    TextVAlignment getTextVerticalAlignment()const;
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    virtual bool init(const std::string& textContent,
                      const std::string& fontName,
                      int fontSize);

protected:
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    virtual void updateFlippedX() override;
    virtual void updateFlippedY() override;
    void labelScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    bool _touchScaleChangeEnabled;
    float _normalScaleValueX;
    float _normalScaleValueY;
    std::string _fontName;
    int _fontSize;
    float _onSelectedScaleOffset;
    Label* _labelRenderer;
    bool _labelRendererAdaptDirty;
    Type _type;
};

}

NS_CC_END

#endif /* defined(__CocoGUI__Label__) */
