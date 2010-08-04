#include "HelloSprite.h"

HelloSprite::HelloSprite()
{

}

HelloSprite::~HelloSprite()
{

}

HelloSprite* HelloSprite::CreateWithTexture(CCTexture2D* aTexture)
{
    HelloSprite* pHSprite = new HelloSprite();
    pHSprite->initWithTexture(aTexture);
    pHSprite->autorelease();

    return pHSprite;
}
