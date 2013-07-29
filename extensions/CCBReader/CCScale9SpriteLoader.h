#ifndef _CCB_CCSCALE9SPRITELOADER_H_
#define _CCB_CCSCALE9SPRITELOADER_H_

#include "CCNodeLoader.h"
#include "CCScale9SpriteLoader.h"
#include "../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class Scale9SpriteLoader : public NodeLoader {
    public:
        virtual ~Scale9SpriteLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(Scale9SpriteLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Scale9Sprite);

        virtual void onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, Color3B pColor3B, CCBReader * ccbReader);
        virtual void onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader);
        virtual void onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader);
        virtual void onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
        virtual void onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * ccbReader);
        virtual void onHandlePropTypeFloat(Node * pNode, Node * pParent, const char * pPropertyName, float pFloat, CCBReader * ccbReader);
};

NS_CC_EXT_END

#endif
