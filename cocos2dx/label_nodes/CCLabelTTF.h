/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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

#include "sprite_nodes/CCSprite.h"
#include "textures/CCTexture2D.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label
 * @{
 */

/** @brief CCLabelTTF is a subclass of CCTextureNode that knows how to render text labels
*
* All features from CCTextureNode are valid in CCLabelTTF
*
* CCLabelTTF objects are slow. Consider using CCLabelAtlas or CCLabelBMFont instead.
*/
class CC_DLL CCLabelTTF : public CCSprite, public CCLabelProtocol
{
public:
    CCLabelTTF();
    virtual ~CCLabelTTF();
    const char* description();    
    
    /** creates a CCLabelTTF with a font name and font size in points
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCLabelTTF * labelWithString(const char *string, const char *fontName, float fontSize);
    
    /** creates a CCLabelTTF from a fontname, horizontal alignment, dimension in points,  and font size in points.
     @deprecated: This interface will be deprecated sooner or later.
     @since v1.0
     */
    CC_DEPRECATED_ATTRIBUTE static CCLabelTTF * labelWithString(const char *string, const CCSize& dimensions, CCTextAlignment hAlignment, const char *fontName, float fontSize);
    
    /** creates a CCLabel from a fontname, alignment, dimension in points and font size in points
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCLabelTTF * labelWithString(const char *string, const CCSize& dimensions, CCTextAlignment hAlignment, CCVerticalTextAlignment vAlignment, const char *fontName, float fontSize);
    
    /** creates a CCLabelTTF with a font name and font size in points
     @since v2.0.1
     */
    static CCLabelTTF * create(const char *string, const char *fontName, float fontSize);
    
    /** creates a CCLabelTTF from a fontname, horizontal alignment, dimension in points,  and font size in points.
     @since v2.0.1
     */
    static CCLabelTTF * create(const char *string, const char *fontName, float fontSize,
                               const CCSize& dimensions, CCTextAlignment hAlignment);
  
    /** creates a CCLabel from a fontname, alignment, dimension in points and font size in points
     @since v2.0.1
     */
    static CCLabelTTF * create(const char *string, const char *fontName, float fontSize,
                               const CCSize& dimensions, CCTextAlignment hAlignment, 
                               CCVerticalTextAlignment vAlignment);
    
    /** initializes the CCLabelTTF with a font name and font size */
    bool initWithString(const char *string, const char *fontName, float fontSize);
    
    /** initializes the CCLabelTTF with a font name, alignment, dimension and font size */
    bool initWithString(const char *string, const char *fontName, float fontSize,
                        const CCSize& dimensions, CCTextAlignment hAlignment);

    /** initializes the CCLabelTTF with a font name, alignment, dimension and font size */
    bool initWithString(const char *string, const char *fontName, float fontSize,
                        const CCSize& dimensions, CCTextAlignment hAlignment, 
                        CCVerticalTextAlignment vAlignment);
    
    /** initializes the CCLabelTTF */
    bool init();
    /** Creates an label.
     */
    static CCLabelTTF * node();

    /** Creates an label.
     */
    static CCLabelTTF * create();

    /** changes the string to render
    * @warning Changing the string is as expensive as creating a new CCLabelTTF. To obtain better performance use CCLabelAtlas
    */
    virtual void setString(const char *label);
    virtual const char* getString(void);
    
    CCTextAlignment getHorizontalAlignment();
    void setHorizontalAlignment(CCTextAlignment alignment);
    
    CCVerticalTextAlignment getVerticalAlignment();
    void setVerticalAlignment(CCVerticalTextAlignment verticalAlignment);
    
    CCSize getDimensions();
    void setDimensions(CCSize &dim);
    
    float getFontSize();
    void setFontSize(float fontSize);
    
    const char* getFontName();
    void setFontName(const char *fontName);

private:
    void updateTexture();
protected:
    /** Dimensions of the label in Points */
    CCSize m_tDimensions;
    /** The alignment of the label */
    CCTextAlignment         m_hAlignment;
    /** The vertical alignment of the label */
    CCVerticalTextAlignment m_vAlignment;
    /** Font name used in the label */
    std::string * m_pFontName;
    /** Font size of the label */
    float m_fFontSize;
    
    std::string m_string;
};

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCLABEL_H__

