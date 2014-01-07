#include "Base.h"
#include "C3DMesh.h"
#include "MeshPart.h"
#include "C3DVertexFormat.h"
#include "C3DAABB.h"

namespace cocos2d
{

C3DMesh::C3DMesh(C3DVertexFormat* vertexFormat) 
    : _vertexFormat(nullptr), _vertexCount(0), _vertexBuffer(0), _primitiveType(PrimitiveType_TRIANGLES), 
      _partCount(0), _parts(nullptr), _dynamic(false)
{
    _vertexFormat = new C3DVertexFormat(vertexFormat);
    _vertexData = nullptr;
    _boundingBox = new C3DAABB();
}



C3DMesh::~C3DMesh()
{
    SAFE_DELETE(_vertexFormat);
    
    for (unsigned int i = 0; i < _partCount; ++i)
    {
        SAFE_DELETE(_parts[i]);
    }
    SAFE_DELETE_ARRAY(_parts);

    if (_vertexBuffer)
    {
        glDeleteBuffers(1, &_vertexBuffer);
        _vertexBuffer = 0;
    }

    SAFE_DELETE_ARRAY(_vertexData);
    SAFE_DELETE(_boundingBox);
}

C3DMesh* C3DMesh::createMesh(C3DVertexFormat* vertexFormat, unsigned int vertexCount, bool dynamic)
{
    GLuint vbo;
    GL_ASSERT( glGenBuffers(1, &vbo) );
    if (GL_LAST_ERROR())
    {
        return NULL;
    }

    GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
    if (GL_LAST_ERROR())
    {
        glDeleteBuffers(1, &vbo);
        return NULL;
    }

    GL_CHECK( glBufferData(GL_ARRAY_BUFFER, vertexFormat->getVertexSize() * vertexCount, NULL, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW) );
    if (GL_LAST_ERROR())
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &vbo);
        return NULL;
    }

    GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, 0) );
    C3DMesh* mesh = new C3DMesh(vertexFormat);
    mesh->_vertexCount = vertexCount;
    mesh->_vertexBuffer = vbo;
    mesh->_dynamic = dynamic;
    return mesh;
}

const std::string& C3DMesh::getUrl() const
{
    return _url;
}

const C3DVertexFormat* C3DMesh::getVertexFormat() const
{
    return _vertexFormat;
}

unsigned int C3DMesh::getVertexCount() const
{
    return _vertexCount;
}

unsigned int C3DMesh::getVertexSize() const
{
    return _vertexFormat->getVertexSize();
}

VertexBufferHandle C3DMesh::getVertexBuffer() const
{
    return _vertexBuffer;
}

bool C3DMesh::isDynamic() const
{
    return _dynamic;
}

PrimitiveType C3DMesh::getPrimitiveType() const
{
    return _primitiveType;
}

void C3DMesh::setPrimitiveType(PrimitiveType type)
{
    _primitiveType = type;
}

void C3DMesh::setVertexData(void* vertexData, unsigned int vertexStart, unsigned int vertexCount)
{
    GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer) );

    if (vertexStart == 0 && vertexCount == 0)
    {
        GL_ASSERT( glBufferData(GL_ARRAY_BUFFER, _vertexCount * _vertexFormat->getVertexSize(), vertexData, _dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW) );
    }
    else
    {
        if (vertexCount == 0)
        {
            vertexCount = _vertexCount - vertexStart;
        }

        GL_ASSERT( glBufferSubData(GL_ARRAY_BUFFER, vertexStart * _vertexFormat->getVertexSize(), vertexCount * _vertexFormat->getVertexSize(), vertexData) );
    }    

    GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}

void C3DMesh::setVertexData(unsigned char* vertexData)
{
    int vertexByteCount = _vertexCount*_vertexFormat->getVertexSize();
    _vertexData = new unsigned char[vertexByteCount];
    memcpy(_vertexData,vertexData,vertexByteCount);
}

    
unsigned int C3DMesh::getTriangleCount() const
{
    int nTriangle = 0;
    if (_partCount > 0)
    {
        for (unsigned int i = 0; i < _partCount; i++) {
            nTriangle += _parts[i]->getTriangleCount();
        }
    }
    else
    {
        if (_primitiveType == PrimitiveType_TRIANGLES)
            nTriangle += _vertexCount / 3;
        else if (_primitiveType == PrimitiveType_TRIANGLE_STRIP)
            nTriangle += _vertexCount - 2;
            
    }
    return nTriangle;
}

MeshPart* C3DMesh::addPart(PrimitiveType primitiveType, IndexFormat indexFormat, unsigned int indexCount, bool dynamic)
{
    MeshPart* part = MeshPart::create(this, _partCount, primitiveType, indexFormat, indexCount, dynamic);
    if (part)
    {
        // Increase size of part array and copy old subets into it.
        MeshPart** oldParts = _parts;
        _parts = new MeshPart*[_partCount + 1];
        for (unsigned int i = 0; i < _partCount; ++i)
        {
            _parts[i] = oldParts[i];
        }

        // Add new part to array.
        _parts[_partCount++] = part;

        // Delete old part array.
        SAFE_DELETE_ARRAY(oldParts);
    }

    return part;
}

unsigned int C3DMesh::getPartCount() const
{
    return _partCount;
}

MeshPart* C3DMesh::getPart(unsigned int index)
{
    return _parts[index];
}

}
