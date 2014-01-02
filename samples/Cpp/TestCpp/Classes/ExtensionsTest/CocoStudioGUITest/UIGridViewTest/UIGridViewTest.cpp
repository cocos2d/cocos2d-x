

#include "UIGridViewTest.h"


// UIGridViewTest_Mode_Column

UIGridViewTest_Mode_Column::UIGridViewTest_Mode_Column()
{
}

UIGridViewTest_Mode_Column::~UIGridViewTest_Mode_Column()
{
}

bool UIGridViewTest_Mode_Column::init()
{
    if (UIScene::init())
    { 
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the scrollview alert will be displayed
        _displayValueLabel = gui::Label::create();
        _displayValueLabel->setText("Move by vertical direction");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Layout is in use with GridView bases on column mode");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the grid view with grid layout mode column
        GridView* gridView = GridView::create();
        gridView->setLayoutType(LAYOUT_GRID_MODE_COLUMN);
        gridView->setScrollEnabled(true);
        gridView->setDirection(SCROLLVIEW_DIR_VERTICAL);
        gridView->setBounceEnabled(true);
        gridView->setTouchEnabled(true);
        gridView->setSize(Size(280, 150));
        Size backgroundSize = background->getSize();
        gridView->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                      (backgroundSize.width - gridView->getSize().width) / 2.0f,
                                      (widgetSize.height - backgroundSize.height) / 2.0f +
                                      (backgroundSize.height - gridView->getSize().height) / 2.0f));
        gridView->addEventListenerScrollView(this, scrollvieweventselector(UIGridViewTest_Mode_Column::selectedChildEvent));
        _uiLayer->addChild(gridView);
        
        
        // create items
        int count = 19;
        for (int i = 0; i < count; ++i)
        {
            Button* button = Button::create();
            button->setTouchEnabled(true);
            button->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
            button->setScale9Enabled(true);
            AffineTransform transform = AffineTransformMakeIdentity();
            transform = AffineTransformScale(transform, 3.0f, 1.3f);
            button->setSize(SizeApplyAffineTransform(button->getContentSize(), transform));
            button->setTitleText(String::createWithFormat("grid_%d", i)->getCString());
            
            Layout* item = Layout::create();
            item->setTouchEnabled(true);
            item->setSize(button->getSize());
            button->setPosition(Point(item->getSize().width / 2.0f, item->getSize().height / 2.0f));
            item->addChild(button);
            
            gridView->addChild(item);
        }
        
        // set grid view row and column
        Widget* item = static_cast<Widget*>(gridView->getChildren().at(0));
        int rowCount = gridView->getSize().height / item->getSize().height;
        int columnCount = gridView->getSize().width / item->getSize().width;
        gridView->setGridLayoutRowAndColumnCount(rowCount, columnCount);
        
        return true;
    }
    
    return false;
}

void UIGridViewTest_Mode_Column::selectedChildEvent(Object *pSender, ScrollviewEventType type)
{
    switch (type)
    {
        case SCROLLVIEW_EVENT_SELECT_CHILD:
        {
            GridView* gridView = static_cast<GridView*>(pSender);
            CCLOG("select child index = %d", gridView->getSelectedChildIndex());
        }
            break;
            
        default:
            break;
    }
}


// UIGridViewTest_Mode_Row

UIGridViewTest_Mode_Row::UIGridViewTest_Mode_Row()
{
}

UIGridViewTest_Mode_Row::~UIGridViewTest_Mode_Row()
{
}

bool UIGridViewTest_Mode_Row::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the scrollview alert will be displayed
        _displayValueLabel = gui::Label::create();
        _displayValueLabel->setText("Move by horizontal direction");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Layout is in use with GridView bases on row mode");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the scroll grid with grid layout mode row
        GridView* gridView = GridView::create();
        gridView->setLayoutType(LAYOUT_GRID_MODE_ROW);
        gridView->setScrollEnabled(true);
        gridView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
        gridView->setBounceEnabled(true);
        gridView->setTouchEnabled(true);
        gridView->setSize(Size(280, 150));
        Size backgroundSize = background->getSize();
        gridView->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                    (backgroundSize.width - gridView->getSize().width) / 2.0f,
                                    (widgetSize.height - backgroundSize.height) / 2.0f +
                                    (backgroundSize.height - gridView->getSize().height) / 2.0f));
        gridView->addEventListenerScrollView(this, scrollvieweventselector(UIGridViewTest_Mode_Row::selectedChildEvent));
        _uiLayer->addChild(gridView);
        
        
        // create items
        int count = 19;
        for (int i = 0; i < count; ++i)
        {
            Button* button = Button::create();
            button->setTouchEnabled(true);
            button->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
            button->setScale9Enabled(true);
            AffineTransform transform = AffineTransformMakeIdentity();
            transform = AffineTransformScale(transform, 3.0f, 1.3f);
            button->setSize(SizeApplyAffineTransform(button->getContentSize(), transform));
            button->setTitleText(String::createWithFormat("grid_%d", i)->getCString());
            
            Layout* item = Layout::create();
            item->setTouchEnabled(true);
            item->setSize(button->getSize());
            button->setPosition(Point(item->getSize().width / 2.0f, item->getSize().height / 2.0f));
            item->addChild(button);
            
            gridView->addChild(item);
        }
        
        // set grid view row and column
        Widget* item = static_cast<Widget*>(gridView->getChildren().at(0));
        int rowCount = gridView->getSize().height / item->getSize().height;
        int columnCount = gridView->getSize().width / item->getSize().width;
        gridView->setGridLayoutRowAndColumnCount(rowCount, columnCount);
        
        return true;
    }
    
    return false;
}

void UIGridViewTest_Mode_Row::selectedChildEvent(Object *pSender, ScrollviewEventType type)
{
    switch (type)
    {
        case SCROLLVIEW_EVENT_SELECT_CHILD:
        {
            GridView* gridView = static_cast<GridView*>(pSender);
            CCLOG("select child index = %d", gridView->getSelectedChildIndex());
        }
            break;
            
        default:
            break;
    }
}
