#pragma once

#include "base/ccMacros.h"
#include "platform/CCGL.h"
#include "renderer/backend/Types.h"

CC_BACKEND_BEGIN

class UtilsGL
{
public:
    static GLenum toGLAttributeType(VertexFormat texture);
    static GLsizei getGLAttributeSize(VertexFormat vertexFormat);
    static GLsizei getGLDataTypeSize(GLenum size);

    static GLint toGLMagFilter(SamplerFilter magFilter);
    static GLint toGLMinFilter(SamplerFilter minFilter, bool hasMipmaps, bool isPow2);
    static GLint toGLAddressMode(SamplerAddressMode addressMode, bool isPow2);
    static void toGLTypes(TextureFormat textureFormat, GLint &internalFormat, GLuint &format, GLenum &type, bool &isCompressed);

    static GLenum toGLComareFunction(CompareFunction compareFunction);
    static GLenum toGLStencilOperation(StencilOperation stencilOperation);

    static GLenum toGLBlendOperation(BlendOperation blendOperation);
    static GLenum toGLBlendFactor(BlendFactor blendFactor);

    static GLenum toGLFrontFace(Winding winding);
    static GLenum toGLPrimitiveType(PrimitiveType primitiveType);
    static GLenum toGLIndexType(IndexFormat indexType);
    static GLenum toGLCullMode(CullMode mode);
};

CC_BACKEND_END