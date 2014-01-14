#include "C3DResourcePool.h"
#include "C3DResource.h"
#include "C3DResourceManager.h"
#include "Base.h"
namespace cocos2d
{
C3DResourcePool::C3DResourcePool(C3DResourceManager* manager)
{
    _manager = manager;
}

C3DResourcePool::~C3DResourcePool()
{
    clear();

    _manager = NULL;
}

void C3DResourcePool::clear()
{
    for (std::map<std::string, C3DResource*>::iterator iter = _items.begin(); iter != _items.end(); ++iter)
    {
        iter->second->release();
    }
    _items.clear();
}

bool C3DResourcePool::addItem(C3DResource* item)
{
    if (_items.find(item->getID()) == _items.end())
    {
        _items[item->getID()] = item;
        item->retain();
        return true;
    }
    else
        return false;
}

bool C3DResourcePool::removeItem(const std::string& name)
{
    std::map<std::string, C3DResource*>::iterator iter = _items.find(name);

    if (iter != _items.end())
    {
        iter->second->release();
        _items.erase(iter);
        return true;
    }
    else
        return false;
}

C3DResource* C3DResourcePool::getItem(const std::string& name)
{
    std::map<std::string, C3DResource*>::iterator iter = _items.find(name);
    if (iter != _items.end())
    {
        return iter->second;
    }
    else
        return NULL;
}

C3DUsedResourcePool::C3DUsedResourcePool(C3DResourceManager* manager)
    :C3DResourcePool(manager)
{
    _manager = manager;
}

void C3DUsedResourcePool::update(long elapsedTime)
{
    C3DResource* item = NULL;
    for (std::map<std::string, C3DResource*>::iterator iter = _items.begin(); iter != _items.end();)
    {
        item = iter->second;

        if (item->retainCount() == 1)
        {
            item->setState(C3DResource::State_Wait);
            _manager->addResource(item);
            item->release();
            _items.erase(iter++);
        }
        else
        {
            ++iter;
        }
    }
}

C3DWaitResourcePool::C3DWaitResourcePool(C3DResourceManager* manager)
    :C3DResourcePool(manager)
{
    _manager = manager;
}

void C3DWaitResourcePool::update(long elapsedTime)
{
    C3DResource* item = NULL;
    for (std::map<std::string, C3DResource*>::iterator iter = _items.begin(); iter != _items.end();)
    {
        item = iter->second;

        item->_checkWaitTime += elapsedTime;
        if (item->_checkWaitTime > item->_waitTime)
        {
            item->_checkWaitTime = 0;

            item->release();
            _items.erase(iter++);
        }
        else
        {
            ++iter;
        }
    }
}
}
