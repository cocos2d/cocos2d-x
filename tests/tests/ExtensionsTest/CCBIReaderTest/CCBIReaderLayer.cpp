#include "CCBIReaderLayer.h"
#include "CCBReader.h"
#include "CCNodeLoaderLibrary.h"

using namespace cocos2d;
using namespace cocos2d::extension;

CCBIReaderLayer * CCBIReaderLayer::node() {
    CCBIReaderLayer *pRet = new CCBIReaderLayer();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool CCBIReaderLayer::init() {
    return CCLayer::init();
}

void CCBIReaderLayer::menuCloseCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool CCBIReaderLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    if(pTarget == this) {
        if(strcmp(pMemberVariableName, "mCCControlButton") == 0) {
            this->mCCControlButton = dynamic_cast<CCControlButton *>(pNode);
            return true;
        } else if(strcmp(pMemberVariableName, "mCCMenuItemImage") == 0) {
            this->mCCMenuItemImage = dynamic_cast<CCMenuItemImage *>(pNode);
            return true;
        }
    }
    return false;
}

SEL_CCControlHandler CCBIReaderLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    if(pTarget == this) {
        if(strcmp(pSelectorName, "onCCControlButtonClicked") == 0) {
            return cccontrol_selector(CCBIReaderLayer::onCCControlButtonClicked);
        }
    }
    return NULL;
}

SEL_MenuHandler CCBIReaderLayer::onResolveCCBCCMenuSelector(CCObject * pTarget, const char * pSelectorName) {
    if(pTarget == this) {
        if(strcmp(pSelectorName, "onCCMenuItemImageClicked") == 0) {
            return menu_selector(CCBIReaderLayer::onCCMenuItemImageClicked);
        }
    }
    return NULL;
}

void CCBIReaderLayer::onCCControlButtonClicked(CCObject * pSender, CCControlEvent pCCControlEvent) {
    switch(pCCControlEvent) {
        case CCControlEventTouchDown:
            CCLOG("onCCControlButtonClicked: Touch Down.");
            break;
        case CCControlEventTouchDragInside:
            CCLOG("onCCControlButtonClicked: Touch Drag Inside.");
            break;
        case CCControlEventTouchDragOutside:
            CCLOG("onCCControlButtonClicked: Touch Drag Outside.");
            break;
        case CCControlEventTouchDragEnter:
            CCLOG("onCCControlButtonClicked: Touch Drag Enter.");
            break;
        case CCControlEventTouchDragExit:
            CCLOG("onCCControlButtonClicked: Touch Drag Exit.");
            break;
        case CCControlEventTouchUpInside:
            CCLOG("onCCControlButtonClicked: Touch Up Inside.");
            break;
        case CCControlEventTouchUpOutside:
            CCLOG("onCCControlButtonClicked: Touch Up Outside.");
            break;
        case CCControlEventTouchCancel:
            CCLOG("onCCControlButtonClicked: Touch Cancel.");
            break;
        case CCControlEventValueChanged:
            CCLOG("onCCControlButtonClicked: Value Changed.");
            break;
        default:
            assert(false); // OH SHIT!
    }
}

void CCBIReaderLayer::onCCMenuItemImageClicked(CCObject * pSender) {
    CCLOG("onCCMenuItemImageClicked!");
}