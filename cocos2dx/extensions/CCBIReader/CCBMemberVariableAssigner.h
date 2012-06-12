#ifndef _CCB_CCBMEMBERVARIABLEASSIGNER_H_
#define _CCB_CCBMEMBERVARIABLEASSIGNER_H_

#include "cocos2d.h"

NS_CC_EXT_BEGIN

class CCBMemberVariableAssigner {
    public:
        virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) = 0;
};

NS_CC_EXT_END

#endif
