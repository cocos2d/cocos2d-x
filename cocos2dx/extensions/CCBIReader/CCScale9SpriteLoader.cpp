#import "CCScale9SpriteLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define PROPERTY_CONTENTSIZE "contentSize"
#define PROPERTY_DISPLAYFRAME "displayFrame"
#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_DIMENSIONS "dimensions"

CCScale9Sprite * CCScale9SpriteLoader::createCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    return CCScale9Sprite::node();
}

void CCScale9SpriteLoader::onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, std::string pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_DISPLAYFRAME) == 0) {
        ((CCSprite *)pNode)->setDisplayFrame(pCCSpriteFrame);
    } else {
        CCNodeLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
    }
}

void CCScale9SpriteLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, std::string pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_COLOR) == 0) {
        ((CCScale9Sprite *)pNode)->setColor(pCCColor3B);
    } else {
        CCNodeLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void CCScale9SpriteLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, std::string pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_OPACITY) == 0) {
        ((CCScale9Sprite *)pNode)->setOpacity(pByte);
    } else {
        CCNodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void CCScale9SpriteLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, std::string pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_BLENDFUNC) == 0) {
        // TODO Not exported by CocosBuilder yet!
        // ((CCScale9Sprite *)pNode)->setBlendFunc(pCCBlendFunc);
    } else {
        CCNodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}

void CCScale9SpriteLoader::onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, std::string pPropertyName, CCSize pSize, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_CONTENTSIZE) == 0) {
        ((CCScale9Sprite *)pNode)->setContentSize(pSize);
    } else if(pPropertyName.compare(PROPERTY_DIMENSIONS) == 0) {
        ((CCScale9Sprite *)pNode)->setContentSize(pSize);
    } else {
        CCNodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, pCCBReader);
    }
}