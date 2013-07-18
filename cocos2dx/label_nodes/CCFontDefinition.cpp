//
//  CCFontDefinition.cpp
//  TestNewStringStuff
//
//  Created by Carlo Morgantini on 4/11/13.
//
//

#include "cocos2d.h"
#include "CCFontDefinition.h"

NS_CC_BEGIN


LabelFontDefinition::LabelFontDefinition():_textImages(0), _commonLineHeight(0)
{
}

LabelFontDefinition::~LabelFontDefinition()
{
    if (_textImages)
    {
        delete _textImages;
    }
}


bool LabelFontDefinition::prepareLetterDefinitions(TextFontPagesDef *pageDefs)
{
    // constants
    float LINE_PADDING  = 1.9;
    float PIXEL_PADDING = 1.0;
    
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
                LetterDefinition tempDef;
                
                tempDef.letteCharUTF8    =    currentGlyph.getUTF8Letter();
                tempDef.width            =    letterWidth + PIXEL_PADDING;
                tempDef.height           =    letterHeight;
                tempDef.U                =    posXUV + LINE_PADDING - PIXEL_PADDING;
                tempDef.V                =    posYUV;
                tempDef.offsetX           =    currentGlyph.getRect().origin.x;
                tempDef.textureID        =    cPages;
                tempDef.commonLineHeight =    currentGlyph.getCommonHeight();
                
                
                // take from pixels to points
                tempDef.width  =    tempDef.width  / CC_CONTENT_SCALE_FACTOR();
                tempDef.height =    tempDef.height / CC_CONTENT_SCALE_FACTOR();
                tempDef.U      =    tempDef.U      / CC_CONTENT_SCALE_FACTOR();
                tempDef.V      =    tempDef.V      / CC_CONTENT_SCALE_FACTOR();
                
                if (tempDef.commonLineHeight>maxLineHeight)
                    maxLineHeight = tempDef.commonLineHeight;
                
                // add this definition
                addLetterDef(tempDef);
                
                // move bounding box to the next letter
                posXUV += letterWidth + currentGlyph.getPadding();
                
                // next char in the string
                ++charsCounter;
            }
        }
    }
    
    // store the common line height
    _commonLineHeight = maxLineHeight;
    
    return true;
}

bool LabelFontDefinition::prepareLetterDefinitionsNew(TextFontPagesDef *pageDefs)
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
                LetterDefinition tempDef;
                
                // little hack (this should be done outside the loop)
                if (posXUV == 0.0)
                    posXUV = currentGlyph.getPadding();
                
                
                int daMeno = 1;
                
                tempDef.letteCharUTF8    =    currentGlyph.getUTF8Letter();
                tempDef.width            =    letterWidth  + currentGlyph.getPadding();
                tempDef.height           =    letterHeight - daMeno;
                tempDef.U                =    posXUV - daMeno;
                tempDef.V                =    posYUV;
                
                tempDef.offsetX           =    currentGlyph.getRect().origin.x;
                tempDef.offsetY           =    currentGlyph.getRect().origin.y;
                
                tempDef.textureID        =    cPages;
                tempDef.commonLineHeight =    currentGlyph.getCommonHeight();
                
                
                // take from pixels to points
                tempDef.width  =    tempDef.width  / CC_CONTENT_SCALE_FACTOR();
                tempDef.height =    tempDef.height / CC_CONTENT_SCALE_FACTOR();
                tempDef.U      =    tempDef.U      / CC_CONTENT_SCALE_FACTOR();
                tempDef.V      =    tempDef.V      / CC_CONTENT_SCALE_FACTOR();
                
                if (tempDef.commonLineHeight>maxLineHeight)
                    maxLineHeight = tempDef.commonLineHeight;
                
                // add this definition
                addLetterDefNew(tempDef);
                
                // move bounding box to the next letter
                posXUV += letterWidth + currentGlyph.getPadding();
                
                // next char in the string
                ++charsCounter;
            }
        }
    }
    
    // store the common line height
    _commonLineHeightNew = maxLineHeight;
    
    return true;
}

