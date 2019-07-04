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

#include "Macros.h"

#include <cstdint>
#include <string>

CC_BACKEND_BEGIN

enum class BufferUsage : uint32_t
{
    STATIC,
    DYNAMIC
};

enum class BufferType : uint32_t
{
    VERTEX,
    INDEX
};

enum class ShaderStage : uint32_t
{
    VERTEX,
    FRAGMENT,
    VERTEX_AND_FRAGMENT
};

enum class VertexFormat : uint32_t
{
    FLOAT4,
    FLOAT3,
    FLOAT2,
    FLOAT,
    INT4,
    INT3,
    INT2,
    INT,
    USHORT4,
    USHORT2,
    UBYTE4
};

/** @typedef backend::PixelFormat
     Possible texture pixel formats
     */
enum class PixelFormat
{
    //! auto detect the type
    AUTO,
    //! 32-bit texture: BGRA8888
    BGRA8888,
    //! 32-bit texture: RGBA8888
    RGBA8888,
    //! 24-bit texture: RGBA888
    RGB888,
    //! 16-bit texture without Alpha channel
    RGB565,
    //! 8-bit textures used as masks
    A8,
    //! 8-bit intensity texture
    I8,
    //! 16-bit textures used as masks
    AI88,
    //! 16-bit textures: RGBA4444
    RGBA4444,
    //! 16-bit textures: RGB5A1
    RGB5A1,
    //! 4-bit PVRTC-compressed texture: PVRTC4
    PVRTC4,
    //! 4-bit PVRTC-compressed texture: PVRTC4 (has alpha channel)
    PVRTC4A,
    //! 2-bit PVRTC-compressed texture: PVRTC2
    PVRTC2,
    //! 2-bit PVRTC-compressed texture: PVRTC2 (has alpha channel)
    PVRTC2A,
    //! ETC-compressed texture: ETC
    ETC,
    //! S3TC-compressed texture: S3TC_Dxt1
    S3TC_DXT1,
    //! S3TC-compressed texture: S3TC_Dxt3
    S3TC_DXT3,
    //! S3TC-compressed texture: S3TC_Dxt5
    S3TC_DXT5,
    //! ATITC-compressed texture: ATC_RGB
    ATC_RGB,
    //! ATITC-compressed texture: ATC_EXPLICIT_ALPHA
    ATC_EXPLICIT_ALPHA,
    //! ATITC-compressed texture: ATC_INTERPOLATED_ALPHA
    ATC_INTERPOLATED_ALPHA,
    //! Default texture format: AUTO

    MTL_B5G6R5,
    //MTL_A1BGR5,
    MTL_BGR5A1,
    MTL_ABGR4,

    // A packed 32-bit combined depth and stencil pixel format with two nomorlized unsigned integer
    // components: 24 bits, typically used for a depth render target, and 8 bits, typically used for
    // a stencil render target.
    D24S8,

    DEFAULT = AUTO,

    NONE = -1
};

enum class TextureUsage : uint32_t
{
    READ,
    WRITE,
    RENDER_TARGET
};

enum class IndexFormat : uint32_t
{
    U_SHORT,
    U_INT
};

enum class VertexStepMode : uint32_t
{
    VERTEX,
    INSTANCE
};

enum class PrimitiveType : uint32_t
{
    POINT,
    LINE,
    LINE_STRIP,
    TRIANGLE,
    TRIANGLE_STRIP
};

enum class TextureType: uint32_t
{
    TEXTURE_2D,
    TEXTURE_CUBE
};

enum class SamplerAddressMode: uint32_t
{
    REPEAT,
    MIRROR_REPEAT,
    CLAMP_TO_EDGE,
    DONT_CARE,
};

enum class SamplerFilter: uint32_t
{
    NEAREST,
    NEAREST_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR,
    LINEAR_MIPMAP_LINEAR,
    LINEAR_MIPMAP_NEAREST,
    DONT_CARE,
};

enum class StencilOperation: uint32_t
{
    KEEP,
    ZERO,
    REPLACE,
    INVERT,
    INCREMENT_WRAP,
    DECREMENT_WRAP
};

enum class CompareFunction: uint32_t
{
    NEVER,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    EQUAL,
    NOT_EQUAL,
    ALWAYS
};

enum class BlendOperation: uint32_t
{
    ADD,
    SUBTRACT,
    RESERVE_SUBTRACT
};

enum class BlendFactor : uint32_t
{
    ZERO,
    ONE,
    SRC_COLOR,
    ONE_MINUS_SRC_COLOR,
    SRC_ALPHA,
    ONE_MINUS_SRC_ALPHA,
    DST_COLOR,
    ONE_MINUS_DST_COLOR,
    DST_ALPHA,
    ONE_MINUS_DST_ALPHA,
    CONSTANT_ALPHA,
    SRC_ALPHA_SATURATE,
    ONE_MINUS_CONSTANT_ALPHA,
    BLEND_CLOLOR
};

enum class ColorWriteMask: uint32_t
{
    NONE = 0x00000000,
    RED = 0x00000001,
    GREEN = 0x00000002,
    BLUE = 0x00000004,
    ALPHA = 0x00000008,
    ALL = 0x0000000F
};

struct SamplerDescriptor
{
    SamplerFilter magFilter = SamplerFilter::LINEAR;
    SamplerFilter minFilter = SamplerFilter::LINEAR;
    SamplerAddressMode sAddressMode = SamplerAddressMode::CLAMP_TO_EDGE;
    SamplerAddressMode tAddressMode = SamplerAddressMode::CLAMP_TO_EDGE;

    SamplerDescriptor() {}

    SamplerDescriptor(
        SamplerFilter _magFilter,
        SamplerFilter _minFilter,
        SamplerAddressMode _sAddressMode,
        SamplerAddressMode _tAddressMode
    ) : magFilter(_magFilter), minFilter(_minFilter),
        sAddressMode(_sAddressMode), tAddressMode(_tAddressMode) {}
};

enum class CullMode: uint32_t
{
    NONE = 0x00000000,
    BACK = 0x00000001,
    FRONT = 0x00000002
};

enum class Winding: uint32_t
{
    CLOCK_WISE,
    COUNTER_CLOCK_WISE
};

struct UniformInfo
{
    int count = 0;
    int location = -1;
    
    //in opengl, type means uniform data type, i.e. GL_FLOAT_VEC2, while in metal type means data basic type, i.e. float
    unsigned int type = 0;
    bool isArray = false;
    unsigned int bufferSize = 0;

    //only used in metal
    bool isMatrix = false;
    bool needConvert = false;
};

struct UniformLocation
{
    int location = -1;
    ShaderStage shaderStage = ShaderStage::VERTEX;
    UniformLocation() = default;
    operator bool() { return location >= 0; }
    void reset() { location = -1; }

    bool operator == (const UniformLocation &other) const;
    std::size_t operator()(const UniformLocation &uniform) const;
};


struct AttributeBindInfo
{
    std::string attributeName;
    int         location    = -1;
    int         size        = 0;
    int         type        = 0;
};

enum class TextureCubeFace : uint32_t
{
    POSITIVE_X = 0,
    NEGATIVE_X = 1,
    POSITIVE_Y = 2, 
    NEGATIVE_Y = 3, 
    POSITIVE_Z = 4,
    NEGATIVE_Z = 5
};

CC_BACKEND_END
