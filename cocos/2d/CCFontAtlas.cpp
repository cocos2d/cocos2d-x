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

#include "2d/CCFontAtlas.h"
#include "2d/CCFontFreeType.h"
#include "base/ccUTF8.h"
#include "base/CCDirector.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"

NS_CC_BEGIN

const int FontAtlas::CacheTextureWidth = 512;
const int FontAtlas::CacheTextureHeight = 512;
const char* FontAtlas::EVENT_PURGE_TEXTURES = "__cc_FontAtlasPurgeTextures";

FontAtlas::FontAtlas(Font &theFont) 
: _font(&theFont)
, _currentPageData(nullptr)
, _fontAscender(0)
, _toForegroundListener(nullptr)
, _toBackgroundListener(nullptr)
, _antialiasEnabled(true)
{
    _font->retain();

    FontFreeType* fontTTf = dynamic_cast<FontFreeType*>(_font);
    if (fontTTf)
    {
        _commonLineHeight = _font->getFontMaxHeight();
        _fontAscender = fontTTf->getFontAscender();
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

        auto  pixelFormat = fontTTf->getOutlineSize() > 0 ? Texture2D::PixelFormat::AI88 : Texture2D::PixelFormat::A8; 
        texture->initWithData(_currentPageData, _currentPageDataSize, 
            pixelFormat, CacheTextureWidth, CacheTextureHeight, Size(CacheTextureWidth,CacheTextureHeight) );

        addTexture(texture,0);
        texture->release();
#if CC_ENABLE_CACHE_TEXTURE_DATA
        auto eventDispatcher = Director::getInstance()->getEventDispatcher();
        _toBackgroundListener = EventListenerCustom::create(EVENT_COME_TO_BACKGROUND, CC_CALLBACK_1(FontAtlas::listenToBackground, this));
        eventDispatcher->addEventListenerWithFixedPriority(_toBackgroundListener, 1);
        _toForegroundListener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, CC_CALLBACK_1(FontAtlas::listenToForeground, this));
        eventDispatcher->addEventListenerWithFixedPriority(_toForegroundListener, 1);
#endif
    }
}

FontAtlas::~FontAtlas()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    FontFreeType* fontTTf = dynamic_cast<FontFreeType*>(_font);
    if (fontTTf)
    {
        auto eventDispatcher = Director::getInstance()->getEventDispatcher();
        if (_toForegroundListener)
        {
            eventDispatcher->removeEventListener(_toForegroundListener);
            _toForegroundListener = nullptr;
        }
        if (_toBackgroundListener)
        {
            eventDispatcher->removeEventListener(_toBackgroundListener);
            _toBackgroundListener = nullptr;
        }
    }
#endif

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
    _atlasTextures.clear();
}

void FontAtlas::purgeTexturesAtlas()
{
    FontFreeType* fontTTf = dynamic_cast<FontFreeType*>(_font);
    if (fontTTf && _atlasTextures.size() > 1)
    {
        for( auto &item: _atlasTextures)
        {
            if (item.first != 0)
            {
                item.second->release();
            }
        }
        auto temp = _atlasTextures[0];
        _atlasTextures.clear();
        _atlasTextures[0] = temp;

        _fontLetterDefinitions.clear();
        memset(_currentPageData,0,_currentPageDataSize);
        _currentPage = 0;
        _currentPageOrigX = 0;
        _currentPageOrigY = 0;

        auto eventDispatcher = Director::getInstance()->getEventDispatcher();
        eventDispatcher->dispatchCustomEvent(EVENT_PURGE_TEXTURES,this);
    }
}

void FontAtlas::listenToBackground(EventCustom *event)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    FontFreeType* fontTTf = dynamic_cast<FontFreeType*>(_font);
    if (fontTTf && _atlasTextures.size() > 1)
    {
        for( auto &item: _atlasTextures)
        {
            if (item.first != 0)
            {
                item.second->release();
            }
        }
        auto temp = _atlasTextures[0];
        _atlasTextures.clear();
        _atlasTextures[0] = temp;

        _fontLetterDefinitions.clear();
        memset(_currentPageData,0,_currentPageDataSize);
        _currentPage = 0;
        _currentPageOrigX = 0;
        _currentPageOrigY = 0;
    }
#endif
}

