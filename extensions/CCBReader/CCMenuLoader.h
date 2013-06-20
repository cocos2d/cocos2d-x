#ifndef _CCB_CCMENULOADER_H_
#define _CCB_CCMENULOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class MenuLoader : public LayerLoader {
    public:
        virtual ~MenuLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MenuLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Menu);
};

NS_CC_EXT_END

#endif
