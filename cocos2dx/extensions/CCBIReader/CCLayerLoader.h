#ifndef _CCLAYER_LOADER_H_
#define _CCLAYER_LOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCLayerLoader : public CCNodeLoader {
    protected:
        virtual cocos2d::CCLayer * createCCNode(cocos2d::CCNode *, CCBReader *);

        virtual void onHandlePropTypeCheck(CCNode *, CCNode *, std::string, bool, CCBReader *);
};

NS_CC_EXT_END

#endif
