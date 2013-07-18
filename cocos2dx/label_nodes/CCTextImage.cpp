//
//  CCTextImage.mm
//  TestNewStringStuff
//
//  Created by Carlo Morgantini on 4/9/13.
//
//

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

const char * _getStringInBoundsUsingGlyphSize(std::map<unsigned short int, GlyphDef> &glyphDefs, const char *str, Font *pFont, Size *constrainSize)
{
    
    Size tmp            = pFont->getTextWidthAndHeight(str);
    float widthWithBBX  =  0.0f;
    
    // get the string to UTF8
    int numChar = 0;
    unsigned short int *strUTF8 = pFont->getUTF8Text(str, numChar);
    
    if (!strUTF8)
        return NULL;
    
    for (int c = 0; c<numChar; ++c)
    {
        widthWithBBX+= (glyphDefs[strUTF8[c]].getRect().size.width + glyphDefs[strUTF8[c]].getPadding());
    }
    
    // not needed anymore
    delete [] strUTF8;
    
    float maxWidth = std::max(tmp.width, widthWithBBX);
    
    if ( maxWidth < constrainSize->width )
    {
        return str;
    }
    else
    {
        // trim the string
        const char *pNewString = pFont->trimUTF8Text(str, 0, (numChar - 2));
        if (!pNewString)
            return 0;
        
        // try again with one less character
        return _getStringInBoundsUsingGlyphSize(glyphDefs, pNewString, pFont, constrainSize);
    }
}

TextImage::TextImage(): _font(0), _fontRender(0), _fontNew(0), _fontRenderNew(0)
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


bool TextImage::initWithStringNew(const char * pText, int nWidth, int nHeight, const char * pFontName, int nSize, bool textIsUTF16, bool releaseRAWData)
{
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
        strUTF16 = _fontNew->getUTF8Text(pText, stringNumChars);
    }
    
    // tell if the string has been trimmed at least one
    bool stringTrimmedOnce = false;
    
    constrainSize.width  = nWidth;
    constrainSize.height = nHeight;
    
    // pointer to the original input stream
    //const char *inputString = pText;
    
    int   delta           = 0;
    int   currentPage     = 0;
    float currentY        = 0.0;
    
    //carloX
    float lineHeight = _fontNew->getTextWidthAndHeight(pText).height;
    
    
    // check if at least one line will fit in the texture
    if ( lineHeight > constrainSize.height )
    {
        // we can't even fit one line in this texture
        return false;
    }
    
    // create pages for the font
    _fontPagesNew = new TextFontPagesDef((char *)pFontName, nSize);
    if (!_fontPagesNew)
        return false;
    
    // create the first page (ther is going to be at least one page)
    TextPageDef *currentPageDef = new TextPageDef(currentPage, nWidth, nHeight);
    if ( !currentPageDef )
        return false;
    
    // add the current page
    _fontPagesNew->addPage(currentPageDef);
    
    
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
            
            _fontPagesNew->addPage(currentPageDef);
        }
        
        
        // get the new fitting string
        Size tempSize;
        tempSize.width  = constrainSize.width;
        tempSize.height = constrainSize.height;
        
        //const char *pNewString = _getStringInBoundsUsingGlyphSizeNew(_textGlyphsNew, inputString, _fontNew, &tempSize);
        
        // figure out how many glyphs fit in this line
        int newLineSize    = 0;
        int numFittingChar = _getNumGlyphsFittingInSize(_textGlyphsNew, strUTF16, _fontNew, &tempSize, newLineSize);
        
        // crete the temporary new string
        unsigned short int *pTempString = 0;
        pTempString = _fontNew->trimUTF16Text(strUTF16, 0, (numFittingChar - 1));
        
        // create the new line and add to the current page
        TextLineDef *newLine  = new TextLineDef(0.0, currentY, newLineSize, lineHeight);
        if ( !newLine )
            return false;
        
        // add all the glyphs to this line
        addGlyphsToLineNew(newLine, (const char *)pTempString, true);
        
        // add the line the to current page
        currentPageDef->addLine(newLine);
        
        // can now release the string
        delete [] pTempString;
        
        // create the new string
        int stringLenght = _fontNew->getUTF16TextLenght(strUTF16);
        delta = (stringLenght - numFittingChar);
        
        // there is still some leftover, need to work on it
        if ( delta )
        {
            // create the new string
            unsigned short int *tempS = _fontNew->trimUTF16Text(strUTF16, numFittingChar, (stringLenght - 1));
            
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
    return createImageDataFromPagesNew(_fontPagesNew, releaseRAWData);
    
    
    return true;
    
}

