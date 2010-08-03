#ifndef __IMGSPRITE__H__
#define __IMGSPRITE__H__

#include "CCSprite.h"
#include "CCTextureCache.h"

class ImgSprite : public CCSprite
{
public:
    ImgSprite();
    ~ImgSprite();

public:
    static ImgSprite* CreateWithTexture(CCTexture2D* aTexture);
};

#endif
