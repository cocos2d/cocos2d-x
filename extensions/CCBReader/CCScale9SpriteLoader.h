#ifndef _CCB_CCSCALE9SPRITELOADER_H_
#define _CCB_CCSCALE9SPRITELOADER_H_

#include "CCNodeLoader.h"
#include "CCScale9SpriteLoader.h"
#include "../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;
/**
 *  @js NA
 *  @lua NA
 */
class CC_EX_DLL CCScale9SpriteLoader : public CCNodeLoader {
    public:
        virtual ~CCScale9SpriteLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCScale9SpriteLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCScale9Sprite);

        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloat, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
