#include "C3DRenderNode.h"
#include "C3DModel.h"
#include "C3DModelNode.h"
#include "C3DNode.h"
#include "C3DBatchMesh.h"
#include "C3DAABB.h"
#include "Vertex.h"
#include "C3DMaterial.h"
#include "C3DRenderChannel.h"
#include "C3DMesh.h"
#include "C3DMeshSkin.h"
#include "C3DSkinModel.h"
#include "C3DBone.h"
#include "C3DVector3.h"
#include "C3DScene.h"
#include "C3DTechnique.h"
#include "C3DRay.h"
#include "C3DElementNode.h"
#include "C3DCollitionBox.h"

#include "C3DModel.h"
#include "AttachNode.h"
#include "C3DParticleSystem.h"
#include "C3DScene.h"
#include "C3DCamera.h"
#include "C3DGeoWireRender.h"

#include "C3DResourceLoader.h"

#include "C3DSprite.h"
#include "C3DStaticObj.h"

namespace cocos3d
{
    
enum
{
    NO_CHANGE = 0,
    CompoundModel_Change_BoundingBox = 1,
    CompoundModel_Change_OBB = 2,
    BoundingBox_OBB_Change = CompoundModel_Change_BoundingBox | CompoundModel_Change_OBB,
};

C3DRenderNode::C3DRenderNode(const char* id):C3DNode(id)
{
	_scene = NULL;		

	_changeFlag = BoundingBox_OBB_Change;//CompoundModel_Change_BoundingBox;
	
	_showAABB = false;
    _showOBB = false;

	_bb = NULL;
    _bbOrigin = NULL;

    _obb.clear();

	_showSkeleton = false;
	_showColitionBox = false;

	_loader = NULL;
}


C3DRenderNode::~C3DRenderNode()
{
	_scene = NULL;	
	
    SAFE_DELETE(_bb);
    SAFE_DELETE(_bbOrigin);

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

	std::vector<C3DCollitionBox*>::iterator iter = m_colitionBoxs.begin();
	for ( ; iter != m_colitionBoxs.end(); iter++ )
	{
		SAFE_DELETE((*iter));
	}
	m_colitionBoxs.clear();
}



C3DRenderNode* C3DRenderNode::create(const char* id,const char* fileName)
{	
	// Load mesh/scene from file
	C3DResourceLoader* loader = C3DResourceLoader::create(fileName);   	
			
	if (loader == NULL)
        return false;	
	C3DRenderNode* renderNode = NULL;
	if(loader->_isSkin == true)
	{
		renderNode = C3DSprite::create(id);
	}
	else
	{
		renderNode = C3DStaticObj::create(id);
	}

	renderNode->_fileName = fileName;
	renderNode->_loader = loader;

	return renderNode;
}


void C3DRenderNode::draw()
{
	if(_active == false)
		return;					

	getAABB();
	if (_scene->getActiveCamera()->isVisible(*_bb))
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


	// update CollitionBox
	std::vector<C3DCollitionBox*>::iterator iter = m_colitionBoxs.begin();
	for ( ; iter != m_colitionBoxs.end(); iter++)
	{
		(*iter)->update();
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
		return NULL;		
	}
	else
	{
		pNode = findNode( nodeName.c_str() );
		if (!pNode)
		{			
			return NULL;
		}
	}
		
	AttachNode * pAttachNode = this->accessNode( pNode );
	
	
	return pAttachNode;
}


void C3DRenderNode::attach(const char* nodeName,C3DNode* attachment)
{	
	AttachNode* attachNode = this->attachNode(nodeName);
	if(attachNode==NULL)
		return;

	attachNode->attach(attachment);
}

void C3DRenderNode::detach(const char* nodeName,C3DNode* attachment)
{
	AttachNode* attachNode = this->attachNode(nodeName);
	if(attachNode==NULL)
		return;

	attachNode->detach(attachment);
}

void C3DRenderNode::drawAABB()
{
	if(_active == false)
		return; 

	if(this->getAABB() == NULL)
	{		
		return;
	}	
    
	_scene->getGeoWireRender()->addBoundingBox(_bb, C3DVector4(1.0f, 0.0f, 0.0f, 1.0f));
}
    
void C3DRenderNode::drawOBB()
{
	if(_active == false)
		return; 

    if (_obb.extents.isZero())
        return;
    
    getOBB();

	_scene->getGeoWireRender()->addOBB(&_obb, C3DVector4(1.0f, 0.0f, 0.0f, 1.0f));
}

void C3DRenderNode::drawColitionBox()
{
	if(_active == false)
		return; 

	std::vector<C3DCollitionBox*>::iterator iter = m_colitionBoxs.begin();
	for ( ; iter != m_colitionBoxs.end(); iter++)
	{
		C3DCollitionBox* bb = *iter;

		_scene->getGeoWireRender()->addCollitionBox(bb, C3DVector4(1,1,0,1));
	}
}

void C3DRenderNode::drawDebug()
{
	if (_showAABB)
		drawAABB();
	if (_showOBB)
		drawOBB();
	if (_showColitionBox)
		drawColitionBox();
}

void C3DRenderNode::transformChanged()
{
	C3DNode::transformChanged();
    
	_changeFlag = BoundingBox_OBB_Change;//CompoundModel_Change_BoundingBox;
	
}

    
void C3DRenderNode::calculateBoundingBox()
{
	if (_bb == NULL)
	{
		calculateBoundingBox_();
	}
	else
	{
		_bb->_min = _bbOrigin->_min;
		_bb->_max = _bbOrigin->_max;
		
		
	}
	_bb->transform(getWorldMatrix());
}

void C3DRenderNode::calculateOrientedBoundingBox()
{
    if (_bb && _obb.extents.isZero())
    {
        calculateOrientedBoundingBox_();
    }
    else if (!_obbOrigin.extents.isZero())
    {
        _obb = _obbOrigin;
		C3DMatrix worldmat = getWorldMatrix(); 
				
		
        _obb.transform(worldmat);

		worldmat.transformPoint(_bbOrigin->getCenter(), &_obb.center);
		_obb.completeExtAxis();
    }
}

void C3DRenderNode::calculateOrientedBoundingBox_()
{
	// build from aabb
	_obb.build(*_bb);
	_obbOrigin = _obb;
	C3DMatrix mat = getWorldMatrix();
	mat.invertOrthMat();
	_obbOrigin.transform(mat);
}

void C3DRenderNode::reCalculateBoundingBox()
{
	calculateBoundingBox_();
	_bb->transform(getWorldMatrix());
}

void C3DRenderNode::reCalculateOrientedBoundingBox()
{
	calculateBoundingBox_();
	calculateOrientedBoundingBox_();
	_obb = _obbOrigin;
	_obb.transform(getWorldMatrix());
}

C3DAABB* C3DRenderNode::getAABB()
{
	if (_changeFlag & CompoundModel_Change_BoundingBox)
    {
		_changeFlag &= ~CompoundModel_Change_BoundingBox;

		calculateBoundingBox();     
	 }  

     return _bb;
}

void C3DRenderNode::showAABB(bool show)
{
    _showAABB = show;
}

bool C3DRenderNode::showAABB()
{
    return _showAABB;
}

void C3DRenderNode::showOBB(bool show)
{
    _showOBB = show;
}
bool C3DRenderNode::showOBB()
{
    return _showOBB;
}


C3DOBB* C3DRenderNode::getOBB()
{
    if (_changeFlag & CompoundModel_Change_OBB)
    {
        _changeFlag &= ~CompoundModel_Change_OBB;
            
        calculateOrientedBoundingBox();
    }
    return &_obb;
}

void C3DRenderNode::showColitionBox(bool show)
{
	 _showColitionBox = show;
}

bool C3DRenderNode::showColitionBox()
{
	return _showColitionBox;
}

void C3DRenderNode::copyFrom(const C3DTransform* other, C3DNode::CloneContext& context)
{
	const C3DRenderNode* otherNode = static_cast<const C3DRenderNode*>(other);

	C3DNode::copyFrom(other, context);
	_changeFlag = otherNode->_changeFlag;
	_showAABB = otherNode->_showAABB;
	_showOBB = otherNode->_showOBB;
	_showSkeleton = otherNode->_showSkeleton;
	_obb = otherNode->_obb;
	_obbOrigin = otherNode->_obbOrigin;

	if (otherNode->_bbOrigin)
	{
		if (!_bbOrigin)
			_bbOrigin = new C3DAABB();
		_bbOrigin->_min = otherNode->_bbOrigin->_min;
		_bbOrigin->_max = otherNode->_bbOrigin->_max;
	}

	if (otherNode->_bb)
	{
		if (!_bb)
			_bb = new C3DAABB();
		_bb->_min = otherNode->_bb->_min;
		_bb->_max = otherNode->_bb->_max;
	}

	if (otherNode->_attachNodes.size())
    {
        for (size_t i = 0; i < otherNode->_attachNodes.size(); i++) {
            C3DNode* node = context.cloneMap[otherNode->_attachNodes[i]->_node];
            C3DNode* owner = context.cloneMap[otherNode->_attachNodes[i]->_owner];
            CCAssert(node == NULL || owner == NULL, "attachment node or owner null");
            if (node == NULL || owner == NULL)
                return;
            AttachNode* attach = new AttachNode(node, owner);
            _attachNodes.push_back(attach);
        }
    }
}

C3DMaterial* C3DRenderNode::getMaterial(const std::string& meshName)
{
	C3DNode* node = findNode(meshName.c_str());
	if(node == NULL)
		return NULL;

	if (node->getType() != C3DNode::NodeType_Model)
		return NULL;

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
	if (node == NULL)
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
	if (node == NULL)
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

unsigned int C3DRenderNode::addColitionBox(const std::string& strBone, const C3DVector3& offset, float fRadius)
{
	m_colitionBoxs.push_back((new cocos3d::C3DCollitionBox(this, strBone, offset, fRadius)));
	return m_colitionBoxs.size();
}

void C3DRenderNode::removeColitionBox(C3DCollitionBox* bb)
{
	std::vector<C3DCollitionBox*>::iterator iter = m_colitionBoxs.begin();
	for ( ; iter != m_colitionBoxs.end(); iter++)
	{
		if ((*iter) == bb)
		{
			SAFE_DELETE((*iter));
			m_colitionBoxs.erase(iter);
			break;
		}
	}
}

const std::vector<C3DCollitionBox*>& C3DRenderNode::getColitionBoxs()const
{
	return m_colitionBoxs;
}

C3DCollitionBox* C3DRenderNode::pickColitionBox(const C3DRay *ray)
{
	std::vector<C3DCollitionBox*>::iterator iter = m_colitionBoxs.begin();
	for ( ; iter != m_colitionBoxs.end(); iter++)
	{
		C3DAABB* tmp = new C3DAABB((*iter)->getMin(), (*iter)->getMax());
		if (ray->intersects(tmp))
		{
			SAFE_DELETE(tmp);
			return *iter;
		}
		SAFE_DELETE(tmp);
	}
	return NULL;
}

bool C3DRenderNode::saveColitionBox(const std::string& fileName)const
{
	cocos3d::C3DElementNode* tpBoxListNode = C3DElementNode::createEmptyNode("", "colitionbox");
	if (!tpBoxListNode)
		return false;

	unsigned int index = 0;
	std::vector<C3DCollitionBox*>::const_iterator iter = m_colitionBoxs.begin();
	for ( ; iter != m_colitionBoxs.end(); ++iter, ++index)
	{
		StringTool::toString(index);
		cocos3d::C3DElementNode* tpNodeTechnique = cocos3d::C3DElementNode::createEmptyNode(StringTool::toString(index).c_str(), "box");
		C3DVector3 localPos = (*iter)->getLocalPos();
		tpNodeTechnique->setElement("center", &localPos);
		float radius = (*iter)->getRadius();
		tpNodeTechnique->setElement("radius", &radius);
		std::string strBone = (*iter)->getBone();
		tpNodeTechnique->setElement("bone", &strBone);

		tpBoxListNode->addChildNode(tpNodeTechnique);
	}
	
	tpBoxListNode->writeToFile(fileName.c_str());
	SAFE_DELETE(tpBoxListNode);
	return true;
}

bool C3DRenderNode::loadColitionBox(const std::string& fileName)
{
	m_colitionBoxs.clear();
	cocos3d::C3DElementNode* tpBoxListNode = C3DElementNode::create(fileName.c_str());
	if (!tpBoxListNode)
		return true;

	tpBoxListNode = tpBoxListNode->getNextChild();
	if (!tpBoxListNode || !(strcmp(tpBoxListNode->getNodeType(), "colitionbox") == 0))
		return false;

	cocos3d::C3DElementNode* tpNode = NULL;
	while ((tpNode = tpBoxListNode->getNextChild()))
	{
		if (tpNode)
		{
			C3DVector3 center;
			tpNode->getElement("center", &center);

			float radius;
			tpNode->getElement("radius", &radius);

			std::string strBoneName = tpNode->getElement("bone");
			
			addColitionBox(std::string(strBoneName), center, radius);
		}
	}
	SAFE_DELETE(tpBoxListNode);
	return true;
}

}
