#include "CCScale9SpriteLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define PROPERTY_CONTENTSIZE "contentSize"
#define PROPERTY_SPRITEFRAME "spriteFrame"
#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_PREFEREDSIZE "preferedSize" // TODO Should be "preferredSize". This is a typo in cocos2d-iphone, cocos2d-x and CocosBuilder!
#define PROPERTY_INSETLEFT "insetLeft"
#define PROPERTY_INSETTOP "insetTop"
#define PROPERTY_INSETRIGHT "insetRight"
#define PROPERTY_INSETBOTTOM "insetBottom"

void CCScale9SpriteLoader::onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_SPRITEFRAME) == 0) {
        ((CCScale9Sprite *)pNode)->initWithSpriteFrame(pCCSpriteFrame);
    } else {
        CCNodeLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
    }
}

void CCScale9SpriteLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_COLOR) == 0) {
        ((CCScale9Sprite *)pNode)->setColor(pCCColor3B);
    } else {
        CCNodeLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void CCScale9SpriteLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_OPACITY) == 0) {
        ((CCScale9Sprite *)pNode)->setOpacity(pByte);
    } else {
        CCNodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void CCScale9SpriteLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_BLENDFUNC) == 0) {
        // TODO Not exported by CocosBuilder yet!
        // ((CCScale9Sprite *)pNode)->setBlendFunc(pCCBlendFunc);
    } else {
        CCNodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}

void CCScale9SpriteLoader::onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSize pSize, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_CONTENTSIZE) == 0) {
        //((CCScale9Sprite *)pNode)->setContentSize(pSize);
    } else if(pPropertyName->compare(PROPERTY_PREFEREDSIZE) == 0) {
        ((CCScale9Sprite *)pNode)->setPreferredSize(pSize);
    } else {
        CCNodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, pCCBReader);
    }
}

void CCScale9SpriteLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pFloat, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_INSETLEFT) == 0) {
        ((CCScale9Sprite *)pNode)->setInsetLeft(pFloat);
    } else if(pPropertyName->compare(PROPERTY_INSETTOP) == 0) {
        ((CCScale9Sprite *)pNode)->setInsetTop(pFloat);
    } else if(pPropertyName->compare(PROPERTY_INSETRIGHT) == 0) {
        ((CCScale9Sprite *)pNode)->setInsetRight(pFloat);
    } else if(pPropertyName->compare(PROPERTY_INSETBOTTOM) == 0) {
        ((CCScale9Sprite *)pNode)->setInsetBottom(pFloat);
    } else {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}