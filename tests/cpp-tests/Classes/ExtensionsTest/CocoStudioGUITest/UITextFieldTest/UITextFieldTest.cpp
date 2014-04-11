

#include "UITextFieldTest.h"

// UITextFieldTest
UITextFieldTest::UITextFieldTest()
: _displayValueLabel(nullptr)
{
    
}

UITextFieldTest::~UITextFieldTest()
{
}

bool UITextFieldTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the textfield events will be displayed
        _displayValueLabel = Text::create("No Event","fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);        
        
        // Add the alert
        Text* alert = Text::create("TextField","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        // Create the textfield
        TextField* textField = TextField::create("input words here","fonts/Marker Felt.ttf",30);

        textField->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textField->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest::textFieldEvent));
        _uiLayer->addChild(textField);
        
        
        return true;
    }
    return false;
}

void UITextFieldTest::textFieldEvent(Ref *pSender, TextFiledEventType type)
{
    switch (type)
    {
        case TEXTFIELD_EVENT_ATTACH_WITH_IME:
        {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            Size screenSize = CCDirector::getInstance()->getWinSize();
            textField->runAction(CCMoveTo::create(0.225f,
                                                  Point(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));
            _displayValueLabel->setText(String::createWithFormat("attach with IME")->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_DETACH_WITH_IME:
        {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            Size screenSize = CCDirector::getInstance()->getWinSize();
            textField->runAction(CCMoveTo::create(0.175f, Point(screenSize.width / 2.0f, screenSize.height / 2.0f)));
            _displayValueLabel->setText(String::createWithFormat("detach with IME")->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_INSERT_TEXT:
            _displayValueLabel->setText(String::createWithFormat("insert words")->getCString());
            break;
            
        case TEXTFIELD_EVENT_DELETE_BACKWARD:
            _displayValueLabel->setText(String::createWithFormat("delete word")->getCString());
            break;
            
        default:
            break;
    }
}

// UITextFieldTest_MaxLength
UITextFieldTest_MaxLength::UITextFieldTest_MaxLength()
: _displayValueLabel(nullptr)
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
        _displayValueLabel = Text::create("No Event","fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f + _displayValueLabel->getSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text *alert = Text::create("TextField max length","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        // Create the textfield
        TextField* textField = TextField::create("input words here","fonts/Marker Felt.ttf",30);
        textField->setMaxLengthEnabled(true);
        textField->setMaxLength(3);
        textField->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f));
        textField->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_MaxLength::textFieldEvent));
        _uiLayer->addChild(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest_MaxLength::textFieldEvent(Ref *pSender, TextFiledEventType type)
{
    switch (type)
    {
        case TEXTFIELD_EVENT_ATTACH_WITH_IME:
        {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            Size screenSize = CCDirector::getInstance()->getWinSize();
            textField->runAction(CCMoveTo::create(0.225f,
                                                  Point(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));
            _displayValueLabel->setText(String::createWithFormat("attach with IME max length %d", textField->getMaxLength())->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_DETACH_WITH_IME:
        {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            Size screenSize = CCDirector::getInstance()->getWinSize();
            textField->runAction(CCMoveTo::create(0.175f, Point(screenSize.width / 2.0f, screenSize.height / 2.0f)));
            _displayValueLabel->setText(String::createWithFormat("detach with IME max length %d", textField->getMaxLength())->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_INSERT_TEXT:
        {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            _displayValueLabel->setText(String::createWithFormat("insert words max length %d", textField->getMaxLength())->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_DELETE_BACKWARD:
        {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            _displayValueLabel->setText(String::createWithFormat("delete word max length %d", textField->getMaxLength())->getCString());
        }
            break;
            
        default:
            break;
    }
}

// UITextFieldTest_Password
UITextFieldTest_Password::UITextFieldTest_Password()
: _displayValueLabel(nullptr)
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
        _displayValueLabel = Text::create("No Event","fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f + _displayValueLabel->getSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text *alert = Text::create("TextField password","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        // Create the textfield
        TextField* textField = TextField::create("input password here","fonts/Marker Felt.ttf",30);
        textField->setPasswordEnabled(true);
        textField->setPasswordStyleText("*");
        textField->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f));
        textField->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_Password::textFieldEvent));
        _uiLayer->addChild(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest_Password::textFieldEvent(Ref *pSender, TextFiledEventType type)
{
    switch (type)
    {
        case TEXTFIELD_EVENT_ATTACH_WITH_IME:
        {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            Size screenSize = CCDirector::getInstance()->getWinSize();
            textField->runAction(CCMoveTo::create(0.225f,
                                                  Point(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));
            _displayValueLabel->setText(String::createWithFormat("attach with IME password")->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_DETACH_WITH_IME:
        {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            Size screenSize = CCDirector::getInstance()->getWinSize();
            textField->runAction(CCMoveTo::create(0.175f, Point(screenSize.width / 2.0f, screenSize.height / 2.0f)));
            _displayValueLabel->setText(String::createWithFormat("detach with IME password")->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_INSERT_TEXT:
            _displayValueLabel->setText(String::createWithFormat("insert words password")->getCString());
            break;
            
        case TEXTFIELD_EVENT_DELETE_BACKWARD:
            _displayValueLabel->setText(String::createWithFormat("delete word password")->getCString());
            break;
            
        default:
            break;
    }
}


// UITextFieldTest_LineWrap
UITextFieldTest_LineWrap::UITextFieldTest_LineWrap()
: _displayValueLabel(nullptr)
{
    
}

UITextFieldTest_LineWrap::~UITextFieldTest_LineWrap()
{
}

bool UITextFieldTest_LineWrap::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the textfield events will be displayed
        _displayValueLabel = Text::create("No Event","fonts/Marker Felt.ttf",30);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getSize().height * 1.5));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text *alert = Text::create("TextField line wrap","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        _uiLayer->addChild(alert);
        
        // Create the textfield
        TextField* textField = TextField::create("input words here","fonts/Marker Felt.ttf",30);
        textField->ignoreContentAdaptWithSize(false);
        textField->setSize(Size(240, 160));
        textField->setTextHorizontalAlignment(TextHAlignment::CENTER);
        textField->setTextVerticalAlignment(TextVAlignment::CENTER);
        textField->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textField->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_LineWrap::textFieldEvent));
        _uiLayer->addChild(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest_LineWrap::textFieldEvent(Ref *pSender, TextFiledEventType type)
{
    switch (type)
    {
        case TEXTFIELD_EVENT_ATTACH_WITH_IME:
        {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            Size widgetSize = _widget->getSize();
            textField->runAction(CCMoveTo::create(0.225f,
                                                  Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + textField->getContentSize().height / 2)));
            textField->setTextHorizontalAlignment(TextHAlignment::LEFT);
            textField->setTextVerticalAlignment(TextVAlignment::TOP);
            
            _displayValueLabel->setText(CCString::createWithFormat("attach with IME")->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_DETACH_WITH_IME:
        {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            Size widgetSize = _widget->getSize();
            textField->runAction(CCMoveTo::create(0.175f, Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f)));
            textField->setTextHorizontalAlignment(TextHAlignment::CENTER);
            textField->setTextVerticalAlignment(TextVAlignment::CENTER);
            
            _displayValueLabel->setText(CCString::createWithFormat("detach with IME")->getCString());
        }
            break;
            
        case TEXTFIELD_EVENT_INSERT_TEXT:
            _displayValueLabel->setText(CCString::createWithFormat("insert words")->getCString());
            break;
            
        case TEXTFIELD_EVENT_DELETE_BACKWARD:
            _displayValueLabel->setText(CCString::createWithFormat("delete word")->getCString());
            break;
            
        default:
            break;
    }
}
