#ifndef ResourceManager_H_
#define ResourceManager_H_

#include "cocos2d.h"

#include "C3DResource.h"
#include <map>

namespace cocos2d
{
class C3DResource;
class C3DResourcePool;
class C3DElementNode;

/**
*  managing a pool of resources of a particular type
*/
class  C3DResourceManager : public cocos2d::CCObject
{
public:
    C3DResourceManager();
    virtual ~C3DResourceManager();

    C3DResource* getResource(const std::string& name);

    virtual C3DResource* createResource(const std::string& name){ return NULL; }

    virtual C3DResource* cloneResource(C3DResource* resource) { return NULL; }

    virtual void preload(const std::string& name){};

    /** Gets the current memory usage, in bytes. */
    virtual size_t getMemoryUsage(void) const { return _memoryUsage; }

    virtual void removeResource(const std::string& name);
    virtual void removeResource(C3DResource* r);

    virtual void removeAll(void);

    void addResource(C3DResource* res);
    void setResourceState(C3DResource* res, C3DResource::State state);

    virtual void update(long elapsedTime);

    virtual bool load(const std::string& name);
    virtual bool save(){ return false; }

    /** Gets a string identifying the type of resource this manager handles. */
    const std::string& getType(void) const { return _type; }

protected:
    C3DResource* findResource(const std::string& name);

public:
    size_t      _memoryUsage; // In bytes

    std::string _type;

    long        _checkTime;
    long        _intervalCheckTime;
    C3DResourcePool*  _usedPool;
    C3DResourcePool*  _waitPool;
};
}

#endif