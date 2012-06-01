#ifndef _CCMENU_LOADER_H_
#define _CCMENU_LOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCMenuLoader : public CCLayerLoader {
    protected:
        virtual CCMenu * createCCNode(CCNode *, CCBReader *);
};

NS_CC_EXT_END

#endif
