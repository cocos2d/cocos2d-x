/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Jason Booth
Copyright (c) 2009      Robert J Payne
Copyright (c) 2011      Zynga Inc.

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

#include "cocoa/CCNS.h"
#include "ccMacros.h"
#include "CCTextureCache.h"
#include "CCSpriteFrameCache.h"
#include "CCSpriteFrame.h"
#include "CCSprite.h"
#include "support/TransformUtils.h"
#include "CCFileUtils.h"
#include "CCString.h"
#include "CCArray.h"
#include <vector>

using namespace std;

NS_CC_BEGIN

static CCSpriteFrameCache *pSharedSpriteFrameCache = NULL;

CCSpriteFrameCache* CCSpriteFrameCache::sharedSpriteFrameCache(void)
{
    if (! pSharedSpriteFrameCache)
    {
        pSharedSpriteFrameCache = new CCSpriteFrameCache();
        pSharedSpriteFrameCache->init();
    }

    return pSharedSpriteFrameCache;
}

void CCSpriteFrameCache::purgeSharedSpriteFrameCache(void)
{
    CC_SAFE_RELEASE_NULL(pSharedSpriteFrameCache);
}

bool CCSpriteFrameCache::init(void)
{
    m_pSpriteFrames= new CCDictionary();
    m_pSpriteFramesAliases = new CCDictionary();
    return true;
}

CCSpriteFrameCache::~CCSpriteFrameCache(void)
{
    CC_SAFE_RELEASE(m_pSpriteFrames);
    CC_SAFE_RELEASE(m_pSpriteFramesAliases);
}

