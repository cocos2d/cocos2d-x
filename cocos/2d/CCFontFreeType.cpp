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

#include "2d/CCFontFreeType.h"

#include <stdio.h>
#include <algorithm>
#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include "platform/CCFileUtils.h"
#include "edtaa3func.h"
#include FT_BBOX_H

NS_CC_BEGIN


FT_Library FontFreeType::_FTlibrary;
bool       FontFreeType::_FTInitialized = false;
const int  FontFreeType::DistanceMapSpread = 3;

typedef struct _DataRef
{
    Data data;
    unsigned int referenceCount;
}DataRef;

static std::unordered_map<std::string, DataRef> s_cacheFontData;

FontFreeType * FontFreeType::create(const std::string &fontName, int fontSize, GlyphCollection glyphs, const char *customGlyphs,bool distanceFieldEnabled /* = false */,int outline /* = 0 */)
{
    FontFreeType *tempFont =  new FontFreeType(distanceFieldEnabled,outline);

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

FontFreeType::FontFreeType(bool distanceFieldEnabled /* = false */,int outline /* = 0 */)
: _fontRef(nullptr)
,_distanceFieldEnabled(distanceFieldEnabled)
,_outlineSize(outline)
,_stroker(nullptr)
{
    if (_outlineSize > 0)
    {
        _outlineSize *= CC_CONTENT_SCALE_FACTOR();
        FT_Stroker_New(FontFreeType::getFTLibrary(), &_stroker);
        FT_Stroker_Set(_stroker,
            (int)(_outlineSize * 64),
            FT_STROKER_LINECAP_ROUND,
            FT_STROKER_LINEJOIN_ROUND,
            0);
    }
}

bool FontFreeType::createFontObject(const std::string &fontName, int fontSize)
{
    FT_Face face;
    // save font name locally
    _fontName = fontName;

    auto it = s_cacheFontData.find(fontName);
    if (it != s_cacheFontData.end())
    {
        (*it).second.referenceCount += 1;
    }
    else
    {
        s_cacheFontData[fontName].referenceCount = 1;
        s_cacheFontData[fontName].data = FileUtils::getInstance()->getDataFromFile(fontName);    

        if (s_cacheFontData[fontName].data.isNull())
        {
            return false;
        }
    }

    if (FT_New_Memory_Face(getFTLibrary(), s_cacheFontData[fontName].data.getBytes(), s_cacheFontData[fontName].data.getSize(), 0, &face ))
        return false;
    
    //we want to use unicode
    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE))
        return false;

    // set the requested font size
    int dpi = 72;
    int fontSizePoints = (int)(64.f * fontSize * CC_CONTENT_SCALE_FACTOR());
    if (FT_Set_Char_Size(face, fontSizePoints, fontSizePoints, dpi, dpi))
        return false;
    
    // store the face globally
    _fontRef = face;
    
    // done and good
    return true;
}

FontFreeType::~FontFreeType()
{
    if (_stroker)
    {
        FT_Stroker_Done(_stroker);
    }
    if (_fontRef)
    {
        FT_Done_Face(_fontRef);
    }

    s_cacheFontData[_fontName].referenceCount -= 1;
    if (s_cacheFontData[_fontName].referenceCount == 0)
    {
        s_cacheFontData.erase(_fontName);
    }
}

FontAtlas * FontFreeType::createFontAtlas()
{
    FontAtlas *atlas = new FontAtlas(*this);
    if (_usedGlyphs != GlyphCollection::DYNAMIC)
    {
        std::u16string utf16;
        if (StringUtils::UTF8ToUTF16(getCurrentGlyphCollection(), utf16))
        {
            atlas->prepareLetterDefinitions(utf16);
        }
    }
    this->release();
    return atlas;
}

int * FontFreeType::getHorizontalKerningForTextUTF16(const std::u16string& text, int &outNumLetters) const
{
    if (!_fontRef)
        return nullptr;
    
    outNumLetters = static_cast<int>(text.length());

    if (!outNumLetters)
        return nullptr;
    
    int *sizes = new int[outNumLetters];
    if (!sizes)
        return nullptr;
    memset(sizes,0,outNumLetters * sizeof(int));

    bool hasKerning = FT_HAS_KERNING( _fontRef ) != 0;
    if (hasKerning)
    {
        for (int c = 1; c < outNumLetters; ++c)
        {
            sizes[c] = getHorizontalKerningForChars(text[c-1], text[c]);
        }
    }
    
    return sizes;
}

