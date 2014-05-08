

#include "UIListViewTest.h"

// UIListViewExTest_Vertical

UIListViewExTest_Vertical::UIListViewExTest_Vertical()
{
    
}

UIListViewExTest_Vertical::~UIListViewExTest_Vertical()
{
    CC_SAFE_RELEASE(m_array);
}

bool UIListViewExTest_Vertical::init()
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
        alert->setText("ListView vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        m_pUiLayer->addWidget(alert);
        
        Layout* background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        CCSize backgroundSize = background->getContentSize();
        
        
        // create list view data
        m_array = CCArray::create();
        CC_SAFE_RETAIN(m_array);
        for (int i = 0; i < 20; ++i)
        {
            CCString* ccstr = CCString::createWithFormat("listview_item_%d", i);
            m_array->addObject(ccstr);
        }
        
        
        // Create the list view
        UIListView* listView = UIListView::create();
        // set list view direction
        listView->setDirection(SCROLLVIEW_DIR_VERTICAL);
        listView->setTouchEnabled(true);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setSize(CCSizeMake(240, 130));
        listView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                    (backgroundSize.width - listView->getSize().width) / 2,
                                    (widgetSize.height - backgroundSize.height) / 2 +
                                    (backgroundSize.height - listView->getSize().height) / 2));
        listView->addEventListenerListView(this, listvieweventselector(UIListViewExTest_Vertical::selectedItemEvent));
        m_pUiLayer->addWidget(listView);
        
        
        // create model
        UIButton* default_button = UIButton::create();
        default_button->setName("TextButton");
        default_button->setTouchEnabled(true);
        default_button->loadTextures("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png", "");
        
        Layout* default_item = Layout::create();
        default_item->setTouchEnabled(true);
        default_item->setSize(default_button->getSize());
        default_button->setPosition(ccp(default_item->getSize().width / 2, default_item->getSize().height / 2));
        default_item->addChild(default_button);
        
        // set model
        listView->setItemModel(default_item);
        
        // add default item
        int count = m_array->count();
        for (int i = 0; i < count / 4; ++i)
        {
            listView->pushBackDefaultItem();
        }
        // insert default item
        for (int i = 0; i < count / 4; ++i)
        {
            listView->insertDefaultItem(0);
        }
        
        // add custom item
        for (int i = 0; i < count / 4; ++i)
        {
            UIButton* custom_button = UIButton::create();
            custom_button->setName("TextButton");
            custom_button->setTouchEnabled(true);
            custom_button->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
            custom_button->setScale9Enabled(true);
            custom_button->setSize(default_button->getSize());
            
            Layout *custom_item = Layout::create();
            custom_item->setSize(custom_button->getSize());
            custom_button->setPosition(ccp(custom_item->getSize().width / 2, custom_item->getSize().height / 2));
            custom_item->addChild(custom_button);
            
            listView->pushBackCustomItem(custom_item);
        }
        // insert custom item
        CCArray *items = listView->getItems();
        int items_count = items->count();
        for (int i = 0; i < count / 4; ++i)
        {
            UIButton* custom_button = UIButton::create();
            custom_button->setName("TextButton");
            custom_button->setTouchEnabled(true);
            custom_button->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
            custom_button->setScale9Enabled(true);
            custom_button->setSize(default_button->getSize());
            
            Layout *custom_item = Layout::create();
            custom_item->setSize(custom_button->getSize());
            custom_button->setPosition(ccp(custom_item->getSize().width / 2, custom_item->getSize().height / 2));
            custom_item->addChild(custom_button);
            
            listView->insertCustomItem(custom_item, items_count);
        }
        
        // set item data
        items_count = items->count();
        for (int i = 0; i < items_count; ++i)
        {
            UIWidget *item = listView->getItem(i);
            UIButton *button = static_cast<UIButton*>(item->getChildByName("TextButton"));
            int index = listView->getIndex(item);
            button->setTitleText(static_cast<CCString*>(m_array->objectAtIndex(index))->getCString());
        }
        
        // remove last item
        listView->removeLastItem();
        
        // remove item by index
        items_count = items->count();
        listView->removeItem(items_count - 1);
        
        // set all items layout gravity
        listView->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
        
        return true;
    }
    
    return false;
}

void UIListViewExTest_Vertical::selectedItemEvent(CCObject *pSender, ListViewEventType type)
{
    switch (type)
    {
        case LISTVIEW_ONSELECTEDITEM_START:
        {
            UIListView* listViewEx = static_cast<UIListView*>(pSender);
            if (listViewEx)
                CCLOG("select child start index = %d", listViewEx->getCurSelectedIndex());
            break;
        }
        case LISTVIEW_ONSELECTEDITEM_END:
        {
            UIListView* listViewEx = static_cast<UIListView*>(pSender);
            if (listViewEx)
                CCLOG("select child end index = %d", listViewEx->getCurSelectedIndex());
            break;
        }
        default:
            break;
    }
}


