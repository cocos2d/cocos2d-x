

#include "UIListViewTest.h"

const char* font_UIListViewTest = "fonts/Marker Felt.ttf";

// UIListViewTest_Vertical

UIListViewTest_Vertical::UIListViewTest_Vertical()
: _displayValueLabel(nullptr)
, _array(nullptr)
{
    
}

UIListViewTest_Vertical::~UIListViewTest_Vertical()
{
    CC_SAFE_RELEASE(_array);
}

bool UIListViewTest_Vertical::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        _displayValueLabel = Text::create("Move by vertical direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vector2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vector2(widgetSize.width / 2.0f,
                                              widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        
        Text* alert = Text::create("ListView vertical", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        
        // create list view ex data
        _array = Array::create();
        CC_SAFE_RETAIN(_array);
        for (int i = 0; i < 20; ++i)
        {
            __String* ccstr = __String::createWithFormat("listview_item_%d", i);
            _array->addObject(ccstr);
        }
        
        
        // Create the list view ex
        ListView* listView = ListView::create();
        // set list view ex direction
        listView->setDirection(SCROLLVIEW_DIR_VERTICAL);
        listView->setTouchEnabled(true);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setSize(Size(240, 130));
        listView->setPosition(Vector2((widgetSize.width - backgroundSize.width) / 2.0f +
                                    (backgroundSize.width - listView->getSize().width) / 2.0f,
                                    (widgetSize.height - backgroundSize.height) / 2.0f +
                                    (backgroundSize.height - listView->getSize().height) / 2.0f));
        listView->addEventListenerListView(this, listvieweventselector(UIListViewTest_Vertical::selectedItemEvent));
        _uiLayer->addChild(listView);
        
        
        // create model
        Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
        default_button->setName("Title Button");
        
        Layout* default_item = Layout::create();
        default_item->setTouchEnabled(true);
        default_item->setSize(default_button->getSize());
        default_button->setPosition(Vector2(default_item->getSize().width / 2.0f,
                                          default_item->getSize().height / 2.0f));
        default_item->addChild(default_button);
        
        // set model
        listView->setItemModel(default_item);
        
        // add default item
        ssize_t count = _array->count();
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
            Button* custom_button = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
            custom_button->setName("Title Button");
            custom_button->setScale9Enabled(true);
            custom_button->setSize(default_button->getSize());
            
            Layout *custom_item = Layout::create();
            custom_item->setSize(custom_button->getSize());
            custom_button->setPosition(Vector2(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->pushBackCustomItem(custom_item);
        }
        // insert custom item
        Vector<Widget*>& items = listView->getItems();
        ssize_t items_count = items.size();
        for (int i = 0; i < count / 4; ++i)
        {
            Button* custom_button = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
            custom_button->setName("Title Button");
            custom_button->setScale9Enabled(true);
            custom_button->setSize(default_button->getSize());
            
            Layout *custom_item = Layout::create();
            custom_item->setSize(custom_button->getSize());
            custom_button->setPosition(Vector2(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->insertCustomItem(custom_item, items_count);
        }
        
        // set item data
        items_count = items.size();
        for (int i = 0; i < items_count; ++i)
        {
            Widget* item = listView->getItem(i);
            Button* button = static_cast<Button*>(item->getChildByName("Title Button"));
            ssize_t index = listView->getIndex(item);
            button->setTitleText(static_cast<__String*>(_array->getObjectAtIndex(index))->getCString());
        }
        
        // remove last item
        listView->removeLastItem();
        
        // remove item by index
        items_count = items.size();
        listView->removeItem(items_count - 1);
        
        // set all items layout gravity
        listView->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
        
        // set items margin
        listView->setItemsMargin(2.0f);
        
        return true;
    }
    
    return false;
}

void UIListViewTest_Vertical::selectedItemEvent(Ref *pSender, ListViewEventType type)
{
    switch (type)
    {
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            break;
        }
        default:
            break;
    }
}

// UIListViewTest_Horizontal

UIListViewTest_Horizontal::UIListViewTest_Horizontal()
: _displayValueLabel(nullptr)
, _array(nullptr)
{
}

UIListViewTest_Horizontal::~UIListViewTest_Horizontal()
{
    CC_SAFE_RELEASE(_array);
}

bool UIListViewTest_Horizontal::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        _displayValueLabel = Text::create("Move by horizontal direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vector2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vector2(widgetSize.width / 2.0f,
                                              widgetSize.height / 2.0f
                                              + _displayValueLabel->getContentSize().height * 1.5f));
        
        _uiLayer->addChild(_displayValueLabel);
        
        
        Text* alert = Text::create("ListView horizontal", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        
        // create list view ex data
        _array = Array::create();
        CC_SAFE_RETAIN(_array);
        for (int i = 0; i < 20; ++i)
        {
            __String* ccstr = __String::createWithFormat("listview_item_%d", i);
            _array->addObject(ccstr);
        }
        
        
        // Create the list view ex
        ListView* listView = ListView::create();
        // set list view ex direction
        listView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
        listView->setTouchEnabled(true);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setSize(Size(240, 130));
        listView->setPosition(Vector2((widgetSize.width - backgroundSize.width) / 2.0f +
                                    (backgroundSize.width - listView->getSize().width) / 2.0f,
                                    (widgetSize.height - backgroundSize.height) / 2.0f +
                                    (backgroundSize.height - listView->getSize().height) / 2.0f));
        listView->addEventListenerListView(this, listvieweventselector(UIListViewTest_Horizontal::selectedItemEvent));
        _uiLayer->addChild(listView);
        
        
        // create model
        Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
        default_button->setName("Title Button");
        
        Layout *default_item = Layout::create();
        default_item->setTouchEnabled(true);
        default_item->setSize(default_button->getSize());
        default_button->setPosition(Vector2(default_item->getSize().width / 2.0f, default_item->getSize().height / 2.0f));
        default_item->addChild(default_button);
        
        // set model
        listView->setItemModel(default_item);
        
        // add default item
        ssize_t count = _array->count();
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
            Button* custom_button = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
            custom_button->setName("Title Button");
            custom_button->setScale9Enabled(true);
            custom_button->setSize(default_button->getSize());
            
            Layout* custom_item = Layout::create();
            custom_item->setSize(custom_button->getSize());
            custom_button->setPosition(Vector2(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->pushBackCustomItem(custom_item);
        }
        // insert custom item
        Vector<Widget*>& items = listView->getItems();
        ssize_t items_count = items.size();
        for (int i = 0; i < count / 4; ++i)
        {
            Button* custom_button = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
            custom_button->setName("Title Button");
            custom_button->setScale9Enabled(true);
            custom_button->setSize(default_button->getSize());
            
            Layout* custom_item = Layout::create();
            custom_item->setSize(custom_button->getSize());
            custom_button->setPosition(Vector2(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->insertCustomItem(custom_item, items_count);
        }
        
        // set item data
        items_count = items.size();
        for (int i = 0; i < items_count; ++i)
        {
            Widget *item = listView->getItem(i);
            Button *button = static_cast<Button*>(item->getChildByName("Title Button"));
            ssize_t index = listView->getIndex(item);
            button->setTitleText(static_cast<__String*>(_array->getObjectAtIndex(index))->getCString());
        }
        
        // remove last item
        listView->removeLastItem();
        
        // remove item by index
        items_count = items.size();
        listView->removeItem(items_count - 1);        
        
        // set all items layout gravity
        listView->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
        
        // set items margin
        listView->setItemsMargin(2);
        
        return true;
    }
    
    return false;
}

void UIListViewTest_Horizontal::selectedItemEvent(Ref *pSender, ListViewEventType type)
{
    switch (type)
    {
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            break;
        }
        default:
            break;
    }
}
