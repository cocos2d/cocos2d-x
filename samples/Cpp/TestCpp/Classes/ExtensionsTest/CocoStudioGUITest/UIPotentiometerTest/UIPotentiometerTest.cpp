

#include "UIPotentiometerTest.h"

// UIPotentiometerTest
UIPotentiometerTest::UIPotentiometerTest()
: _displayValueLabel(NULL)
{
}

UIPotentiometerTest::~UIPotentiometerTest()
{
}

bool UIPotentiometerTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the button events will be displayed
        _displayValueLabel = gui::Label::create();
        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getSize().height / 3));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Potentiometer");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2));
        _uiLayer->addChild(alert);
        
        // Create the potentiometer
        Potentiometer *potentiometer = Potentiometer::create();
        potentiometer->setTouchEnabled(true);
        potentiometer->loadTexture("cocosgui/potentiometerTrack.png", "cocosgui/potentiometerProgress.png", "cocosgui/potentiometerButton.png");
        potentiometer->setPosition(Point(widgetSize.width / 2 - potentiometer->getSize().width, widgetSize.height / 2));
        potentiometer->addEventListenerPotentiometer(this, potentiometervaluechangedselector(UIPotentiometerTest::valueChangedEvent));
        
        _uiLayer->addChild(potentiometer);
        
        
        // Create the potentiometer with allow min and max value
        Potentiometer *potentiometerAllow = Potentiometer::create();
        potentiometerAllow->setTouchEnabled(true);
        potentiometerAllow->loadTexture("cocosgui/potentiometerTrack.png", "cocosgui/potentiometerProgress.png", "cocosgui/potentiometerButton.png");
        potentiometerAllow->setPosition(Point(widgetSize.width / 2 + potentiometerAllow->getSize().width, widgetSize.height / 2));
        potentiometerAllow->addEventListenerPotentiometer(this, potentiometervaluechangedselector(UIPotentiometerTest::valueChangedEvent));
        
        potentiometerAllow->setMinimumAllowValue(0.3);
        potentiometerAllow->setMaximumAllowValue(0.7);
        potentiometerAllow->setValue(0.3);
        
        _uiLayer->addChild(potentiometerAllow);
        
        return true;
    }
    return false;
}

void UIPotentiometerTest::valueChangedEvent(Object *pSender, PotentiometerEventType type)
{
    Potentiometer* potentiometer = static_cast<Potentiometer*>(pSender);
    
    switch (type)
    {
        case POTENTIOMETER_EVENT_VALUECHANGED:
            _displayValueLabel->setText(CCString::createWithFormat("%.02f", potentiometer->getValue())->getCString());
            break;
            
        default:
            break;
    }
}
