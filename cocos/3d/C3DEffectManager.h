#ifndef EFFECTMANAGER_H_
#define EFFECTMANAGER_H_

#include "Base.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "C3DMatrix.h"

#include <string>
#include <map>
#include "cocos2d.h"
#include "C3DResourceManager.h"

NS_CC_BEGIN

class ElementNode;
class C3DEffect;

/**
*A C3DEffectManager manager effect's load£¬preload, and so on.
*/
class C3DEffectManager : public C3DResourceManager
{
public:    

    static C3DEffectManager* getInstance();

    virtual C3DResource* createResource(const std::string& name);

    virtual C3DResource* cloneResource(C3DResource* resource);

    /**
    * preload all shader files from the specific config file.
    *
    * @param fileName The path to the shader config file.     
    */
    virtual void preload(const std::string& name);

    /**
    * preload  this shader file.
    *
    * @param vshPath The path to the vertex shader file.
    * @param fshPath The path to the fragment shader file.
    * @param defines The precompile defines.
    */
    void preload(ElementNode* node);

    static std::string generateID( std::string& vshPath, std::string& fshPath, std::string& defines);
private:

    C3DEffectManager();

    ~C3DEffectManager();    

    void loadAllEffect(ElementNode* effectNodes);    



};

NS_CC_END

#endif // EFFECTMANAGER_H_
