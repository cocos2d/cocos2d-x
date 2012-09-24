#ifndef _CCB_CCBMEMBERVARIABLEASSIGNER_H_
#define _CCB_CCBMEMBERVARIABLEASSIGNER_H_

#include "cocos2d.h"

NS_CC_EXT_BEGIN

#define CCB_MEMBERVARIABLEASSIGNER_GLUE(TARGET, MEMBERVARIABLENAME, MEMBERVARIABLETYPE, MEMBERVARIABLE) \
    if (pTarget == TARGET && pMemberVariableName->compare(MEMBERVARIABLENAME) == 0) { \
        MEMBERVARIABLETYPE pOldVar = MEMBERVARIABLE; \
        MEMBERVARIABLE = dynamic_cast<MEMBERVARIABLETYPE>(pNode); \
        CC_ASSERT(MEMBERVARIABLE); \
        if (pOldVar != MEMBERVARIABLE) { \
            CC_SAFE_RELEASE(pOldVar); \
            MEMBERVARIABLE->retain(); \
        } \
        return true; \
    }

class CCBMemberVariableAssigner {
    public:
        virtual ~CCBMemberVariableAssigner() {};

        virtual bool onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) = 0;
};

NS_CC_EXT_END

#endif
