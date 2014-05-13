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

#include "CCFont.h"
#include "ccUTF8.h"

NS_CC_BEGIN

const char * Font::_glyphASCII = "\"!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ ";

const char * Font::_glyphNEHE =  "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ";


Font::Font() : 
_usedGlyphs(GlyphCollection::ASCII)
, _customGlyphs(nullptr)
{
}

const char * Font::getGlyphCollection(GlyphCollection glyphs) const
{
    switch (glyphs)
    {
        case GlyphCollection::NEHE:
            return _glyphNEHE;
            break;
            
        case GlyphCollection::ASCII:
            return _glyphASCII;
            break;
            
        default:
            return 0;
            break;
    }
}

void Font::setCurrentGlyphCollection(GlyphCollection glyphs, const char *customGlyphs)
{
    if (_customGlyphs)
        delete [] _customGlyphs;
    
    switch (glyphs)
    {
        case GlyphCollection::NEHE:
            _customGlyphs = 0;
            break;
            
        case GlyphCollection::ASCII:
            _customGlyphs = 0;
            break;
            
        default:
            if (customGlyphs)
            {
                size_t lenght = strlen(customGlyphs);
                _customGlyphs = new char [lenght + 2];
                memcpy(_customGlyphs, customGlyphs, lenght);

                _customGlyphs[lenght]   = 0;
                _customGlyphs[lenght+1] = 0;
            }           
            
            break;
    }
    _usedGlyphs = glyphs;
}

const char * Font::getCurrentGlyphCollection() const
{
    if (_customGlyphs)
    {
        return _customGlyphs;
    }
    else
    {
        return getGlyphCollection(_usedGlyphs);
    }
}


NS_CC_END


