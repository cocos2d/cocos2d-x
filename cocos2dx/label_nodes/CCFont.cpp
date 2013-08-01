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

#include "CCFont.h"
#include "ccUTF8.h"

#include "CCFontFNT.h"
#include "CCFontFreeType.cpp"

NS_CC_BEGIN

static const char *glyphASCII = "\"!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ ";

static const char *glyphNEHE =  "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ";


const char * getGlyphCollection(GlyphCollection glyphs)
{
    switch (glyphs)
    {
        case GlyphCollection::NEHE:
            return glyphNEHE;
            break;
            
        case GlyphCollection::ASCII:
            return glyphASCII;
            break;
            
        default:
            return 0;
            break;
    }
}

Font* Font::createWithTTF(const char* fntName, int fontSize, GlyphCollection glyphs, const char *customGlyphs)
{
    // create the font
    Font *tempFont = new FontFreeType();
    
    if (!tempFont)
        return nullptr;
    
    if( !tempFont->createFontObject(fntName, fontSize))
        return false;
    
    FontDefinitionTTF *def = 0;
    
    if ( (glyphs == GlyphCollection::NEHE) || (glyphs == GlyphCollection::ASCII) )
    {
        def = FontDefinitionTTF::create(fntName, fontSize, getGlyphCollection(glyphs));
    }
    else
    {
        if( glyphs == GlyphCollection::DYNAMIC )
        {
            log("ERROR: GlyphCollection::DYNAMIC is not supported yet!");
            return nullptr;
        }
        else
        {
            if ( !customGlyphs )
            {
                log("ERROR: GlyphCollection::CUSTOM used but no input glyphs provided!");
                return nullptr;
            }
            
            def = FontDefinitionTTF::create(fntName, fontSize, customGlyphs);
        }
    }
    
    if(!def)
        return nullptr;
    
    

    return nullptr;
}

Font* Font::createWithFNT(const char* fntFilePath)
{
    CCBMFontConfiguration *newConf = FNTConfigLoadFile(fntFilePath);
    if (!newConf)
        return nullptr;
    
    // add the texture
    Texture2D *tempTexture = TextureCache::getInstance()->addImage(newConf->getAtlasName());
    if ( !tempTexture )
    {
        delete newConf;
        return nullptr;
    }
    
    FontFNT *tempFont = new FontFNT(newConf);
    
    if (!tempFont)
    {
        delete newConf;
        return nullptr;
    }
    
    return tempFont;
}

unsigned short int  * Font::getUTF16Text(const char *pText, int &outNumLetters)
{
    unsigned short* utf16String = cc_utf8_to_utf16(pText);
    
    if(!utf16String)
        return 0;
    
    outNumLetters = cc_wcslen(utf16String);
    return utf16String;
}

int Font::getUTF16TextLenght(unsigned short int *pText)
{
     return cc_wcslen(pText);
}

unsigned short int  * Font::trimUTF16Text(unsigned short int *pText, int newBegin, int newEnd)
{
    if ( newBegin<0 || newEnd<=0 )
        return 0;
    
    if ( newBegin>=newEnd )
        return 0;
    
    if (newEnd >= cc_wcslen(pText))
        return 0;
    
    int newLenght = newEnd - newBegin + 2;
    unsigned short* trimmedString = new unsigned short[newLenght];
    
    for(int c = 0; c < (newLenght-1); ++c)
    {
        trimmedString[c] = pText[newBegin + c];
    }
    
    // last char
    trimmedString[newLenght-1] = 0x0000;
    
    // done
    return trimmedString;
}

Rect Font::getRectForChar(unsigned short theChar)
{
    Rect temp;
    temp.size.width  = 0;
    temp.size.height = 0;
    temp.origin.x = 0;
    temp.origin.y = 0;
    
    return temp;
}

NS_CC_END


