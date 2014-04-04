

#include "UIPageViewTest.h"


// UIPageViewTest
UIPageViewTest::UIPageViewTest()
: _displayValueLabel(NULL)
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
        _displayValueLabel = Text::create();
        _displayValueLabel->setText("Move by horizontal direction");
        _displayValueLabel->setFontName("fonts/Marker Felt.ttf");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the black background
        Text* alert = Text::create();
        alert->setText("PageView");
        alert->setFontName("fonts/Marker Felt.ttf");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the page view
        PageView* pageView = PageView::create();
        pageView->setTouchEnabled(true);
        pageView->setSize(Size(240.0f, 130.0f));
        Size backgroundSize = background->getContentSize();
        pageView->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - pageView->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - pageView->getSize().height) / 2.0f));
        
        for (int i = 0; i < 3; ++i)
        {
            Layout* layout = Layout::create();
            layout->setSize(Size(240.0f, 130.0f));
            
            ImageView* imageView = ImageView::create();
            imageView->setTouchEnabled(true);
            imageView->setScale9Enabled(true);
            imageView->loadTexture("cocosui/scrollviewbg.png");
            imageView->setSize(Size(240, 130));
            imageView->setPosition(Point(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
            layout->addChild(imageView);
            
            Text* label = Text::create();
            label->setText(CCString::createWithFormat("page %d", (i + 1))->getCString());
            label->setFontName("fonts/Marker Felt.ttf");
            label->setFontSize(30);
            label->setColor(Color3B(192, 192, 192));
            label->setPosition(Point(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
            layout->addChild(label);
            
            pageView->addPage(layout);
        }
        pageView->addEventListenerPageView(this, pagevieweventselector(UIPageViewTest::pageViewEvent));
        
        _uiLayer->addChild(pageView);
        
        return true;
    }
    return false;
}

void UIPageViewTest::pageViewEvent(Ref *pSender, PageViewEventType type)
{
    switch (type)
    {
        case PAGEVIEW_EVENT_TURNING:
        {
            PageView* pageView = dynamic_cast<PageView*>(pSender);
            
            _displayValueLabel->setText(CCString::createWithFormat("page = %ld", pageView->getCurPageIndex() + 1)->getCString());
        }
            break;
            
        default:
            break;
    }
}
