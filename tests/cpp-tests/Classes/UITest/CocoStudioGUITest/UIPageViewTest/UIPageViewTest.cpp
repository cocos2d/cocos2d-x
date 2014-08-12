

#include "UIPageViewTest.h"


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

void UIPageViewButtonTest::onButtonClicked(Ref* pSender, Widget::TouchEventType type)
{
    Button *btn = (Button*)pSender;
    CCLOG("button %s clicked", btn->getName().c_str());
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