void CCSpriteFrameCache::addSpriteFramesWithDictionary(CCDictionary* dictionary, CCTexture2D *pobTexture)
{
    /*
    Supported Zwoptex Formats:

    ZWTCoordinatesFormatOptionXMLLegacy = 0, // Flash Version
    ZWTCoordinatesFormatOptionXML1_0 = 1, // Desktop Version 0.0 - 0.4b
    ZWTCoordinatesFormatOptionXML1_1 = 2, // Desktop Version 1.0.0 - 1.0.1
    ZWTCoordinatesFormatOptionXML1_2 = 3, // Desktop Version 1.0.2+
    */

    CCDictionary *metadataDict = (CCDictionary*)dictionary->objectForKey("metadata");
    CCDictionary *framesDict = (CCDictionary*)dictionary->objectForKey("frames");
    int format = 0;

    // get the format
    if(metadataDict != NULL) 
    {
        format = metadataDict->valueForKey("format")->intValue();
    }

    // check the format
    CCAssert(format >=0 && format <= 3, "");

    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(framesDict, pElement)
    {
        CCDictionary* frameDict = (CCDictionary*)pElement->getObject();
        CCSpriteFrame* spriteFrame = (CCSpriteFrame*)m_pSpriteFrames->objectForKey(pElement->getStrKey());
        if (spriteFrame)
        {
            continue;
        }
        
        if(format == 0) 
        {
            float x = frameDict->valueForKey("x")->floatValue();
            float y = frameDict->valueForKey("y")->floatValue();
            float w = frameDict->valueForKey("width")->floatValue();
            float h = frameDict->valueForKey("height")->floatValue();
            float ox = frameDict->valueForKey("offsetX")->floatValue();
            float oy = frameDict->valueForKey("offsetY")->floatValue();
            int ow = frameDict->valueForKey("originalWidth")->intValue();
            int oh = frameDict->valueForKey("originalHeight")->intValue();
            // check ow/oh
            if(!ow || !oh)
            {
                CCLOG("cocos2d: WARNING: originalWidth/Height not found on the CCSpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
            }
            // abs ow/oh
            ow = abs(ow);
            oh = abs(oh);
            // create frame
            spriteFrame = new CCSpriteFrame();
            spriteFrame->initWithTexture(pobTexture, 
                                        CCRectMake(x, y, w, h), 
                                        false,
                                        CCPointMake(ox, oy),
                                        CCSizeMake((float)ow, (float)oh)
                                        );
        } 
        else if(format == 1 || format == 2) 
        {
            CCRect frame = CCRectFromString(frameDict->valueForKey("frame")->getCString());
            bool rotated = false;

            // rotation
            if (format == 2)
            {
                rotated = frameDict->valueForKey("rotated")->boolValue();
            }

            CCPoint offset = CCPointFromString(frameDict->valueForKey("offset")->getCString());
            CCSize sourceSize = CCSizeFromString(frameDict->valueForKey("sourceSize")->getCString());

            // create frame
            spriteFrame = new CCSpriteFrame();
            spriteFrame->initWithTexture(pobTexture, 
                frame,
                rotated,
                offset,
                sourceSize
                );
        } 
        else if (format == 3)
        {
            // get values
            CCSize spriteSize = CCSizeFromString(frameDict->valueForKey("spriteSize")->getCString());
            CCPoint spriteOffset = CCPointFromString(frameDict->valueForKey("spriteOffset")->getCString());
            CCSize spriteSourceSize = CCSizeFromString(frameDict->valueForKey("spriteSourceSize")->getCString());
            CCRect textureRect = CCRectFromString(frameDict->valueForKey("textureRect")->getCString());
            bool textureRotated = frameDict->valueForKey("textureRotated")->boolValue();

            // get aliases
            CCArray* aliases = (CCArray*) (frameDict->objectForKey("aliases"));
            CCString * frameKey = new CCString(pElement->getStrKey());

            CCObject* pObj = NULL;
            CCARRAY_FOREACH(aliases, pObj)
            {
                std::string oneAlias = ((CCString*)pObj)->getCString();
                if (m_pSpriteFramesAliases->objectForKey(oneAlias.c_str()))
                {
                    CCLOG("cocos2d: WARNING: an alias with name %s already exists", oneAlias.c_str());
                }

                m_pSpriteFramesAliases->setObject(frameKey, oneAlias.c_str());
            }
            frameKey->release();
            // create frame
            spriteFrame = new CCSpriteFrame();
            spriteFrame->initWithTexture(pobTexture,
                            CCRectMake(textureRect.origin.x, textureRect.origin.y, spriteSize.width, spriteSize.height),
                            textureRotated,
                            spriteOffset,
                            spriteSourceSize);
        }

        // add sprite frame
        m_pSpriteFrames->setObject(spriteFrame, pElement->getStrKey());
        spriteFrame->release();
    }
}

void CCSpriteFrameCache::addSpriteFramesWithFile(const char *pszPlist, CCTexture2D *pobTexture)
{
    const char *pszPath = CCFileUtils::fullPathFromRelativePath(pszPlist);
    CCDictionary *dict = CCDictionary::dictionaryWithContentsOfFileThreadSafe(pszPath);

    addSpriteFramesWithDictionary(dict, pobTexture);

    dict->release();
}

void CCSpriteFrameCache::addSpriteFramesWithFile(const char* plist, const char* textureFileName)
{
    CCAssert(textureFileName, "texture name should not be null");
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(textureFileName);

    if (texture)
    {
        addSpriteFramesWithFile(plist, texture);
    }
    else
    {
        CCLOG("cocos2d: CCSpriteFrameCache: couldn't load texture file. File not found %s", textureFileName);
    }
}

void CCSpriteFrameCache::addSpriteFramesWithFile(const char *pszPlist)
{
    const char *pszPath = CCFileUtils::fullPathFromRelativePath(pszPlist);
    CCDictionary *dict = CCDictionary::dictionaryWithContentsOfFileThreadSafe(pszPath);
    
    string texturePath("");

    CCDictionary* metadataDict = (CCDictionary*)dict->objectForKey("metadata");
    if (metadataDict)
    {
        // try to read  texture file name from meta data
        texturePath = metadataDict->valueForKey("textureFileName")->getCString();
    }

    if (! texturePath.empty())
    {
        // build texture path relative to plist file
        texturePath = CCFileUtils::fullPathFromRelativeFile(texturePath.c_str(), pszPath);
    }
    else
    {
        // build texture path by replacing file extension
        texturePath = pszPath;

        // remove .xxx
        size_t startPos = texturePath.find_last_of("."); 
        texturePath = texturePath.erase(startPos);

        // append .png
        texturePath = texturePath.append(".png");

        CCLOG("cocos2d: CCSpriteFrameCache: Trying to use file %s as texture", texturePath.c_str());
    }

    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(texturePath.c_str());

    if (pTexture)
    {
        addSpriteFramesWithDictionary(dict, pTexture);
    }
    else
    {
        CCLOG("cocos2d: CCSpriteFrameCache: Couldn't load texture");
    }

    dict->release();
}

void CCSpriteFrameCache::addSpriteFrame(CCSpriteFrame *pobFrame, const char *pszFrameName)
{
    m_pSpriteFrames->setObject(pobFrame, pszFrameName);
}

void CCSpriteFrameCache::removeSpriteFrames(void)
{
    m_pSpriteFrames->removeAllObjects();
    m_pSpriteFramesAliases->removeAllObjects();
}

void CCSpriteFrameCache::removeUnusedSpriteFrames(void)
{
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(m_pSpriteFrames, pElement)
    {
        CCSpriteFrame* spriteFrame = (CCSpriteFrame*)pElement->getObject();
        if( spriteFrame->retainCount() == 1 ) 
        {
            CCLOG("cocos2d: CCSpriteFrameCache: removing unused frame: %s", pElement->getStrKey());
            m_pSpriteFrames->removeObjectForElememt(pElement);
        }
    }
}


void CCSpriteFrameCache::removeSpriteFrameByName(const char *pszName)
{
    // explicit nil handling
    if( ! pszName )
    {
        return;
    }

    // Is this an alias ?
    CCString* key = (CCString*)m_pSpriteFramesAliases->objectForKey(pszName);

    if (key)
    {
        m_pSpriteFrames->removeObjectForKey(key->getCString());
        m_pSpriteFramesAliases->removeObjectForKey(key->getCString());
    }
    else
    {
        m_pSpriteFrames->removeObjectForKey(pszName);
    }
}

void CCSpriteFrameCache::removeSpriteFramesFromFile(const char* plist)
{
    const char* path = CCFileUtils::fullPathFromRelativePath(plist);
    CCDictionary* dict = CCDictionary::dictionaryWithContentsOfFileThreadSafe(path);

    removeSpriteFramesFromDictionary((CCDictionary*)dict);

    dict->release();
}

void CCSpriteFrameCache::removeSpriteFramesFromDictionary(CCDictionary* dictionary)
{
    CCDictionary* framesDict = (CCDictionary*)dictionary->objectForKey("frames");
    CCArray* keysToRemove = CCArray::array();

    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(framesDict, pElement)
    {
        if (m_pSpriteFrames->objectForKey(pElement->getStrKey()))
        {
            keysToRemove->addObject(CCString::stringWithCString(pElement->getStrKey()));
        }
    }

    m_pSpriteFrames->removeObjectsForKeys(keysToRemove);
}

void CCSpriteFrameCache::removeSpriteFramesFromTexture(CCTexture2D* texture)
{
    CCArray* keysToRemove = CCArray::array();

    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(m_pSpriteFrames, pElement)
    {
        string key = pElement->getStrKey();
        CCSpriteFrame* frame = (CCSpriteFrame*)m_pSpriteFrames->objectForKey(key.c_str());
        if (frame && (frame->getTexture() == texture))
        {
            keysToRemove->addObject(CCString::stringWithCString(pElement->getStrKey()));
        }
    }

    m_pSpriteFrames->removeObjectsForKeys(keysToRemove);
}

CCSpriteFrame* CCSpriteFrameCache::spriteFrameByName(const char *pszName)
{
    CCSpriteFrame* frame = (CCSpriteFrame*)m_pSpriteFrames->objectForKey(pszName);
    if (!frame)
    {
        // try alias dictionary
        CCString *key = (CCString*)m_pSpriteFramesAliases->objectForKey(pszName);  
        if (key)
        {
            frame = (CCSpriteFrame*)m_pSpriteFrames->objectForKey(key->getCString());
            if (! frame)
            {
                CCLOG("cocos2d: CCSpriteFrameCahce: Frame '%s' not found", pszName);
            }
        }
    }
    return frame;
}

NS_CC_END
