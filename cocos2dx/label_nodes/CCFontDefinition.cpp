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

#include "cocos2d.h"
#include "CCFontDefinition.h"

NS_CC_BEGIN


FontDefinitionTTF::FontDefinitionTTF():_textImages(0), _commonLineHeight(0)
{
}

FontDefinitionTTF* FontDefinitionTTF::create(const char *fontName, int fontSize, const char *letters, int textureSize )
{
    FontDefinitionTTF *ret = new FontDefinitionTTF;
    
    if(!ret)
        return 0;
    
    if ( ret->initDefinition( fontName, fontSize, letters, textureSize ) )
    {
        return ret;
    }
    else
    {
        delete ret;
        return 0;
    }
}

FontDefinitionTTF::~FontDefinitionTTF()
{
    if (_textImages)
    {
        delete _textImages;
    }
}

bool FontDefinitionTTF::prepareLetterDefinitions(TextFontPagesDef *pageDefs)
{
    // get all the pages
    TextFontPagesDef *pPages = pageDefs;
    if (!pPages)
        return (false);
    
    float maxLineHeight = -1;
    
    // loops all the pages
    for (int cPages = 0; cPages<pPages->getNumPages(); ++cPages)
    {
        // loops all the lines in this page
        for (int cLines = 0; cLines<pPages->getPageAt(cPages)->getNumLines(); ++cLines)
        {
            float posXUV       = 0.0;
            float posYUV       = pPages->getPageAt(cPages)->getLineAt(cLines)->getY();
            
            int   charsCounter = 0;
            
            for (int c = 0; c < pPages->getPageAt(cPages)->getLineAt(cLines)->getNumGlyph(); ++c)
            {
                
                // the current glyph
                GlyphDef currentGlyph = pPages->getPageAt(cPages)->getLineAt(cLines)->getGlyphAt(c);
                
                // letter width
                float letterWidth  = currentGlyph.getRect().size.width;
                
                // letter height
                float letterHeight = pPages->getPageAt(cPages)->getLineAt(cLines)->getHeight();
                
                // add this letter definition
                FontLetterDefinition tempDef;
                
                
                // carloX little hack (this should be done outside the loop)
                if (posXUV == 0.0)
                    posXUV = currentGlyph.getPadding();
                
                tempDef.validDefinition  =    currentGlyph.isValid();
                
                if (tempDef.validDefinition)
                {
                    tempDef.letteCharUTF16   =    currentGlyph.getUTF8Letter();
                    tempDef.width            =    letterWidth  + currentGlyph.getPadding();
                    tempDef.height           =    (letterHeight - 1);
                    tempDef.U                =    (posXUV       - 1);
                    tempDef.V                =    posYUV;
                    
                    tempDef.offsetX          =    currentGlyph.getRect().origin.x;
                    tempDef.offsetY          =    currentGlyph.getRect().origin.y;
                    
                    tempDef.textureID        =    cPages;
                    tempDef.commonLineHeight =    currentGlyph.getCommonHeight();
                    
                    // take from pixels to points
                    tempDef.width  =    tempDef.width  / CC_CONTENT_SCALE_FACTOR();
                    tempDef.height =    tempDef.height / CC_CONTENT_SCALE_FACTOR();
                    tempDef.U      =    tempDef.U      / CC_CONTENT_SCALE_FACTOR();
                    tempDef.V      =    tempDef.V      / CC_CONTENT_SCALE_FACTOR();
                    
                    if (tempDef.commonLineHeight>maxLineHeight)
                        maxLineHeight = tempDef.commonLineHeight;
                }
                else
                {
                    tempDef.letteCharUTF16   =    currentGlyph.getUTF8Letter();
                    tempDef.commonLineHeight =    0;
                    tempDef.width            =    0;
                    tempDef.height           =    0;
                    tempDef.U                =    0;
                    tempDef.V                =    0;
                    tempDef.offsetX          =    0;
                    tempDef.offsetY          =    0;
                    tempDef.textureID        =    0;
                }
                
                
                // add this definition
                addLetterDefinition(tempDef);
                
                // move bounding box to the next letter
                posXUV += letterWidth + currentGlyph.getPadding();
                
                // next char in the string
                ++charsCounter;
            }
        }
    }
    
    // store the common line height
    _commonLineHeight = maxLineHeight;
    
    //
    return true;
}

bool FontDefinitionTTF::initDefinition(const char *fontName, int fontSize, const char *letters, int textureSize)
{
    // preare texture/image stuff
    _textImages = new TextImage();
    if (!_textImages)
        return false;
    
    if (!_textImages->initWithString(letters, textureSize, textureSize, fontName, fontSize, true))
    {
        delete _textImages;
        _textImages = 0;
        return false;
    }
    
    // prepare the new letter definition
    return prepareLetterDefinitions(_textImages->getPages());
}

void FontDefinitionTTF::addLetterDefinition(FontLetterDefinition &defToAdd)
{
    if (_fontLettersDefinitionUTF16.find(defToAdd.letteCharUTF16) == _fontLettersDefinitionUTF16.end())
    {
        _fontLettersDefinitionUTF16[defToAdd.letteCharUTF16] = defToAdd;
    }
}

FontLetterDefinition & FontDefinitionTTF::getLetterDefinition(unsigned short int theLetter)
{
    return _fontLettersDefinitionUTF16[theLetter];
}

Texture2D * FontDefinitionTTF::getTexture(int index)
{
    TextFontPagesDef *pPages = _textImages->getPages();
    
    if (!pPages)
        return nullptr;
    
    return pPages->getPageAt(index)->getPageTexture();
}

int FontDefinitionTTF::getNumTextures()
{
    TextFontPagesDef *pPages = _textImages->getPages();
    if (pPages)
    {
        return pPages->getNumPages();
    }
    
    return 0;
}

FontAtlas * FontDefinitionTTF::createFontAtlas()
{
    FontAtlas *retAtlas = new FontAtlas( *_textImages->getFont() );
    
    if (!retAtlas)
        return 0;
    
    // add all the textures
    int numTextures = getNumTextures();
    if (!numTextures)
        return 0;
    
    for (int c = 0; c<numTextures; ++c)
        retAtlas->addTexture(*getTexture(c), c);
    
    // set the common line height
    retAtlas->setCommonLineHeight(getCommonLineHeight() * 0.8);
    
    
    for( auto &item: _fontLettersDefinitionUTF16 )
    {
        if ( item.second.validDefinition )
        {
            FontLetterDefinition tempDefinition = item.second;
            tempDefinition.offsetX = 0;
            tempDefinition.anchorX = 0.0f;
            tempDefinition.anchorY = 1.0f;
            retAtlas->addLetterDefinition(tempDefinition);
        }
    }
    
    // done here
    return retAtlas;
}

NS_CC_END
