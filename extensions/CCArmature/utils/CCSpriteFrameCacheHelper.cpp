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
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistPath, imagePath);
}

CCTextureAtlas *CCSpriteFrameCacheHelper::getTexureAtlasWithTexture(CCTexture2D *texture)
{
    int key = texture->getName();
    CCTextureAtlas *atlas = (CCTextureAtlas *)m_pTextureAtlasDic->objectForKey(key);
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
