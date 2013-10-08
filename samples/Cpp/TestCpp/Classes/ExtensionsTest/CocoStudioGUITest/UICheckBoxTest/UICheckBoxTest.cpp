

#include "UICheckBoxTest.h"

const char* font_UICheckBoxTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

// UICheckBoxTest
UICheckBoxTest::UICheckBoxTest()
: m_pDisplayValueLabel(NULL)
{
    
}

UICheckBoxTest::~UICheckBoxTest()
{
}

bool UICheckBoxTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = m_pWidget->getSize();;
        
        // Add a label in which the checkbox events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName(font_UICheckBoxTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("CheckBox");
        alert->setFontName(font_UICheckBoxTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the checkbox
        UICheckBox* checkBox = UICheckBox::create();
        checkBox->setTouchEnabled(true);
        checkBox->loadTextures("cocosgui/check_box_normal.png",
                               "cocosgui/check_box_normal_press.png",
                               "cocosgui/check_box_active.png",
                               "cocosgui/check_box_normal_disable.png",
                               "cocosgui/check_box_active_disable.png");
        checkBox->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        
        checkBox->addEventListener(this, checkboxselectedeventselector(UICheckBoxTest::selectedEvent));
        
//        checkBox->addSelectEvent(this, coco_selectselector(UICheckBoxTest::selectedEvent));
        m_pUiLayer->addWidget(checkBox);
        
        return true;
    }
    return false;
}

void UICheckBoxTest::selectedEvent(Object* pSender,CheckBoxEventType type)
{
    switch (type) {
        case cocos2d::extension::CHECKBOX_STATE_EVENT_SELECTED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Selected")->getCString());
            break;
        case cocos2d::extension::CHECKBOX_STATE_EVENT_UNSELECTED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Unselected")->getCString());
            break;
        default:
            break;
    }
    
}