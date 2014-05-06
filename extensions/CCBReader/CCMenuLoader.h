#ifndef _CCB_CCMENULOADER_H_
#define _CCB_CCMENULOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;
/**
 *  @js NA
 *  @lua NA
 */
class CC_EX_DLL CCMenuLoader : public CCLayerLoader {
    public:
        virtual ~CCMenuLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCMenuLoader, loader);

    protected:
//        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCMenu);
    
    virtual cocos2d::CCMenu * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * ccbReader) {
        cocos2d::CCMenu* pMenu = cocos2d::CCMenu::create();
        
        pMenu->setContentSize(cocos2d::CCSize(0,0));
        
        return pMenu;
    };
};

NS_CC_EXT_END

#endif
