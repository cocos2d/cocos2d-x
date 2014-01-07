#include "MeshPart.h"


namespace cocos2d
{

MeshPart::MeshPart() :
    _mesh(nullptr), _meshIndex(0), _primitiveType(PrimitiveType_TRIANGLES), _indexCount(0), _indexBuffer(0), _dynamic(false)
{
}


MeshPart::~MeshPart()
{
    if (_indexBuffer)
    {
        glDeleteBuffers(1, &_indexBuffer);
    }
}

MeshPart* MeshPart::create(C3DMesh* mesh, unsigned int meshIndex, PrimitiveType primitiveType,
    IndexFormat indexFormat, unsigned int indexCount, bool dynamic)
{
    // Create a VBO for our index buffer.
    GLuint vbo;
    GL_ASSERT( glGenBuffers(1, &vbo) );
    if (GL_LAST_ERROR())
    {
        return nullptr;
    }

    GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo) );
    if (GL_LAST_ERROR())
    {
        glDeleteBuffers(1, &vbo);
        return nullptr;
    }

    unsigned int indexSize = 0;
    switch (indexFormat)
    {
    case IndexFormat_INDEX8:
        indexSize = 1;
        break;
    case IndexFormat_INDEX16:
        indexSize = 2;
        break;
    case IndexFormat_INDEX32:
        indexSize = 4;
        break;
    }
    GL_CHECK( glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * indexCount, nullptr, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW) );
    if (GL_LAST_ERROR())
    {
        glDeleteBuffers(1, &vbo);
        return nullptr;
    }
     GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );


    MeshPart* part = new MeshPart();
    part->_mesh = mesh;
    part->_meshIndex = meshIndex;
    part->_primitiveType = primitiveType;
    part->_indexFormat = indexFormat;
    part->_indexCount = indexCount;
    part->_indexBuffer = vbo;
    part->_dynamic = dynamic;

    return part;
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

IndexBufferHandle MeshPart::getIndexBuffer() const
{
    return _indexBuffer;
}

bool MeshPart::isDynamic() const
{
    return _dynamic;
}

void MeshPart::setIndexData(void* indexData, unsigned int indexStart, unsigned int indexCount)
{
    GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer) );

    unsigned int indexSize = 0;
    switch (_indexFormat)
    {
    case IndexFormat_INDEX8:
        indexSize = 1;
        break;
    case IndexFormat_INDEX16:
        indexSize = 2;
        break;
    case IndexFormat_INDEX32:
        indexSize = 4;
        break;
    }

    if (indexStart == 0 && indexCount == 0)
    {
        GL_ASSERT( glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * _indexCount, indexData, _dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW) );
    }
    else
    {
        if (indexCount == 0)
        {
            indexCount = _indexCount - indexStart;
        }

        GL_ASSERT( glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indexStart * indexSize, indexCount * indexSize, indexData) );
    }

    GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
}

}
