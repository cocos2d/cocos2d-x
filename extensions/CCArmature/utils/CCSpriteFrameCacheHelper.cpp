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


NS_CC_EXT_BEGIN

CCSpriteFrameCacheHelper *CCSpriteFrameCacheHelper::s_SpriteFrameCacheHelper = NULL;

CCSpriteFrameCacheHelper *CCSpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()
{
    if(!s_SpriteFrameCacheHelper)
    {
        s_SpriteFrameCacheHelper = new CCSpriteFrameCacheHelper();
    }

    return s_SpriteFrameCacheHelper;
}

void CCSpriteFrameCacheHelper::purge()
{
    delete s_SpriteFrameCacheHelper;
    s_SpriteFrameCacheHelper = NULL;
}

void CCSpriteFrameCacheHelper::addSpriteFrameFromFile(const char *plistPath, const char *imagePath)
{

    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(plistPath);
    CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(path.c_str());


    CCTexture2D *pobTexture = CCTextureCache::sharedTextureCache()->addImage(imagePath);

    addSpriteFrameFromDict(dict, pobTexture, imagePath);

    dict->release();

}

void string_replace(std::string& str, const std::string & strsrc, const std::string &strdst)
{
	std::string::size_type pos = 0;

	while( (pos = str.find(strsrc, pos)) != string::npos)
	{
		str.replace(pos, strsrc.length(), strdst);
		pos += strdst.length();

	}
}

void CCSpriteFrameCacheHelper::addSpriteFrameFromDict(CCDictionary *dictionary, CCTexture2D *pobTexture, const char *imagePath)
{
    /*
    Supported Zwoptex Formats:

    ZWTCoordinatesFormatOptionXMLLegacy = 0, // Flash Version
    ZWTCoordinatesFormatOptionXML1_0 = 1, // Desktop Version 0.0 - 0.4b
    ZWTCoordinatesFormatOptionXML1_1 = 2, // Desktop Version 1.0.0 - 1.0.1
    ZWTCoordinatesFormatOptionXML1_2 = 3, // Desktop Version 1.0.2+
    */

    CCDictionary *metadataDict = (CCDictionary *)dictionary->objectForKey("metadata");
    CCDictionary *framesDict = (CCDictionary *)dictionary->objectForKey("frames");
    int format = 0;

    // get the format
    if(metadataDict != NULL)
    {
        format = metadataDict->valueForKey("format")->intValue();
    }

    // check the format
    CCAssert(format >= 0 && format <= 3, "format is not supported for CCSpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");

    CCDictElement *pElement = NULL;
    CCDICT_FOREACH(framesDict, pElement)
    {
        CCDictionary *frameDict = (CCDictionary *)pElement->getObject();
        std::string spriteFrameName = pElement->getStrKey();
        
        string_replace(spriteFrameName, "\\", "/");

        CCSpriteFrame *spriteFrame = (CCSpriteFrame *)CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName.c_str());
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
            spriteFrame->initWithTexture(pobTexture, CCRectMake(x, y, w, h), false, CCPointMake(ox, oy), CCSizeMake((float)ow, (float)oh));
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
            spriteFrame->initWithTexture(pobTexture, frame, rotated, offset, sourceSize );
        }
        else if (format == 3)
        {

        }

        // add sprite frame
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spriteFrame, spriteFrameName.c_str());
        spriteFrame->release();
    }
}


CCTextureAtlas *CCSpriteFrameCacheHelper::getTexureAtlasWithTexture(CCTexture2D *texture)
{
	int key = texture->getName();
	CCTextureAtlas *atlas = (CCTextureAtlas*)m_pTextureAtlasDic->objectForKey(key);
	if (atlas == NULL)
	{
		atlas = CCTextureAtlas::createWithTexture(texture, 4);
		m_pTextureAtlasDic->setObject(atlas, key);
	}
	return atlas;
}

CCSpriteFrameCacheHelper::CCSpriteFrameCacheHelper()
{
    m_pTextureAtlasDic = new CCDictionary();
}

CCSpriteFrameCacheHelper::~CCSpriteFrameCacheHelper()
{
    CC_SAFE_RELEASE_NULL(m_pTextureAtlasDic);
}

NS_CC_EXT_END
