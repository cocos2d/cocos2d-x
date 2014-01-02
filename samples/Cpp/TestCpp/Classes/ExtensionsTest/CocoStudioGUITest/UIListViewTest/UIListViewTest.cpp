

#include "UIListViewTest.h"

const char* font_UIListViewTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

// UIListViewTest_Vertical

UIListViewTest_Vertical::UIListViewTest_Vertical()
: _displayValueLabel(nullptr)
{
    
}

UIListViewTest_Vertical::~UIListViewTest_Vertical()
{
}

bool UIListViewTest_Vertical::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("Move by vertical direction");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        
        gui::Text* alert = gui::Text::create();
        alert->setText("ListView vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        
        // create list view ex data
        for (int i = 0; i < 20; ++i)
        {
            _array.push_back(StringUtils::format("listview_item_%d", i));
        }
        
        
        // Create the list view ex
        ListView* listView = ListView::create();
        // set list view ex direction
        listView->setDirection(SCROLLVIEW_DIR_VERTICAL);
        listView->setTouchEnabled(true);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosgui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setSize(Size(240, 130));
        listView->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                    (backgroundSize.width - listView->getSize().width) / 2.0f,
                                    (widgetSize.height - backgroundSize.height) / 2.0f +
                                    (backgroundSize.height - listView->getSize().height) / 2.0f));
        listView->addEventListenerListView(this, listvieweventselector(UIListViewTest_Vertical::selectedItemEvent));
        _uiLayer->addChild(listView);
        
        
        // create model
        Button* default_button = Button::create();
        default_button->setName("Title Button");
        default_button->setTouchEnabled(true);
        default_button->loadTextures("cocosgui/backtotoppressed.png", "cocosgui/backtotopnormal.png", "");
        
        Layout* default_item = Layout::create();
        default_item->setTouchEnabled(true);
        default_item->setSize(default_button->getSize());
        default_button->setPosition(Point(default_item->getSize().width / 2.0f, default_item->getSize().height / 2.0f));
        default_item->addChild(default_button);
        
        // set model
        listView->setItemModel(default_item);
        
        // add default item
        size_t count = _array.size();
        for (size_t i = 0; i < count / 4; ++i)
        {
            listView->pushBackDefaultItem();
        }
        // insert default item
        for (size_t i = 0; i < count / 4; ++i)
        {
            listView->insertDefaultItem(0);
        }
        
        // add custom item
        for (size_t i = 0; i < count / 4; ++i)
        {
            Button* custom_button = Button::create();
            custom_button->setName("Title Button");
            custom_button->setTouchEnabled(true);
            custom_button->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
            custom_button->setScale9Enabled(true);
            custom_button->setSize(default_button->getSize());
            
            Layout *custom_item = Layout::create();
            custom_item->setSize(custom_button->getSize());
            custom_button->setPosition(Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->pushBackCustomItem(custom_item);
        }
        // insert custom item
        Vector<Widget*>& items = listView->getItems();
        ssize_t items_count = items.size();
        for (size_t i = 0; i < count / 4; ++i)
        {
            Button* custom_button = Button::create();
            custom_button->setName("Title Button");
            custom_button->setTouchEnabled(true);
            custom_button->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
            custom_button->setScale9Enabled(true);
            custom_button->setSize(default_button->getSize());
            
            Layout *custom_item = Layout::create();
            custom_item->setSize(custom_button->getSize());
            custom_button->setPosition(Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->insertCustomItem(custom_item, items_count);
        }
        
        // set item data
        items_count = items.size();
        for (ssize_t i = 0; i < items_count; ++i)
        {
            Widget* item = listView->getItem(i);
            Button* button = static_cast<Button*>(item->getChildByName("Title Button"));
            int index = listView->getIndex(item);
            button->setTitleText(_array[index]);
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

void UIListViewTest_Vertical::selectedItemEvent(Object *pSender, ListViewEventType type)
{
    switch (type)
    {
        case LISTVIEW_ONSELECTEDITEM:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CCLOG("select child index = %ld", listView->getCurSelectedIndex());
        }
            break;
            
        default:
            break;
    }
}

// UIListViewTest_Horizontal

UIListViewTest_Horizontal::UIListViewTest_Horizontal()
: _displayValueLabel(nullptr)
{
}

UIListViewTest_Horizontal::~UIListViewTest_Horizontal()
{
}

bool UIListViewTest_Horizontal::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("Move by horizontal direction");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        
        gui::Text* alert = gui::Text::create();
        alert->setText("ListView horizontal");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        
        // create list view ex data
        for (int i = 0; i < 20; ++i)
        {
            _array.push_back(StringUtils::format("listview_item_%d", i));
        }
        
        
        // Create the list view ex
        ListView* listView = ListView::create();
        // set list view ex direction
        listView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
        listView->setTouchEnabled(true);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosgui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setSize(Size(240, 130));
        listView->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                    (backgroundSize.width - listView->getSize().width) / 2.0f,
                                    (widgetSize.height - backgroundSize.height) / 2.0f +
                                    (backgroundSize.height - listView->getSize().height) / 2.0f));
        listView->addEventListenerListView(this, listvieweventselector(UIListViewTest_Horizontal::selectedItemEvent));
        _uiLayer->addChild(listView);
        
        
        // create model
        Button* default_button = Button::create();
        default_button->setName("Title Button");
        default_button->setTouchEnabled(true);
        default_button->loadTextures("cocosgui/backtotoppressed.png", "cocosgui/backtotopnormal.png", "");
        
        Layout *default_item = Layout::create();
        default_item->setTouchEnabled(true);
        default_item->setSize(default_button->getSize());
        default_button->setPosition(Point(default_item->getSize().width / 2.0f, default_item->getSize().height / 2.0f));
        default_item->addChild(default_button);
        
        // set model
        listView->setItemModel(default_item);
        
        // add default item
        size_t count = _array.size();
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
            Button* custom_button = Button::create();
            custom_button->setName("Title Button");
            custom_button->setTouchEnabled(true);
            custom_button->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
            custom_button->setScale9Enabled(true);
            custom_button->setSize(default_button->getSize());
            
            Layout* custom_item = Layout::create();
            custom_item->setSize(custom_button->getSize());
            custom_button->setPosition(Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->pushBackCustomItem(custom_item);
        }
        // insert custom item
        Vector<Widget*>& items = listView->getItems();
        int items_count = items.size();
        for (int i = 0; i < count / 4; ++i)
        {
            Button* custom_button = Button::create();
            custom_button->setName("Title Button");
            custom_button->setTouchEnabled(true);
            custom_button->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
            custom_button->setScale9Enabled(true);
            custom_button->setSize(default_button->getSize());
            
            Layout* custom_item = Layout::create();
            custom_item->setSize(custom_button->getSize());
            custom_button->setPosition(Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->insertCustomItem(custom_item, items_count);
        }
        
        // set item data
        items_count = items.size();
        for (int i = 0; i < items_count; ++i)
        {
            Widget *item = listView->getItem(i);
            Button *button = static_cast<Button*>(item->getChildByName("Title Button"));
            int index = listView->getIndex(item);
            button->setTitleText(_array[index]);
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

void UIListViewTest_Horizontal::selectedItemEvent(Object *pSender, ListViewEventType type)
{
    switch (type)
    {
        case LISTVIEW_ONSELECTEDITEM:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CCLOG("select child index = %ld", listView->getCurSelectedIndex());
        }
            break;
            
        default:
            break;
    }
}
