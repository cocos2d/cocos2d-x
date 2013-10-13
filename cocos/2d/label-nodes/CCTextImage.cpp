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
#include "CCTextImage.h"
#include "CCFontFreeType.h"
#include "CCFont.h"

NS_CC_BEGIN


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
        _pageTexture->release();
    }
}

bool TextPageDef::generatePageTexture(bool releasePageData)
{
    if (!_pageData)
        return false;
    
    if (_pageTexture)
    {
        _pageTexture->release();
        _pageTexture = 0;
    }
    
    Size imageSize = Size((float)(_width), (float)(_height));
    if((imageSize.width <= 0) || (imageSize.height <= 0))
        return false;
    
    _pageTexture = new Texture2D();
    if (!_pageTexture)
        return false;
    
    int  dataLenght     = (_width * _height * 4);
    bool textureCreated = _pageTexture->initWithData(_pageData, dataLenght, Texture2D::PixelFormat::RGBA8888, _width, _height, imageSize);
    
    // release the page data if requested
    if (releasePageData && textureCreated)
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

TextFontPagesDef::TextFontPagesDef()
{
}

TextFontPagesDef::~TextFontPagesDef()
{
    int numPages = _pages.size();
    for( int c = 0; c < numPages; ++c )
    {
        if (_pages[c])
            delete _pages[c];
    }
}

TextImage::TextImage(): _font(0), _fontPages(0)
{
}

TextImage::~TextImage()
{
    if (_fontPages)
        delete _fontPages;
    
    if (_font)
        _font->release();
}

bool TextImage::initWithString(const char *text, int width, int height, cocos2d::Font* font, bool releaseRAWData)
{
    bool textIsUTF16 = false;
    
    if (_font)
    {
        _font->release();
        _font = 0;
    }
    
    // carloX
    _font = font;
    
    // generate the glyphs for the requested text (glyphs are latter's bounding boxes)
    if (!generateTextGlyphs(text))
        return false;
    
    Size constrainSize;
    unsigned short int *strUTF16 = 0;
    
    int stringNumChars;
    if (textIsUTF16)
    {
        strUTF16       = (unsigned short int *)text;
        stringNumChars = cc_wcslen(strUTF16);
    }
    else
    {
        // string needs to go to unicode
        strUTF16 = _font->getUTF16Text(text, stringNumChars);
    }
    
    if (!strUTF16 || !stringNumChars)
        return false;
    
    // create all the needed pages
    if (!createPageDefinitions(strUTF16, width, height, _font->getFontMaxHeight()))
        return false;
    
    // release the original string if needed
    if (!textIsUTF16)
        delete [] strUTF16;
    
    // actually create the needed images
    return createImageDataFromPages(_fontPages, releaseRAWData);
    
    return true;
}

bool TextImage::createPageDefinitions(unsigned short int *inText, int imageWidth, int imageHeight, int lineHeight)
{
    bool  needToReleaseText = false;
    int   delta             = 0;
    int   currentPage       = 0;
    float currentY          = 0.0;
    
    //
    unsigned short int *strUTF16 = inText;
    
    if (_fontPages)
        delete _fontPages;
    
    // create pages for the font
    _fontPages = new TextFontPagesDef();
    if (!_fontPages)
        return false;
    
    // create the first page (ther is going to be at least one page)
    TextPageDef *currentPageDef = new TextPageDef(currentPage, imageWidth, imageHeight);
    if (!currentPageDef)
        return false;
    
    // add the current page
    _fontPages->addPage(currentPageDef);
    
    // work out creating pages
    
    do {
        
        // choose texture page
        if ((currentY + lineHeight) > imageHeight)
        {
            currentY     = 0;
            currentPage += 1;
            
            // create a new page and add
            currentPageDef = new TextPageDef(currentPage, imageWidth, imageHeight);
            if (!currentPageDef)
                return false;
            
            _fontPages->addPage(currentPageDef);
        }
        
        // get the new fitting string
        Size tempSize;
        tempSize.width  = imageWidth;
        tempSize.height = imageHeight;
        
        // figure out how many glyphs fit in this line
        int newLineSize    = 0;
        int numFittingChar = getNumGlyphsFittingInSize(_textGlyphs, strUTF16, _font, &tempSize, newLineSize);
        
        // crete the temporary new string
        unsigned short int *pTempString = 0;
        pTempString = _font->trimUTF16Text(strUTF16, 0, (numFittingChar - 1));
        
        // create the new line and add to the current page
        TextLineDef *newLine  = new TextLineDef(0.0, currentY, newLineSize, lineHeight);
        if (!newLine)
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
        if (delta)
        {
            // create the new string
            unsigned short int *tempS = _font->trimUTF16Text(strUTF16, numFittingChar, (stringLenght - 1));
            
            if (needToReleaseText)
                delete [] strUTF16;
            
            // a copy of the string has been created, so next time I'll need to release it
            needToReleaseText = true;
            
            // assign pointer
            strUTF16 = tempS;
        }
        
        // go to next line
        currentY += lineHeight;
        
    } while(delta);
    
    if (needToReleaseText)
        delete [] strUTF16;
    
    return true;
}

int TextImage::getNumGlyphsFittingInSize(std::map<unsigned short int, GlyphDef> &glyphDefs, unsigned short int *strUTF8, Font *pFont, Size *constrainSize, int &outNewSize)
{
    if (!strUTF8)
        return 0;
    
    float widthWithBBX  =  0.0f;
    float lastWidth     =  0.0f;
    
    // get the string to UTF8
    int numChar = cc_wcslen(strUTF8);
    
    for (int c = 0; c < numChar; ++c)
    {
        widthWithBBX += (glyphDefs[strUTF8[c]].getRect().size.width + glyphDefs[strUTF8[c]].getPadding());
        
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

bool TextImage::addGlyphsToLine(TextLineDef *line, const char *lineText, bool textIsUTF16)
{
    if (!_font)
        return false;
    
    int numLetters                   = 0;
    unsigned short int *UTF16string  = 0;
    
    if (textIsUTF16)
    {
        UTF16string = (unsigned short int *)lineText;
        numLetters = cc_wcslen(UTF16string);
    }
    else
    {
        UTF16string  = _font->getUTF16Text(lineText, numLetters);
    }
    
    for (int c = 0; c < numLetters; ++c)
    {
        _textGlyphs[UTF16string[c]].setCommonHeight(line->getHeight());
        line->addGlyph(_textGlyphs[UTF16string[c]] );
    }
    
    if(!textIsUTF16)
        delete [] UTF16string;
    
    return true;
}

bool TextImage::generateTextGlyphs(const char * text)
{
    if (!_font)
        return false;
    
    int numGlyphs = 0;
    GlyphDef *newGlyphs  = _font->getGlyphDefintionsForText(text, numGlyphs);
    
    if (!newGlyphs)
        return false;
    
    if (!_textGlyphs.empty())
        _textGlyphs.clear();
    
    for (int c = 0; c < numGlyphs; ++c)
        _textGlyphs[newGlyphs[c].getUTF8Letter()] = newGlyphs[c];
    
    delete [] newGlyphs;
    return true;
}

bool TextImage::createImageDataFromPages(TextFontPagesDef *thePages, bool releaseRAWData)
{
    int numPages = thePages->getNumPages();
    if (!numPages)
        return false;
    
    for (int c = 0; c < numPages; ++c)
    {
        unsigned char *pageData = 0;
        pageData = preparePageGlyphData(thePages->getPageAt(c));
        
        if (pageData)
        {
            // set the page data
            thePages->getPageAt(c)->setPageData(pageData);
            
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

unsigned char * TextImage::preparePageGlyphData(TextPageDef *thePage)
{
    return renderGlyphData(thePage);
}

unsigned char * TextImage::renderGlyphData(TextPageDef *thePage)
{
    if (!thePage)
        return 0;
    
    if (!_font)
        return 0;
    
    if (thePage->getNumLines() == 0)
        return NULL;
    
    int pageWidth  = thePage->getWidth();
    int pageHeight = thePage->getHeight();
    
    // prepare memory and clean to 0
    int sizeInBytes     = (pageWidth * pageHeight * 4);
    unsigned char* data = new unsigned char[sizeInBytes];
    
    if (!data)
        return 0;
    
    memset(data, 0, sizeInBytes);
    
    int numLines = thePage->getNumLines();
    
    for (int c = 0; c < numLines; ++c)
    {
        TextLineDef *currentLine   = thePage->getLineAt(c);
        
        float origX         = _font->getLetterPadding();
        float origY         = currentLine->getY();
        
        int numGlyphToRender = currentLine->getNumGlyph();
        
        for (int cglyph = 0; cglyph < numGlyphToRender; ++cglyph)
        {
            GlyphDef currGlyph      = currentLine->getGlyphAt(cglyph);
            renderCharAt(currGlyph.getUTF8Letter(), origX, origY, data, pageWidth);
            origX += (currGlyph.getRect().size.width + _font->getLetterPadding());
        }
    }
    
#ifdef _DEBUG_FONTS_
    static int counter = 0;
    char outFilename[512];
    sprintf(outFilename,"testIMG%d", counter);
    ++counter;
    Image *image = new Image;
    image->initWithRawData(data, (pageWidth * pageWidth * 4), 1024, 1024, 8, false);
    image->saveToFile(outFilename);
#endif
    
    // we are done here
    return data;
}

bool TextImage::renderCharAt(unsigned short int charToRender, int posX, int posY, unsigned char *destMemory, int destSize)
{
    if (!_font)
        return false;
    
    unsigned char *sourceBitmap = 0;
    int sourceWidth  = 0;
    int sourceHeight = 0;
    
    // get the glyph's bitmap
    sourceBitmap = _font->getGlyphBitmap(charToRender, sourceWidth, sourceHeight);
    
    if (!sourceBitmap)
        return false;
    
    int iX = posX;
    int iY = posY;
    
    for (int y = 0; y < sourceHeight; ++y)
    {
        int bitmap_y = y * sourceWidth;
        
        for (int x = 0; x < sourceWidth; ++x)
        {
            unsigned char cTemp = sourceBitmap[bitmap_y + x];
            
            // the final pixel
            int iTemp = cTemp << 24 | cTemp << 16 | cTemp << 8 | cTemp;
            *(int*) &destMemory[(iX + ( iY * destSize ) ) * 4] = iTemp;
            
            iX += 1;
        }
        
        iX  = posX;
        iY += 1;
    }
    
    //everything good
    return true;
}

NS_CC_END












