/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCSpriteFrameCacheHelper.h"


namespace cocos2d { namespace extension { namespace armature {

SpriteFrameCacheHelper *SpriteFrameCacheHelper::s_SpriteFrameCacheHelper = NULL;

SpriteFrameCacheHelper *SpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()
{
    if(!s_SpriteFrameCacheHelper)
    {
        s_SpriteFrameCacheHelper = new SpriteFrameCacheHelper();
    }

    return s_SpriteFrameCacheHelper;
}

void SpriteFrameCacheHelper::purgeSpriteFrameCacheHelper()
{
    delete s_SpriteFrameCacheHelper;
    s_SpriteFrameCacheHelper = NULL;
}

void SpriteFrameCacheHelper::addSpriteFrameFromFile(const char *plistPath, const char *imagePath)
{

    std::string path = FileUtils::getInstance()->fullPathForFilename(plistPath);
    Dictionary *dict = Dictionary::createWithContentsOfFileThreadSafe(path.c_str());


    Texture2D *pobTexture = TextureCache::getInstance()->addImage(imagePath);

    addSpriteFrameFromDict(dict, pobTexture, imagePath);

    dict->release();

}

void SpriteFrameCacheHelper::addSpriteFrameFromDict(Dictionary *dictionary, Texture2D *pobTexture, const char *imagePath)
{
    /*
    Supported Zwoptex Formats:

    ZWTCoordinatesFormatOptionXMLLegacy = 0, // Flash Version
    ZWTCoordinatesFormatOptionXML1_0 = 1, // Desktop Version 0.0 - 0.4b
    ZWTCoordinatesFormatOptionXML1_1 = 2, // Desktop Version 1.0.0 - 1.0.1
    ZWTCoordinatesFormatOptionXML1_2 = 3, // Desktop Version 1.0.2+
    */

    Dictionary *metadataDict = (Dictionary *)dictionary->objectForKey("metadata");
    Dictionary *framesDict = (Dictionary *)dictionary->objectForKey("frames");
    int format = 0;

    // get the format
    if(metadataDict != NULL)
    {
        format = metadataDict->valueForKey("format")->intValue();
    }

    // check the format
    CCASSERT(format >= 0 && format <= 3, "format is not supported for SpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");

    DictElement *pElement = NULL;
    CCDICT_FOREACH(framesDict, pElement)
    {
        Dictionary *frameDict = static_cast<Dictionary*>(pElement->getObject());
        std::string spriteFrameName = pElement->getStrKey();

        _display2ImageMap[spriteFrameName] = imagePath;

        //log("spriteFrameName : %s,    imagePath : %s", spriteFrameName.c_str(), _imagePath);

        SpriteFrame *spriteFrame = (SpriteFrame *)SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName.c_str());
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
                CCLOG("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
            }
            // abs ow/oh
            ow = abs(ow);
            oh = abs(oh);
            // create frame
            spriteFrame = new SpriteFrame();
            spriteFrame->initWithTexture(pobTexture, Rect(x, y, w, h), false, Point(ox, oy), Size((float)ow, (float)oh));
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
            spriteFrame->initWithTexture(pobTexture, frame, rotated, offset, sourceSize );
        }
        else if (format == 3)
        {

        }

        // add sprite frame
        SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, spriteFrameName.c_str());
        spriteFrame->release();
    }
}

const char *SpriteFrameCacheHelper::getDisplayImagePath(const char *displayName)
{
    return _display2ImageMap[displayName].c_str();
}


TextureAtlas *SpriteFrameCacheHelper::getTextureAtlas(const char *displayName)
{
    const char *textureName = getDisplayImagePath(displayName);
    TextureAtlas *atlas = (TextureAtlas *)_display2TextureAtlas->objectForKey(textureName);
    if (atlas == NULL)
    {
        atlas = TextureAtlas::createWithTexture(TextureCache::getInstance()->addImage(textureName), 4);
        _display2TextureAtlas->setObject(atlas, textureName);
    }

    return atlas;
}

SpriteFrameCacheHelper::SpriteFrameCacheHelper()
{
    _display2TextureAtlas = new Dictionary();
}

SpriteFrameCacheHelper::~SpriteFrameCacheHelper()
{
    CC_SAFE_RELEASE_NULL(_display2TextureAtlas);
}

}}} // namespace cocos2d { namespace extension { namespace armature {
