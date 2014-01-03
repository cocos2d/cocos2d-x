

#include "UIPotentiometerTest.h"

// UIPotentiometerTest
UIPotentiometerTest::UIPotentiometerTest()
: m_pDisplayValueLabel(NULL)
{
}

UIPotentiometerTest::~UIPotentiometerTest()
{
}

bool UIPotentiometerTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the button events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getSize().height / 3));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Potentiometer");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2));
        m_pUiLayer->addWidget(alert);
        
        // Create the potentiometer
        UIPotentiometer *potentiometer = UIPotentiometer::create();
        potentiometer->setTouchEnabled(true);
        potentiometer->loadTexture("cocosgui/potentiometerTrack.png", "cocosgui/potentiometerProgress.png", "cocosgui/potentiometerButton.png");
        potentiometer->setPosition(ccp(widgetSize.width / 2 - potentiometer->getSize().width, widgetSize.height / 2));
        potentiometer->addEventListenerPotentiometer(this, potentiometervaluechangedselector(UIPotentiometerTest::valueChangedEvent));
        
        m_pUiLayer->addWidget(potentiometer);
        
        
        // Create the potentiometer with allow min and max value
        UIPotentiometer *potentiometerAllow = UIPotentiometer::create();
        potentiometerAllow->setTouchEnabled(true);
        potentiometerAllow->loadTexture("cocosgui/potentiometerTrack.png", "cocosgui/potentiometerProgress.png", "cocosgui/potentiometerButton.png");
        potentiometerAllow->setPosition(ccp(widgetSize.width / 2 + potentiometerAllow->getSize().width, widgetSize.height / 2));
        potentiometerAllow->addEventListenerPotentiometer(this, potentiometervaluechangedselector(UIPotentiometerTest::valueChangedEvent));
        
        potentiometerAllow->setMinimumAllowValue(0.3);
        potentiometerAllow->setMaximumAllowValue(0.7);
        potentiometerAllow->setValue(0.3);
        
        m_pUiLayer->addWidget(potentiometerAllow);
        
        return true;
    }
    return false;
}

void UIPotentiometerTest::valueChangedEvent(CCObject *pSender, PotentiometerEventType type)
{
    UIPotentiometer *potentiometer = static_cast<UIPotentiometer*>(pSender);
    
    switch (type)
    {
        case POTENTIOMETER_EVENT_VALUECHANGED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("%.02f", potentiometer->getValue())->getCString());
            break;
            
        default:
            break;
    }
}
