#ifndef _CCB_CCLABELTTFLOADER_H_
#define _CCB_CCLABELTTFLOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;
/**
 *  @js NA
 *  @lua NA
 */
class CC_EX_DLL CCLabelTTFLoader : public CCNodeLoader {
    public:
        virtual ~CCLabelTTFLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCLabelTTFLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCLabelTTF);

        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * pCCBReader);
        virtual void onHandlePropTypeText(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pText, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloatScale, CCBReader * pCCBReader);
        virtual void onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