bool TextImage::initWithString(const char * pText, int nWidth, int nHeight, const char * pFontName, int nSize, bool releaseRAWData)
{
    // create the reference to the system font
    if ( !createFontRef(pFontName, nSize) )
        return false;
    
    // generate the glyphs
    if ( !generateTextGlyphs(pText) )
        return false;
    
    
    // carloX new stuff
    
    initWithStringNew(pText, nWidth, nHeight, pFontName, nSize, false, releaseRAWData);
    
    // end new stuff
    
    
    CGSize constrainSize;
    constrainSize.width  = nWidth;
    constrainSize.height = nHeight;
    
    // pointer to the original input stream
    const char *inputString = pText;
    
    int   delta           = 0;
    int   currentPage     = 0;
    float currentY        = 0.0;
    
    float lineHeight      = _font->getTextWidthAndHeight(pText).height;
    
    // check if at least one line will fit in the texture
    if (lineHeight > constrainSize.height)
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
        const char *pNewString = _getStringInBoundsUsingGlyphSize(_textGlyphs, inputString, _font, &tempSize);
        
        // get the new string width
        float newStringWidth = _font->getTextWidthAndHeight(pNewString).width;
        
        // create the new line and add to the current page
        TextLineDef *newLine  = new TextLineDef(0.0, currentY, newStringWidth, lineHeight);
        if ( !newLine )
            return false;
        
        // add all the glyphs to this line
        
        //
        addGlyphsToLine(newLine, pNewString);
        
        // add the line the to current page
        currentPageDef->addLine(newLine);
        
        // get the remaining string
        delta = _font->getUTF8TextLenght(inputString) - _font->getUTF8TextLenght(pNewString);
        
        if (delta)
        {
            int startIndex = _font->getUTF8TextLenght(pNewString);
            inputString    = _font->trimUTF8Text(inputString, startIndex, startIndex + (delta - 1));
        }
        
        // go to next line
        currentY += lineHeight;
        
        
    } while( delta );
    
    
    // actually create the needed images
    return createImageDataFromPages(_fontPages, releaseRAWData);
}

bool TextImage::createFontRef(const char *fontName, int fontSize)
{
    //carloX new stuff
    
    if (_fontNew)
    {
        delete _fontNew;
        _fontNew = 0;
    }
    
    _fontNew = new FontFreeType();
    if (!_fontNew)
        return false;
    
    
    // fixed font name for now, to be changed
    //if( !_fontNew->createFontObject("fonts/Marker Felt.ttf", 20))
    
    if( !_fontNew->createFontObject("fonts/arial.ttf", 26))
        return false;
    
    
    // end carloX new stuff
    
    
    
    if (_font)
    {
        delete _font;
        _font = 0;
    }
    
    // carloX 
    _font = new FontIOS();
    
    if (_font)
        return _font->createFontObject(std::string(fontName), fontSize);
    else
        return false;
}

bool TextImage::createFontRenderNew()
{
    if (!_fontNew)
        return false;
    
    if (_fontRenderNew)
    {
        delete _fontRenderNew;
        _fontRenderNew = 0;
    }
    
    _fontRenderNew = new FontRenderFreeType(_fontNew);
    
    if (!_fontRenderNew)
        return false;
    
    return true;
}

bool TextImage::createFontRender()
{
    if (_fontRender)
    {
        delete _fontRender;
        _fontRender = 0;
    }
    
    // carloX
    _fontRender = new FontRenderIOS(_font);
    
    return true;
}

bool TextImage::addGlyphsToLineNew(TextLineDef *line, const char *lineText, bool textIsUTF16)
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
        UTF16string  = _fontNew->getUTF8Text(lineText, numLetters);
    }
    
    for (int c=0; c<numLetters; ++c)
    {
        _textGlyphsNew[UTF16string[c]].setCommonHeight(line->getHeight());
        line->addGlyph(_textGlyphsNew[UTF16string[c]] );
    }
    
    if(!textIsUTF16)
        delete [] UTF16string;
    
    return true;
}

