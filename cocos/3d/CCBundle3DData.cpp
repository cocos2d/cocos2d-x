#include "3d/CCBundle3DData.h"

NS_CC_BEGIN


int MeshVertexAttrib::getAttribSizeBytes() const
{
    int ret = 0;
    switch (type)
    {
    case backend::VertexFormat::FLOAT_R32G32B32A32:
    case backend::VertexFormat::INT_R32G32B32A32:
        return 16;
    case backend::VertexFormat::FLOAT_R32G32B32:
    case backend::VertexFormat::INT_R32G32B32:
        return 12;
    case backend::VertexFormat::FLOAT_R32G32:
    case backend::VertexFormat::INT_R32G32:
    case backend::VertexFormat::USHORT_R16G16B16A16:
        return 8;
    case backend::VertexFormat::FLOAT_R32:
    case backend::VertexFormat::INT_R32:
    case backend::VertexFormat::UBYTE_R8G8B8A8:
    case backend::VertexFormat::UNORM_R8G8B8A8:
    case backend::VertexFormat::USHORT_R16G16:
        return 4;
    case backend::VertexFormat::UNORM_R8G8:
        return 2;
    default:
        CCASSERT(false, "VertexFormat convert to size error");
    }
    return ret;
}

NS_CC_END