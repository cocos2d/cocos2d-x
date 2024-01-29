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

#ifndef _CCFontCharMap_h_
#define _CCFontCharMap_h_

/// @cond DO_NOT_SHOW

#include "2d/CCFont.h"

NS_CC_BEGIN

class Texture2D;
class FontCharMap : public Font
{  
public:
    static FontCharMap * create(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    static FontCharMap * create(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    static FontCharMap * create(const std::string& plistFile);
    
    virtual int* getHorizontalKerningForTextUTF32(const std::u32string& text, int &outNumLetters) const override;
    virtual FontAtlas *createFontAtlas() override;
    
protected:    
    FontCharMap(Texture2D* texture,int itemWidth, int itemHeight, int startCharMap)
        :_texture(texture)
        ,_mapStartChar(startCharMap)
        ,_itemWidth(itemWidth)
        ,_itemHeight(itemHeight)
    {}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~FontCharMap();
    
private:
    Texture2D* _texture;
    int _mapStartChar;
    int _itemWidth;
    int _itemHeight;

};

/// @endcond

NS_CC_END

#endif /* defined(_CCFontCharMap_h_) */