int  FontFreeType::getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar) const
{
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

int FontFreeType::getFontAscender() const
{
    return (static_cast<int>(_fontRef->size->metrics.ascender >> 6));
}

unsigned char* FontFreeType::getGlyphBitmap(unsigned short theChar, long &outWidth, long &outHeight, Rect &outRect,int &xAdvance)
{
    bool invalidChar = true;
    unsigned char * ret = nullptr;

    do 
    {
        if (!_fontRef)
            break;

        auto glyphIndex = FT_Get_Char_Index(_fontRef, theChar);
        if(!glyphIndex)
            break;

        if (_distanceFieldEnabled)
        {
            if (FT_Load_Glyph(_fontRef,glyphIndex,FT_LOAD_RENDER | FT_LOAD_NO_HINTING | FT_LOAD_NO_AUTOHINT))
                break;
        }
        else
        {
            if (FT_Load_Glyph(_fontRef,glyphIndex,FT_LOAD_RENDER))
                break;
        }

        outRect.origin.x    = _fontRef->glyph->metrics.horiBearingX >> 6;
        outRect.origin.y    = - (_fontRef->glyph->metrics.horiBearingY >> 6);
        outRect.size.width  =   (_fontRef->glyph->metrics.width  >> 6);
        outRect.size.height =   (_fontRef->glyph->metrics.height >> 6);

        xAdvance = (static_cast<int>(_fontRef->glyph->metrics.horiAdvance >> 6));

        outWidth  = _fontRef->glyph->bitmap.width;
        outHeight = _fontRef->glyph->bitmap.rows;
        ret = _fontRef->glyph->bitmap.buffer;

        if (_outlineSize > 0)
        {
            auto copyBitmap = new unsigned char[outWidth * outHeight];
            memcpy(copyBitmap,ret,outWidth * outHeight * sizeof(unsigned char));

            FT_BBox bbox;
            auto outlineBitmap = getGlyphBitmapWithOutline(theChar,bbox);
            if(outlineBitmap == nullptr)
            {
                ret = nullptr;
                delete [] copyBitmap;
                break;
            }

            auto outlineWidth = (bbox.xMax - bbox.xMin)>>6;
            auto outlineHeight = (bbox.yMax - bbox.yMin)>>6;

            auto blendWidth = outlineWidth > outWidth ? outlineWidth : outWidth;
            auto blendHeight = outlineHeight > outHeight ? outlineHeight : outHeight;

            long index,index2;
            auto blendImage = new unsigned char[blendWidth * blendHeight * 2];
            memset(blendImage, 0, blendWidth * blendHeight * 2);

            auto px = (blendWidth - outlineWidth) / 2;
            auto py = (blendHeight - outlineHeight) / 2;
            for (int x = 0; x < outlineWidth; ++x)
            {
                for (int y = 0; y < outlineHeight; ++y)
                {
                    index = px + x + ( (py + y) * blendWidth );
                    index2 = x + (y * outlineWidth);
                    blendImage[2 * index] = outlineBitmap[index2];
                }
            }

            px = (blendWidth - outWidth) / 2;
            py = (blendHeight - outHeight) / 2;
            for (int x = 0; x < outWidth; ++x)
            {
                for (int y = 0; y < outHeight; ++y)
                {
                    index = px + x + ( (y + py) * blendWidth );
                    index2 = x + (y * outWidth);
                    blendImage[2 * index + 1] = copyBitmap[index2];
                }
            }

            outRect.origin.x = bbox.xMin >> 6;
            outRect.origin.y = - (bbox.yMax >> 6);
            xAdvance += 2 * _outlineSize;
            outRect.size.width  =  blendWidth;
            outRect.size.height =  blendHeight;
            outWidth  = blendWidth;
            outHeight = blendHeight;

            delete [] outlineBitmap;
            delete [] copyBitmap;
            ret = blendImage;
        }

        invalidChar = false;
    } while (0);

    if (invalidChar)
    {
        outRect.size.width  = 0;
        outRect.size.height = 0;
        xAdvance = 0;

        return nullptr;
    }
    else
    {
       return ret;
    }
}

unsigned char * FontFreeType::getGlyphBitmapWithOutline(unsigned short theChar, FT_BBox &bbox)
{   
    unsigned char* ret = nullptr;

    FT_UInt gindex = FT_Get_Char_Index(_fontRef, theChar);
    if (FT_Load_Glyph(_fontRef, gindex, FT_LOAD_NO_BITMAP) == 0)
    {
        if (_fontRef->glyph->format == FT_GLYPH_FORMAT_OUTLINE)
        {
            FT_Glyph glyph;
            if (FT_Get_Glyph(_fontRef->glyph, &glyph) == 0)
            {
                FT_Glyph_StrokeBorder(&glyph, _stroker, 0, 1);
                if (glyph->format == FT_GLYPH_FORMAT_OUTLINE)
                {
                    FT_Outline *outline = &reinterpret_cast<FT_OutlineGlyph>(glyph)->outline;
                    FT_Glyph_Get_CBox(glyph,FT_GLYPH_BBOX_GRIDFIT,&bbox);
                    long width = (bbox.xMax - bbox.xMin)>>6;
                    long rows = (bbox.yMax - bbox.yMin)>>6;

                    FT_Bitmap bmp;
                    bmp.buffer = new unsigned char[width * rows];
                    memset(bmp.buffer, 0, width * rows);
                    bmp.width = (int)width;
                    bmp.rows = (int)rows;
                    bmp.pitch = (int)width;
                    bmp.pixel_mode = FT_PIXEL_MODE_GRAY;
                    bmp.num_grays = 256;

                    FT_Raster_Params params;
                    memset(&params, 0, sizeof (params));
                    params.source = outline;
                    params.target = &bmp;
                    params.flags = FT_RASTER_FLAG_AA;
                    FT_Outline_Translate(outline,-bbox.xMin,-bbox.yMin);
                    FT_Outline_Render(_FTlibrary, outline, &params);

                    ret = bmp.buffer;
                }
                FT_Done_Glyph(glyph);
            }
        }
    }

    return ret;
}

unsigned char * makeDistanceMap( unsigned char *img, long width, long height)
{
    long pixelAmount = (width + 2 * FontFreeType::DistanceMapSpread) * (height + 2 * FontFreeType::DistanceMapSpread);

    short * xdist = (short *)  malloc( pixelAmount * sizeof(short) );
    short * ydist = (short *)  malloc( pixelAmount * sizeof(short) );
    double * gx   = (double *) calloc( pixelAmount, sizeof(double) );
    double * gy      = (double *) calloc( pixelAmount, sizeof(double) );
    double * data    = (double *) calloc( pixelAmount, sizeof(double) );
    double * outside = (double *) calloc( pixelAmount, sizeof(double) );
    double * inside  = (double *) calloc( pixelAmount, sizeof(double) );
    long i,j;

    // Convert img into double (data) rescale image levels between 0 and 1
    long outWidth = width + 2 * FontFreeType::DistanceMapSpread;
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
    computegradient( data, (int)width, (int)height, gx, gy);
    edtaa3(data, gx, gy, (int)width, (int)height, xdist, ydist, outside);
    for( i=0; i< pixelAmount; i++)
        if( outside[i] < 0.0 )
            outside[i] = 0.0;

    // Transform foreground (inside contour, in areas of 1's)   
    for( i=0; i< pixelAmount; i++)
        data[i] = 1 - data[i];
    computegradient( data, (int)width, (int)height, gx, gy);
    edtaa3(data, gx, gy, (int)width, (int)height, xdist, ydist, inside);
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

void FontFreeType::renderCharAt(unsigned char *dest,int posX, int posY, unsigned char* bitmap,long bitmapWidth,long bitmapHeight)
{
    int iX = posX;
    int iY = posY;

    if (_distanceFieldEnabled)
    {
        auto distanceMap = makeDistanceMap(bitmap,bitmapWidth,bitmapHeight);

        bitmapWidth += 2 * DistanceMapSpread;
        bitmapHeight += 2 * DistanceMapSpread;

        for (long y = 0; y < bitmapHeight; ++y)
        {
            long bitmap_y = y * bitmapWidth;

            for (long x = 0; x < bitmapWidth; ++x)
            {    
                /* Dual channel 16-bit output (more complicated, but good precision and range) */
                /*int index = (iX + ( iY * destSize )) * 3;                
                int index2 = (bitmap_y + x)*3;
                dest[index] = out[index2];
                dest[index + 1] = out[index2 + 1];
                dest[index + 2] = out[index2 + 2];*/

                //Single channel 8-bit output 
                dest[iX + ( iY * FontAtlas::CacheTextureWidth )] = distanceMap[bitmap_y + x];

                iX += 1;
            }

            iX  = posX;
            iY += 1;
        }
        free(distanceMap);
    }
    else if(_outlineSize > 0)
    {
        unsigned char tempChar;
        for (long y = 0; y < bitmapHeight; ++y)
        {
            long bitmap_y = y * bitmapWidth;

            for (int x = 0; x < bitmapWidth; ++x)
            {
                tempChar = bitmap[(bitmap_y + x) * 2];
                dest[(iX + ( iY * FontAtlas::CacheTextureWidth ) ) * 2] = tempChar;
                tempChar = bitmap[(bitmap_y + x) * 2 + 1];
                dest[(iX + ( iY * FontAtlas::CacheTextureWidth ) ) * 2 + 1] = tempChar;

                iX += 1;
            }

            iX  = posX;
            iY += 1;
        }
        delete [] bitmap;
    }
    else
    {
        for (long y = 0; y < bitmapHeight; ++y)
        {
            long bitmap_y = y * bitmapWidth;

            for (int x = 0; x < bitmapWidth; ++x)
            {
                unsigned char cTemp = bitmap[bitmap_y + x];

                // the final pixel
                dest[(iX + ( iY * FontAtlas::CacheTextureWidth ) )] = cTemp;

                iX += 1;
            }

            iX  = posX;
            iY += 1;
        }
    } 
}

NS_CC_END
