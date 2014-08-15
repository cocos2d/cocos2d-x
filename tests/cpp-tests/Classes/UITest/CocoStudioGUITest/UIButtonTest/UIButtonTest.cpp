

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
//        button->setColor(Color3B::RED);
        button->setOpacity(100);
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
            Button *btn = (Button*)pSender;
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
        
        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setPosition(button->getPosition() + Vec2(100,0));
        button2->setName("button2");
        _uiLayer->addChild(button2);
        
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
            
            Button* btn2 = (Button*)_uiLayer->getChildByName("button2");
            btn2->setAnchorPoint(Vec2(0,0.5));
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


// UIButtonTest_RemoveSelf
UIButtonTestRemoveSelf::UIButtonTestRemoveSelf()
: _displayValueLabel(nullptr)
{
    
}

UIButtonTestRemoveSelf::~UIButtonTestRemoveSelf()
{
}

bool UIButtonTestRemoveSelf::init()
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
        Text* alert = Text::create("Remove Self in the Button's Callback shouldn't cause crash!","fonts/Marker Felt.ttf",10);
        alert->setColor(Color3B(159, 168, 176));
        
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 2.75f));
        
        _uiLayer->addChild(alert);
        
        Layout *layout = Layout::create();
        layout->setContentSize(widgetSize * 0.6);
        layout->setBackGroundColor(Color3B::GREEN);
        layout->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        layout->setBackGroundColorOpacity(100);
        layout->setPosition(Size(widgetSize.width/2, widgetSize.height/2));
        layout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        layout->setTag(12);
        _uiLayer->addChild(layout);
        
        // Create the button
        Button* button = Button::create("cocosui/animationbuttonnormal.png",
                                        "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
        //        button->addTouchEventListener(this, toucheventselector(UIButtonTest::touchEvent));
        button->addTouchEventListener(CC_CALLBACK_2(UIButtonTestRemoveSelf::touchEvent, this));
        layout->addChild(button);
        
        
        
        return true;
    }
    return false;
}

void UIButtonTestRemoveSelf::touchEvent(Ref *pSender, Widget::TouchEventType type)
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
            auto layout = _uiLayer->getChildByTag(12);
            layout->removeFromParentAndCleanup(true);
        }
            break;
            
        case Widget::TouchEventType::CANCELED:
            _displayValueLabel->setString(String::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}

// UIButtonTestSwitchScale9
UIButtonTestSwitchScale9::UIButtonTestSwitchScale9()
: _displayValueLabel(nullptr)
{
    
}

UIButtonTestSwitchScale9::~UIButtonTestSwitchScale9()
{
}

bool UIButtonTestSwitchScale9::init()
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
        button->addTouchEventListener(CC_CALLBACK_2(UIButtonTestSwitchScale9::touchEvent, this));
        button->ignoreContentAdaptWithSize(false);

        _uiLayer->addChild(button);
        
        
        
        return true;
    }
    return false;
}

void UIButtonTestSwitchScale9::touchEvent(Ref *pSender, Widget::TouchEventType type)
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
            auto btn = ((Button*)pSender);
            btn->setScale9Enabled(!btn->isScale9Enabled());
            btn->setContentSize(Size(200,100));
        }
            break;
            
        case Widget::TouchEventType::CANCELED:
            _displayValueLabel->setString(String::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}


// UIButtonTestZoomScale
UIButtonTestZoomScale::UIButtonTestZoomScale()
: _displayValueLabel(nullptr)
{
    
}

UIButtonTestZoomScale::~UIButtonTestZoomScale()
{
}

bool UIButtonTestZoomScale::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the button events will be displayed
        _displayValueLabel = Text::create("Zoom Scale: 0.1", "fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 20));
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
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 20));
        button->setPressedActionEnabled(true);
        button->setName("button");
        _uiLayer->addChild(button);
        button->setZoomScale(-0.5);
        
        Slider* slider = Slider::create();
        slider->loadBarTexture("cocosui/sliderTrack.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosui/sliderProgress.png");
        slider->setPosition(Vec2(widgetSize.width / 2.0f , widgetSize.height / 2.0f - 20));
        slider->addEventListener(CC_CALLBACK_2(UIButtonTestZoomScale::sliderEvent, this));
        slider->setPercent(button->getZoomScale()*100);
        _uiLayer->addChild(slider);
        return true;
    }
    return false;
}

void UIButtonTestZoomScale::sliderEvent(Ref *pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percent = slider->getPercent();
        Button* btn = (Button*)_uiLayer->getChildByName("button");
        float zoomScale = percent * 0.01;
        btn->setZoomScale(zoomScale);
        _displayValueLabel->setString(String::createWithFormat("Zoom Scale: %f", zoomScale)->getCString());
    }
}
