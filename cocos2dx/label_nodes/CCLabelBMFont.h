/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "sprite_nodes/CCSpriteBatchNode.h"
#include "support/data_support/uthash.h"
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
    kCCLabelAutomaticWidth = -1,
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
    CCRect rect;
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
} tCCFontDefHashElement;

// Equal function for targetSet.
typedef struct _KerningHashElement
{
	int				key;		// key for the hash. 16-bit for 1st element, 16-bit for 2nd element
	int				amount;
	UT_hash_handle	hh;
} tCCKerningHashElement;

/** @brief CCBMFontConfiguration has parsed configuration of the the .fnt file
@since v0.8
*/
class CC_DLL CCBMFontConfiguration : public CCObject
{
    // XXX: Creating a public interface so that the bitmapFontArray[] is accessible
public://@public
    // BMFont definitions
    tCCFontDefHashElement *m_pFontDefDictionary;

    //! FNTConfig: Common Height Should be signed (issue #1343)
    int m_nCommonHeight;
    //! Padding
    ccBMFontPadding    m_tPadding;
    //! atlas name
    std::string m_sAtlasName;
    //! values for kerning
    tCCKerningHashElement *m_pKerningDictionary;
    
    // Character Set defines the letters that actually exist in the font
    std::set<unsigned int> *m_pCharacterSet;
public:
    CCBMFontConfiguration();
    virtual ~CCBMFontConfiguration();
    const char * description();

    /** allocates a CCBMFontConfiguration with a FNT file */
    static CCBMFontConfiguration * create(const char *FNTfile);

    /** initializes a BitmapFontConfiguration with a FNT file */
    bool initWithFNTfile(const char *FNTfile);
    
    inline const char* getAtlasName(){ return m_sAtlasName.c_str(); }
    inline void setAtlasName(const char* atlasName) { m_sAtlasName = atlasName; }
    
    std::set<unsigned int>* getCharacterSet() const;
private:
    std::set<unsigned int>* parseConfigFile(const char *controlFile);
    void parseCharacterDefinition(std::string line, ccBMFontDef *characterDefinition);
    void parseInfoArguments(std::string line);
    void parseCommonArguments(std::string line);
    void parseImageFileName(std::string line, const char *fntFile);
    void parseKerningEntry(std::string line);
    void purgeKerningDictionary();
    void purgeFontDefDictionary();
};

/** @brief CCLabelBMFont is a subclass of CCSpriteBatchNode.

Features:
- Treats each character like a CCSprite. This means that each individual character can be:
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

CCLabelBMFont implements the protocol CCLabelProtocol, like CCLabel and CCLabelAtlas.
CCLabelBMFont has the flexibility of CCLabel, the speed of CCLabelAtlas and all the features of CCSprite.
If in doubt, use CCLabelBMFont instead of CCLabelAtlas / CCLabel.

Supported editors:
http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
http://www.angelcode.com/products/bmfont/ (Free, Windows only)

@since v0.8
*/

class CC_DLL CCLabelBMFont : public CCSpriteBatchNode, public CCLabelProtocol, public CCRGBAProtocol
{
public:
    CCLabelBMFont();

    virtual ~CCLabelBMFont();
    /** Purges the cached data.
    Removes from memory the cached configurations and the atlas name dictionary.
    @since v0.99.3
    */
    static void purgeCachedData();

    /** creates a bitmap font atlas with an initial string and the FNT file */
    static CCLabelBMFont * create(const char *str, const char *fntFile, float width, CCTextAlignment alignment, CCPoint imageOffset);
    
	static CCLabelBMFont * create(const char *str, const char *fntFile, float width, CCTextAlignment alignment);

	static CCLabelBMFont * create(const char *str, const char *fntFile, float width);

	static CCLabelBMFont * create(const char *str, const char *fntFile);

    /** Creates an label.
     */
    static CCLabelBMFont * create();

    bool init();
    /** init a bitmap font atlas with an initial string and the FNT file */
    bool initWithString(const char *str, const char *fntFile, float width = kCCLabelAutomaticWidth, CCTextAlignment alignment = kCCTextAlignmentLeft, CCPoint imageOffset = CCPointZero);

    /** updates the font chars based on the string to render */
    void createFontChars();
    // super method
    virtual void setString(const char *newString);
    virtual void setString(const char *newString, bool needUpdateLabel);

    virtual const char* getString(void);
    virtual void setCString(const char *label);
    virtual void setAnchorPoint(const CCPoint& var);
    virtual void updateLabel();
    virtual void setAlignment(CCTextAlignment alignment);
    virtual void setWidth(float width);
    virtual void setLineBreakWithoutSpace(bool breakWithoutSpace);
    virtual void setScale(float scale);
    virtual void setScaleX(float scaleX);
    virtual void setScaleY(float scaleY);
    
    // CCRGBAProtocol 
    virtual bool isOpacityModifyRGB();
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB); virtual GLubyte getOpacity();
    virtual GLubyte getDisplayedOpacity();
    virtual void setOpacity(GLubyte opacity);
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);
    virtual bool isCascadeOpacityEnabled();
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    virtual const ccColor3B& getColor(void);
    virtual const ccColor3B& getDisplayedColor();
    virtual void setColor(const ccColor3B& color);
    virtual void updateDisplayedColor(const ccColor3B& parentColor);
    virtual bool isCascadeColorEnabled();
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);

    void setFntFile(const char* fntFile);
    const char* getFntFile();
#if CC_LABELBMFONT_DEBUG_DRAW
    virtual void draw();
#endif // CC_LABELBMFONT_DEBUG_DRAW
private:
    char * atlasNameFromFntFile(const char *fntFile);
    int kerningAmountForFirst(unsigned short first, unsigned short second);
    float getLetterPosXLeft( CCSprite* characterSprite );
    float getLetterPosXRight( CCSprite* characterSprite );
    
protected:
    virtual void setString(unsigned short *newString, bool needUpdateLabel);
    // string to render
    unsigned short* m_sString;
    
    // name of fntFile
    std::string m_sFntFile;
    
    // initial string without line breaks
    unsigned short* m_sInitialString;
    std::string m_sInitialStringUTF8;
    
    // alignment of all lines
    CCTextAlignment m_pAlignment;
    // max width until a line break is added
    float m_fWidth;
    
    CCBMFontConfiguration *m_pConfiguration;
    
    bool m_bLineBreakWithoutSpaces;
    // offset of the texture atlas
    CCPoint    m_tImageOffset;
    
    // reused char
    CCSprite *m_pReusedChar;
    
    // texture RGBA
    GLubyte m_cDisplayedOpacity;
    GLubyte m_cRealOpacity;
    ccColor3B m_tDisplayedColor;
    ccColor3B m_tRealColor;
    bool m_bCascadeColorEnabled;
    bool m_bCascadeOpacityEnabled;
    /** conforms to CCRGBAProtocol protocol */
    bool        m_bIsOpacityModifyRGB;

};

/** Free function that parses a FNT file a place it on the cache
*/
CC_DLL CCBMFontConfiguration * FNTConfigLoadFile( const char *file );
/** Purges the FNT config cache
*/
CC_DLL void FNTConfigRemoveCache( void );

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCBITMAP_FONT_ATLAS_H__
