#ifndef _CCB_CCBSELECTORRESOLVER_H_
#define _CCB_CCBSELECTORRESOLVER_H_

#include "extensions//GUI/CCControlExtension/CCInvocation.h"


namespace cocosbuilder {

#define CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(TARGET, SELECTORNAME, METHOD) if(pTarget == TARGET && strcmp(pSelectorName, SELECTORNAME) == 0) { \
    return CC_MENU_SELECTOR(METHOD); \
}

#define CCB_SELECTORRESOLVER_CCCONTROL_GLUE(TARGET, SELECTORNAME, METHOD) if(pTarget == TARGET && strcmp(pSelectorName, SELECTORNAME) == 0) { \
    return cccontrol_selector(METHOD); \
}

#define CCB_SELECTORRESOLVER_CALLFUNC_GLUE(TARGET, SELECTORNAME, METHOD) if(pTarget == TARGET && strcmp(pSelectorName, SELECTORNAME) == 0) { \
    return CC_CALLFUNCN_SELECTOR(METHOD); \
}

class CC_DLL CCBSelectorResolver {
    public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CCBSelectorResolver() {};
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName) = 0;
    virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName) { return NULL; };
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName) = 0;
};


class CC_DLL CCBScriptOwnerProtocol {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CCBScriptOwnerProtocol() {};
    virtual CCBSelectorResolver * createNew() = 0;
};

}

#endif
