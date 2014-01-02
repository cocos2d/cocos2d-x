

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
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);        
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("TextField");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        // Create the textfield
        TextField* textField = TextField::create();
        textField->setTouchEnabled(true);
        textField->setFontName("Marker Felt");
        textField->setFontSize(30);
        textField->setPlaceHolder("input words here");
        textField->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textField->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest::textFieldEvent));
        _uiLayer->addChild(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest::textFieldEvent(Object *pSender, TextFiledEventType type)
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
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f + _displayValueLabel->getSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Text *alert = gui::Text::create();
        alert->setText("TextField max length");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        // Create the textfield
        TextField* textField = TextField::create();
        textField->setMaxLengthEnabled(true);
        textField->setMaxLength(3);
        textField->setTouchEnabled(true);
        textField->setFontName("Marker Felt");
        textField->setFontSize(30);
        textField->setPlaceHolder("input words here");
        textField->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f));
        textField->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_MaxLength::textFieldEvent));
        _uiLayer->addChild(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest_MaxLength::textFieldEvent(Object *pSender, TextFiledEventType type)
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
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f + _displayValueLabel->getSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Text *alert = gui::Text::create();
        alert->setText("TextField password");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        // Create the textfield
        TextField* textField = TextField::create();
        textField->setPasswordEnabled(true);
        textField->setPasswordStyleText("*");
        textField->setTouchEnabled(true);
        textField->setFontName("Marker Felt");
        textField->setFontSize(30);
        textField->setPlaceHolder("input password here");
        textField->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f));
        textField->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_Password::textFieldEvent));
        _uiLayer->addChild(textField);
        
        return true;
    }
    return false;
}

void UITextFieldTest_Password::textFieldEvent(Object *pSender, TextFiledEventType type)
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
