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


namespace cocos2d { namespace extension { namespace armature {

static ArmatureDataManager *s_sharedArmatureDataManager = NULL;

ArmatureDataManager *ArmatureDataManager::sharedArmatureDataManager()
{
    if (s_sharedArmatureDataManager == NULL)
    {
        s_sharedArmatureDataManager = new ArmatureDataManager();
        if (!s_sharedArmatureDataManager || !s_sharedArmatureDataManager->init())
        {
            CC_SAFE_DELETE(s_sharedArmatureDataManager);
        }
    }
    return s_sharedArmatureDataManager;
}

ArmatureDataManager::ArmatureDataManager(void)
{
	_armarureDatas = NULL;
    _animationDatas = NULL;
    _textureDatas = NULL;
}


ArmatureDataManager::~ArmatureDataManager(void)
{
    removeAll();

    CC_SAFE_DELETE(_animationDatas);
    CC_SAFE_DELETE(_armarureDatas);
    CC_SAFE_DELETE(_textureDatas);
}

void ArmatureDataManager::purgeArmatureSystem()
{
    SpriteFrameCacheHelper::purgeSpriteFrameCacheHelper();
    PhysicsWorld::purgePhysicsWorld();

    CC_SAFE_RELEASE_NULL(s_sharedArmatureDataManager);
}

bool ArmatureDataManager::init()
{
    bool bRet = false;
    do
    {
        _armarureDatas = Dictionary::create();
        CCASSERT(_armarureDatas, "create ArmatureDataManager::_armarureDatas fail!");
        _armarureDatas->retain();

        _animationDatas = Dictionary::create();
        CCASSERT(_animationDatas, "create ArmatureDataManager::_animationDatas fail!");
        _animationDatas->retain();

        _textureDatas = Dictionary::create();
        CCASSERT(_textureDatas, "create ArmatureDataManager::_textureDatas fail!");
        _textureDatas->retain();

        bRet = true;
    }
    while (0);

    return bRet;
}

void ArmatureDataManager::addArmatureData(const char *id, ArmatureData *armatureData)
{
    if(_armarureDatas)
    {
        _armarureDatas->setObject(armatureData, id);
    }
}

ArmatureData *ArmatureDataManager::getArmatureData(const char *id)
{
    ArmatureData *armatureData = NULL;
    if (_armarureDatas)
    {
        armatureData = (ArmatureData *)_armarureDatas->objectForKey(id);
    }
    return armatureData;
}

void ArmatureDataManager::addAnimationData(const char *id, AnimationData *animationData)
{
    if(_animationDatas)
    {
        _animationDatas->setObject(animationData, id);
    }
}

void ArmatureDataManager::addTextureData(const char *id, TextureData *textureData)
{
    if(_textureDatas)
    {
        _textureDatas->setObject(textureData, id);
    }
}

AnimationData *ArmatureDataManager::getAnimationData(const char *id)
{
    AnimationData *animationData = NULL;
    if (_animationDatas)
    {
        animationData = (AnimationData *)_animationDatas->objectForKey(id);
    }
    return animationData;
}

TextureData *ArmatureDataManager::getTextureData(const char *id)
{
    TextureData *textureData = NULL;
    if (_textureDatas)
    {
        textureData = (TextureData *)_textureDatas->objectForKey(id);
    }
    return textureData;
}



void ArmatureDataManager::addArmatureFileInfo(const char *armatureName, const char *useExistFileInfo, const char *imagePath, const char *plistPath, const char *configFilePath)
{
    addArmatureFileInfo(imagePath, plistPath, configFilePath);
}

void ArmatureDataManager::addArmatureFileInfo(const char *imagePath, const char *plistPath, const char *configFilePath)
{

    DataReaderHelper::addDataFromFile(configFilePath);
    addSpriteFrameFromFile(plistPath, imagePath);
}

void ArmatureDataManager::addSpriteFrameFromFile(const char *plistPath, const char *imagePath)
{
    //	if(Game::sharedGame()->isUsePackage())
    //	{
    //		SpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->addSpriteFrameFromPak(plistPath, imagePath);
    //	}
    //    else
    //	{
    //		SpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->addSpriteFrameFromFile(plistPath, imagePath);
    //	}
    SpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->addSpriteFrameFromFile(plistPath, imagePath);
}


void ArmatureDataManager::removeAll()
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

    DataReaderHelper::clear();
}

}}} // namespace cocos2d { namespace extension { namespace armature {
