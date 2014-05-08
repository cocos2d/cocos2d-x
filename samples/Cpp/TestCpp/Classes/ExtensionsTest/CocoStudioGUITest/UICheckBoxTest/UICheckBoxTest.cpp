

#include "UICheckBoxTest.h"


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
        CCSize widgetSize = m_pWidget->getSize();;
        
        // Add a label in which the checkbox events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("CheckBox");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the checkbox
        UICheckBox* checkBox = UICheckBox::create();
        checkBox->setTouchEnabled(true);
        checkBox->loadTextures("cocosui/check_box_normal.png",
                              "cocosui/check_box_normal_press.png",
                              "cocosui/check_box_active.png",
                              "cocosui/check_box_normal_disable.png",
                              "cocosui/check_box_active_disable.png");
        checkBox->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        checkBox->addEventListenerCheckBox(this, checkboxselectedeventselector(UICheckBoxTest::selectedStateEvent));
        m_pUiLayer->addWidget(checkBox);
        
        return true;
    }
    return false;
}

void UICheckBoxTest::selectedStateEvent(CCObject *pSender, CheckBoxEventType type)
{
    switch (type)
    {
        case CHECKBOX_STATE_EVENT_UNSELECTED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Unselected")->getCString());
            break;
            
        case CHECKBOX_STATE_EVENT_SELECTED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Selected")->getCString());
            break;
            
        default:
            break;
    }
}
