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
#ifndef __CCBITMAP_FONT_ATLAS_H__NEW__
#define __CCBITMAP_FONT_ATLAS_H__NEW__

#include "sprite_nodes/CCSpriteBatchNode.h"
#include "support/data_support/uthash.h"

#include <map>
#include <sstream>
#include <iostream>
#include <vector>


#include "CClabelTextFormatProtocol.h"
#include "CCLabelBMFont.h"

NS_CC_BEGIN

class CC_DLL LabelBMFontNew : public SpriteBatchNode, public LabelProtocol, public RGBAProtocol, public LabelTextFormatProtocol
{
public:
    LabelBMFontNew();

    virtual ~LabelBMFontNew();
    /** Purges the cached data.
    Removes from memory the cached configurations and the atlas name dictionary.
    @since v0.99.3
    */
    static void purgeCachedData();

    /** creates a bitmap font atlas with an initial string and the FNT file */
    static LabelBMFontNew * create(const char *str, const char *fntFile, float width, TextAlignment alignment, Point imageOffset);
    
	static LabelBMFontNew * create(const char *str, const char *fntFile, float width, TextAlignment alignment);

	static LabelBMFontNew * create(const char *str, const char *fntFile, float width);

	static LabelBMFontNew * create(const char *str, const char *fntFile);

    /** Creates an label.
     */
    static LabelBMFontNew * create();

    bool init();
    
    /** init a bitmap font atlas with an initial string and the FNT file */
    bool initWithString(const char *str, const char *fntFile, float width = kLabelAutomaticWidth, TextAlignment alignment = kTextAlignmentLeft, Point imageOffset = PointZero);

    /** updates the font chars based on the string to render */
    
    

    
public:
    
    // protocol stuff
    virtual Sprite *                     getSpriteChild(int ID);
    virtual Array  *                     getChildrenLetters();
    virtual Sprite *                     getSpriteForChar(unsigned short int theChar, int spriteIndexHint);
    virtual int                          getCommonLineHeight();
    virtual int                          getKerningForCharsPair(unsigned short first, unsigned short second);
    virtual int                          getXOffsetForChar(unsigned short c);
    virtual int                          getYOffsetForChar(unsigned short c);
    virtual int                          getAdvanceForChar(unsigned short c, int hintPositionInString);
    virtual Rect                         getRectForChar(unsigned short c);
    float                                getLetterPosXLeft( Sprite* sp );
    float                                getLetterPosXRight( Sprite* sp );
    virtual int                          getStringNumLines();
    virtual int                          getStringLenght();
    virtual unsigned short               getCharAtStringPosition(int position);
    virtual unsigned short *             getUTF8String();
    virtual void                         assignNewUTF8String(unsigned short *newString);
    virtual float                        getMaxLineWidth();
    virtual bool                         breakLineWithoutSpace();
    virtual TextAlignment                getTextAlignment();
    virtual Size                         getLabelContentSize();
    virtual void                         setLabelContentSize(const Size &newSize);
    
    
private:
    
    // update the label
    void                updateLabel();
    
    // align the text
    void                alignText();
    
    // put the test on more than one line if needed
    void                multilineText();
    
    //
    ccBMFontDef         getFontDefForChar(unsigned short int theChar);
    
    // create and place all the sprites needed by the current string
    void createStringSprites();
    
    // hide all the sprites needed by the current string
    void hideStringSprites();
    
    // hide sprite and create new ones
    void updateLetterSprites();
   
    
public:
    
    // super method
    virtual void setString(const char *label);
    virtual const char* getString(void);
    virtual void setCString(const char *label);
    virtual void setAnchorPoint(const Point& var);
    virtual void setAlignment(TextAlignment alignment);
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
    virtual const Color3B& getColor(void);
    virtual const Color3B& getDisplayedColor();
    virtual void setColor(const Color3B& color);
    virtual void updateDisplayedColor(const Color3B& parentColor);
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
   
    
protected:
    
    // string to render
    unsigned short* m_sString;
    
    // name of fntFile
    std::string m_sFntFile;
    
    // initial string without line breaks
    std::string m_sInitialString;
    
    // alignment of all lines
    TextAlignment m_pAlignment;
    
    // max width until a line break is added
    float m_fWidth;
    
    //
    CCBMFontConfiguration *m_pConfiguration;
    //
    bool m_bLineBreakWithoutSpaces;
    
    // offset of the texture atlas
    Point    m_tImageOffset;
    
    // reused char
    Sprite *m_pReusedChar;
    
    // texture RGBA
    GLubyte m_cDisplayedOpacity;
    GLubyte m_cRealOpacity;
    Color3B m_tDisplayedColor;
    Color3B m_tRealColor;
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
