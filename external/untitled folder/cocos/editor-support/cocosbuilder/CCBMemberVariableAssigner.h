#ifndef _CCB_CCBMEMBERVARIABLEASSIGNER_H_
#define _CCB_CCBMEMBERVARIABLEASSIGNER_H_


namespace cocosbuilder {

#define CCB_MEMBERVARIABLEASSIGNER_GLUE(TARGET, MEMBERVARIABLENAME, MEMBERVARIABLETYPE, MEMBERVARIABLE) \
    if (pTarget == TARGET && 0 == strcmp(pMemberVariableName, (MEMBERVARIABLENAME))) { \
        MEMBERVARIABLETYPE pOldVar = MEMBERVARIABLE; \
        MEMBERVARIABLE = dynamic_cast<MEMBERVARIABLETYPE>(pNode); \
        CC_ASSERT(MEMBERVARIABLE); \
        if (pOldVar != MEMBERVARIABLE) { \
            CC_SAFE_RELEASE(pOldVar); \
            MEMBERVARIABLE->retain(); \
        } \
        return true; \
    }

#define CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(TARGET, MEMBERVARIABLENAME, MEMBERVARIABLETYPE, MEMBERVARIABLE) \
    if (pTarget == TARGET && 0 == strcmp(pMemberVariableName, MEMBERVARIABLENAME)) { \
        MEMBERVARIABLE = dynamic_cast<MEMBERVARIABLETYPE>(pNode); \
        CC_ASSERT(MEMBERVARIABLE); \
        return true; \
    }

class CC_DLL CCBMemberVariableAssigner {
    public:
        /**
         * @js NA
         * @lua NA
         */
        virtual ~CCBMemberVariableAssigner() {};

        /**
         *  The callback function of assigning member variable.
         *  @note The member variable must be Node or its subclass.
         *  @param target               The custom class.
         *  @param memberVariableName   The name of the member variable.
         *  @param node                 The member variable.
         *  @return Whether the assignment was successful.
         */
        virtual bool onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node) = 0;

        /**
         *  The callback function of assigning custom properties.
         *  @note The member variable must be Integer, Float, Boolean or String.
         *  @param target               The custom class.
         *  @param memberVariableName   The name of the member variable.
         *  @param value                The value of the property.
         *  @return Whether the assignment was successful.
         */
        virtual bool onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value) { return false; };
};

}

#endif
