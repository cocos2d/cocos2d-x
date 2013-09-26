#ifndef _CCB_CCMENULOADER_H_
#define _CCB_CCMENULOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;
/**
 *  @js NA
 *  @lua NA
 */
class CCMenuLoader : public CCLayerLoader {
    public:
        virtual ~CCMenuLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCMenuLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCMenu);
};

NS_CC_EXT_END

#endif
