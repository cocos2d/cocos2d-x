#include "C3DResourceManager.h"
#include "C3DResource.h"
#include "C3DResourcePool.h"
#include "Base.h"

namespace cocos2d
{
C3DResourceManager::C3DResourceManager() :_memoryUsage(0)
{
    _usedPool = new C3DUsedResourcePool(this);
    _waitPool = new C3DWaitResourcePool(this);

    _intervalCheckTime = 1000;
    _checkTime = 0;
}

C3DResourceManager::~C3DResourceManager()
{
    removeAll();

    SAFE_DELETE(_usedPool);
    SAFE_DELETE(_waitPool);
}

C3DResource* C3DResourceManager::findResource(const std::string& name)
{
    C3DResource* res = NULL;
    res = _usedPool->getItem(name);
    if (res == NULL)
        res = _waitPool->getItem(name);
    return  res;
}

bool C3DResourceManager::load(const std::string& name)
{
    return false;
}

void C3DResourceManager::addResource(C3DResource* res)
{
    if (res->getState() == C3DResource::State_Used)
    {
        _usedPool->addItem(res);
    }
    else if (res->getState() == C3DResource::State_Wait)
    {
        _waitPool->addItem(res);
    }
}

C3DResource* C3DResourceManager::getResource(const std::string& name)
{
    C3DResource* sprite = findResource(name);
    if (sprite != NULL)
    {
        return cloneResource(sprite);
    }
    else
    {
        return createResource(name);
    }
}

void C3DResourceManager::removeResource(C3DResource* res)
{
    if (res == NULL)
        return;

    if (res->getState() == C3DResource::State_Used)
    {
        _usedPool->removeItem(res->getID());
    }
    else if (res->getState() == C3DResource::State_Wait)
    {
        _waitPool->removeItem(res->getID());
    }
}

void C3DResourceManager::removeResource(const std::string& name)
{
    C3DResource* res = findResource(name);

    if (res)
    {
        this->removeResource(res);
    }
}

void C3DResourceManager::removeAll(void)
{
    if (_usedPool != NULL)
        _usedPool->clear();

    if (_waitPool != NULL)
        _waitPool->clear();
}

void C3DResourceManager::setResourceState(C3DResource* res, C3DResource::State state)
{
    if (res->getState() == state)
    {
        return;
    }
    else
    {
        res->retain();
        if (res->getState() == C3DResource::State_Init && state == C3DResource::State_Used)
        {
            _usedPool->addItem(res);
        }

        if (res->getState() == C3DResource::State_Used && state == C3DResource::State_Wait)
        {
            _usedPool->removeItem(res->getID());
            _waitPool->addItem(res);
        }
        else if (res->getState() == C3DResource::State_Wait && state == C3DResource::State_Used)
        {
            _waitPool->removeItem(res->getID());
            _usedPool->addItem(res);
        }
        res->setState(state);
        res->release();
    }
}

void C3DResourceManager::update(long elapsedTime)
{
    _checkTime += elapsedTime;
    if (_checkTime > _intervalCheckTime)
    {
        _checkTime = 0;

        if (_usedPool != NULL)
            _usedPool->update(elapsedTime);

        if (_waitPool != NULL)
            _waitPool->update(elapsedTime);
    }
}
}
