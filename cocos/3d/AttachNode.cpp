#include "AttachNode.h"
#include "C3DNode.h"
#include "C3DLayer.h"
#include "C3DScene.h"

NS_CC_BEGIN

AttachNode::AttachNode( C3DNode* pNode, C3DNode* pOwner )
{
    _node = pNode;
    _owner = pOwner;    
}


AttachNode::~AttachNode()
{
    _node = nullptr;
    _owner = nullptr;
}

void AttachNode::attach( C3DNode* pAttachment )
{
    pAttachment->scale(1.0f/_owner->getScaleX(),1.0f/_owner->getScaleY(),1.0f/_owner->getScaleZ());
    _node->addChild(pAttachment);
    _owner->getScene()->removeChild(pAttachment);
    _attachments.push_back(pAttachment);
}

bool AttachNode::detach( C3DNode* pAttachment )
{
    std::vector<C3DNode*>::iterator nit;
    for (nit = _attachments.begin(); nit != _attachments.end(); nit++)
    {        
        if ( *nit == pAttachment ) 
        {
            pAttachment->scale(_owner->getScaleX(),_owner->getScaleY(),_owner->getScaleZ());
            _owner->getScene()->addChild(pAttachment);
            _attachments.erase(nit);
            return true;
        }            
    }    

    return false;
}

void AttachNode::update(long elapsedTime)
{
    std::vector<C3DNode*>::iterator nit;
    for (nit = _attachments.begin(); nit != _attachments.end(); nit++)
    {
        (*nit)->update(elapsedTime);
    }    
}

void AttachNode::draw()
{
    std::vector<C3DNode*>::iterator nit;
    for (nit = _attachments.begin(); nit != _attachments.end(); nit++)
    {        
        (*nit)->draw();
    }
}

NS_CC_END
