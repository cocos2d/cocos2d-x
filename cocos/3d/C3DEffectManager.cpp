#include "Base.h"
#include "C3DEffect.h"
#include "C3DElementNode.h"
#include "C3DEffectManager.h"
#include "C3DElementNode.h"
#include "StringTool.h"

NS_CC_BEGIN

static C3DEffectManager* __effectManagerInstance = nullptr;

C3DEffectManager::C3DEffectManager() 
{
}

C3DEffectManager::~C3DEffectManager()
{
	__effectManagerInstance = nullptr;

}

C3DEffectManager* C3DEffectManager::getInstance()
{	   
	if (!__effectManagerInstance)
	{
		__effectManagerInstance = new C3DEffectManager();
		__effectManagerInstance->autorelease();
	}
	return __effectManagerInstance;

}

void C3DEffectManager::preload(const std::string& name)
{
	if(name.c_str() != nullptr)
	{
		C3DElementNode* doc = C3DElementNode::create(name.c_str());
		if (!doc)
		{
			LOG_ERROR_VARG("Error loading effect: Could not load file: %s", name.c_str());
			return;
		}

		loadAllEffect((strlen(doc->getNodeType()) > 0) ? doc : doc->getNextChild());
		SAFE_DELETE(doc);
	}	
}


void C3DEffectManager::loadAllEffect(C3DElementNode* effectNodes)
{
	if( effectNodes != nullptr )
	{		
		if (strcmp(effectNodes->getNodeType(), "Effects") != 0)
		{
			LOG_ERROR("Error proLoading Effects: No 'Effects' namespace found");
			return;
		}
		else
		{		
			effectNodes->rewind();
			C3DElementNode* effectNode = nullptr;

			while ((effectNode = effectNodes->getNextChild()))
			{
				if (strcmp(effectNode->getNodeType(), "Effect") == 0)
				{
					const char* vspath = effectNode->getElement("vertexShader");
					assert(vspath);

					const char* fspath = effectNode->getElement("fragmentShader");
					assert(fspath);
					std::vector<std::string> flags;
					flags.push_back("");
					C3DElementNode* flagsNode = effectNode->getNextChild();
					if (flagsNode != nullptr && strcmp(flagsNode->getNodeType(), "flags") == 0)
					{
						flagsNode->rewind();
						const char* defines = nullptr;
						const char* value = nullptr;
						while (defines = flagsNode->getNextElement())
						{
							value = flagsNode->getElement();

							std::string flag;
							if (defines != nullptr)
							{
								flag = value;
								flag.insert(0, "#define ");
								unsigned int pos;
								while ((pos = flag.find(';')) != std::string::npos)
								{
									flag.replace(pos, 1, "\n#define ");
								}
								flag += "\n";
							}							

							flags.push_back(flag);
						}						
					}	

					C3DElementNode* elementNode = C3DElementNode::createEmptyNode("test", "effect");
					elementNode->setElement("vertexShader", (vspath == nullptr) ? "" : vspath);
					elementNode->setElement("fragmentShader", (fspath == nullptr) ? "" : fspath);	
					const char* define;

					for(std::vector<std::string>::iterator iter = flags.begin();iter!=flags.end();++iter)
					{		
						define = (*iter).c_str();
						if(define != nullptr)
							elementNode->setElement("defines", define);

						preload(elementNode);
					}
					SAFE_DELETE(elementNode);
				}				
			}
		}	
	}	

}

C3DResource* C3DEffectManager::createResource(const std::string& name)
{
	std::vector<std::string> a = StringTool::StringSplitByChar(name,';');
	if(a.size() < 2)
		return nullptr;

	std::string vshpath = a[0];
	std::string fshpath = a[1];
	std::string define;
	if(a.size()==3)
		define = a[2];

	C3DElementNode* elementNode = C3DElementNode::createEmptyNode("test", "effect");

	if(elementNode != nullptr)
	{
		elementNode->setElement("vertexShader", vshpath.c_str());
		elementNode->setElement("fragmentShader", fshpath.c_str());			
		if(define.c_str() != nullptr)
			elementNode->setElement("defines", define.c_str());
	} 				

	C3DResource* effect = new C3DEffect(name);
	effect->autorelease();

	if(effect->load(elementNode) == true)
	{	
		this->setResourceState(effect,C3DResource::State_Used);
	}
	effect->retain();

	SAFE_DELETE(elementNode);

	return effect;    
}

std::string C3DEffectManager::generateID( std::string& vshPath, std::string& fshPath, std::string& defines )
{	 
	assert(vshPath.c_str());

	assert(fshPath.c_str());

	std::string define;
	if (defines.size() != 0)
	{
		define = defines;
		define.insert(0, "#define ");
		unsigned int pos;
		while ((pos = define.find(';')) != std::string::npos)
		{
			define.replace(pos, 1, "\n#define ");
		}
		define += "\n";
	}

	std::string uniqueId = vshPath;
	uniqueId += ';';
	uniqueId += fshPath;
	uniqueId += ';';
	if (define.c_str() != 0)
	{
		uniqueId += define;
	}

	return uniqueId;

}


C3DResource* C3DEffectManager::cloneResource(C3DResource* resource)
{
	if(resource != nullptr)
	{
		resource->retain();		
		this->setResourceState(resource,C3DResource::State_Used);
		return resource;		
	}
	else
		return nullptr;

}

void C3DEffectManager::preload(C3DElementNode* node)
{	
	const char* vshPath = node->getElement("vertexShader");
	const char* fshPath = node->getElement("fragmentShader");
	const char* defines = node->getElement("defines");

	std::string uniqueId = vshPath;
	uniqueId += ';';
	uniqueId += fshPath;
	uniqueId += ';';
	if (defines != 0)
	{
		uniqueId += defines;
	}

	C3DResource* effect = this->findResource(uniqueId);

	if(effect != nullptr)
		return; 
	else
	{
		C3DEffect* effect = new C3DEffect(uniqueId);

		effect->autorelease();

		if(effect->load(node) == true)
		{			
			this->setResourceState(effect,C3DResource::State_Used);

		}	
	}

}

NS_CC_END