// UIListViewExTest_Horizontal

UIListViewExTest_Horizontal::UIListViewExTest_Horizontal()
{
    
}

UIListViewExTest_Horizontal::~UIListViewExTest_Horizontal()
{
    CC_SAFE_RELEASE(m_array);
}

bool UIListViewExTest_Horizontal::init()
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
        alert->setText("ListView horizontal");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        m_pUiLayer->addWidget(alert);
        
        Layout* background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        CCSize backgroundSize = background->getContentSize();
        
        
        // create list view data
        m_array = CCArray::create();
        CC_SAFE_RETAIN(m_array);
        for (int i = 0; i < 20; ++i)
        {
            CCString* ccstr = CCString::createWithFormat("listview_item_%d", i);
            m_array->addObject(ccstr);
        }
        
        
        // Create the list view
        UIListView* listView = UIListView::create();
        // set list view direction
        listView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
        listView->setTouchEnabled(true);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setSize(CCSizeMake(240, 130));
        listView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                    (backgroundSize.width - listView->getSize().width) / 2,
                                    (widgetSize.height - backgroundSize.height) / 2 +
                                    (backgroundSize.height - listView->getSize().height) / 2));
        listView->addEventListenerListView(this, listvieweventselector(UIListViewExTest_Horizontal::selectedItemEvent));
        m_pUiLayer->addWidget(listView);
        
        
        // create model
        UIButton* default_button = UIButton::create();
        default_button->setName("TextButton");
        default_button->setTouchEnabled(true);
        default_button->loadTextures("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png", "");
        
        Layout* default_item = Layout::create();
        default_item->setTouchEnabled(true);
        default_item->setSize(default_button->getSize());
        default_button->setPosition(ccp(default_item->getSize().width / 2, default_item->getSize().height / 2));
        default_item->addChild(default_button);
        
        // set model
        listView->setItemModel(default_item);
        
        // add default item
        int count = m_array->count();
        for (int i = 0; i < count / 4; ++i)
        {
            listView->pushBackDefaultItem();
        }
        // insert default item
        for (int i = 0; i < count / 4; ++i)
        {
            listView->insertDefaultItem(0);
        }
        
        // add custom item
        for (int i = 0; i < count / 4; ++i)
        {
            UIButton* custom_button = UIButton::create();
            custom_button->setName("TextButton");
            custom_button->setTouchEnabled(true);
            custom_button->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
            custom_button->setScale9Enabled(true);
            custom_button->setSize(default_button->getSize());
            
            Layout *custom_item = Layout::create();
            custom_item->setSize(custom_button->getSize());
            custom_button->setPosition(ccp(custom_item->getSize().width / 2, custom_item->getSize().height / 2));
            custom_item->addChild(custom_button);
            
            listView->pushBackCustomItem(custom_item);
        }
        // insert custom item
        CCArray *items = listView->getItems();
        int items_count = items->count();
        for (int i = 0; i < count / 4; ++i)
        {
            UIButton* custom_button = UIButton::create();
            custom_button->setName("TextButton");
            custom_button->setTouchEnabled(true);
            custom_button->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
            custom_button->setScale9Enabled(true);
            custom_button->setSize(default_button->getSize());
            
            Layout *custom_item = Layout::create();
            custom_item->setSize(custom_button->getSize());
            custom_button->setPosition(ccp(custom_item->getSize().width / 2, custom_item->getSize().height / 2));
            custom_item->addChild(custom_button);
            
            listView->insertCustomItem(custom_item, items_count);
        }
        
        // set item data
        items_count = items->count();
        for (int i = 0; i < items_count; ++i)
        {
            UIWidget *item = listView->getItem(i);
            UIButton *button = static_cast<UIButton*>(item->getChildByName("TextButton"));
            int index = listView->getIndex(item);
            button->setTitleText(static_cast<CCString*>(m_array->objectAtIndex(index))->getCString());
        }
        
        // remove last item
        listView->removeLastItem();
        
        // remove item by index
        items_count = items->count();
        listView->removeItem(items_count - 1);        
        
        // set all items layout gravity
        listView->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
        
        // set items margin
        listView->setItemsMargin(2);
        
        return true;
    }
    
    return false;
}

void UIListViewExTest_Horizontal::selectedItemEvent(CCObject *pSender, ListViewEventType type)
{
    switch (type)
    {
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_START:
        {
            UIListView* listViewEx = static_cast<UIListView*>(pSender);
            if (listViewEx)
                CCLOG("select child start index = %d", listViewEx->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_END:
        {
            UIListView* listViewEx = static_cast<UIListView*>(pSender);
            if (listViewEx)
                CCLOG("select child end index = %d", listViewEx->getCurSelectedIndex());
            break;
        }
        default:
            break;
    }
}
