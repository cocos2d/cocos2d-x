#include "CCBFileLoader.h"



NS_CC_EXT_BEGIN

#define PROPERTY_CCBFILE "ccbFile"

void CCBFileLoader::onHandlePropTypeCCBFile(Node * pNode, Node * pParent, const char * pPropertyName, Node * pCCBFileNode, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_CCBFILE) == 0) {
        ((CCBFile*)pNode)->setCCBFileNode(pCCBFileNode);
    } else {
        NodeLoader::onHandlePropTypeCCBFile(pNode, pParent, pPropertyName, pCCBFileNode, ccbReader);
    }
}

NS_CC_EXT_END
