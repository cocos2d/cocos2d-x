#ifndef NODELESSMODEL_H_
#define NODELESSMODEL_H_

#include "C3DModel.h"
#include "C3DNode.h"

namespace cocos2d
{
    
/**
 * Defines a model which doesn't have skin mesh.
 */
class C3DSkinlessModel : public C3DModel
{
public:

    C3DSkinlessModel(C3DMesh* mesh);

    ~C3DSkinlessModel();

    static C3DModel* create(C3DMesh* mesh);

    virtual C3DModel* clone(C3DNode::CloneContext& context) const;

};

}

#endif
