/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef _StringTTF_h
#define _StringTTF_h

#include "CCFontDefinition.h"
#include "CCLabelTextFormatProtocol.h"

NS_CC_BEGIN

class StringTTF : public Node , public LabelTextFormatProtocol
{
public:
    
    StringTTF(LabelFontDefinition *pDefinition, TextAlignment alignment = kTextAlignmentLeft);
    ~StringTTF();
    
    bool setText(char *pStringToRender, float lineWidth, TextAlignment alignment = kTextAlignmentLeft, bool lineBreakWithoutSpaces = false);

    
    // CCLabelTextFormat protocol implementation
    
    // sprite related stuff
    virtual Sprite *                  getSpriteChild(int ID);
    virtual Array  *                  getChildrenLetters();
    virtual Sprite *                  getSpriteForChar(unsigned short int theChar, int spriteIndexHint);
    virtual float                       getLetterPosXLeft( Sprite* sp );
    virtual float                       getLetterPosXRight( Sprite* sp );
    
    // font related stuff
    virtual int                         getCommonLineHeight();
    virtual int                         getKerningForCharsPair(unsigned short first, unsigned short second);
    virtual int                         getXOffsetForChar(unsigned short c);
    virtual int                         getYOffsetForChar(unsigned short c);
    virtual int                         getAdvanceForChar(unsigned short c, int hintPositionInString);
    virtual Rect                      getRectForChar(unsigned short c) ;
    
    // string related stuff
    virtual int                         getStringNumLines();
    virtual int                         getStringLenght();
    virtual unsigned short              getCharAtStringPosition(int position);
    virtual unsigned short *            getUTF8String();
    virtual void                        assignNewUTF8String(unsigned short *newString);
    virtual TextAlignment             getTextAlignment();
    
    // label related stuff
    virtual float                       getMaxLineWidth() ;
    virtual bool                        breakLineWithoutSpace();
    virtual Size                      getLabelContentSize();
    virtual void                        setLabelContentSize(const Size &newSize);
    
    
private:
    
    
    void alignText();
    void hideAllLetters();
    void moveAllSpritesToCache();
    bool computeAdvancesForString(const char *stringToRender);
    bool computeAdvancesForString(unsigned short int *stringToRender);
    bool setCurrentString(unsigned short *stringToSet);
    Sprite * getSprite();
    Sprite * createNewSpriteFromLetterDefinition(LetterDefinition &theDefinition, Texture2D *theTexture);
    Sprite * updateSpriteWithLetterDefinition(Sprite *spriteToUpdate, LetterDefinition &theDefinition, Texture2D *theTexture);
    Sprite * getSpriteForLetter(unsigned short int newLetter);
    Sprite * updateSpriteForLetter(Sprite *spriteToUpdate, unsigned short int newLetter);
    
    Array                       _spriteArray;
    Array                       _spriteArrayCache;
    float                       _commonLineHeight;
    bool                        _lineBreakWithoutSpaces;
    float                       _width;
    TextAlignment               _alignment;
    LabelFontDefinition*        _fontDef;
    unsigned short int *        _currentUTF8String;
    Size               *        _advances;
    
};

NS_CC_END

#endif


