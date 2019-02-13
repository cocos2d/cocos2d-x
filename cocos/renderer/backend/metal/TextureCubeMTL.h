#pragma once

#include "renderer/CCTextureCube.h"
#include "renderer/CCTexture2D.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class CC_DLL TextureCubeMapMTL : public TextureCube
{
public:
    virtual void setTexParameters(const TexParams &);
    bool init(const std::string& positive_x, const std::string& negative_x,
              const std::string& positive_y, const std::string& negative_y,
              const std::string& positive_z, const std::string& negative_z);
};

CC_BACKEND_END
