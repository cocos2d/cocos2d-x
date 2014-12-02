#include "CCLayerGradientLoader.h"

using namespace cocos2d;

#define PROPERTY_STARTCOLOR "startColor"
#define PROPERTY_ENDCOLOR "endColor"
#define PROPERTY_STARTOPACITY "startOpacity"
#define PROPERTY_ENDOPACITY "endOpacity"
#define PROPERTY_VECTOR "vector"
#define PROPERTY_BLENDFUNC "blendFunc"

namespace spritebuilder {

void LayerGradientLoader::onHandlePropTypeColor4(Node * pNode, Node * pParent, const char * pPropertyName, Color4F pColor4F, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_STARTCOLOR) == 0) {
        ((LayerGradient *)pNode)->setEndColor(Color3B(pColor4F.r * 255, pColor4F.g * 255, pColor4F.b * 255));
        ((LayerGradient *)pNode)->setEndOpacity(pColor4F.a * 255);
    } else if(strcmp(pPropertyName, PROPERTY_ENDCOLOR) == 0) {
        ((LayerGradient *)pNode)->setStartColor(Color3B(pColor4F.r * 255, pColor4F.g * 255, pColor4F.b * 255));
        ((LayerGradient *)pNode)->setStartOpacity(pColor4F.a * 255);

    } else {
        LayerLoader::onHandlePropTypeColor4(pNode, pParent, pPropertyName, pColor4F, ccbReader);
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


void LayerGradientLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Point pPoint, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_VECTOR) == 0) {
        ((LayerGradient *)pNode)->setVector(pPoint);

        // TODO Not passed along the ccbi file.
        // ((LayerGradient *)pNode)->setCompressedInterpolation(true);
    } else {
        LayerLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, ccbReader);
    }
}

}
