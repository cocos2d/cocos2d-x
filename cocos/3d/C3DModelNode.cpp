#include "Base.h"
#include "C3DModelNode.h"
#include "C3DModel.h"
#include "C3DMesh.h"
#include "MeshPart.h"
#include "C3DMeshSkin.h"
#include "C3DScene.h"
#include "C3DTechnique.h"
#include "C3DPass.h"
#include "C3DNode.h"
#include "C3DSkinModel.h"
#include "C3DMaterial.h"

#include "BonePart.h"
#include "C3DVertexDeclaration.h"

#include "MaterialParameter.h"

#include "C3DMaterialManager.h"

namespace cocos2d
{

C3DModelNode::C3DModelNode(const std::string& id)
    : C3DNode(id.c_str()), _model(nullptr)
{
    
}

C3DModelNode::~C3DModelNode()
{
    if (_model)
        _model->setNode(nullptr);
    SAFE_RELEASE(_model);
}

C3DModelNode* C3DModelNode::create(const std::string& id)
{
    return new C3DModelNode(id);
}



C3DNode::Type C3DModelNode::getType() const
{
    return C3DNode::NodeType_Model;
}

void C3DModelNode::setModel(C3DModel* model)
{
    if (_model != model)
    {
        if (_model)
        {
            _model->setNode(nullptr);
            SAFE_RELEASE(_model);
        }

        _model = model;

        if (_model)
        {
            _model->retain();
            _model->setNode(this);
        }
    }

}

C3DModel* C3DModelNode::getModel()
{
    return _model;
}

void C3DModelNode::draw()
{
    if (_model)
    {
        _model->draw();
    }
}

const Matrix& C3DModelNode::getWorldMatrix()
{
    if (_dirtyBits & NODE_DIRTY_WORLD)
    {
        // Clear our dirty flag immediately to prevent this block from being entered if our
        // parent calls our getWorldMatrix() method as a result of the following calculations.
        _dirtyBits &= ~NODE_DIRTY_WORLD;

        // If we have a parent, multiply our parent world transform by our local
        // transform to obtain our final resolved world transform.
        C3DNode* parent = getParent();
        if (parent)
        {

            if(parent->getType()==C3DNode::NodeType_SuperModel)
            {
                _world = getMatrix();
                
            }
            else
            {
                Matrix::multiply(parent->getWorldMatrix(), getMatrix(), &_world);
            }
            
        }
        else
        {
            _world = getMatrix();
        }

        // Our world matrix was just updated, so call getWorldMatrix() on all child nodes
        // to force their resolved world matrices to be updated.
        for(auto iter=_children.begin(); iter!=_children.end(); ++iter)       
        {
            (*iter)->getWorldMatrix();           
        }
    }

    return _world;
}

C3DNode* C3DModelNode::clone(CloneContext& context) const
{
    C3DModelNode* other = new C3DModelNode(_id.c_str());
    other->copyFrom(this, context);
    other->_id = _id;
    C3DModel* newModel = _model ? _model->clone(context) : nullptr;
    other->setModel(newModel);
    other->autorelease();
    return other;
}

}
