#include "CCBFileLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define PROPERTY_CCBFILE "ccbFile"

void CCBFileLoader::onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCNode * pCCBFileNode, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_CCBFILE) == 0) {
        pNode->addChild(pCCBFileNode);
    } else {
        CCNodeLoader::onHandlePropTypeCCBFile(pNode, pParent, pPropertyName, pCCBFileNode, pCCBReader);
    }
}
