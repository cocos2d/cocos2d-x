//
//  CCFontAtlasFactory.cpp
//  cocos2d_libs
//
//  Created by Carlo Morgantini on 7/23/13.
//
//

#include "CCFontAtlasFactory.h"
#include "CCFontFNT.h"

// carloX this NEEDS to be changed
#include "CCLabelBMFont.h"

NS_CC_BEGIN


const char *FontAtlasFactory::glyphASCII = "\"!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ ";

const char *FontAtlasFactory::glyphNEHE =  "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ";



FontAtlas * FontAtlasFactory::createAtlasFromTTF(const char* fntFilePath, int fontSize, GlyphCollection glyphs, const char *customGlyphs)
{
    FontDefinitionTTF *def = 0;
    if ( (glyphs == GlyphCollection::NEHE) || (glyphs == GlyphCollection::ASCII) )
    {
        def = FontDefinitionTTF::create(fntFilePath, fontSize, getGlyphCollection(glyphs));
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
            
            def = FontDefinitionTTF::create(fntFilePath, fontSize, customGlyphs);
        }
    }
    
    if(!def)
        return nullptr;
    
    // create the font atlas from the font definition
    FontAtlas *tempAtlas = def->createFontAtlas();
    
    // release the font definition, we don't need it anymore
    def->release();
    
    // return the atlas
    return tempAtlas;
}

FontAtlas * FontAtlasFactory::createAtlasFromFNT(const char* fntFilePath)
{
    CCBMFontConfiguration *newConf = FNTConfigLoadFile(fntFilePath);
    
    if (newConf)
        return createFontAtlasFromFNTConfig(newConf);
    else
        return 0;
}

const char * FontAtlasFactory::getGlyphCollection(GlyphCollection glyphs)
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

FontAtlas * FontAtlasFactory::createFontAtlasFromFNTConfig(CCBMFontConfiguration *theConfig)
{
    if (!theConfig)
        return 0;
    
    FontFNT *tempFont = new FontFNT(theConfig);
    if (!tempFont)
        return 0;
    
    FontAtlas *tempAtlas = new FontAtlas(*tempFont);
    if (!tempAtlas)
        return 0;
    
    // check that everything is fine with the BMFontCofniguration
    if (!theConfig->_fontDefDictionary)
        return 0;
    
    
    int numGlyphs = theConfig->_characterSet->size();
    if (!numGlyphs)
        return 0;
    
    if (theConfig->_commonHeight == 0)
        return 0;
    
    // commone height
    tempAtlas->setCommonLineHeight(theConfig->_commonHeight);
    
    
    ccBMFontDef fontDef;
    tFontDefHashElement *current_element, *tmp;
    
    // Purge uniform hash
    HASH_ITER(hh, theConfig->_fontDefDictionary, current_element, tmp)
    {
        
        FontLetterDefinition tempDefinition;
        
        fontDef = current_element->fontDef;
        Rect tempRect;
        
        tempRect = fontDef.rect;
        tempRect = CC_RECT_PIXELS_TO_POINTS(tempRect);
        
        tempDefinition.letteCharUTF16 = fontDef.charID;
        
        tempDefinition.offsetX  = fontDef.xOffset;
        tempDefinition.offsetY  = fontDef.yOffset;
        
        tempDefinition.U        = tempRect.origin.x;
        tempDefinition.V        = tempRect.origin.y;
        
        tempDefinition.width    = tempRect.size.width;
        tempDefinition.height   = tempRect.size.height;
        
        //carloX: only one texture supported FOR NOW
        tempDefinition.textureID = 0;
        
        tempDefinition.anchorX = 0.5f;
        tempDefinition.anchorY = 0.5f;
        
        // add the new definition
        tempAtlas->addLetterDefinition(tempDefinition);
    }
    
    // add the texture (only one texture for now)
    
    Texture2D *tempTexture = TextureCache::getInstance()->addImage(theConfig->getAtlasName());
    if (!tempTexture)
        return 0;
    
    // add the texture
    tempAtlas->addTexture(*tempTexture, 0);
    return tempAtlas;
}

NS_CC_END
