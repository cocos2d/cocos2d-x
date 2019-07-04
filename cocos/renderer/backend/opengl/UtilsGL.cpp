/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#include "UtilsGL.h"
#include "ProgramGL.h"
#include "renderer/backend/Types.h"

CC_BACKEND_BEGIN


GLenum UtilsGL::toGLAttributeType(VertexFormat vertexFormat)
{
    GLenum ret = GL_INT;
    switch (vertexFormat)
    {
    case VertexFormat::FLOAT4:
    case VertexFormat::FLOAT3:
    case VertexFormat::FLOAT2:
    case VertexFormat::FLOAT:
        ret = GL_FLOAT;
        break;
    case VertexFormat::INT4:
    case VertexFormat::INT3:
    case VertexFormat::INT2:
    case VertexFormat::INT:
        ret = GL_INT;
        break;
    case VertexFormat::UBYTE4:
        ret = GL_UNSIGNED_BYTE;
        break;
    default:
        break;
    }
    return ret;
}

GLsizei UtilsGL::getGLAttributeSize(VertexFormat vertexFormat)
{
    GLsizei ret = 0;
    switch (vertexFormat)
    {
    case VertexFormat::FLOAT4:
    case VertexFormat::INT4:
    case VertexFormat::UBYTE4:
        ret = 4;
        break;
    case VertexFormat::FLOAT3:
    case VertexFormat::INT3:
        ret = 3;
        break;
    case VertexFormat::FLOAT2:
    case VertexFormat::INT2:
        ret = 2;
        break;
    case VertexFormat::FLOAT:
    case VertexFormat::INT:
        ret = 1;
        break;
    default:
        break;
    }
    return ret;
}

GLsizei UtilsGL::getGLDataTypeSize(GLenum size)
{
    GLsizei ret = 0;
    switch (size)
    {
    case GL_BOOL:
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
        ret = sizeof(GLbyte);
        break;
    case GL_BOOL_VEC2:
    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
        ret = sizeof(GLshort);
        break;
    case GL_BOOL_VEC3:
        ret = sizeof(GLboolean);
        break;
    case GL_BOOL_VEC4:
    case GL_INT:
    case GL_UNSIGNED_INT:
    case GL_FLOAT:
        ret = sizeof(GLfloat);
        break;
    case GL_FLOAT_VEC2:
    case GL_INT_VEC2:
        ret = sizeof(GLfloat) * 2;
        break;
    case GL_FLOAT_VEC3:
    case GL_INT_VEC3:
        ret = sizeof(GLfloat) * 3;
        break;
    case GL_FLOAT_MAT2:
    case GL_FLOAT_VEC4:
    case GL_INT_VEC4:
        ret = sizeof(GLfloat) * 4;
        break;
    case GL_FLOAT_MAT3:
        ret = sizeof(GLfloat) * 9;
        break;
    case GL_FLOAT_MAT4:
        ret = sizeof(GLfloat) * 16;
        break;
    default:
        break;
    }
    return ret;
}


GLint UtilsGL::toGLMagFilter(SamplerFilter magFilter)
{
    GLint ret = GL_LINEAR;
    switch (magFilter)
    {
    case SamplerFilter::LINEAR:
        ret = GL_LINEAR;
        break;
    case SamplerFilter::NEAREST:
        ret = GL_NEAREST;
        break;
    default:
        break;
    }
    return ret;
}

GLint UtilsGL::toGLMinFilter(SamplerFilter minFilter, bool hasMipmaps, bool isPow2)
{
    if (hasMipmaps && !isPow2)
    {
        CCLOG("Change minification filter to either NEAREST or LINEAR since non-power-of-two texture occur in %s %s %d", __FILE__, __FUNCTION__, __LINE__);
        if (SamplerFilter::LINEAR == minFilter)
            return GL_LINEAR;
        else
            return GL_NEAREST;
    }

    switch (minFilter)
    {
        case SamplerFilter::LINEAR:
            return GL_LINEAR;
        case SamplerFilter::LINEAR_MIPMAP_LINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;
        case SamplerFilter::LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;
        case SamplerFilter::NEAREST:
            return GL_NEAREST;
        case SamplerFilter::NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
        case SamplerFilter::NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;
        default:
            break;
    }

    return GL_NEAREST;
}

