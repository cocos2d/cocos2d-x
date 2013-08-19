

#include "UISliderTest.h"

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
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the slider alert will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move the slider thumb");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Slider");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the slider
        UISlider* slider = UISlider::create();
        slider->setTouchEnable(true);
        slider->setBarTexture("cocosgui/sliderTrack.png");
        slider->setSlidBallTextures("cocosgui/sliderThumb.png", "cocosgui/sliderThumb.png", "");
        slider->setProgressBarVisible(true);
        slider->setProgressBarTexture("cocosgui/sliderProgress.png");
        slider->setSlidBallAnchorPoint(ccp(0.6, 0.5));
        slider->setSlidBallPercent(0);
        slider->setProgressBarScale();
        slider->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        slider->addPercentChangedEvent(this, coco_percentchangedselector(UISliderTest::percentChangedEvent));
        m_pUiLayer->addWidget(slider);
        
        return true;
    }
    return false;
}

void UISliderTest::percentChangedEvent(CCObject *pSender)
{
    UISlider* slider = dynamic_cast<UISlider*>(pSender);
    int percent = slider->getPercent();
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Percent %d", percent)->getCString());
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
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the slider alert will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move the slider thumb");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Slider scale9 render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the slider
        UISlider* slider = UISlider::create();
        slider->setTouchEnable(true);        
        slider->setBarTexture("cocosgui/sliderTrack2.png");
        slider->setSlidBallTextures("cocosgui/sliderThumb.png", "cocosgui/sliderThumb.png", "");
        slider->setProgressBarVisible(true);
        slider->setProgressBarTexture("cocosgui/slider_bar_active_9patch.png");
        slider->setScale9Enable(true);
        slider->setCapInsets(CCRectMake(0, 0, 0, 0));
        slider->setScale9Size(CCSizeMake(250, slider->getRect().size.height));
        slider->setProgressBarScale9Enable(true);
        slider->setProgressBarCapInsets(CCRectMake(0, 0, 0, 0));
        slider->setProgressBarScale9Size(CCSizeMake(250, slider->getProgressBarTextureSize().height));
        slider->setSlidBallPercent(0);
        slider->setProgressBarScale();
        slider->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        slider->addPercentChangedEvent(this, coco_percentchangedselector(UISliderTest_Scale9::percentChangedEvent));
        m_pUiLayer->addWidget(slider);
        
        return true;
    }
    return false;
}

void UISliderTest_Scale9::percentChangedEvent(CCObject *pSender)
{
    UISlider* slider = dynamic_cast<UISlider*>(pSender);
    int percent = slider->getPercent();
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Percent %d", percent)->getCString());
}