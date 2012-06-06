#ifndef _CCB_SELECTORRESOLVER_H_
#define _CCB_SELECTORRESOLVER_H_

#include "cocos2d.h"

NS_CC_EXT_BEGIN

class CCBSelectorResolver {
    public:
        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuSelector(CCObject * pTarget, const char * pSelectorName) = 0;
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) = 0;
};

NS_CC_EXT_END

#endif
