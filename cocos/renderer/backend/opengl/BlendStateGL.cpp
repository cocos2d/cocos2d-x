#include "BlendStateGL.h"
#include "renderer/backend/opengl/UtilsGL.h"
#include "GLStateCached.h"

CC_BACKEND_BEGIN

void BlendStateGL::reset()
{
    GL::disable(GL_BLEND);
    GL::colorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

BlendStateGL::BlendStateGL(const BlendDescriptor& descriptor)
: _blendEnabled(descriptor.blendEnabled)
, _rgbBlendOperation(UtilsGL::toGLBlendOperation(descriptor.rgbBlendOperation))
, _alphaBlendOperation(UtilsGL::toGLBlendOperation(descriptor.alphaBlendOperation))
, _sourceRGBBlendFactor(UtilsGL::toGLBlendFactor(descriptor.sourceRGBBlendFactor))
, _destinationRGBBlendFactor(UtilsGL::toGLBlendFactor(descriptor.destinationRGBBlendFactor))
, _sourceAlphaBlendFactor(UtilsGL::toGLBlendFactor(descriptor.sourceAlphaBlendFactor))
, _destinationAlphaBlendFactor(UtilsGL::toGLBlendFactor(descriptor.destinationAlphaBlendFactor))
, _writeMaskRed((uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::RED)
, _writeMaskGreen((uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::GREEN)
, _writeMaskBlue((uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::BLUE)
, _writeMaskAlpha((uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::ALPHA)
{
}

void BlendStateGL::apply() const
{
    if (_blendEnabled)
    {
        GL::enable(GL_BLEND);
        GL::blendEquationSeparate(_rgbBlendOperation, _alphaBlendOperation);
        GL::blendFuncSeparate(_sourceRGBBlendFactor,
            _destinationRGBBlendFactor,
            _sourceAlphaBlendFactor,
            _destinationAlphaBlendFactor);
    }
    else
        GL::disable(GL_BLEND);
    
    GL::colorMask(_writeMaskRed, _writeMaskGreen, _writeMaskBlue, _writeMaskAlpha);
}

CC_BACKEND_END
