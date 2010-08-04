#ifndef _HelloSprite_H_
#define _HelloSprite_H_

#include "CCSprite.h"
#include "CCTextureCache.h"

class HelloSprite : public CCSprite
{
public:
    HelloSprite();
    ~HelloSprite();

public:
    static HelloSprite* CreateWithTexture(CCTexture2D* aTexture);
};

#endif
