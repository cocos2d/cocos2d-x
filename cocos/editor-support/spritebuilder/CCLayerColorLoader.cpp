#include "CCLayerColorLoader.h"

using namespace cocos2d;

namespace spritebuilder {

#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"

void LayerColorLoader::onHandlePropTypeColor4(Node * pNode, Node * pParent, const char * pPropertyName, Color4F pColor4F, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((LayerColor *)pNode)->setColor(Color3B(pColor4F.r * 255, pColor4F.g * 255, pColor4F.b * 255));
        ((LayerColor *)pNode)->setOpacity(pColor4F.a * 255);
    } else {
        LayerLoader::onHandlePropTypeColor4(pNode, pParent, pPropertyName, pColor4F, ccbReader);
    }
}

void LayerColorLoader::onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        ((LayerColor *)pNode)->setOpacity(pByte);
    } else {
        LayerLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, ccbReader);
    }
}

void LayerColorLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((LayerColor *)pNode)->setBlendFunc(pBlendFunc);
    } else {
        LayerLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pBlendFunc, ccbReader);
    }
}

}