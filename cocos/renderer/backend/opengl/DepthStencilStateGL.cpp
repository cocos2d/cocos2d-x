#include "DepthStencilStateGL.h"
#include "platform/CCGL.h"

#include "base/ccMacros.h"
#include "renderer/backend/opengl/UtilsGL.h"

CC_BACKEND_BEGIN

void DepthStencilStateGL::reset()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
}

DepthStencilStateGL::DepthStencilStateGL(const DepthStencilDescriptor& descriptor)
: DepthStencilState(descriptor)
{}

void DepthStencilStateGL::apply(unsigned int stencilReferenceValueFront, unsigned int stencilReferenceValueBack) const
{
    // depth test
    
    if (_depthStencilInfo.depthTestEnabled)
    {
        glEnable(GL_DEPTH_TEST); 
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
    
    if (_depthStencilInfo.depthWriteEnabled)
        glDepthMask(GL_TRUE);
    else
        glDepthMask(GL_FALSE);
    
    glDepthFunc(UtilsGL::toGLComareFunction(_depthStencilInfo.depthCompareFunction));
    
    if (_depthStencilInfo.stencilTestEnabled)
        glEnable(GL_STENCIL_TEST);
    else
        glDisable(GL_STENCIL_TEST);

    // stencil test
    if (_depthStencilInfo.stencilTestEnabled)
    {
        if (_isBackFrontStencilEqual)
        {
            glStencilFunc(UtilsGL::toGLComareFunction(_depthStencilInfo.frontFaceStencil.stencilCompareFunction),
                          stencilReferenceValueFront,
                          _depthStencilInfo.frontFaceStencil.readMask);
            glStencilOp(UtilsGL::toGLStencilOperation(_depthStencilInfo.frontFaceStencil.stencilFailureOperation),
                        UtilsGL::toGLStencilOperation(_depthStencilInfo.frontFaceStencil.depthFailureOperation),
                        UtilsGL::toGLStencilOperation(_depthStencilInfo.frontFaceStencil.depthStencilPassOperation));
            glStencilMask(_depthStencilInfo.frontFaceStencil.writeMask);
        }
        else
        {
            glStencilFuncSeparate(GL_BACK,
                                  UtilsGL::toGLComareFunction(_depthStencilInfo.backFaceStencil.stencilCompareFunction),
                                  stencilReferenceValueBack,
                                  _depthStencilInfo.backFaceStencil.readMask);
            glStencilFuncSeparate(GL_FRONT,
                                  UtilsGL::toGLComareFunction(_depthStencilInfo.frontFaceStencil.stencilCompareFunction),
                                  stencilReferenceValueFront,
                                  _depthStencilInfo.frontFaceStencil.readMask);
            
            glStencilOpSeparate(GL_BACK,
                                UtilsGL::toGLStencilOperation(_depthStencilInfo.backFaceStencil.stencilFailureOperation),
                                UtilsGL::toGLStencilOperation(_depthStencilInfo.backFaceStencil.depthFailureOperation),
                                UtilsGL::toGLStencilOperation(_depthStencilInfo.backFaceStencil.depthStencilPassOperation));
            glStencilOpSeparate(GL_FRONT,
                                UtilsGL::toGLStencilOperation(_depthStencilInfo.frontFaceStencil.stencilFailureOperation),
                                UtilsGL::toGLStencilOperation(_depthStencilInfo.frontFaceStencil.depthFailureOperation),
                                UtilsGL::toGLStencilOperation(_depthStencilInfo.frontFaceStencil.depthStencilPassOperation));
            
            glStencilMaskSeparate(GL_BACK, _depthStencilInfo.backFaceStencil.writeMask);
            glStencilMaskSeparate(GL_FRONT, _depthStencilInfo.frontFaceStencil.writeMask);
        }
    }
    
    CHECK_GL_ERROR_DEBUG();
}

CC_BACKEND_END
