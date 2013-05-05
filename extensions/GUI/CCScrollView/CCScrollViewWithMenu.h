#ifndef __CCSCROLLVIEWWITHMENU_H__
#define __CCSCROLLVIEWWITHMENU_H__

#include "cocos-ext.h"
#include "CCScrollView.h"

NS_CC_EXT_BEGIN

class CCBReader;

class CCScrollViewWithMenu : public cocos2d::extension::CCScrollView
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCScrollViewWithMenu, create);
    void registerWithTouchDispatcher();
};

class CCScrollViewWithMenuLoader : public cocos2d::extension::CCScrollViewLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCScrollViewWithMenuLoader, loader);

protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCScrollViewWithMenu);
};

NS_CC_EXT_END

#endif /* __CCSCROLLVIEWWITHMENU_H__ */