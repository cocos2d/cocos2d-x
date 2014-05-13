
#ifndef __CCMESHPART_H_
#define __CCMESHPART_H_


#include <string>
#include <vector>

#include "base/ccTypes.h"

NS_CC_BEGIN

class Mesh;
/**
 * Defines supported index formats.
 */
enum IndexFormat
{
    IndexFormat_INDEX8 = GL_UNSIGNED_BYTE,
    IndexFormat_INDEX16 = GL_UNSIGNED_SHORT,
};

/**
 * Defines supported primitive types.
 */
enum PrimitiveType
{
    PrimitiveType_TRIANGLES = GL_TRIANGLES,
    PrimitiveType_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    PrimitiveType_LINES = GL_LINES,
    PrimitiveType_LINE_STRIP = GL_LINE_STRIP,
    PrimitiveType_POINTS = GL_POINTS
};
/**
 * Defines a part of a mesh describing the way the
 * mesh's vertices are connected together.
 */
class MeshPart
{
    
public:
    ~MeshPart();
    
    unsigned int getMeshIndex() const;
    
    PrimitiveType getPrimitiveType() const;
    
    unsigned int getIndexCount() const;
    
    IndexFormat getIndexFormat() const;
    
    GLuint getIndexBuffer() const;
    
    static MeshPart* create(Mesh* mesh, unsigned int meshIndex, PrimitiveType primitiveType, IndexFormat indexformat,  void* indexData, unsigned int indexCount);
    
private:
    MeshPart();
    
    Mesh* _mesh;
    unsigned int _meshIndex;
    PrimitiveType _primitiveType;
    IndexFormat _indexFormat;
    unsigned int _indexCount;
    GLuint _indexBuffer;
};

NS_CC_END

#endif // __CCMESHPART_H_