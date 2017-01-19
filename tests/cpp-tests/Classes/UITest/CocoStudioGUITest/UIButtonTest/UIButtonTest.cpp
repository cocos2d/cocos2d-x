#include "UIButtonTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIButtonTests::UIButtonTests()
{
    ADD_TEST_CASE(UIButtonTest);
    ADD_TEST_CASE(UIButtonTest_Scale9);
    ADD_TEST_CASE(UIButtonTest_Scale9_State_Change);
    ADD_TEST_CASE(UIButtonTest_PressedAction);
    ADD_TEST_CASE(UIButtonTest_Title);
    ADD_TEST_CASE(UIButtonTestRemoveSelf);
    ADD_TEST_CASE(UIButtonTestSwitchScale9);
    ADD_TEST_CASE(UIButtonTestZoomScale);
    ADD_TEST_CASE(UIButtonTextOnly);
    ADD_TEST_CASE(UIButtonIgnoreContentSizeTest);
    ADD_TEST_CASE(UIButtonTitleEffectTest);
    ADD_TEST_CASE(UIButtonFlipTest);
    ADD_TEST_CASE(UIButtonNormalDefaultTest);
    ADD_TEST_CASE(UIButtonDisableDefaultTest);
    ADD_TEST_CASE(UIButtonCloneTest);
    ADD_TEST_CASE(Issue12249);
    ADD_TEST_CASE(Issue17116);
    ADD_TEST_CASE(UIButtonWithPolygonInfo);
}

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
        CCLOG("content size should be greater than 0:  width = %f, height = %f", button->getContentSize().width,
              button->getContentSize().height);
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->addTouchEventListener(CC_CALLBACK_2(UIButtonTest::touchEvent, this));
        button->setZoomScale(0.4f);
        button->setPressedActionEnabled(true);
        _uiLayer->addChild(button);
        button->setOpacity(100);
        // Create the imageview
        ImageView* imageView = ImageView::create();

        imageView->setPosition(Vec2(widgetSize.width / 2.0f + 50+ button->getContentSize().width/2,
                                    widgetSize.height / 2.0f));
        imageView->setTag(12);

        _uiLayer->addChild(imageView);

        _button = button;

        TTFConfig ttfConfig("fonts/arial.ttf", 15);
        auto label1 = Label::createWithTTF(ttfConfig, "Print Resources");
        auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(UIButtonTest::printWidgetResources, this));
        item1->setPosition(Vec2(VisibleRect::left().x + 60, VisibleRect::bottom().y + item1->getContentSize().height * 3));
        auto pMenu1 = Menu::create(item1, nullptr);
        pMenu1->setPosition(Vec2(0, 0));
        this->addChild(pMenu1, 10);

        return true;
    }
    return false;
}

void UIButtonTest::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            _displayValueLabel->setString(StringUtils::format("Touch Down"));
            break;

        case Widget::TouchEventType::MOVED:
            _displayValueLabel->setString(StringUtils::format("Touch Move"));
            break;

        case Widget::TouchEventType::ENDED:
        {
            _displayValueLabel->setString(StringUtils::format("Touch Up"));
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
            _displayValueLabel->setString(StringUtils::format("Touch Cancelled"));
            break;

        default:
            break;
    }
}

void UIButtonTest::printWidgetResources(cocos2d::Ref* sender)
{
    cocos2d::ResourceData normalFileName = _button->getNormalFile();
    CCLOG("normalFileName  Name : %s, Type: %d", normalFileName.file.c_str(), normalFileName.type);
    cocos2d::ResourceData clickedFileName = _button->getPressedFile();
    CCLOG("clickedFileName  Name : %s, Type: %d", clickedFileName.file.c_str(), clickedFileName.type);
    cocos2d::ResourceData disabledFileName = _button->getDisabledFile();
    CCLOG("disabledFileName  Name : %s, Type: %d", disabledFileName.file.c_str(), disabledFileName.type);
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
        button->setContentSize(Size(150, 70));
        button->setPosition(Vec2(-button->getContentSize().width - 10, widgetSize.height / 2.0f));
        auto moveBy = MoveBy::create(1.0, Vec2(widgetSize.width/2, 0));
        auto moveByReverse = moveBy->reverse()->clone();
        button->runAction(RepeatForever::create(
                                Sequence::create(moveBy,moveByReverse, NULL)));
        button->setPressedActionEnabled(true);
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
            _displayValueLabel->setString(StringUtils::format("Touch Down"));
            break;

        case Widget::TouchEventType::MOVED:
            _displayValueLabel->setString(StringUtils::format("Touch Move"));
            break;

        case Widget::TouchEventType::ENDED:
        {
            _displayValueLabel->setString(StringUtils::format("Touch Up"));
            Button *btn = (Button*)_uiLayer->getChildByName("normal");
            btn->loadTextureNormal("cocosui/animationbuttonnormal.png");
            btn->loadTexturePressed("cocosui/animationbuttonpressed.png");
            btn->runAction(Sequence::create(FadeIn::create(0.5),DelayTime::create(1.0),FadeOut::create(0.5), nullptr));
        }
            break;

        case Widget::TouchEventType::CANCELED:
            _displayValueLabel->setString(StringUtils::format("Touch Cancelled"));
            break;

        default:
            break;
    }
}

