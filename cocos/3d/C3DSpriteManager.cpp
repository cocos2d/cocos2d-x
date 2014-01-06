#include "Base.h"
#include "C3DSprite.h"
#include "C3DSpriteManager.h"
#include "StringTool.h"

NS_CC_BEGIN

static C3DSpriteManager* __spriteManagerInstance = nullptr;

C3DSpriteManager::C3DSpriteManager() 
{
}

C3DSpriteManager::~C3DSpriteManager()
{
	__spriteManagerInstance = nullptr;
}

C3DSpriteManager* C3DSpriteManager::getInstance()
{	   
	if (!__spriteManagerInstance)
	{
		__spriteManagerInstance = new C3DSpriteManager();
		__spriteManagerInstance->autorelease();
	}
	return __spriteManagerInstance;
}


C3DResource* C3DSpriteManager::createResource(const std::string& name)
{   
	C3DResource* sprite = new C3DSprite(name.c_str());
	sprite->autorelease();		

	if(sprite->load(name) == true)
	{	
		this->setResourceState(sprite,C3DResource::State_Used);
	}

	return sprite;
}


void C3DSpriteManager::preload( const std::string& name )
{		
	C3DResource* sprite = this->findResource(name);

	if(sprite != nullptr)
		return; 
	else
	{		
		sprite = new C3DSprite(name.c_str());
		sprite->autorelease();

		if(sprite->load(name) == true)
		{			
			this->setResourceState(sprite,C3DResource::State_Used);			
		}	
	}	
}	


C3DResource* C3DSpriteManager::cloneResource(C3DResource* sprite)
{	 
	if(sprite != nullptr)
	{					
		C3DNode::CloneContext context;
		context.cloneChildren = true;

		context.cloneMap.clear();
		context.clonedAnim.clear();
		context.clonedMeshSkin.clear();

		context.idSuffix = StringTool::toString( sprite->getCloneNum()+1 );
		C3DSprite* newSprite = static_cast<C3DSprite*> (static_cast<C3DSprite*>(sprite)->clone(context));

		this->setResourceState(newSprite,C3DResource::State_Used);
		return newSprite;
	}
	else
		return nullptr;
}

NS_CC_END
