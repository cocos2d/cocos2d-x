#ifndef Resource_H_
#define Resource_H_
#include <string>
#include "cocos2d.h"

namespace cocos2d
{
class ElementNode;
class C3DResourcePool;

/**
Abstract class representing a loadable resource (e.g. textures, mesh etc)
*/
class C3DResource : public virtual cocos2d::CCObject
{
    friend class C3DUsedResourcePool;
    friend class C3DWaitResourcePool;

public:
    enum State
    {
        State_Init = 0,
        State_Used,
        State_Wait,
    };

    C3DResource();
    C3DResource(const std::string& id);

    virtual ~C3DResource();

    /** Calculate the size of a resource; this will only be called after 'load' */
    virtual size_t calculateSize(void) const
    {
        return 0;
    }

    virtual bool load(const std::string& fileName){ return false; }

    /**
    * load resource info from the elementnode
    *
    * @param nodes elementnode which contains the resource info.
    */
    virtual bool load(ElementNode* node);

    /**
    * save the resource info into the elementnode
    *
    * @param nodes elementnode which contains the renderstate info.
    */
    virtual bool save(ElementNode* node);

    virtual void unload(){};

    size_t getSize(void) const;

    /**
    * Returns the unique string identifier for the resource.
    */
    const std::string& getID(void) const;

    void setID(std::string& id);

    const C3DResource::State getState(void) const;

    void setState(C3DResource::State state);

    virtual void update(long elapsedTime);

    /**
    * clone a material from current material.
    */
    virtual C3DResource* clone() const;

    void copyFrom(const C3DResource* other);

    int getCloneNum();

private:

    std::string _id;    // Unique id of the resource

    size_t      _size;  // The size of the resource in bytes

    long        _waitTime;
    long        _checkWaitTime;
    State       _state;

    int         _cloneNum;
};
}

#endif
