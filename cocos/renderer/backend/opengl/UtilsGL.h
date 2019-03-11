#pragma once

#include "base/ccMacros.h"
#include "renderer/backend/Types.h"
#include "platform/CCGL.h"

#ifdef CC_USE_METAL
#error "this header should only included in opengl"
#endif
CC_BACKEND_BEGIN

class UtilsGL
{
public:
    static GLenum toGLAttributeType(VertexFormat texture);
    static GLsizei getGLAttributeSize(VertexFormat vertexFormat);
    static GLsizei getGLDataTypeSize(GLenum size);

    static GLint toGLMagFilter(SamplerFilter magFilter);
    static GLint toGLMinFilter(SamplerFilter minFilter, SamplerFilter mipmapFilter, bool mipmapEnabled, bool isPow2);
    static GLint toGLAddressMode(SamplerAddressMode addressMode, bool isPow2);
    static void toGLTypes(TextureFormat textureFormat, GLint &internalFormat, GLuint &format, GLenum &type, bool &isCompressed);

    static GLenum toGLComareFunction(CompareFunction compareFunction);
    static GLenum toGLStencilOperation(StencilOperation stencilOperation);

    static GLenum toGLBlendOperation(BlendOperation blendOperation);
    static GLenum toGLBlendFactor(BlendFactor blendFactor);
};

CC_BACKEND_END