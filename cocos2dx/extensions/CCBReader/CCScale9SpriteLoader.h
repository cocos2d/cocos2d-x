#ifndef _CCB_CCSCALE9SPRITELOADER_H_
#define _CCB_CCSCALE9SPRITELOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CC_DLL CCScale9SpriteLoader : public CCNodeLoader {
    public:
        virtual ~CCScale9SpriteLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCScale9SpriteLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCScale9Sprite);

        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor3B, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, unsigned char, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSpriteFrame *, CCBReader *);
        virtual void onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSize, CCBReader *);
        virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float, CCBReader *);
};

NS_CC_EXT_END

#endif
