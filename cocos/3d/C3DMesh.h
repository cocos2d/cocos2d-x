#ifndef MESH_H_
#define MESH_H_

#include "Vector3.h"
#include "Base.h"
#include "EnumDef_GL.h"
#include "cocos2d.h"

namespace cocos2d
{

class C3DVertexFormat;
class MeshPart;
class C3DMaterial;
class C3DModel;
class C3DMorph;
class C3DAABB;

/**
 * Defines a mesh supporting various vertex formats and 1 or more
 * MeshPart(s) to define how the vertices are connected.
 */
class C3DMesh : public cocos2d::CCObject
{
    friend class C3DModel;
    friend class C3DResourceLoader;
    friend class Geo;

public:

    /**
    create mesh
    @param vertexFormat defines vertex format
    @param vertexCount vertex count
    @param dynamic dynamic increase the vertex number or not
    */
    static C3DMesh* createMesh(C3DVertexFormat* vertexFormat, unsigned int vertexCount, bool dynamic = false);
   
    const std::string& getUrl() const;


    const C3DVertexFormat* getVertexFormat() const;


    unsigned int getVertexCount() const;

    unsigned int getVertexSize() const;


    VertexBufferHandle getVertexBuffer() const;

    bool isDynamic() const;

    PrimitiveType getPrimitiveType() const;

    void setPrimitiveType(PrimitiveType type);

    void setVertexData(void* vertexData, unsigned int vertexStart = 0, unsigned int vertexCount = 0);
    void setVertexData(unsigned char* vertexData);


    void pushMorph(C3DMorph* morph,int morphTargetIndex,float weight);
    void popMorph(C3DMorph* morph,int morphTargetIndex);
    void changeMorph(C3DMorph* morph,int morphTargetIndex,float weight);
    void clearMorph(C3DMorph* morph);

    MeshPart* addPart(PrimitiveType primitiveType, IndexFormat indexFormat, unsigned int indexCount, bool dynamic = false);


    unsigned int getPartCount() const;

    MeshPart* getPart(unsigned int index);
    
    unsigned int getTriangleCount() const;

    virtual ~C3DMesh();

    C3DAABB* getBoundingBox() { return _boundingBox; };

private:
    C3DMesh(C3DVertexFormat* vertexFormat);
    void applyMorph(C3DMorph* morph);

private:    

    std::string _url;
    const C3DVertexFormat* _vertexFormat;
    unsigned int _vertexCount;
    VertexBufferHandle _vertexBuffer;
    PrimitiveType _primitiveType;
    unsigned int _partCount;
    MeshPart** _parts;
    bool _dynamic;

    unsigned char* _vertexData;    

    C3DAABB* _boundingBox;

};

}

#endif
