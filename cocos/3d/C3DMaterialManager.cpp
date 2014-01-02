#include "Base.h"
#include "C3DMaterial.h"
#include "ElementNode.h"
#include "C3DMaterialManager.h"
#include "ElementNode.h"

NS_CC_BEGIN

static C3DMaterialManager* __materialManagerInstance = nullptr;

C3DMaterialManager::C3DMaterialManager() 
{
}

C3DMaterialManager::~C3DMaterialManager()
{
	__materialManagerInstance = nullptr;

}

C3DMaterialManager* C3DMaterialManager::getInstance()
{	   
	if (!__materialManagerInstance)
	{
		__materialManagerInstance = new C3DMaterialManager();
		__materialManagerInstance->autorelease();
	}
	return __materialManagerInstance;

}


C3DResource* C3DMaterialManager::createResource(const std::string& name)
{
	// Load the material properties from file
	ElementNode* nodes = ElementNode::create(name.c_str());
	assert(nodes);
	if (nodes == nullptr)
	{
		return nullptr;
	}   

	ElementNode* materialNodes = (strlen(nodes->getNodeType()) > 0) ? nodes : nodes->getNextChild();
	assert(materialNodes);
	if (!materialNodes || !(strcmp(materialNodes->getNodeType(), "material") == 0))
	{
		return nullptr;
	}

	C3DMaterial* material = new C3DMaterial(name);

	material->autorelease();

	if(material->load(materialNodes) == true)
	{
		this->setResourceState(material,C3DResource::State_Used);
	}
	else
	{
		SAFE_RELEASE(material);
		SAFE_DELETE(nodes);
		return nullptr;
	}

	SAFE_DELETE(nodes);

	return material;
}


C3DResource* C3DMaterialManager::cloneResource(C3DResource* resource)
{
	if(resource != nullptr)
	{
		C3DResource* newResource = resource->clone();

		this->setResourceState(newResource,C3DResource::State_Used);
		return newResource;		
	}
}

NS_CC_END
