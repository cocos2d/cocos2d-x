#include "CCLayerGradientLoader.h"

using namespace cocos2d;

#define PROPERTY_STARTCOLOR "startColor"
#define PROPERTY_ENDCOLOR "endColor"
#define PROPERTY_STARTOPACITY "startOpacity"
#define PROPERTY_ENDOPACITY "endOpacity"
#define PROPERTY_VECTOR "vector"
#define PROPERTY_BLENDFUNC "blendFunc"

namespace cocosbuilder {

void LayerGradientLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, Color3B pColor3B, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_STARTCOLOR) == 0) {
        ((LayerGradient *)pNode)->setStartColor(pColor3B);
    } else if(strcmp(pPropertyName, PROPERTY_ENDCOLOR) == 0) {
        ((LayerGradient *)pNode)->setEndColor(pColor3B);
    } else {
        LayerLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pColor3B, ccbReader);
    }
}

void LayerGradientLoader::onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_STARTOPACITY) == 0) {
        ((LayerGradient *)pNode)->setStartOpacity(pByte);
    } else if(strcmp(pPropertyName, PROPERTY_ENDOPACITY) == 0) {
        ((LayerGradient *)pNode)->setEndOpacity(pByte);
    } else {
        LayerLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, ccbReader);
    }
}

void LayerGradientLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((LayerGradient *)pNode)->setBlendFunc(pBlendFunc);
    } else {
        LayerLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pBlendFunc, ccbReader);
    }
}


void LayerGradientLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Vec2 pPoint, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_VECTOR) == 0) {
        ((LayerGradient *)pNode)->setVector(pPoint);

        // TODO: Not passed along the ccbi file.
        // ((LayerGradient *)pNode)->setCompressedInterpolation(true);
    } else {
        LayerLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, ccbReader);
    }
}

}
