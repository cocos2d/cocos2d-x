#ifndef __CCSCROLLMENU_H__
#define __CCSCROLLMENU_H__

#include "cocos-ext.h"

NS_CC_EXT_BEGIN

class CCBReader;

class CCScrollMenu: public cocos2d::CCMenu
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCScrollMenu, create);

    CCScrollMenu();
    virtual ~CCScrollMenu();

    virtual void registerWithTouchDispatcher();
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};


class CCScrollMenuLoader : public cocos2d::extension::CCMenuLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCScrollMenuLoader, loader);

protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCScrollMenu);
};

NS_CC_EXT_END

#endif /* __CCSCROLLMENU_H__ */