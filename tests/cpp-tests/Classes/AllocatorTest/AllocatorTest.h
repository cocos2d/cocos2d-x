
#pragma once

/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 
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

#include "../testBasic.h"
#include "../BaseTest.h"
#include "base/allocator/CCAllocatorStrategyPool.h"

namespace AllocatorTestNS
{
    
    //
    // Test Classes
    //
    
#define kNumberOfInstances 100000
#define kObjectSize 952 // sizeof(Sprite)
    
    class Test1;
    
    class Test1
    {
    public:
        
        Test1()
        {
            memset(bytes, 0, sizeof(bytes));
        }
        uint8_t bytes[kObjectSize];
        
#if CC_ENABLE_ALLOCATOR
        typedef cocos2d::allocator::AllocatorStrategyPool<Test1> tAllocator;
        static tAllocator _allocator;
#endif // CC_ENABLE_ALLOCATOR
        CC_USE_ALLOCATOR_POOL(Test1, _allocator);
    };
    
    class Test2
    {
    public:
        
        Test2()
        {
            memset(bytes, 0, sizeof(bytes));
        }
        uint8_t bytes[kObjectSize];
    };
    
    class AllocatorTest : public BaseTest
    {
    public:
        CREATE_FUNC(AllocatorTest);
        AllocatorTest();
        virtual ~AllocatorTest();
        
        virtual std::string title() const;
        virtual std::string subtitle() const;
        
        virtual void restartCallback(Ref* sender);
        virtual void nextCallback(Ref* sender);
        virtual void backCallback(Ref* sender);
        
        virtual void onEnter() override;
        virtual void onExit() override;
        
        virtual void update(float delta);
    };
    
    class AllocatorTestScene : public TestScene
    {
    public:
        AllocatorTestScene();
        virtual void runThisTest();
    };
    
} // AllocatorTestNS
