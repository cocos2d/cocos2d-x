#include "CCLayerGradientLoader.h"



#define PROPERTY_STARTCOLOR "startColor"
#define PROPERTY_ENDCOLOR "endColor"
#define PROPERTY_STARTOPACITY "startOpacity"
#define PROPERTY_ENDOPACITY "endOpacity"
#define PROPERTY_VECTOR "vector"
#define PROPERTY_BLENDFUNC "blendFunc"

NS_CC_EXT_BEGIN

void CCLayerGradientLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_STARTCOLOR) == 0) {
        ((CCLayerGradient *)pNode)->setStartColor(pCCColor3B);
    } else if(strcmp(pPropertyName, PROPERTY_ENDCOLOR) == 0) {
        ((CCLayerGradient *)pNode)->setEndColor(pCCColor3B);
    } else {
        CCLayerLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void CCLayerGradientLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_STARTOPACITY) == 0) {
        ((CCLayerGradient *)pNode)->setStartOpacity(pByte);
    } else if(strcmp(pPropertyName, PROPERTY_ENDOPACITY) == 0) {
        ((CCLayerGradient *)pNode)->setEndOpacity(pByte);
    } else {
        CCLayerLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void CCLayerGradientLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((CCLayerGradient *)pNode)->setBlendFunc(pCCBlendFunc);
    } else {
        CCLayerLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}


void CCLayerGradientLoader::onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPoint, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_VECTOR) == 0) {
        ((CCLayerGradient *)pNode)->setVector(pPoint);

        // TODO Not passed along the ccbi file.
        // ((CCLayerGradient *)pNode)->setCompressedInterpolation(true);
    } else {
        CCLayerLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, pCCBReader);
    }
}

NS_CC_EXT_END