bool LabelFontDefinition::createFontDefinition(char *fontName, int fontSize, char *letters, int textureSize, bool debugOutput)
{
    debugUseFreetype = true;
    
    // constants
    //float LINE_PADDING  = 1.9;
    //float PIXEL_PADDING = 1.0;
    
    
    // preare texture/image stuff
    _textImages = new TextImage();
    if (!_textImages)
        return false;
    
    if (!_textImages->initWithString(letters, textureSize, textureSize, fontName, fontSize, !debugOutput))
    {
        delete _textImages;
        _textImages = 0;
        return false;
    }
    
    if ( debugOutput )
        _textImages->debugSaveToFile("debugFontDef.png", false);
    
    
    // prepare the new letter definition
    prepareLetterDefinitionsNew(_textImages->getPagesNew());
    
    // prepare the letter definitions
    return prepareLetterDefinitions(_textImages->getPages());
    
    /*
    // get all the pages
    TextFontPagesDef *pPages = _textImages->getPages();
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
                LetterDefinition tempDef;
                
                tempDef.letteCharUTF8    =    currentGlyph.getUTF8Letter();
                tempDef.width            =    letterWidth + PIXEL_PADDING;
                tempDef.height           =    letterHeight;
                tempDef.U                =    posXUV + LINE_PADDING - PIXEL_PADDING;
                tempDef.V                =    posYUV;
                tempDef.offset           =    currentGlyph.getRect().origin.x;
                tempDef.textureID        =    cPages;
                tempDef.commonLineHeight =    currentGlyph.getCommonHeight();
                
                
                // take from pixels to points
                tempDef.width  =    tempDef.width  / CC_CONTENT_SCALE_FACTOR();
                tempDef.height =    tempDef.height / CC_CONTENT_SCALE_FACTOR();
                tempDef.U      =    tempDef.U      / CC_CONTENT_SCALE_FACTOR();
                tempDef.V      =    tempDef.V      / CC_CONTENT_SCALE_FACTOR();
                
                if (tempDef.commonLineHeight>maxLineHeight)
                    maxLineHeight = tempDef.commonLineHeight;
                
                // add this definition
                addLetterDef(tempDef);
                
                // move bounding box to the next letter
                posXUV += letterWidth + currentGlyph.getPadding();
                
                // next char in the string
                ++charsCounter;
            }
        }
    }
    
    // store the common line height
    _commonLineHeight = maxLineHeight;
    
    return true;
    */
}

void LabelFontDefinition::addLetterDef(LetterDefinition &defToAdd)
{
    if (_fontLettersDefinitionUTF8.find(defToAdd.letteCharUTF8) == _fontLettersDefinitionUTF8.end())
    {
        _fontLettersDefinitionUTF8[defToAdd.letteCharUTF8] = defToAdd;
    }
}

void LabelFontDefinition::addLetterDefNew(LetterDefinition &defToAdd)
{
    if (_fontLettersDefinitionUTF16.find(defToAdd.letteCharUTF8) == _fontLettersDefinitionUTF16.end())
    {
        _fontLettersDefinitionUTF16[defToAdd.letteCharUTF8] = defToAdd;
    }
}

LetterDefinition & LabelFontDefinition::getLetterDefinition(unsigned short int theLetter)
{
    if (debugUseFreetype)
        return _fontLettersDefinitionUTF16[theLetter];
    else
        return _fontLettersDefinitionUTF8[theLetter];
}

Texture2D * LabelFontDefinition::getTexture(int index)
{
    TextFontPagesDef *pPages = 0;
    
    if ( debugUseFreetype )
    {
        pPages = _textImages->getPagesNew();
    }
    else
    {
        pPages = _textImages->getPages();
    }
    
    if (!pPages)
        return (false);
    
    return pPages->getPageAt(index)->getPageTexture();
}

NS_CC_END
