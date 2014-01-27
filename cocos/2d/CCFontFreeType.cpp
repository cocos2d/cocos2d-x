/****************************************************************************
Copyright (c) 2013      Zynga Inc.
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
****************************************************************************/

#include <stdio.h>
#include <algorithm>

#include "ccUTF8.h"
#include "CCFontFreeType.h"
#include "platform/CCFileUtils.h"
#include "edtaa3func.h"

NS_CC_BEGIN


FT_Library FontFreeType::_FTlibrary;
bool       FontFreeType::_FTInitialized = false;
const int  FontFreeType::DistanceMapSpread = 3;

FontFreeType * FontFreeType::create(const std::string &fontName, int fontSize, GlyphCollection glyphs, const char *customGlyphs)
{
    FontFreeType *tempFont =  new FontFreeType();

    if (!tempFont)
        return nullptr;
    
    tempFont->setCurrentGlyphCollection(glyphs, customGlyphs);
    
    if (!tempFont->createFontObject(fontName, fontSize))
    {
        delete tempFont;
        return nullptr;
    }
    return tempFont;
}

bool FontFreeType::initFreeType()
{
    if (_FTInitialized == false)
    {
        // begin freetype
        if (FT_Init_FreeType( &_FTlibrary ))
            return false;
        
        _FTInitialized = true;
    }
    
    return  _FTInitialized;
}

void FontFreeType::shutdownFreeType()
{
    if (_FTInitialized == true)
    {
        FT_Done_FreeType(_FTlibrary);
        _FTInitialized = false;
    }
}

FT_Library FontFreeType::getFTLibrary()
{
    initFreeType();
    return _FTlibrary;
}

FontFreeType::FontFreeType()
: _fontRef(nullptr)
,_distanceFieldEnabled(false)
{
}

bool FontFreeType::createFontObject(const std::string &fontName, int fontSize)
{
    FT_Face face;

    _ttfData = FileUtils::getInstance()->getDataFromFile(fontName);
    
    if (_ttfData.isNull())
        return false;

    // create the face from the data
    if (FT_New_Memory_Face(getFTLibrary(), _ttfData.getBytes(), _ttfData.getSize(), 0, &face ))
        return false;

    //we want to use unicode
    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE))
        return false;

    // set the requested font size
    int dpi = 72;
    int fontSizePoints = (int)(64.f * fontSize);
    if (FT_Set_Char_Size(face, fontSizePoints, fontSizePoints, dpi, dpi))
        return false;
    
    // store the face globally
    _fontRef = face;
    
    // save font name locally
    _fontName = fontName;
    
    // done and good
    return true;
}

FontFreeType::~FontFreeType()
{
    if (_fontRef)
    {
        FT_Done_Face(_fontRef);
    }
}

FontAtlas * FontFreeType::createFontAtlas()
{
    FontAtlas *atlas = new FontAtlas(*this);
    if (_usedGlyphs != GlyphCollection::DYNAMIC)
    {
        unsigned short* utf16 = cc_utf8_to_utf16(getCurrentGlyphCollection());
        atlas->prepareLetterDefinitions(utf16);
        CC_SAFE_DELETE_ARRAY(utf16);
    }
    this->release();
    return atlas;
}

bool FontFreeType::getBBOXFotChar(unsigned short theChar, Rect &outRect, int &xAdvance) const
{
    if (!_fontRef)
        return false;
    
    // get the ID to the char we need
    int glyph_index = FT_Get_Char_Index(_fontRef, theChar);
    
    if (!glyph_index)
        return false;
    
    // load glyph infos
    if (FT_Load_Glyph(_fontRef, glyph_index, FT_LOAD_DEFAULT))
        return false;
    
    // store result in the passed rectangle
    outRect.origin.x    = _fontRef->glyph->metrics.horiBearingX >> 6;
    outRect.origin.y    = - (_fontRef->glyph->metrics.horiBearingY >> 6);
    outRect.size.width  =   (_fontRef->glyph->metrics.width  >> 6);
    outRect.size.height =   (_fontRef->glyph->metrics.height >> 6);
    
    xAdvance = (static_cast<int>(_fontRef->glyph->metrics.horiAdvance >> 6));

    return true;
}

