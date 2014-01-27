/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
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
#ifndef __CCLABELTTF_H__
#define __CCLABELTTF_H__

#include "CCTexture2D.h"
#include "CCSprite.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label
 * @{
 */



/** @brief LabelTTF is a subclass of TextureNode that knows how to render text labels
 *
 * All features from TextureNode are valid in LabelTTF
 *
 * LabelTTF objects are slow. Consider using LabelAtlas or LabelBMFont instead.
 *
 * Custom ttf file can be put in assets/ or external storage that the Application can access.
 * @code
 * LabelTTF *label1 = LabelTTF::create("alignment left", "A Damn Mess", fontSize, blockSize, 
 *                                          TextHAlignment::LEFT, TextVAlignment::CENTER);
 * LabelTTF *label2 = LabelTTF::create("alignment right", "/mnt/sdcard/Scissor Cuts.ttf", fontSize, blockSize,
 *                                          TextHAlignment::LEFT, TextVAlignment::CENTER);
 * @endcode
 *
 */
class CC_DLL LabelTTF : public Sprite, public LabelProtocol
{
public:
    /**
     * @js ctor
     */
    LabelTTF();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LabelTTF();

    /** creates a LabelTTF with a font name and font size in points
     @since v2.0.1
     */
    static LabelTTF * create(const std::string& string, const std::string& fontName, float fontSize);
    
    /** creates a LabelTTF from a fontname, horizontal alignment, dimension in points,  and font size in points.
     @since v2.0.1
     */
    static LabelTTF * create(const std::string& string, const std::string& fontName, float fontSize,
                             const Size& dimensions, TextHAlignment hAlignment);
  
    /** creates a Label from a fontname, alignment, dimension in points and font size in points
     @since v2.0.1
     */
    static LabelTTF * create(const std::string& string, const std::string& fontName, float fontSize,
                             const Size& dimensions, TextHAlignment hAlignment,
                             TextVAlignment vAlignment);
    
    
    /** Create a lable with string and a font definition*/
    static LabelTTF * createWithFontDefinition(const std::string& string, FontDefinition &textDefinition);
    
    /** initializes the LabelTTF with a font name and font size */
    bool initWithString(const std::string& string, const std::string& fontName, float fontSize);
    
    /** initializes the LabelTTF with a font name, alignment, dimension and font size */
    bool initWithString(const std::string& string, const std::string& fontName, float fontSize,
                        const Size& dimensions, TextHAlignment hAlignment);

    /** initializes the LabelTTF with a font name, alignment, dimension and font size */
    bool initWithString(const std::string& string, const std::string& fontName, float fontSize,
                        const Size& dimensions, TextHAlignment hAlignment, 
                        TextVAlignment vAlignment);
    
    /** initializes the LabelTTF with a font name, alignment, dimension and font size */
    bool initWithStringAndTextDefinition(const std::string& string, FontDefinition &textDefinition);
    
    /** set the text definition used by this label */
    void setTextDefinition(const FontDefinition& theDefinition);
    
    /** get the text definition used by this label */
    FontDefinition getTextDefinition();
    
    
    
    /** enable or disable shadow for the label */
    void enableShadow(const Size &shadowOffset, float shadowOpacity, float shadowBlur, bool mustUpdateTexture = true);
    
    /** disable shadow rendering */
    void disableShadow(bool mustUpdateTexture = true);
    
    /** enable or disable stroke */
    void enableStroke(const Color3B &strokeColor, float strokeSize, bool mustUpdateTexture = true);
    
    /** disable stroke */
    void disableStroke(bool mustUpdateTexture = true);
    
    /** set text tinting */
    void setFontFillColor(const Color3B &tintColor, bool mustUpdateTexture = true);

    
    
    /** initializes the LabelTTF */
    bool init();

    /** Creates an label.
     */
    static LabelTTF * create();

    /** changes the string to render
    * @warning Changing the string is as expensive as creating a new LabelTTF. To obtain better performance use LabelAtlas
    */
    virtual void setString(const std::string &label) override;
    virtual const std::string& getString(void) const override;
    
    TextHAlignment getHorizontalAlignment() const;
    void setHorizontalAlignment(TextHAlignment alignment);
    
    TextVAlignment getVerticalAlignment() const;
    void setVerticalAlignment(TextVAlignment verticalAlignment);
    
    const Size& getDimensions() const;
    void setDimensions(const Size &dim);
    
    float getFontSize() const;
    void setFontSize(float fontSize);
    
    const std::string& getFontName() const;
    void setFontName(const std::string& fontName);

    /**
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const override;

protected:
    bool updateTexture();

    /** set the text definition for this label */
    void _updateWithTextDefinition(const FontDefinition& textDefinition, bool mustUpdateTexture = true);
    FontDefinition    _prepareTextDefinition(bool adjustForResolution = false);
    
    /** Dimensions of the label in Points */
    Size _dimensions;
    /** The alignment of the label */
    TextHAlignment         _alignment;
    /** The vertical alignment of the label */
    TextVAlignment _vAlignment;
    /** Font name used in the label */
    std::string _fontName;
    /** Font size of the label */
    float _fontSize;
    /** label's string */
    std::string _string;
    
    /** font shadow */
    bool    _shadowEnabled;
    Size    _shadowOffset;
    float   _shadowOpacity;
    float   _shadowBlur;
    
    
    /** font stroke */
    bool        _strokeEnabled;
    Color3B     _strokeColor;
    float       _strokeSize;
        
    /** font tint */
    Color3B   _textFillColor;
};


// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCLABEL_H__

