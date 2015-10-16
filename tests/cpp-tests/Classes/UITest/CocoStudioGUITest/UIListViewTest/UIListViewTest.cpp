#include "UIListViewTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

const char* font_UIListViewTest = "fonts/Marker Felt.ttf";

UIListViewTests::UIListViewTests()
{
    ADD_TEST_CASE(UIListViewTest_Horizontal);
    ADD_TEST_CASE(UIListViewTest_Vertical);
    ADD_TEST_CASE(UIListViewTest_ScrollToItemVertical);
    ADD_TEST_CASE(UIListViewTest_ScrollToItemHorizontal);
    ADD_TEST_CASE(UIListViewTest_MagneticVertical);
    ADD_TEST_CASE(UIListViewTest_MagneticHorizontal);
    ADD_TEST_CASE(Issue12692);
    ADD_TEST_CASE(Issue8316);
}

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
        Size widgetSize = _widget->getContentSize();
        
        _displayValueLabel = Text::create("Move by vertical direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                              widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        
        Text* alert = Text::create("ListView vertical", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        
        // create list view ex data
       
        for (int i = 0; i < 20; ++i)
        {
            std::string ccstr = StringUtils::format("listview_item_%d", i);
            _array.push_back(ccstr);
        }
        
        
        // Create the list view ex
        ListView* listView = ListView::create();
        // set list view ex direction
        listView->setDirection(ui::ScrollView::Direction::VERTICAL);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setContentSize(Size(240, 130));
		listView->setPosition(Vec2((widgetSize - listView->getContentSize()) / 2.0f));
        listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(UIListViewTest_Vertical::selectedItemEvent, this));
        listView->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(UIListViewTest_Vertical::selectedItemEventScrollView,this));
		listView->setScrollBarPositionFromCorner(Vec2(7, 7));
        _uiLayer->addChild(listView);
        
        
        // create model
        Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
        default_button->setName("Title Button");
        
        Layout* default_item = Layout::create();
        default_item->setTouchEnabled(true);
        default_item->setContentSize(default_button->getContentSize());
		default_button->setPosition(Vec2(default_item->getContentSize() / 2.0f));
        default_item->addChild(default_button);
        
        // set model
        listView->setItemModel(default_item);
        
        // add default item
        ssize_t count = _array.size();
        for (int i = 0; i < count / 4; ++i)
        {
            listView->pushBackDefaultItem();
        }
        // insert default item
        for (int i = 0; i < count / 4; ++i)
        {
            listView->insertDefaultItem(0);
        }
        
        listView->removeAllChildren();
        
        Sprite* testSprite = Sprite::create("cocosui/backtotoppressed.png");
        testSprite->setPosition(Vec2(200,200));
        listView->addChild(testSprite);
        
        // add custom item
        for (int i = 0; i < count / 4; ++i)
        {
            Button* custom_button = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
            custom_button->setName("Title Button");
            custom_button->setScale9Enabled(true);
            custom_button->setContentSize(default_button->getContentSize());
            
            Layout *custom_item = Layout::create();
            custom_item->setContentSize(custom_button->getContentSize());
            custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->addChild(custom_item);
        }
        // insert custom item
        Vector<Widget*>& items = listView->getItems();
        ssize_t items_count = items.size();
        for (int i = 0; i < count / 4; ++i)
        {
            Button* custom_button = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
            custom_button->setName("Title Button");
            custom_button->setScale9Enabled(true);
            custom_button->setContentSize(default_button->getContentSize());
            
            Layout *custom_item = Layout::create();
            custom_item->setContentSize(custom_button->getContentSize());
            custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
            custom_item->addChild(custom_button);
            custom_item->setTag(1);
            
            listView->insertCustomItem(custom_item, items_count);
        }
        
        // set item data
        items_count = items.size();
        for (int i = 0; i < items_count; ++i)
        {
            Widget* item = listView->getItem(i);
            Button* button = static_cast<Button*>(item->getChildByName("Title Button"));
            ssize_t index = listView->getIndex(item);
            button->setTitleText(_array[index]);
        }
        
        // remove last item
        listView->removeChildByTag(1);
        
        // remove item by index
        items_count = items.size();
        listView->removeItem(items_count - 1);
        
        // set all items layout gravity
        listView->setGravity(ListView::Gravity::CENTER_VERTICAL);
        
        // set items margin
        listView->setItemsMargin(2.0f);

        // Show the indexes of items on each boundary.
        {
            float position = 75;
            // Labels
            _indexLabels[0] = Text::create(" ", "fonts/Marker Felt.ttf", 12);
            _indexLabels[0]->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            _indexLabels[0]->setPosition(_uiLayer->getContentSize() / 2 + Size(0, position));
            _uiLayer->addChild(_indexLabels[0]);
            _indexLabels[1] = Text::create("  ", "fonts/Marker Felt.ttf", 12);
            _indexLabels[1]->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            _indexLabels[1]->setPosition(_uiLayer->getContentSize() / 2 + Size(140, 0));
            _uiLayer->addChild(_indexLabels[1]);
            _indexLabels[2] = Text::create(" ", "fonts/Marker Felt.ttf", 12);
            _indexLabels[2]->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            _indexLabels[2]->setPosition(_uiLayer->getContentSize() / 2 + Size(0, -position));
            _uiLayer->addChild(_indexLabels[2]);
            
            // Callback
            listView->ScrollView::addEventListener([this](Ref* ref, ScrollView::EventType eventType) {
                ListView* listView = dynamic_cast<ListView*>(ref);
                if(listView == nullptr || eventType != ScrollView::EventType::CONTAINER_MOVED)
                {
                    return;
                }
                auto bottom = listView->getBottommostItemInCurrentView();
                auto center = listView->getCenterItemInCurrentView();
                auto top = listView->getTopmostItemInCurrentView();
                
                _indexLabels[0]->setString(StringUtils::format("Top index=%zd", listView->getIndex(top)));
                _indexLabels[1]->setString(StringUtils::format("Center\nindex=%zd", listView->getIndex(center)));
                _indexLabels[2]->setString(StringUtils::format("Bottom index=%zd", listView->getIndex(bottom)));
            });
        }

        // Jump to bottom
        listView->jumpToBottom();

        return true;
    }
    
    return false;
}

