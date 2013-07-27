/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "textures/CCTextureCache.h"
#include "CCSpriteFrameCache.h"
#include "CCSpriteFrame.h"
#include "CCSprite.h"
#include "support/TransformUtils.h"
#include "platform/CCFileUtils.h"
#include "cocoa/CCString.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCDictionary.h"
#include <vector>

using namespace std;

NS_CC_BEGIN

static SpriteFrameCache *_sharedSpriteFrameCache = NULL;

SpriteFrameCache* SpriteFrameCache::getInstance()
{
    if (! _sharedSpriteFrameCache)
    {
        _sharedSpriteFrameCache = new SpriteFrameCache();
        _sharedSpriteFrameCache->init();
    }

    return _sharedSpriteFrameCache;
}

void SpriteFrameCache::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_sharedSpriteFrameCache);
}

bool SpriteFrameCache::init(void)
{
    _spriteFrames= new Dictionary();
    _spriteFramesAliases = new Dictionary();
    _loadedFileNames = new std::set<std::string>();
    return true;
}

SpriteFrameCache::~SpriteFrameCache(void)
{
    CC_SAFE_RELEASE(_spriteFrames);
    CC_SAFE_RELEASE(_spriteFramesAliases);
    CC_SAFE_DELETE(_loadedFileNames);
}

void SpriteFrameCache::addSpriteFramesWithDictionary(Dictionary* dictionary, Texture2D *pobTexture)
{
    /*
    Supported Zwoptex Formats:

    ZWTCoordinatesFormatOptionXMLLegacy = 0, // Flash Version
    ZWTCoordinatesFormatOptionXML1_0 = 1, // Desktop Version 0.0 - 0.4b
    ZWTCoordinatesFormatOptionXML1_1 = 2, // Desktop Version 1.0.0 - 1.0.1
    ZWTCoordinatesFormatOptionXML1_2 = 3, // Desktop Version 1.0.2+
    */

    Dictionary *metadataDict = (Dictionary*)dictionary->objectForKey("metadata");
    Dictionary *framesDict = (Dictionary*)dictionary->objectForKey("frames");
    int format = 0;

    // get the format
    if(metadataDict != NULL) 
    {
        format = metadataDict->valueForKey("format")->intValue();
    }

    // check the format
    CCASSERT(format >=0 && format <= 3, "format is not supported for SpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");

    DictElement* pElement = NULL;
    CCDICT_FOREACH(framesDict, pElement)
    {
        Dictionary* frameDict = static_cast<Dictionary*>(pElement->getObject());
        std::string spriteFrameName = pElement->getStrKey();
        SpriteFrame* spriteFrame = static_cast<SpriteFrame*>(_spriteFrames->objectForKey(spriteFrameName));
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
                CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
            }
            // abs ow/oh
            ow = abs(ow);
            oh = abs(oh);
            // create frame
            spriteFrame = new SpriteFrame();
            spriteFrame->initWithTexture(pobTexture, 
                                        Rect(x, y, w, h), 
                                        false,
                                        Point(ox, oy),
                                        Size((float)ow, (float)oh)
                                        );
        } 
        else if(format == 1 || format == 2) 
        {
            Rect frame = RectFromString(frameDict->valueForKey("frame")->getCString());
            bool rotated = false;

            // rotation
            if (format == 2)
            {
                rotated = frameDict->valueForKey("rotated")->boolValue();
            }

            Point offset = PointFromString(frameDict->valueForKey("offset")->getCString());
            Size sourceSize = SizeFromString(frameDict->valueForKey("sourceSize")->getCString());

            // create frame
            spriteFrame = new SpriteFrame();
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
            Size spriteSize = SizeFromString(frameDict->valueForKey("spriteSize")->getCString());
            Point spriteOffset = PointFromString(frameDict->valueForKey("spriteOffset")->getCString());
            Size spriteSourceSize = SizeFromString(frameDict->valueForKey("spriteSourceSize")->getCString());
            Rect textureRect = RectFromString(frameDict->valueForKey("textureRect")->getCString());
            bool textureRotated = frameDict->valueForKey("textureRotated")->boolValue();

            // get aliases
            Array* aliases = (Array*) (frameDict->objectForKey("aliases"));
            String * frameKey = new String(spriteFrameName);

            Object* pObj = NULL;
            CCARRAY_FOREACH(aliases, pObj)
            {
                std::string oneAlias = static_cast<String*>(pObj)->getCString();
                if (_spriteFramesAliases->objectForKey(oneAlias.c_str()))
                {
                    CCLOGWARN("cocos2d: WARNING: an alias with name %s already exists", oneAlias.c_str());
                }

                _spriteFramesAliases->setObject(frameKey, oneAlias.c_str());
            }
            frameKey->release();
            // create frame
            spriteFrame = new SpriteFrame();
            spriteFrame->initWithTexture(pobTexture,
                            Rect(textureRect.origin.x, textureRect.origin.y, spriteSize.width, spriteSize.height),
                            textureRotated,
                            spriteOffset,
                            spriteSourceSize);
        }

        // add sprite frame
        _spriteFrames->setObject(spriteFrame, spriteFrameName);
        spriteFrame->release();
    }
}

void SpriteFrameCache::addSpriteFramesWithFile(const char *pszPlist, Texture2D *pobTexture)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszPlist);
    Dictionary *dict = Dictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());

    addSpriteFramesWithDictionary(dict, pobTexture);

    dict->release();
}

void SpriteFrameCache::addSpriteFramesWithFile(const char* plist, const char* textureFileName)
{
    CCASSERT(textureFileName, "texture name should not be null");
    Texture2D *texture = TextureCache::getInstance()->addImage(textureFileName);

    if (texture)
    {
        addSpriteFramesWithFile(plist, texture);
    }
    else
    {
        CCLOG("cocos2d: SpriteFrameCache: couldn't load texture file. File not found %s", textureFileName);
    }
}

