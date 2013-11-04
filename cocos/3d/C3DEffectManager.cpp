#include "Base.h"
#include "C3DEffect.h"
#include "C3DElementNode.h"
#include "C3DEffectManager.h"
#include "C3DElementNode.h"

namespace cocos3d
{
static C3DEffectManager* __effectManagerInstance = NULL;

C3DEffectManager::C3DEffectManager() 
{
}

C3DEffectManager::~C3DEffectManager()
{
	__effectManagerInstance = NULL;
    
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

void C3DEffectManager::preload(const std::string& fileName)
{
	if(fileName.c_str() != NULL)
	{
		C3DElementNode* doc = C3DElementNode::create(fileName.c_str());
		if (!doc)
		{
			LOG_ERROR_VARG("Error loading effect: Could not load file: %s", fileName.c_str());
			return;
		}

		loadAllEffect((strlen(doc->getNodeType()) > 0) ? doc : doc->getNextChild());
		SAFE_DELETE(doc);
	}	
}


void C3DEffectManager::loadAllEffect(C3DElementNode* effectNodes)
{
	if( effectNodes != NULL )
	{		
		if (strcmp(effectNodes->getNodeType(), "Effects") != 0)
		{
			LOG_ERROR("Error proLoading Effects: No 'Effects' namespace found");
			return;
		}
		else
		{		
			effectNodes->rewind();
			C3DElementNode* effectNode = NULL;
			
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
					if (flagsNode != NULL && strcmp(flagsNode->getNodeType(), "flags") == 0)
					{
						flagsNode->rewind();
						const char* defines = NULL;
						const char* value = NULL;
						while (defines = flagsNode->getNextElement())
						{
							value = flagsNode->getElement();
														
							std::string flag;
							if (defines != NULL)
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
					elementNode->setElement("vertexShader", (vspath == NULL) ? "" : vspath);
					elementNode->setElement("fragmentShader", (fspath == NULL) ? "" : fspath);	
					const char* define;

					for(std::vector<std::string>::iterator iter = flags.begin();iter!=flags.end();++iter)
					{		
						define = (*iter).c_str();
						if(define != NULL)
							elementNode->setElement("defines", define);

						preload(elementNode);
					}
					SAFE_DELETE(elementNode);
				}				
			}
		}	
	}	

}

C3DResource* C3DEffectManager::createResource(const std::string& name,C3DElementNode* node)
{
	C3DResource* effect = new C3DEffect(name);

	effect->autorelease();		

	if(effect->load(node) == true)
	{	
		this->setResourceState(effect,C3DResource::State_Used);
	}
	effect->retain();
		
	return effect;
}

std::string C3DEffectManager::generateID( std::string& vshPath, std::string& fshPath, std::string& defines,C3DElementNode* outNode )
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

	if(outNode != NULL)
	{
		outNode->setElement("vertexShader", vshPath.c_str());
	    outNode->setElement("fragmentShader", fshPath.c_str());			
		if(define.c_str() != NULL)
			outNode->setElement("defines", define.c_str());
	}


	return uniqueId;

}



C3DResource* C3DEffectManager::getResource(const std::string& name)
{   

	C3DResource* effect = this->findResource(name);  
	if(effect != NULL)
    {
		effect->retain();		
		this->setResourceState(effect,C3DResource::State_Used);
		return effect;		
    }	

    return NULL;
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

	if(effect != NULL)
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

}
