#include "UIPageViewTest.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIPageViewTests::UIPageViewTests()
{
    ADD_TEST_CASE(UIPageViewTest);
    ADD_TEST_CASE(UIPageViewButtonTest);
    ADD_TEST_CASE(UIPageViewCustomScrollThreshold);
    ADD_TEST_CASE(UIPageViewTouchPropagationTest);
    ADD_TEST_CASE(UIPageViewDynamicAddAndRemoveTest);
}

// UIPageViewTest
UIPageViewTest::UIPageViewTest()
: _displayValueLabel(nullptr)
{
    
}

UIPageViewTest::~UIPageViewTest()
{
}

bool UIPageViewTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the dragpanel events will be displayed
        _displayValueLabel = Text::create("Move by horizontal direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                              widgetSize.height / 2.0f +
                                              _displayValueLabel->getContentSize().height * 1.5));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the black background
        Text* alert = Text::create("PageView", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the page view
        PageView* pageView = PageView::create();
        pageView->setContentSize(Size(240.0f, 130.0f));
        Size backgroundSize = background->getContentSize();
        pageView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - pageView->getContentSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - pageView->getContentSize().height) / 2.0f));
        
        pageView->removeAllPages();
        
        int pageCount = 4;
        for (int i = 0; i < pageCount; ++i)
        {
            Layout* layout = Layout::create();
            layout->setContentSize(Size(240.0f, 130.0f));
            
            ImageView* imageView = ImageView::create("cocosui/scrollviewbg.png");
            imageView->setScale9Enabled(true);
            imageView->setContentSize(Size(240, 130));
            imageView->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
            layout->addChild(imageView);
            
            Text* label = Text::create(StringUtils::format("page %d",(i+1)), "fonts/Marker Felt.ttf", 30);
            label->setColor(Color3B(192, 192, 192));
            label->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
            layout->addChild(label);
            
            pageView->insertPage(layout,i);
        }
        
        pageView->removePageAtIndex(0);
        pageView->scrollToPage(pageCount-2);
        
        pageView->addEventListener(CC_CALLBACK_2(UIPageViewTest::pageViewEvent, this));
        
        _uiLayer->addChild(pageView);
        
        return true;
    }
    return false;
}

void UIPageViewTest::pageViewEvent(Ref *pSender, PageView::EventType type)
{
    switch (type)
    {
        case PageView::EventType::TURNING:
        {
            PageView* pageView = dynamic_cast<PageView*>(pSender);
            
            _displayValueLabel->setString(CCString::createWithFormat("page = %ld", pageView->getCurPageIndex() + 1)->getCString());
        }
            break;
            
        default:
            break;
    }
}


// UIPageViewButtonTest
UIPageViewButtonTest::UIPageViewButtonTest()
: _displayValueLabel(nullptr)
{
    
}

UIPageViewButtonTest::~UIPageViewButtonTest()
{
}

bool UIPageViewButtonTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the dragpanel events will be displayed
        _displayValueLabel = Text::create("Move by horizontal direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                             widgetSize.height / 2.0f +
                                             _displayValueLabel->getContentSize().height * 1.5));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the black background
        Text* alert = Text::create("PageView with Buttons", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the page view
        PageView* pageView = PageView::create();
        pageView->setContentSize(Size(240.0f, 130.0f));
        Size backgroundSize = background->getContentSize();
        pageView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                   (backgroundSize.width - pageView->getContentSize().width) / 2.0f,
                                   (widgetSize.height - backgroundSize.height) / 2.0f +
                                   (backgroundSize.height - pageView->getContentSize().height) / 2.0f));
        
        pageView->removeAllPages();
        
        int pageCount = 4;
        for (int i = 0; i < pageCount; ++i)
        {
            HBox* outerBox = HBox::create();
            outerBox->setContentSize(Size(240.0f, 130.0f));

            for (int k = 0; k < 2; ++k) {
                VBox* innerBox = VBox::create();
                
                for (int j = 0; j < 3; j++) {
                    Button *btn = Button::create("cocosui/animationbuttonnormal.png",
                                                 "cocosui/animationbuttonpressed.png");
                    btn->setName(StringUtils::format("button %d", j));
                    btn->addTouchEventListener( CC_CALLBACK_2(UIPageViewButtonTest::onButtonClicked, this));
                    
                    innerBox->addChild(btn);
                }
                
                LinearLayoutParameter *parameter = LinearLayoutParameter::create();
                parameter->setMargin(Margin(0,0,100,0));
                innerBox->setLayoutParameter(parameter);
                
                outerBox->addChild(innerBox);

            }
            
            pageView->insertPage(outerBox,i);
        }
        
        pageView->removePageAtIndex(0);
        
        pageView->addEventListener(CC_CALLBACK_2(UIPageViewButtonTest::pageViewEvent, this));
        
        _uiLayer->addChild(pageView);
        
        return true;
    }
    return false;
}

