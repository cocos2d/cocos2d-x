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

void ArmatureDataManager::purge()
{
    SpriteFrameCacheHelper::purge();
    DataReaderHelper::purge();
    CC_SAFE_RELEASE_NULL(s_sharedArmatureDataManager);
}

ArmatureDataManager::ArmatureDataManager(void)
{
    m_pArmarureDatas = NULL;
    m_pAnimationDatas = NULL;
    m_pTextureDatas = NULL;
    m_bAutoLoadSpriteFile = false;
}


ArmatureDataManager::~ArmatureDataManager(void)
{
    removeAll();

    CC_SAFE_DELETE(m_pAnimationDatas);
    CC_SAFE_DELETE(m_pArmarureDatas);
    CC_SAFE_DELETE(m_pTextureDatas);
}


bool ArmatureDataManager::init()
{
    bool bRet = false;
    do
    {
        m_pArmarureDatas = Dictionary::create();
        CCAssert(m_pArmarureDatas, "create ArmatureDataManager::m_pArmarureDatas fail!");
        m_pArmarureDatas->retain();

        m_pAnimationDatas = Dictionary::create();
        CCAssert(m_pAnimationDatas, "create ArmatureDataManager::m_pAnimationDatas fail!");
        m_pAnimationDatas->retain();

        m_pTextureDatas = Dictionary::create();
        CCAssert(m_pTextureDatas, "create ArmatureDataManager::m_pTextureDatas fail!");
        m_pTextureDatas->retain();

        bRet = true;
    }
    while (0);

    return bRet;
}

void ArmatureDataManager::addArmatureData(const char *id, ArmatureData *armatureData)
{
    if(m_pArmarureDatas)
    {
        m_pArmarureDatas->setObject(armatureData, id);
    }
}

ArmatureData *ArmatureDataManager::getArmatureData(const char *id)
{
    ArmatureData *armatureData = NULL;
    if (m_pArmarureDatas)
    {
        armatureData = (ArmatureData *)m_pArmarureDatas->objectForKey(id);
    }
    return armatureData;
}

void ArmatureDataManager::removeArmatureData(const char *id)
{
    if (m_pArmarureDatas)
    {
        m_pArmarureDatas->removeObjectForKey(id);
    }
}

void ArmatureDataManager::addAnimationData(const char *id, AnimationData *animationData)
{
    if(m_pAnimationDatas)
    {
        m_pAnimationDatas->setObject(animationData, id);
    }
}

AnimationData *ArmatureDataManager::getAnimationData(const char *id)
{
    AnimationData *animationData = NULL;
    if (m_pAnimationDatas)
    {
        animationData = (AnimationData *)m_pAnimationDatas->objectForKey(id);
    }
    return animationData;
}

void ArmatureDataManager::removeAnimationData(const char *id)
{
    if (m_pAnimationDatas)
    {
        m_pAnimationDatas->removeObjectForKey(id);
    }
}

void ArmatureDataManager::addTextureData(const char *id, TextureData *textureData)
{
    if(m_pTextureDatas)
    {
        m_pTextureDatas->setObject(textureData, id);
    }
}


TextureData *ArmatureDataManager::getTextureData(const char *id)
{
    TextureData *textureData = NULL;
    if (m_pTextureDatas)
    {
        textureData = (TextureData *)m_pTextureDatas->objectForKey(id);
    }
    return textureData;
}


void ArmatureDataManager::removeTextureData(const char *id)
{
    if(m_pTextureDatas)
    {
        m_pTextureDatas->removeObjectForKey(id);
    }
}

void ArmatureDataManager::addArmatureFileInfo(const char *configFilePath)
{
    m_bAutoLoadSpriteFile = true;
    DataReaderHelper::sharedDataReaderHelper()->addDataFromFile(configFilePath);
}

void ArmatureDataManager::addArmatureFileInfoAsync(const char *configFilePath, Object *target, SEL_SCHEDULE selector)
{
    m_bAutoLoadSpriteFile = true;
    DataReaderHelper::sharedDataReaderHelper()->addDataFromFileAsync(configFilePath, target, selector);
}

void ArmatureDataManager::addArmatureFileInfo(const char *imagePath, const char *plistPath, const char *configFilePath)
{
    m_bAutoLoadSpriteFile = false;
    DataReaderHelper::sharedDataReaderHelper()->addDataFromFile(configFilePath);
    addSpriteFrameFromFile(plistPath, imagePath);
}

void ArmatureDataManager::addArmatureFileInfoAsync(const char *imagePath, const char *plistPath, const char *configFilePath, Object *target, SEL_SCHEDULE selector)
{
    m_bAutoLoadSpriteFile = false;
    DataReaderHelper::sharedDataReaderHelper()->addDataFromFileAsync(configFilePath, target, selector);
    addSpriteFrameFromFile(plistPath, imagePath);
}

void ArmatureDataManager::addSpriteFrameFromFile(const char *plistPath, const char *imagePath)
{
    SpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->addSpriteFrameFromFile(plistPath, imagePath);
}


void ArmatureDataManager::removeAll()
{
    if( m_pAnimationDatas )
    {
        m_pAnimationDatas->removeAllObjects();
    }
    if( m_pArmarureDatas )
    {
        m_pArmarureDatas->removeAllObjects();
    }

    if( m_pTextureDatas )
    {
        m_pTextureDatas->removeAllObjects();
    }

    DataReaderHelper::clear();
}

bool ArmatureDataManager::isAutoLoadSpriteFile()
{
    return m_bAutoLoadSpriteFile;
}

Dictionary *ArmatureDataManager::getArmatureDatas() const
{
    return m_pArmarureDatas;
}
Dictionary *ArmatureDataManager::getAnimationDatas() const
{
    return m_pAnimationDatas;
}
Dictionary *ArmatureDataManager::getTextureDatas() const
{
    return m_pTextureDatas;
}

NS_CC_EXT_ARMATURE_END
