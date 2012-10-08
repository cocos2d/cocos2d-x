#include "CCBFileLoader.h"



NS_CC_EXT_BEGIN

#define PROPERTY_CCBFILE "ccbFile"

void CCBFileLoader::onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCNode * pCCBFileNode, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_CCBFILE) == 0) {
        ((CCBFile*)pNode)->setCCBFileNode(pCCBFileNode);
    } else {
        CCNodeLoader::onHandlePropTypeCCBFile(pNode, pParent, pPropertyName, pCCBFileNode, pCCBReader);
    }
}

NS_CC_EXT_END
