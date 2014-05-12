
#ifndef __CCMESH_H_
#define __CCMESH_H_

#include <string>
#include <vector>

#include "ccTypes.h"
#include "MeshPart.h"
#include "CCMath.h"

USING_NS_CC_MATH;

NS_CC_BEGIN

class MeshPart;

struct RenderMeshData
{
    int attrFlag;
    int vertexsize;
    std::vector<float> _vertexs;
    std::vector<std::vector<unsigned short> > _partindices;
    
    RenderMeshData(): attrFlag(0), vertexsize(0)
    {
        
    }
    
    bool initFrom(std::vector<float>& posions, std::vector<float>& normals, std::vector<float>& texs, const std::vector<std::vector<unsigned short> >& partindices);
    
    static std::vector<float>& generateNormals(std::vector<float>& posions, std::vector<float>& texs, const std::vector<std::vector<unsigned short> >& partindices);
    
    bool generateNormals();
};

namespace GL {
    enum
    {
         VERTEX_ATTRIB_FLAG_NORMAL = VERTEX_ATTRIB_FLAG_TEX_COORDS << 1,
    };
}


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
    
    //get attribute flag
    int getAttribFlag() const { return _renderdata.attrFlag; }
    
    bool generateNormals();


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