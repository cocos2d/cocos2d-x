/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32 && CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
#include <iconv.h>
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
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
{
    _font->retain();

    _fontFreeType = dynamic_cast<FontFreeType*>(_font);
    if (_fontFreeType)
    {
        _lineHeight = (float)_font->getFontMaxHeight();
        _fontAscender = _fontFreeType->getFontAscender();
        _letterEdgeExtend = 2;

        if (_fontFreeType->isDistanceFieldEnabled())
        {
            _letterPadding += 2 * FontFreeType::DistanceMapSpread;    
        }

        auto outlineSize = _fontFreeType->getOutlineSize();
        if (outlineSize > 0)
        {
            _lineHeight += 2 * outlineSize;
        }

        
#if CC_ENABLE_CACHE_TEXTURE_DATA
        auto eventDispatcher = Director::getInstance()->getEventDispatcher();

        _rendererRecreatedListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, CC_CALLBACK_1(FontAtlas::listenRendererRecreated, this));
        eventDispatcher->addEventListenerWithFixedPriority(_rendererRecreatedListener, 1);
#endif
    }
}

void FontAtlas::reinit()
{
    if (_currentPageData)
    {
        delete []_currentPageData;
        _currentPageData = nullptr;
    }
    
    CC_SAFE_DELETE_ARRAY(_currentPageDataRGBA);
    
    auto texture = new (std::nothrow) Texture2D;
    
    _currentPageDataSize = CacheTextureWidth * CacheTextureHeight;
    
    auto outlineSize = _fontFreeType->getOutlineSize();
    if(outlineSize > 0)
    {
        _currentPageDataSize *= 2;
        
        _currentPageDataSizeRGBA = _currentPageDataSize * 2;
        _currentPageDataRGBA = new (std::nothrow) unsigned char[_currentPageDataSizeRGBA];
        memset(_currentPageDataRGBA, 0, _currentPageDataSizeRGBA);
    }
    
    _currentPageData = new (std::nothrow) unsigned char[_currentPageDataSize];
    memset(_currentPageData, 0, _currentPageDataSize);
    
    initTextureWithZeros(texture);

    addTexture(texture,0);
    texture->release();
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
    releaseTextures();

    delete []_currentPageData;

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32 && CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
    if (_iconv)
    {
        iconv_close(_iconv);
        _iconv = nullptr;
    }
#endif
}

void FontAtlas::initTextureWithZeros(Texture2D *texture)
{
    char *zeros = nullptr;    
    backend::PixelFormat pixelFormat;
    float outlineSize = _fontFreeType->getOutlineSize();
    size_t zeroBytes = 0;
    if (outlineSize > 0)
    {    
        //metal do no support AI88 format
        pixelFormat = backend::PixelFormat::RGBA8888;
        zeroBytes = CacheTextureWidth * CacheTextureWidth * 4;
    }
    else
    {
        pixelFormat = backend::PixelFormat::A8;
        zeroBytes = CacheTextureWidth * CacheTextureWidth;
    }
    zeros = new char[zeroBytes]();
    //std::fill(zeros, zeros + cnt, 0);
    texture->initWithData(zeros, zeroBytes, pixelFormat, CacheTextureWidth, CacheTextureHeight, Size(CacheTextureWidth, CacheTextureHeight));
    delete[] zeros;
}

void FontAtlas::reset()
{
    releaseTextures();
    
    _currLineHeight = 0;
    _currentPage = 0;
    _currentPageOrigX = 0;
    _currentPageOrigY = 0;
    _letterDefinitions.clear();
    
    reinit();
}

void FontAtlas::releaseTextures()
{
    for( auto &item: _atlasTextures)
    {
        item.second->release();
    }
    _atlasTextures.clear();
}

void FontAtlas::purgeTexturesAtlas()
{
    if (_fontFreeType)
    {
        reset();
        auto eventDispatcher = Director::getInstance()->getEventDispatcher();
        eventDispatcher->dispatchCustomEvent(CMD_PURGE_FONTATLAS,this);
        eventDispatcher->dispatchCustomEvent(CMD_RESET_FONTATLAS,this);
    }
}

void FontAtlas::listenRendererRecreated(EventCustom * /*event*/)
{
    purgeTexturesAtlas();
}

void FontAtlas::addLetterDefinition(char32_t utf32Char, const FontLetterDefinition &letterDefinition)
{
    _letterDefinitions[utf32Char] = letterDefinition;
}

void FontAtlas::scaleFontLetterDefinition(float scaleFactor)
{
    for (auto&& fontDefinition : _letterDefinitions) {
        auto& letterDefinition = fontDefinition.second;
        letterDefinition.width *= scaleFactor;
        letterDefinition.height *= scaleFactor;
        letterDefinition.offsetX *= scaleFactor;
        letterDefinition.offsetY *= scaleFactor;
        letterDefinition.xAdvance = (int)(letterDefinition.xAdvance * scaleFactor);
    }
}

