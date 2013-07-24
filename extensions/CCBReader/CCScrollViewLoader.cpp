#include "CCScrollViewLoader.h"



#define PROPERTY_CONTAINER "container"
#define PROPERTY_DIRECTION "direction"
#define PROPERTY_CLIPSTOBOUNDS "clipsToBounds"
#define PROPERTY_BOUNCES "bounces"
#define PROPERTY_SCALE "scale"

NS_CC_EXT_BEGIN

void ScrollViewLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * pCCBReader) {
	if(strcmp(pPropertyName, PROPERTY_CONTENTSIZE) == 0) {
		((ScrollView *)pNode)->setViewSize(pSize);
	} else {
		NodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, pCCBReader);
	}
}

void ScrollViewLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_CLIPSTOBOUNDS) == 0) {
        ((ScrollView *)pNode)->setClippingToBounds(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_BOUNCES) == 0) {
        ((ScrollView *)pNode)->setBounceable(pCheck);
    } else {
        NodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

void ScrollViewLoader::onHandlePropTypeCCBFile(Node * pNode, Node * pParent, const char * pPropertyName, Node * pCCBFileNode, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_CONTAINER) == 0) {
        ((ScrollView *)pNode)->setContainer(pCCBFileNode);
		((ScrollView *)pNode)->updateInset();
    } else {
        NodeLoader::onHandlePropTypeCCBFile(pNode, pParent, pPropertyName, pCCBFileNode, pCCBReader);
    }
}

void ScrollViewLoader::onHandlePropTypeFloat(Node * pNode, Node * pParent, const char * pPropertyName, float pFloat, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_SCALE) == 0) {
        ((ScrollView *)pNode)->setScale(pFloat);
    } else {
        NodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void ScrollViewLoader::onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_DIRECTION) == 0) {
        ((ScrollView *)pNode)->setDirection(ScrollViewDirection(pIntegerLabeled));
    } else {
        NodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

NS_CC_EXT_END