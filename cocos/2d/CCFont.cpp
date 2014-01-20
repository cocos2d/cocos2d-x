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

#include "CCFont.h"
#include "ccUTF8.h"

#include "CCFontFNT.h"
#include "CCFontFreeType.h"
#include "CCFontCharMap.h"
#include "edtaa3func.h"

NS_CC_BEGIN

const int Font::DistanceMapSpread = 3;

const char * Font::_glyphASCII = "\"!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ ";

const char * Font::_glyphNEHE =  "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ";


Font::Font() : 
_usedGlyphs(GlyphCollection::ASCII)
, _customGlyphs(nullptr)
,_distanceFieldEnabled(false)
{
}

const char * Font::getGlyphCollection(GlyphCollection glyphs) const
{
    switch (glyphs)
    {
        case GlyphCollection::NEHE:
            return _glyphNEHE;
            break;
            
        case GlyphCollection::ASCII:
            return _glyphASCII;
            break;
            
        default:
            return 0;
            break;
    }
}

void Font::setCurrentGlyphCollection(GlyphCollection glyphs, const char *customGlyphs)
{
    if (_customGlyphs)
        delete [] _customGlyphs;
    
    switch (glyphs)
    {
        case GlyphCollection::NEHE:
            _customGlyphs = 0;
            break;
            
        case GlyphCollection::ASCII:
            _customGlyphs = 0;
            break;
            
        default:
            if (customGlyphs)
            {
                size_t lenght = strlen(customGlyphs);
                _customGlyphs = new char [lenght + 2];
                memcpy(_customGlyphs, customGlyphs, lenght);

                _customGlyphs[lenght]   = 0;
                _customGlyphs[lenght+1] = 0;
            }           
            
            break;
    }
}

const char * Font::getCurrentGlyphCollection() const
{
    if (_customGlyphs)
    {
        return _customGlyphs;
    }
    else
    {
        return getGlyphCollection(_usedGlyphs);
    }
}

Font* Font::createWithTTF(const std::string& fntName, int fontSize, GlyphCollection glyphs, const char *customGlyphs)
{
    return FontFreeType::create(fntName, fontSize, glyphs, customGlyphs);
}

Font* Font::createWithFNT(const std::string& fntFilePath)
{
   return FontFNT::create(fntFilePath);
}

Font* Font::createWithCharMap(const std::string& plistFile)
{
    return FontCharMap::create(plistFile);
}

Font* Font::createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    return FontCharMap::create(texture,itemWidth,itemHeight,startCharMap);
}

Font* Font::createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    return FontCharMap::create(charMapFile,itemWidth,itemHeight,startCharMap);
}

unsigned char * Font::makeDistanceMap( unsigned char *img, unsigned int width, unsigned int height)
{
    unsigned int pixelAmount = (width + 2 * DistanceMapSpread) * (height + 2 * DistanceMapSpread);

    short * xdist = (short *)  malloc( pixelAmount * sizeof(short) );
    short * ydist = (short *)  malloc( pixelAmount * sizeof(short) );
    double * gx   = (double *) calloc( pixelAmount, sizeof(double) );
    double * gy      = (double *) calloc( pixelAmount, sizeof(double) );
    double * data    = (double *) calloc( pixelAmount, sizeof(double) );
    double * outside = (double *) calloc( pixelAmount, sizeof(double) );
    double * inside  = (double *) calloc( pixelAmount, sizeof(double) );
    unsigned int i,j;

    // Convert img into double (data) rescale image levels between 0 and 1
    unsigned int outWidth = width + 2 * DistanceMapSpread;
    for (i = 0; i < width; ++i)
    {
        for (j = 0; j < height; ++j)
        {
            data[j * outWidth + DistanceMapSpread + i] = img[j * width + i] / 255.0;
        }
    }

    width += 2 * DistanceMapSpread;
    height += 2 * DistanceMapSpread;

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

void Font::setDistanceFieldEnabled(bool distanceFieldEnabled)
{
    _distanceFieldEnabled = distanceFieldEnabled;
}

bool Font::renderCharAt(unsigned short int charToRender, int posX, int posY, unsigned char *destMemory, int destSize)
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

unsigned short int  * Font::getUTF16Text(const char *text, int &outNumLetters) const
{
    unsigned short* utf16String = cc_utf8_to_utf16(text);
    
    if(!utf16String)
        return 0;
    
    outNumLetters = cc_wcslen(utf16String);
    return utf16String;
}

int Font::getUTF16TextLenght(unsigned short int *text) const
{
     return cc_wcslen(text);
}

unsigned short int  * Font::trimUTF16Text(unsigned short int *text, int newBegin, int newEnd) const
{
    if ( newBegin < 0 || newEnd <= 0 )
        return 0;
    
    if ( newBegin >= newEnd )
        return 0;
    
    if (newEnd >= cc_wcslen(text))
        return 0;
    
    int newLenght = newEnd - newBegin + 2;
    unsigned short* trimmedString = new unsigned short[newLenght];
    
    for(int c = 0; c < (newLenght - 1); ++c)
    {
        trimmedString[c] = text[newBegin + c];
    }
    
    // last char
    trimmedString[newLenght-1] = 0x0000;
    
    // done
    return trimmedString;
}

Rect Font::getRectForChar(unsigned short theChar) const
{
    return Rect::ZERO;
}

NS_CC_END


