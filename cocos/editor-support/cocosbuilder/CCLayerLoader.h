#ifndef _CCB_CCLAYERLOADER_H_
#define _CCB_CCLAYERLOADER_H_

#include "CCNodeLoader.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class CC_DLL LayerLoader : public NodeLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LayerLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerLoader, loader);

protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::Layer);

    virtual void onHandlePropTypeCheck(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader);
};

}

#endif
