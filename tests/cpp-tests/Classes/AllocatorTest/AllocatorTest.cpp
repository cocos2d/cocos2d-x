
/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
 LIABILITY, WHETHER INAN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AllocatorTest.h"
#include "cocos2d.h"
#include <chrono>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

AllocatorTests::AllocatorTests()
{
    ADD_TEST_CASE(AllocatorTest);
}

#define kNumberOfInstances 100000
#define kObjectSize 952 // sizeof(Sprite)

namespace
{
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

#if CC_ENABLE_ALLOCATOR
    Test1::tAllocator Test1::_allocator("Test1", kNumberOfInstances);
#endif // CC_ENABLE_ALLOCATOR
}

//
// AllocatorTest
//

AllocatorTest::AllocatorTest()
{
    typedef std::vector<Test1*> tTest1Container;
    typedef std::vector<Test2*> tTest2Container;

    tTest1Container test1Container;
    test1Container.reserve(kNumberOfInstances);

    tTest2Container test2Container;
    test2Container.reserve(kNumberOfInstances);

    std::chrono::time_point<std::chrono::high_resolution_clock> alloc1Start, alloc1End, alloc2Start, alloc2End;
    std::chrono::time_point<std::chrono::high_resolution_clock> free1Start, free1End, free2Start, free2End;

    alloc1Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < kNumberOfInstances; ++i)
        test1Container.push_back(new Test1);
    alloc1End = std::chrono::high_resolution_clock::now();

    free1Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < kNumberOfInstances; ++i)
        delete test1Container[i];
    free1End = std::chrono::high_resolution_clock::now();
    test1Container.clear();

    alloc2Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < kNumberOfInstances; ++i)
        test2Container.push_back(new Test2);
    alloc2End = std::chrono::high_resolution_clock::now();


    free2Start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < kNumberOfInstances; ++i)
        delete test2Container[i];
    free2End = std::chrono::high_resolution_clock::now();

    test2Container.clear();

    std::chrono::duration<double> elapsed_seconds_alloc1 = alloc1End - alloc1Start;
    std::chrono::duration<double> elapsed_seconds_alloc2 = alloc2End - alloc2Start;
    std::chrono::duration<double> elapsed_seconds_free1 = free1End - free1Start;
    std::chrono::duration<double> elapsed_seconds_free2 = free2End - free2Start;

    char buf[1000];

    const float x_start = 240;
    const float y_start = 100;
    const float y_delta = 20;
    float y = 0;

    sprintf(buf, "alloc1 %f", elapsed_seconds_alloc1.count());
    auto alloc1 = Label::createWithSystemFont(buf, "Helvetica", 12);
    alloc1->setPosition(x_start, y++ * y_delta + y_start);
    addChild(alloc1);

    sprintf(buf, "alloc2 %f", elapsed_seconds_alloc2.count());
    auto alloc2 = Label::createWithSystemFont(buf, "Helvetica", 12);
    alloc2->setPosition(x_start, y++ * y_delta + y_start);
    addChild(alloc2);

    sprintf(buf, "free1  %f", elapsed_seconds_free1.count());
    auto free1 = Label::createWithSystemFont(buf, "Helvetica", 12);
    free1->setPosition(x_start, y++ * y_delta + y_start);
    addChild(free1);

    sprintf(buf, "free2  %f", elapsed_seconds_free2.count());
    auto free2 = Label::createWithSystemFont(buf, "Helvetica", 12);
    free2->setPosition(x_start, y++ * y_delta + y_start);
    addChild(free2);
}

AllocatorTest::~AllocatorTest()
{
}

std::string AllocatorTest::title() const
{
    return "Allocator Test";
}