void UIListViewTest_Vertical::selectedItemEvent(Ref *pSender, ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
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

void UIListViewTest_Vertical::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
{
    switch (type) {
        case ui::ScrollView::EventType::SCROLL_TO_BOTTOM:
            CCLOG("SCROLL_TO_BOTTOM");
            break;
        case ui::ScrollView::EventType::SCROLL_TO_TOP:
            CCLOG("SCROLL_TO_TOP");
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
        Size widgetSize = _widget->getContentSize();
        
        _displayValueLabel = Text::create("Move by horizontal direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                              widgetSize.height / 2.0f
                                              + _displayValueLabel->getContentSize().height * 1.5f));
        
        _uiLayer->addChild(_displayValueLabel);
        
        
        Text* alert = Text::create("ListView horizontal", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        
        // create list view ex data
      
        for (int i = 0; i < 20; ++i)
        {
            std::string ccstr = StringUtils::format("listview_item_%d", i);
            _array.push_back(ccstr);
        }
        
        
        // Create the list view ex
        ListView* listView = ListView::create();
        // set list view ex direction
        listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
        listView->setTouchEnabled(true);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setContentSize(Size(240, 130));
        listView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                    (backgroundSize.width - listView->getContentSize().width) / 2.0f,
                                    (widgetSize.height - backgroundSize.height) / 2.0f +
                                    (backgroundSize.height - listView->getContentSize().height) / 2.0f));
        listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(UIListViewTest_Horizontal::selectedItemEvent, this));
		listView->setScrollBarPositionFromCorner(Vec2(7, 7));
        _uiLayer->addChild(listView);
        
        
        // create model
        Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
        default_button->setName("Title Button");
        
        Layout *default_item = Layout::create();
        default_item->setTouchEnabled(true);
        default_item->setContentSize(default_button->getContentSize());
        default_button->setPosition(Vec2(default_item->getContentSize().width / 2.0f, default_item->getContentSize().height / 2.0f));
        default_item->addChild(default_button);
        
        // set model
        listView->setItemModel(default_item);
        
        // add default item
        ssize_t count = _array.size();
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
            custom_button->setContentSize(default_button->getContentSize());
            
            Layout* custom_item = Layout::create();
            custom_item->setContentSize(custom_button->getContentSize());
            custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
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
            custom_button->setContentSize(default_button->getContentSize());
            
            Layout* custom_item = Layout::create();
            custom_item->setContentSize(custom_button->getContentSize());
            custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
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
            button->setTitleText(_array[index]);
        }
        // remove last item
        listView->removeLastItem();
        
        // remove item by index
        items_count = items.size();
        listView->removeItem(items_count - 1);        
        
        // set all items layout gravity
        listView->setGravity(ListView::Gravity::CENTER_VERTICAL);
        
        // set items margin
        listView->setItemsMargin(2);

        // Jump to right
        listView->jumpToRight();

        return true;
    }
    
    return false;
}

