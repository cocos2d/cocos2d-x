#ifndef C3DMODELNODE_H_
#define C3DMODELNODE_H_

#include "C3DNode.h"
#include "cocos2d.h"
namespace cocos3d
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
	static C3DModelNode* create(const char* id);
	
    C3DModel* getModel();
    void setModel(C3DModel* model);

	virtual void draw();

	virtual const C3DMatrix& getWorldMatrix();
	C3DAnimation* getAnimation(const char* id = NULL){return NULL;};
	
	virtual C3DNode* clone(CloneContext& context) const;

protected:

    C3DModelNode(const char* id);

    virtual ~C3DModelNode();

public:

	 /**
     * Pointer to the C3DModel attached to the C3DNode.
     */
    C3DModel* _model;
	
};

}

#endif
