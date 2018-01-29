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

#include "ReleasePoolTest.h"

using namespace cocos2d;

ReleasePoolTests::ReleasePoolTests()
{
    ADD_TEST_CASE(ReleasePoolTest);
}

class TestObject : public Ref
{
public:
    TestObject() : _name(""){}
    
    TestObject(std::string name) : _name(name)
    {
        CCLOG("TestObject:%s is created", _name.c_str());
    }
    
    ~TestObject()
    {
        if (_name.size() > 0)
            CCLOG("TestObject:%s is destroyed", _name.c_str());
    }
    
private:
    std::string _name;
};

bool ReleasePoolTest::init()
{
    if (!TestCase::init())
    {
        return false;
    }
    // title
    auto label = Label::createWithTTF("AutoreasePool Test", "fonts/arial.ttf", 32);
    addChild(label, 9999);
    label->setPosition(Vec2(VisibleRect::center().x, VisibleRect::top().y - 30));
    
    // reference count should be added when added into auto release pool
    
    TestObject *obj = new (std::nothrow) TestObject("testobj");
    obj->autorelease();
    assert(obj->getReferenceCount() == 1);
    
    // should retain first before invoking autorelease
    obj->retain();
    obj->autorelease();
    assert(obj->getReferenceCount() == 2);
    
    // create an autorelease pool in stack
    
    {
        AutoreleasePool pool1;
        
        // can invoke autorelease more than once
        obj->retain();
        obj->autorelease();
        assert(obj->getReferenceCount() == 3);
        obj->retain();
        obj->autorelease();
        assert(obj->getReferenceCount() == 4);
        
        // retain, release can work together with autorelease pool
        obj->retain();
        assert(obj->getReferenceCount() == 5);
        obj->release();
        assert(obj->getReferenceCount() == 4);
    }
    
    assert(obj->getReferenceCount() == 2);
    
    // example of using temple autorelease pool
    {
        AutoreleasePool pool2;
        char name[20];
        for (int i = 0; i < 100; ++i)
        {
            snprintf(name, 20, "object%d", i);
            TestObject *tmpObj = new (std::nothrow) TestObject(name);
            tmpObj->autorelease();
        }
    }
    
    // object in pool2 should be released

    {
        new AutoreleasePool;
        PoolManager::destroyInstance();
    }
    
    return true;
}
