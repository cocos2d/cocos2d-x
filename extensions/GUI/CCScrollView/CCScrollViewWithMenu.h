#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCScrollView.h"
class CCScrollViewWithMenu :public cocos2d::extension::CCScrollView {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCScrollViewWithMenu, create);
    void registerWithTouchDispatcher();
protected:
private:
};

class CCBReader;
class CCScrollViewWithMenuLoader : public cocos2d::extension::CCScrollViewLoader {
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCScrollViewWithMenuLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCScrollViewWithMenu);
};
