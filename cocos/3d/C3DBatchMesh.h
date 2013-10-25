#ifndef BATCHMESH_H_
#define BATCHMESH_H_


#include "EnumDef_GL.h"

namespace cocos3d
{


class C3DVertexFormat;
class BBVertex;
struct VertexColorCoord1;

/**
 * Defines a class for rendering multiple mesh into a single draw call.
 */
class C3DBatchMesh
{
friend class C3DBatchModel;
public:
	C3DBatchMesh(const C3DVertexFormat* vertexFormat, PrimitiveType primitiveType, bool bIndex = false, unsigned int initialCapacity = 1024, unsigned int growSize = 1024);
	  
    
    ~C3DBatchMesh();

    unsigned int getCapacity() const;

	unsigned int getIndexCapacity() const
	{
		return _indexCapacity;
	}

    void setCapacity(unsigned int capacity);
    
    void setIndexCapacity(unsigned int capacity);

  // adds a group of primitives to the batch.        
	void add(const BBVertex* vertices, unsigned int vertexCount);

	void add(const BBVertex* vertices, unsigned int vertexCount, const unsigned short* indices, unsigned int indexCount);
    
    void add(const VertexColorCoord1* vertices, unsigned int vertexCount, const unsigned short* indices, unsigned int indexCount);
	
    void begin();
    void end();
    void draw();

private:

    bool resize(unsigned int capacity);
    
    bool resizeIndex(unsigned int capacity);

    const C3DVertexFormat* _vertexFormat;
    PrimitiveType _primitiveType;    
    unsigned int _capacity; //the capacity of the primitive.
    unsigned int _growSize;//the value the batch grow when it overflows.
    unsigned int _vertexCapacity;//the  capacity of the vertex.
    unsigned int _vertexCount;//cur number of vertices   
    unsigned char* _vertices;//vertice array
    unsigned char* _verticesPtr;//cur vertice offset pointer
    
    bool _bUseIndex;
    unsigned int _indexCapacity;
    unsigned short* _indices;
    unsigned short* _indicesPtr;
    unsigned int _indexCount;
   
};

}

#endif
