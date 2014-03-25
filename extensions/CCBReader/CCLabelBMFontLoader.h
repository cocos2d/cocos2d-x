#ifndef _CCB_CCLABELBMFONTLOADER_H_
#define _CCB_CCLABELBMFONTLOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;
/**
 *  @js NA
 *  @lua NA
 */
class CC_EX_DLL CCLabelBMFontLoader : public CCNodeLoader {
    public:
        virtual ~CCLabelBMFontLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCLabelBMFontLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCLabelBMFont);

        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFntFile(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char* pFntFile, CCBReader * pCCBReader);
        virtual void onHandlePropTypeText(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char* pText, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
