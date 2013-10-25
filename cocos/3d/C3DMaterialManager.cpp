#include "Base.h"
#include "C3DMaterial.h"
#include "C3DElementNode.h"
#include "C3DMaterialManager.h"
#include "C3DElementNode.h"

namespace cocos3d
{
static C3DMaterialManager* __materialManagerInstance = NULL;

C3DMaterialManager::C3DMaterialManager() 
{
}

C3DMaterialManager::~C3DMaterialManager()
{
	__materialManagerInstance = NULL;
    
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


C3DResource* C3DMaterialManager::createResource(const std::string& name,C3DElementNode* node)
{
	C3DResource* material = new C3DMaterial(name);

	material->autorelease();		

	if(material->load(node) == true)
	{	
		this->setResourceState(material,C3DResource::State_Used);
	}
	material->retain();
		
	return material;
}

C3DResource* C3DMaterialManager::createResource(const std::string& name)
{
    // Load the material properties from file
	C3DElementNode* nodes = C3DElementNode::create(name.c_str());
    assert(nodes);
    if (nodes == NULL)
    {
        return NULL;
    }   
	
    C3DElementNode* materialNodes = (strlen(nodes->getNodeType()) > 0) ? nodes : nodes->getNextChild();
	assert(materialNodes);
    if (!materialNodes || !(strcmp(materialNodes->getNodeType(), "material") == 0))
    {
        return NULL;
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
		return NULL;
	}
	
    SAFE_DELETE(nodes);

	return material;
}


C3DResource* C3DMaterialManager::getResource(const std::string& name)
{
	C3DResource* material = this->findResource(name);  
	if(material != NULL)
    {
		C3DResource* newMaterial = material->clone();
					
		this->setResourceState(newMaterial,C3DResource::State_Used);
		return newMaterial;		
    }
    else
        return NULL;

	return NULL;
}

	

}