int * FontFreeType::getHorizontalKerningForTextUTF16(unsigned short *text, int &outNumLetters) const
{
    if (!text)
        return 0;
    
    outNumLetters = cc_wcslen(text);

    if (!outNumLetters)
        return 0;
    
    int *sizes = new int[outNumLetters];
    if (!sizes)
        return 0;
    
    for (int c = 0; c < outNumLetters; ++c)
    {
        if (c < (outNumLetters-1))
            sizes[c] = getHorizontalKerningForChars(text[c], text[c+1]);
        else
            sizes[c] = 0;
    }
    
    return sizes;
}

int  FontFreeType::getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar) const
{
    if (!_fontRef)
        return 0;

    bool hasKerning = FT_HAS_KERNING( _fontRef ) != 0;
    
    if (!hasKerning)
        return 0;
    
    // get the ID to the char we need
    int glyphIndex1 = FT_Get_Char_Index(_fontRef, firstChar);
    
    if (!glyphIndex1)
        return 0;
    
    // get the ID to the char we need
    int glyphIndex2 = FT_Get_Char_Index(_fontRef, secondChar);
    
    if (!glyphIndex2)
        return 0;
    
    FT_Vector kerning;
    
    if (FT_Get_Kerning( _fontRef, glyphIndex1, glyphIndex2,  FT_KERNING_DEFAULT,  &kerning))
        return 0;
    
    return (static_cast<int>(kerning.x >> 6));
}

int FontFreeType::getFontMaxHeight() const
{
    return (static_cast<int>(_fontRef->size->metrics.height >> 6));
}

unsigned char * FontFreeType::getGlyphBitmap(unsigned short theChar, int &outWidth, int &outHeight) const
{
    if (!_fontRef)
        return 0;
    
    if (_distanceFieldEnabled)
    {    
        if (FT_Load_Char(_fontRef,theChar,FT_LOAD_RENDER | FT_LOAD_NO_HINTING | FT_LOAD_NO_AUTOHINT))
            return 0;
    }
    else
    {
        if (FT_Load_Char(_fontRef,theChar,FT_LOAD_RENDER))
            return 0;
    }
    
    outWidth  = _fontRef->glyph->bitmap.width;
    outHeight = _fontRef->glyph->bitmap.rows;
    
    // return the pointer to the bitmap
    return _fontRef->glyph->bitmap.buffer;
}