GLint UtilsGL::toGLAddressMode(SamplerAddressMode addressMode, bool isPow2)
{
    GLint ret = GL_REPEAT;
    if (!isPow2 && (addressMode != SamplerAddressMode::CLAMP_TO_EDGE))
    {
        CCLOG("Change texture wrap mode to CLAMP_TO_EDGE since non-power-of-two texture occur in %s %s %d", __FILE__, __FUNCTION__, __LINE__);
        return GL_CLAMP_TO_EDGE;
    }

    switch (addressMode)
    {
    case SamplerAddressMode::REPEAT:
        ret = GL_REPEAT;
        break;
    case SamplerAddressMode::MIRROR_REPEAT:
        ret = GL_MIRRORED_REPEAT;
        break;
    case SamplerAddressMode::CLAMP_TO_EDGE:
        ret = GL_CLAMP_TO_EDGE;
        break;
    default:
        break;
    }
    return ret;
}


void UtilsGL::toGLTypes(PixelFormat textureFormat, GLint &internalFormat, GLuint &format, GLenum &type, bool &isCompressed)
{
    switch (textureFormat)
    {
    case PixelFormat::RGBA8888:
        internalFormat = GL_RGBA;
        format = GL_RGBA;
        type = GL_UNSIGNED_BYTE;
        break;
    case PixelFormat::RGB888:
        internalFormat = GL_RGB;
        format = GL_RGB;
        type = GL_UNSIGNED_BYTE;
        break;
    case PixelFormat::RGBA4444:
        internalFormat = GL_RGBA;
        format = GL_RGBA;
        type = GL_UNSIGNED_SHORT_4_4_4_4;
        break;
    case PixelFormat::A8:
        internalFormat = GL_ALPHA;
        format = GL_ALPHA;
        type = GL_UNSIGNED_BYTE;
        break;
    case PixelFormat::I8:
        internalFormat = GL_LUMINANCE;
        format = GL_LUMINANCE;
        type = GL_UNSIGNED_BYTE;
        break;
    case PixelFormat::AI88:
        internalFormat = GL_LUMINANCE_ALPHA;
        format = GL_LUMINANCE_ALPHA;
        type = GL_UNSIGNED_BYTE;
        break;
    case PixelFormat::RGB565:
        internalFormat = GL_RGB;
        format = GL_RGB;
        type = GL_UNSIGNED_SHORT_5_6_5;
        break;
    case PixelFormat::RGB5A1:
        internalFormat = GL_RGBA;
        format = GL_RGBA;
        type = GL_UNSIGNED_SHORT_5_5_5_1;
        break;
#ifdef GL_ETC1_RGB8_OES
    case PixelFormat::ETC:
        internalFormat = GL_ETC1_RGB8_OES;
        format = 0xFFFFFFFF;
        type = 0xFFFFFFFF;
        isCompressed = true;
        break;
#endif // GL_ETC1_RGB8_OES
#ifdef GL_ATC_RGB_AMD
    case PixelFormat::ATC_RGB:
        internalFormat = GL_ATC_RGB_AMD;
        format = 0xFFFFFFFF;
        type = 0xFFFFFFFF;
        isCompressed = true;
        break;
#endif // GL_ATC_RGB_AMD
#ifdef GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
    case PixelFormat::ATC_EXPLICIT_ALPHA:
        internalFormat = GL_ATC_RGBA_EXPLICIT_ALPHA_AMD;
        format = 0xFFFFFFFF;
        type = 0xFFFFFFFF;
        isCompressed = true;
        break;
#endif // GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
#ifdef GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD
    case PixelFormat::ATC_INTERPOLATED_ALPHA:
        internalFormat = GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD;
        format = 0xFFFFFFFF;
        type = 0xFFFFFFFF;
        isCompressed = true;
        break;
#endif // GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD

#ifdef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
    case PixelFormat::PVRTC2:
        internalFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
        format = 0xFFFFFFFF;
        type = 0xFFFFFFFF;
        isCompressed = true;
        break;
#endif 
#ifdef GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG
    case PixelFormat::PVRTC2A:
        internalFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
        format = 0xFFFFFFFF;
        type = 0xFFFFFFFF;
        isCompressed = true;
        break;
#endif
#ifdef GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG
    case PixelFormat::PVRTC4:
        internalFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
        format = 0xFFFFFFFF;
        type = 0xFFFFFFFF;
        isCompressed = true;
        break;
#endif
#ifdef GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG
    case PixelFormat::PVRTC4A:
        internalFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
        format = 0xFFFFFFFF;
        type = 0xFFFFFFFF;
        isCompressed = true;
        break;
#endif
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
    case PixelFormat::S3TC_DXT1:
        internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        format = 0xFFFFFFFF;
        type = 0xFFFFFFFF;
        isCompressed = true;
        break;
#endif 
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
    case PixelFormat::S3TC_DXT3:
        internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        format = 0xFFFFFFFF;
        type = 0xFFFFFFFF;
        isCompressed = true;
        break;
#endif
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
    case PixelFormat::S3TC_DXT5:
        internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        format = 0xFFFFFFFF;
        type = 0xFFFFFFFF;
        isCompressed = true;
        break;
#endif
        //        case PixelFormat::D16:
        //            format = GL_DEPTH_COMPONENT;
        //            internalFormat = GL_DEPTH_COMPONENT;
        //            type = GL_UNSIGNED_INT;
    case PixelFormat::D24S8:
#ifdef CC_USE_GLES
        format = GL_DEPTH_STENCIL_OES;
        internalFormat = GL_DEPTH_STENCIL_OES;
        type = GL_UNSIGNED_INT_24_8_OES;
#else
        format = GL_DEPTH_STENCIL;
        internalFormat = GL_DEPTH24_STENCIL8;
        type = GL_UNSIGNED_INT_24_8;
#endif
        break;
    default:
        break;
    }
}


