//
// Created by NiTe Luo on 11/11/13.
//



#ifndef __CCNewTextureAtlas_H_
#define __CCNewTextureAtlas_H_

#include "CCPlatformMacros.h"
#include "CCTextureAtlas.h"

NS_CC_BEGIN

class NewTextureAtlas : public TextureAtlas
{
public:
    static NewTextureAtlas* create(const char* file, long capacity);

    static NewTextureAtlas* createWithTexture(Texture2D *texture, long capacity);

    NewTextureAtlas();

    virtual ~NewTextureAtlas();

    void drawNumberOfQuads(long numberOfQuads, long start);
};

NS_CC_END

#endif //__CCNewTextureAtlas_H_
