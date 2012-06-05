#import "CCBFileLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define PROPERTY_CCBFILE "ccbFile"

CCNode * CCBFileLoader::createCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    return CCNode::node();
}

void CCBFileLoader::onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCNode * pCCBFileNode, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_CCBFILE) == 0) {
        pNode->addChild(pCCBFileNode);
    } else {
        CCNodeLoader::onHandlePropTypeCCBFile(pNode, pParent, pPropertyName, pCCBFileNode, pCCBReader);
    }
}
