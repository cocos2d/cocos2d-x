#ifndef __IMGSPRITE__H__
#define __IMGSPRITE__H__

#include "CCSprite.h"
#include "CCTextureCache.h"

using namespace cocos2d;

class ImgSprite : public CCSprite
{
public:
    ImgSprite();
    ~ImgSprite();

public:
    static ImgSprite* CreateWithTexture(CCTexture2D* aTexture);
};

#endif
