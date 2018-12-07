#include "BlendStateGL.h"

CC_BACKEND_BEGIN

namespace
{
    GLenum toGLBlendOperation(BlendOperation blendOperation)
    {
        GLenum ret = GL_FUNC_ADD;
        switch (blendOperation)
        {
            case BlendOperation::ADD:
                ret = GL_FUNC_ADD;
                break;
            case BlendOperation::SUBTRACT:
                ret = GL_FUNC_SUBTRACT;
                break;
            case BlendOperation::RESERVE_SUBTRACT:
                ret = GL_FUNC_REVERSE_SUBTRACT;
                break;
            default:
                break;
        }
        return ret;
    }
    
    GLenum toGLBlendFactor(BlendFactor blendFactor)
    {
        GLenum ret = GL_ONE;
        switch (blendFactor)
        {
            case BlendFactor::ZERO:
                ret = GL_ZERO;
                break;
            case BlendFactor::ONE:
                ret = GL_ONE;
                break;
            case BlendFactor::SRC_COLOR:
                ret = GL_SRC_COLOR;
                break;
            case BlendFactor::ONE_MINUS_SRC_COLOR:
                ret = GL_ONE_MINUS_SRC_COLOR;
                break;
            case BlendFactor::SRC_ALPHA:
                ret = GL_SRC_ALPHA;
                break;
            case BlendFactor::ONE_MINUS_SRC_ALPHA:
                ret = GL_ONE_MINUS_SRC_ALPHA;
                break;
            case BlendFactor::DST_COLOR:
                ret = GL_DST_COLOR;
                break;
            case BlendFactor::ONE_MINUS_DST_COLOR:
                ret = GL_ONE_MINUS_DST_COLOR;
                break;
            case BlendFactor::DST_ALPHA:
                ret = GL_DST_ALPHA;
                break;
            case BlendFactor::ONE_MINUS_DST_ALPHA:
                ret = GL_ONE_MINUS_DST_ALPHA;
                break;
            case BlendFactor::SRC_ALPHA_SATURATE:
                ret = GL_SRC_ALPHA_SATURATE;
                break;
            case BlendFactor::BLEND_CLOLOR:
                ret = GL_BLEND_COLOR;
                break;
            default:
                break;
        }
        return ret;
    }
}

void BlendStateGL::reset()
{
    glDisable(GL_BLEND);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

BlendStateGL::BlendStateGL(const BlendDescriptor& descriptor)
: _blendEnabled(descriptor.blendEnabled)
, _rgbBlendOperation(toGLBlendOperation(descriptor.rgbBlendOperation))
, _alphaBlendOperation(toGLBlendOperation(descriptor.alphaBlendOperation))
, _sourceRGBBlendFactor(toGLBlendFactor(descriptor.sourceRGBBlendFactor))
, _destinationRGBBlendFactor(toGLBlendFactor(descriptor.destinationRGBBlendFactor))
, _sourceAlphaBlendFactor(toGLBlendFactor(descriptor.sourceAlphaBlendFactor))
, _destinationAlphaBlendFactor(toGLBlendFactor(descriptor.destinationAlphaBlendFactor))
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
        glEnable(GL_BLEND);
        glBlendEquationSeparate(_rgbBlendOperation, _alphaBlendOperation);
        glBlendFuncSeparate(_sourceRGBBlendFactor,
                            _destinationRGBBlendFactor,
                            _sourceAlphaBlendFactor,
                            _destinationAlphaBlendFactor);
    }
    else
        glDisable(GL_BLEND);
    
    glColorMask(_writeMaskRed, _writeMaskGreen, _writeMaskBlue, _writeMaskAlpha);
}

CC_BACKEND_END
