#include "C3DSkinlessModel.h"
#include "C3DMesh.h"
#include "MeshPart.h"
#include "C3DTechnique.h"
#include "C3DPass.h"
#include "C3DMaterial.h"


namespace cocos2d
{

C3DSkinlessModel::C3DSkinlessModel(C3DMesh* mesh) :C3DModel(mesh)   
{
    
}

C3DSkinlessModel::~C3DSkinlessModel()
{ 

}

C3DModel* C3DSkinlessModel::create(C3DMesh* mesh)
{   
    return new C3DSkinlessModel(mesh);
}

C3DModel* C3DSkinlessModel::clone(C3DNode::CloneContext& context) const
{
    C3DSkinlessModel* other = new C3DSkinlessModel(_mesh);
    other->copyFrom(this);
    other->autorelease();
    return other;
}

}
