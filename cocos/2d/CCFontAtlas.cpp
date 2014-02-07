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

#define  PAGE_WIDTH 1024
#define  PAGE_HEIGHT 1024

NS_CC_BEGIN

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
        Texture2D * tex = new Texture2D;
        _currentPage = 0;
        _currentPageOrigX = 0;
        _currentPageOrigY = 0;
        _letterPadding = 0;

        _makeDistanceMap = fontTTf->isDistanceFieldEnabled();
        if(_makeDistanceMap)
        {
            _commonLineHeight += 2 * FontFreeType::DistanceMapSpread;
            _letterPadding += 2 * FontFreeType::DistanceMapSpread;    
        }
        _currentPageDataSize = (PAGE_WIDTH * PAGE_HEIGHT * 1);

        _currentPageData = new unsigned char[_currentPageDataSize];       
        memset(_currentPageData, 0, _currentPageDataSize);  
        addTexture(*tex,0);
        tex->release();
    }
    else
    {
        _makeDistanceMap = false;
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

    std::unordered_map<unsigned short, FontLetterDefinition> fontDefs;
    int length = cc_wcslen(utf16String);

    float offsetAdjust = _letterPadding / 2;
    //find out new letter
    for (int i = 0; i < length; ++i)
    {
        auto outIterator = _fontLetterDefinitions.find(utf16String[i]);
        
        if (outIterator == _fontLetterDefinitions.end())
        {  
            auto outIterator2 = fontDefs.find(utf16String[i]);
            if(outIterator2 != fontDefs.end())
                continue;

            Rect tempRect;           

            FontLetterDefinition tempDef;

            if (!fontTTf->getBBOXFotChar(utf16String[i], tempRect,tempDef.xAdvance))
            {
                tempDef.validDefinition = false;
                tempDef.letteCharUTF16   = utf16String[i];
                tempDef.width            = 0;
                tempDef.height           = 0;
                tempDef.U                = 0;
                tempDef.V                = 0;
                tempDef.offsetX          = 0;
                tempDef.offsetY          = 0;
                tempDef.textureID        = 0;
                tempDef.xAdvance         = 0;
            }
            else
            {
                tempDef.validDefinition = true;
                tempDef.letteCharUTF16   = utf16String[i];
                tempDef.width            = tempRect.size.width + _letterPadding;
                tempDef.height           = tempRect.size.height + _letterPadding;
                tempDef.offsetX          = tempRect.origin.x + offsetAdjust;
                tempDef.offsetY          = _commonLineHeight + tempRect.origin.y - offsetAdjust;
            } 
            fontDefs[utf16String[i]] = tempDef;
        }       
    }

    Size _pageContentSize = Size(PAGE_WIDTH,PAGE_HEIGHT);
    float scaleFactor = CC_CONTENT_SCALE_FACTOR();
    float glyphWidth;
    Texture2D::PixelFormat  pixelFormat = Texture2D::PixelFormat::A8;
    

    for(auto it = fontDefs.begin(); it != fontDefs.end(); it++)
    {
        if(it->second.validDefinition)
        {
            glyphWidth = it->second.width;

            if (_currentPageOrigX + glyphWidth > PAGE_WIDTH)
            {
                _currentPageOrigY += _currentPageLineHeight;
                _currentPageOrigX = 0;
                if(_currentPageOrigY >= PAGE_HEIGHT)
                {             
                    _atlasTextures[_currentPage]->initWithData(_currentPageData, _currentPageDataSize, pixelFormat, PAGE_WIDTH, PAGE_HEIGHT, _pageContentSize );
                    _currentPageOrigY = 0;

                    delete []_currentPageData;
                    _currentPageData = new unsigned char[_currentPageDataSize];
                    if(_currentPageData == nullptr)
                        return false;
                    memset(_currentPageData, 0, _currentPageDataSize);
                    _currentPage++;
                    Texture2D* tex = new Texture2D;
                    addTexture(*tex,_currentPage);
                    tex->release();
                }
            }
            fontTTf->renderCharAt(it->second.letteCharUTF16,_currentPageOrigX,_currentPageOrigY,_currentPageData,PAGE_WIDTH);

            it->second.U                = _currentPageOrigX;
            it->second.V                = _currentPageOrigY;
            it->second.textureID        = _currentPage;
            // take from pixels to points
            it->second.width  =    it->second.width  / scaleFactor;
            it->second.height =    it->second.height / scaleFactor;      
            it->second.U      =    it->second.U      / scaleFactor;
            it->second.V      =    it->second.V      / scaleFactor;
        }
        else
            glyphWidth = 0;       
       
        _fontLetterDefinitions[it->second.letteCharUTF16] = it->second;
        _currentPageOrigX += glyphWidth + 1;
    }
    if(fontDefs.size() > 0)
        _atlasTextures[_currentPage]->initWithData(_currentPageData, _currentPageDataSize, pixelFormat, PAGE_WIDTH, PAGE_HEIGHT, _pageContentSize );
    return true;
}

void FontAtlas::addTexture(Texture2D &texture, int slot)
{
    texture.retain();
    _atlasTextures[slot] = &texture;
}

Texture2D & FontAtlas::getTexture(int slot)
{
    return *(_atlasTextures[slot]);
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
