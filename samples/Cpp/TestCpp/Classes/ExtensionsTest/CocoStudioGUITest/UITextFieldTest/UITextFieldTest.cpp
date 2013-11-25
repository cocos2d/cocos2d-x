

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
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the textfield events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName(font_UITextFieldTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getRect().size.height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);        
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("TextField");
        alert->setFontName(font_UITextFieldTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        // Create the textfield
        UITextField* textField = UITextField::create();
        textField->setTouchEnable(true);
        textField->setFontName(font_UITextFieldTest);
        textField->setFontSize(30);
        textField->setPlaceHolder("input words here");
        textField->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textField->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest::textFieldEvent));
        m_pUiLayer->addWidget(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest::textFieldEvent(CCObject *pSender, TextFiledEventType type)
{
    switch (type)
    {
        case TEXTFIELD_EVENT_ATTACH_WITH_IME:
        {
            UITextField* textField = dynamic_cast<UITextField*>(pSender);
            CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
            textField->runAction(CCMoveTo::create(0.225,
                                                  ccp(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2)));
            m_pDisplayValueLabel->setText(CCString::createWithFormat("attach with IME")->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_DETACH_WITH_IME:
        {
            UITextField* textField = dynamic_cast<UITextField*>(pSender);
            CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
            textField->runAction(CCMoveTo::create(0.175, ccp(screenSize.width / 2.0f, screenSize.height / 2.0f)));
            m_pDisplayValueLabel->setText(CCString::createWithFormat("detach with IME")->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_INSERT_TEXT:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("insert words")->getCString());
            break;
            
        case TEXTFIELD_EVENT_DELETE_BACKWARD:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("delete word")->getCString());
            break;
            
        default:
            break;
    }
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
        m_pDisplayValueLabel->setFontName(font_UITextFieldTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f + m_pDisplayValueLabel->getRect().size.height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("TextField max length");
        alert->setFontName(font_UITextFieldTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        // Create the textfield
        UITextField* textField = UITextField::create();
        textField->setMaxLengthEnable(true);
        textField->setMaxLength(3);
        textField->setTouchEnable(true);
        textField->setFontName(font_UITextFieldTest);
        textField->setFontSize(30);
        textField->setPlaceHolder("input words here");
        textField->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
        textField->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_MaxLength::textFieldEvent));
        m_pUiLayer->addWidget(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest_MaxLength::textFieldEvent(CCObject *pSender, TextFiledEventType type)
{
    switch (type)
    {
        case TEXTFIELD_EVENT_ATTACH_WITH_IME:
        {
            UITextField* textField = dynamic_cast<UITextField*>(pSender);
            CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
            textField->runAction(CCMoveTo::create(0.225,
                                                  ccp(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2)));
            m_pDisplayValueLabel->setText(CCString::createWithFormat("attach with IME max length %d", textField->getMaxLength())->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_DETACH_WITH_IME:
        {
            UITextField* textField = dynamic_cast<UITextField*>(pSender);
            CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
            textField->runAction(CCMoveTo::create(0.175, ccp(screenSize.width / 2.0f, screenSize.height / 2.0f)));
            m_pDisplayValueLabel->setText(CCString::createWithFormat("detach with IME max length %d", textField->getMaxLength())->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_INSERT_TEXT:
        {
            UITextField* textField = dynamic_cast<UITextField*>(pSender);
            m_pDisplayValueLabel->setText(CCString::createWithFormat("insert words max length %d", textField->getMaxLength())->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_DELETE_BACKWARD:
        {
            UITextField* textField = dynamic_cast<UITextField*>(pSender);
            m_pDisplayValueLabel->setText(CCString::createWithFormat("delete word max length %d", textField->getMaxLength())->getCString());
        }
            break;
            
        default:
            break;
    }
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
        m_pDisplayValueLabel->setFontName(font_UITextFieldTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f + m_pDisplayValueLabel->getRect().size.height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("TextField password");
        alert->setFontName(font_UITextFieldTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        // Create the textfield
        UITextField* textField = UITextField::create();
        textField->setPasswordEnable(true);
        textField->setPasswordStyleText("*");
        textField->setTouchEnable(true);
        textField->setFontName(font_UITextFieldTest);
        textField->setFontSize(30);
        textField->setPlaceHolder("input password here");
        textField->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
        textField->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_Password::textFieldEvent));
        m_pUiLayer->addWidget(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest_Password::textFieldEvent(CCObject *pSender, TextFiledEventType type)
{
    switch (type)
    {
        case TEXTFIELD_EVENT_ATTACH_WITH_IME:
        {
            UITextField* textField = dynamic_cast<UITextField*>(pSender);
            CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
            textField->runAction(CCMoveTo::create(0.225,
                                                  ccp(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2)));
            m_pDisplayValueLabel->setText(CCString::createWithFormat("attach with IME password")->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_DETACH_WITH_IME:
        {
            UITextField* textField = dynamic_cast<UITextField*>(pSender);
            CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
            textField->runAction(CCMoveTo::create(0.175, ccp(screenSize.width / 2.0f, screenSize.height / 2.0f)));
            m_pDisplayValueLabel->setText(CCString::createWithFormat("detach with IME password")->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_INSERT_TEXT:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("insert words password")->getCString());
            break;
            
        case TEXTFIELD_EVENT_DELETE_BACKWARD:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("delete word password")->getCString());
            break;
            
        default:
            break;
    }
}
