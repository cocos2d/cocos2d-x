#ifndef _CCB_CCBMEMBERVARIABLEASSIGNER_H_
#define _CCB_CCBMEMBERVARIABLEASSIGNER_H_

#include "cocos2d.h"

NS_CC_EXT_BEGIN

#define CCB_MEMBERVARIABLEASSIGNER_GLUE(TARGET, MEMBERVARIABLENAME, MEMBERVARIABLETYPE, MEMBERVARIABLE) if(pTarget == TARGET && pMemberVariableName->compare(MEMBERVARIABLENAME) == 0) { \
    MEMBERVARIABLE = dynamic_cast<MEMBERVARIABLETYPE>(pNode); \
    CC_ASSERT(MEMBERVARIABLE); \
    MEMBERVARIABLE->retain(); \
    return true; \
}

class CCBMemberVariableAssigner {
    public:
        virtual bool onAssignCCBMemberVariable(CCObject * pTarget, cocos2d::CCString * pMemberVariableName, CCNode * pNode) = 0;
};

NS_CC_EXT_END

#endif
