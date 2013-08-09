

#include "UITextFieldTest.h"

// UITextFieldTest
UITextFieldTest::UITextFieldTest()
: m_pDisplayValueLabel(NULL)
{
    
}

UITextFieldTest::~UITextFieldTest()
{
}

bool UITextFieldTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the textfield events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getRect().size.height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);        
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("TextField");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        // Create the textfield
        UITextField* textField = UITextField::create();
        textField->setTouchEnable(true);
        textField->setFontName("Marker Felt");
        textField->setFontSize(30);
        textField->setPlaceHolder("input words here");
        textField->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textField->addAttachWithIMEEvent(this, coco_TextField_AttachWithIME_selector(UITextFieldTest::attachWithIMEEvent));
        textField->addDetachWithIMEEvent(this, coco_TextField_DetachWithIME_selector(UITextFieldTest::detachWithIMEEvent));
        textField->addInsertTextEvent(this, coco_TextField_InsertText_selector(UITextFieldTest::insertTextEvent));
        textField->addDeleteBackwardEvent(this, coco_TextField_DeleteBackward_selector(UITextFieldTest::deleteBackwardEvent));
        m_pUiLayer->addWidget(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest::attachWithIMEEvent(CCObject *pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    textField->runAction(CCMoveTo::create(0.225,
                                          ccp(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2)));
    m_pDisplayValueLabel->setText(CCString::createWithFormat("attach with IME")->getCString());
}

void UITextFieldTest::detachWithIMEEvent(CCObject* pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    textField->runAction(CCMoveTo::create(0.175, ccp(screenSize.width / 2.0f, screenSize.height / 2.0f)));
    m_pDisplayValueLabel->setText(CCString::createWithFormat("detach with IME")->getCString());    
}

void UITextFieldTest::insertTextEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("insert words")->getCString());
}

void UITextFieldTest::deleteBackwardEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("delete word")->getCString());
}

// UITextFieldTest_MaxLength
UITextFieldTest_MaxLength::UITextFieldTest_MaxLength()
: m_pDisplayValueLabel(NULL)
{
    
}

UITextFieldTest_MaxLength::~UITextFieldTest_MaxLength()
{
}

bool UITextFieldTest_MaxLength::init()
{
    if (UIScene::init())
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        // Add a label in which the textfield events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f + m_pDisplayValueLabel->getRect().size.height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("TextField max length");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        // Create the textfield
        UITextField* textField = UITextField::create();
        textField->setMaxLengthEnable(true);
        textField->setMaxLength(3);
        textField->setTouchEnable(true);
        textField->setFontName("Marker Felt");
        textField->setFontSize(30);
        textField->setPlaceHolder("input words here");
        textField->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
        textField->addAttachWithIMEEvent(this, coco_TextField_AttachWithIME_selector(UITextFieldTest_MaxLength::attachWithIMEEvent));
        textField->addDetachWithIMEEvent(this, coco_TextField_DetachWithIME_selector(UITextFieldTest_MaxLength::detachWithIMEEvent));
        textField->addInsertTextEvent(this, coco_TextField_InsertText_selector(UITextFieldTest_MaxLength::insertTextEvent));
        textField->addDeleteBackwardEvent(this, coco_TextField_DeleteBackward_selector(UITextFieldTest_MaxLength::deleteBackwardEvent));
        m_pUiLayer->addWidget(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest_MaxLength::attachWithIMEEvent(CCObject *pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    textField->runAction(CCMoveTo::create(0.225,
                                          ccp(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2)));
    m_pDisplayValueLabel->setText(CCString::createWithFormat("attach with IME max length %d", textField->getMaxLength())->getCString());
}

void UITextFieldTest_MaxLength::detachWithIMEEvent(CCObject* pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    textField->runAction(CCMoveTo::create(0.175, ccp(screenSize.width / 2.0f, screenSize.height / 2.0f)));
    m_pDisplayValueLabel->setText(CCString::createWithFormat("detach with IME max length %d", textField->getMaxLength())->getCString());
}

void UITextFieldTest_MaxLength::insertTextEvent(CCObject *pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    m_pDisplayValueLabel->setText(CCString::createWithFormat("insert words max length %d", textField->getMaxLength())->getCString());
}

void UITextFieldTest_MaxLength::deleteBackwardEvent(CCObject *pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    m_pDisplayValueLabel->setText(CCString::createWithFormat("delete word max length %d", textField->getMaxLength())->getCString());
}

// UITextFieldTest_Password
UITextFieldTest_Password::UITextFieldTest_Password()
: m_pDisplayValueLabel(NULL)
{
    
}

UITextFieldTest_Password::~UITextFieldTest_Password()
{
}

bool UITextFieldTest_Password::init()
{
    if (UIScene::init())
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        // Add a label in which the textfield events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f + m_pDisplayValueLabel->getRect().size.height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("TextField password");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        // Create the textfield
        UITextField* textField = UITextField::create();
        textField->setPasswordEnable(true);
        textField->setPasswordStyleText("*");
        textField->setTouchEnable(true);
        textField->setFontName("Marker Felt");
        textField->setFontSize(30);
        textField->setPlaceHolder("input password here");
        textField->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
        textField->addAttachWithIMEEvent(this, coco_TextField_AttachWithIME_selector(UITextFieldTest_Password::attachWithIMEEvent));
        textField->addDetachWithIMEEvent(this, coco_TextField_DetachWithIME_selector(UITextFieldTest_Password::detachWithIMEEvent));
        textField->addInsertTextEvent(this, coco_TextField_InsertText_selector(UITextFieldTest_Password::insertTextEvent));
        textField->addDeleteBackwardEvent(this, coco_TextField_DeleteBackward_selector(UITextFieldTest_Password::deleteBackwardEvent));
        m_pUiLayer->addWidget(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest_Password::attachWithIMEEvent(CCObject *pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    textField->runAction(CCMoveTo::create(0.225,
                                          ccp(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2)));
    m_pDisplayValueLabel->setText(CCString::createWithFormat("attach with IME password")->getCString());
}

void UITextFieldTest_Password::detachWithIMEEvent(CCObject* pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    textField->runAction(CCMoveTo::create(0.175, ccp(screenSize.width / 2.0f, screenSize.height / 2.0f)));
    m_pDisplayValueLabel->setText(CCString::createWithFormat("detach with IME password")->getCString());
}

void UITextFieldTest_Password::insertTextEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("insert words password")->getCString());
}

void UITextFieldTest_Password::deleteBackwardEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("delete word password")->getCString());
}
