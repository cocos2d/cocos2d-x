/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2015 Chukong Technologies Inc.
 
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
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32 && CC_TARGET_PLATFORM != CC_PLATFORM_WINRT && CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
#include <iconv.h>
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#endif
#include "2d/CCFontFreeType.h"
#include "base/ccUTF8.h"
#include "base/CCDirector.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"

NS_CC_BEGIN

const int FontAtlas::CacheTextureWidth = 512;
const int FontAtlas::CacheTextureHeight = 512;
const char* FontAtlas::CMD_PURGE_FONTATLAS = "__cc_PURGE_FONTATLAS";
const char* FontAtlas::CMD_RESET_FONTATLAS = "__cc_RESET_FONTATLAS";

FontAtlas::FontAtlas(Font &theFont) 
: _font(&theFont)
, _fontFreeType(nullptr)
, _iconv(nullptr)
, _currentPageData(nullptr)
, _fontAscender(0)
, _rendererRecreatedListener(nullptr)
, _antialiasEnabled(true)
, _currLineHeight(0)
{
    _font->retain();

    _fontFreeType = dynamic_cast<FontFreeType*>(_font);
    if (_fontFreeType)
    {
        _lineHeight = _font->getFontMaxHeight();
        _fontAscender = _fontFreeType->getFontAscender();
        auto texture = new (std::nothrow) Texture2D;
        _currentPage = 0;
        _currentPageOrigX = 0;
        _currentPageOrigY = 0;
        _letterEdgeExtend = 2;
        _letterPadding = 0;

        if (_fontFreeType->isDistanceFieldEnabled())
        {
            _letterPadding += 2 * FontFreeType::DistanceMapSpread;    
        }
        _currentPageDataSize = CacheTextureWidth * CacheTextureHeight;
        auto outlineSize = _fontFreeType->getOutlineSize();
        if(outlineSize > 0)
        {
            _lineHeight += 2 * outlineSize;
            _currentPageDataSize *= 2;
        }

        _currentPageData = new unsigned char[_currentPageDataSize];
        memset(_currentPageData, 0, _currentPageDataSize);

        auto  pixelFormat = outlineSize > 0 ? Texture2D::PixelFormat::AI88 : Texture2D::PixelFormat::A8; 
        texture->initWithData(_currentPageData, _currentPageDataSize, 
            pixelFormat, CacheTextureWidth, CacheTextureHeight, Size(CacheTextureWidth,CacheTextureHeight) );

        addTexture(texture,0);
        texture->release();

#if CC_ENABLE_CACHE_TEXTURE_DATA
        auto eventDispatcher = Director::getInstance()->getEventDispatcher();

        _rendererRecreatedListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, CC_CALLBACK_1(FontAtlas::listenRendererRecreated, this));
        eventDispatcher->addEventListenerWithFixedPriority(_rendererRecreatedListener, 1);
#endif
    }
}

FontAtlas::~FontAtlas()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    if (_fontFreeType && _rendererRecreatedListener)
    {
        auto eventDispatcher = Director::getInstance()->getEventDispatcher();
        eventDispatcher->removeEventListener(_rendererRecreatedListener);
        _rendererRecreatedListener = nullptr;
    }
#endif

    _font->release();
    relaseTextures();

    delete []_currentPageData;

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32 && CC_TARGET_PLATFORM != CC_PLATFORM_WINRT && CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
    if (_iconv)
    {
        iconv_close(_iconv);
        _iconv = nullptr;
    }
#endif
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
    if (_fontFreeType && _atlasTextures.size() > 1)
    {
        auto eventDispatcher = Director::getInstance()->getEventDispatcher();
        eventDispatcher->dispatchCustomEvent(CMD_PURGE_FONTATLAS,this);
        eventDispatcher->dispatchCustomEvent(CMD_RESET_FONTATLAS,this);
    }
}

void FontAtlas::listenRendererRecreated(EventCustom *event)
{
    if (_fontFreeType)
    {
        auto eventDispatcher = Director::getInstance()->getEventDispatcher();
        eventDispatcher->dispatchCustomEvent(CMD_PURGE_FONTATLAS,this);
        eventDispatcher->dispatchCustomEvent(CMD_RESET_FONTATLAS,this);
    }
}

void FontAtlas::addLetterDefinition(char16_t utf16Char, const FontLetterDefinition &letterDefinition)
{
    _letterDefinitions[utf16Char] = letterDefinition;
}

