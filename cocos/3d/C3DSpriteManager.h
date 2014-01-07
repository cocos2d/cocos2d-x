#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include "Base.h"
#include "C3DResourceManager.h"

NS_CC_BEGIN

class ElementNode;
class C3DEffect;

/**
*A materialManager manager material's load£¬preload, and so on.
*/
class C3DSpriteManager : public C3DResourceManager
{
public:    

    static C3DSpriteManager* getInstance();    

    virtual C3DResource* createResource(const std::string& name);

    virtual C3DResource* cloneResource(C3DResource* sprite);

    virtual void preload( const std::string& name );

private:

    C3DSpriteManager();

    virtual ~C3DSpriteManager();
};

NS_CC_END

#endif // SPRITEMANAGER_H_
