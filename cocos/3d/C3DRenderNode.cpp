#include "C3DRenderNode.h"
#include "C3DModel.h"
#include "C3DModelNode.h"
#include "C3DNode.h"
#include "C3DAABB.h"
#include "Vertex.h"
#include "C3DMaterial.h"
#include "C3DMesh.h"
#include "C3DMeshSkin.h"
#include "C3DSkinModel.h"
#include "C3DBone.h"
#include "Vector3.h"
#include "C3DScene.h"
#include "C3DTechnique.h"
#include "C3DRay.h"
#include "ElementNode.h"
#include "C3DModel.h"
#include "AttachNode.h"
#include "C3DScene.h"
#include "C3DCamera.h"
#include "C3DResourceLoader.h"
#include "C3DSprite.h"
#include "C3DStaticObj.h"

NS_CC_BEGIN

C3DRenderNode::C3DRenderNode(const char* id)
:C3DNode(id)
{
    _scene = nullptr;        

    _showSkeleton = false;
    _showCollitionBox = false;

}


C3DRenderNode::~C3DRenderNode()
{
    _scene = nullptr;    

    if (_attachNodes.size() > 0)
    {        
        std::vector<AttachNode*>::iterator iter = _attachNodes.begin();        
        while (iter != _attachNodes.end())
        {
            AttachNode* an = *iter;
            SAFE_DELETE(an);
            ++iter;
        }
        _attachNodes.clear();
    }

}

C3DRenderNode* C3DRenderNode::create(const char* id,const char* fileName)
{    
    // Load mesh/scene from file
    C3DResourceLoader* loader = C3DResourceLoader::create(fileName);       

    if (loader == nullptr)
        return false;    
    C3DRenderNode* renderNode = nullptr;
    if(loader->_isSkin == true)
    {
        renderNode = C3DSprite::create(id);
    }
    else
    {
        renderNode = C3DStaticObj::create(id);
    }

    renderNode->_fileName = fileName;
    //renderNode->_loader = loader;

    return renderNode;
}


void C3DRenderNode::draw()
{
    if(_active == false)
        return;                    

    getAABB();
    //if (_scene->getActiveCamera()->isVisible(*_bb))
    {
        for(std::vector<C3DNode*>::const_iterator iter=_children.begin(); iter!=_children.end(); ++iter)
        {
            C3DNode* node = *iter;

            if (node->getType() != C3DNode::NodeType_Model)
                continue;


            node->draw();        
        }    
    }

    std::vector<AttachNode*>::iterator nit;
    for (nit = _attachNodes.begin(); nit != _attachNodes.end(); nit++)
    {        
        (*nit)->draw();            
    }

}

/**
* Update routine
*/
void C3DRenderNode::update(long elapsedTime)
{
    //C3DNode::update(deltatime);

    if(_attachNodes.size()>0)
    {        
        for (std::vector<AttachNode*>::iterator nit = _attachNodes.begin(); nit != _attachNodes.end(); nit++)
        {        
            (*nit)->update(elapsedTime);            
        }
    }

}

AttachNode * C3DRenderNode::accessNode( C3DNode* pNode)
{    
    std::vector<AttachNode*>::iterator nit;
    for (nit = _attachNodes.begin(); nit != _attachNodes.end(); nit++)
    {        
        if ( (*nit)->node() == pNode ) 
            break;
    }
    if (nit == _attachNodes.end())
    {
        _attachNodes.push_back( new AttachNode( pNode, this ) );
        nit = _attachNodes.end() - 1;
    }
    return *nit;
}

AttachNode * C3DRenderNode::attachNode( const std::string & nodeName )
{

    C3DNode* pNode;

    if (nodeName.empty())
    {                    
        return nullptr;        
    }
    else
    {
        pNode = findNode( nodeName.c_str() );
        if (!pNode)
        {            
            return nullptr;
        }
    }

    AttachNode * pAttachNode = this->accessNode( pNode );

    return pAttachNode;
}


void C3DRenderNode::attach(const char* nodeName,C3DNode* attachment)
{    
    AttachNode* attachNode = this->attachNode(nodeName);
    if(attachNode==nullptr)
        return;

    attachNode->attach(attachment);
}

