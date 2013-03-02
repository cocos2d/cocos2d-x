#include "cocos2d.h"
#include "cocos-ext.h"

class CCScrollMenu: public cocos2d::CCMenu {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCScrollMenu, create);

    CCScrollMenu();
    virtual ~CCScrollMenu();
    virtual void registerWithTouchDispatcher();
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
protected:
private:
};

class CCBReader;

class CCScrollMenuLoader : public cocos2d::extension::CCMenuLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCScrollMenuLoader, loader);

protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCScrollMenu);
};

