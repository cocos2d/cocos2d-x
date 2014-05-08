

#include "UISliderTest.h"


// UISliderTest

UISliderTest::UISliderTest()
: m_pDisplayValueLabel(NULL)
{
    
}

UISliderTest::~UISliderTest()
{
}

/*===*/
bool UISliderTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
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
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the slider
        UISlider* slider = UISlider::create();
        slider->setTouchEnabled(true);
        slider->loadBarTexture("cocosui/sliderTrack.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosui/sliderProgress.png");
        slider->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
//        slider->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + slider->getSize().height * 2));
        slider->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest::sliderEvent));
        m_pUiLayer->addWidget(slider);

        /*
        // Create the slider that set allow min progress and allow max progress
        UISlider* sliderAllow = UISlider::create();
        //===//
//        sliderAllow->setMinAllowPercent(20);
//        sliderAllow->setMaxAllowPercent(80);
        //
        sliderAllow->setTouchEnabled(true);
        sliderAllow->loadBarTexture("cocosui/sliderTrack.png");
        sliderAllow->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        sliderAllow->loadProgressBarTexture("cocosui/sliderProgress.png");
        sliderAllow->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - sliderAllow->getSize().height * 2));
        sliderAllow->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest::sliderEvent));
        m_pUiLayer->addWidget(sliderAllow);
         */
        
        return true;
    }
    return false;
}
/*=*/

void UISliderTest::sliderEvent(CCObject *pSender, SliderEventType type)
{
    switch (type)
    {
        case SLIDER_PERCENTCHANGED:
        {
            UISlider* slider = dynamic_cast<UISlider*>(pSender);
            int percent = slider->getPercent();
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Percent %d", percent)->getCString());
        }
            break;
            
        default:
            break;
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

/*===*/
bool UISliderTest_Scale9::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
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
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the slider
        UISlider* slider = UISlider::create();
        slider->setTouchEnabled(true);
        slider->loadBarTexture("cocosui/sliderTrack2.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosui/slider_bar_active_9patch.png");
        slider->setScale9Enabled(true);
        slider->setCapInsets(CCRectMake(0, 0, 0, 0));
        slider->setSize(CCSizeMake(250, 19));
        slider->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
//        slider->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + slider->getSize().height * 2));
        slider->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest_Scale9::sliderEvent));
        m_pUiLayer->addWidget(slider);

        /*
        // Create the slider that set allow min progress and allow max progress
        UISlider* sliderAllow = UISlider::create();
        //===//
//        sliderAllow->setMinAllowPercent(20);
//        sliderAllow->setMaxAllowPercent(80);
        //
        sliderAllow->setTouchEnabled(true);
        sliderAllow->loadBarTexture("cocosui/sliderTrack2.png");
        sliderAllow->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        sliderAllow->loadProgressBarTexture("cocosui/slider_bar_active_9patch.png");
        sliderAllow->setScale9Enabled(true);
        sliderAllow->setCapInsets(CCRectMake(0, 0, 0, 0));
        sliderAllow->setSize(CCSizeMake(250, 10));
        sliderAllow->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - slider->getSize().height * 2));
        sliderAllow->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest_Scale9::sliderEvent));
        m_pUiLayer->addWidget(sliderAllow);
        */
        
        return true;
    }
    return false;
}
/*=*/

void UISliderTest_Scale9::sliderEvent(CCObject *pSender, SliderEventType type)
{
    switch (type)
    {
        case SLIDER_PERCENTCHANGED:
        {
            UISlider* slider = dynamic_cast<UISlider*>(pSender);
            int percent = slider->getPercent();
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Percent %d", percent)->getCString());
        }
            break;
            
        default:
            break;
    }
}
