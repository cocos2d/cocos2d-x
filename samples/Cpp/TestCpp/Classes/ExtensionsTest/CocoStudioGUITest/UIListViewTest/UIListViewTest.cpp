

#include "UIListViewTest.h"

const char* font_UIListViewTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

// UIListViewTest_Vertical

UIListViewTest_Vertical::UIListViewTest_Vertical()
: m_pDisplayValueLabel(NULL)
, m_nCount(0)
, m_array(NULL)
{
}

UIListViewTest_Vertical::~UIListViewTest_Vertical()
{   
}

bool UIListViewTest_Vertical::init()
{
    if (UIScene::init())
    {
        Size widgetSize = m_pWidget->getSize();
        
        // Add a label in which the button events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by vertical direction");
        m_pDisplayValueLabel->setFontName(font_UIListViewTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        UILabel *alert = UILabel::create();
        alert->setText("ListView");
        alert->setFontName(font_UIListViewTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        
        UIListView* lv = UIListView::create();
        UIButton* model = UIButton::create();
        model->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        lv->setItemModel(model);
        
        for (int i=0; i<20; i++)
        {
            lv->pushBackDefaultItem();
        }
        lv->setItemsMargin(10);
        lv->setGravity(LISTVIEW_GRAVITY_CENTER_HORIZONTAL);
        lv->setSize(Size(100, 100));
        lv->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        lv->setBackGroundColor(Color3B::GREEN);
        lv->setPosition(Point(100, 100));
        m_pUiLayer->addWidget(lv);
        
        return true;
    }
    
    return false;
}

// UIListViewTest_Horizontal

UIListViewTest_Horizontal::UIListViewTest_Horizontal()
: m_pDisplayValueLabel(NULL)
, m_nCount(0)
, m_array(NULL)
{
}

UIListViewTest_Horizontal::~UIListViewTest_Horizontal()
{
}

bool UIListViewTest_Horizontal::init()
{
    if (UIScene::init())
    {
        Size widgetSize = m_pWidget->getSize();
        
        // Add a label in which the button events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by vertical direction");
        m_pDisplayValueLabel->setFontName(font_UIListViewTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        UILabel *alert = UILabel::create();
        alert->setText("ListView");
        alert->setFontName(font_UIListViewTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.925));
        m_pUiLayer->addWidget(alert);
        

        UIListView* lv = UIListView::create();
        lv->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
        UIButton* model = UIButton::create();
        model->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        lv->setItemModel(model);
        
        for (int i=0; i<20; i++)
        {
            lv->pushBackDefaultItem();
        }
        lv->setItemsMargin(10);
        lv->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
        lv->setSize(Size(100, 100));
        lv->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        lv->setBackGroundColor(Color3B::GREEN);
        lv->setPosition(Point(100, 100));
        m_pUiLayer->addWidget(lv);
        return true;
    }
    
    return false;
}