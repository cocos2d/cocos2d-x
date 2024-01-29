/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "2d/CCSpriteFrameCache.h"

#include "editor-support/cocostudio/CCArmatureDataManager.h"
#include "editor-support/cocostudio/CCTransformHelp.h"
#include "editor-support/cocostudio/CCDataReaderHelper.h"
#include "editor-support/cocostudio/CCSpriteFrameCacheHelper.h"

using namespace cocos2d;

namespace cocostudio {

static ArmatureDataManager *s_sharedArmatureDataManager = nullptr;

ArmatureDataManager *ArmatureDataManager::getInstance()
{
    if (s_sharedArmatureDataManager == nullptr)
    {
        s_sharedArmatureDataManager = new (std::nothrow) ArmatureDataManager();
        if (!s_sharedArmatureDataManager || !s_sharedArmatureDataManager->init())
        {
            CC_SAFE_DELETE(s_sharedArmatureDataManager);
        }
    }
    return s_sharedArmatureDataManager;
}

void ArmatureDataManager::destroyInstance()
{
    SpriteFrameCacheHelper::purge();
    DataReaderHelper::purge();
    CC_SAFE_RELEASE_NULL(s_sharedArmatureDataManager);
}

ArmatureDataManager::ArmatureDataManager()
{
    _armarureDatas.clear();
    _animationDatas.clear();
    _textureDatas.clear();
    _autoLoadSpriteFile = false;
}


ArmatureDataManager::~ArmatureDataManager()
{
    _animationDatas.clear();
    _armarureDatas.clear();
    _textureDatas.clear();

    _relativeDatas.clear();
}


bool ArmatureDataManager::init()
{
    bool bRet = false;
    do
    {
        _armarureDatas.clear();
        _animationDatas.clear();
        _textureDatas.clear();

        bRet = true;
    }
    while (0);

    return bRet;
}

void ArmatureDataManager::removeArmatureFileInfo(const std::string& configFilePath)
{
    if (RelativeData *data = getRelativeData(configFilePath))
    {
        for (const std::string& str : data->armatures)
        {
            removeArmatureData(str);
        }

        for (const std::string& str : data->animations)
        {
            removeAnimationData(str);
        }

        for (const std::string& str : data->textures)
        {
            removeTextureData(str);
        }

        for (const std::string& str : data->plistFiles)
        {
            SpriteFrameCacheHelper::getInstance()->removeSpriteFrameFromFile(str);
        }

        _relativeDatas.erase(configFilePath);
        DataReaderHelper::getInstance()->removeConfigFile(configFilePath);
    }
}


void ArmatureDataManager::addArmatureData(const std::string& id, ArmatureData *armatureData, const std::string& configFilePath)
{
    if (RelativeData *data = getRelativeData(configFilePath))
    {
        data->armatures.push_back(id);
    }

    _armarureDatas.insert(id, armatureData);
}

ArmatureData *ArmatureDataManager::getArmatureData(const std::string& id)
{
    return dynamic_cast<ArmatureData*>(_armarureDatas.at(id));
}

void ArmatureDataManager::removeArmatureData(const std::string& id)
{
    _armarureDatas.erase(id);
}

void ArmatureDataManager::addAnimationData(const std::string& id, AnimationData *animationData, const std::string& configFilePath)
{
    if (RelativeData *data = getRelativeData(configFilePath))
    {
        data->animations.push_back(id);
    }

    _animationDatas.insert(id, animationData);
}

AnimationData *ArmatureDataManager::getAnimationData(const std::string& id)
{
    return dynamic_cast<AnimationData*>(_animationDatas.at(id));
}

void ArmatureDataManager::removeAnimationData(const std::string& id)
{
    _animationDatas.erase(id);
}

void ArmatureDataManager::addTextureData(const std::string& id, TextureData *textureData, const std::string& configFilePath)
{
    if (RelativeData *data = getRelativeData(configFilePath))
    {
        data->textures.push_back(id);
    }

    _textureDatas.insert(id, textureData);
}


TextureData *ArmatureDataManager::getTextureData(const std::string& id)
{
    return dynamic_cast<TextureData*>(_textureDatas.at(id));
}


void ArmatureDataManager::removeTextureData(const std::string& id)
{
    _textureDatas.erase(id);
}

void ArmatureDataManager::addArmatureFileInfo(const std::string& configFilePath)
{
    addRelativeData(configFilePath);

    _autoLoadSpriteFile = true;
    DataReaderHelper::getInstance()->addDataFromFile(configFilePath);
}

void ArmatureDataManager::addArmatureFileInfoAsync(const std::string& configFilePath, Ref *target, SEL_SCHEDULE selector)
{
    addRelativeData(configFilePath);

    _autoLoadSpriteFile = true;
    DataReaderHelper::getInstance()->addDataFromFileAsync("", "", configFilePath, target, selector);
}

void ArmatureDataManager::addArmatureFileInfo(const std::string& imagePath, const std::string& plistPath, const std::string& configFilePath)
{
    addRelativeData(configFilePath);

    _autoLoadSpriteFile = false;
    DataReaderHelper::getInstance()->addDataFromFile(configFilePath);
    addSpriteFrameFromFile(plistPath, imagePath, configFilePath);
}

void ArmatureDataManager::addArmatureFileInfoAsync(const std::string& imagePath, const std::string& plistPath, const std::string& configFilePath, Ref *target, SEL_SCHEDULE selector)
{
    addRelativeData(configFilePath);

    _autoLoadSpriteFile = false;
    DataReaderHelper::getInstance()->addDataFromFileAsync(imagePath, plistPath, configFilePath, target, selector);
    addSpriteFrameFromFile(plistPath, imagePath, configFilePath);
}

void ArmatureDataManager::addSpriteFrameFromFile(const std::string& plistPath, const std::string& imagePath, const std::string& configFilePath)
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

const cocos2d::Map<std::string, ArmatureData*>& ArmatureDataManager::getArmatureDatas() const
{
    return _armarureDatas;
}
const cocos2d::Map<std::string, AnimationData*>& ArmatureDataManager::getAnimationDatas() const
{
    return _animationDatas;
}
const cocos2d::Map<std::string, TextureData*>& ArmatureDataManager::getTextureDatas() const
{
    return _textureDatas;
}

void ArmatureDataManager::addRelativeData(const std::string& configFilePath)
{
    if (_relativeDatas.find(configFilePath) == _relativeDatas.end())
    {
        _relativeDatas[configFilePath] = RelativeData();
    }
}

RelativeData *ArmatureDataManager::getRelativeData(const std::string& configFilePath)
{
    return &_relativeDatas[configFilePath];
}

}
