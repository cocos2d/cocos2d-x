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

#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>

#include "cocos2d.h"
#include "CCFontIOS.h"
#include "CCTextImage.h"
#include "CCFontRenderIOS.h"

// new stuff CarloX
#include "CCFontFreeType.h"

NS_CC_BEGIN

int _getNumGlyphsFittingInSize(std::map<unsigned short int, GlyphDef> &glyphDefs, unsigned short int *strUTF8, Font *pFont, Size *constrainSize, int &outNewSize)
{
    if (!strUTF8)
        return NULL;
    
    float widthWithBBX  =  0.0f;
    float lastWidth     = 0.0f;
    
    // get the string to UTF8
    int numChar = cc_wcslen(strUTF8);
    
    for (int c = 0; c<numChar; ++c)
    {
        widthWithBBX+= (glyphDefs[strUTF8[c]].getRect().size.width + glyphDefs[strUTF8[c]].getPadding());
        
        if (widthWithBBX >= constrainSize->width)
        {
            outNewSize = lastWidth;
            return c;
        }
        
        lastWidth = widthWithBBX;
    }
    
    outNewSize = constrainSize->width;
    return numChar;
}

TextLineDef::TextLineDef(float x, float y, float width, float height) :_x(x), _y(y), _width(width), _height(height)
{
}

TextPageDef::TextPageDef(int pageNum, int width, int height):   _pageNum(pageNum),
                                                                _width(width),
                                                                _height(height),
                                                                _pageData(0),
                                                                _pageTexture(0)
{
}

TextPageDef::~TextPageDef()
{
    int numLines = _lines.size();
    
    for( int c = 0; c<numLines; ++c )
    {
        delete _lines[c];
    }
    
    _lines.clear();
    
    if (_pageData)
    {
        delete [] _pageData;
    }
    
    if (_pageTexture)
    {
        delete _pageTexture;
    }
}

bool TextPageDef::generatePageTexture(bool releasePageData)
{
    if (!_pageData)
        return false;
    
    if (_pageTexture)
    {
        delete _pageTexture;
        _pageTexture = 0;
    }
    
    Size imageSize = CCSizeMake((float)(_width), (float)(_height));
    if( (imageSize.width <=0) || (imageSize.height<=0) )
        return false;
    
    _pageTexture = new Texture2D();
    if (!_pageTexture)
        return false;
    
    bool textureCreated = _pageTexture->initWithData(_pageData, kTexture2DPixelFormat_Default, _width, _height, imageSize);
    
    _pageTexture->setPremultipliedAlpha(true);
    
    // release the page data if requested
    if ( releasePageData && textureCreated )
    {
        delete [] _pageData;
        _pageData = 0;
    }
    
    return textureCreated;
}

void TextPageDef::preparePageTexture(bool releaseRAWData)
{
    generatePageTexture(releaseRAWData);
}

Texture2D *TextPageDef::getPageTexture()
{
    if (!_pageTexture)
    {
        generatePageTexture();
    }
    
    return _pageTexture;
}

TextFontPagesDef::TextFontPagesDef(char *fontName, int fontSize): _fontSize(fontSize)
{
    _fontName = new char[strlen(fontName)+1];
    if (_fontName)
        strcpy(_fontName, fontName);
}

TextFontPagesDef::~TextFontPagesDef()
{
    int numPages = _pages.size();
    for( int c = 0; c<numPages; ++c )
    {
        if (_pages[c])
            delete _pages[c];
    }
    
    if (_fontName)
    {
        delete [] _fontName;
    }
}

TextImage::TextImage(): _font(0), _fontRender(0)
{
}

TextImage::~TextImage()
{
    if (_fontPages)
    {
        delete _fontPages;
    }
    
    if (_font)
    {
        delete _font;
    }
}

