#include "ModalLayer.h"

using namespace cocos2d;

ModalLayer::~ModalLayer()
{
	CC_SAFE_RELEASE(m_frame);
}

bool ModalLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize visibleSize = pDirector->getVisibleSize();
    CCPoint origin = pDirector->getVisibleOrigin();

    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
    
	m_frame = CCLayerColor::create(ccc4(0, 0, 0, 255 *.75));
	CC_SAFE_RETAIN(m_frame);

    m_frame->setPosition(ccp(0, 0));
    this->addChild(m_frame);

	CCMenuItemFont *pCloseItem = CCMenuItemFont::create("OK", this, menu_selector(ModalLayer::menuCloseCallback) );
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    m_frame->addChild(pMenu);
    
    return true;
}

void ModalLayer::setMessage(const char* pszMsg)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
	CCSize visibleSize = pDirector->getVisibleSize();
    CCPoint origin = pDirector->getVisibleOrigin();

	CCLabelTTF *pLabel = CCLabelTTF::create(pszMsg,  "Arial", 24, CCSizeMake(0, 0), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
   pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

 
    // add the label as a child to this layer
    m_frame->addChild(pLabel, 1);
}





bool ModalLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    // can not touch on back layers
    return true;
}

void ModalLayer::menuCloseCallback(CCObject* pSender)
{
    this->removeFromParentAndCleanup(true);
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
}