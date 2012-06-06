#ifndef _CCLAYER_LOADER_H_
#define _CCLAYER_LOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCLayerLoader : public CCNodeLoader {
    public:
        STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCLayerLoader, loader);

    protected:
        virtual CCLayer * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool, CCBReader *);
};

NS_CC_EXT_END

#endif