// UIButtonTest_Scale9_State_Change
UIButtonTest_Scale9_State_Change::UIButtonTest_Scale9_State_Change()
    : _displayValueLabel(nullptr)
{

}

UIButtonTest_Scale9_State_Change::~UIButtonTest_Scale9_State_Change()
{

}

bool UIButtonTest_Scale9_State_Change::init()
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
        Text* alert = Text::create("Button scale9 render", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
            widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);

        // Create the button
        Button* button = Button::create("cocosui/button.png");
        // open scale9 render
        button->ignoreContentAdaptWithSize(false);
        button->setScale9Enabled(true);
        button->setPosition(Vec2(widgetSize.width / 2.0f - 100, widgetSize.height / 2.0f));
        button->setContentSize(Size(180, 60));
        button->setTitleText("Hello Scale9");
        button->setPressedActionEnabled(false);
        button->addTouchEventListener(CC_CALLBACK_2(UIButtonTest_Scale9_State_Change::touchEvent, this));
        _uiLayer->addChild(button);

        Button* button2 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        // open scale9 render
        button2->ignoreContentAdaptWithSize(false);
        button2->setScale9Enabled(true);
        button2->setTitleText("Hello scale9");
        button2->setPosition(Vec2(widgetSize.width / 2.0f + 100, widgetSize.height / 2.0f));
        button2->setContentSize(Size(180, 60));
        button2->setPressedActionEnabled(true);
        button2->addTouchEventListener(CC_CALLBACK_2(UIButtonTest_Scale9_State_Change::touchEvent, this));
        _uiLayer->addChild(button2);
        return true;
    }
    return false;
}

