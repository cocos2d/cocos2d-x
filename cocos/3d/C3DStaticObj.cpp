#include "C3DStaticObj.h"
#include "Base.h"
#include "C3DResourceLoader.h"
#include "C3DMaterial.h"
#include "C3DModel.h"
#include "C3DNode.h"

#include "C3DMesh.h"
#include "C3DAABB.h"
#include "C3DMeshSkin.h"
#include "C3DSkinModel.h"
#include "C3DBone.h"
#include "C3DModelNode.h"
#include "StringTool.h"

NS_CC_BEGIN

C3DStaticObj* C3DStaticObj::create(const char* id)
{  

	C3DStaticObj* pRet = new C3DStaticObj(id);

	pRet->autorelease();
	return pRet;

}

C3DStaticObj::C3DStaticObj(const char* id):C3DRenderNode(id)
{

}


C3DStaticObj::~C3DStaticObj()
{
}
C3DNode::Type C3DStaticObj::getType() const
{
	return C3DNode::NodeType_SceneModel;
}


bool C3DStaticObj::loadFromFile(const char* fileName,bool isLoadAll)
{	
	// Load mesh/scene from file
	C3DResourceLoader* bundle = C3DResourceLoader::create(fileName);   	

	if (bundle == nullptr)
		return false;

	bundle->loadSceneModel(this);
	this->setDefaultMaterial(StringTool::getFilePath(fileName));
	SAFE_RELEASE(bundle);

	getAABB();


	return true;

}


void C3DStaticObj::calculateBoundingBox_()
{
	C3DAABB box;

	box._min.set(1000, 1000, 1000);
	box._max.set(-1000, -1000, -1000);

	for(std::vector<C3DNode*>::const_iterator iter=_children.begin(); iter!=_children.end(); ++iter)
	{
		C3DNode* node = *iter;
		if(node->getType()!=C3DNode::NodeType_Model )
			continue;
		C3DModel* model = static_cast<C3DModelNode*>(node)->getModel();

		if (model)
		{	
			C3DAABB worldSpaceBox(*model->getMesh()->getBoundingBox());       

			worldSpaceBox.transform(node->getWorldMatrix());            

			box.merge(worldSpaceBox);
		}	

	}	

	Matrix mat = getWorldMatrix();
	mat.invertOrthMat();
	box.transform(mat);
	if (!_bbOrigin)
		_bbOrigin = new C3DAABB();
	_bbOrigin->_min = box._min;
	_bbOrigin->_max = box._max;

	if (!_bb)
		_bb = new C3DAABB();
	_bb->_min = box._min;
	_bb->_max = box._max;
}

void C3DStaticObj::copyFrom(const Transform* other, C3DNode::CloneContext& context)
{
	const C3DStaticObj* otherNode = static_cast<const C3DStaticObj*>(other);
	C3DRenderNode::copyFrom(other, context);

}

C3DNode* C3DStaticObj::clone(C3DNode::CloneContext& context) const
{
	C3DStaticObj* other = new C3DStaticObj(_id.c_str());
	other->copyFrom(this, context);
	other->autorelease();
	return other;
}

NS_CC_END
