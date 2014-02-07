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

#include "CCFontCharMap.h"
#include "CCFontAtlas.h"
#include "platform/CCFileUtils.h"
#include "CCDirector.h"
#include "CCTextureCache.h"
#include "ccUTF8.h"

NS_CC_BEGIN

FontCharMap * FontCharMap::create(const std::string& plistFile)
{
    std::string pathStr = FileUtils::getInstance()->fullPathForFilename(plistFile);
    std::string relPathStr = pathStr.substr(0, pathStr.find_last_of("/"))+"/";

    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(pathStr.c_str());

    CCASSERT(dict["version"].asInt() == 1, "Unsupported version. Upgrade cocos2d version");

    std::string textureFilename = relPathStr + dict["textureFilename"].asString();

    unsigned int width = dict["itemWidth"].asInt() / CC_CONTENT_SCALE_FACTOR();
    unsigned int height = dict["itemHeight"].asInt() / CC_CONTENT_SCALE_FACTOR();
    unsigned int startChar = dict["firstChar"].asInt();

    Texture2D *tempTexture = Director::getInstance()->getTextureCache()->addImage(textureFilename);
    if (!tempTexture)
    {
        return nullptr;
    }
    
    FontCharMap *tempFont =  new FontCharMap(tempTexture,width,height,startChar);
    
    if (!tempFont)
    {
        return nullptr;
    }
    tempFont->autorelease();
    return tempFont;
}

FontCharMap* FontCharMap::create(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    Texture2D *tempTexture = Director::getInstance()->getTextureCache()->addImage(charMapFile);

    if (!tempTexture)
    {
        return nullptr;
    }

    FontCharMap *tempFont =  new FontCharMap(tempTexture,itemWidth,itemHeight,startCharMap);

    if (!tempFont)
    {
        return nullptr;
    }
    tempFont->autorelease();
    return tempFont;
}

FontCharMap* FontCharMap::create(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    FontCharMap *tempFont =  new FontCharMap(texture,itemWidth,itemHeight,startCharMap);

    if (!tempFont)
    {
        return nullptr;
    }
    tempFont->autorelease();
    return tempFont;
}

FontCharMap::~FontCharMap()
{

}

int * FontCharMap::getHorizontalKerningForTextUTF16(unsigned short *text, int &outNumLetters) const
{
    if (!text)
        return 0;
    
    outNumLetters = cc_wcslen(text);
    
    if (!outNumLetters)
        return 0;
    
    int *sizes = new int[outNumLetters];
    if (!sizes)
        return 0;
    
    for (int c = 0; c < outNumLetters; ++c)
    {
        sizes[c] = 0;
    }
    
    return sizes;
}

FontAtlas * FontCharMap::createFontAtlas()
{
    FontAtlas *tempAtlas = new FontAtlas(*this);
    if (!tempAtlas)
        return nullptr;
    
    Size s = _texture->getContentSize();

    int itemsPerColumn = (int)(s.height / _itemHeight);
    int itemsPerRow = (int)(s.width / _itemWidth);

    tempAtlas->setCommonLineHeight(_itemHeight);
    
    FontLetterDefinition tempDefinition;
    tempDefinition.textureID = 0;
    tempDefinition.offsetX  = 0.0f;
    tempDefinition.offsetY  = 0.0f;
    tempDefinition.validDefinition = true;
    tempDefinition.width    = _itemWidth;
    tempDefinition.height   = _itemHeight;
    tempDefinition.xAdvance = _itemWidth * CC_CONTENT_SCALE_FACTOR();

    int charId = _mapStartChar;
    for (int row = 0; row < itemsPerColumn; ++row)
    {
        for (int col = 0; col < itemsPerRow; ++col)
        {
            tempDefinition.letteCharUTF16 = charId;

            tempDefinition.U        = _itemWidth * col;
            tempDefinition.V        = _itemHeight * row;           

            tempAtlas->addLetterDefinition(tempDefinition);
            charId++;
        }
    }
    
    tempAtlas->addTexture(*_texture,0);

    return tempAtlas;
}

NS_CC_END