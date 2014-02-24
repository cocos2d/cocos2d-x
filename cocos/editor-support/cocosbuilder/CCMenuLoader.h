#ifndef _CCB_CCMENULOADER_H_
#define _CCB_CCMENULOADER_H_

#include "CCLayerLoader.h"
#include "CCRef.h"
#include "CCMenu.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class MenuLoader : public LayerLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuLoader() {};
    /**
     * @js NA
     * @lua NA
     */
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MenuLoader, loader);

protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::Menu);
};

}

#endif
