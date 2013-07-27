#ifndef _CCB_CCSPRITELOADER_H_
#define _CCB_CCSPRITELOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class SpriteLoader : public NodeLoader {
    public:
        virtual ~SpriteLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SpriteLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Sprite);

        virtual void onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, Color3B pColor3B, CCBReader * ccbReader);
        virtual void onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader);
        virtual void onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pCCBBlendFunc, CCBReader * ccbReader);
        virtual void onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
        virtual void onHandlePropTypeFlip(Node * pNode, Node * pParent, const char * pPropertyName, bool * pFlip, CCBReader * ccbReader);
};

NS_CC_EXT_END

#endif
