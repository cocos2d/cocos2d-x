#ifndef _CCB_CCSPRITELOADER_H_
#define _CCB_CCSPRITELOADER_H_

#include "CCNodeLoader.h"

namespace spritebuilder {

/* Forward declaration. */
class CCBReader;

class SpriteLoader : public NodeLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~SpriteLoader() {};
    /**
     * @js NA
     * @lua NA
     */
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SpriteLoader, loader);

protected:
    SB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::Sprite);

    virtual void onHandlePropTypeColor4(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color4F pColor4F, CCBReader * ccbReader);
    virtual void onHandlePropTypeByte(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader);
    virtual void onHandlePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::BlendFunc pCCBBlendFunc, CCBReader * ccbReader);
    virtual void onHandlePropTypeSpriteFrame(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
    virtual void onHandlePropTypeFlip(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, bool * pFlip, CCBReader * ccbReader);
};

}

#endif
