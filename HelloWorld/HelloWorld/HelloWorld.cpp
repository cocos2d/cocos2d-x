#include "HelloWorld.h"

HelloWorld::HelloWorld()
{
    CCTextureCache * pTexCache = CCTextureCache::sharedTextureCache();

    m_pHSprite = HelloSprite::CreateWithTexture(pTexCache->addImage("/NEWPLUS/TDA_DATA/UserData/HelloWorld.png"));
    m_pHSprite->setPosition(CGPointMake(0.0f, 0.0f));
    addChild(m_pHSprite);
    m_pHSprite->retain();
}

HelloWorld::~HelloWorld()
{
    m_pHSprite->release();
}
