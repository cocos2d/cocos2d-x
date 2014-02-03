#include "CCSpriteLoader.h"

using namespace cocos2d;

#define PROPERTY_FLIP "flip"
#define PROPERTY_DISPLAYFRAME "displayFrame"
#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"

namespace cocosbuilder {

void SpriteLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_DISPLAYFRAME) == 0) {
        if(pSpriteFrame != NULL) {
            ((Sprite *)pNode)->setSpriteFrame(pSpriteFrame);
        } else {
            CCLOG("ERROR: SpriteFrame NULL");
        }
    } else {
        NodeLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, ccbReader);
    }
}

void SpriteLoader::onHandlePropTypeFlip(Node * pNode, Node * pParent, const char * pPropertyName, bool * pFlip, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_FLIP) == 0) {
        ((Sprite *)pNode)->setFlippedX(pFlip[0]);
        ((Sprite *)pNode)->setFlippedY(pFlip[1]);
    } else {
        NodeLoader::onHandlePropTypeFlip(pNode, pParent, pPropertyName, pFlip, ccbReader);
    }
}

void SpriteLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, Color3B pColor3B, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((Sprite *)pNode)->setColor(pColor3B);
    } else {
        NodeLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pColor3B, ccbReader);
    }
}

void SpriteLoader::onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        ((Sprite *)pNode)->setOpacity(pByte);
    } else {
        NodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, ccbReader);
    }
}

void SpriteLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((Sprite *)pNode)->setBlendFunc(pBlendFunc);
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pBlendFunc, ccbReader);
    }
}

}
