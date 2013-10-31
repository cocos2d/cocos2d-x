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

void CCArmatureDataManager::purge()
{
    CCSpriteFrameCacheHelper::purge();
    CCDataReaderHelper::purge();
    CC_SAFE_RELEASE_NULL(s_sharedArmatureDataManager);
}

CCArmatureDataManager::CCArmatureDataManager(void)
{
    m_pArmarureDatas = NULL;
    m_pAnimationDatas = NULL;
    m_pTextureDatas = NULL;
    m_bAutoLoadSpriteFile = false;
}


CCArmatureDataManager::~CCArmatureDataManager(void)
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

    m_sRelativeDatas.clear();

    CC_SAFE_DELETE(m_pAnimationDatas);
    CC_SAFE_DELETE(m_pArmarureDatas);
    CC_SAFE_DELETE(m_pTextureDatas);
}


bool CCArmatureDataManager::init()
{
    bool bRet = false;
    do
    {
        m_pArmarureDatas = CCDictionary::create();
        CCAssert(m_pArmarureDatas, "create CCArmatureDataManager::m_pArmarureDatas fail!");
        m_pArmarureDatas->retain();

        m_pAnimationDatas = CCDictionary::create();
        CCAssert(m_pAnimationDatas, "create CCArmatureDataManager::m_pAnimationDatas fail!");
        m_pAnimationDatas->retain();

        m_pTextureDatas = CCDictionary::create();
        CCAssert(m_pTextureDatas, "create CCArmatureDataManager::m_pTextureDatas fail!");
        m_pTextureDatas->retain();

        bRet = true;
    }
    while (0);

    return bRet;
}


void CCArmatureDataManager::removeArmatureFileInfo(const char *configFilePath)
{
    if (CCRelativeData *data = getRelativeData(configFilePath))
    {
        for (std::vector<std::string>::iterator i = data->armatures.begin(); i != data->armatures.end(); i++)
        {
            removeArmatureData(i->c_str());
        }

        for (std::vector<std::string>::iterator i = data->animations.begin(); i != data->animations.end(); i++)
        {
            removeAnimationData(i->c_str());
        }

        for (std::vector<std::string>::iterator i = data->textures.begin(); i != data->textures.end(); i++)
        {
            removeTextureData(i->c_str());
        }

        for (std::vector<std::string>::iterator i = data->plistFiles.begin(); i != data->plistFiles.end(); i++)
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(i->c_str());
        }

        m_sRelativeDatas.erase(configFilePath);
        CCDataReaderHelper::sharedDataReaderHelper()->removeConfigFile(configFilePath);
    }
}

void CCArmatureDataManager::addArmatureData(const char *id, CCArmatureData *armatureData, const char *configFilePath)
{
    if(m_pArmarureDatas)
    {
        if (CCRelativeData *data = getRelativeData(configFilePath))
        {
            data->armatures.push_back(id);
        }

        m_pArmarureDatas->setObject(armatureData, id);
    }
}

CCArmatureData *CCArmatureDataManager::getArmatureData(const char *id)
{
    CCArmatureData *armatureData = NULL;
    if (m_pArmarureDatas)
    {
        armatureData = (CCArmatureData *)m_pArmarureDatas->objectForKey(id);
    }
    return armatureData;
}

void CCArmatureDataManager::removeArmatureData(const char *id)
{
    if (m_pArmarureDatas)
    {
        m_pArmarureDatas->removeObjectForKey(id);
    }
}

void CCArmatureDataManager::addAnimationData(const char *id, CCAnimationData *animationData, const char *configFilePath)
{
    if(m_pAnimationDatas)
    {
        if (CCRelativeData *data = getRelativeData(configFilePath))
        {
            data->animations.push_back(id);
        }

        m_pAnimationDatas->setObject(animationData, id);
    }
}

