

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
        Size widgetSize = _widget->getSize();
        
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
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the page view
        PageView* pageView = PageView::create();
        pageView->setSize(Size(240.0f, 130.0f));
        Size backgroundSize = background->getContentSize();
        pageView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - pageView->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - pageView->getSize().height) / 2.0f));
        
        for (int i = 0; i < 3; ++i)
        {
            Layout* layout = Layout::create();
            layout->setSize(Size(240.0f, 130.0f));
            
            ImageView* imageView = ImageView::create("cocosui/scrollviewbg.png");
            imageView->setScale9Enabled(true);
            imageView->setSize(Size(240, 130));
            imageView->setPosition(Vec2(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
            layout->addChild(imageView);
            
            Text* label = Text::create(StringUtils::format("page %d",(i+1)), "fonts/Marker Felt.ttf", 30);
            label->setColor(Color3B(192, 192, 192));
            label->setPosition(Vec2(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
            layout->addChild(label);
            
            pageView->addPage(layout);
        }
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