bool TextImage::initWithString(const char * pText, int nWidth, int nHeight, const char * pFontName, int nSize, bool releaseRAWData)
{
    // carloX
    bool textIsUTF16 = false;
    
    // create the reference to the system font
    if ( !createFontRef(pFontName, nSize) )
        return false;
    
    // generate the glyphs
    if ( !generateTextGlyphs(pText) )
        return false;

    
    CGSize constrainSize;
    unsigned short int *strUTF16 = 0;
    int stringNumChars;
    
    if ( textIsUTF16 )
    {
        strUTF16 = (unsigned short int *)pText;
        stringNumChars = cc_wcslen(strUTF16);
    }
    else
    {
        // string needs to go to unicode
        strUTF16 = _font->getUTF16Text(pText, stringNumChars);
    }
    
    // tell if the string has been trimmed at least one
    bool stringTrimmedOnce = false;
    
    constrainSize.width  = nWidth;
    constrainSize.height = nHeight;
    
    int   delta           = 0;
    int   currentPage     = 0;
    float currentY        = 0.0;
    
    //carloX
    float lineHeight = _font->getTextWidthAndHeight(pText).height;
    
    // check if at least one line will fit in the texture
    if ( lineHeight > constrainSize.height )
    {
        // we can't even fit one line in this texture
        return false;
    }
    
    // create pages for the font
    _fontPages = new TextFontPagesDef((char *)pFontName, nSize);
    if (!_fontPages)
        return false;
    
    // create the first page (ther is going to be at least one page)
    TextPageDef *currentPageDef = new TextPageDef(currentPage, nWidth, nHeight);
    if ( !currentPageDef )
        return false;
    
    // add the current page
    _fontPages->addPage(currentPageDef);
    
    do {
        
        // choose texture page
        if ( ( currentY + lineHeight ) > constrainSize.height )
        {
            currentY     = 0;
            currentPage += 1;
            
            // create a new page and add
            currentPageDef = new TextPageDef(currentPage, nWidth, nHeight);
            if ( !currentPageDef )
                return false;
            
            _fontPages->addPage(currentPageDef);
        }
        
        
        // get the new fitting string
        Size tempSize;
        tempSize.width  = constrainSize.width;
        tempSize.height = constrainSize.height;

        // figure out how many glyphs fit in this line
        int newLineSize    = 0;
        int numFittingChar = _getNumGlyphsFittingInSize(_textGlyphs, strUTF16, _font, &tempSize, newLineSize);
        
        // crete the temporary new string
        unsigned short int *pTempString = 0;
        pTempString = _font->trimUTF16Text(strUTF16, 0, (numFittingChar - 1));
        
        // create the new line and add to the current page
        TextLineDef *newLine  = new TextLineDef(0.0, currentY, newLineSize, lineHeight);
        if ( !newLine )
            return false;
        
        // add all the glyphs to this line
        addGlyphsToLine(newLine, (const char *)pTempString, true);
        
        // add the line the to current page
        currentPageDef->addLine(newLine);
        
        // can now release the string
        delete [] pTempString;
        
        // create the new string
        int stringLenght = _font->getUTF16TextLenght(strUTF16);
        delta = (stringLenght - numFittingChar);
        
        // there is still some leftover, need to work on it
        if ( delta )
        {
            // create the new string
            unsigned short int *tempS = _font->trimUTF16Text(strUTF16, numFittingChar, (stringLenght - 1));
            
            // a copy of the string has been created
            stringTrimmedOnce = true;
            
            // release the old one
            delete [] strUTF16;
            
            // assign pointer
            strUTF16 = tempS;
        }
        
        // go to next line
        currentY += lineHeight;
        
    } while( delta );
    
    
    if (!textIsUTF16 || stringTrimmedOnce)
        delete [] strUTF16;
    
    // actually create the needed images
    return createImageDataFromPages(_fontPages, releaseRAWData);
}

bool TextImage::createFontRef(const char *fontName, int fontSize)
{
    if (_font)
    {
        delete _font;
        _font = 0;
    }
    
    _font = new FontFreeType();
    if (!_font)
        return false;
    
    // carloX hack fixed font name for now, to be changed
    if( !_font->createFontObject("fonts/arial.ttf", 26))
        return false;
    
    return true;
}

bool TextImage::createFontRender()
{
    if (!_font)
        return false;
    
    if (_fontRender)
    {
        delete _fontRender;
        _fontRender = 0;
    }
    
    _fontRender = new FontRenderFreeType(_font);
    
    if (!_fontRender)
        return false;
    
    return true;
}

bool TextImage::addGlyphsToLine(TextLineDef *line, const char *lineText, bool textIsUTF16)
{
    if (!_font)
        return false;
    
    int numLetters                   = 0;
    unsigned short int *UTF16string  = 0;
    
    if (textIsUTF16)
    {
        UTF16string = (unsigned short int *) lineText;
        numLetters = cc_wcslen(UTF16string);
    }
    else
    {
        UTF16string  = _font->getUTF16Text(lineText, numLetters);
    }
    
    for (int c=0; c<numLetters; ++c)
    {
        _textGlyphs[UTF16string[c]].setCommonHeight(line->getHeight());
        line->addGlyph(_textGlyphs[UTF16string[c]] );
    }
    
    if(!textIsUTF16)
        delete [] UTF16string;
    
    return true;
}

bool TextImage::generateTextGlyphs(const char * pText)
{
    if(!_font)
        return false;
    
    int numGlyphs = 0;
    GlyphDef *pNewGlyphs  = _font->getGlyphsForText(pText, numGlyphs);
    
    if (!pNewGlyphs)
        return false;
    
    for (int c=0; c < numGlyphs; ++c)
        _textGlyphs[pNewGlyphs[c].getUTF8Letter()] = pNewGlyphs[c];
    
    delete [] pNewGlyphs;
    return true;
}

bool TextImage::createImageDataFromPages(TextFontPagesDef *thePages, bool releaseRAWData)
{
    int numPages = thePages->getNumPages();
    if (!numPages)
        return false;
    
    for (int c = 0; c < numPages; ++c)
    {
        unsigned char *pPageData = 0;
        pPageData = preparePageGlyphData(thePages->getPageAt(c), thePages->getFontName(), thePages->getFontSize());
        
        if (pPageData)
        {
            // set the page data
            thePages->getPageAt(c)->setPageData(pPageData);
            
            // crete page texture and relase RAW data
            thePages->getPageAt(c)->preparePageTexture(releaseRAWData);
        }
        else
        {
            return false;
        }
        
    }
    
    return true;
}

unsigned char * TextImage::preparePageGlyphData(TextPageDef *thePage, char *fontName, int fontSize)
{
    if ( !_fontRender )
    {
        createFontRender();
    }
    
    if (_fontRender)
    {
        return _fontRender->preparePageGlyphData(thePage, fontName, fontSize);
    }
    else
    {
        return 0;
    }
}

NS_CC_END












