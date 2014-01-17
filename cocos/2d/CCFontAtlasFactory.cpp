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

#include "CCFontAtlasFactory.h"
#include "CCFontFNT.h"

// carloX this NEEDS to be changed
#include "CCLabelBMFont.h"

NS_CC_BEGIN

FontAtlas * FontAtlasFactory::createAtlasFromTTF(const std::string& fntFilePath, int fontSize, GlyphCollection glyphs, const char *customGlyphs, bool useDistanceField)
{
    
    Font *font = Font::createWithTTF(fntFilePath, fontSize, glyphs, customGlyphs);
    if (font)
    {
        font->setDistanceFieldEnabled(useDistanceField);
        return font->createFontAtlas();
    }
    else
    {
        return nullptr;
    }
}

FontAtlas * FontAtlasFactory::createAtlasFromFNT(const std::string& fntFilePath)
{
    Font *font = Font::createWithFNT(fntFilePath);
    
    if(font)
    {
        return font->createFontAtlas();
    }
    else
    {
        return nullptr;
    }
}

FontAtlas * FontAtlasFactory::createAtlasFromCharMap(const std::string& plistFile)
{
    Font *font = Font::createWithCharMap(plistFile);

    if(font)
    {
        return font->createFontAtlas();
    }
    else
    {
        return nullptr;
    }
}

FontAtlas * FontAtlasFactory::createAtlasFromCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    Font *font = Font::createWithCharMap(texture,itemWidth,itemHeight,startCharMap);

    if(font)
    {
        return font->createFontAtlas();
    }
    else
    {
        return nullptr;
    }
}

FontAtlas * FontAtlasFactory::createAtlasFromCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    Font *font = Font::createWithCharMap(charMapFile,itemWidth,itemHeight,startCharMap);

    if(font)
    {
        return font->createFontAtlas();
    }
    else
    {
        return nullptr;
    }
}

NS_CC_END
