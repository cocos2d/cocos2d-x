#include "DepthStencilStateGL.h"
#include "platform/CCGL.h"

#include "ccMacros.h"

CC_BACKEND_BEGIN

namespace
{
    GLenum toGLComareFunction(CompareFunction compareFunction)
    {
        GLenum ret = GL_ALWAYS;
        switch (compareFunction)
        {
            case CompareFunction::NEVER:
                ret = GL_NEVER;
                break;
            case CompareFunction::LESS:
                ret = GL_LESS;
                break;
            case CompareFunction::LESS_EQUAL:
                ret = GL_LEQUAL;
                break;
            case CompareFunction::GREATER:
                ret = GL_GREATER;
                break;
            case CompareFunction::GREATER_EQUAL:
                ret = GL_GEQUAL;
                break;
            case CompareFunction::NOT_EQUAL:
                ret = GL_NOTEQUAL;
                break;
            case CompareFunction::EQUAL:
                ret = GL_EQUAL;
                break;
            case CompareFunction::ALWAYS:
                ret = GL_ALWAYS;
                break;
            default:
                break;
        }
        return ret;
    }
    
    GLenum toGLStencilOperation(StencilOperation stencilOperation)
    {
        GLenum ret = GL_KEEP;
        switch (stencilOperation)
        {
            case StencilOperation::KEEP:
                ret = GL_KEEP;
                break;
            case StencilOperation::ZERO:
                ret = GL_ZERO;
                break;
            case StencilOperation::REPLACE:
                ret = GL_REPLACE;
                break;
            case StencilOperation::INVERT:
                ret = GL_INVERT;
                break;
            case StencilOperation::INCREMENT_WRAP:
                ret = GL_INCR_WRAP;
                break;
            case StencilOperation::DECREMENT_WRAP:
                ret = GL_DECR_WRAP;
                break;
            default:
                break;
        }
        return ret;
    }
}

void DepthStencilStateGL::reset()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
}

DepthStencilStateGL::DepthStencilStateGL(const DepthStencilDescriptor& descriptor)
: DepthStencilState(descriptor)
{}

void DepthStencilStateGL::apply(uint32_t stencilReferenceValueFront, uint32_t stencilReferenceValueBack) const
{
    // depth test
    
    if (_depthStencilInfo.depthTestEnabled)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
    
    if (_depthStencilInfo.depthWriteEnabled)
        glDepthMask(GL_TRUE);
    else
        glDepthMask(GL_FALSE);
    
    glDepthFunc(toGLComareFunction(_depthStencilInfo.depthCompareFunction));
    
    if (_depthStencilInfo.stencilTestEnabled)
        glEnable(GL_STENCIL_TEST);
    else
        glDisable(GL_STENCIL_TEST);
    
    // stencil test
    if (_depthStencilInfo.stencilTestEnabled)
    {
        if (_isBackFrontStencilEqual)
        {
            glStencilFunc(toGLComareFunction(_depthStencilInfo.frontFaceStencil.stencilCompareFunction),
                          stencilReferenceValueFront,
                          _depthStencilInfo.frontFaceStencil.readMask);
            glStencilOp(toGLStencilOperation(_depthStencilInfo.frontFaceStencil.stencilFailureOperation),
                        toGLStencilOperation(_depthStencilInfo.frontFaceStencil.depthFailureOperation),
                        toGLStencilOperation(_depthStencilInfo.frontFaceStencil.depthStencilPassOperation));
            glStencilMask(_depthStencilInfo.frontFaceStencil.writeMask);
        }
        else
        {
            glStencilFuncSeparate(GL_BACK,
                                  toGLComareFunction(_depthStencilInfo.backFaceStencil.stencilCompareFunction),
                                  stencilReferenceValueBack,
                                  _depthStencilInfo.backFaceStencil.readMask);
            glStencilFuncSeparate(GL_FRONT,
                                  toGLComareFunction(_depthStencilInfo.frontFaceStencil.stencilCompareFunction),
                                  stencilReferenceValueFront,
                                  _depthStencilInfo.frontFaceStencil.readMask);
            
            glStencilOpSeparate(GL_BACK,
                                toGLStencilOperation(_depthStencilInfo.backFaceStencil.stencilFailureOperation),
                                toGLStencilOperation(_depthStencilInfo.backFaceStencil.depthFailureOperation),
                                toGLStencilOperation(_depthStencilInfo.backFaceStencil.depthStencilPassOperation));
            glStencilOpSeparate(GL_FRONT,
                                toGLStencilOperation(_depthStencilInfo.frontFaceStencil.stencilFailureOperation),
                                toGLStencilOperation(_depthStencilInfo.frontFaceStencil.depthFailureOperation),
                                toGLStencilOperation(_depthStencilInfo.frontFaceStencil.depthStencilPassOperation));
            
            glStencilMaskSeparate(GL_BACK, _depthStencilInfo.backFaceStencil.writeMask);
            glStencilMaskSeparate(GL_FRONT, _depthStencilInfo.frontFaceStencil.writeMask);
        }
    }
    
    CHECK_GL_ERROR_DEBUG();
}

CC_BACKEND_END
