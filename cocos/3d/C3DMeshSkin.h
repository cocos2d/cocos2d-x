#ifndef MESHSKIN_H_
#define MESHSKIN_H_

#include "CocosMath.h"
#include "Transform.h"
#include "C3DNode.h"

namespace cocos2d
{

class C3DResourceLoader;
class C3DModel;
class C3DBone;
class C3DNode;
class BonePart;

/**
 * Represents the skin for a mesh.
 */
class C3DMeshSkin : public C3DNode::Listener
{
    friend class C3DResourceLoader;
    friend class C3DSkinModel;
    friend class C3DBone;
    friend class C3DNode;


public:

     C3DMeshSkin();


    ~C3DMeshSkin();

    const Matrix& getBindShape();

    void setBindShape(const float* matrix);

    unsigned int getJointCount();

    C3DBone* getJoint(unsigned int index);

    C3DBone* getJoint(const char* id);

    C3DBone* getRootJoint() const;

    void setRootJoint(C3DBone* joint);

    int getJointIndex(C3DBone* joint);

    void setBonePartIndex(unsigned int index);
    unsigned int getBonePartIndex();

    Vector4* getMatrixPalette(unsigned int index);

    unsigned int getMatrixPaletteSize(unsigned index);

    C3DModel* getModel() const;

    void transformChanged(Transform* transform);

    BonePart* addPart(unsigned int batchID, unsigned int offsetVertexIndex, unsigned int numVertexIndex);
    
    void copyFrom(C3DMeshSkin* skin, C3DNode::CloneContext& context);

private:    

    void setJointCount(unsigned int jointCount);

    void setJoint(C3DBone* joint, unsigned int index);

    
    void clearJoints();

Matrix _bindShape;
    std::vector<C3DBone*> _joints;
    C3DBone* _rootJoint;
    


    // Pointer to the array of palette matrices.
    // This array is passed to the vertex shader as a uniform.
    // Each 4x3 row-wise matrix is represented as 3 Vector4's.
    // The number of Vector4's is (_joints.size() * 3).
    Vector4* _matrixPalette;
    C3DModel* _model;

    unsigned int _partCount;
    BonePart** _parts;
    unsigned int _curPartIndex;
};

}

#endif