CCAnimationData *CCArmatureDataManager::getAnimationData(const char *id)
{
    CCAnimationData *animationData = NULL;
    if (m_pAnimationDatas)
    {
        animationData = (CCAnimationData *)m_pAnimationDatas->objectForKey(id);
    }
    return animationData;
}

void CCArmatureDataManager::removeAnimationData(const char *id)
{
    if (m_pAnimationDatas)
    {
        m_pAnimationDatas->removeObjectForKey(id);
    }
}

void CCArmatureDataManager::addTextureData(const char *id, CCTextureData *textureData, const char *configFilePath)
{
    if(m_pTextureDatas)
    {
        if (CCRelativeData *data = getRelativeData(configFilePath))
        {
            data->textures.push_back(id);
        }

        m_pTextureDatas->setObject(textureData, id);
    }
}


CCTextureData *CCArmatureDataManager::getTextureData(const char *id)
{
    CCTextureData *textureData = NULL;
    if (m_pTextureDatas)
    {
        textureData = (CCTextureData *)m_pTextureDatas->objectForKey(id);
    }
    return textureData;
}


void CCArmatureDataManager::removeTextureData(const char *id)
{
    if(m_pTextureDatas)
    {
        m_pTextureDatas->removeObjectForKey(id);
    }
}

void CCArmatureDataManager::addArmatureFileInfo(const char *configFilePath)
{
    addRelativeData(configFilePath);

    m_bAutoLoadSpriteFile = true;
    CCDataReaderHelper::sharedDataReaderHelper()->addDataFromFile(configFilePath);
}

void CCArmatureDataManager::addArmatureFileInfoAsync(const char *configFilePath, CCObject *target, SEL_SCHEDULE selector)
{
    addRelativeData(configFilePath);

    m_bAutoLoadSpriteFile = true;
    CCDataReaderHelper::sharedDataReaderHelper()->addDataFromFileAsync("", "", configFilePath, target, selector);
}

void CCArmatureDataManager::addArmatureFileInfo(const char *imagePath, const char *plistPath, const char *configFilePath)
{
    addRelativeData(configFilePath);

    m_bAutoLoadSpriteFile = false;
    CCDataReaderHelper::sharedDataReaderHelper()->addDataFromFile(configFilePath);

    addSpriteFrameFromFile(plistPath, imagePath, configFilePath);
}

void CCArmatureDataManager::addArmatureFileInfoAsync(const char *imagePath, const char *plistPath, const char *configFilePath, CCObject *target, SEL_SCHEDULE selector)
{
    addRelativeData(configFilePath);

    m_bAutoLoadSpriteFile = false;
    CCDataReaderHelper::sharedDataReaderHelper()->addDataFromFileAsync(imagePath, plistPath, configFilePath, target, selector);
}

void CCArmatureDataManager::addSpriteFrameFromFile(const char *plistPath, const char *imagePath, const char *configFilePath)
{
    if (CCRelativeData *data = getRelativeData(configFilePath))
    {
        data->plistFiles.push_back(plistPath);
    }

    CCSpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->addSpriteFrameFromFile(plistPath, imagePath);
}

bool CCArmatureDataManager::isAutoLoadSpriteFile()
{
    return m_bAutoLoadSpriteFile;
}

CCDictionary *CCArmatureDataManager::getArmatureDatas() const
{
    return m_pArmarureDatas;
}
CCDictionary *CCArmatureDataManager::getAnimationDatas() const
{
    return m_pAnimationDatas;
}
CCDictionary *CCArmatureDataManager::getTextureDatas() const
{
    return m_pTextureDatas;
}

void CCArmatureDataManager::addRelativeData(const char *configFilePath)
{
    if (m_sRelativeDatas.find(configFilePath) == m_sRelativeDatas.end())
    {
        m_sRelativeDatas[configFilePath] = CCRelativeData();
    }
}

CCRelativeData *CCArmatureDataManager::getRelativeData(const char* configFilePath)
{
    return &m_sRelativeDatas[configFilePath];
}

NS_CC_EXT_END
