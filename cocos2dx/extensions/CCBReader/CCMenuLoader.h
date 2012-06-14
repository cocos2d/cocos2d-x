#ifndef _CCB_CCMENULOADER_H_
#define _CCB_CCMENULOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCMenuLoader : public CCLayerLoader {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCMenuLoader, loader);

    protected:
        virtual CCMenu * createCCNode(CCNode *, CCBReader *);
};

NS_CC_EXT_END

#endif