bool TextImage::addGlyphsToLine(TextLineDef *line, const char *lineText, bool textIsUTF16)
{
    if (!_font)
        return false;
    
    int numLetters                  = 0;
    unsigned short int *UTF16string  = 0;
    
    if (textIsUTF16)
    {
        UTF16string = (unsigned short int *) lineText;
        numLetters = cc_wcslen(UTF16string);
    }
    else
    {
        UTF16string  = _font->getUTF8Text(lineText, numLetters);
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
    
    int numGlyphs = 0;
    
    // carloX new stuff
    
    if(!_fontNew)
        return false;
    
    
    GlyphDef *pNewGlyphs  = _fontNew->getGlyphsForText(pText, numGlyphs);
    
    if (!pNewGlyphs)
        return false;
    
    for (int c=0; c < numGlyphs; ++c)
    {
        _textGlyphsNew[pNewGlyphs[c].getUTF8Letter()] = pNewGlyphs[c];
    }
    
    
    delete [] pNewGlyphs;
    
    // end new stuff
    
    
    if (!_font)
        return false;
    
    
    GlyphDef *pGlyphs = _font->getGlyphsForText(pText, numGlyphs);
    
    if (!pGlyphs || !numGlyphs)
        return false;
    
    for (int c=0; c<numGlyphs; ++c)
    {
        _textGlyphs[pGlyphs[c].getUTF8Letter()] = pGlyphs[c];
    }
    
    delete [] pGlyphs;
    return true;
}


bool TextImage::createImageDataFromPagesNew(TextFontPagesDef *thePages, bool releaseRAWData)
{
    int numPages = thePages->getNumPages();
    if (!numPages)
        return false;
    
    for (int c = 0; c < numPages; ++c)
    {
        unsigned char *pPageData = 0;
        pPageData = preparePageGlyphDataNew(thePages->getPageAt(c), thePages->getFontName(), thePages->getFontSize());
        
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

unsigned char * TextImage::preparePageGlyphDataNew(TextPageDef *thePage, char *fontName, int fontSize)
{
    if ( !_fontRenderNew )
    {
        createFontRenderNew();
    }
    
    if (_fontRenderNew)
    {
        return _fontRenderNew->preparePageGlyphData(thePage, fontName, fontSize);
    }
    else
    {
        return 0;
    }
}

unsigned char * TextImage::preparePageGlyphData(TextPageDef *thePage, char *fontName, int fontSize)
{
    // crate the font renderer if needed
    if (!_fontRender)
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

bool TextImage::debugSaveToFile(const char *pszFilePath, bool bIsToRGB)
{
    /* TO DO 
    if ( (!mFontPages) || (mFontPages->getNumPages() == 0))
        return false;
    
    bool saveToPNG = false;
    bool needToCopyPixels = false;
    std::string filePath(pszFilePath);
    if (std::string::npos != filePath.find(".png"))
    {
        saveToPNG = true;
    }
    
    int bitsPerComponent    = 8;
    int bitsPerPixel        = 32;
    
    if ((! saveToPNG) || bIsToRGB)
    {
        bitsPerPixel = 24;
    }
    
    int pageWidth  = mFontPages->getPageAt(0)->getWidth();
    int pageHeight = mFontPages->getPageAt(0)->getHeight();
    
    
    int bytesPerRow    = (bitsPerPixel/8) * pageWidth;
    int myDataLength = bytesPerRow * pageHeight;
    
    for(int cPages = 0; cPages<mFontPages->getNumPages(); ++cPages)
    {
        TextPageDef *pCurrentPage = mFontPages->getPageAt(cPages);
        if(!pCurrentPage)
            return false;
        
        
        unsigned char *pixels    = pCurrentPage->getPageData();
        
        // make data provider with data.
        CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
        if (saveToPNG)
        {
            bitmapInfo |= kCGImageAlphaPremultipliedLast;
        }
        
        CGDataProviderRef provider        = CGDataProviderCreateWithData(NULL, pixels, myDataLength, NULL);
        CGColorSpaceRef colorSpaceRef    = CGColorSpaceCreateDeviceRGB();
        CGImageRef iref                    = CGImageCreate(pageWidth, pageHeight,
                                                           bitsPerComponent, bitsPerPixel, bytesPerRow,
                                                           colorSpaceRef, bitmapInfo, provider,
                                                           NULL, false,
                                                           kCGRenderingIntentDefault);
        
        UIImage* image                    = [[UIImage alloc] initWithCGImage:iref];
        
        CGImageRelease(iref);
        CGColorSpaceRelease(colorSpaceRef);
        CGDataProviderRelease(provider);
        
        NSData *data;
        
        if (saveToPNG)
        {
            data = UIImagePNGRepresentation(image);
        }
        else
        {
            data = UIImageJPEGRepresentation(image, 1.0f);
        }
        
        char tempString[1000];
        sprintf(tempString, "%d", cPages);
        std::string couterString(tempString);
        std::string finalFileName = couterString + pszFilePath;
        
        [data writeToFile:[NSString stringWithUTF8String:finalFileName.c_str()] atomically:YES];
        
        [image release];
        
        if (needToCopyPixels)
        {
            delete [] pixels;
        }
        
    }
    
    return true;
    */
    
    return false;
}


NS_CC_END












