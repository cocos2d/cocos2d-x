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
#ifndef __CCBITMAP_FONT_ATLAS_H__NEW_
#define __CCBITMAP_FONT_ATLAS_H__NEW_

#include "sprite_nodes/CCSpriteBatchNode.h"
#include "support/data_support/uthash.h"
#include "CCLabelBMFont.h"
#include "CCLabelTextFormatProtocol.h"
#include <map>
#include <sstream>
#include <iostream>
#include <vector>
#include "CCLabel.h"

NS_CC_BEGIN

class CC_DLL StringBMFont: public Label, public LabelTextFormatProtocol
{
public:
    StringBMFont();

    virtual ~StringBMFont();
    /** Purges the cached data.
    Removes from memory the cached configurations and the atlas name dictionary.
    @since v0.99.3
    */
    static void purgeCachedData();

    /** creates a bitmap font atlas with an initial string and the FNT file */
    static StringBMFont * create(const char *str, const char *fntFile, float width, TextHAlignment alignment, Point imageOffset);
    
	static StringBMFont * create(const char *str, const char *fntFile, float width, TextHAlignment alignment);

	static StringBMFont * create(const char *str, const char *fntFile, float width);

	static StringBMFont * create(const char *str, const char *fntFile);

    /** Creates an label.
     */
    static StringBMFont * create();

    bool init();
    /** init a bitmap font atlas with an initial string and the FNT file */
    bool initWithString(const char *str, const char *fntFile, float width = kLabelAutomaticWidth, TextHAlignment alignment = TextHAlignment::LEFT, Point imageOffset = Point::ZERO);

    /** updates the font chars based on the string to render */
    // super method
    virtual void setString(const char *newString);
    
    virtual const char* getString(void) const;
    virtual void setCString(const char *label);
    virtual void setAnchorPoint(const Point& var);
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
    virtual GLubyte getOpacity() const;
    virtual GLubyte getDisplayedOpacity() const;
    virtual void setOpacity(GLubyte opacity);
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);
    virtual bool isCascadeOpacityEnabled() const;
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    virtual const Color3B& getColor(void) const;
    virtual const Color3B& getDisplayedColor() const;
    virtual void setColor(const Color3B& color);
    virtual void updateDisplayedColor(const Color3B& parentColor);
    virtual bool isCascadeColorEnabled() const;
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);
    
    
    // StringBMFont protocol stuff
    virtual Sprite *          getSpriteChild(int ID);
    virtual Array  *          getChildrenLetters();
    virtual Sprite *          getSpriteForChar(unsigned short int theChar, int spriteIndexHint);
    virtual int               getCommonLineHeight();
    virtual int               getKerningForCharsPair(unsigned short first, unsigned short second);
    virtual int               getXOffsetForChar(unsigned short c);
    virtual int               getYOffsetForChar(unsigned short c);
    virtual int               getAdvanceForChar(unsigned short c, int hintPositionInString);
    virtual Rect              getRectForChar(unsigned short c);
    float                     getLetterPosXLeft( Sprite* sp );
    float                     getLetterPosXRight( Sprite* sp );
    virtual int               getStringNumLines();
    virtual int               getStringLenght();
    virtual unsigned short    getCharAtStringPosition(int position);
    virtual unsigned short *  getUTF8String();
    virtual void              assignNewUTF8String(unsigned short *newString);
    virtual float             getMaxLineWidth();
    virtual bool              breakLineWithoutSpace();
    virtual TextHAlignment getTextAlignment();
    virtual Size              getLabelContentSize();
    virtual void              setLabelContentSize(const Size &newSize);
    

    void setFntFile(const char* fntFile);
    const char* getFntFile();

#if CC_LABELBMFONT_DEBUG_DRAW
    virtual void draw();
#endif // CC_LABELBMFONT_DEBUG_DRAW

private:
    char * atlasNameFromFntFile(const char *fntFile);
    int kerningAmountForFirst(unsigned short first, unsigned short second);
    
    // some more new stuff
    void                alignText();
    void                multilineText();
    ccBMFontDef         getFontDefForChar(unsigned short int theChar);
    void                createStringSprites();
    void                hideStringSprites();
    void                updateLetterSprites();
    
    
protected:
    
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
    GLubyte _displayedOpacity;
    GLubyte _realOpacity;
    Color3B _displayedColor;
    Color3B _realColor;
    bool _cascadeColorEnabled;
    bool _cascadeOpacityEnabled;
    /** conforms to RGBAProtocol protocol */
    bool        _isOpacityModifyRGB;

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
