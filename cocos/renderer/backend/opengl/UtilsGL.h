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
 
#pragma once

#include "base/ccMacros.h"
#include "platform/CCGL.h"
#include "renderer/backend/Types.h"

CC_BACKEND_BEGIN
/**
 * @addtogroup _opengl
 * @{
 */

/**
 * Convert backend enum class to corresponding opengl defined value.
 */
class UtilsGL
{
public:
    /**
     * Convert attribute enum classs type to GLenum type. i.e. convert VertexFormat::FLOAT4 to GL_FLOAT.
     * @param vertexFormat Specifies the attribute data type to convert.
     * @return Attribute type.
     */
    static GLenum toGLAttributeType(VertexFormat vertexFormat);

    /**
     * Convert attribute component count to GLsizei. i.e. convert VertexFormat::FLOAT4 to 4.
     * @param vertexFormat Specifies the attribute type.
     * @return Attribute component counts.
     */
    static GLsizei getGLAttributeSize(VertexFormat vertexFormat);

    /**
     * Get opengl data type size in bytes. i.e. GL_FLOAT_VEC4 data type size is sizeof(GLfloat) * 4.
     * @param size  Specifies the data type.
     * @return Data type size in bytes.
     */
    static GLsizei getGLDataTypeSize(GLenum size);

    /**
     * Convert magnification filter to GLint. i.e. convert SamplerFilter::LINEAR to GL_LINEAR.
     * @param magFilter Specifies the magnification filter to convert.
     * @return Magnification filter.
     */
    static GLint toGLMagFilter(SamplerFilter magFilter);

    /**
     * Convert minifying filter to GLint. i.e. convert SamplerFilter::LINEAR to GL_LINEAR.
     * If mipmaps is enabled and texture width and height are not power of two, then if minFilter is SamplerFilter::LINEAR, GL_LINEAR is returned, otherwise return GL_NEAREST.
     * @param minFilter Specifies minifying filter.
     * @param hasMipmaps Specifies whether mipmap is enabled.
     * @param isPow2 Specifies if texture width and height are power of two.
     * @return Minifying filter
     */
    static GLint toGLMinFilter(SamplerFilter minFilter, bool hasMipmaps, bool isPow2);

    /**
     * Convert wrap parameter for texture coordinate to GLint. i.e. convert SamplerAddressMode::REPEAT to GL_REPEAT.
     * If texture width and height are not power of 2, then GL_CLAMP_TO_EDGE is returned.
     * @param addressMode Specifies wrapping mode.
     * @param isPow2 Specifies if texture width and height are power of two.
     * @return Wrap mode.
     */
    static GLint toGLAddressMode(SamplerAddressMode addressMode, bool isPow2);

    /**
     * Get textrue parameters from texture pixle format.
     * @param in textureFormat Specifies texture pixel format.
     * @param out internalFormat Specifies the internal format of the texture. 
     * @param out format Specifies the format of the texel data.
     * @param out type Specifies the data type of the texel data. 
     * @param out isCompressed Specifies if the texel data is compressed.
     */
    static void toGLTypes(PixelFormat textureFormat, GLint &internalFormat, GLuint &format, GLenum &type, bool &isCompressed);

    /**
     * Convert compare function to GLenum. i.e. convert CompareFunction::NEVER to GL_NEVER.
     * @param compareFunction Specifies the compare function to convert.
     * @return Compare function.
     */
    static GLenum toGLComareFunction(CompareFunction compareFunction);

    /**
     * Convert stencil operation to GLenum. i.e. convert StencilOperation::KEEP to GL_KEEP.
     * @param stencilOperation Specifies stencil operation.
     * @return Stencil operation.
     */
    static GLenum toGLStencilOperation(StencilOperation stencilOperation);

    /**
     * Convert blend operation to GLenum. i.e. convert BlendOperation::ADD to GL_FUNC_ADD.
     * @param blendOperation Specifies blend function to convert.
     * @return Blend operation.
     */
    static GLenum toGLBlendOperation(BlendOperation blendOperation);

    /**
     * Convert blend factor to GLenum. i.e. convert BlendFactor::ZERO to GL_ZERO.
     * @param blendFactor Specifies the blend factor to convert.
     * @return Blend factor.
     */
    static GLenum toGLBlendFactor(BlendFactor blendFactor);

    /**
     * Convert winding value to GLenum. i.e. convert Winding::CLOCK_WISE to GL_CW.
     * @param winding Specifies the winding value to convert.
     * @return Winding mode.
     */
    static GLenum toGLFrontFace(Winding winding);

    /**
     * Convert primitive type to GLenum. i.e. convert PrimitiveType::TRIANGLE to GL_TRIANGLES.
     * @param primitiveType Specifies the kind of primitives to convert.
     * @return Primitive type.
     */
    static GLenum toGLPrimitiveType(PrimitiveType primitiveType);

    /**
     * Convert index type to GLenum. i.e. convert IndexFormat::U_INT to GL_UNSIGNED_INT.
     * @param indexType Specifies the index type to convert.
     * @return Index type.
     */
    static GLenum toGLIndexType(IndexFormat indexType);

    /**
     * Convert cull mode to GLenum. i.e. convert CullMode::BACK to GL_BACK.
     * @param mode Specifies the cull mode to convert.
     * @return Cull mode.
     */
    static GLenum toGLCullMode(CullMode mode);
};
//end of _opengl group
/// @}
CC_BACKEND_END