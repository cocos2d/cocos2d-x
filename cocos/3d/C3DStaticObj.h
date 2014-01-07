#ifndef SCENEMODEL_H_
#define SCENEMODEL_H_

#include "C3DRenderNode.h"
using namespace std;

NS_CC_BEGIN

class C3DMaterial;
class C3DScene;
class C3DNode;
class MeshBatch;

/**
*Defines this static object of the scene,which can change material.
*/
class C3DStaticObj : public C3DRenderNode
{
    friend class C3DScene; 
public:

    static C3DStaticObj* create(const char* id); 

    virtual bool loadFromFile(const char* fileName,bool isLoadAll=false);

    C3DNode::Type getType() const;

    void calculateBoundingBox_();

    virtual void copyFrom(const Transform* other, C3DNode::CloneContext& context);
    virtual C3DNode* clone(CloneContext& context) const;

private:

    C3DStaticObj(const char* id);

    ~C3DStaticObj();
};

NS_CC_END

#endif // SCENEMODEL_H_