void UIButtonTest_Scale9_State_Change::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        _displayValueLabel->setString(StringUtils::format("Touch Down"));
        break;

    case Widget::TouchEventType::MOVED:
        _displayValueLabel->setString(StringUtils::format("Touch Move"));
        break;

    case Widget::TouchEventType::ENDED:
    {
        _displayValueLabel->setString(StringUtils::format("Touch Up"));
        Button *btn = (Button*)pSender;
        if (btn->isScale9Enabled())
        {
            btn->setScale9Enabled(false);
        }
        else
            btn->setScale9Enabled(true);
    }
        break;

    case Widget::TouchEventType::CANCELED:
        _displayValueLabel->setString(StringUtils::format("Touch Cancelled"));
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
            _displayValueLabel->setString(StringUtils::format("Touch Down"));
            break;

        case Widget::TouchEventType::MOVED:
            _displayValueLabel->setString(StringUtils::format("Touch Move"));
            break;

        case Widget::TouchEventType::ENDED:
        {
            _displayValueLabel->setString(StringUtils::format("Touch Up"));
            Button* btn = (Button*)_uiLayer->getChildByName("button");
            btn->loadTextureNormal("cocosui/animationbuttonnormal.png");

            Button* btn2 = (Button*)_uiLayer->getChildByName("button2");
            btn2->setAnchorPoint(Vec2(0,0.5));
        }
            break;

        case Widget::TouchEventType::CANCELED:
            _displayValueLabel->setString(StringUtils::format("Touch Cancelled"));
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
        Text* alert = Text::create("Button with title, title should be flipped!", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));

        _uiLayer->addChild(alert);

        // Create the button with title
        Button* button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
        button->setTitleText("Title Button!");
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->setTitleColor(Color3B::YELLOW);
        CCASSERT(button->getTitleColor() == Color3B::YELLOW, "Button setTitleColotr & getTitleColor not match!");
        button->addTouchEventListener(CC_CALLBACK_2(UIButtonTest_Title::touchEvent, this));
        _uiLayer->addChild(button);
        button->setFlippedX(true);
        auto label = button->getTitleRenderer();
        label->setScale(4.0);
        button->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(1.0f, 1.2f),
                                                                 ScaleTo::create(1.0f, 1.0f),nullptr)));


        TextBMFont *text = TextBMFont::create("BMFont", "cocosui/bitmapFontTest2.fnt");
        text->setPosition(button->getPosition() + Vec2(button->getContentSize().width/2 + 50,0));
        text->setColor(Color3B::YELLOW);
        text->setOpacity(50);
        text->setName("text");

        auto button2 = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        button2->setTitleFontName("fonts/helvetica-32.fnt");
        button2->setTitleText("BMFont");
        //the change of font size will take no effect.
        button2->setTitleFontSize(30);
        button2->setPosition(Vec2(button->getPosition() + Vec2(50,-80)));
        this->addChild(button2);

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
            _displayValueLabel->setString(StringUtils::format("Touch Down"));
            break;

        case Widget::TouchEventType::MOVED:
            _displayValueLabel->setString(StringUtils::format("Touch Move"));
            break;

        case Widget::TouchEventType::ENDED:
        {
            _displayValueLabel->setString(StringUtils::format("Touch Up"));
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
            _displayValueLabel->setString(StringUtils::format("Touch Cancelled"));
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
        layout->setContentSize(widgetSize * 0.6f);
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
            _displayValueLabel->setString(StringUtils::format("Touch Down"));
            break;

        case Widget::TouchEventType::MOVED:
            _displayValueLabel->setString(StringUtils::format("Touch Move"));
            break;

        case Widget::TouchEventType::ENDED:
        {
            _displayValueLabel->setString(StringUtils::format("Touch Up"));
            auto layout = _uiLayer->getChildByTag(12);
            layout->removeFromParentAndCleanup(true);
        }
            break;

        case Widget::TouchEventType::CANCELED:
            _displayValueLabel->setString(StringUtils::format("Touch Cancelled"));
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


        // Create the button
        Button* button = Button::create("cocosui/animationbuttonnormal.png",
                                        "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->addTouchEventListener(CC_CALLBACK_2(UIButtonTestSwitchScale9::touchEvent, this));
        button->setTitleText("Button Title");
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
            _displayValueLabel->setString(StringUtils::format("Touch Down"));
            break;

        case Widget::TouchEventType::MOVED:
            _displayValueLabel->setString(StringUtils::format("Touch Move"));
            break;

        case Widget::TouchEventType::ENDED:
        {
            _displayValueLabel->setString(StringUtils::format("Touch Up"));
            auto btn = ((Button*)pSender);
            btn->setScale9Enabled(!btn->isScale9Enabled());
            btn->setContentSize(Size(200,100));
        }
            break;

        case Widget::TouchEventType::CANCELED:
            _displayValueLabel->setString(StringUtils::format("Touch Cancelled"));
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
        _displayValueLabel = Text::create("Zoom Scale: -0.5", "fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 20));
        _uiLayer->addChild(_displayValueLabel);


        // Create the button
        Button* button = Button::create("cocosui/animationbuttonnormal.png",
                                        "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 20));
        button->setPressedActionEnabled(true);
        button->addClickEventListener([=](Ref* sender){
            CCLOG("Button clicked, position = (%f, %f)", button->getPosition().x,
                  button->getPosition().y);

        });
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
        _displayValueLabel->setString(StringUtils::format("Zoom Scale: %f", zoomScale));
    }
}

// UIButtonTextOnly
UIButtonTextOnly::UIButtonTextOnly()
: _displayValueLabel(nullptr)
{

}

UIButtonTextOnly::~UIButtonTextOnly()
{
}

bool UIButtonTextOnly::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the button events will be displayed
        _displayValueLabel = Text::create("Text Only Button", "fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 20));
        _uiLayer->addChild(_displayValueLabel);


        // Create the button
        auto button = Button::create();
        button->setPositionNormalized(Vec2(0.5f, 0.5f));

        button->setTitleText("PLAY GAME");
        CCLOG("content size should be greater than 0:  width = %f, height = %f", button->getContentSize().width,
              button->getContentSize().height);
        button->setZoomScale(0.3f);
        button->setPressedActionEnabled(true);
        button->addClickEventListener([this](Ref* sender) {
            CCLOG("clicked!");
        });
        _uiLayer->addChild(button);

        return true;
    }
    return false;
}

// UIButtonIgnoreContentSizeTest
UIButtonIgnoreContentSizeTest::UIButtonIgnoreContentSizeTest()
: _displayValueLabel(nullptr)
{

}

UIButtonIgnoreContentSizeTest::~UIButtonIgnoreContentSizeTest()
{
}

bool UIButtonIgnoreContentSizeTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the button events will be displayed
        _displayValueLabel = Text::create("Button IgnoreContent Size Test", "fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 20));
        _uiLayer->addChild(_displayValueLabel);


        // Create the button
        auto button = Button::create("cocosui/animationbuttonnormal.png",
                                     "cocosui/animationbuttonpressed.png");
        button->ignoreContentAdaptWithSize(false);
        button->setContentSize(Size(200,100));
        button->setPositionNormalized(Vec2(0.3f, 0.5f));
        button->setTitleText("PLAY GAME");
        button->setZoomScale(0.3f);
        button->setPressedActionEnabled(true);
        button->addClickEventListener([=](Ref* sender) {
            CCLOG("clicked!");
            button->setScale(1.2f);
        });
        _uiLayer->addChild(button);

        // Create the button
        auto button2 = Button::create("cocosui/animationbuttonnormal.png",
                                     "cocosui/animationbuttonpressed.png");
        button2->ignoreContentAdaptWithSize(false);
        button2->setContentSize(Size(200,100));
        button2->setPositionNormalized(Vec2(0.8f, 0.5f));
        button2->setTitleText("PLAY GAME");
        button2->setZoomScale(0.3f);
        button2->setPressedActionEnabled(true);
        button2->addClickEventListener([=](Ref* sender) {
            button2->runAction(ScaleTo::create(1.0f, 1.2f));
            CCLOG("clicked!");
        });
        _uiLayer->addChild(button2);

        return true;
    }
    return false;
}


