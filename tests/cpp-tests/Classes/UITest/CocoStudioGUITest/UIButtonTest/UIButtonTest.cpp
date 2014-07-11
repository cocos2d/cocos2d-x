

#include "UIButtonTest.h"


// UIButtonTest
UIButtonTest::UIButtonTest()
: _displayValueLabel(nullptr)
{
    
}

UIButtonTest::~UIButtonTest()
{
}

bool UIButtonTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the button events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);        
        
        // Add the alert
        Text* alert = Text::create("Button","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));                
        
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        
        _uiLayer->addChild(alert);        
        
        // Create the button
        Button* button = Button::create("cocosui/animationbuttonnormal.png",
                                        "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
//        button->addTouchEventListener(this, toucheventselector(UIButtonTest::touchEvent));
        button->addTouchEventListener(CC_CALLBACK_2(UIButtonTest::touchEvent, this));
        _uiLayer->addChild(button);
        
        // Create the imageview
        ImageView* imageView = ImageView::create();
    
        imageView->setPosition(Vec2(widgetSize.width / 2.0f + 50+ button->getContentSize().width/2,
                                    widgetSize.height / 2.0f));
        imageView->setTag(12);
        
        _uiLayer->addChild(imageView);
        
        

        return true;
    }
    return false;
}

void UIButtonTest::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            _displayValueLabel->setString(String::createWithFormat("Touch Down")->getCString());
            break;
            
        case Widget::TouchEventType::MOVED:
            _displayValueLabel->setString(String::createWithFormat("Touch Move")->getCString());
            break;
            
        case Widget::TouchEventType::ENDED:
        {
            _displayValueLabel->setString(String::createWithFormat("Touch Up")->getCString());
            ImageView* imageView = (ImageView*)_uiLayer->getChildByTag(12);
            imageView->setVisible(false);
            imageView->loadTexture("cocosui/ccicon.png");
            imageView->setOpacity(0);
            imageView->setVisible(true);
            imageView->runAction(Sequence::create(FadeIn::create(0.5),DelayTime::create(1.0),FadeOut::create(0.5), nullptr));
        }
            break;
            
        case Widget::TouchEventType::CANCELED:
            _displayValueLabel->setString(String::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}


// UIButtonTest_Scale9
UIButtonTest_Scale9::UIButtonTest_Scale9()
: _displayValueLabel(nullptr)
{
    
}

UIButtonTest_Scale9::~UIButtonTest_Scale9()
{
    
}

bool UIButtonTest_Scale9::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the button events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("Button scale9 render", "fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);        
        
        // Create the button
        Button* button = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        // open scale9 render
        button->setScale9Enabled(true);
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->setContentSize(Size(150, 70));
        button->addTouchEventListener(CC_CALLBACK_2(UIButtonTest_Scale9::touchEvent, this));
        _uiLayer->addChild(button);
        
        // Create the imageview
        Button* button2 = Button::create();
        button2->setPosition(Vec2(widgetSize.width / 2.0f + button->getContentSize().width + 20, widgetSize.height / 2.0f));
        button2->setName("normal");
        _uiLayer->addChild(button2);
        
        Sprite *sprite = Sprite::create("cocosui/animationbuttonnormal.png");
        button2->addChild(sprite);
        
        return true;
    }
    return false;
}

void UIButtonTest_Scale9::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            _displayValueLabel->setString(String::createWithFormat("Touch Down")->getCString());
            break;
            
        case Widget::TouchEventType::MOVED:
            _displayValueLabel->setString(String::createWithFormat("Touch Move")->getCString());
            break;
            
        case Widget::TouchEventType::ENDED:
        {
            _displayValueLabel->setString(String::createWithFormat("Touch Up")->getCString());
            Button *btn = (Button*)_uiLayer->getChildByName("normal");
            btn->loadTextureNormal("cocosui/animationbuttonnormal.png");
            btn->loadTexturePressed("cocosui/animationbuttonpressed.png");
            btn->runAction(Sequence::create(FadeIn::create(0.5),DelayTime::create(1.0),FadeOut::create(0.5), nullptr));
        }
            break;
            
        case Widget::TouchEventType::CANCELED:
            _displayValueLabel->setString(String::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}

// UIButtonTest_PressAction
UIButtonTest_PressedAction::UIButtonTest_PressedAction()
: _displayValueLabel(nullptr)
{
}

UIButtonTest_PressedAction::~UIButtonTest_PressedAction()
{
}

bool UIButtonTest_PressedAction::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the button events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("Button Pressed Action", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        
        _uiLayer->addChild(alert);
        
        // Create the button
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPressedActionEnabled(true);
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->setColor(Color3B::GREEN);
        button->setOpacity(30);
        button->addTouchEventListener(CC_CALLBACK_2(UIButtonTest_PressedAction::touchEvent, this));
        button->setName("button");
        _uiLayer->addChild(button);
        
        return true;
    }
    return false;
}

void UIButtonTest_PressedAction::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            _displayValueLabel->setString(String::createWithFormat("Touch Down")->getCString());
            break;
            
        case Widget::TouchEventType::MOVED:
            _displayValueLabel->setString(String::createWithFormat("Touch Move")->getCString());
            break;
            
        case Widget::TouchEventType::ENDED:
        {
            _displayValueLabel->setString(String::createWithFormat("Touch Up")->getCString());
            Button* btn = (Button*)_uiLayer->getChildByName("button");
            btn->loadTextureNormal("cocosui/animationbuttonnormal.png");
        }
            break;
            
        case Widget::TouchEventType::CANCELED:
            _displayValueLabel->setString(String::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}

// UIButtonTest_Title
UIButtonTest_Title::UIButtonTest_Title()
: _displayValueLabel(nullptr)
{
    
}

UIButtonTest_Title::~UIButtonTest_Title()
{
}

bool UIButtonTest_Title::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the text button events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("Button with title", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        
        _uiLayer->addChild(alert);
        
        // Create the button with title
        Button* button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
        button->setTitleText("Title Button");
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->setTitleColor(Color3B::YELLOW);
        CCASSERT(button->getTitleColor() == Color3B::YELLOW, "Button setTitleColotr & getTitleColor not match!");
//        button->addTouchEventListener(this, toucheventselector(UIButtonTest_Title::touchEvent));
        button->addTouchEventListener(CC_CALLBACK_2(UIButtonTest_Title::touchEvent, this));
        _uiLayer->addChild(button);
        
        
        TextBMFont *text = TextBMFont::create("BMFont", "cocosui/bitmapFontTest2.fnt");
        text->setPosition(button->getPosition() + Vec2(button->getContentSize().width/2 + 50,0));
        text->setColor(Color3B::YELLOW);
        text->setOpacity(50);
        text->setName("text");


        _uiLayer->addChild(text);
        
        return true;
    }
    return false;
}


void UIButtonTest_Title::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            _displayValueLabel->setString(String::createWithFormat("Touch Down")->getCString());
            break;
            
        case Widget::TouchEventType::MOVED:
            _displayValueLabel->setString(String::createWithFormat("Touch Move")->getCString());
            break;
            
        case Widget::TouchEventType::ENDED:
        {
            _displayValueLabel->setString(String::createWithFormat("Touch Up")->getCString());
            TextBMFont *text = (TextBMFont*)_uiLayer->getChildByName("text");
            text->setFntFile("cocosui/bitmapFontTest2.fnt");
            if (text->getString() == "BMFont") {
                text->setString("Hello");
            }
            else{
                text->setString("BMFont");
            }
        }
            break;
            
        case Widget::TouchEventType::CANCELED:
            _displayValueLabel->setString(String::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}