void C3DRenderNode::detach(const char* nodeName,C3DNode* attachment)
{
    AttachNode* attachNode = this->attachNode(nodeName);
    if(attachNode==nullptr)
        return;

    attachNode->detach(attachment);
}

void C3DRenderNode::transformChanged()
{
    C3DNode::transformChanged();   
}

void C3DRenderNode::copyFrom(const Transform* other, C3DNode::CloneContext& context)
{
    const C3DRenderNode* otherNode = static_cast<const C3DRenderNode*>(other);

    C3DNode::copyFrom(other, context);    
    _showSkeleton = otherNode->_showSkeleton;

    if (otherNode->_attachNodes.size())
    {
        for (size_t i = 0; i < otherNode->_attachNodes.size(); i++) {
            C3DNode* node = context.cloneMap[otherNode->_attachNodes[i]->_node];
            C3DNode* owner = context.cloneMap[otherNode->_attachNodes[i]->_owner];
            CCAssert(node == nullptr || owner == nullptr, "attachment node or owner null");
            if (node == nullptr || owner == nullptr)
                return;
            AttachNode* attach = new AttachNode(node, owner);
            _attachNodes.push_back(attach);
        }
    }
}

C3DMaterial* C3DRenderNode::getMaterial(const std::string& meshName)
{
    C3DNode* node = findNode(meshName.c_str());
    if(node == nullptr)
        return nullptr;

    if (node->getType() != C3DNode::NodeType_Model)
        return nullptr;

    return static_cast<C3DModelNode*>(node)->getModel()->getMaterial();        
}

void C3DRenderNode::getAllModel(std::list<C3DNode*>& models)
{        
    models.clear();
    for(std::vector<C3DNode*>::const_iterator iter=_children.begin(); iter!=_children.end(); ++iter)
    {
        C3DNode* node = *iter;

        if (node->getType() != C3DNode::NodeType_Model)
            continue;
        models.push_back(node);
    }
}

void C3DRenderNode::setMaterial(const std::string& modelName, const std::string& matName)
{

    C3DNode* node = findNode(modelName.c_str());
    if (node == nullptr)
        return;

    if (node->getType() != C3DNode::NodeType_Model)
        return;    

    static_cast<C3DModelNode*>(node)->getModel()->setMaterial(matName.c_str());        
}

void C3DRenderNode::setMaterial(const std::string& matName)
{
    for (std::vector<C3DNode*>::const_iterator iter = _children.begin(); iter!=_children.end(); ++iter)
    {
        C3DNode* node = *iter;

        if(node->getType()!=C3DNode::NodeType_Model )
            continue;
        static_cast<C3DModelNode*>(node)->getModel()->setMaterial(matName.c_str());        
    }
}

void C3DRenderNode::setDefaultMaterial(const std::string& path)
{
    for (std::vector<C3DNode*>::const_iterator iter = _children.begin(); iter!=_children.end(); ++iter)
    {
        C3DNode* node = *iter;

        if(node->getType()!=C3DNode::NodeType_Model )
            continue;
        static_cast<C3DModelNode*>(node)->getModel()->setDefaultMaterial(path);        
    }
}

void C3DRenderNode::removeMaterial(const std::string& modelName, const std::string& matName)
{
    C3DNode* node = findNode(modelName.c_str());
    if (node == nullptr)
        return;

    if (node->getType() != C3DNode::NodeType_Model)
        return;    

    static_cast<C3DModelNode*>(node)->getModel()->removeMaterial();
}

void C3DRenderNode::removeMaterial(const std::string& matName)
{
    for (std::vector<C3DNode*>::const_iterator iter = _children.begin(); iter!=_children.end(); ++iter)
    {
        C3DNode* node = *iter;

        if(node->getType()!=C3DNode::NodeType_Model )
            continue;
        static_cast<C3DModelNode*>(node)->getModel()->removeMaterial();        
    }
}

unsigned int C3DRenderNode::getTriangleCount() const
{
    int nTriangle = 0;

    for(std::vector<C3DNode*>::const_iterator iter=_children.begin(); iter!=_children.end(); ++iter)
    {
        C3DNode* node = *iter;

        if(node->getType()!=C3DNode::NodeType_Model )
            continue;

        C3DMesh* mesh = ((C3DModelNode*)node)->getModel()->getMesh();
        nTriangle += mesh->getTriangleCount();
    }
    return nTriangle;
}

NS_CC_END