void UIListViewTest_Horizontal::selectedItemEvent(Ref *pSender, ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
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

bool Issue12692::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        auto label = Text::create("Issue 12692", "fonts/Marker Felt.ttf", 32);
        label->setName("Text Title");
        label->setAnchorPoint(Vec2(0.5f, -1.0f));
        label->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f + label->getContentSize().height * 1.5f));
        _uiLayer->addChild(label);
        
        
        Text* alert = Text::create("ListView in ListView enable Scissor Clipping", "fonts/Marker Felt.ttf", 20);
        alert->setName("Text Alert");
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        // Create the list view ex
        ListView* listView = ListView::create();
        // set list view ex direction
        listView->setDirection(ui::ScrollView::Direction::VERTICAL);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setContentSize(Size(240, 130));
        listView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                   (backgroundSize.width - listView->getContentSize().width) / 2.0f,
                                   (widgetSize.height - backgroundSize.height) / 2.0f +
                                   (backgroundSize.height - listView->getContentSize().height) / 2.0f));
        listView->setScrollBarPositionFromCorner(Vec2(7, 7));
        listView->setClippingEnabled(true);
        listView->setClippingType(ui::Layout::ClippingType::SCISSOR);
        listView->setName("listview1");
        _uiLayer->addChild(listView);
        
        auto list2 = ListView::create();
        list2->setDirection(ui::ScrollView::Direction::VERTICAL);
        list2->setBounceEnabled(true);
        list2->setBackGroundImage("cocosui/green_edit.png");
        list2->setBackGroundImageScale9Enabled(true);
        list2->setContentSize(Size(240, 65));
        list2->setClippingEnabled(true);
        list2->setClippingType(ui::Layout::ClippingType::SCISSOR);
        list2->setName("listview2");
        listView->insertCustomItem(list2, 0);
        
        {
            Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
            default_button->setName("Title Button");
            
            Layout* default_item = Layout::create();
            default_item->setTouchEnabled(true);
            default_item->setContentSize(default_button->getContentSize());
            default_button->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
                                             default_item->getContentSize().height / 2.0f));
            default_item->addChild(default_button);
            
            // set model
            listView->setItemModel(default_item);
            listView->pushBackDefaultItem();
            listView->pushBackDefaultItem();
            listView->pushBackDefaultItem();
        }
        {
            Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
            default_button->setName("Title Button 2");
            
            Layout* default_item = Layout::create();
            default_item->setTouchEnabled(true);
            default_item->setContentSize(default_button->getContentSize());
            default_button->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
                                             default_item->getContentSize().height / 2.0f));
            default_item->addChild(default_button);
            
            // set model
            list2->setItemModel(default_item);
            list2->pushBackDefaultItem();
            list2->pushBackDefaultItem();
            list2->pushBackDefaultItem();
        }
        return true;
    }
    
    return false;
}


