
#ifndef __CCMESH_H__
#define __CCMESH_H__

#include <string>
#include <vector>

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "CCMeshPart.h"
#include "math/CCMath.h"
#include "renderer/CCGLProgram.h"


USING_NS_CC_MATH;

NS_CC_BEGIN

class MeshPart;

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
    std::vector<std::vector<unsigned short> > _partindices;
    std::vector<MeshVertexAttrib> _vertexAttribs;
    
    RenderMeshData(): vertexsizeBytes(0)
    {
        
    }
    
    bool hasVertexAttrib(int attrib);
    
    bool initFrom(std::vector<float>& posions, std::vector<float>& normals, std::vector<float>& texs, const std::vector<std::vector<unsigned short> >& partindices);
    
    static std::vector<float>& generateNormals(std::vector<float>& posions, std::vector<float>& texs, const std::vector<std::vector<unsigned short> >& partindices);
    
    bool generateNormals();
};


class Mesh : public Ref
{
public:
    
    virtual ~Mesh();
    
    //create
    static Mesh* create(std::vector<float>& posions, std::vector<float>& normals, std::vector<float>& texs, const std::vector<std::vector<unsigned short> >& partindices);
    
    bool init(std::vector<float>& posions, std::vector<float>& normals, std::vector<float>& texs, const std::vector<std::vector<unsigned short> >& partindices);

    //get vertex buffer
    inline GLuint getVertexBuffer() const { return _vertexBuffer; }
    
    //get mesh part count
    inline ssize_t getMeshPartCount() const { return _partCount; }
    
    //get mesh part by index
    inline MeshPart* getMeshPart(int idx) { return _parts[idx]; }
    
    //build vertex buffer from renderdata
    void restore();
    
    //get mesh vertex attribute count
    int getMeshVertexAttribCount() const { return _renderdata._vertexAttribs.size(); }
    
    //get MeshVertexAttribute by index
    const MeshVertexAttrib& getMeshVertexAttribute(int idx) const { return _renderdata._vertexAttribs[idx]; }
    
    //has vertex attribute?
    bool hasVertexAttrib(int attrib) { return _renderdata.hasVertexAttrib(attrib); }
    
    //get per vertex size in bytes
    int getVertexSizeInBytes() const { return _renderdata.vertexsizeBytes; }

protected:
    Mesh();
    
    //build buffer
    void buildBuffer();


    void freeBuffers();
    
    void releaseMeshPart();
    
    void addMeshPart(PrimitiveType primitiveType, IndexFormat indexformat,  void* indexData, unsigned int indexCount);
    

protected:
    void countVertexData() const;
    std::string _name;

    GLuint _vertexBuffer;
    
    unsigned int _partCount;
    MeshPart** _parts;

private:
    
    RenderMeshData _renderdata;
};

NS_CC_END
#endif // __CCMESH_H_