void UIPageViewButtonTest::onButtonClicked(Ref* sender, Widget::TouchEventType type)
{
    log("button %s clicked", static_cast<Button*>(sender)->getName().c_str());
}


void UIPageViewButtonTest::pageViewEvent(Ref *pSender, PageView::EventType type)
{
    switch (type)
    {
        case PageView::EventType::TURNING:
        {
            PageView* pageView = dynamic_cast<PageView*>(pSender);
            
            _displayValueLabel->setString(CCString::createWithFormat("page = %ld", pageView->getCurPageIndex() + 1)->getCString());
        }
            break;
            
        default:
            break;
    }
}


// UIPageViewCustomScrollThreshold
UIPageViewCustomScrollThreshold::UIPageViewCustomScrollThreshold()
: _displayValueLabel(nullptr)
{
    
}

UIPageViewCustomScrollThreshold::~UIPageViewCustomScrollThreshold()
{
}

bool UIPageViewCustomScrollThreshold::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the dragpanel events will be displayed
        _displayValueLabel = Text::create("Scroll Threshold", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                             widgetSize.height / 2.0f +
                                             _displayValueLabel->getContentSize().height * 1.5));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the black background
        Text* alert = Text::create("PageView", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the page view
        PageView* pageView = PageView::create();
        pageView->setContentSize(Size(240.0f, 100.0f));
        Size backgroundSize = background->getContentSize();
        pageView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                   (backgroundSize.width - pageView->getContentSize().width) / 2.0f,
                                   (widgetSize.height - backgroundSize.height) / 2.0f +
                                   (backgroundSize.height - pageView->getContentSize().height) / 2.0f + 20));
        
        int pageCount = 4;
        for (int i = 0; i < pageCount; ++i)
        {
            Layout* layout = Layout::create();
            layout->setContentSize(Size(240.0f, 130.0f));
            
            ImageView* imageView = ImageView::create("cocosui/scrollviewbg.png");
            imageView->setScale9Enabled(true);
            imageView->setContentSize(Size(240, 130));
            imageView->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
            layout->addChild(imageView);
            
            Text* label = Text::create(StringUtils::format("page %d",(i+1)), "fonts/Marker Felt.ttf", 30);
            label->setColor(Color3B(192, 192, 192));
            label->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
            layout->addChild(label);
            
            pageView->insertPage(layout,i);
        }
        
        _uiLayer->addChild(pageView);
        pageView->setName("pageView");
        
        Slider* slider = Slider::create();
        slider->loadBarTexture("cocosui/sliderTrack.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosui/sliderProgress.png");
        slider->setPosition(Vec2(widgetSize.width / 2.0f , widgetSize.height / 2.0f - 40));
        slider->addEventListener(CC_CALLBACK_2(UIPageViewCustomScrollThreshold::sliderEvent, this));
        slider->setPercent(50);
        _uiLayer->addChild(slider);

        
        return true;
    }
    return false;
}


