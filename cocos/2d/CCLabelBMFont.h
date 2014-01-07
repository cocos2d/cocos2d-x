/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

Use any of these editors to generate BMFonts:
  http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
  http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
  http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
  http://www.angelcode.com/products/bmfont/ (Free, Windows only)

****************************************************************************/
#ifndef __CCBITMAP_FONT_ATLAS_H__
#define __CCBITMAP_FONT_ATLAS_H__

#include "CCSpriteBatchNode.h"
#include "uthash.h"
#include <map>
#include <sstream>
#include <iostream>
#include <vector>

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label
 * @{
 */

enum {
    kLabelAutomaticWidth = -1,
};

struct _FontDefHashElement;

/**
@struct ccBMFontDef
BMFont definition
*/
typedef struct _BMFontDef {
    //! ID of the character
    unsigned int charID;
    //! origin and size of the font
    Rect rect;
    //! The X amount the image should be offset when drawing the image (in pixels)
    short xOffset;
    //! The Y amount the image should be offset when drawing the image (in pixels)
    short yOffset;
    //! The amount to move the current position after drawing the character (in pixels)
    short xAdvance;
} ccBMFontDef;

/** @struct ccBMFontPadding
BMFont padding
@since v0.8.2
*/
typedef struct _BMFontPadding {
    /// padding left
    int    left;
    /// padding top
    int top;
    /// padding right
    int right;
    /// padding bottom
    int bottom;
} ccBMFontPadding;

typedef struct _FontDefHashElement
{
	unsigned int	key;		// key. Font Unicode value
	ccBMFontDef		fontDef;	// font definition
	UT_hash_handle	hh;
} tFontDefHashElement;

// Equal function for targetSet.
typedef struct _KerningHashElement
{
	int				key;		// key for the hash. 16-bit for 1st element, 16-bit for 2nd element
	int				amount;
	UT_hash_handle	hh;
} tKerningHashElement;

/** @brief CCBMFontConfiguration has parsed configuration of the the .fnt file
@since v0.8
*/
class CC_DLL CCBMFontConfiguration : public Object
{
    // XXX: Creating a public interface so that the bitmapFontArray[] is accessible
public://@public
    // BMFont definitions
    tFontDefHashElement *_fontDefDictionary;

    //! FNTConfig: Common Height Should be signed (issue #1343)
    int _commonHeight;
    //! Padding
    ccBMFontPadding    _padding;
    //! atlas name
    std::string _atlasName;
    //! values for kerning
    tKerningHashElement *_kerningDictionary;
    
    // Character Set defines the letters that actually exist in the font
    std::set<unsigned int> *_characterSet;
public:
    /**
     * @js ctor
     */
    CCBMFontConfiguration();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CCBMFontConfiguration();
    /**
     * @js NA
     * @lua NA
     */
    std::string description() const;

    /** allocates a CCBMFontConfiguration with a FNT file */
    static CCBMFontConfiguration * create(const std::string& FNTfile);

    /** initializes a BitmapFontConfiguration with a FNT file */
    bool initWithFNTfile(const std::string& FNTfile);
    
    inline const std::string& getAtlasName(){ return _atlasName; }
    inline void setAtlasName(const std::string& atlasName) { _atlasName = atlasName; }
    
    std::set<unsigned int>* getCharacterSet() const;
private:
    std::set<unsigned int>* parseConfigFile(const std::string& controlFile);
	std::set<unsigned int>* parseBinaryConfigFile(unsigned char* pData, unsigned long size, const std::string& controlFile);
    void parseCharacterDefinition(std::string line, ccBMFontDef *characterDefinition);
    void parseInfoArguments(std::string line);
    void parseCommonArguments(std::string line);
    void parseImageFileName(std::string line, const std::string& fntFile);
    void parseKerningEntry(std::string line);
    void purgeKerningDictionary();
    void purgeFontDefDictionary();
};

/** @brief LabelBMFont is a subclass of SpriteBatchNode.

Features:
- Treats each character like a Sprite. This means that each individual character can be:
- rotated
- scaled
- translated
- tinted
- change the opacity
- It can be used as part of a menu item.
- anchorPoint can be used to align the "label"
- Supports AngelCode text format

Limitations:
- All inner characters are using an anchorPoint of (0.5f, 0.5f) and it is not recommend to change it
because it might affect the rendering

LabelBMFont implements the protocol LabelProtocol, like Label and LabelAtlas.
LabelBMFont has the flexibility of Label, the speed of LabelAtlas and all the features of Sprite.
If in doubt, use LabelBMFont instead of LabelAtlas / Label.

Supported editors:
http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
http://www.angelcode.com/products/bmfont/ (Free, Windows only)

@since v0.8
*/

class CC_DLL LabelBMFont : public SpriteBatchNode, public LabelProtocol
{
public:
    /**
     * @js ctor
     */
    LabelBMFont();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LabelBMFont();
    /** Purges the cached data.
    Removes from memory the cached configurations and the atlas name dictionary.
    @since v0.99.3
    */
    static void purgeCachedData();

    /** creates a bitmap font atlas with an initial string and the FNT file */
    static LabelBMFont * create(const std::string& str, const std::string& fntFile, float width, TextHAlignment alignment, Point imageOffset);
    
	static LabelBMFont * create(const std::string& str, const std::string& fntFile, float width, TextHAlignment alignment);

	static LabelBMFont * create(const std::string& str, const std::string& fntFile, float width);

	static LabelBMFont * create(const std::string& str, const std::string& fntFile);

    /** Creates an label.
     */
    static LabelBMFont * create();

    bool init();
    /** init a bitmap font atlas with an initial string and the FNT file */
    bool initWithString(const std::string& str, const std::string& fntFile, float width = kLabelAutomaticWidth, TextHAlignment alignment = TextHAlignment::LEFT, Point imageOffset = Point::ZERO);

    /** updates the font chars based on the string to render */
    void createFontChars();
    // super method
    virtual void setString(const std::string& newString) override;
    virtual void setString(const std::string& newString, bool needUpdateLabel);

    virtual const std::string& getString() const override;
    virtual void setCString(const char *label);
    virtual void setAnchorPoint(const Point& var) override;
    virtual void updateLabel();
    virtual void setAlignment(TextHAlignment alignment);
    virtual void setWidth(float width);
    virtual void setLineBreakWithoutSpace(bool breakWithoutSpace);
    virtual void setScale(float scale);
    virtual void setScaleX(float scaleX);
    virtual void setScaleY(float scaleY);
    
    // RGBAProtocol 
    virtual bool isOpacityModifyRGB() const;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB);

    void setFntFile(const std::string& fntFile);
    const std::string& getFntFile() const;

    virtual std::string getDescription() const override;

#if CC_LABELBMFONT_DEBUG_DRAW
    virtual void draw();
#endif // CC_LABELBMFONT_DEBUG_DRAW
protected:
    char * atlasNameFromFntFile(const std::string& fntFile);
    int kerningAmountForFirst(unsigned short first, unsigned short second);
    float getLetterPosXLeft( Sprite* characterSprite );
    float getLetterPosXRight( Sprite* characterSprite );
    
    virtual void setString(unsigned short *newString, bool needUpdateLabel);
    // string to render
    unsigned short* _string;
    
    // name of fntFile
    std::string _fntFile;
    
    // initial string without line breaks
    unsigned short* _initialString;
    std::string _initialStringUTF8;
    
    // alignment of all lines
    TextHAlignment _alignment;
    // max width until a line break is added
    float _width;
    
    CCBMFontConfiguration *_configuration;
    
    bool _lineBreakWithoutSpaces;
    // offset of the texture atlas
    Point    _imageOffset;
    
    // reused char
    Sprite *_reusedChar;
    
    // texture RGBA
    bool _isOpacityModifyRGB;

};

/** Free function that parses a FNT file a place it on the cache
*/
CC_DLL CCBMFontConfiguration * FNTConfigLoadFile(const std::string &file);
/** Purges the FNT config cache
*/
CC_DLL void FNTConfigRemoveCache( void );

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCBITMAP_FONT_ATLAS_H__
