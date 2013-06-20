#include "CCLayerColorLoader.h"



NS_CC_EXT_BEGIN

#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"

void LayerColorLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, ccColor3B pColor3B, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((LayerColor *)pNode)->setColor(pColor3B);
    } else {
        LayerLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pColor3B, pCCBReader);
    }
}

void LayerColorLoader::onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        ((LayerColor *)pNode)->setOpacity(pByte);
    } else {
        LayerLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void LayerColorLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, ccBlendFunc pBlendFunc, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((LayerColor *)pNode)->setBlendFunc(pBlendFunc);
    } else {
        LayerLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pBlendFunc, pCCBReader);
    }
}

NS_CC_EXT_END