void UIPageViewCustomScrollThreshold::sliderEvent(Ref *pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percent = slider->getPercent();
        PageView* pageView = (PageView*)_uiLayer->getChildByName("pageView");
        if (percent == 0) {
            percent = 1;
        }
        pageView->setCustomScrollThreshold(percent * 0.01 * pageView->getContentSize().width);
        
        _displayValueLabel->setString(String::createWithFormat("Scroll Threshold: %f", pageView->getCustomScrollThreshold())->getCString());
    }
}

// UIPageViewTouchPropagationTest
UIPageViewTouchPropagationTest::UIPageViewTouchPropagationTest()
: _displayValueLabel(nullptr)
{
    
}

UIPageViewTouchPropagationTest::~UIPageViewTouchPropagationTest()
{
}

bool UIPageViewTouchPropagationTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the dragpanel events will be displayed
        _displayValueLabel = Text::create("Move by horizontal direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                             widgetSize.height / 2.0f +
                                             _displayValueLabel->getContentSize().height * 1.5));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the black background
        Text* alert = Text::create("PageView Touch Propagation", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the page view
        PageView* pageView = PageView::create();
        pageView->setContentSize(Size(240.0f, 130.0f));
        pageView->setAnchorPoint(Vec2(0.5,0.5));
        Size backgroundSize = background->getContentSize();
        pageView->setPosition(Vec2(widgetSize.width / 2.0f ,widgetSize.height / 2.0f));
        pageView->setBackGroundColor(Color3B::GREEN);
        pageView->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        
        int pageCount = 4;
        for (int i = 0; i < pageCount; ++i)
        {
            HBox* outerBox = HBox::create();
            outerBox->setContentSize(Size(240.0f, 130.0f));
            
            for (int k = 0; k < 2; ++k) {
                VBox* innerBox = VBox::create();
                
                for (int j = 0; j < 3; j++) {
                    Button *btn = Button::create("cocosui/animationbuttonnormal.png",
                                                 "cocosui/animationbuttonpressed.png");
                    btn->setName(StringUtils::format("button %d", j));
                    btn->addTouchEventListener( CC_CALLBACK_2(UIPageViewTouchPropagationTest::onButtonClicked, this));
                    
                    innerBox->addChild(btn);
                }
                
                LinearLayoutParameter *parameter = LinearLayoutParameter::create();
                parameter->setMargin(Margin(0,0,100,0));
                innerBox->setLayoutParameter(parameter);
                
                outerBox->addChild(innerBox);
                
            }
            
            pageView->insertPage(outerBox,i);
        }
        
        pageView->addEventListener(CC_CALLBACK_2(UIPageViewTouchPropagationTest::pageViewEvent, this));
        pageView->setName("pageView");
        pageView->addTouchEventListener([](Ref* sender, Widget::TouchEventType type){
            if (type == Widget::TouchEventType::BEGAN)
            {
                CCLOG("page view touch began");
            }
            else if(type == Widget::TouchEventType::MOVED)
            {
                CCLOG("page view touch moved");
            }
            else if(type == Widget::TouchEventType::ENDED)
            {
                CCLOG("page view touch ended");
            }
            else
            {
                CCLOG("page view touch cancelled");
            }
        });
        _uiLayer->addChild(pageView);
        
        Text *propagationText = Text::create("Allow Propagation", "Arial", 10);
        propagationText->setAnchorPoint(Vec2(0,0.5));
        propagationText->setTextColor(Color4B::RED);
        propagationText->setPosition(Vec2(0, pageView->getPosition().y + 50));
        _uiLayer->addChild(propagationText);
        
        Text *swallowTouchText = Text::create("Swallow Touches", "Arial", 10);
        swallowTouchText->setAnchorPoint(Vec2(0,0.5));
        swallowTouchText->setTextColor(Color4B::RED);
        swallowTouchText->setPosition(Vec2(0, pageView->getPosition().y));
        _uiLayer->addChild(swallowTouchText);
        
        // Create the checkbox
        CheckBox* checkBox1 = CheckBox::create("cocosui/check_box_normal.png",
                                              "cocosui/check_box_normal_press.png",
                                              "cocosui/check_box_active.png",
                                              "cocosui/check_box_normal_disable.png",
                                              "cocosui/check_box_active_disable.png");
        checkBox1->setPosition(propagationText->getPosition() + Vec2(propagationText->getContentSize().width/2, -20));
        
        checkBox1->setName("propagation");
        _uiLayer->addChild(checkBox1);
        
        
        // Create the checkbox
        CheckBox* checkBox2 = CheckBox::create("cocosui/check_box_normal.png",
                                              "cocosui/check_box_normal_press.png",
                                              "cocosui/check_box_active.png",
                                              "cocosui/check_box_normal_disable.png",
                                              "cocosui/check_box_active_disable.png");
        checkBox2->setPosition(swallowTouchText->getPosition() + Vec2(swallowTouchText->getContentSize().width/2, -20));

        checkBox2->setName("swallow");
        _uiLayer->addChild(checkBox2);

        
        auto eventListener = EventListenerTouchOneByOne::create();
        eventListener->onTouchBegan = [](Touch* touch, Event* event) -> bool{
            CCLOG("layout recieves touches");
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
        
        return true;
    }
    return false;
}

