#include "BundleData.h"
#include "C3DVertexFormat.h"
#include "C3DAABB.h"

// Object deletion macro
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) \
    if (x) \
    { \
        delete x; \
        x = nullptr; \
    }
#endif

// Array deletion macro
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) \
    if (x) \
    { \
        delete[] x; \
        x = nullptr; \
    }
#endif

namespace cocos2d
{

MeshData::MeshData(C3DVertexElement* elements, unsigned int elementCount)
    : vertexFormat(nullptr), vertexCount(0), vertexData(nullptr), boundingBox(nullptr)
{
    vertexFormat = new C3DVertexFormat(elements,elementCount);
    boundingBox = new C3DAABB();
}

MeshData::~MeshData()
{
    SAFE_DELETE(vertexFormat);
    SAFE_DELETE_ARRAY(vertexData);

    for (unsigned int i = 0; i < parts.size(); ++i)
    {
        SAFE_DELETE(parts[i]);
    }
    SAFE_DELETE(boundingBox);
    
}

MeshSkinData::MeshSkinData(): skin(nullptr)
{

}

MeshSkinData::~MeshSkinData()
{
    skin = nullptr;
}


BonePartData::BonePartData()
{
    indexData = nullptr;
}

BonePartData::~BonePartData()
{
    SAFE_DELETE_ARRAY(indexData);
}

MeshPartData::MeshPartData() :
    indexCount(0), indexData(nullptr)
{
}

MeshPartData::~MeshPartData()
{
    SAFE_DELETE_ARRAY(indexData);
}

}
