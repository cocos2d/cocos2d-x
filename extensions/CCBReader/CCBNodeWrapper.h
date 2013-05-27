#ifndef _CCB_CCBNODEWRAPPER_H_
#define _CCB_CCBNODEWRAPPER_H_

#include "cocos2d.h"
#include "CCBValue.h"

NS_CC_EXT_BEGIN

class CCBNodeWrapper {
    public:
        virtual ~CCBNodeWrapper() {};

        /**
         *  Unwraps the node contained within this wrapper
         *  @note The member variable must be CCNode or its subclass.
         *  @param pTarget The custom class.
         *  @param pMemberVariableName The name of the member variable.
         *  @param pNode The member variable.
         *  @return Whether the assignment was successful.
         */
        virtual CCNode* unwrapNode() = 0;
};

NS_CC_EXT_END

#endif
