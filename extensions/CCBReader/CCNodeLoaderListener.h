#ifndef _CCB_CCNODELOADERLISTENER_H_
#define _CCB_CCNODELOADERLISTENER_H_

#include "cocos2d.h"

NS_CC_EXT_BEGIN
/**
 *  @js NA
 *  @lua NA
 */
class CCNodeLoaderListener {
    public:
        virtual ~CCNodeLoaderListener() {};

        virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader) = 0;
};

NS_CC_EXT_END

#endif
