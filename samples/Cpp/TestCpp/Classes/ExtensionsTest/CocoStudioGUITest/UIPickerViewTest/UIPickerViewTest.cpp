

#include "UIPickerViewTest.h"

// UIPickerViewTest_Vertical

UIPickerViewTest_Vertical::UIPickerViewTest_Vertical()
{
    
}

UIPickerViewTest_Vertical::~UIPickerViewTest_Vertical()
{
    CC_SAFE_RELEASE(m_array);
}

bool UIPickerViewTest_Vertical::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by vertical direction");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        
        UILabel* alert = UILabel::create();
        alert->setText("PickerView vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        m_pUiLayer->addWidget(alert);
        
        Layout* background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        CCSize backgroundSize = background->getContentSize();
        
        
        // create picker view data
        m_array = CCArray::create();
        CC_SAFE_RETAIN(m_array);
        for (int i = 0; i < 20; ++i)
        {
            CCString* ccstr = CCString::createWithFormat("pickerview_%d", i);
            m_array->addObject(ccstr);
        }
        
        
        // Create the picker view
        UIPickerView* pickerView = UIPickerView::create();
        // set picker view direction
        pickerView->setDirection(SCROLLVIEW_DIR_VERTICAL);
        pickerView->setTouchEnabled(true);
        pickerView->setBounceEnabled(true);
        pickerView->setBackGroundImage("cocosgui/yellow_edit.png");
        pickerView->setBackGroundImageScale9Enabled(true);
        pickerView->setSize(CCSizeMake(240, 150));
        pickerView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                    (backgroundSize.width - pickerView->getSize().width) / 2,
                                    (widgetSize.height - backgroundSize.height) / 2 +
                                    (backgroundSize.height - pickerView->getSize().height) / 2));
        pickerView->addEventListenerScrollView(this, scrollvieweventselector(UIPickerViewTest_Vertical::selectedItemEvent));
        pickerView->addEventListenerPickerView(this, pickervieweventselector(UIPickerViewTest_Vertical::pickItemEvent));
        m_pUiLayer->addWidget(pickerView);
        
        int count = m_array->count();
        pickerView->setItemCountInContainerWithOddNumber(count / 5);
        
        for (int i = 0; i < count; ++i)
        {
            UIButton* button = UIButton::create();
            button->loadTextures("cocosgui/orange_edit.png", "cocosgui/orange_edit.png", "");
            button->setScale9Enabled(true);
            button->setSize(CCSizeMake(100,
                                       pickerView->getSize().height / pickerView->getItemCountInContainerWithOddNumber()));
            button->setTitleText(static_cast<CCString*>(m_array->objectAtIndex(i))->getCString());
            
            pickerView->addChild(button);
        }
        
        pickerView->refreshView();
        
        // create picker render of picker view
        UIButton* button_0 = static_cast<UIButton*>(pickerView->getChildren()->objectAtIndex(0));
        pickerView->loadPickerTexture("cocosgui/green_edit.png");
        CCScale9Sprite* pickerRender = pickerView->getPickerRender();
        pickerRender->setOpacity(pickerView->getOpacity() / 3);
        pickerRender->setPreferredSize(CCSizeMake(pickerView->getSize().width, button_0->getSize().height));
        
        return true;
    }
    
    return false;
}

void UIPickerViewTest_Vertical::selectedItemEvent(CCObject *pSender, ScrollviewEventType type)
{
    switch (type)
    {
        case SCROLLVIEW_EVENT_SELECT_CHILD:
        {
            UIPickerView* pickerView = static_cast<UIPickerView*>(pSender);
            CCLOG("select child index = %d", pickerView->getSelectedChildIndex());
        }
            break;
            
        default:
            break;
    }
}

void UIPickerViewTest_Vertical::pickItemEvent(CCObject *pSender, PickerViewEventType type)
{
    switch (type)
    {
        case PICKERVIEW_EVENT_PICK_ITEM:
            {
                UIPickerView* pickerView = static_cast<UIPickerView*>(pSender);
                CCLOG("picker view pick index = %d", pickerView->getPickIndex());
            }
            break;
            
        default:
            break;
    }
}

// UIPickerViewTest_Horizontal

UIPickerViewTest_Horizontal::UIPickerViewTest_Horizontal()
{
    
}

