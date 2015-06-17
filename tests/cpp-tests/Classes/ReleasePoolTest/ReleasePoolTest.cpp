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
