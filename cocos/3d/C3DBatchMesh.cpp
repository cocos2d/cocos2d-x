#include "C3DBatchMesh.h"
#include "C3DVertexFormat.h"
#include "Vertex.h"

namespace cocos3d
{

C3DBatchMesh::C3DBatchMesh(const C3DVertexFormat* vertexFormat, PrimitiveType primitiveType, bool bIndex, unsigned int initialCapacity, unsigned int growSize)
    : _vertexFormat(NULL), _primitiveType(primitiveType), _capacity(0), _growSize(growSize),
      _vertexCapacity(0), _vertexCount(0), _vertices(NULL), _verticesPtr(NULL), _indices(NULL), _indicesPtr(NULL), _indexCount(0)
{
	_vertexFormat = new C3DVertexFormat(vertexFormat);
    _bUseIndex = bIndex;
    _indexCapacity = 0;
    resize(initialCapacity);
}

C3DBatchMesh::~C3DBatchMesh()
{   
    SAFE_DELETE_ARRAY(_vertices);
    SAFE_DELETE_ARRAY(_indices);

	_verticesPtr = NULL;
	_indicesPtr = NULL;
	SAFE_DELETE(_vertexFormat);
}

unsigned int C3DBatchMesh::getCapacity() const
{
    return _capacity;
}

void C3DBatchMesh::setCapacity(unsigned int capacity)
{
    resize(capacity);
}
    
void C3DBatchMesh::setIndexCapacity(unsigned int capacity)
{
    resizeIndex(capacity);
}

bool C3DBatchMesh::resize(unsigned int capacity)
{   
    if (capacity == 0)
        return false;

    if (capacity == _capacity)
        return true;
    
    unsigned char* oldVertices = _vertices;    

    unsigned int vertexCapacity = 0;
    switch (_primitiveType)
    {
    case PrimitiveType_LINES:
        vertexCapacity = capacity * 2;
        
        break;   
    case PrimitiveType_TRIANGLES:
        vertexCapacity = capacity * 3;
        
        break;   
    default:
        assert(0); 
        break;
    }

    // Allocate new data and reset pointers
    unsigned int voffset = _verticesPtr - _vertices;
    unsigned int vBytes = vertexCapacity * _vertexFormat->getVertexSize();
    _vertices = new unsigned char[vBytes];
    if (voffset >= vBytes)
        voffset = vBytes - 1;
    _verticesPtr = _vertices + voffset;   

    // Copy old data back in
    if (oldVertices)
        memcpy(_vertices, oldVertices, std::min(_vertexCapacity, vertexCapacity) * _vertexFormat->getVertexSize());
    SAFE_DELETE_ARRAY(oldVertices); 

    // Assign new capacities
    _capacity = capacity;
    _vertexCapacity = vertexCapacity;
    
    

    return true;
}
    
bool C3DBatchMesh::resizeIndex(unsigned int capacity)
{
    if (_bUseIndex)
    {
        
        unsigned short* oldIndex = _indices;
        unsigned int voffset = _indicesPtr - _indices;
        unsigned int vBytes = capacity * sizeof(unsigned short);
        _indices = new unsigned short[capacity];
        if (voffset >= vBytes)
            voffset = vBytes - 1;
        _indicesPtr = _indices + voffset;
        
        if (oldIndex)
        {
            if (voffset)
            memcpy(_indices, oldIndex, voffset);
            SAFE_DELETE_ARRAY(oldIndex);
        }
        _indexCapacity = capacity;
    }
    
    return true;
}

void C3DBatchMesh::add(const BBVertex* vertices, unsigned int vertexCount)
{
    assert(sizeof(BBVertex) == _vertexFormat->getVertexSize() && !_bUseIndex);
    
    unsigned int newVertexCount = _vertexCount + vertexCount;    
    
    if (newVertexCount > _vertexCapacity)
    {
        if (_growSize == 0)
            return; 
		int growSize = ((newVertexCount - _vertexCapacity) / _growSize + 1) * _growSize;
		if (!resize(_capacity + growSize))
            return; 
    }    
    
    unsigned int vBytes = vertexCount * _vertexFormat->getVertexSize();
    memcpy(_verticesPtr, vertices, vBytes);    
    
    _verticesPtr += vBytes;
    _vertexCount = newVertexCount;
}

void C3DBatchMesh::add(const BBVertex* vertices, unsigned int vertexCount, const unsigned short* indices, unsigned int indexCount)
{
	assert(sizeof(BBVertex) == _vertexFormat->getVertexSize() && _bUseIndex);
	unsigned int newVertexCount = _vertexCount + vertexCount; 
	unsigned int newIdxCount = _indexCount + indexCount;
	unsigned int oldVertexCount = _vertexCount;

	if (newVertexCount > _vertexCapacity)
	{
		if (_growSize == 0)
			return; 

		int growSize = ((newVertexCount - _vertexCapacity) / _growSize + 1) * _growSize;
		if (!resize(_capacity + growSize))
			return; 
	}
	if (newIdxCount > _indexCapacity)
	{
		int growSize = ((newIdxCount - _indexCount) / _growSize + 1) * _growSize;
		if (!resizeIndex(_capacity + growSize))
			return;
	}

	unsigned int vBytes = vertexCount * _vertexFormat->getVertexSize();
	memcpy(_verticesPtr, vertices, vBytes);   

	_verticesPtr += vBytes;
	_vertexCount = newVertexCount;

	for (int i = 0; i < indexCount; i++) {
		*_indicesPtr = indices[i] + oldVertexCount;
		_indicesPtr++;
	}
	_indexCount = newIdxCount;
}
    
void C3DBatchMesh::add(const VertexColorCoord1* vertices, unsigned int vertexCount, const unsigned short* indices, unsigned int indexCount)
{
    //make sure use index
    unsigned int newVertexCount = _vertexCount + vertexCount;
    unsigned int newIndexCount = _indexCount + indexCount;
    unsigned int oldVertexCount = _vertexCount;
    
    while (newVertexCount > _vertexCapacity)
    {
        if (_growSize == 0)
            return;
        if (!resize(_capacity + _growSize))
            return;
    }
    
    if (newIndexCount > _indexCapacity) {
        
        if (!resizeIndex(std::max(newIndexCount, _indexCapacity + _indexCapacity) ) )
            return;
    }
    
    unsigned int vBytes = vertexCount * _vertexFormat->getVertexSize();
    memcpy(_verticesPtr, vertices, vBytes);
    
    _verticesPtr += vBytes;
    _vertexCount = newVertexCount;
    
    for (int i = 0; i < indexCount; i++) {
        *_indicesPtr = indices[i] + oldVertexCount;
        _indicesPtr++;
    }
    _indexCount = newIndexCount;
}
    
void C3DBatchMesh::begin()
{
    _vertexCount = 0;  
    _verticesPtr = _vertices;
    _indicesPtr = _indices;
    _indexCount = 0;
}

void C3DBatchMesh::end()
{
}   

}
