#ifndef _CCB_CCLAYERCOLORLOADER_H_
#define _CCB_CCLAYERCOLORLOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class LayerColorLoader : public LayerLoader {
    public:
        virtual ~LayerColorLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerColorLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerColor);

        virtual void onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, ccColor3B pColor3B, CCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, ccBlendFunc pBlendFunc, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
