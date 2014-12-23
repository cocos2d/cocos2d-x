/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#ifndef __CC_RENDERCOMMANDPOOL_H__
#define __CC_RENDERCOMMANDPOOL_H__

#include <list>

#include "platform/CCPlatformMacros.h"

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
        _freePool.clear();
        for (typename std::list<T*>::iterator iter = _allocatedPoolBlocks.begin(); iter != _allocatedPoolBlocks.end(); ++iter)
        {
            delete[] *iter;
            *iter = nullptr;
        }
        _allocatedPoolBlocks.clear();
    }

    T* generateCommand()
    {
        T* result = nullptr;
        if(_freePool.empty())
        {
            AllocateCommands();
        }
        result = _freePool.front();
        _freePool.pop_front();
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
    void AllocateCommands()
    {
        static const int COMMANDS_ALLOCATE_BLOCK_SIZE = 32;
        T* commands = new (std::nothrow) T[COMMANDS_ALLOCATE_BLOCK_SIZE];
        _allocatedPoolBlocks.push_back(commands);
        for(int index = 0; index < COMMANDS_ALLOCATE_BLOCK_SIZE; ++index)
        {
            _freePool.push_back(commands+index);
        }
    }

    std::list<T*> _allocatedPoolBlocks;
    std::list<T*> _freePool;
    //std::set<T*> _usedPool;
};

NS_CC_END

#endif
