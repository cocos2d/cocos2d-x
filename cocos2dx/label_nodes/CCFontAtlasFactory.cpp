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

static const char *glyphASCII = "\"!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ ";

static const char *glyphNEHE =  "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ";


FontAtlas * FontAtlasFactory::createAtlasFromTTF(const char* tttFilePath, int fontSize, GlyphCollection glyphs, const char *customGlyphs)
{
    FontDefinitionTTF *def = 0;
    if ( (glyphs == GlyphCollection::NEHE) || (glyphs == GlyphCollection::ASCII) )
    {
        def = FontDefinitionTTF::create(tttFilePath, fontSize, getGlyphCollection(glyphs));
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
            
            def = FontDefinitionTTF::create(tttFilePath, fontSize, customGlyphs);
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
    Font *pFont = Font::createWithFNT(fntFilePath);
    
    if(pFont)
        return pFont->createFontAtlas();
    else
        return nullptr;
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

NS_CC_END
