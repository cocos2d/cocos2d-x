#ifndef MESHPART_H_
#define MESHPART_H_
#include "EnumDef_GL.h"


namespace cocos2d
{
class C3DMesh;

/**
 * Defines a part of a mesh describing the way the
 * mesh's vertices are connected together.
 */
class MeshPart
{
    friend class C3DMesh;
    friend class C3DModel;
    friend class C3DSkinModel;
    friend class C3DSkinlessModel;
    friend class BoardModel;

public:

    ~MeshPart();

    unsigned int getMeshIndex() const;

    PrimitiveType getPrimitiveType() const;

    unsigned int getIndexCount() const;
    
    inline unsigned int getTriangleCount() const
    {
        if (_primitiveType == PrimitiveType_TRIANGLES)
            return _indexCount / 3;
        
        if (_primitiveType == PrimitiveType_TRIANGLE_STRIP)
            return _indexCount - 2;
        
        return 0;
    }

 
   IndexFormat getIndexFormat() const;


    IndexBufferHandle getIndexBuffer() const;

    //Determines if the indices are dynamic.
    bool isDynamic() const;

    void setIndexData(void* indexData, unsigned int indexStart, unsigned int indexCount);

private:


    MeshPart();

    static MeshPart* create(C3DMesh* mesh, unsigned int meshIndex, PrimitiveType primitiveType, IndexFormat indexFormat, unsigned int indexCount, bool dynamic = false);

    C3DMesh* _mesh;
    unsigned int _meshIndex;
    PrimitiveType _primitiveType;
    IndexFormat _indexFormat;
    unsigned int _indexCount;
    IndexBufferHandle _indexBuffer;
    bool _dynamic;
};

}

#endif
