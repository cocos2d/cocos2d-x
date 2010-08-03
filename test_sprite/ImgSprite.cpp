
#include "ImgSprite.h"
#include "CCTextureCache.h"

ImgSprite::ImgSprite(void)
{
}

ImgSprite::~ImgSprite(void)
{
}

ImgSprite* ImgSprite::CreateWithTexture(CCTexture2D* aTexture)
{
    ImgSprite* pImg = new ImgSprite();
    pImg->initWithTexture(aTexture);
    pImg->autorelease();

    return pImg;
}
