

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
        CCSize widgetSize = m_pWidget->getRect().size;;
        
        // Add a label in which the checkbox events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("CheckBox");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the checkbox
        UICheckBox* checkBox = UICheckBox::create();
        checkBox->setTouchEnable(true);
        checkBox->setTextures("cocosgui/check_box_normal.png",
                              "cocosgui/check_box_normal_press.png",
                              "cocosgui/check_box_active.png",
                              "cocosgui/check_box_normal_disable.png",
                              "cocosgui/check_box_active_disable.png");
        checkBox->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        checkBox->addSelectEvent(this, coco_selectselector(UICheckBoxTest::selectedEvent));
        checkBox->addUnSelectEvent(this, coco_selectselector(UICheckBoxTest::unSelectedEvent));
        m_pUiLayer->addWidget(checkBox);
        
        return true;
    }
    return false;
}

void UICheckBoxTest::selectedEvent(CCObject* pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Selected")->getCString());
}

void UICheckBoxTest::unSelectedEvent(CCObject* pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Unselected")->getCString());
}