#include "HelloWorld.h"

#include "CCDirector.h"

using namespace cocos2d;

HelloWorld::HelloWorld()
{
    CCTextureCache * pTexCache = CCTextureCache::sharedTextureCache();

    m_pHSprite = HelloSprite::CreateWithTexture(pTexCache->addImage("/NEWPLUS/TDA_DATA/UserData/HelloWorld.png"));
    CGSize size = CCDirector::getSharedDirector()->getWinSize();
    m_pHSprite->setPosition(CGPointMake(size.width / 2, size.height / 2));
    addChild(m_pHSprite);
    m_pHSprite->retain();
}

HelloWorld::~HelloWorld()
{
}
