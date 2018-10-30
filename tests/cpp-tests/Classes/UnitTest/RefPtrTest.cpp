/****************************************************************************
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
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "RefPtrTest.h"

USING_NS_CC;

void RefPtrTest::onEnter()
{
    UnitTestDemo::onEnter();

#if (defined(COCOS2D_DEBUG) && COCOS2D_DEBUG > 0)
    // TEST(constructors)
    {
        // Default constructor
        RefPtr<Ref> ref1;
        CC_ASSERT(nullptr == ref1.get());

        // Parameter constructor
        RefPtr<__String> ref2(__String::create("Hello"));
        CC_ASSERT(strcmp("Hello", ref2->getCString()) == 0);
        CC_ASSERT(2 == ref2->getReferenceCount());

        // Parameter constructor with nullptr
        RefPtr<__String> ref3(nullptr);
        CC_ASSERT((__String*) nullptr == ref3.get());
        
        // Copy constructor
        RefPtr<__String> ref4(ref2);
        CC_ASSERT(strcmp("Hello", ref4->getCString()) == 0);
        CC_ASSERT(3 == ref2->getReferenceCount());
        CC_ASSERT(3 == ref4->getReferenceCount());
        
        // Copy constructor with nullptr reference
        RefPtr<Ref> ref5(ref1);
        CC_ASSERT((Ref*) nullptr == ref5.get());
    }
    
    // TEST(destructor)
    {
        __String * hello = __String::create("Hello");
        CC_ASSERT(1 == hello->getReferenceCount());
        
        {
            RefPtr<Ref> ref(hello);
            CC_ASSERT(2 == hello->getReferenceCount());
        }
        
        CC_ASSERT(1 == hello->getReferenceCount());
    }
    
    // TEST(assignmentOperator)
    {
        // Test basic assignment with pointer
        RefPtr<__String> ref1;
        CC_ASSERT((Ref*) nullptr == ref1.get());
        
        ref1 = __String::create("World");
        CC_ASSERT(strcmp("World", ref1->getCString()) == 0);
        CC_ASSERT(2 == ref1->getReferenceCount());
        
        // Assignment back to nullptr
        __String * world = ref1;
        CC_ASSERT(2 == world->getReferenceCount());
        
        ref1 = nullptr;
        CC_ASSERT(1 == world->getReferenceCount());
        
        // Assignment swapping 
        ref1 = __String::create("Hello");
        CC_ASSERT(strcmp("Hello", ref1->getCString()) == 0);
        CC_ASSERT(2 == ref1->getReferenceCount());
        
        __String * hello = (__String*) ref1;
        CC_ASSERT(2 == hello->getReferenceCount());
        
        ref1 = world;
        CC_ASSERT(1 == hello->getReferenceCount());
        CC_ASSERT(2 == world->getReferenceCount());
        
        // Test assignment with another reference
        RefPtr<__String> ref2 = __String::create("blah");
        __String * blah = ref2;
        CC_ASSERT(2 == blah->getReferenceCount());
        
        ref2 = ref1;
        CC_ASSERT(1 == blah->getReferenceCount());
        CC_ASSERT(3 == world->getReferenceCount());
    }
    
    // TEST(castBackToPointerOperator)
    {
        RefPtr<__String> ref1 = __String::create("Hello");
        __String * helloPtr = ref1;
        Ref * objectPtr = ref1;
        
        CC_ASSERT(helloPtr == objectPtr);
    }
    
    // TEST(dereferenceOperators)
    {
        RefPtr<__String> ref1 = __String::create("Hello");
        CC_ASSERT(strcmp("Hello", ref1->getCString()) == 0);
        CC_ASSERT(strcmp("Hello", (*ref1).getCString()) == 0);
    }
    
    // TEST(convertToBooleanOperator)
    {
        RefPtr<__String> ref1 = __String::create("Hello");
        CC_ASSERT(true == (bool) ref1);
        
        ref1 = nullptr;
        CC_ASSERT(false == (bool) ref1);
    }
    
    // TEST(get)
    {
        RefPtr<__String> ref1 = __String::create("Hello");
        CC_ASSERT(strcmp("Hello", ref1.get()->getCString()) == 0);
        
        ref1.reset();
        CC_ASSERT((__String*) nullptr == ref1.get());

        RefPtr<__String const> ref2 = __String::create("Hello");
        CC_ASSERT(strcmp("Hello", ref2.get()->getCString()) == 0);
        
        ref2.reset();
        CC_ASSERT(nullptr == ref2.get());
        static_assert(std::is_same<const __String*, decltype(ref2.get())>::value, "");
    }
    
    // TEST(reset)
    {
        RefPtr<__String> ref1;
        CC_ASSERT((__String*) nullptr == ref1.get());
        
        ref1.reset();
        CC_ASSERT((__String*) nullptr == ref1.get());
        
        ref1 = __String::create("Hello");
        CC_ASSERT(strcmp("Hello", ref1.get()->getCString()) == 0);
        
        __String * hello = ref1.get();
        CC_ASSERT(2 == hello->getReferenceCount());
        
        ref1.reset();
        CC_ASSERT((__String*) nullptr == ref1.get());
        CC_ASSERT(1 == hello->getReferenceCount());
    }
    
    // TEST(swap)
    {
        RefPtr<__String> ref1;
        RefPtr<__String> ref2;
        
        CC_ASSERT((__String*) nullptr == ref1.get());
        CC_ASSERT((__String*) nullptr == ref2.get());
        
        ref1.swap(ref2);
        
        CC_ASSERT((__String*) nullptr == ref1.get());
        CC_ASSERT((__String*) nullptr == ref2.get());
        
        __String * hello = __String::create("Hello");
        CC_ASSERT(1 == hello->getReferenceCount());
        
        ref1 = hello;
        CC_ASSERT(2 == hello->getReferenceCount());
        
        ref1.swap(ref2);
        CC_ASSERT(2 == hello->getReferenceCount());
        CC_ASSERT((__String*) nullptr == ref1.get());
        CC_ASSERT(strcmp("Hello", ref2->getCString()) == 0);
        
        ref1.swap(ref2);
        CC_ASSERT(2 == hello->getReferenceCount());
        CC_ASSERT(strcmp("Hello", ref1->getCString()) == 0);
        CC_ASSERT((__String*) nullptr == ref2.get());
        
        __String * world = __String::create("World");
        CC_ASSERT(1 == world->getReferenceCount());
        
        ref2 = world;
        CC_ASSERT(2 == world->getReferenceCount());
        
        ref2.swap(ref1);
        CC_ASSERT(strcmp("World", ref1->getCString()) == 0);
        CC_ASSERT(strcmp("Hello", ref2->getCString()) == 0);
        
        CC_ASSERT(2 == hello->getReferenceCount());
        CC_ASSERT(2 == world->getReferenceCount());
        
        ref1.swap(ref2);
        
        CC_ASSERT(strcmp("Hello", ref1->getCString()) == 0);
        CC_ASSERT(strcmp("World", ref2->getCString()) == 0);
        
        CC_ASSERT(2 == hello->getReferenceCount());
        CC_ASSERT(2 == world->getReferenceCount());
    }
    
    // TEST(staticPointerCast)
    {
        RefPtr<__String> ref1 = __String::create("Hello");
        CC_ASSERT(2 == ref1->getReferenceCount());
        
        RefPtr<Ref> ref2 = static_pointer_cast<Ref>(ref1);
        CC_ASSERT(strcmp("Hello", ((__String*) ref2.get())->getCString()) == 0);
        CC_ASSERT(3 == ref1->getReferenceCount());
    }
    
    // TEST(dynamicPointerCast)
    {
        RefPtr<__String> ref1 = __String::create("Hello");
        CC_ASSERT(2 == ref1->getReferenceCount());
        
        RefPtr<Ref> ref2 = dynamic_pointer_cast<Ref>(ref1);
        CC_ASSERT(strcmp("Hello", ((__String*) ref2.get())->getCString()) == 0);
        CC_ASSERT(3 == ref1->getReferenceCount());
        
        RefPtr<__String> ref3 = dynamic_pointer_cast<__String>(ref2);
        CC_ASSERT(strcmp("Hello", ref3->getCString()) == 0);
        CC_ASSERT(4 == ref1->getReferenceCount());
        
        RefPtr<cocos2d::Node> ref4 = dynamic_pointer_cast<cocos2d::Node>(ref2);
        CC_ASSERT((Ref*) nullptr == ref4.get());
    }
    
    // TEST(weakAssign)
    {
        RefPtr<__String> ref1;
        
        __String * string1 = new __String("Hello");
        ref1.weakAssign(string1);
        CC_ASSERT(1 == string1->getReferenceCount());
        
        RefPtr<__String> ref2 = ref1;
        CC_ASSERT(2 == string1->getReferenceCount());
        
        __String * string2 = new __String("World");
        ref1.weakAssign(string2);
        
        CC_ASSERT(1 == string1->getReferenceCount());
        CC_ASSERT(1 == ref2->getReferenceCount());
        
        __String * string3 = new __String("Blah");
        RefPtr<__String> ref3;
        ref3.weakAssign(string3);
        CC_ASSERT(1 == string3->getReferenceCount());
        
        string3->retain();
        CC_ASSERT(2 == string3->getReferenceCount());
        
        ref3.weakAssign(nullptr);
        CC_ASSERT(1 == string3->getReferenceCount());
        CC_SAFE_RELEASE_NULL(string3);
    }
    
    // TEST(comparisonOperators)
    {
        RefPtr<Ref> ref1;
        RefPtr<Ref> ref2;
        
        CC_ASSERT(true == (ref1 == ref2));
        CC_ASSERT(false == (ref1 != ref2));
        CC_ASSERT(false == (ref1 < ref2));
        CC_ASSERT(false == (ref1 > ref2));
        CC_ASSERT(true == (ref1 <= ref2));
        CC_ASSERT(true == (ref1 >= ref2));
        
        CC_ASSERT(true == (ref1 == nullptr));
        CC_ASSERT(false == (ref1 != nullptr));
        CC_ASSERT(false == (ref1 < nullptr));
        CC_ASSERT(false == (ref1 > nullptr));
        CC_ASSERT(true == (ref1 <= nullptr));
        CC_ASSERT(true == (ref1 >= nullptr));
        CC_ASSERT(false == (nullptr < ref1));
        CC_ASSERT(false == (nullptr > ref1));
        CC_ASSERT(true == (nullptr <= ref1));
        CC_ASSERT(true == (nullptr >= ref1));
        
        CC_ASSERT(false == (ref1 == __String::create("Hello")));
        CC_ASSERT(true == (ref1 != __String::create("Hello")));
        CC_ASSERT(true == (ref1 < __String::create("Hello")));
        CC_ASSERT(false == (ref1 > __String::create("Hello")));
        CC_ASSERT(true == (ref1 <= __String::create("Hello")));
        CC_ASSERT(false == (ref1 >= __String::create("Hello")));
        
        ref1 = __String::create("Hello");
        
        CC_ASSERT(false == (ref1 == ref2));
        CC_ASSERT(true == (ref1 != ref2));
        CC_ASSERT(false == (ref1 < ref2));
        CC_ASSERT(true == (ref1 > ref2));
        CC_ASSERT(false == (ref1 <= ref2));
        CC_ASSERT(true == (ref1 >= ref2));

        CC_ASSERT(false == (ref1 == nullptr));
        CC_ASSERT(true == (ref1 != nullptr));
        CC_ASSERT(false == (ref1 < nullptr));
        CC_ASSERT(true == (ref1 > nullptr));
        CC_ASSERT(false == (ref1 <= nullptr));
        CC_ASSERT(true == (ref1 >= nullptr));
        CC_ASSERT(true == (nullptr < ref1));
        CC_ASSERT(false == (nullptr > ref1));
        CC_ASSERT(true == (nullptr <= ref1));
        CC_ASSERT(false == (nullptr >= ref1));
    }
    
    // TEST(moveConstructor)
    {
        auto someFunc = []() -> RefPtr<__String>
        {
            return __String::create("Hello world!");
        };
        
        // Note: std::move will turn the rvalue into an rvalue reference and thus cause the move constructor to be invoked.
        // Have to use this because the compiler will try and optimize how we handle the return value otherwise and skip the move constructor.
        RefPtr<__String> theString(std::move(someFunc()));
        CC_ASSERT(theString->getReferenceCount() == 2);
        CC_ASSERT(theString->compare("Hello world!") == 0);
        
        __String * theStringPtr = theString;
        theString.reset();
        CC_ASSERT(theStringPtr->getReferenceCount() == 1);
        CC_ASSERT(theStringPtr->compare("Hello world!") == 0);
    }
    
    // TEST(moveAssignmentOperator)
    {
        auto someFunc = []() -> RefPtr<__String>
        {
            return __String::create("Hello world!");
        };
        
        RefPtr<__String> theString(someFunc());
        CC_ASSERT(theString->getReferenceCount() == 2);
        CC_ASSERT(theString->compare("Hello world!") == 0);
        
        theString = someFunc();                             // No need to use std::move here, compiler should figure out that move semantics are appropriate for this statement.
        CC_ASSERT(theString->getReferenceCount() == 2);
        CC_ASSERT(theString->compare("Hello world!") == 0);
    }
#else
    log("RefPtr tests are not executed in release mode");
#endif
}

std::string RefPtrTest::subtitle() const
{
    return "RefPtrTest, should not crash!";
}
