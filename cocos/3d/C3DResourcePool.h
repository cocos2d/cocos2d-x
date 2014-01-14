#ifndef ResourcePool_H_
#define ResourcePool_H_

#include <map>
#include <string>

namespace cocos2d
{
class C3DResource;
class C3DResourceManager;

/**
Resource pool
*/
class  C3DResourcePool
{
public:
    C3DResourcePool(C3DResourceManager* manager);
    virtual ~C3DResourcePool();

    bool  removeItem(const std::string& name);

    bool addItem(C3DResource* item);

    C3DResource* getItem(const std::string& name);
    void clear();

    virtual void update(long elapsedTime) = 0;

protected:
    std::map<std::string, C3DResource*> _items;
    C3DResourceManager* _manager;
};

class C3DUsedResourcePool : public C3DResourcePool
{
public:
    C3DUsedResourcePool(C3DResourceManager* manager);
    virtual void update(long elapsedTime);
};

class C3DWaitResourcePool : public C3DResourcePool
{
public:
    C3DWaitResourcePool(C3DResourceManager* manager);
    virtual void update(long elapsedTime);
};
}

#endif