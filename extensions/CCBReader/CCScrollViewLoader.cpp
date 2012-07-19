#include "CCScrollViewLoader.h"

USING_NS_CC;

#define PROPERTY_CONTAINER "container"
#define PROPERTY_DIRECTION "direction"
#define PROPERTY_CLIPSTOBOUNDS "clipsToBounds"
#define PROPERTY_BOUNCES "bounces"
#define PROPERTY_SCALE "scale"

NS_CC_EXT_BEGIN

void CCScrollViewLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_CLIPSTOBOUNDS) == 0) {
        ((CCScrollView *)pNode)->setClippingToBounds(pCheck);
    } else if(pPropertyName->compare(PROPERTY_BOUNCES) == 0) {
        ((CCScrollView *)pNode)->setBounceable(pCheck);
    } else {
        CCNodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

void CCScrollViewLoader::onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCNode * pCCBFileNode, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_CONTAINER) == 0) {
        ((CCScrollView *)pNode)->setContainer(pCCBFileNode);
    } else {
        CCNodeLoader::onHandlePropTypeCCBFile(pNode, pParent, pPropertyName, pCCBFileNode, pCCBReader);
    }
}

void CCScrollViewLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pFloat, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_SCALE) == 0) {
        ((CCScrollView *)pNode)->setScale(pFloat);
    } else {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void CCScrollViewLoader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_DIRECTION) == 0) {
        ((CCScrollView *)pNode)->setDirection(CCScrollViewDirection(pIntegerLabeled));
    } else {
        CCNodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

NS_CC_EXT_END