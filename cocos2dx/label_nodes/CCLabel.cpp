/****************************************************************************
 Copyright (c) 2013      Zynga Inc.

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

#include "CCLabel.h"
#include "CCStringBMFont.h"
#include "CCStringTTF.h"
#include "CCFontDefinition.h"
#include "CCFontCache.h"
#include "CCFontAtlasCache.h"

NS_CC_BEGIN

Label* Label::createWithTTF( const char* label, const char* tttFilePath, int fontSize, GlyphCollection glyphs, int lineSize )
{
    FontAtlas *tempAtlas = FontAtlasCache::getFontAtlasTTF(tttFilePath, fontSize, glyphs);
    if (!tempAtlas)
        return 0;
     
    // create the actual label
    StringTTF* templabel = StringTTF::create(tempAtlas, kTextAlignmentCenter, lineSize);
    
    if (templabel)
    {
        templabel->setText(label, lineSize, kTextAlignmentCenter, false);
        return templabel;
    }
    else
    {
        return 0;
    }
}

Label* Label::createWithBMFont( const char* label, const char* bmfontFilePath, int lineSize )
{
    
    FontAtlas *tempAtlas = FontAtlasCache::getFontAtlasFNT(bmfontFilePath);
    //if (!tempAtlas)
    //    return 0;
    
    return StringBMFont::create(label, bmfontFilePath, lineSize);
}

Label::Label()
{
}

Label::~Label()
{
}

NS_CC_END