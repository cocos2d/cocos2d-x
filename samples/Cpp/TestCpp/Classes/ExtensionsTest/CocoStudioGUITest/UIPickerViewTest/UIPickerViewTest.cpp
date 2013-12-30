

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
        Size widgetSize = _widget->getSize();
        
        m_pDisplayValueLabel = gui::Label::create();
        m_pDisplayValueLabel->setText("Move by vertical direction");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        _uiLayer->addChild(m_pDisplayValueLabel);
        
        
        gui::Label* alert = gui::Label::create();
        alert->setText("PickerView vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        
        // create picker view data
        m_array = __Array::create();
        CC_SAFE_RETAIN(m_array);
        for (int i = 0; i < 20; ++i)
        {
            String* ccstr = String::createWithFormat("pickerview_%d", i);
            m_array->addObject(ccstr);
        }
        
        
        // Create the picker view
        PickerView* pickerView = PickerView::create();
        // set picker view direction
        pickerView->setDirection(SCROLLVIEW_DIR_VERTICAL);
        pickerView->setTouchEnabled(true);
        pickerView->setBounceEnabled(true);
        pickerView->setBackGroundImage("cocosgui/yellow_edit.png");
        pickerView->setBackGroundImageScale9Enabled(true);
        pickerView->setSize(Size(240, 150));
        pickerView->setPosition(Point((widgetSize.width - backgroundSize.width) / 2 +
                                      (backgroundSize.width - pickerView->getSize().width) / 2,
                                      (widgetSize.height - backgroundSize.height) / 2 +
                                      (backgroundSize.height - pickerView->getSize().height) / 2));
        pickerView->addEventListenerScrollView(this, scrollvieweventselector(UIPickerViewTest_Vertical::selectedItemEvent));
        pickerView->addEventListenerPickerView(this, pickervieweventselector(UIPickerViewTest_Vertical::pickItemEvent));
        _uiLayer->addChild(pickerView);
        
        int count = m_array->count();
        pickerView->setItemCountInContainerWithOddNumber(count / 5);
        
        for (int i = 0; i < count; ++i)
        {
            Button* button = Button::create();
            button->loadTextures("cocosgui/orange_edit.png", "cocosgui/orange_edit.png", "");
            button->setScale9Enabled(true);
            button->setSize(Size(100,
                                 pickerView->getSize().height / pickerView->getItemCountInContainerWithOddNumber()));
            button->setTitleText(static_cast<String*>(m_array->getObjectAtIndex(i))->getCString());
            
            pickerView->addChild(button);
        }
        
        // create picker render of picker view
        Button* button_0 = static_cast<Button*>(pickerView->getChildren().at(0));
        pickerView->loadPickerTexture("cocosgui/green_edit.png");
        Scale9Sprite* pickerRender = pickerView->getPickerRender();
        pickerRender->setOpacity(pickerView->getOpacity() / 3);
        pickerRender->setPreferredSize(Size(pickerView->getSize().width, button_0->getSize().height));
        
        return true;
    }
    
    return false;
}

void UIPickerViewTest_Vertical::selectedItemEvent(Object *pSender, ScrollviewEventType type)
{
    switch (type)
    {
        case SCROLLVIEW_EVENT_SELECT_CHILD:
        {
            PickerView* pickerView = static_cast<PickerView*>(pSender);
            CCLOG("select child index = %d", pickerView->getSelectedChildIndex());
        }
            break;
            
        default:
            break;
    }
}

void UIPickerViewTest_Vertical::pickItemEvent(Object *pSender, PickerViewEventType type)
{
    switch (type)
    {
        case PICKERVIEW_EVENT_PICK_ITEM:
            {
                PickerView* pickerView = static_cast<PickerView*>(pSender);
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
        Size widgetSize = _widget->getSize();
        
        m_pDisplayValueLabel = gui::Label::create();
        m_pDisplayValueLabel->setText("Move by horizontal direction");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        _uiLayer->addChild(m_pDisplayValueLabel);
        
        
        gui::Label* alert = gui::Label::create();
        alert->setText("PickerView horizontal");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        
        // create picker view data
        m_array = __Array::create();
        CC_SAFE_RETAIN(m_array);
        for (int i = 0; i < 20; ++i)
        {
            String* ccstr = String::createWithFormat("PCKER%d", i);
            m_array->addObject(ccstr);
        }
        const char* title_0 = static_cast<String*>(m_array->getObjectAtIndex(0))->getCString();
        
        
        // Create the picker view
        PickerView* pickerView = PickerView::create();
        // set picker view direction
        pickerView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
        pickerView->setTouchEnabled(true);
        pickerView->setBounceEnabled(true);
        pickerView->setBackGroundImage("cocosgui/yellow_edit.png");
        pickerView->setBackGroundImageScale9Enabled(true);
        pickerView->setSize(Size(240, 150));
        pickerView->setPosition(Point((widgetSize.width - backgroundSize.width) / 2 +
                                    (backgroundSize.width - pickerView->getSize().width) / 2,
                                    (widgetSize.height - backgroundSize.height) / 2 +
                                    (backgroundSize.height - pickerView->getSize().height) / 2));
        pickerView->addEventListenerScrollView(this, scrollvieweventselector(UIPickerViewTest_Horizontal::selectedItemEvent));
        pickerView->addEventListenerPickerView(this, pickervieweventselector(UIPickerViewTest_Horizontal::pickItemEvent));
        _uiLayer->addChild(pickerView);
        
        int count = m_array->count();
        pickerView->setItemCountInContainerWithOddNumber(count / 4);
        
        for (int i = 0; i < count; ++i)
        {
            Button* button = Button::create();
            button->loadTextures("cocosgui/orange_edit.png", "cocosgui/orange_edit.png", "");
            button->setScale9Enabled(true);
            button->setSize(Size(pickerView->getSize().width / pickerView->getItemCountInContainerWithOddNumber(),
                                       120));            
            button->setTitleText(static_cast<String*>(m_array->getObjectAtIndex(i))->getCString());
            button->setTitleDimension(Size(button->getTitleFontSize(),
                                                 button->getTitleFontSize() * (strlen(title_0) * 2)));
            button->setTitleHorizontalAlignment(TextHAlignment::CENTER);
            button->setTitleVerticalAlignment(TextVAlignment::CENTER);
            
            pickerView->addChild(button);
        }
        
        // create picker render of picker view
        Button* button_0 = static_cast<Button*>(pickerView->getChildren().at(0));
        pickerView->loadPickerTexture("cocosgui/green_edit.png");
        Scale9Sprite* pickerRender = pickerView->getPickerRender();
        pickerRender->setOpacity(pickerView->getOpacity() / 3);
        pickerRender->setPreferredSize(Size(button_0->getSize().width, pickerView->getSize().height));
        
        return true;
    }
    
    return false;
}

void UIPickerViewTest_Horizontal::selectedItemEvent(Object *pSender, ScrollviewEventType type)
{
    switch (type)
    {
        case SCROLLVIEW_EVENT_SELECT_CHILD:
        {
            PickerView* pickerView = static_cast<PickerView*>(pSender);
            CCLOG("select child index = %d", pickerView->getSelectedChildIndex());
        }
            break;
            
        default:
            break;
    }
}

void UIPickerViewTest_Horizontal::pickItemEvent(Object *pSender, PickerViewEventType type)
{
    switch (type)
    {
        case PICKERVIEW_EVENT_PICK_ITEM:
        {
            PickerView* pickerView = static_cast<PickerView*>(pSender);
            CCLOG("picker view pick index = %d", pickerView->getPickIndex());
        }
            break;
            
        default:
            break;
    }
}
