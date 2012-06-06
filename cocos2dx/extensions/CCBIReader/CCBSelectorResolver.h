#ifndef _CCB_SELECTORRESOLVER_H_
#define _CCB_SELECTORRESOLVER_H_

#include "cocos2d.h"

NS_CC_EXT_BEGIN

class CCBSelectorResolver {
    public:
        virtual cocos2d::SEL_MenuHandler onResolveCCBSelector(CCObject * pTarget, const char * pSelectorName) = 0;
};

NS_CC_EXT_END

#endif
