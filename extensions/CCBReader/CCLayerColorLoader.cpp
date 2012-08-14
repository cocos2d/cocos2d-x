#include "CCLayerColorLoader.h"

USING_NS_CC;

NS_CC_EXT_BEGIN

#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"

void CCLayerColorLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_COLOR) == 0) {
        ((CCLayerColor *)pNode)->setColor(pCCColor3B);
    } else {
        CCLayerLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void CCLayerColorLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_OPACITY) == 0) {
        ((CCLayerColor *)pNode)->setOpacity(pByte);
    } else {
        CCLayerLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void CCLayerColorLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_BLENDFUNC) == 0) {
        ((CCLayerColor *)pNode)->setBlendFunc(pCCBlendFunc);
    } else {
        CCLayerLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}

NS_CC_EXT_END