bool FontAtlas::getLetterDefinitionForChar(char32_t utf32Char, FontLetterDefinition &letterDefinition)
{
    auto outIterator = _letterDefinitions.find(utf32Char);

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

void FontAtlas::conversionU32TOGB2312(const std::u32string& u32Text, std::unordered_map<unsigned int, unsigned int>& charCodeMap)
{
    size_t strLen = u32Text.length();
    auto gb2312StrSize = strLen * 2;
    auto gb2312Text = new (std::nothrow) char[gb2312StrSize];
    memset(gb2312Text, 0, gb2312StrSize);

    switch (_fontFreeType->getEncoding())
    {
    case FT_ENCODING_GB2312:
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
        std::u16string u16Text;
        cocos2d::StringUtils::UTF32ToUTF16(u32Text, u16Text);
        WideCharToMultiByte(936, NULL, (LPCWCH)u16Text.c_str(), strLen, (LPSTR)gb2312Text, gb2312StrSize, NULL, NULL);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        conversionEncodingJNI((char*)u32Text.c_str(), gb2312StrSize, "UTF-32LE", gb2312Text, "GB2312");
#else
        if (_iconv == nullptr)
        {
            _iconv = iconv_open("GBK//TRANSLIT", "UTF-32LE");
        }

        if (_iconv == (iconv_t)-1)
        {
            CCLOG("conversion from utf32 to gb2312 not available");
        }
        else
        {
            char* pin = (char*)u32Text.c_str();
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
    char32_t u32Code;
    for (size_t index = 0, gbIndex = 0; index < strLen; ++index)
    {
        u32Code = u32Text[index];
        if (u32Code < 256)
        {
            charCodeMap[u32Code] = u32Code;
            gbIndex += 1;
        }
        else
        {
            dst[0] = gb2312Text[gbIndex + 1];
            dst[1] = gb2312Text[gbIndex];
            charCodeMap[u32Code] = gb2312Code;

            gbIndex += 2;
        }
    }

    delete[] gb2312Text;
}

void FontAtlas::findNewCharacters(const std::u32string& u32Text, std::unordered_map<unsigned int, unsigned int>& charCodeMap)
{
    std::u32string newChars;
    FT_Encoding charEncoding = _fontFreeType->getEncoding();

    //find new characters
    if (_letterDefinitions.empty())
    {
        // fixed #16169: new android project crash in android 5.0.2 device (Nexus 7) when use 3.12.
        // While using clang compiler with gnustl_static on android, the copy assignment operator of `std::u32string`
        // will affect the memory validity, it means after `newChars` is destroyed, the memory of `u32Text` holds
        // will be a dead region. `u32text` represents the variable in `Label::_utf32Text`, when somewhere
        // allocates memory by `malloc, realloc, new, new[]`, the generated memory address may be the same
        // as `Label::_utf32Text` holds. If doing a `memset` or other memory operations, the orignal `Label::_utf32Text`
        // will be in an unknown state. Meanwhile, a bunch lots of logic which depends on `Label::_utf32Text`
        // will be broken.
        
        // newChars = u32Text;
        
        // Using `append` method is a workaround for this issue. So please be carefuly while using the assignment operator
        // of `std::u32string`.
        newChars.append(u32Text);
    }
    else
    {
        auto length = u32Text.length();
        newChars.reserve(length);
        for (size_t i = 0; i < length; ++i)
        {
            auto outIterator = _letterDefinitions.find(u32Text[i]);
            if (outIterator == _letterDefinitions.end())
            {
                newChars.push_back(u32Text[i]);
            }
        }
    }

    if (!newChars.empty())
    {
        switch (charEncoding)
        {
        case FT_ENCODING_UNICODE:
        {
            for (auto u32Code : newChars)
            {
                charCodeMap[u32Code] = u32Code;
            }
            break;
        }
        case FT_ENCODING_GB2312:
        {
            conversionU32TOGB2312(newChars, charCodeMap);
            break;
        }
        default:
            CCLOG("FontAtlas::findNewCharacters: Unsupported encoding:%d", charEncoding);
            break;
        }
    }
}

bool FontAtlas::prepareLetterDefinitions(const std::u32string& utf32Text)
{
    if (_fontFreeType == nullptr)
    {
        return false;
    }

    if (!_currentPageData)
        reinit(); 
    
    std::unordered_map<unsigned int, unsigned int> codeMapOfNewChar;
    findNewCharacters(utf32Text, codeMapOfNewChar);
    if (codeMapOfNewChar.empty())
    {
        return false;
    }

    int adjustForDistanceMap = _letterPadding / 2;
    int adjustForExtend = _letterEdgeExtend / 2;
    long bitmapWidth;
    long bitmapHeight;
    int glyphHeight;
    Rect tempRect;
    FontLetterDefinition tempDef;

    auto scaleFactor = CC_CONTENT_SCALE_FACTOR();
    auto  pixelFormat = _fontFreeType->getOutlineSize() > 0 ? backend::PixelFormat::AI88 : backend::PixelFormat::A8;

    int startY = (int)_currentPageOrigY;

    for (auto&& it : codeMapOfNewChar)
    {
        auto bitmap = _fontFreeType->getGlyphBitmap(it.second, bitmapWidth, bitmapHeight, tempRect, tempDef.xAdvance);
        if (bitmap && bitmapWidth > 0 && bitmapHeight > 0)
        {
            tempDef.validDefinition = true;
            tempDef.width = tempRect.size.width + _letterPadding + _letterEdgeExtend;
            tempDef.height = tempRect.size.height + _letterPadding + _letterEdgeExtend;
            tempDef.offsetX = tempRect.origin.x - adjustForDistanceMap - adjustForExtend;
            tempDef.offsetY = _fontAscender + tempRect.origin.y - adjustForDistanceMap - adjustForExtend;

            if (_currentPageOrigX + tempDef.width > CacheTextureWidth)
            {
                _currentPageOrigY += _currLineHeight;
                _currLineHeight = 0;
                _currentPageOrigX = 0;
                if (_currentPageOrigY + _lineHeight + _letterPadding + _letterEdgeExtend >= CacheTextureHeight)
                {
                    updateTextureContent(pixelFormat, startY);

                    startY = 0;

                    _currentPageOrigY = 0;
                    memset(_currentPageData, 0, _currentPageDataSize);
                    _currentPage++;
                    auto tex = new (std::nothrow) Texture2D;
                    
                    initTextureWithZeros(tex);

                    if (_antialiasEnabled)
                    {
                        tex->setAntiAliasTexParameters();
                    }
                    else
                    {
                        tex->setAliasTexParameters();
                    }
                    addTexture(tex, _currentPage);
                    
                    tex->release();
                }
            }
            glyphHeight = static_cast<int>(bitmapHeight) + _letterPadding + _letterEdgeExtend;
            if (glyphHeight > _currLineHeight)
            {
                _currLineHeight = glyphHeight;
            }
            _fontFreeType->renderCharAt(_currentPageData, (int)_currentPageOrigX + adjustForExtend, (int)_currentPageOrigY + adjustForExtend, bitmap, bitmapWidth, bitmapHeight);

            tempDef.U = _currentPageOrigX;
            tempDef.V = _currentPageOrigY;
            tempDef.textureID = _currentPage;
            _currentPageOrigX += tempDef.width + 1;
            // take from pixels to points
            tempDef.width = tempDef.width / scaleFactor;
            tempDef.height = tempDef.height / scaleFactor;
            tempDef.U = tempDef.U / scaleFactor;
            tempDef.V = tempDef.V / scaleFactor;
            tempDef.rotated = false;
        }
        else{
            if(bitmap)
                delete[] bitmap;
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
            tempDef.rotated = false;
            _currentPageOrigX += 1;
        }

        _letterDefinitions[it.first] = tempDef;
    }

    updateTextureContent(pixelFormat, startY);
    return true;
}

void FontAtlas::updateTextureContent(backend::PixelFormat format, int startY)
{
    unsigned char *data = nullptr;
    auto outlineSize = _fontFreeType->getOutlineSize();
    if (outlineSize > 0 && format == backend::PixelFormat::AI88)
    {
        int nLen = CacheTextureWidth * ((int)_currentPageOrigY - startY + _currLineHeight);
        data = _currentPageData + CacheTextureWidth * (int)startY * 2;
        memset(_currentPageDataRGBA, 0, 4 * nLen);
        for (auto i = 0; i < nLen; i++)
        {
            _currentPageDataRGBA[i*4] = data[i*2];
            _currentPageDataRGBA[i*4+3] = data[i*2+1];
        }
        _atlasTextures[_currentPage]->updateWithData(_currentPageDataRGBA, 0, startY, CacheTextureWidth, (int)_currentPageOrigY - startY + _currLineHeight);
    }
    else
    {
        data = _currentPageData + CacheTextureWidth * (int)startY;
       _atlasTextures[_currentPage]->updateWithData(data, 0, startY, CacheTextureWidth, (int)_currentPageOrigY - startY + _currLineHeight);
    }
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

void FontAtlas::setLineHeight(float newHeight)
{
    _lineHeight = newHeight;
}

std::string FontAtlas::getFontName() const
{
    std::string fontName = _fontFreeType ? _fontFreeType->getFontName() : "";
    if(fontName.empty()) return fontName;
    auto idx = fontName.rfind('/');
    if (idx != std::string::npos) { return fontName.substr(idx + 1); }
    idx = fontName.rfind('\\');
    if (idx != std::string::npos) { return fontName.substr(idx + 1); }
    return fontName;
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
