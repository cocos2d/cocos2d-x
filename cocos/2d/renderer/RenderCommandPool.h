//
//  RenderCommandPool.h
//  cocos2d_libs
//
//  Created by Huabing on 11/28/13.
//
//

#ifndef __CC_RENDERCOMMANDPOOL_H__
#define __CC_RENDERCOMMANDPOOL_H__

#include <set>
#include <list>
#include "CCPlatformMacros.h"
NS_CC_BEGIN

template <class T>
class RenderCommandPool
{
public:
    RenderCommandPool()
    {
    }
    ~RenderCommandPool()
    {
//        if( 0 != _usedPool.size())
//        {
//            CCLOG("All RenderCommand should not be used when Pool is released!");
//        }
        for (typename std::list<T*>::iterator iter = _freePool.begin(); iter != _freePool.end(); ++iter)
        {
            delete *iter;
            *iter = nullptr;
        }
        _freePool.clear();
    }
    
public:
    T* generateCommand()
    {
        T* result = nullptr;
        if(0 == _freePool.size())
        {
            result = new T();
        }
        else
        {
            result = _freePool.front();
            _freePool.pop_front();
        }
        //_usedPool.insert(result);
        return result;
    }
    
    void pushBackCommand(T* ptr)
    {
//        if(_usedPool.find(ptr) == _usedPool.end())
//        {
//            CCLOG("push Back Wrong command!");
//            return;
//        }
        
        _freePool.push_back(ptr);
        //_usedPool.erase(ptr);
        
    }
    
private:
    std::list<T*> _freePool;
    //std::set<T*> _usedPool;
};

NS_CC_END

#endif
