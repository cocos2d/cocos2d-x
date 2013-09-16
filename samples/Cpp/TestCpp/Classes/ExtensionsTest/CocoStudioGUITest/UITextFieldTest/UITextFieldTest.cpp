

#include "UITextFieldTest.h"

const char* font_UITextFieldTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

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
        Size widgetSize = m_pWidget->getSize();
        
        // Add a label in which the textfield events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName(font_UITextFieldTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);        
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("TextField");
        alert->setFontName(font_UITextFieldTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        // Create the textfield
        UITextField* textField = UITextField::create();
        textField->setTouchEnabled(true);
        textField->setFontName(font_UITextFieldTest);
        textField->setFontSize(30);
        textField->setPlaceHolder("input words here");
        textField->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textField->addAttachWithIMEEvent(this, coco_TextField_AttachWithIME_selector(UITextFieldTest::attachWithIMEEvent));
        textField->addDetachWithIMEEvent(this, coco_TextField_DetachWithIME_selector(UITextFieldTest::detachWithIMEEvent));
        textField->addInsertTextEvent(this, coco_TextField_InsertText_selector(UITextFieldTest::insertTextEvent));
        textField->addDeleteBackwardEvent(this, coco_TextField_DeleteBackward_selector(UITextFieldTest::deleteBackwardEvent));
        m_pUiLayer->addWidget(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest::attachWithIMEEvent(Object *pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    Size screenSize = CCDirector::getInstance()->getWinSize();
    textField->runAction(CCMoveTo::create(0.225,
                                          Point(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2)));
    m_pDisplayValueLabel->setText(CCString::createWithFormat("attach with IME")->getCString());
}

void UITextFieldTest::detachWithIMEEvent(Object* pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    Size screenSize = CCDirector::getInstance()->getWinSize();
    textField->runAction(CCMoveTo::create(0.175, Point(screenSize.width / 2.0f, screenSize.height / 2.0f)));
    m_pDisplayValueLabel->setText(CCString::createWithFormat("detach with IME")->getCString());    
}

void UITextFieldTest::insertTextEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("insert words")->getCString());
}

void UITextFieldTest::deleteBackwardEvent(Object *pSender)
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
        Size screenSize = CCDirector::getInstance()->getWinSize();
        
        // Add a label in which the textfield events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName(font_UITextFieldTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f + m_pDisplayValueLabel->getSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("TextField max length");
        alert->setFontName(font_UITextFieldTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getSize().height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        // Create the textfield
        UITextField* textField = UITextField::create();
        textField->setMaxLengthEnable(true);
        textField->setMaxLength(3);
        textField->setTouchEnabled(true);
        textField->setFontName(font_UITextFieldTest);
        textField->setFontSize(30);
        textField->setPlaceHolder("input words here");
        textField->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f));
        textField->addAttachWithIMEEvent(this, coco_TextField_AttachWithIME_selector(UITextFieldTest_MaxLength::attachWithIMEEvent));
        textField->addDetachWithIMEEvent(this, coco_TextField_DetachWithIME_selector(UITextFieldTest_MaxLength::detachWithIMEEvent));
        textField->addInsertTextEvent(this, coco_TextField_InsertText_selector(UITextFieldTest_MaxLength::insertTextEvent));
        textField->addDeleteBackwardEvent(this, coco_TextField_DeleteBackward_selector(UITextFieldTest_MaxLength::deleteBackwardEvent));
        m_pUiLayer->addWidget(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest_MaxLength::attachWithIMEEvent(Object *pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    Size screenSize = CCDirector::getInstance()->getWinSize();
    textField->runAction(CCMoveTo::create(0.225,
                                          Point(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2)));
    m_pDisplayValueLabel->setText(CCString::createWithFormat("attach with IME max length %d", textField->getMaxLength())->getCString());
}

void UITextFieldTest_MaxLength::detachWithIMEEvent(Object* pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    Size screenSize = CCDirector::getInstance()->getWinSize();
    textField->runAction(CCMoveTo::create(0.175, Point(screenSize.width / 2.0f, screenSize.height / 2.0f)));
    m_pDisplayValueLabel->setText(CCString::createWithFormat("detach with IME max length %d", textField->getMaxLength())->getCString());
}

void UITextFieldTest_MaxLength::insertTextEvent(Object *pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    m_pDisplayValueLabel->setText(CCString::createWithFormat("insert words max length %d", textField->getMaxLength())->getCString());
}

void UITextFieldTest_MaxLength::deleteBackwardEvent(Object *pSender)
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
        Size screenSize = CCDirector::getInstance()->getWinSize();
        
        // Add a label in which the textfield events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName(font_UITextFieldTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f + m_pDisplayValueLabel->getSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("TextField password");
        alert->setFontName(font_UITextFieldTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getSize().height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        // Create the textfield
        UITextField* textField = UITextField::create();
        textField->setPasswordEnable(true);
        textField->setPasswordStyleText("*");
        textField->setTouchEnabled(true);
        textField->setFontName(font_UITextFieldTest);
        textField->setFontSize(30);
        textField->setPlaceHolder("input password here");
        textField->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f));
        textField->addAttachWithIMEEvent(this, coco_TextField_AttachWithIME_selector(UITextFieldTest_Password::attachWithIMEEvent));
        textField->addDetachWithIMEEvent(this, coco_TextField_DetachWithIME_selector(UITextFieldTest_Password::detachWithIMEEvent));
        textField->addInsertTextEvent(this, coco_TextField_InsertText_selector(UITextFieldTest_Password::insertTextEvent));
        textField->addDeleteBackwardEvent(this, coco_TextField_DeleteBackward_selector(UITextFieldTest_Password::deleteBackwardEvent));
        m_pUiLayer->addWidget(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest_Password::attachWithIMEEvent(Object *pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    Size screenSize = CCDirector::getInstance()->getWinSize();
    textField->runAction(CCMoveTo::create(0.225,
                                          Point(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2)));
    m_pDisplayValueLabel->setText(CCString::createWithFormat("attach with IME password")->getCString());
}

void UITextFieldTest_Password::detachWithIMEEvent(Object* pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
    Size screenSize = CCDirector::getInstance()->getWinSize();
    textField->runAction(CCMoveTo::create(0.175, Point(screenSize.width / 2.0f, screenSize.height / 2.0f)));
    m_pDisplayValueLabel->setText(CCString::createWithFormat("detach with IME password")->getCString());
}

void UITextFieldTest_Password::insertTextEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("insert words password")->getCString());
}

void UITextFieldTest_Password::deleteBackwardEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("delete word password")->getCString());
}
