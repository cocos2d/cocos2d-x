#ifndef _CCB_CCLAYERCOLORLOADER_H_
#define _CCB_CCLAYERCOLORLOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CC_DLL CCLayerColorLoader : public CCLayerLoader {
    public:
        STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCLayerColorLoader, loader);
    protected:
        virtual CCLayerColor * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc, CCBReader *);
};

NS_CC_EXT_END

#endif
