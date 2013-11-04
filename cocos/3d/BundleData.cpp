#include "BundleData.h"
#include "C3DVertexFormat.h"
#include "C3DAABB.h"

// Object deletion macro
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) \
    if (x) \
    { \
        delete x; \
        x = NULL; \
    }
#endif

// Array deletion macro
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) \
    if (x) \
    { \
        delete[] x; \
        x = NULL; \
    }
#endif

namespace cocos3d
{

MeshData::MeshData(C3DVertexElement* elements, unsigned int elementCount)
	: vertexFormat(NULL), vertexCount(0), vertexData(NULL), boundingBox(NULL)
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

MeshSkinData::MeshSkinData()
{
	skin = NULL;
}

MeshSkinData::~MeshSkinData()
{
	skin = NULL;
}


BonePartData::BonePartData()
{
	indexData = NULL;
}

BonePartData::~BonePartData()
{
	SAFE_DELETE_ARRAY(indexData);
}

MeshPartData::MeshPartData() :
    indexCount(0), indexData(NULL)
{
}

MeshPartData::~MeshPartData()
{
    SAFE_DELETE_ARRAY(indexData);
}

}
