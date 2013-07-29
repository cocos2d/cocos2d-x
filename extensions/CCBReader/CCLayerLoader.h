#ifndef _CCB_CCLAYERLOADER_H_
#define _CCB_CCLAYERLOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class LayerLoader : public NodeLoader {
    public:
        virtual ~LayerLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Layer);

        virtual void onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader);
};

NS_CC_EXT_END

#endif
