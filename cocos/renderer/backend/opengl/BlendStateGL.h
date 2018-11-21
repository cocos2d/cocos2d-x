#pragma once

#include "../BlendState.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

class BlendStateGL : public BlendState
{
public:
    // Reset to default state.
    static void reset();
    
    BlendStateGL(const BlendDescriptor& descriptor);
    
    void apply() const;
    
private:
    GLboolean _writeMaskRed = GL_TRUE;
    GLboolean _writeMaskGreen = GL_TRUE;
    GLboolean _writeMaskBlue = GL_TRUE;
    GLboolean _writeMaskAlpha = GL_TRUE;
    
    bool _blendEnabled = false;
    
    GLenum _rgbBlendOperation = GL_FUNC_ADD;
    GLenum _alphaBlendOperation = GL_FUNC_ADD;
    
    GLenum _sourceRGBBlendFactor = GL_ONE;
    GLenum _destinationRGBBlendFactor = GL_ZERO;
    GLenum _sourceAlphaBlendFactor = GL_ONE;
    GLenum _destinationAlphaBlendFactor = GL_ZERO;
};

CC_BACKEND_END
