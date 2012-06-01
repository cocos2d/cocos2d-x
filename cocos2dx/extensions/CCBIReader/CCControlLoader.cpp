#import "CCControlLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define PROPERTY_ENABLED "enabled"
#define PROPERTY_SELECTED "selected"
#define PROPERTY_CCCONTROL "ccControl"

void CCControlLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, std::string pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_ENABLED) == 0) {
        ((CCControl *)pNode)->setIsEnabled(pCheck);
    } else if(pPropertyName.compare(PROPERTY_SELECTED) == 0) {
        ((CCControl *)pNode)->setIsSelected(pCheck);
    } else {
        CCNodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

void CCControlLoader::onHandlePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, std::string pPropertyName, void * pBlockCCControl, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_CCCONTROL) == 0) {
        // TODO selector thingy...
        // ((CCControl *)pNode)->setTarget(???, ???);
    } else {
        CCNodeLoader::onHandlePropTypeBlockCCControl(pNode, pParent, pPropertyName, pBlockCCControl, pCCBReader);
    }
}