void FontAtlas::scaleFontLetterDefinition(float scaleFactor)
{
    for (auto&& fontDefinition : _letterDefinitions) {
        auto& letterDefinition = fontDefinition.second;
        letterDefinition.width *= scaleFactor;
        letterDefinition.height *= scaleFactor;
        letterDefinition.offsetX *= scaleFactor;
        letterDefinition.offsetY *= scaleFactor;
        letterDefinition.xAdvance *= scaleFactor;
    }
}

bool FontAtlas::getLetterDefinitionForChar(char16_t utf16Char, FontLetterDefinition &letterDefinition)
{
    auto outIterator = _letterDefinitions.find(utf16Char);

    if (outIterator != _letterDefinitions.end())
    {
        letterDefinition = (*outIterator).second;
        return letterDefinition.validDefinition;
    }
    else
    {
        return false;
    }
}

void FontAtlas::conversionU16TOGB2312(const std::u16string& u16Text, std::unordered_map<unsigned short, unsigned short>& charCodeMap)
{
    size_t strLen = u16Text.length();
    auto gb2312StrSize = strLen * 2;
    auto gb2312Text = new (std::nothrow) char[gb2312StrSize];
    memset(gb2312Text, 0, gb2312StrSize);

    switch (_fontFreeType->getEncoding())
    {
    case FT_ENCODING_GB2312:
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
        WideCharToMultiByte(936, NULL, (LPCWCH)u16Text.c_str(), strLen, (LPSTR)gb2312Text, gb2312StrSize, NULL, NULL);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        conversionEncodingJNI((char*)u16Text.c_str(), gb2312StrSize, "UTF-16LE", gb2312Text, "GB2312");
#else
        if (_iconv == nullptr)
        {
            _iconv = iconv_open("gb2312", "utf-16le");
        }

        if (_iconv == (iconv_t)-1)
        {
            CCLOG("conversion from utf16 to gb2312 not available");
        }
        else
        {
            char* pin = (char*)u16Text.c_str();
            char* pout = gb2312Text;
            size_t inLen = strLen * 2;
            size_t outLen = gb2312StrSize;

            iconv(_iconv, (char**)&pin, &inLen, &pout, &outLen);
        }
#endif
    }
    break;
    default:
        CCLOG("Unsupported encoding:%d", _fontFreeType->getEncoding());
        break;
    }

    unsigned short gb2312Code = 0;
    unsigned char* dst = (unsigned char*)&gb2312Code;
    unsigned short u16Code;
    for (size_t index = 0, gbIndex = 0; index < strLen; ++index)
    {
        u16Code = u16Text[index];
        if (u16Code < 256)
        {
            charCodeMap[u16Code] = u16Code;
            gbIndex += 1;
        }
        else
        {
            dst[0] = gb2312Text[gbIndex + 1];
            dst[1] = gb2312Text[gbIndex];
            charCodeMap[u16Code] = gb2312Code;

            gbIndex += 2;
        }
    }

    delete[] gb2312Text;
}

void FontAtlas::findNewCharacters(const std::u16string& u16Text, std::unordered_map<unsigned short, unsigned short>& charCodeMap)
{
    std::u16string newChars;
    FT_Encoding charEncoding = _fontFreeType->getEncoding();

    //find new characters
    if (_letterDefinitions.empty())
    {
        newChars = u16Text;
    }
    else
    {
        auto length = u16Text.length();
        newChars.reserve(length);
        for (size_t i = 0; i < length; ++i)
        {
            auto outIterator = _letterDefinitions.find(u16Text[i]);
            if (outIterator == _letterDefinitions.end())
            {
                newChars.push_back(u16Text[i]);
            }
        }
    }

    if (!newChars.empty())
    {
        switch (charEncoding)
        {
        case FT_ENCODING_UNICODE:
        {
            for (auto u16Code : newChars)
            {
                charCodeMap[u16Code] = u16Code;
            }
            break;
        }
        case FT_ENCODING_GB2312:
        {
            conversionU16TOGB2312(newChars, charCodeMap);
            break;
        }
        default:
            CCLOG("FontAtlas::findNewCharacters: Unsupported encoding:%d", charEncoding);
            break;
        }
    }
}

