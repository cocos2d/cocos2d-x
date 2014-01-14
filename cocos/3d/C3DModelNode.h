#ifndef C3DMODELNODE_H_
#define C3DMODELNODE_H_

#include "C3DNode.h"
#include "cocos2d.h"
namespace cocos2d
{

class C3DModel;
class C3DMaterial;
class C3DMesh;
class C3DLightFilter;
class C3DPass;
class C3DAnimation;

/**
 * Defines a node which contains a model.
 */
class C3DModelNode : public C3DNode
{

public:
    C3DNode::Type getType() const;

    static C3DModelNode* create(const std::string& id);
    
    C3DModel* getModel();

    void setModel(C3DModel* model);

    virtual void draw();

    virtual const Matrix& getWorldMatrix();

    C3DAnimation* getAnimation(const std::string& id = ""){return nullptr;};
    
    virtual C3DNode* clone(CloneContext& context) const;

protected:

    C3DModelNode(const std::string& id);

    virtual ~C3DModelNode();

public:

     /**
     * Pointer to the C3DModel attached to the C3DNode.
     */
    C3DModel* _model;
    
};

}

#endif
