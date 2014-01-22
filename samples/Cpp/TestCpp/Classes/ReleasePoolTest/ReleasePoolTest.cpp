#include "ReleasePoolTest.h"

using namespace cocos2d;

class TestObject : public Object
{
public:
    
};

void ReleasePoolTestScene::runThisTest()
{
    // title
    auto label = LabelTTF::create("AutoreasePool Test", "Arial", 32);
    addChild(label, 9999);
    label->setPosition(Point(VisibleRect::center().x, VisibleRect::top().y - 30));
    
    // reference count should be added when added into auto release pool
    
    TestObject *obj = new TestObject();
    obj->autorelease();
    assert(obj->retainCount() == 2);
    
    // can invoke autorelease more than once
    obj->autorelease();
    assert(obj->retainCount() == 3);
    
    // create an autorelease pool in stack
    
    {
        AutoreleasePool pool1;
        
        obj->autorelease();
        assert(obj->retainCount() == 4);
        
        // retain, release can work together with autorelease pool
        obj->retain();
        assert(obj->retainCount() == 5);
        obj->release();
        assert(obj->retainCount() == 4);
        
        
        AutoreleasePool pool2;
        for (int i = 0; i < 1000; ++i)
        {
            TestObject *tmpObj = new TestObject();
            tmpObj->autorelease();
        }
        pool2.dump();
    }
    
    // pool is destroyed, so the release count is minused by one
    assert(obj->retainCount() == 3);
    
    Director::getInstance()->replaceScene(this);
}