void UIPageViewTouchPropagationTest::onButtonClicked(Ref* pSender, Widget::TouchEventType type)
{
    Button *btn = (Button*)pSender;
    CheckBox *ck1 = (CheckBox*)_uiLayer->getChildByName("propagation");
    CheckBox *ck2 = (CheckBox*)_uiLayer->getChildByName("swallow");
    auto pageView = (PageView*)_uiLayer->getChildByName("pageView");
    
    if (type == Widget::TouchEventType::BEGAN)
    {
        if (ck1->isSelected())
        {
            btn->setPropagateTouchEvents(true);
            pageView->setPropagateTouchEvents(true);
            
        }else
        {
            btn->setPropagateTouchEvents(false);
            pageView->setPropagateTouchEvents(false);
        }
        
        if (ck2->isSelected())
        {
            btn->setSwallowTouches(true);
            pageView->setSwallowTouches(true);
        }else
        {
            btn->setSwallowTouches(false);
            pageView->setSwallowTouches(false);
        }
    }
    if (type == Widget::TouchEventType::ENDED) {
        CCLOG("button clicked");
    }
}


void UIPageViewTouchPropagationTest::pageViewEvent(Ref *pSender, PageView::EventType type)
{
    switch (type)
    {
        case PageView::EventType::TURNING:
        {
            PageView* pageView = dynamic_cast<PageView*>(pSender);
            
            _displayValueLabel->setString(CCString::createWithFormat("page = %ld", pageView->getCurPageIndex() + 1)->getCString());
        }
            break;
            
        default:
            break;
    }
}

// UIPageViewDynamicAddAndRemoveTest
UIPageViewDynamicAddAndRemoveTest::UIPageViewDynamicAddAndRemoveTest()
: _displayValueLabel(nullptr)
{
    
}

UIPageViewDynamicAddAndRemoveTest::~UIPageViewDynamicAddAndRemoveTest()
{
}

bool UIPageViewDynamicAddAndRemoveTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the dragpanel events will be displayed
        _displayValueLabel = Text::create("Click Buttons on the Left", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                             widgetSize.height / 2.0f +
                                             _displayValueLabel->getContentSize().height * 1.5));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the black background
        Text* alert = Text::create("PageView Dynamic Modification", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the page view
        PageView* pageView = PageView::create();
        pageView->setContentSize(Size(240.0f, 130.0f));
        pageView->setAnchorPoint(Vec2(0.5,0.5));
        Size backgroundSize = background->getContentSize();
        pageView->setPosition(Vec2(widgetSize.width / 2.0f ,widgetSize.height / 2.0f));
        pageView->setBackGroundColor(Color3B::GREEN);
        pageView->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        
        int pageCount = 4;
        for (int i = 0; i < pageCount; ++i)
        {
            HBox* outerBox = HBox::create();
            outerBox->setContentSize(Size(240.0f, 130.0f));
            
            for (int k = 0; k < 2; ++k)
            {
                VBox* innerBox = VBox::create();
                
                for (int j = 0; j < 3; j++)
                {
                    Button *btn = Button::create("cocosui/animationbuttonnormal.png",
                                                 "cocosui/animationbuttonpressed.png");
                    btn->setName(StringUtils::format("button %d", j));
                    
                    innerBox->addChild(btn);
                }
                
                LinearLayoutParameter *parameter = LinearLayoutParameter::create();
                parameter->setMargin(Margin(0,0,100,0));
                innerBox->setLayoutParameter(parameter);
                
                outerBox->addChild(innerBox);
                
            }
            
            pageView->insertPage(outerBox,i);
        }
        
        pageView->addEventListener(CC_CALLBACK_2(UIPageViewDynamicAddAndRemoveTest::pageViewEvent, this));
        pageView->setName("pageView");
        _uiLayer->addChild(pageView);
        
        //add buttons
        auto button = Button::create();
        button->setNormalizedPosition(Vec2(0.12f,0.7f));
        button->setTitleText("Add A Page");
        button->setZoomScale(0.3f);
        button->setPressedActionEnabled(true);
        button->setTitleColor(Color3B::RED);
        button->addClickEventListener([=](Ref* sender)
        {
            HBox* outerBox = HBox::create();
            outerBox->setContentSize(Size(240.0f, 130.0f));
            
            for (int k = 0; k < 2; ++k)
            {
                VBox* innerBox = VBox::create();
                
                for (int j = 0; j < 3; j++)
                {
                    Button *btn = Button::create("cocosui/animationbuttonnormal.png",
                                                 "cocosui/animationbuttonpressed.png");
                    btn->setName(StringUtils::format("button %d", j));
                    
                    innerBox->addChild(btn);
                }
                
                LinearLayoutParameter *parameter = LinearLayoutParameter::create();
                parameter->setMargin(Margin(0,0,100,0));
                innerBox->setLayoutParameter(parameter);
                
                outerBox->addChild(innerBox);
                
            }
            
            pageView->addPage(outerBox);
            _displayValueLabel->setString(CCString::createWithFormat("page count = %ld", pageView->getPages().size())->getCString());

        });
        _uiLayer->addChild(button);
        
        auto button2 = Button::create();
        button2->setNormalizedPosition(Vec2(0.12f,0.5f));
        button2->setTitleText("Remove A Page");
        button2->setZoomScale(0.3f);
        button2->setPressedActionEnabled(true);
        button2->setTitleColor(Color3B::RED);
        button2->addClickEventListener([=](Ref* sender)
        {
            if (pageView->getPages().size() > 0)
            {
                pageView->removePageAtIndex(pageView->getPages().size()-1);
            }
            else
            {
                CCLOG("There is no page to remove!");
            }
            _displayValueLabel->setString(CCString::createWithFormat("page count = %ld", pageView->getPages().size())->getCString());

        });
        _uiLayer->addChild(button2);
        
        auto button3 = Button::create();
        button3->setNormalizedPosition(Vec2(0.12f,0.3f));
        button3->setTitleText("Remove All Pages");
        button3->setZoomScale(0.3f);
        button3->setPressedActionEnabled(true);
        button3->setTitleColor(Color3B::RED);
        button3->addClickEventListener([=](Ref* sender)
        {
            pageView->removeAllPages();
            _displayValueLabel->setString(CCString::createWithFormat("page count = %ld", pageView->getPages().size())->getCString());

        });
        _uiLayer->addChild(button3);

        
        
        return true;
    }
    return false;
}


void UIPageViewDynamicAddAndRemoveTest::pageViewEvent(Ref *pSender, PageView::EventType type)
{
    switch (type)
    {
        case PageView::EventType::TURNING:
        {
            PageView* pageView = dynamic_cast<PageView*>(pSender);
            
            _displayValueLabel->setString(CCString::createWithFormat("page = %ld", pageView->getCurPageIndex() + 1)->getCString());
        }
            break;
            
        default:
            break;
    }
}