unsigned char * makeDistanceMap( unsigned char *img, unsigned int width, unsigned int height)
{
    unsigned int pixelAmount = (width + 2 * FontFreeType::DistanceMapSpread) * (height + 2 * FontFreeType::DistanceMapSpread);

    short * xdist = (short *)  malloc( pixelAmount * sizeof(short) );
    short * ydist = (short *)  malloc( pixelAmount * sizeof(short) );
    double * gx   = (double *) calloc( pixelAmount, sizeof(double) );
    double * gy      = (double *) calloc( pixelAmount, sizeof(double) );
    double * data    = (double *) calloc( pixelAmount, sizeof(double) );
    double * outside = (double *) calloc( pixelAmount, sizeof(double) );
    double * inside  = (double *) calloc( pixelAmount, sizeof(double) );
    unsigned int i,j;

    // Convert img into double (data) rescale image levels between 0 and 1
    unsigned int outWidth = width + 2 * FontFreeType::DistanceMapSpread;
    for (i = 0; i < width; ++i)
    {
        for (j = 0; j < height; ++j)
        {
            data[j * outWidth + FontFreeType::DistanceMapSpread + i] = img[j * width + i] / 255.0;
        }
    }

    width += 2 * FontFreeType::DistanceMapSpread;
    height += 2 * FontFreeType::DistanceMapSpread;

    // Transform background (outside contour, in areas of 0's)   
    computegradient( data, width, height, gx, gy);
    edtaa3(data, gx, gy, width, height, xdist, ydist, outside);
    for( i=0; i< pixelAmount; i++)
        if( outside[i] < 0.0 )
            outside[i] = 0.0;

    // Transform foreground (inside contour, in areas of 1's)   
    for( i=0; i< pixelAmount; i++)
        data[i] = 1 - data[i];
    computegradient( data, width, height, gx, gy);
    edtaa3(data, gx, gy, width, height, xdist, ydist, inside);
    for( i=0; i< pixelAmount; i++)
        if( inside[i] < 0.0 )
            inside[i] = 0.0;

    // The bipolar distance field is now outside-inside
    double dist;
    /* Single channel 8-bit output (bad precision and range, but simple) */    
    unsigned char *out = (unsigned char *) malloc( pixelAmount * sizeof(unsigned char) );
    for( i=0; i < pixelAmount; i++)
    {
        dist = outside[i] - inside[i];
        dist = 128.0 - dist*16;
        if( dist < 0 ) dist = 0;
        if( dist > 255 ) dist = 255;
        out[i] = (unsigned char) dist;
    }
    /* Dual channel 16-bit output (more complicated, but good precision and range) */
    /*unsigned char *out = (unsigned char *) malloc( pixelAmount * 3 * sizeof(unsigned char) ); 
    for( i=0; i< pixelAmount; i++)
    {
        dist = outside[i] - inside[i];
        dist = 128.0 - dist*16;
        if( dist < 0.0 ) dist = 0.0;
        if( dist >= 256.0 ) dist = 255.999;
        // R channel is a copy of the original grayscale image
        out[3*i] = img[i];
        // G channel is fraction
        out[3*i + 1] = (unsigned char) ( 256 - (dist - floor(dist)* 256.0 ));
        // B channel is truncated integer part
        out[3*i + 2] = (unsigned char)dist; 
    }*/
    
    free( xdist );
    free( ydist );
    free( gx );
    free( gy );
    free( data );
    free( outside );
    free( inside );

    return out;
}

void FontFreeType::setDistanceFieldEnabled(bool distanceFieldEnabled)
{
    _distanceFieldEnabled = distanceFieldEnabled;
}

bool FontFreeType::renderCharAt(unsigned short int charToRender, int posX, int posY, unsigned char *destMemory, int destSize)
{
    unsigned char *sourceBitmap = 0;
    int sourceWidth  = 0;
    int sourceHeight = 0;

    sourceBitmap = getGlyphBitmap(charToRender, sourceWidth, sourceHeight);

    if (!sourceBitmap)
        return false;

    if (_distanceFieldEnabled)
    {
        unsigned char * out = makeDistanceMap(sourceBitmap,sourceWidth,sourceHeight);

        int iX = posX;
        int iY = posY;

        sourceWidth += 2 * DistanceMapSpread;
        sourceHeight += 2 * DistanceMapSpread;

        for (int y = 0; y < sourceHeight; ++y)
        {
            int bitmap_y = y * sourceWidth;

            for (int x = 0; x < sourceWidth; ++x)
            {    
                /* Dual channel 16-bit output (more complicated, but good precision and range) */
                /*int index = (iX + ( iY * destSize )) * 3;                
                int index2 = (bitmap_y + x)*3;
                destMemory[index] = out[index2];
                destMemory[index + 1] = out[index2 + 1];
                destMemory[index + 2] = out[index2 + 2];*/

                //Single channel 8-bit output 
                destMemory[iX + ( iY * destSize )] = out[bitmap_y + x];

                iX += 1;
            }

            iX  = posX;
            iY += 1;
        }
        free(out);        
        return true;
    }

    int iX = posX;
    int iY = posY;

    for (int y = 0; y < sourceHeight; ++y)
    {
        int bitmap_y = y * sourceWidth;

        for (int x = 0; x < sourceWidth; ++x)
        {
            unsigned char cTemp = sourceBitmap[bitmap_y + x];

            // the final pixel
            destMemory[(iX + ( iY * destSize ) )] = cTemp;

            iX += 1;
        }

        iX  = posX;
        iY += 1;
    }

    //everything good
    return true;
}

NS_CC_END