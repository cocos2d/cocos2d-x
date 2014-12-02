#include "CCScale9SpriteLoader.h"

using namespace cocos2d;
using namespace cocos2d::ui;

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

namespace spritebuilder {

void Scale9SpriteLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_SPRITEFRAME) == 0) {
//        ((Scale9Sprite *)pNode)->setSpriteFrame(pSpriteFrame);
        if (pSpriteFrame) {
            _spriteFrame = pSpriteFrame;
            _spriteFrame->retain();
        }

    } else {
        NodeLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, ccbReader);
    }
}

void Scale9SpriteLoader::onHandlePropTypeColor4(Node * pNode, Node * pParent, const char * pPropertyName, Color4F pColor4F, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((Scale9Sprite *)pNode)->setColor(Color3B(pColor4F.r * 255, pColor4F.g * 255, pColor4F.b * 255));
    } else {
        NodeLoader::onHandlePropTypeColor4(pNode, pParent, pPropertyName, pColor4F, ccbReader);
    }
}

void Scale9SpriteLoader::onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        ((Scale9Sprite *)pNode)->setOpacity(pByte);
    } else {
        NodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, ccbReader);
    }
}

void Scale9SpriteLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        // TODO Not exported by CocosBuilder yet!
        //((Scale9Sprite *)pNode)->setBlendFunc(pBlendFunc);
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pBlendFunc, ccbReader);
    }
}

void Scale9SpriteLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_CONTENTSIZE) == 0) {
        _contentSize = pSize;
    } else if(strcmp(pPropertyName, PROPERTY_PREFEREDSIZE) == 0) {
        this->_preferedSize = pSize;
    } else {
        NodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, ccbReader);
    }
}

void Scale9SpriteLoader::onHandlePropTypeFloat(Node * pNode, Node * pParent, const char * pPropertyName, float pFloat, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_INSETLEFT) == 0) {
        this->_insetLeft = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_INSETTOP) == 0) {
        this->_insetTop = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_INSETRIGHT) == 0) {
        this->_insetRight = pFloat;
    } else if(strcmp(pPropertyName, PROPERTY_INSETBOTTOM) == 0) {
        this->_insetBottom = pFloat;
    } else {
        NodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, ccbReader);
    }
}
void Scale9SpriteLoader::onDone(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader) {
    if (_spriteFrame)
        ((Scale9Sprite *)pNode)->setSpriteFrame(_spriteFrame);
    ((Scale9Sprite *)pNode)->setContentSize(_contentSize);
    ((Scale9Sprite *)pNode)->setPreferredSize(_contentSize);
    
    ((Scale9Sprite *)pNode)->setInsetLeft(_insetLeft);
    ((Scale9Sprite *)pNode)->setInsetTop(_insetTop);
    ((Scale9Sprite *)pNode)->setInsetRight(_insetRight);
    ((Scale9Sprite *)pNode)->setInsetBottom(_insetBottom);
    
    
    if (_spriteFrame)
        _spriteFrame->release();
}
}
