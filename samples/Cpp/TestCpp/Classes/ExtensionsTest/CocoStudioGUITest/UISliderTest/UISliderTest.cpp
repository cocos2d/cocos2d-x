

#include "UISliderTest.h"

const char* font_UISliderTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

// UISliderTest

UISliderTest::UISliderTest()
: m_pDisplayValueLabel(NULL)
{
    
}

UISliderTest::~UISliderTest()
{
}

bool UISliderTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = m_pWidget->getSize();
        
        // Add a label in which the slider alert will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move the slider thumb");
        m_pDisplayValueLabel->setFontName(font_UISliderTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Slider");
        alert->setFontName(font_UISliderTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the slider
        UISlider* slider = UISlider::create();
        slider->setTouchEnabled(true);
        slider->loadBarTexture("cocosgui/sliderTrack.png");
        slider->loadSlidBallTextures("cocosgui/sliderThumb.png", "cocosgui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosgui/sliderProgress.png");
        slider->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        slider->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest::percentChangedEvent));
        m_pUiLayer->addWidget(slider);
        
        return true;
    }
    return false;
}

void UISliderTest::percentChangedEvent(Object *pSender, SliderEventType type)
{
    if (type == SLIDER_PERCENTCHANGED)
    {
        UISlider* slider = dynamic_cast<UISlider*>(pSender);
        int percent = slider->getPercent();
        m_pDisplayValueLabel->setText(CCString::createWithFormat("Percent %d", percent)->getCString());
    }
}

// UISliderTest_Scale9

UISliderTest_Scale9::UISliderTest_Scale9()
: m_pDisplayValueLabel(NULL)
{
    
}

UISliderTest_Scale9::~UISliderTest_Scale9()
{
}

bool UISliderTest_Scale9::init()
{
    if (UIScene::init())
    {
        Size widgetSize = m_pWidget->getSize();
        
        // Add a label in which the slider alert will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move the slider thumb");
        m_pDisplayValueLabel->setFontName(font_UISliderTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Slider scale9 render");
        alert->setFontName(font_UISliderTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the slider
        UISlider* slider = UISlider::create();
        slider->setTouchEnabled(true);
        slider->loadBarTexture("cocosgui/sliderTrack2.png");
        slider->loadSlidBallTextures("cocosgui/sliderThumb.png", "cocosgui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosgui/slider_bar_active_9patch.png");
        slider->setScale9Enabled(true);
        slider->setCapInsets(Rect(0, 0, 0, 0));
        slider->setSize(Size(250, 10));
        slider->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        slider->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest_Scale9::percentChangedEvent));
        m_pUiLayer->addWidget(slider);
        
        return true;
    }
    return false;
}

void UISliderTest_Scale9::percentChangedEvent(Object *pSender, SliderEventType type)
{
    if (type == SLIDER_PERCENTCHANGED)
    {
        UISlider* slider = dynamic_cast<UISlider*>(pSender);
        int percent = slider->getPercent();
        m_pDisplayValueLabel->setText(CCString::createWithFormat("Percent %d", percent)->getCString());
    }
}