bool Issue8316::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        auto label = Text::create("Issue 8316", "fonts/Marker Felt.ttf", 32);
        label->setAnchorPoint(Vec2(0.5f, -1.0f));
        label->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f + label->getContentSize().height * 1.5f));
        _uiLayer->addChild(label);
        
        Text* alert = Text::create("ListView Disable Touch", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        // Create the list view ex
        ListView* listView = ListView::create();
        // set list view ex direction
        listView->setDirection(ui::ScrollView::Direction::VERTICAL);
        listView->setBounceEnabled(true);
        listView->setTouchEnabled(false);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setContentSize(Size(240, 130));
        listView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                   (backgroundSize.width - listView->getContentSize().width) / 2.0f,
                                   (widgetSize.height - backgroundSize.height) / 2.0f +
                                   (backgroundSize.height - listView->getContentSize().height) / 2.0f));
        listView->setScrollBarPositionFromCorner(Vec2(7, 7));
        listView->setClippingEnabled(true);
        listView->setClippingType(ui::Layout::ClippingType::SCISSOR);
        listView->setName("listview1");
        
        {
            Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
            default_button->setName("Title Button");
            
            Layout* default_item = Layout::create();
            default_item->setTouchEnabled(true);
            default_item->setContentSize(default_button->getContentSize());
            default_button->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
                                             default_item->getContentSize().height / 2.0f));
            default_item->addChild(default_button);
            
            // set model
            listView->setItemModel(default_item);
            listView->pushBackDefaultItem();
            listView->pushBackDefaultItem();
            listView->pushBackDefaultItem();
        }
        
        _uiLayer->addChild(listView);
        
      
        return true;
    }
    
    return false;
}


// UIListViewTest_ScrollToItem
bool UIListViewTest_ScrollToItem::init()
{
    if(!UIScene::init())
    {
        return false;
    }
    
    Size layerSize = _uiLayer->getContentSize();
    
    static int NUMBER_OF_ITEMS = 31;
    _nextIndex = 0;
    _titleLabel = Text::create("Scroll to item", "fonts/Marker Felt.ttf", 32);
    _titleLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _titleLabel->setPosition(Vec2(layerSize / 2) + Vec2(0, _titleLabel->getContentSize().height * 3.15f));
    _uiLayer->addChild(_titleLabel, 3);
    
    // Create the list view
    _listView = ListView::create();
    _listView->setDirection(getListViewDirection());
    _listView->setBounceEnabled(true);
    _listView->setBackGroundImage("cocosui/green_edit.png");
    _listView->setBackGroundImageScale9Enabled(true);
    _listView->setContentSize(layerSize / 2);
    _listView->setScrollBarPositionFromCorner(Vec2(7, 7));
    _listView->setItemsMargin(2.0f);
    _listView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _listView->setPosition(layerSize / 2);
    _uiLayer->addChild(_listView);
    
    // Guide line for center align
    {
        DrawNode* pNode = DrawNode::create();
        Vec2 center = layerSize / 2;
        if(getListViewDirection() == ScrollView::Direction::HORIZONTAL)
        {
            float halfY = 110;
            pNode->drawLine(Vec2(center.x, center.y - halfY), Vec2(center.x, center.y + halfY), Color4F(0, 0, 0, 1));
        }
        else
        {
            float halfX = 150;
            pNode->drawLine(Vec2(center.x - halfX, center.y), Vec2(center.x + halfX, center.y), Color4F(0, 0, 0, 1));
        }
        pNode->setLineWidth(2);
        _uiLayer->addChild(pNode);
    }
    
    // Button
    auto pButton = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
    pButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    pButton->setScale(0.8f);
    pButton->setPosition(Vec2(layerSize / 2) + Vec2(120, -60));
    pButton->setTitleText(StringUtils::format("Go to '%d'", _nextIndex));
    pButton->addClickEventListener([this, pButton](Ref*) {
        _listView->scrollToItem(_nextIndex, Vec2::ANCHOR_MIDDLE, Vec2::ANCHOR_MIDDLE);
        _nextIndex = (_nextIndex + (NUMBER_OF_ITEMS / 2)) % NUMBER_OF_ITEMS;
        pButton->setTitleText(StringUtils::format("Go to '%d'", _nextIndex));
    });
    _uiLayer->addChild(pButton);
    
    // Add list items
    static const Size BUTTON_SIZE(50, 40);
    for (int i = 0; i < NUMBER_OF_ITEMS; ++i)
    {
        auto pButton = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        pButton->setContentSize(BUTTON_SIZE);
        pButton->setScale9Enabled(true);
        pButton->setTitleText(StringUtils::format("Button-%d", i));
        _listView->pushBackCustomItem(pButton);
    }
    return true;
}