// UIButtonTitleEffectTest
UIButtonTitleEffectTest::UIButtonTitleEffectTest()
: _displayValueLabel(nullptr)
{

}

UIButtonTitleEffectTest::~UIButtonTitleEffectTest()
{
}

bool UIButtonTitleEffectTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the button events will be displayed
        _displayValueLabel = Text::create("Button Title Effect", "fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 20));
        _uiLayer->addChild(_displayValueLabel);


        // Create the button
        auto button = Button::create("cocosui/animationbuttonnormal.png",
                                     "cocosui/animationbuttonpressed.png");
        button->setPositionNormalized(Vec2(0.3f, 0.5f));
        button->setTitleText("PLAY GAME");
        button->setTitleFontName("fonts/Marker Felt.ttf");
        button->setZoomScale(0.3f);
        button->setScale(2.0f);
        button->setPressedActionEnabled(true);
        Label *title = button->getTitleRenderer();
        button->setTitleColor(Color3B::RED);
        title->enableShadow(Color4B::BLACK,Size(2,-2));


        _uiLayer->addChild(button);

        // Create the button
        auto button2 = Button::create("cocosui/animationbuttonnormal.png",
                                      "cocosui/animationbuttonpressed.png");
        button2->setPositionNormalized(Vec2(0.8f, 0.5f));
        button2->setTitleText("PLAY GAME");
        auto title2 = button2->getTitleRenderer();
        title2->enableOutline(Color4B::GREEN, 3);
        _uiLayer->addChild(button2);

        return true;
    }
    return false;
}
// UIButtonFlipTest
UIButtonFlipTest::UIButtonFlipTest()
: _displayValueLabel(nullptr)
{

}

UIButtonFlipTest::~UIButtonFlipTest()
{
}

