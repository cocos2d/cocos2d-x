#include "Base.h"
#include "C3DSkeleton.h"
#include "C3DBone.h"
#include "Vertex.h"
#include "C3DGeoWireRender.h"

namespace cocos3d
{

C3DSkeleton::C3DSkeleton()
{
	_rootBone = NULL;
}


C3DSkeleton::~C3DSkeleton()
{

	//SAFE_RELEASE(_activeC3DCameraNode);

	//
	//removeAllCompoundModels();
	//
	//SAFE_DELETE(_ambientColor);

	//SAFE_DELETE(_batchModel);
}

void C3DSkeleton::getChild(std::map<std::string, C3DBone*>& bones,C3DNode* node)
{
	if(node->getType() == C3DNode::NodeType_Bone)
	{
		bones[node->getId()] = static_cast<C3DBone*>(node);
	}
	

	for(std::vector<C3DNode*>::const_iterator iter=node->_children.begin(); iter!=node->_children.end(); ++iter)
	{		
		getChild(bones,*iter);			
	   
	}

}

C3DBone* C3DSkeleton::getBone(const std::string& name) const
{
	std::map<std::string, C3DBone*>::const_iterator iter = _bones.find(name);
	if (iter == _bones.end())
		return NULL;
	return iter->second;
}

void C3DSkeleton::drawSkeleton(C3DGeoWireRender *render, C3DBone* root)
{
	C3DBone* tpParentBone = root;
	C3DMatrix matParent = tpParentBone->getWorldMatrix();
	C3DVector3 vParentPos;
	matParent.getPosition(&vParentPos);

	for(std::vector<C3DNode*>::const_iterator iter=root->_children.begin(); iter!=root->_children.end(); ++iter)
	{	
		C3DBone* tpChildBone = static_cast<C3DBone*>(*iter);
		C3DMatrix matChild = tpChildBone->getWorldMatrix();
		C3DVector3 vChildPos;
		matChild.getPosition(&vChildPos);

		if (tpChildBone->getSelect())
		{
			render->add3DLine(vParentPos, vChildPos, C3DVector4(1,0,0,1));
		}
		else
		{
			render->add3DLine(vParentPos, vChildPos, C3DVector4(1,1,0,1));
		}

		drawSkeleton(render, (C3DBone*)(*iter));
	}
}

void C3DSkeleton::set(C3DBone* joint)
{
	if(joint == NULL)
		return;
	_rootBone = joint;

	getChild(_bones,_rootBone);
}

C3DAnimation* C3DSkeleton::getAnimation(const std::string& name) const
{
	return _rootBone->getAnimation(name.c_str());

}

C3DSkeleton* C3DSkeleton::clone()
{
	return NULL;
}




















}