// UIListViewTest_Magnetic
bool UIListViewTest_Magnetic::init()
{
    if(!UIScene::init())
    {
        return false;
    }
    
    Size layerSize = _uiLayer->getContentSize();
    
    _titleLabel = Text::create("Magnetic scroll", "fonts/Marker Felt.ttf", 32);
    _titleLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _titleLabel->setPosition(Vec2(layerSize / 2) + Vec2(0, _titleLabel->getContentSize().height * 3.15f));
    _uiLayer->addChild(_titleLabel, 3);
    
    // Create the list view
    _listView = ListView::create();
    _listView->setDirection(getListViewDirection());
    _listView->setBounceEnabled(true);
    _listView->setBackGroundImage("cocosui/green_edit.png");
    _listView->setBackGroundImageScale9Enabled(true);
    _listView->setContentSize(layerSize / 2);
    _listView->setScrollBarPositionFromCorner(Vec2(7, 7));
    _listView->setItemsMargin(2.0f);
    _listView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _listView->setPosition(layerSize / 2);
    _uiLayer->addChild(_listView);
    
    // Guide line for center align
    {
        DrawNode* pNode = DrawNode::create();
        Vec2 center = layerSize / 2;
        if(getListViewDirection() == ScrollView::Direction::HORIZONTAL)
        {
            float halfY = 110;
            pNode->drawLine(Vec2(center.x, center.y - halfY), Vec2(center.x, center.y + halfY), Color4F(0, 0, 0, 1));
        }
        else
        {
            float halfX = 150;
            pNode->drawLine(Vec2(center.x - halfX, center.y), Vec2(center.x + halfX, center.y), Color4F(0, 0, 0, 1));
        }
        pNode->setLineWidth(2);
        _uiLayer->addChild(pNode);
    }
    
    // Show the indexes of items on each boundary.
    {
        for(int i = 0; i < 5; ++i)
        {
            _indexLabels[i] = Text::create(" ", "fonts/Marker Felt.ttf", 12);
            _indexLabels[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            _uiLayer->addChild(_indexLabels[i]);
        }
        float deltaX = 145, deltaY = 90;
        _indexLabels[0]->setPosition(_uiLayer->getContentSize() / 2 + Size(-deltaX, 0));   // left
        _indexLabels[1]->setPosition(_uiLayer->getContentSize() / 2 + Size(deltaX, 0));   // right
        _indexLabels[2]->setPosition(_uiLayer->getContentSize() / 2 + Size(0, deltaY));   // top
        _indexLabels[3]->setPosition(_uiLayer->getContentSize() / 2 + Size(0, -deltaY));   // bottom
        _indexLabels[4]->setPosition(_uiLayer->getContentSize() / 2 + Size(deltaX, deltaY));  // center
        
        // Callback
        _listView->ScrollView::addEventListener([this](Ref* ref, ScrollView::EventType eventType) {
            ListView* listView = dynamic_cast<ListView*>(ref);
            if(listView == nullptr || eventType != ScrollView::EventType::CONTAINER_MOVED)
            {
                return;
            }
            auto left = listView->getLeftmostItemInCurrentView();
            auto right = listView->getRightmostItemInCurrentView();
            auto top = listView->getTopmostItemInCurrentView();
            auto bottom = listView->getBottommostItemInCurrentView();
            auto center = listView->getCenterItemInCurrentView();
            
            _indexLabels[0]->setString(StringUtils::format("Left\nindex=%zd", listView->getIndex(left)));
            _indexLabels[1]->setString(StringUtils::format("RIght\nindex=%zd", listView->getIndex(right)));
            _indexLabels[2]->setString(StringUtils::format("Top index=%zd", listView->getIndex(top)));
            _indexLabels[3]->setString(StringUtils::format("Bottom index=%zd", listView->getIndex(bottom)));
            _indexLabels[4]->setString(StringUtils::format("Center\nindex=%zd", listView->getIndex(center)));
        });
    }
    
    // Initial magnetic type
    _listView->setMagneticType(ListView::MagneticType::NONE);
    _titleLabel->setString("MagneticType - NONE");
    
    // Magnetic change button
    auto pButton = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
    pButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    pButton->setScale(0.8f);
    pButton->setPosition(Vec2(layerSize / 2) + Vec2(130, -60));
    pButton->setTitleText("Next Magnetic");
    pButton->addClickEventListener([this](Ref*) {
        ListView::MagneticType eCurrentType = _listView->getMagneticType();
        ListView::MagneticType eNextType;
        std::string sString;
        if(eCurrentType == ListView::MagneticType::NONE)
        {
            eNextType = ListView::MagneticType::CENTER;
            sString = "CENTER";
        }
        else if(eCurrentType == ListView::MagneticType::CENTER)
        {
            eNextType = ListView::MagneticType::BOTH_END;
            sString = "BOTH_END";
        }
        else if(eCurrentType == ListView::MagneticType::BOTH_END)
        {
            if(getListViewDirection() == ScrollView::Direction::HORIZONTAL)
            {
                eNextType = ListView::MagneticType::LEFT;
                sString = "LEFT";
            }
            else
            {
                eNextType = ListView::MagneticType::TOP;
                sString = "TOP";
            }
        }
        else if(eCurrentType == ListView::MagneticType::LEFT)
        {
            eNextType = ListView::MagneticType::RIGHT;
            sString = "RIGHT";
        }
        else if(eCurrentType == ListView::MagneticType::RIGHT)
        {
            eNextType = ListView::MagneticType::NONE;
            sString = "NONE";
        }
        else if(eCurrentType == ListView::MagneticType::TOP)
        {
            eNextType = ListView::MagneticType::BOTTOM;
            sString = "BOTTOM";
        }
        else if(eCurrentType == ListView::MagneticType::BOTTOM)
        {
            eNextType = ListView::MagneticType::NONE;
            sString = "NONE";
        }
        _listView->setMagneticType(eNextType);
        _titleLabel->setString(StringUtils::format("MagneticType - %s", sString.c_str()));
    });
    _uiLayer->addChild(pButton);
    
    // Add list items
    static const Size BUTTON_SIZE(100, 70);
    for (int i = 0; i < 40; ++i)
    {
        auto pButton = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        pButton->setContentSize(BUTTON_SIZE);
        pButton->setScale9Enabled(true);
        pButton->setTitleText(StringUtils::format("Button-%d", i));
        _listView->pushBackCustomItem(pButton);
    }
    return true;
}
