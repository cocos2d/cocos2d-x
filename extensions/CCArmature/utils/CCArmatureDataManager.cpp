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


#include "CCArmatureDataManager.h"
#include "CCTransformHelp.h"
#include "CCDataReaderHelper.h"
#include "CCSpriteFrameCacheHelper.h"
#include "../physics/CCPhysicsWorld.h"


NS_CC_EXT_BEGIN

static CCArmatureDataManager *s_sharedArmatureDataManager = NULL;

CCArmatureDataManager *CCArmatureDataManager::sharedArmatureDataManager()
{
    if (s_sharedArmatureDataManager == NULL)
    {
        s_sharedArmatureDataManager = new CCArmatureDataManager();
        if (!s_sharedArmatureDataManager || !s_sharedArmatureDataManager->init())
        {
            CC_SAFE_DELETE(s_sharedArmatureDataManager);
        }
    }
    return s_sharedArmatureDataManager;
}

CCArmatureDataManager::CCArmatureDataManager(void)
{
	_armarureDatas = NULL;
    _animationDatas = NULL;
    _textureDatas = NULL;
}


CCArmatureDataManager::~CCArmatureDataManager(void)
{
    removeAll();

    CC_SAFE_DELETE(_animationDatas);
    CC_SAFE_DELETE(_armarureDatas);
    CC_SAFE_DELETE(_textureDatas);
}

void CCArmatureDataManager::purgeArmatureSystem()
{
    CCSpriteFrameCacheHelper::purgeSpriteFrameCacheHelper();
    CCPhysicsWorld::purgePhysicsWorld();

    CC_SAFE_RELEASE_NULL(s_sharedArmatureDataManager);
}

bool CCArmatureDataManager::init()
{
    bool bRet = false;
    do
    {
        _armarureDatas = CCDictionary::create();
        CCAssert(_armarureDatas, "create CCArmatureDataManager::_armarureDatas fail!");
        _armarureDatas->retain();

        _animationDatas = CCDictionary::create();
        CCAssert(_animationDatas, "create CCArmatureDataManager::_animationDatas fail!");
        _animationDatas->retain();

        _textureDatas = CCDictionary::create();
        CCAssert(_textureDatas, "create CCArmatureDataManager::_textureDatas fail!");
        _textureDatas->retain();

        bRet = true;
    }
    while (0);

    return bRet;
}

void CCArmatureDataManager::addArmatureData(const char *id, CCArmatureData *armatureData)
{
    if(_armarureDatas)
    {
        _armarureDatas->setObject(armatureData, id);
    }
}

CCArmatureData *CCArmatureDataManager::getArmatureData(const char *id)
{
    CCArmatureData *armatureData = NULL;
    if (_armarureDatas)
    {
        armatureData = (CCArmatureData *)_armarureDatas->objectForKey(id);
    }
    return armatureData;
}

void CCArmatureDataManager::addAnimationData(const char *id, CCAnimationData *animationData)
{
    if(_animationDatas)
    {
        _animationDatas->setObject(animationData, id);
    }
}

void CCArmatureDataManager::addTextureData(const char *id, CCTextureData *textureData)
{
    if(_textureDatas)
    {
        _textureDatas->setObject(textureData, id);
    }
}

CCAnimationData *CCArmatureDataManager::getAnimationData(const char *id)
{
    CCAnimationData *animationData = NULL;
    if (_animationDatas)
    {
        animationData = (CCAnimationData *)_animationDatas->objectForKey(id);
    }
    return animationData;
}

CCTextureData *CCArmatureDataManager::getTextureData(const char *id)
{
    CCTextureData *textureData = NULL;
    if (_textureDatas)
    {
        textureData = (CCTextureData *)_textureDatas->objectForKey(id);
    }
    return textureData;
}



void CCArmatureDataManager::addArmatureFileInfo(const char *armatureName, const char *useExistFileInfo, const char *imagePath, const char *plistPath, const char *configFilePath)
{
    addArmatureFileInfo(imagePath, plistPath, configFilePath);
}

void CCArmatureDataManager::addArmatureFileInfo(const char *imagePath, const char *plistPath, const char *configFilePath)
{

    CCDataReaderHelper::addDataFromFile(configFilePath);
    addSpriteFrameFromFile(plistPath, imagePath);
}

void CCArmatureDataManager::addSpriteFrameFromFile(const char *plistPath, const char *imagePath)
{
    //	if(Game::sharedGame()->isUsePackage())
    //	{
    //		CCSpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->addSpriteFrameFromPak(plistPath, imagePath);
    //	}
    //    else
    //	{
    //		CCSpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->addSpriteFrameFromFile(plistPath, imagePath);
    //	}
    CCSpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->addSpriteFrameFromFile(plistPath, imagePath);
}


void CCArmatureDataManager::removeAll()
{
    if( _animationDatas )
    {
        _animationDatas->removeAllObjects();
    }
    if( _armarureDatas )
    {
        _armarureDatas->removeAllObjects();
    }

    if( _textureDatas )
    {
        _textureDatas->removeAllObjects();
    }

    CCDataReaderHelper::clear();
}

NS_CC_EXT_END