bool UIButtonFlipTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the button events will be displayed
        _displayValueLabel = Text::create("Button X Flipped", "fonts/Marker Felt.ttf",20);
        _displayValueLabel->setPositionNormalized(Vec2(0.3f, 0.7f));
        _uiLayer->addChild(_displayValueLabel);


        // Create the button
        auto button = Button::create("cocosui/animationbuttonnormal.png",
                                     "cocosui/animationbuttonpressed.png");
        button->setPositionNormalized(Vec2(0.3f, 0.5f));
        button->setTitleText("PLAY GAME");
        button->setTitleFontName("fonts/Marker Felt.ttf");
        button->setZoomScale(0.3f);
        button->setScale(2.0f);
        button->setFlippedX(true);
        button->setPressedActionEnabled(true);


        _uiLayer->addChild(button);

        // Create the button
        auto button2 = Button::create("cocosui/animationbuttonnormal.png",
                                      "cocosui/animationbuttonpressed.png");
        button2->setPositionNormalized(Vec2(0.8f, 0.5f));
        button2->setTitleText("PLAY GAME");
        button2->setFlippedY(true);
        _uiLayer->addChild(button2);

        auto titleLabel = Text::create("Button Y flipped", "Arial", 20);
        titleLabel->setPositionNormalized(Vec2(0.8f, 0.7f));
        this->addChild(titleLabel);

        return true;
    }
    return false;
}

// UIButtonNormalDefaultTest
UIButtonNormalDefaultTest::UIButtonNormalDefaultTest()
: _displayValueLabel(nullptr)
{

}

UIButtonNormalDefaultTest::~UIButtonNormalDefaultTest()
{
}

bool UIButtonNormalDefaultTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the button events will be displayed
        _displayValueLabel = Text::create("", "fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("Button should scale when clicked","fonts/Marker Felt.ttf",20);
        alert->setColor(Color3B(159, 168, 176));

        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));

        _uiLayer->addChild(alert);

        // Create the button
        Button* button = Button::create("cocosui/animationbuttonnormal.png");
        button->setPosition(Vec2(widgetSize.width / 2.0f - 80, widgetSize.height / 2.0f + 40));
        button->setZoomScale(0.4f);
        button->setPressedActionEnabled(true);
        _uiLayer->addChild(button);

        // Create the button
        Button* buttonScale9 = Button::create("cocosui/button.png");
        // open scale9 render
        buttonScale9->setScale9Enabled(true);
        buttonScale9->setPosition(Vec2(widgetSize.width / 2.0f + 50, widgetSize.height / 2.0f + 40));
        buttonScale9->setContentSize(Size(150, 70));
        buttonScale9->setPressedActionEnabled(true);
        _uiLayer->addChild(buttonScale9);




        return true;
    }
    return false;
}


// UIButtonDisableDefaultTest
UIButtonDisableDefaultTest::UIButtonDisableDefaultTest()
: _displayValueLabel(nullptr)
{

}

UIButtonDisableDefaultTest::~UIButtonDisableDefaultTest()
{
}

bool UIButtonDisableDefaultTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the button events will be displayed
        _displayValueLabel = Text::create("", "fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("Left button will turn normal when clicked","fonts/Marker Felt.ttf",20);
        alert->setColor(Color3B(159, 168, 176));

        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));

        _uiLayer->addChild(alert);

        // Create the button
        Button* button = Button::create("cocosui/animationbuttonnormal.png");
        button->setPosition(Vec2(widgetSize.width / 2.0f - 80, widgetSize.height / 2.0f + 40));
        button->setZoomScale(0.4f);
        button->setPressedActionEnabled(true);
        button->setBright(false);
        button->setScale9Enabled(true);
        button->setCapInsets(Rect(3,3,5,5));
        button->addClickEventListener([=](Ref*){
            button->setBright(true);
        });
        _uiLayer->addChild(button);

        // Create the button
        Button* buttonScale9 = Button::create("cocosui/button.png");
        // open scale9 render
        buttonScale9->setScale9Enabled(true);
        buttonScale9->setPosition(Vec2(widgetSize.width / 2.0f + 50, widgetSize.height / 2.0f + 40));
        buttonScale9->setContentSize(Size(150, 70));
        buttonScale9->setPressedActionEnabled(true);
        buttonScale9->setEnabled(false);
        buttonScale9->setBright(false);
        _uiLayer->addChild(buttonScale9);




        return true;
    }
    return false;
}

// UIButtonCloneTest
UIButtonCloneTest::UIButtonCloneTest()
: _displayValueLabel(nullptr)
{

}

UIButtonCloneTest::~UIButtonCloneTest()
{
}

