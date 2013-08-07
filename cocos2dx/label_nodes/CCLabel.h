/****************************************************************************
 Copyright (c) 2013      Zynga Inc.

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


#ifndef _COCOS2D_CCLABEL_H_
#define _COCOS2D_CCLABEL_H_

#include "sprite_nodes/CCSpriteBatchNode.h"
#include "CCLabelTextFormatProtocol.h"
#include "ccTypes.h"

NS_CC_BEGIN

enum class GlyphCollection {
    
    DYNAMIC,
    NEHE,
    ASCII,
    CUSTOM
    
};

//fwd
class FontLetterDefinition;
class FontAtlas;



class CC_DLL Label : public SpriteBatchNode, public LabelProtocol, public RGBAProtocol, public LabelTextFormatProtocol
{
public:
    
    static Label* createWithTTF( const char* label, const char* tttFilePath, int fontSize, GlyphCollection glyphs = GlyphCollection::NEHE, int lineSize = 0, const char *customGlyphs = 0 );
    static Label* createWithBMFont( const char* label, const char* bmfontFilePath, int lineSize = 0 );
    
    Label(FontAtlas *pAtlas, TextHAlignment alignment);
    ~Label();
          
    bool setText(const char *stringToRender, float lineWidth, TextHAlignment alignment = TextHAlignment::LEFT, bool lineBreakWithoutSpaces = false);
    void setString(const char *stringToRender);
    
    virtual void setAlignment(TextHAlignment alignment);
    virtual void setWidth(float width);
    virtual void setLineBreakWithoutSpace(bool breakWithoutSpace);
    virtual void setScale(float scale);
    virtual void setScaleX(float scaleX);
    virtual void setScaleY(float scaleY);
    
    // carloX
    const char * getString() const { return "not implemented"; }
    
    // RGBAProtocol
    virtual bool isOpacityModifyRGB() const;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB);
    virtual void setOpacity(GLubyte opacity);
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);
    virtual bool isCascadeOpacityEnabled() const;
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    virtual void setColor(const Color3B& color);
    virtual void updateDisplayedColor(const Color3B& parentColor);
    virtual bool isCascadeColorEnabled() const;
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);
    virtual const Color3B& getColor(void) const;
    virtual const Color3B& getDisplayedColor() const;
    virtual unsigned char  getOpacity() const;
    virtual unsigned char  getDisplayedOpacity() const;
    
     // CCLabelTextFormat protocol implementation
    virtual Sprite *                    getSpriteChild(int ID);
    virtual Array  *                    getChildrenLetters();
    virtual Sprite *                    getSpriteForChar(unsigned short int theChar, int spriteIndexHint);
    virtual float                       getLetterPosXLeft( Sprite* sp );
    virtual float                       getLetterPosXRight( Sprite* sp );
    
    // font related stuff
    virtual int                         getCommonLineHeight();
    virtual int                         getKerningForCharsPair(unsigned short first, unsigned short second);
    virtual int                         getXOffsetForChar(unsigned short c);
    virtual int                         getYOffsetForChar(unsigned short c);
    virtual int                         getAdvanceForChar(unsigned short c, int hintPositionInString);
    virtual Rect                        getRectForChar(unsigned short c) ;
    
    // string related stuff
    virtual int                         getStringNumLines();
    virtual int                         getStringLenght();
    virtual unsigned short              getCharAtStringPosition(int position);
    virtual unsigned short *            getUTF8String();
    virtual void                        assignNewUTF8String(unsigned short *newString);
    virtual TextHAlignment              getTextAlignment();
    
    // label related stuff
    virtual float                       getMaxLineWidth() ;
    virtual bool                        breakLineWithoutSpace();
    virtual Size                        getLabelContentSize();
    virtual void                        setLabelContentSize(const Size &newSize);
    
    
private:
    
    static Label* create(FontAtlas *pAtlas, TextHAlignment alignment = TextHAlignment::LEFT, int lineSize = 0);
    
    bool init();
    
    void alignText();
    void hideAllLetters();
    void moveAllSpritesToCache();
    
    bool computeAdvancesForString(unsigned short int *stringToRender);
    bool setCurrentString(unsigned short *stringToSet);
    bool setOriginalString(unsigned short *stringToSet);
    void resetCurrentString();
    
    Sprite * getSprite();
    Sprite * createNewSpriteFromLetterDefinition(FontLetterDefinition &theDefinition, Texture2D *theTexture);
    Sprite * updateSpriteWithLetterDefinition(Sprite *spriteToUpdate, FontLetterDefinition &theDefinition, Texture2D *theTexture);
    Sprite * getSpriteForLetter(unsigned short int newLetter);
    Sprite * updateSpriteForLetter(Sprite *spriteToUpdate, unsigned short int newLetter);
    
    Array                       _spriteArray;
    Array                       _spriteArrayCache;
    float                       _commonLineHeight;
    bool                        _lineBreakWithoutSpaces;
    float                       _width;
    TextHAlignment              _alignment;
    unsigned short int *        _currentUTF8String;
    unsigned short int *        _originalUTF8String;
    Size               *        _advances;
    FontAtlas          *        _fontAtlas;
    Color3B                     _displayedColor;
    Color3B                     _realColor;
    bool                        _cascadeColorEnabled;
    
    
};


NS_CC_END

#endif /*__COCOS2D_CCLABEL_H */
