#ifndef SKELETON_H_
#define SKELETON_H_

#include <string>
#include <map>
#include "Vector3.h"
#include "Vector4.h"
namespace cocos2d
{

class C3DNode;
class C3DAnimation;
class C3DBone;
class C3DGeoWireRender;

/**
 * Defines a class for controlling skeleton bone.
 */
class C3DSkeleton
{
public:
    /**
     * Constructor.
     */
    C3DSkeleton();

    /**
     * Destructor.
     */
    virtual ~C3DSkeleton();
        
    /**
     * Creates C3DBone.
     */
    C3DBone* createBone(const std::string& name);
    
    /**
     * Get root bone.
     */
    C3DBone* getRootBone(void) const{return _rootBone;}

    /**
     * Get root by specified name.
     */
    C3DBone* getBone(const std::string& name) const;
    
    /**
     * Creates C3DAnimation.
     */
    C3DAnimation* createAnimation(const std::string& name);

    /**
     * Gets C3DAnimation by specified name.
     */
    C3DAnimation* getAnimation(const std::string& name) const;
    
    /**
     * Removes C3DAnimation by specified name.
     */
    void removeAnimation(const std::string& name);

    /**
     * Sets C3DBone.
     */
    void set(C3DBone* joint);

    /**
     * Gets bone's child bone.
     */
    void getChild(std::map<std::string, C3DBone*>& bones,C3DNode* node);

    /**
     * clone.
     */
    C3DSkeleton* clone();

private:
    C3DBone* _rootBone;
    /// Lookup by bone name
    std::map<std::string, C3DBone*> _bones;
    
    /// Storage of animations, lookup by name
    std::map<std::string, C3DAnimation*> _animations;

   
};

    

}


#endif