UIPickerViewTest_Horizontal::~UIPickerViewTest_Horizontal()
{
    CC_SAFE_RELEASE(m_array);
}

bool UIPickerViewTest_Horizontal::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by horizontal direction");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        
        UILabel* alert = UILabel::create();
        alert->setText("PickerView horizontal");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        m_pUiLayer->addWidget(alert);
        
        Layout* background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        CCSize backgroundSize = background->getContentSize();
        
        
        // create picker view data
        m_array = CCArray::create();
        CC_SAFE_RETAIN(m_array);
        for (int i = 0; i < 20; ++i)
        {
            CCString* ccstr = CCString::createWithFormat("PCKER%d", i);
            m_array->addObject(ccstr);
        }
        const char* title_0 = static_cast<CCString*>(m_array->objectAtIndex(0))->getCString();
        
        
        // Create the picker view
        UIPickerView* pickerView = UIPickerView::create();
        // set picker view direction
        pickerView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
        pickerView->setTouchEnabled(true);
        pickerView->setBounceEnabled(true);
        pickerView->setBackGroundImage("cocosgui/yellow_edit.png");
        pickerView->setBackGroundImageScale9Enabled(true);
        pickerView->setSize(CCSizeMake(240, 150));
        pickerView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                    (backgroundSize.width - pickerView->getSize().width) / 2,
                                    (widgetSize.height - backgroundSize.height) / 2 +
                                    (backgroundSize.height - pickerView->getSize().height) / 2));
        pickerView->addEventListenerScrollView(this, scrollvieweventselector(UIPickerViewTest_Horizontal::selectedItemEvent));
        pickerView->addEventListenerPickerView(this, pickervieweventselector(UIPickerViewTest_Horizontal::pickItemEvent));
        m_pUiLayer->addWidget(pickerView);
        
        int count = m_array->count();
        pickerView->setItemCountInContainerWithOddNumber(count / 4);
        
        for (int i = 0; i < count; ++i)
        {
            UIButton* button = UIButton::create();
            button->loadTextures("cocosgui/orange_edit.png", "cocosgui/orange_edit.png", "");
            button->setScale9Enabled(true);
            button->setSize(CCSizeMake(pickerView->getSize().width / pickerView->getItemCountInContainerWithOddNumber(),
                                       120));            
            button->setTitleText(static_cast<CCString*>(m_array->objectAtIndex(i))->getCString());
            button->setTitleDimension(CCSizeMake(button->getTitleFontSize(),
                                                 button->getTitleFontSize() * (strlen(title_0) * 2)));
            button->setTitleHorizontalAlignment(kCCTextAlignmentCenter);
            button->setTitleVerticalAlignment(kCCVerticalTextAlignmentCenter);
            
            pickerView->addChild(button);
        }
        
        pickerView->refreshView();
        
        // create picker render of picker view
        UIButton* button_0 = static_cast<UIButton*>(pickerView->getChildren()->objectAtIndex(0));
        pickerView->loadPickerTexture("cocosgui/green_edit.png");
        CCScale9Sprite* pickerRender = pickerView->getPickerRender();
        pickerRender->setOpacity(pickerView->getOpacity() / 3);
        pickerRender->setPreferredSize(CCSizeMake(button_0->getSize().width, pickerView->getSize().height));
        
        return true;
    }
    
    return false;
}

void UIPickerViewTest_Horizontal::selectedItemEvent(CCObject *pSender, ScrollviewEventType type)
{
    switch (type)
    {
        case SCROLLVIEW_EVENT_SELECT_CHILD:
        {
            UIPickerView* pickerView = static_cast<UIPickerView*>(pSender);
            CCLOG("select child index = %d", pickerView->getSelectedChildIndex());
        }
            break;
            
        default:
            break;
    }
}

void UIPickerViewTest_Horizontal::pickItemEvent(CCObject *pSender, PickerViewEventType type)
{
    switch (type)
    {
        case PICKERVIEW_EVENT_PICK_ITEM:
        {
            UIPickerView* pickerView = static_cast<UIPickerView*>(pSender);
            CCLOG("picker view pick index = %d", pickerView->getPickIndex());
        }
            break;
            
        default:
            break;
    }
}
