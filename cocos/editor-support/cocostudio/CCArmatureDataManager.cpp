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


#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCTransformHelp.h"
#include "cocostudio/CCDataReaderHelper.h"
#include "cocostudio/CCSpriteFrameCacheHelper.h"

using namespace cocos2d;

namespace cocostudio {

static ArmatureDataManager *s_sharedArmatureDataManager = nullptr;

ArmatureDataManager *ArmatureDataManager::getInstance()
{
    if (s_sharedArmatureDataManager == nullptr)
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
    _armarureDatas = nullptr;
    _animationDatas = nullptr;
    _textureDatas = nullptr;
    _autoLoadSpriteFile = false;
}


ArmatureDataManager::~ArmatureDataManager(void)
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

    _relativeDatas.clear();

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

void ArmatureDataManager::removeArmatureFileInfo(const char *configFilePath)
{
    if (RelativeData *data = getRelativeData(configFilePath))
    {
        for (std::string str : data->armatures)
        {
            removeArmatureData(str.c_str());
        }

        for (std::string str : data->animations)
        {
            removeAnimationData(str.c_str());
        }

        for (std::string str : data->textures)
        {
            removeTextureData(str.c_str());
        }

        for (std::string str : data->plistFiles)
        {
            SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(str.c_str());
        }

        _relativeDatas.erase(configFilePath);
        DataReaderHelper::getInstance()->removeConfigFile(configFilePath);
    }
}


void ArmatureDataManager::addArmatureData(const char *id, ArmatureData *armatureData, const char *configFilePath)
{
    if(_armarureDatas)
    {
        if (RelativeData *data = getRelativeData(configFilePath))
        {
            data->armatures.push_back(id);
        }

        _armarureDatas->setObject(armatureData, id);
    }
}

ArmatureData *ArmatureDataManager::getArmatureData(const char *id)
{
    ArmatureData *armatureData = nullptr;
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

void ArmatureDataManager::addAnimationData(const char *id, AnimationData *animationData, const char *configFilePath)
{
    if(_animationDatas)
    {
        if (RelativeData *data = getRelativeData(configFilePath))
        {
            data->animations.push_back(id);
        }

        _animationDatas->setObject(animationData, id);
    }
}

AnimationData *ArmatureDataManager::getAnimationData(const char *id)
{
    AnimationData *animationData = nullptr;
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

void ArmatureDataManager::addTextureData(const char *id, TextureData *textureData, const char *configFilePath)
{
    if(_textureDatas)
    {
        if (RelativeData *data = getRelativeData(configFilePath))
        {
            data->textures.push_back(id);
        }

        _textureDatas->setObject(textureData, id);
    }
}


TextureData *ArmatureDataManager::getTextureData(const char *id)
{
    TextureData *textureData = nullptr;
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
    addRelativeData(configFilePath);

    _autoLoadSpriteFile = true;
    DataReaderHelper::getInstance()->addDataFromFile(configFilePath);
}

void ArmatureDataManager::addArmatureFileInfoAsync(const char *configFilePath, Object *target, SEL_SCHEDULE selector)
{
    addRelativeData(configFilePath);

    _autoLoadSpriteFile = true;
    DataReaderHelper::getInstance()->addDataFromFileAsync("", "", configFilePath, target, selector);
}

void ArmatureDataManager::addArmatureFileInfo(const char *imagePath, const char *plistPath, const char *configFilePath)
{
    addRelativeData(configFilePath);

    _autoLoadSpriteFile = false;
    DataReaderHelper::getInstance()->addDataFromFile(configFilePath);
    addSpriteFrameFromFile(plistPath, imagePath);
}

void ArmatureDataManager::addArmatureFileInfoAsync(const char *imagePath, const char *plistPath, const char *configFilePath, Object *target, SEL_SCHEDULE selector)
{
    addRelativeData(configFilePath);

    _autoLoadSpriteFile = false;
    DataReaderHelper::getInstance()->addDataFromFileAsync(imagePath, plistPath, configFilePath, target, selector);
    addSpriteFrameFromFile(plistPath, imagePath);
}

void ArmatureDataManager::addSpriteFrameFromFile(const char *plistPath, const char *imagePath, const char *configFilePath)
{
    if (RelativeData *data = getRelativeData(configFilePath))
    {
        data->plistFiles.push_back(plistPath);
    }
    SpriteFrameCacheHelper::getInstance()->addSpriteFrameFromFile(plistPath, imagePath);
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

void CCArmatureDataManager::addRelativeData(const char *configFilePath)
{
    if (_relativeDatas.find(configFilePath) == _relativeDatas.end())
    {
        _relativeDatas[configFilePath] = RelativeData();
    }
}

RelativeData *CCArmatureDataManager::getRelativeData(const char* configFilePath)
{
    return &_relativeDatas[configFilePath];
}

}