bool FontAtlas::prepareLetterDefinitions(const std::u16string& utf16Text)
{
    if (_fontFreeType == nullptr)
    {
        return false;
    } 
    
    std::unordered_map<unsigned short, unsigned short> codeMapOfNewChar;
    findNewCharacters(utf16Text, codeMapOfNewChar);
    if (codeMapOfNewChar.empty())
    {
        return false;
    }

    int adjustForDistanceMap = _letterPadding / 2;
    int adjustForExtend = _letterEdgeExtend / 2;
    long bitmapWidth;
    long bitmapHeight;
    Rect tempRect;
    FontLetterDefinition tempDef;

    auto scaleFactor = CC_CONTENT_SCALE_FACTOR();
    auto  pixelFormat = _fontFreeType->getOutlineSize() > 0 ? Texture2D::PixelFormat::AI88 : Texture2D::PixelFormat::A8;

    float startY = _currentPageOrigY;

    for (auto&& it : codeMapOfNewChar)
    {
        auto bitmap = _fontFreeType->getGlyphBitmap(it.second, bitmapWidth, bitmapHeight, tempRect, tempDef.xAdvance);
        if (bitmap && bitmapWidth > 0 && bitmapHeight > 0)
        {
            tempDef.validDefinition = true;
            tempDef.width = tempRect.size.width + _letterPadding + _letterEdgeExtend;
            tempDef.height = tempRect.size.height + _letterPadding + _letterEdgeExtend;
            tempDef.offsetX = tempRect.origin.x + adjustForDistanceMap + adjustForExtend;
            tempDef.offsetY = _fontAscender + tempRect.origin.y - adjustForDistanceMap - adjustForExtend;

            if (bitmapHeight > _currLineHeight)
            {
                _currLineHeight = static_cast<int>(bitmapHeight) + _letterPadding + _letterEdgeExtend + 1;
            }
            if (_currentPageOrigX + tempDef.width > CacheTextureWidth)
            {
                _currentPageOrigY += _currLineHeight;
                _currLineHeight = 0;
                _currentPageOrigX = 0;
                if (_currentPageOrigY + _lineHeight >= CacheTextureHeight)
                {
                    unsigned char *data = nullptr;
                    if (pixelFormat == Texture2D::PixelFormat::AI88)
                    {
                        data = _currentPageData + CacheTextureWidth * (int)startY * 2;
                    }
                    else
                    {
                        data = _currentPageData + CacheTextureWidth * (int)startY;
                    }
                    _atlasTextures[_currentPage]->updateWithData(data, 0, startY,
                        CacheTextureWidth, CacheTextureHeight - startY);

                    startY = 0.0f;

                    _currentPageOrigY = 0;
                    memset(_currentPageData, 0, _currentPageDataSize);
                    _currentPage++;
                    auto tex = new (std::nothrow) Texture2D;
                    if (_antialiasEnabled)
                    {
                        tex->setAntiAliasTexParameters();
                    }
                    else
                    {
                        tex->setAliasTexParameters();
                    }
                    tex->initWithData(_currentPageData, _currentPageDataSize,
                        pixelFormat, CacheTextureWidth, CacheTextureHeight, Size(CacheTextureWidth, CacheTextureHeight));
                    addTexture(tex, _currentPage);
                    tex->release();
                }
            }
            _fontFreeType->renderCharAt(_currentPageData, _currentPageOrigX + adjustForExtend, _currentPageOrigY + adjustForExtend, bitmap, bitmapWidth, bitmapHeight);

            tempDef.U = _currentPageOrigX;
            tempDef.V = _currentPageOrigY;
            tempDef.textureID = _currentPage;
            _currentPageOrigX += tempDef.width + 1;
            // take from pixels to points
            tempDef.width = tempDef.width / scaleFactor;
            tempDef.height = tempDef.height / scaleFactor;
            tempDef.U = tempDef.U / scaleFactor;
            tempDef.V = tempDef.V / scaleFactor;
        }
        else{
            if (tempDef.xAdvance)
                tempDef.validDefinition = true;
            else
                tempDef.validDefinition = false;

            tempDef.width = 0;
            tempDef.height = 0;
            tempDef.U = 0;
            tempDef.V = 0;
            tempDef.offsetX = 0;
            tempDef.offsetY = 0;
            tempDef.textureID = 0;
            _currentPageOrigX += 1;
        }

        _letterDefinitions[it.first] = tempDef;
    }

    unsigned char *data = nullptr;
    if (pixelFormat == Texture2D::PixelFormat::AI88)
    {
        data = _currentPageData + CacheTextureWidth * (int)startY * 2;
    }
    else
    {
        data = _currentPageData + CacheTextureWidth * (int)startY;
    }
    _atlasTextures[_currentPage]->updateWithData(data, 0, startY, CacheTextureWidth, _currentPageOrigY - startY + _lineHeight);

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

void  FontAtlas::setLineHeight(float newHeight)
{
    _lineHeight = newHeight;
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
