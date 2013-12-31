#ifndef MATERIALMANAGER_H_
#define MATERIALMANAGER_H_
#include "Base.h"

#include "C3DResourceManager.h"

NS_CC_BEGIN

class C3DElementNode;
class C3DEffect;

/**
*A materialManager manager material's load£¬preload, and so on.
*/
class C3DMaterialManager : public C3DResourceManager
{
public:
	static C3DMaterialManager* getInstance();

	virtual C3DResource* createResource(const std::string& name);	

	virtual C3DResource* cloneResource(C3DResource* resource);		

private:

	C3DMaterialManager();

	~C3DMaterialManager();

};

NS_CC_END

#endif
