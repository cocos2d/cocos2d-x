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
#include "CCFontAtlas.h"
#include "CCFont.h"
#include "CCFontFreeType.h"

NS_CC_BEGIN

FontAtlas::FontAtlas(Font &theFont) : 
_font(&theFont),
_currentPageData(nullptr)
{
    _font->retain();
   
    FontFreeType* fontTTf = dynamic_cast<FontFreeType*>(_font);
    if (fontTTf && fontTTf->isDynamicGlyphCollection())
    {
        _currentPageLineHeight = _font->getFontMaxHeight();
        _commonLineHeight = _currentPageLineHeight * 0.8f;
        Texture2D * tex = new Texture2D;
        _currentPage = 0;
        _currentPageOrigX = 0;
        _currentPageOrigY = 0;
        _letterPadding = 5;
        _currentPageDataSize = (1024 * 1024 * 4);

        _currentPageData = new unsigned char[_currentPageDataSize];       
        memset(_currentPageData, 0, _currentPageDataSize);  
        addTexture(*tex,0);
        tex->release();
    }
}

FontAtlas::~FontAtlas()
{
    _font->release();
    relaseTextures();

    delete []_currentPageData;
}

void FontAtlas::relaseTextures()
{
    for( auto &item: _atlasTextures)
    {
        item.second->release();
    }
}

void FontAtlas::addLetterDefinition(const FontLetterDefinition &letterDefinition)
{
    _fontLetterDefinitions[letterDefinition.letteCharUTF16] = letterDefinition;
}

bool FontAtlas::getLetterDefinitionForChar(unsigned short  letteCharUTF16, FontLetterDefinition &outDefinition)
{
    auto outIterator = _fontLetterDefinitions.find(letteCharUTF16);
    
    if (outIterator != _fontLetterDefinitions.end())
    {
        outDefinition = (*outIterator).second;
        return true;
    }
    else
    {
        return false;
    }
}

bool FontAtlas::prepareLetterDefinitions(unsigned short *utf16String)
{
    if(_currentPageData == nullptr)
        return false;

    FontFreeType* fontTTf = (FontFreeType*)_font;

    std::vector<FontLetterDefinition> fontDefs;
    int length = cc_wcslen(utf16String);

    //find out new letter
    for (int i = 0; i < length; ++i)
    {
        auto outIterator = _fontLetterDefinitions.find(utf16String[i]);

        if (outIterator == _fontLetterDefinitions.end())
        {         
            Rect tempRect;           

            FontLetterDefinition tempDef;
            tempDef.offsetX = 0;
            tempDef.anchorX = 0.0f;
            tempDef.anchorY = 1.0f;

            if (!fontTTf->getBBOXFotChar(utf16String[i], tempRect))
            {
                tempDef.validDefinition = false;
                tempDef.letteCharUTF16   = utf16String[i];
                tempDef.commonLineHeight = 0;
                tempDef.width            = 0;
                tempDef.height           = 0;
                tempDef.U                = 0;
                tempDef.V                = 0;            
                tempDef.offsetY          = 0;
                tempDef.textureID        = 0;
            }
            else
            {
                tempDef.validDefinition = true;
                tempDef.letteCharUTF16   = utf16String[i];
                tempDef.width            = tempRect.size.width  + _letterPadding;
                tempDef.height           = _currentPageLineHeight - 1;             
                tempDef.offsetY          = tempRect.origin.y;
                tempDef.commonLineHeight = _currentPageLineHeight;
                        
            }            
            fontDefs.push_back(tempDef);
        }       
    }

    float scaleFactor = CC_CONTENT_SCALE_FACTOR();
    int newLetterCount = fontDefs.size();
    float glyphWidth;
    for (int i = 0; i < newLetterCount; ++i)
    {
        if (fontDefs[i].validDefinition)
        {
            _currentPageOrigX += _letterPadding;
            glyphWidth = fontDefs[i].width - _letterPadding;

            if (_currentPageOrigX + glyphWidth > 1024)
            {
                _currentPageOrigY += _currentPageLineHeight;
                if(_currentPageOrigY >= 1024)
                {             
                    _atlasTextures[_currentPage]->initWithData(_currentPageData, _currentPageDataSize, Texture2D::PixelFormat::RGBA8888, 1024, 1024, Size(1024, 1024) );
                    _currentPageOrigX = 0;
                    _currentPageOrigY = 0;

                    delete []_currentPageData;
                    _currentPageData = new unsigned char[_currentPageDataSize];
                    if(_currentPageData == nullptr)
                        return false;
                    memset(_currentPageData, 0, _currentPageDataSize);
                    _currentPage++;
                    Texture2D* tex = new Texture2D;
                    addTexture(*tex,_currentPage);
                    tex->release();
                }
            }
            renderCharAt(fontDefs[i].letteCharUTF16,_currentPageOrigX,_currentPageOrigY,_currentPageData,1024);

            fontDefs[i].U                = _currentPageOrigX - 1;
            fontDefs[i].V                = _currentPageOrigY;
            fontDefs[i].textureID        = _currentPage;
            // take from pixels to points
            fontDefs[i].width  =    fontDefs[i].width  / scaleFactor;
            fontDefs[i].height =    fontDefs[i].height / scaleFactor;      
            fontDefs[i].U      =    fontDefs[i].U      / scaleFactor;
            fontDefs[i].V      =    fontDefs[i].V      / scaleFactor;
        }
        else
            glyphWidth = 0;       
       
        this->addLetterDefinition(fontDefs[i]);
        _currentPageOrigX += glyphWidth;
    }
    if(newLetterCount > 0)
        _atlasTextures[_currentPage]->initWithData(_currentPageData, _currentPageDataSize, Texture2D::PixelFormat::RGBA8888, 1024, 1024, Size(1024, 1024) );
    return true;
}

bool FontAtlas::renderCharAt(unsigned short int charToRender, int posX, int posY, unsigned char *destMemory, int destSize)
{
    unsigned char *sourceBitmap = 0;
    int sourceWidth  = 0;
    int sourceHeight = 0;

    // get the glyph's bitmap
    sourceBitmap = _font->getGlyphBitmap(charToRender, sourceWidth, sourceHeight);

    if (!sourceBitmap)
        return false;

    int iX = posX;
    int iY = posY;

    for (int y = 0; y < sourceHeight; ++y)
    {
        int bitmap_y = y * sourceWidth;

        for (int x = 0; x < sourceWidth; ++x)
        {
            unsigned char cTemp = sourceBitmap[bitmap_y + x];

            // the final pixel
            int iTemp = cTemp << 24 | cTemp << 16 | cTemp << 8 | cTemp;
            *(int*) &destMemory[(iX + ( iY * destSize ) ) * 4] = iTemp;

            iX += 1;
        }

        iX  = posX;
        iY += 1;
    }

    //everything good
    return true;
}

void FontAtlas::addTexture(Texture2D &texture, int slot)
{
    texture.retain();
    _atlasTextures[slot] = &texture;
}

Texture2D & FontAtlas::getTexture(int slot)
{
    return *(_atlasTextures[slot]);
}

float FontAtlas::getCommonLineHeight() const
{
    return _commonLineHeight;
}

void  FontAtlas::setCommonLineHeight(float newHeight)
{
    _commonLineHeight = newHeight;
}

const Font * FontAtlas::getFont() const
{
    return _font;
}

NS_CC_END