GLenum UtilsGL::toGLComareFunction(CompareFunction compareFunction)
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

GLenum UtilsGL::toGLStencilOperation(StencilOperation stencilOperation)
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


GLenum UtilsGL::toGLBlendOperation(BlendOperation blendOperation)
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

GLenum UtilsGL::toGLBlendFactor(BlendFactor blendFactor)
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

GLenum UtilsGL::toGLFrontFace(Winding winding)
{
    if (Winding::CLOCK_WISE == winding)
        return GL_CW;
    else
        return GL_CCW;
}

GLenum UtilsGL::toGLPrimitiveType(PrimitiveType primitiveType)
{
    GLenum ret = GL_TRIANGLES;
    switch (primitiveType)
    {
    case PrimitiveType::POINT:
        ret = GL_POINTS;
        break;
    case PrimitiveType::LINE:
        ret = GL_LINES;
        break;
    case PrimitiveType::LINE_STRIP:
        ret = GL_LINE_STRIP;
        break;
    case PrimitiveType::TRIANGLE:
        ret = GL_TRIANGLES;
        break;
    case PrimitiveType::TRIANGLE_STRIP:
        ret = GL_TRIANGLE_STRIP;
        break;
    default:
        break;
    }
    return ret;
}

GLenum UtilsGL::toGLIndexType(IndexFormat indexType)
{
    GLenum ret = GL_BYTE;
    switch (indexType)
    {
    case IndexFormat::U_INT:
        ret = GL_UNSIGNED_INT;
        break;
    case IndexFormat::U_SHORT:
        ret = GL_UNSIGNED_SHORT;
        break;
    default:
        break;
    }
    return ret;
}

GLenum UtilsGL::toGLCullMode(CullMode mode)
{
    if (CullMode::BACK == mode)
        return GL_BACK;
    else
        return GL_FRONT;
}

CC_BACKEND_END