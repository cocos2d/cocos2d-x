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

#ifndef _CCFontFNT_h_
#define _CCFontFNT_h_

/// @cond DO_NOT_SHOW

#include "2d/CCFont.h"
#include <set>
#include <unordered_map>

NS_CC_BEGIN

/**
@struct BMFontDef
BMFont definition
*/
typedef struct _BMFontDef {
    //! ID of the character
    unsigned int charID;
    //! origin and size of the font
    Rect rect;
    //! The X amount the image should be offset when drawing the image (in pixels)
    short xOffset;
    //! The Y amount the image should be offset when drawing the image (in pixels)
    short yOffset;
    //! The amount to move the current position after drawing the character (in pixels)
    short xAdvance;
} BMFontDef;

/** @struct BMFontPadding
BMFont padding
@since v0.8.2
*/
typedef struct _BMFontPadding {
    /// padding left
    int left;
    /// padding top
    int top;
    /// padding right
    int right;
    /// padding bottom
    int bottom;
} BMFontPadding;

/** @brief BMFontConfiguration has parsed configuration of the .fnt file
@since v0.8
*/
class CC_DLL BMFontConfiguration : public Ref
{
    // FIXME: Creating a public interface so that the bitmapFontArray[] is accessible
public://@public
    // BMFont definitions
    std::unordered_map<int /* key */, BMFontDef /* fontDef */> _fontDefDictionary;

    //! FNTConfig: Common Height Should be signed (issue #1343)
    int _commonHeight;

    //! Padding
    BMFontPadding    _padding;

    //! atlas name
    std::string _atlasName;

    //! values for kerning
    std::unordered_map<uint64_t /* key */, int /* amount */> _kerningDictionary;

    // Character Set defines the letters that actually exist in the font
    std::set<unsigned int>* _characterSet;

    //! Font Size
    int _fontSize;
public:
    /**
     * @js ctor
     */
    BMFontConfiguration();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~BMFontConfiguration();
    /**
     * @js NA
     * @lua NA
     */
    std::string description() const;

    /** allocates a BMFontConfiguration with a FNT file */
    static BMFontConfiguration* create(const std::string& FNTfile);

    /** initializes a BitmapFontConfiguration with a FNT file */
    bool initWithFNTfile(const std::string& FNTfile);

    const std::string& getAtlasName() { return _atlasName; }
    void setAtlasName(const std::string& atlasName) { _atlasName = atlasName; }

    std::set<unsigned int>* getCharacterSet() const;

protected:
    virtual std::set<unsigned int>* parseConfigFile(const std::string& controlFile);
    virtual std::set<unsigned int>* parseBinaryConfigFile(unsigned char* pData, unsigned long size, const std::string& controlFile);

private:
    unsigned int parseCharacterDefinition(const char* line);
    void parseInfoArguments(const char* line);
    void parseCommonArguments(const char* line);
    void parseImageFileName(const char* line, const std::string& fntFile);
    void parseKerningEntry(const char* line);
    void purgeKerningDictionary();
    void purgeFontDefDictionary();
};

class CC_DLL FontFNT : public Font
{
    
public:
    
    static FontFNT* create(const std::string& fntFilePath, const Rect& imageRect, bool imageRotated);
    static FontFNT* create(const std::string& fntFilePath, const std::string& subTextureKey);
    static FontFNT* create(const std::string& fntFilePath);

    CC_DEPRECATED_ATTRIBUTE static FontFNT* create(const std::string& fntFilePath, const Vec2& imageOffset = Vec2::ZERO);

    /** Purges the cached data.
    Removes from memory the cached configurations and the atlas name dictionary.
    */
    static void purgeCachedData();
    virtual int* getHorizontalKerningForTextUTF32(const std::u32string& text, int &outNumLetters) const override;
    virtual FontAtlas *createFontAtlas() override;

    void setFontSize(float fontSize);
    float getFontSize() const { return _fontSize; }

    int getOriginalFontSize()const;

    static void reloadBMFontResource(const std::string& fntFilePath);

protected:
    
    FontFNT(BMFontConfiguration* theContfig, const Rect& imageRect, bool imageRotated);
    FontFNT(BMFontConfiguration* theContfig);

    /**
     * @js NA
     * @lua NA
     */
    virtual ~FontFNT();

    BMFontConfiguration* _configuration;

    int  getHorizontalKerningForChars(char32_t firstChar, char32_t secondChar) const;

    Rect _imageRectInPoints;
    bool _imageRotated;

    //User defined font size
    float  _fontSize;
};

/// @endcond

NS_CC_END

#endif /* defined(__cocos2d_libs__CCFontFNT__) */
