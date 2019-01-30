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

//TODO: simplify name
enum class VertexFormat : uint32_t
{
    FLOAT_R32G32B32A32,
    FLOAT_R32G32B32,
    FLOAT_R32G32,
    FLOAT_R32,
    INT_R32G32B32A32,
    INT_R32G32B32,
    INT_R32G32,
    INT_R32,
    USHORT_R16G16B16A16,
    USHORT_R16G16,
    UBYTE_R8G8B8A8,
    UNORM_R8G8B8A8,
    UNORM_R8G8
};

enum class TextureFormat : uint32_t
{
    NONE,
    // Four 8-bit normalized unsigned integer components in RGBA order.
    R8G8B8A8,
    // Three 8-bit normalized unsigned integer components in RGB order.
    R8G8B8,
    // One 8-bit normalized unsigned integer component.
    A8,
    // A packed 32-bit combined depth and stencil pixel format with two nomorlized unsigned integer
    // components: 24 bits, typically used for a depth render target, and 8 bits, typically used for
    // a stencil render target.
    D24S8,
    I8,
    AI88,
    RGBA4444,
    RGB565,
    RGB5A1,
    //metal 16 bits pixel formats
    MTL_B5G6R5,
    //MTL_A1BGR5,
    MTL_BGR5A1,
    MTL_ABGR4,
    // compressed format
    ETC1,
    ATC_RGB,
    ATC_EXPLICIT_ALPHA,
    ATC_INTERPOLATED_ALPHA,
    PVRTC2,
    PVRTC2A,
    PVRTC4,
    PVRTC4A,
    S3TC_DXT1,
    S3TC_DXT3,
    S3TC_DXT5,
    SYSTEM_DEFAULT
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
    LINEAR,
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
    SRC_ALPHA_SATURATE,
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
    bool mipmapEnabled = false;
    SamplerFilter magFilter = SamplerFilter::LINEAR;
    SamplerFilter minFilter = SamplerFilter::LINEAR;
    SamplerFilter mipmapFilter = SamplerFilter::LINEAR;
    SamplerAddressMode sAddressMode = SamplerAddressMode::CLAMP_TO_EDGE;
    SamplerAddressMode tAddressMode = SamplerAddressMode::CLAMP_TO_EDGE;
    
    SamplerDescriptor(bool _mipmapEnabled = false,
                      SamplerFilter _magFilter = SamplerFilter::LINEAR,
                      SamplerFilter _minFilter = SamplerFilter::LINEAR,
                      SamplerFilter _mipmapFilter = SamplerFilter::LINEAR,
                      SamplerAddressMode _sAddressMode = SamplerAddressMode::CLAMP_TO_EDGE,
                      SamplerAddressMode _tAddressMode = SamplerAddressMode::CLAMP_TO_EDGE
                      ):mipmapEnabled(_mipmapEnabled), magFilter(_magFilter), minFilter(_minFilter),
    mipmapFilter(_mipmapFilter), sAddressMode(_sAddressMode), tAddressMode(_tAddressMode) {}
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
    int location = 0;
    unsigned int type = 0;
    bool isArray = false;
    unsigned int bufferSize = 0;
};

struct UniformLocation
{
    int location = -1;
    ShaderStage shaderStage = ShaderStage::VERTEX;
};

struct AttributeBindInfo
{
    std::string attributeName;
    int         location    = -1;
    int         size        = 0;
    int         type        = 0;
};

CC_BACKEND_END
