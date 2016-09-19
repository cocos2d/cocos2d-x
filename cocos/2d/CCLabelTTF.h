/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
 
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

/// @cond DO_NOT_SHOW

#include "2d/CCNode.h"

NS_CC_BEGIN

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif

/// @cond

class Label;

/**
 * @addtogroup _2d
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
class CC_DLL CC_DEPRECATED_ATTRIBUTE LabelTTF : public Node, public LabelProtocol, public BlendProtocol
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

    /** creates a Label from a fontname, alignment, dimension in points and font size in points
     @since v2.0.1
     */
    static LabelTTF * create(const std::string& string, const std::string& fontName, float fontSize,
                             const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::CENTER,
                             TextVAlignment vAlignment = TextVAlignment::TOP);
    
    
    /** Create a label with string and a font definition*/
    static LabelTTF * createWithFontDefinition(const std::string& string, FontDefinition &textDefinition);
    
    /** initializes the LabelTTF with a font name, alignment, dimension and font size */
    bool initWithString(const std::string& string, const std::string& fontName, float fontSize,
                        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT, 
                        TextVAlignment vAlignment = TextVAlignment::TOP);
    
    /** initializes the LabelTTF with a font name, alignment, dimension and font size */
    bool initWithStringAndTextDefinition(const std::string& string, FontDefinition &textDefinition);
    
    /** set the text definition used by this label */
    void setTextDefinition(const FontDefinition& theDefinition);
    
    /** get the text definition used by this label */
    const FontDefinition& getTextDefinition();
    
    
    
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

    /** Creates an label.
     */
    static LabelTTF * create();

    /** changes the string to render
    * @warning Changing the string is as expensive as creating a new LabelTTF. To obtain better performance use LabelAtlas
    */
    virtual void setString(const std::string &label) override;
    virtual const std::string& getString(void) const override ;
    
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

    virtual void setBlendFunc(const BlendFunc &blendFunc) override;

    virtual const BlendFunc &getBlendFunc() const override;

    virtual void setFlippedX(bool flippedX);
    virtual void setFlippedY(bool flippedY);

    virtual Rect getBoundingBox() const override;

    /**
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual const Size& getContentSize() const override;
protected:
    Label*    _renderLabel;
    bool _contentDirty;
    FontDefinition _fontDef;
};


// end of group
/// @}
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif

NS_CC_END

/// @endcond
#endif //__CCLABEL_H__

