

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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the scrollview alert will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by vertical direction");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("ScrollGrid set child coordinate according to column");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        m_pUiLayer->addWidget(alert);
        
        Layout* background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the grid view with grid layout mode column
        UIGridView* gridView = UIGridView::create();
        gridView->setLayoutType(LAYOUT_GRID_MODE_COLUMN);
        gridView->setScrollEnabled(true);
        gridView->setDirection(SCROLLVIEW_DIR_VERTICAL);
        gridView->setBounceEnabled(true);
        gridView->setTouchEnabled(true);
        gridView->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getSize();
        gridView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                    (backgroundSize.width - gridView->getSize().width) / 2,
                                    (widgetSize.height - backgroundSize.height) / 2 +
                                    (backgroundSize.height - gridView->getSize().height) / 2));
        gridView->addEventListenerScrollView(this, scrollvieweventselector(UIGridViewTest_Mode_Column::selectedChildEvent));
        m_pUiLayer->addWidget(gridView);
        
        
        // create items
        int count = 19;
        for (int i = 0; i < count; ++i)
        {
            UIButton* button = UIButton::create();
            button->setName("TextButton");
            button->setTouchEnabled(true);
            button->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
            button->setScale9Enabled(true);
            CCAffineTransform transform = CCAffineTransformMakeIdentity();
            transform = CCAffineTransformScale(transform, 3.0f, 1.3f);
            button->setSize(CCSizeApplyAffineTransform(button->getContentSize(), transform));
            button->setTitleText(CCString::createWithFormat("grid_%d", i)->getCString());
            
            Layout* item = Layout::create();
            item->setTouchEnabled(true);
            item->setSize(button->getSize());
            button->setPosition(ccp(item->getSize().width / 2, item->getSize().height / 2));
            item->addChild(button);
            
            gridView->addChild(item);
        }
        
        // set grid view row and column
        UIWidget* item = static_cast<UIWidget*>(gridView->getChildren()->objectAtIndex(0));
        int rowCount = gridView->getSize().height / item->getSize().height;
        int columnCount = gridView->getSize().width / item->getSize().width;
        gridView->setGridLayoutRowAndColumnCount(rowCount, columnCount);
        
        // execute layout
        gridView->refreshView();
        
        return true;
    }
    
    return false;
}

void UIGridViewTest_Mode_Column::selectedChildEvent(CCObject *pSender, ScrollviewEventType type)
{
    switch (type)
    {
        case SCROLLVIEW_EVENT_SELECT_CHILD:
        {
            UIGridView* gridView = static_cast<UIGridView*>(pSender);
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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the scrollview alert will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by horizontal direction");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("ScrollGrid set child coordinate according to row");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        m_pUiLayer->addWidget(alert);
        
        Layout* background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the grid view with grid layout mode row
        UIGridView* gridView = UIGridView::create();
        gridView->setLayoutType(LAYOUT_GRID_MODE_ROW);
        gridView->setScrollEnabled(true);
        gridView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
        gridView->setBounceEnabled(true);
        gridView->setTouchEnabled(true);
        gridView->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getSize();
        gridView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                    (backgroundSize.width - gridView->getSize().width) / 2,
                                    (widgetSize.height - backgroundSize.height) / 2 +
                                    (backgroundSize.height - gridView->getSize().height) / 2));
        gridView->addEventListenerScrollView(this, scrollvieweventselector(UIGridViewTest_Mode_Row::selectedChildEvent));
        m_pUiLayer->addWidget(gridView);
        
        
        // create items
        int count = 19;
        for (int i = 0; i < count; ++i)
        {
            UIButton* button = UIButton::create();
            button->setName("TextButton");
            button->setTouchEnabled(true);
            button->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
            button->setScale9Enabled(true);
            CCAffineTransform transform = CCAffineTransformMakeIdentity();
            transform = CCAffineTransformScale(transform, 3.0f, 1.3f);
            button->setSize(CCSizeApplyAffineTransform(button->getContentSize(), transform));
            button->setTitleText(CCString::createWithFormat("grid_%d", i)->getCString());
            
            Layout* item = Layout::create();
            item->setTouchEnabled(true);
            item->setSize(button->getSize());
            button->setPosition(ccp(item->getSize().width / 2, item->getSize().height / 2));
            item->addChild(button);
            
            gridView->addChild(item);
        }
        
        // set grid view row and column
        UIWidget* item = static_cast<UIWidget*>(gridView->getChildren()->objectAtIndex(0));
        int rowCount = gridView->getSize().height / item->getSize().height;
        int columnCount = gridView->getSize().width / item->getSize().width;
        gridView->setGridLayoutRowAndColumnCount(rowCount, columnCount);
        
        // execute layout
        gridView->refreshView();
        
        return true;
    }
    
    return false;
}

void UIGridViewTest_Mode_Row::selectedChildEvent(CCObject *pSender, ScrollviewEventType type)
{
    switch (type)
    {
        case SCROLLVIEW_EVENT_SELECT_CHILD:
        {
            UIGridView* gridView = static_cast<UIGridView*>(pSender);
            CCLOG("select child index = %d", gridView->getSelectedChildIndex());
        }
            break;
            
        default:
            break;
    }
}
