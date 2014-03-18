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
#ifndef _CCFontAtlas_h_
#define _CCFontAtlas_h_

#include <unordered_map>
#include "CCPlatformMacros.h"
#include "CCRef.h"

NS_CC_BEGIN

//fwd
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
};

class CC_DLL FontAtlas : public Ref
{
public:
    static const int CacheTextureWidth;
    static const int CacheTextureHeight;
    static const char* EVENT_PURGE_TEXTURES;
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
    bool getLetterDefinitionForChar(unsigned short  letteCharUTF16, FontLetterDefinition &outDefinition);
    
    bool prepareLetterDefinitions(unsigned short  *utf16String);

    inline const std::unordered_map<int, Texture2D*>& getTextures() const{ return _atlasTextures;}
    void  addTexture(Texture2D *texture, int slot);
    float getCommonLineHeight() const;
    void  setCommonLineHeight(float newHeight);
    
    Texture2D* getTexture(int slot);
    const Font* getFont() const;

    /** Listen "come to background" message, and clear the texture atlas.
     It only has effect on Android.
     */
    void listenToBackground(EventCustom *event);

    /** Listen "come to foreground" message and restore the texture atlas.
     It only has effect on Android.
     */
    void listenToForeground(EventCustom *event);
    
    /** Removes textures atlas.
     It will purge the textures atlas and if multiple texture exist in the FontAtlas.
     */
    void purgeTexturesAtlas();

private:

    void relaseTextures();
    std::unordered_map<int, Texture2D*> _atlasTextures;
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
    bool  _makeDistanceMap;

    int _fontAscender;
    EventListenerCustom* _toBackgroundListener;
    EventListenerCustom* _toForegroundListener;
};


NS_CC_END


#endif /* defined(__cocos2d_libs__CCFontAtlas__) */