bool UIButtonCloneTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the button events will be displayed
        _displayValueLabel = Text::create("", "fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                             widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("This test case shouldn't trigger the Assertion!",
                                   "fonts/Marker Felt.ttf",20);
        alert->setColor(Color3B(159, 168, 176));

        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f
                                - alert->getContentSize().height * 1.75f));

        _uiLayer->addChild(alert);

        // Create the button
        Button* button = Button::create("cocosui/animationbuttonnormal.png");
        button->setPosition(Vec2(widgetSize.width / 2.0f - 80,
                                 widgetSize.height / 2.0f + 40));
        _uiLayer->addChild(button);


        CCASSERT(button->getTitleRenderer() == nullptr,
                 "Button title render must be nullptr ");

        auto buttonCopy = (Button*)button->clone();
        buttonCopy->setPosition(Vec2(widgetSize.width / 2.0f + 80,
                                     widgetSize.height / 2.0f + 40));
        this->addChild(buttonCopy);
        
        
        
        auto buttonScale9Copy = (Button*)button->clone();
        buttonScale9Copy->setPosition(button->getPosition() + Vec2(0, -60));
        buttonScale9Copy->setScale9Enabled(true);
        buttonScale9Copy->setContentSize(button->getContentSize() * 1.5);
        this->addChild(buttonScale9Copy);
        
        
        auto buttonScale9Copy2 = (Button*)buttonScale9Copy->clone();
        buttonScale9Copy2->setPosition(buttonCopy->getPosition() + Vec2(0, -60));
        buttonScale9Copy2->setScale9Enabled(true);
        buttonScale9Copy2->setContentSize(buttonCopy->getContentSize() * 1.5);
        this->addChild(buttonScale9Copy2);
        
        
        CCASSERT(button->getTitleRenderer() == nullptr,
                 "Original Button title render must be nullptr ");

        CCASSERT(buttonCopy->getTitleRenderer() == nullptr,
                 "Copied Button title render must be nullptr ");

        return true;
    }
    return false;
}

// https://github.com/cocos2d/cocos2d-x/issues/12249
Issue12249::Issue12249()
: _displayValueLabel(nullptr)
{
    
}

bool Issue12249::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the button events will be displayed
        _displayValueLabel = Text::create("Test Issue 12249", "fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                             widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("This test case two buttons should seem to be same!",
                                   "fonts/Marker Felt.ttf",20);
        alert->setColor(Color3B(159, 168, 176));
        
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f
                                - alert->getContentSize().height * 2.0f));
        
        _uiLayer->addChild(alert);
        
        // Create the button 1
        Button* button = nullptr, *button2 = nullptr;
        float btnWidth = 100;
        button = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button->setScale9Enabled(true);
        button->setContentSize(Size(btnWidth, button->getContentSize().height));
        button->setTitleText("Scale9 Button 1");
        button->setPosition(Vec2(widgetSize.width / 2.0f - btnWidth, widgetSize.height / 2.0f));
        _uiLayer->addChild(button);

        // create button 2, load texture after button creation
        button2 = Button::create();
        button2->setScale9Enabled(true);
        button2->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
        button2->setContentSize(Size(btnWidth, button2->getContentSize().height));
        button2->setTitleText("Scale9 Button 2");
        button2->setPosition(Vec2(widgetSize.width / 2.0f + btnWidth, widgetSize.height / 2.0f));
        _uiLayer->addChild(button2);
        
        return true;
    }
    return false;
}

// https://github.com/cocos2d/cocos2d-x/issues/17116
Issue17116::Issue17116()
{
}

bool Issue17116::init()
{
    if (UIScene::init())
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();

        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/issue_17116.plist");
        auto button = ui::Button::create();
        button->loadTextureNormal("buttons/play-big", ui::Widget::TextureResType::PLIST);
        button->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
        button->setOpacity(100);
        addChild(button);
        return true;
    }
    return false;
}

UIButtonWithPolygonInfo::UIButtonWithPolygonInfo()
{
}

bool UIButtonWithPolygonInfo::init()
{
    if (UIScene::init())
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/poly_test_textures.plist");
        auto button = ui::Button::create();
        button->loadTextureNormal("poly_test/wheel_disc_back.png", ui::Widget::TextureResType::PLIST);
        button->setPosition(Vec2(visibleSize.width/2 - 100, visibleSize.height/2));
        button->setScale(0.5);
        button->setScale9Enabled(true);
        addChild(button);
        
        auto buttonCopy = button->clone();
        button->setPosition(Vec2(visibleSize.width/2 + 100, visibleSize.height/2));
        addChild(buttonCopy);
        
        return true;
    }
    return false;
}
