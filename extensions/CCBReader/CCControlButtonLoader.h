#ifndef _CCB_CCCONTROLBUTTONLOADER_H_
#define _CCB_CCCONTROLBUTTONLOADER_H_

#include "CCControlLoader.h"
#include "../GUI/CCControlExtension/CCControlButton.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCControlButtonLoader : public CCControlLoader {
    public:
        virtual ~CCControlButtonLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCControlButtonLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCControlButton);

        virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool pCheck, CCBReader * pCCBReader);
        virtual void onHandlePropTypeString(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pString, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pFontTTF, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pFloatScale, CCBReader * pCCBReader);
        virtual void onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCPoint pPoint, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSize pSize, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader);
        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
