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

#ifndef _CCFontAtlas_h_
#define _CCFontAtlas_h_

/// @cond DO_NOT_SHOW

#include <string>
#include <unordered_map>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "platform/CCStdC.h" // ssize_t on windows

NS_CC_BEGIN

class Font;
class Texture2D;
class EventCustom;
class EventListenerCustom;

struct FontLetterDefinition
{
    unsigned short  letteCharUTF16;
    float U;
    float V;
    float width;
    float height;
    float offsetX;
    float offsetY;
    int textureID;
    bool validDefinition;
    int xAdvance;

    int clipBottom;
};

class CC_DLL FontAtlas : public Ref
{
public:
    static const int CacheTextureWidth;
    static const int CacheTextureHeight;
    static const char* CMD_PURGE_FONTATLAS;
    static const char* CMD_RESET_FONTATLAS;
    /**
     * @js ctor
     */
    FontAtlas(Font &theFont);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~FontAtlas();
    
    void addLetterDefinition(const FontLetterDefinition &letterDefinition);
    bool getLetterDefinitionForChar(char16_t letteCharUTF16, FontLetterDefinition &outDefinition);
    
    bool prepareLetterDefinitions(const std::u16string& utf16String);

    inline const std::unordered_map<ssize_t, Texture2D*>& getTextures() const{ return _atlasTextures;}
    void  addTexture(Texture2D *texture, int slot);
    float getCommonLineHeight() const;
    void  setCommonLineHeight(float newHeight);
    
    Texture2D* getTexture(int slot);
    const Font* getFont() const;

    /** listen the event that renderer was recreated on Android/WP8
     It only has effect on Android and WP8.
     */
    void listenRendererRecreated(EventCustom *event);
    
    /** Removes textures atlas.
     It will purge the textures atlas and if multiple texture exist in the FontAtlas.
     */
    void purgeTexturesAtlas();

    /** sets font texture parameters:
     - GL_TEXTURE_MIN_FILTER = GL_LINEAR
     - GL_TEXTURE_MAG_FILTER = GL_LINEAR
     */
     void setAntiAliasTexParameters();

     /** sets font texture parameters:
     - GL_TEXTURE_MIN_FILTER = GL_NEAREST
     - GL_TEXTURE_MAG_FILTER = GL_NEAREST
     */
     void setAliasTexParameters();

protected:
    void relaseTextures();
    std::unordered_map<ssize_t, Texture2D*> _atlasTextures;
    std::unordered_map<unsigned short, FontLetterDefinition> _fontLetterDefinitions;
    float _commonLineHeight;
    Font * _font;

    // Dynamic GlyphCollection related stuff
    int _currentPage;
    unsigned char *_currentPageData;
    int _currentPageDataSize;
    float _currentPageOrigX;
    float _currentPageOrigY;
    float _letterPadding;

    int _fontAscender;
    EventListenerCustom* _rendererRecreatedListener;
    bool _antialiasEnabled;
};

NS_CC_END

/// @endcond
#endif /* defined(__cocos2d_libs__CCFontAtlas__) */