void SpriteFrameCache::addSpriteFramesWithFile(const char *pszPlist)
{
    CCASSERT(pszPlist, "plist filename should not be NULL");

    if (_loadedFileNames->find(pszPlist) == _loadedFileNames->end())
    {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszPlist);
        Dictionary *dict = Dictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());

        string texturePath("");

        Dictionary* metadataDict = (Dictionary*)dict->objectForKey("metadata");
        if (metadataDict)
        {
            // try to read  texture file name from meta data
            texturePath = metadataDict->valueForKey("textureFileName")->getCString();
        }

        if (! texturePath.empty())
        {
            // build texture path relative to plist file
            texturePath = FileUtils::getInstance()->fullPathFromRelativeFile(texturePath.c_str(), pszPlist);
        }
        else
        {
            // build texture path by replacing file extension
            texturePath = pszPlist;

            // remove .xxx
            size_t startPos = texturePath.find_last_of("."); 
            texturePath = texturePath.erase(startPos);

            // append .png
            texturePath = texturePath.append(".png");

            CCLOG("cocos2d: SpriteFrameCache: Trying to use file %s as texture", texturePath.c_str());
        }

        Texture2D *texture = TextureCache::getInstance()->addImage(texturePath.c_str());

        if (texture)
        {
            addSpriteFramesWithDictionary(dict, texture);
            _loadedFileNames->insert(pszPlist);
        }
        else
        {
            CCLOG("cocos2d: SpriteFrameCache: Couldn't load texture");
        }

        dict->release();
    }

}

void SpriteFrameCache::addSpriteFrame(SpriteFrame *pobFrame, const char *pszFrameName)
{
    _spriteFrames->setObject(pobFrame, pszFrameName);
}

void SpriteFrameCache::removeSpriteFrames(void)
{
    _spriteFrames->removeAllObjects();
    _spriteFramesAliases->removeAllObjects();
    _loadedFileNames->clear();
}

void SpriteFrameCache::removeUnusedSpriteFrames(void)
{
    bool bRemoved = false;
    DictElement* pElement = NULL;
    CCDICT_FOREACH(_spriteFrames, pElement)
    {
        SpriteFrame* spriteFrame = static_cast<SpriteFrame*>(pElement->getObject());
        if( spriteFrame->retainCount() == 1 ) 
        {
            CCLOG("cocos2d: SpriteFrameCache: removing unused frame: %s", pElement->getStrKey());
            _spriteFrames->removeObjectForElememt(pElement);
            bRemoved = true;
        }
    }

    // XXX. Since we don't know the .plist file that originated the frame, we must remove all .plist from the cache
    if( bRemoved )
    {
        _loadedFileNames->clear();
    }
}


void SpriteFrameCache::removeSpriteFrameByName(const char *pszName)
{
    // explicit nil handling
    if( ! pszName )
    {
        return;
    }

    // Is this an alias ?
    String* key = (String*)_spriteFramesAliases->objectForKey(pszName);

    if (key)
    {
        _spriteFrames->removeObjectForKey(key->getCString());
        _spriteFramesAliases->removeObjectForKey(key->getCString());
    }
    else
    {
        _spriteFrames->removeObjectForKey(pszName);
    }

    // XXX. Since we don't know the .plist file that originated the frame, we must remove all .plist from the cache
    _loadedFileNames->clear();
}

void SpriteFrameCache::removeSpriteFramesFromFile(const char* plist)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    Dictionary* dict = Dictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());

    removeSpriteFramesFromDictionary((Dictionary*)dict);

    // remove it from the cache
    set<string>::iterator ret = _loadedFileNames->find(plist);
    if (ret != _loadedFileNames->end())
    {
        _loadedFileNames->erase(ret);
    }

    dict->release();
}

void SpriteFrameCache::removeSpriteFramesFromDictionary(Dictionary* dictionary)
{
    Dictionary* framesDict = static_cast<Dictionary*>(dictionary->objectForKey("frames"));
    Array* keysToRemove = Array::create();

    DictElement* pElement = NULL;
    CCDICT_FOREACH(framesDict, pElement)
    {
        if (_spriteFrames->objectForKey(pElement->getStrKey()))
        {
            keysToRemove->addObject(String::create(pElement->getStrKey()));
        }
    }

    _spriteFrames->removeObjectsForKeys(keysToRemove);
}

void SpriteFrameCache::removeSpriteFramesFromTexture(Texture2D* texture)
{
    Array* keysToRemove = Array::create();

    DictElement* pElement = NULL;
    CCDICT_FOREACH(_spriteFrames, pElement)
    {
        string key = pElement->getStrKey();
        SpriteFrame* frame = static_cast<SpriteFrame*>(_spriteFrames->objectForKey(key.c_str()));
        if (frame && (frame->getTexture() == texture))
        {
            keysToRemove->addObject(String::create(pElement->getStrKey()));
        }
    }

    _spriteFrames->removeObjectsForKeys(keysToRemove);
}

SpriteFrame* SpriteFrameCache::getSpriteFrameByName(const char *pszName)
{
    SpriteFrame* frame = (SpriteFrame*)_spriteFrames->objectForKey(pszName);
    if (!frame)
    {
        // try alias dictionary
        String *key = (String*)_spriteFramesAliases->objectForKey(pszName);  
        if (key)
        {
            frame = (SpriteFrame*)_spriteFrames->objectForKey(key->getCString());
            if (! frame)
            {
                CCLOG("cocos2d: SpriteFrameCache: Frame '%s' not found", pszName);
            }
        }
    }
    return frame;
}

NS_CC_END
