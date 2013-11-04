#ifndef MATERIALMANAGER_H_
#define MATERIALMANAGER_H_
#include "Base.h"

#include "C3DResourceManager.h"

namespace cocos3d
{

class C3DElementNode;
class C3DEffect;

/**
 *A materialManager manager material's load£¬preload, and so on.
 */
class C3DMaterialManager : public C3DResourceManager
{
public:	

	static C3DMaterialManager* getInstance();

	virtual C3DResource* createResource(const std::string& name,C3DElementNode* node);

	virtual C3DResource* createResource(const std::string& name);
				
	 /**
     * get an effect using the specified vertex and fragment shader.
     * @return The created effect.
     */
	virtual C3DResource* getResource(const std::string& name);
	
private:

    C3DMaterialManager();

    ~C3DMaterialManager();
	   
};

}

#endif
