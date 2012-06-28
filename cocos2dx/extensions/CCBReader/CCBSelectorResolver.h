#ifndef _CCB_CCBSELECTORRESOLVER_H_
#define _CCB_CCBSELECTORRESOLVER_H_

#include "cocos2d.h"

NS_CC_EXT_BEGIN

#define CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(TARGET, SELECTORNAME, METHOD) if(pTarget == TARGET && pSelectorName->compare(SELECTORNAME) == 0) { \
    return menu_selector(METHOD); \
}

#define CCB_SELECTORRESOLVER_CCCONTROL_GLUE(TARGET, SELECTORNAME, METHOD) if(pTarget == TARGET && pSelectorName->compare(SELECTORNAME) == 0) { \
    return cccontrol_selector(METHOD); \
}

class CC_DLL CCBSelectorResolver {
    public:
        virtual ~CCBSelectorResolver() {};

        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) = 0;
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) = 0;
};

NS_CC_EXT_END

#endif
