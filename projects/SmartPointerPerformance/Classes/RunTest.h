//
//  RunTest.c
//  SmartPointer
//
//  Created by Walzer on 6/10/13.
//  Copyright (c) 2013 cocos2d-x. All rights reserved.
//

#ifndef _RunTest_h_
#define _RunTest_h_

#include <memory>
#include "SharedPointer.h"
#include "CppPointer.h"

// shared pointer
class TestSharedPointer
{
public:
    TestSharedPointer(): _scene(nullptr) {}
    
    void onEnter();
    void update();
    
private:
    std::shared_ptr<shared::Node> _scene;    
};

// cpp pointer
class TestCppPointer
{
public:
    TestCppPointer() :_scene(nullptr){};
    ~TestCppPointer();
    void onEnter();
    void update();
private:
    cpp::Node* _scene;
};

#endif // end of _RunTest_h_
