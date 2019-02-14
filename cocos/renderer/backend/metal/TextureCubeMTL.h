#pragma once

#include "renderer/CCTextureCube.h"
#include "renderer/CCTexture2D.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class CC_DLL TextureCubeMTL : public TextureCube
{
public:
    virtual void setTexParameters(const TexParams &);
    virtual bool updateImageData(int side, Texture2D::PixelFormat format, int width, int height, unsigned char *data);
};

CC_BACKEND_END
