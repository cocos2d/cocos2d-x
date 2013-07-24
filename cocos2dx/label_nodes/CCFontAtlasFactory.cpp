//
//  CCFontAtlasFactory.cpp
//  cocos2d_libs
//
//  Created by Carlo Morgantini on 7/23/13.
//
//

#include "CCFontAtlasFactory.h"

// carloX this NEEDS to be changed
#include "CCLabelBMFont.h"

NS_CC_BEGIN

static const char *glpyhsASCII = "\"!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ";
static const char *glpyhsNEHE =  "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";


FontAtlas * FontAtlasFactory::createAtlasFromTTF(const char* tttFilePath, int fontSize, GlyphCollection glyphs)
{
    FontDefinitionTTF *def = FontDefinitionTTF::create(tttFilePath, fontSize, getGlyphCollection(glyphs));
    if(!def)
        return 0;
    
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
    return 0;
}

const char * FontAtlasFactory::getGlyphCollection(GlyphCollection glyphs)
{
    switch (glyphs)
    {
        case GlyphCollection::NEHE:
            return glpyhsNEHE;
            break;
            
        case GlyphCollection::ASCII:
            return glpyhsASCII;
            break;
            
        default:
            return 0;
            break;
    }
}

NS_CC_END
