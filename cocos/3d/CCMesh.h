
#ifndef __CCMESH_H__
#define __CCMESH_H__

#include <string>
#include <vector>

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "math/CCMath.h"
#include "renderer/CCGLProgram.h"


USING_NS_CC_MATH;

NS_CC_BEGIN

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

//mesh vertex attribute
struct MeshVertexAttrib
{
    //attribute size
    GLint size;
    //GL_FLOAT
    GLenum type;
    
    //VERTEX_ATTRIB_POSITION,VERTEX_ATTRIB_COLOR,VERTEX_ATTRIB_TEX_COORD,VERTEX_ATTRIB_NORMAL, GLProgram for detail
    int  vertexAttrib;
    
    //size in bytes
    int attribSizeBytes;
};

class RenderMeshData
{
public:
    int vertexsizeBytes;
    int vertexNum;
    std::vector<float> _vertexs;
    std::vector<unsigned short> _indices;
    std::vector<MeshVertexAttrib> _vertexAttribs;
    
    RenderMeshData(): vertexsizeBytes(0)
    {
        
    }
    
    bool hasVertexAttrib(int attrib);
    
    bool initFrom(std::vector<float>& posions, std::vector<float>& normals, std::vector<float>& texs, const std::vector<unsigned short>& indices);
};


class Mesh : public Ref
{
public:
    
    virtual ~Mesh();
    
    //create
    static Mesh* create(std::vector<float>& posions, std::vector<float>& normals, std::vector<float>& texs, const std::vector<unsigned short>& indices);
    
    bool init(std::vector<float>& posions, std::vector<float>& normals, std::vector<float>& texs, const std::vector<unsigned short>& indices);

    //get vertex buffer
    inline GLuint getVertexBuffer() const { return _vertexBuffer; }
    
    //get mesh vertex attribute count
    int getMeshVertexAttribCount() const { return _renderdata._vertexAttribs.size(); }
    
    //get MeshVertexAttribute by index
    const MeshVertexAttrib& getMeshVertexAttribute(int idx) const { return _renderdata._vertexAttribs[idx]; }
    
    //has vertex attribute?
    bool hasVertexAttrib(int attrib) { return _renderdata.hasVertexAttrib(attrib); }
    
    //get per vertex size in bytes
    int getVertexSizeInBytes() const { return _renderdata.vertexsizeBytes; }
    
    PrimitiveType getPrimitiveType() const { return _primitiveType; }
    
    unsigned int getIndexCount() const { return _indexCount; }
    
    IndexFormat getIndexFormat() const { return _indexFormat; }
    
    GLuint getIndexBuffer() const {return _indexBuffer; }
    
    //build vertex buffer from renderdata
    void restore();
protected:
    Mesh();

    //build buffer
    void buildBuffer();

    void cleanAndFreeBuffers();
    
    //void releaseMeshPart();
    
    //void addMeshPart(PrimitiveType primitiveType, IndexFormat indexformat,  void* indexData, unsigned int indexCount);
    
protected:
    void countVertexData() const;
    std::string _name;

    GLuint _vertexBuffer;
    
    PrimitiveType _primitiveType;
    IndexFormat _indexFormat;
    unsigned int _indexCount;
    GLuint _indexBuffer;
    
private:
    
    RenderMeshData _renderdata;
};

NS_CC_END
#endif // __CCMESH_H_
