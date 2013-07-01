#include "CCLayerGradientLoader.h"



#define PROPERTY_STARTCOLOR "startColor"
#define PROPERTY_ENDCOLOR "endColor"
#define PROPERTY_STARTOPACITY "startOpacity"
#define PROPERTY_ENDOPACITY "endOpacity"
#define PROPERTY_VECTOR "vector"
#define PROPERTY_BLENDFUNC "blendFunc"

NS_CC_EXT_BEGIN

void LayerGradientLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, ccColor3B pColor3B, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_STARTCOLOR) == 0) {
        ((LayerGradient *)pNode)->setStartColor(pColor3B);
    } else if(strcmp(pPropertyName, PROPERTY_ENDCOLOR) == 0) {
        ((LayerGradient *)pNode)->setEndColor(pColor3B);
    } else {
        LayerLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pColor3B, pCCBReader);
    }
}

void LayerGradientLoader::onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_STARTOPACITY) == 0) {
        ((LayerGradient *)pNode)->setStartOpacity(pByte);
    } else if(strcmp(pPropertyName, PROPERTY_ENDOPACITY) == 0) {
        ((LayerGradient *)pNode)->setEndOpacity(pByte);
    } else {
        LayerLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void LayerGradientLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, ccBlendFunc pBlendFunc, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((LayerGradient *)pNode)->setBlendFunc(pBlendFunc);
    } else {
        LayerLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pBlendFunc, pCCBReader);
    }
}


void LayerGradientLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Point pPoint, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_VECTOR) == 0) {
        ((LayerGradient *)pNode)->setVector(pPoint);

        // TODO Not passed along the ccbi file.
        // ((LayerGradient *)pNode)->setCompressedInterpolation(true);
    } else {
        LayerLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, pCCBReader);
    }
}

NS_CC_EXT_END
