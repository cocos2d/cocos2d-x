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

#include "CCFontAtlas.h"
#include "CCFontFreeType.h"
#include "ccUTF8.h"
#include "CCDirector.h"

NS_CC_BEGIN

const int FontAtlas::CacheTextureWidth = 1024;
const int FontAtlas::CacheTextureHeight = 1024;

FontAtlas::FontAtlas(Font &theFont) : 
_font(&theFont),
_currentPageData(nullptr)
{
    _font->retain();

    FontFreeType* fontTTf = dynamic_cast<FontFreeType*>(_font);
    if (fontTTf)
    {
        _currentPageLineHeight = _font->getFontMaxHeight();
        _commonLineHeight = _currentPageLineHeight * 0.8f;
        auto texture = new Texture2D;
        _currentPage = 0;
        _currentPageOrigX = 0;
        _currentPageOrigY = 0;
        _letterPadding = 0;

        if(fontTTf->isDistanceFieldEnabled())
        {
            _letterPadding += 2 * FontFreeType::DistanceMapSpread;    
        }
        _currentPageDataSize = CacheTextureWidth * CacheTextureHeight;
        if(fontTTf->getOutlineSize() > 0)
        {
            _currentPageDataSize *= 2;
        }    

        _currentPageData = new unsigned char[_currentPageDataSize];       
        memset(_currentPageData, 0, _currentPageDataSize);  
        addTexture(texture,0);
        texture->release();
    }
}

FontAtlas::~FontAtlas()
{
    _font->release();
    relaseTextures();

    delete []_currentPageData;
}

void FontAtlas::relaseTextures()
{
    for( auto &item: _atlasTextures)
    {
        item.second->release();
    }
}

void FontAtlas::addLetterDefinition(const FontLetterDefinition &letterDefinition)
{
    _fontLetterDefinitions[letterDefinition.letteCharUTF16] = letterDefinition;
}

bool FontAtlas::getLetterDefinitionForChar(unsigned short  letteCharUTF16, FontLetterDefinition &outDefinition)
{
    auto outIterator = _fontLetterDefinitions.find(letteCharUTF16);
    
    if (outIterator != _fontLetterDefinitions.end())
    {
        outDefinition = (*outIterator).second;
        return true;
    }
    else
    {
        outDefinition.validDefinition = false;
        return false;
    }
}

bool FontAtlas::prepareLetterDefinitions(unsigned short *utf16String)
{
    if(_currentPageData == nullptr)
        return false;

    FontFreeType* fontTTf = (FontFreeType*)_font;
    int length = cc_wcslen(utf16String);

    float offsetAdjust = _letterPadding / 2;  
    int bitmapWidth;
    int bitmapHeight;
    Rect tempRect;
    FontLetterDefinition tempDef;

    auto contentSize = Size(CacheTextureWidth,CacheTextureHeight);
    auto scaleFactor = CC_CONTENT_SCALE_FACTOR();
    auto  pixelFormat = fontTTf->getOutlineSize() > 0 ? Texture2D::PixelFormat::AI88 : Texture2D::PixelFormat::A8; 

    bool existNewLetter = false;
    for (int i = 0; i < length; ++i)
    {
        auto outIterator = _fontLetterDefinitions.find(utf16String[i]);

        if (outIterator == _fontLetterDefinitions.end())
        {  
            existNewLetter = true;

            auto bitmap = fontTTf->getGlyphBitmap(utf16String[i],bitmapWidth,bitmapHeight,tempRect,tempDef.xAdvance);
            if (bitmap)
            {
                tempDef.validDefinition = true;
                tempDef.letteCharUTF16   = utf16String[i];
                tempDef.width            = tempRect.size.width + _letterPadding;
                tempDef.height           = tempRect.size.height + _letterPadding;
                tempDef.offsetX          = tempRect.origin.x + offsetAdjust;
                tempDef.offsetY          = _commonLineHeight + tempRect.origin.y - offsetAdjust;

                if (_currentPageOrigX + tempDef.width > CacheTextureWidth)
                {
                    _currentPageOrigY += _currentPageLineHeight;
                    _currentPageOrigX = 0;
                    if(_currentPageOrigY + _currentPageLineHeight >= CacheTextureHeight)
                    {             
                        _atlasTextures[_currentPage]->initWithData(_currentPageData, _currentPageDataSize, pixelFormat, CacheTextureWidth, CacheTextureHeight, contentSize );
                        _currentPageOrigY = 0;

                        delete []_currentPageData;
                        _currentPageData = new unsigned char[_currentPageDataSize];
                        if(_currentPageData == nullptr)
                            return false;
                        memset(_currentPageData, 0, _currentPageDataSize);
                        _currentPage++;
                        auto tex = new Texture2D;
                        addTexture(tex,_currentPage);
                        tex->release();
                    }  
                }
                fontTTf->renderCharAt(_currentPageData,_currentPageOrigX,_currentPageOrigY,bitmap,bitmapWidth,bitmapHeight);

                tempDef.U                = _currentPageOrigX;
                tempDef.V                = _currentPageOrigY;
                tempDef.textureID        = _currentPage;
                _currentPageOrigX        += tempDef.width + 1;
                // take from pixels to points
                tempDef.width  =    tempDef.width  / scaleFactor;
                tempDef.height =    tempDef.height / scaleFactor;      
                tempDef.U      =    tempDef.U      / scaleFactor;
                tempDef.V      =    tempDef.V      / scaleFactor;
            }
            else{
                if(tempDef.xAdvance)
                    tempDef.validDefinition = true;
                else
                    tempDef.validDefinition = false;

                tempDef.letteCharUTF16   = utf16String[i];
                tempDef.width            = 0;
                tempDef.height           = 0;
                tempDef.U                = 0;
                tempDef.V                = 0;
                tempDef.offsetX          = 0;
                tempDef.offsetY          = 0;
                tempDef.textureID        = 0;
                _currentPageOrigX += 1;
            }

            _fontLetterDefinitions[tempDef.letteCharUTF16] = tempDef;
        }       
    }

    if(existNewLetter)
    {
        _atlasTextures[_currentPage]->initWithData(_currentPageData, _currentPageDataSize, pixelFormat, CacheTextureWidth, CacheTextureHeight, contentSize );
    }
    return true;
}

void FontAtlas::addTexture(Texture2D *texture, int slot)
{
    texture->retain();
    _atlasTextures[slot] = texture;
}

Texture2D* FontAtlas::getTexture(int slot)
{
    return _atlasTextures[slot];
}

float FontAtlas::getCommonLineHeight() const
{
    return _commonLineHeight;
}

void  FontAtlas::setCommonLineHeight(float newHeight)
{
    _commonLineHeight = newHeight;
}

const Font * FontAtlas::getFont() const
{
    return _font;
}

NS_CC_END