void FontAtlas::listenToForeground(EventCustom *event)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    FontFreeType* fontTTf = dynamic_cast<FontFreeType*>(_font);
    if (fontTTf)
    {
        if (_currentPageOrigX == 0 && _currentPageOrigY == 0)
        {
            auto eventDispatcher = Director::getInstance()->getEventDispatcher();
            eventDispatcher->dispatchCustomEvent(EVENT_PURGE_TEXTURES,this);
        }
        else
        {
            auto  pixelFormat = fontTTf->getOutlineSize() > 0 ? Texture2D::PixelFormat::AI88 : Texture2D::PixelFormat::A8;

            _atlasTextures[_currentPage]->initWithData(_currentPageData, _currentPageDataSize, 
                pixelFormat, CacheTextureWidth, CacheTextureHeight, Size(CacheTextureWidth,CacheTextureHeight) );
        }
    }
#endif
}

void FontAtlas::addLetterDefinition(const FontLetterDefinition &letterDefinition)
{
    _fontLetterDefinitions[letterDefinition.letteCharUTF16] = letterDefinition;
}

bool FontAtlas::getLetterDefinitionForChar(char16_t letteCharUTF16, FontLetterDefinition &outDefinition)
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

bool FontAtlas::prepareLetterDefinitions(const std::u16string& utf16String)
{
    FontFreeType* fontTTf = dynamic_cast<FontFreeType*>(_font);
    if(fontTTf == nullptr)
        return false;

    size_t length = utf16String.length();

    float offsetAdjust = _letterPadding / 2;  
    long bitmapWidth;
    long bitmapHeight;
    Rect tempRect;
    FontLetterDefinition tempDef;

    auto scaleFactor = CC_CONTENT_SCALE_FACTOR();
    auto  pixelFormat = fontTTf->getOutlineSize() > 0 ? Texture2D::PixelFormat::AI88 : Texture2D::PixelFormat::A8; 

    bool existNewLetter = false;
    int bottomHeight = _commonLineHeight - _fontAscender;

    float startY = _currentPageOrigY;

    for (size_t i = 0; i < length; ++i)
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
                tempDef.offsetY          = _fontAscender + tempRect.origin.y - offsetAdjust;
                tempDef.clipBottom     = bottomHeight - (tempDef.height + tempRect.origin.y + offsetAdjust);

                if (_currentPageOrigX + tempDef.width > CacheTextureWidth)
                {
                    _currentPageOrigY += _commonLineHeight;
                    _currentPageOrigX = 0;
                    if(_currentPageOrigY + _commonLineHeight >= CacheTextureHeight)
                    {     
                        auto data = _currentPageData + CacheTextureWidth * (int)startY;
                        _atlasTextures[_currentPage]->updateWithData(data, 0, startY, 
                            CacheTextureWidth, CacheTextureHeight - startY);

                        startY = 0.0f;

                        _currentPageOrigY = 0;
                        memset(_currentPageData, 0, _currentPageDataSize);
                        _currentPage++;
                        auto tex = new Texture2D;
                        if (_antialiasEnabled)
                        {
                            tex->setAntiAliasTexParameters();
                        } 
                        else
                        {
                            tex->setAliasTexParameters();
                        }
                        tex->initWithData(_currentPageData, _currentPageDataSize, 
                            pixelFormat, CacheTextureWidth, CacheTextureHeight, Size(CacheTextureWidth,CacheTextureHeight) );
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
                tempDef.clipBottom = 0;
                _currentPageOrigX += 1;
            }

            _fontLetterDefinitions[tempDef.letteCharUTF16] = tempDef;
        }       
    }

    if(existNewLetter)
    {
        auto data = _currentPageData + CacheTextureWidth * (int)startY;
        _atlasTextures[_currentPage]->updateWithData(data, 0, startY, 
            CacheTextureWidth, _currentPageOrigY - startY + _commonLineHeight);
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

void FontAtlas::setAliasTexParameters()
{
    if (_antialiasEnabled)
    {
        _antialiasEnabled = false;
        for (const auto & tex : _atlasTextures)
        {
            tex.second->setAliasTexParameters();
        }
    }
}

void FontAtlas::setAntiAliasTexParameters()
{
    if (! _antialiasEnabled)
    {
        _antialiasEnabled = true;
        for (const auto & tex : _atlasTextures)
        {
            tex.second->setAntiAliasTexParameters();
        }
    }
}

NS_CC_END
