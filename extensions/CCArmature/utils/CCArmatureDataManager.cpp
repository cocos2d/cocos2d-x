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
	m_pArmarureDatas = NULL;
    m_pAnimationDatas = NULL;
    m_pTextureDatas = NULL;
}


CCArmatureDataManager::~CCArmatureDataManager(void)
{
    removeAll();

    CC_SAFE_DELETE(m_pAnimationDatas);
    CC_SAFE_DELETE(m_pArmarureDatas);
    CC_SAFE_DELETE(m_pTextureDatas);
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

void CCArmatureDataManager::addArmatureData(const char *id, CCArmatureData *armatureData)
{
    if(m_pArmarureDatas)
    {
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

void CCArmatureDataManager::addAnimationData(const char *id, CCAnimationData *animationData)
{
    if(m_pAnimationDatas)
    {
        m_pAnimationDatas->setObject(animationData, id);
    }
}

void CCArmatureDataManager::addTextureData(const char *id, CCTextureData *textureData)
{
    if(m_pTextureDatas)
    {
        m_pTextureDatas->setObject(textureData, id);
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

CCTextureData *CCArmatureDataManager::getTextureData(const char *id)
{
    CCTextureData *textureData = NULL;
    if (m_pTextureDatas)
    {
        textureData = (CCTextureData *)m_pTextureDatas->objectForKey(id);
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

    CCDataReaderHelper::clear();
}

NS_CC_EXT_END
