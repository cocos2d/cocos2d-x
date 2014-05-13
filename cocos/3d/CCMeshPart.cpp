
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "base/ccMacros.h"
#include "CCMeshPart.h"
#include "CCMesh.h"

using namespace std;
using namespace cocos2d;

NS_CC_BEGIN

MeshPart::MeshPart() :
_mesh(NULL), _meshIndex(0), _primitiveType(PrimitiveType_TRIANGLES), _indexCount(0), _indexBuffer(0), _indexFormat(IndexFormat_INDEX16)
{
}

MeshPart::~MeshPart()
{
    if (_indexBuffer)
    {
        glDeleteBuffers(1, &_indexBuffer);
    }
}

unsigned int MeshPart::getMeshIndex() const
{
    return _meshIndex;
}

PrimitiveType MeshPart::getPrimitiveType() const
{
    return _primitiveType;
}

unsigned int MeshPart::getIndexCount() const
{
    return _indexCount;
}

IndexFormat MeshPart::getIndexFormat() const
{
    return _indexFormat;
}

GLuint MeshPart::getIndexBuffer() const
{
    return _indexBuffer;
}

MeshPart* MeshPart::create(Mesh* mesh, unsigned int meshIndex, PrimitiveType primitiveType, IndexFormat indexformat,  void* indexData, unsigned int indexCount)
{
    // Create a VBO for our index buffer.
    GLuint vbo;
    glGenBuffers(1, &vbo);
    
    
    ( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo) );
    
    unsigned int indexSize = 0;

    switch (indexformat)
    {
        case IndexFormat_INDEX8:
            indexSize = 1;
            break;
        case IndexFormat_INDEX16:
            indexSize = 2;
            break;
    }
    
    ( glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * indexCount, indexData, GL_STATIC_DRAW) );
    
    ( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
    
    MeshPart* part = new MeshPart();
    part->_mesh = mesh;
    part->_meshIndex = meshIndex;
    part->_primitiveType = primitiveType;
    part->_indexFormat = indexformat;
    part->_indexCount = indexCount;
    part->_indexBuffer = vbo;
    
    return part;
}

NS_CC_END
