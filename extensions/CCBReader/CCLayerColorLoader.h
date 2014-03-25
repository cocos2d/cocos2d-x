#ifndef _CCB_CCLAYERCOLORLOADER_H_
#define _CCB_CCLAYERCOLORLOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;
/**
 *  @js NA
 *  @lua NA
 */
class CC_EX_DLL CCLayerColorLoader : public CCLayerLoader {
    public:
        virtual ~CCLayerColorLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCLayerColorLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCLayerColor);

        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
