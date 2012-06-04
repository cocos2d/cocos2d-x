#ifndef _CCB_MEMBERVARIABLEASSIGNER_H_
#define _CCB_MEMBERVARIABLEASSIGNER_H_

#include "cocos2d.h"

NS_CC_EXT_BEGIN

class CCBMemberVariableAssigner {
    public:
        virtual bool onAssignCCBMemberVariable(CCObject * pTarget, std::string pMemberVariableName, CCNode * pNode) = 0;
};

NS_CC_EXT_END

#endif
