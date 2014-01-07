#ifndef BUNDLEDATA_H_
#define BUNDLEDATA_H_

#include <vector>
#include "CocosMath.h"
#include "EnumDef_GL.h"

namespace cocos2d
{

class C3DMeshSkin;
class MeshPartData;
class C3DVertexFormat;
class C3DVertexElement;
class C3DAABB;

/**
mesh data 
*/
class MeshData
{
public:  
    /**
     * Constructor & Destructor.
     */
    MeshData(C3DVertexElement* elements, unsigned int elementCount);

    ~MeshData();

    C3DVertexFormat* vertexFormat;
    unsigned int vertexCount;
    unsigned char* vertexData;
    C3DAABB* boundingBox;

    PrimitiveType primitiveType;
    std::vector<MeshPartData*> parts;

};

/**
bone index data
*/
class BonePartData
{
public:
    /**
     * Constructor & Destructor.
     */
    BonePartData();

    ~BonePartData();

    unsigned int _batchID;
    unsigned int _offsetVertexIndex;
    unsigned int _numVertexIndex;

    unsigned int indexCount;
    unsigned char* indexData;
};

/**
mesh skin data
*/
class MeshSkinData
{
public:
    /**
     * Constructor & Destructor.
     */
    MeshSkinData();

    ~MeshSkinData();

    C3DMeshSkin* skin;
    std::vector<std::string> joints;
    std::vector<Matrix> inverseBindPoseMatrices;

    
};

/**
Mesh part index data
*/
class MeshPartData
{
public:
    /**
     * Constructor & Destructor.
     */
    MeshPartData();

    ~MeshPartData();

    PrimitiveType primitiveType;
    IndexFormat indexFormat;
    unsigned int indexCount;
    unsigned char* indexData;
};

}

#endif
