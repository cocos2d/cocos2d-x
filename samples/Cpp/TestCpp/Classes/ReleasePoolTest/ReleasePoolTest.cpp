#include "ReleasePoolTest.h"

using namespace cocos2d;

class TestObject : public Object
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

void ReleasePoolTestScene::runThisTest()
{
    // title
    auto label = LabelTTF::create("AutoreasePool Test", "Arial", 32);
    addChild(label, 9999);
    label->setPosition(Point(VisibleRect::center().x, VisibleRect::top().y - 30));
    
    // reference count should be added when added into auto release pool
    
    TestObject *obj = new TestObject("my test object");
    obj->autorelease();
    assert(obj->retainCount() == 1);
    
    // can invoke autorelease more than once
    obj->autorelease();
    assert(obj->retainCount() == 1);
    
    // create an autorelease pool in stack
    
    {
        AutoreleasePool pool1;
        
        obj->autorelease();
        assert(obj->retainCount() == 1);
        
        // retain, release can work together with autorelease pool
        obj->retain();
        assert(obj->retainCount() == 2);
        obj->release();
        assert(obj->retainCount() == 1);
    }
    
    // pool is destroyed, so the release count is minused by one, should print that the "obj" is released
    
    {
        AutoreleasePool pool2;
        for (int i = 0; i < 100; ++i)
        {
            TestObject *tmpObj = new TestObject();
            tmpObj->autorelease();
        }
        pool2.dump();
    }
    
    Director::getInstance()->replaceScene(this);
}
