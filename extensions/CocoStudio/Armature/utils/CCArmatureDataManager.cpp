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


NS_CC_EXT_ARMATURE_BEGIN

static ArmatureDataManager *s_sharedArmatureDataManager = NULL;

ArmatureDataManager *ArmatureDataManager::getInstance()
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

void ArmatureDataManager::destoryInstance()
{
    SpriteFrameCacheHelper::purge();
    DataReaderHelper::purge();
    CC_SAFE_RELEASE_NULL(s_sharedArmatureDataManager);
}

ArmatureDataManager::ArmatureDataManager(void)
{
    _armarureDatas = NULL;
    _animationDatas = NULL;
    _textureDatas = NULL;
    _autoLoadSpriteFile = false;
}


ArmatureDataManager::~ArmatureDataManager(void)
{
    removeAll();

    CC_SAFE_DELETE(_animationDatas);
    CC_SAFE_DELETE(_armarureDatas);
    CC_SAFE_DELETE(_textureDatas);
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

void ArmatureDataManager::removeArmatureData(const char *id)
{
    if (_armarureDatas)
    {
        _armarureDatas->removeObjectForKey(id);
    }
}

void ArmatureDataManager::addAnimationData(const char *id, AnimationData *animationData)
{
    if(_animationDatas)
    {
        _animationDatas->setObject(animationData, id);
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

void ArmatureDataManager::removeAnimationData(const char *id)
{
    if (_animationDatas)
    {
        _animationDatas->removeObjectForKey(id);
    }
}

void ArmatureDataManager::addTextureData(const char *id, TextureData *textureData)
{
    if(_textureDatas)
    {
        _textureDatas->setObject(textureData, id);
    }
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


void ArmatureDataManager::removeTextureData(const char *id)
{
    if(_textureDatas)
    {
        _textureDatas->removeObjectForKey(id);
    }
}

void ArmatureDataManager::addArmatureFileInfo(const char *configFilePath)
{
    _autoLoadSpriteFile = true;
    DataReaderHelper::getInstance()->addDataFromFile(configFilePath);
}

void ArmatureDataManager::addArmatureFileInfoAsync(const char *configFilePath, Object *target, SEL_SCHEDULE selector)
{
    _autoLoadSpriteFile = true;
    DataReaderHelper::getInstance()->addDataFromFileAsync(configFilePath, target, selector);
}

void ArmatureDataManager::addArmatureFileInfo(const char *imagePath, const char *plistPath, const char *configFilePath)
{
    _autoLoadSpriteFile = false;
    DataReaderHelper::getInstance()->addDataFromFile(configFilePath);
    addSpriteFrameFromFile(plistPath, imagePath);
}

void ArmatureDataManager::addArmatureFileInfoAsync(const char *imagePath, const char *plistPath, const char *configFilePath, Object *target, SEL_SCHEDULE selector)
{
    _autoLoadSpriteFile = false;
    DataReaderHelper::getInstance()->addDataFromFileAsync(configFilePath, target, selector);
    addSpriteFrameFromFile(plistPath, imagePath);
}

void ArmatureDataManager::addSpriteFrameFromFile(const char *plistPath, const char *imagePath)
{
    SpriteFrameCacheHelper::getInstance()->addSpriteFrameFromFile(plistPath, imagePath);
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

bool ArmatureDataManager::isAutoLoadSpriteFile()
{
    return _autoLoadSpriteFile;
}

Dictionary *ArmatureDataManager::getArmatureDatas() const
{
    return _armarureDatas;
}
Dictionary *ArmatureDataManager::getAnimationDatas() const
{
    return _animationDatas;
}
Dictionary *ArmatureDataManager::getTextureDatas() const
{
    return _textureDatas;
}

NS_CC_EXT_ARMATURE_END
