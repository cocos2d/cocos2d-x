#ifndef _CCB_CCLABELTTFLOADER_H_
#define _CCB_CCLABELTTFLOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CC_DLL CCLabelTTFLoader : public CCNodeLoader {
    public:
        virtual ~CCLabelTTFLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCLabelTTFLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCLabelTTF);

        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, unsigned char pByte, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pFontTTF, CCBReader * pCCBReader);
        virtual void onHandlePropTypeText(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pText, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pFloatScale, CCBReader * pCCBReader);
        virtual void onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSize pSize, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
