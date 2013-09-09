

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
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the button events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by vertical direction");
        m_pDisplayValueLabel->setFontName(font_UIListViewTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        UILabel *alert = UILabel::create();
        alert->setText("ListView");
        alert->setFontName(font_UIListViewTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the list view
        m_nCount = 0;
        m_array = CCArray::create();
        m_array->retain();
        for (int i = 0; i < 20; ++i)
        {
            CCString* ccstr = CCString::createWithFormat("object_%d", i);
            m_array->addObject(ccstr);
        }
        
        UIListView *listView = UIListView::create();
        listView->setTouchEnable(true);
        listView->setBackGroundImageScale9Enabled(true);
        listView->setBackGroundImage("cocosgui/green_edit.png");
        listView->setSize(CCSizeMake(240, 130));
        CCSize backgroundSize = background->getContentSize();
        listView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                              (backgroundSize.width - listView->getRect().size.width) / 2,
                              (widgetSize.height - backgroundSize.height) / 2 +
                              (backgroundSize.height - listView->getRect().size.height) / 2));                
        
        float listWidth = listView->getRect().size.width;
        float listHeight = listView->getRect().size.height;                
         
        for (int i = 0; i < 5; ++i)
        {
            UITextButton* textButton = UITextButton::create();
            textButton->setName("TextButton");
            textButton->setTouchEnable(true);
            textButton->loadTextures("cocosgui/backtotoppressed.png", "cocosgui/backtotopnormal.png", "");
            
            Layout *layout = Layout::create();
            layout->setName(CCString::createWithFormat("panel_%i", i)->getCString());
            layout->setSize(CCSizeMake(textButton->getRect().size.width, textButton->getRect().size.height));
            textButton->setPosition(ccp(layout->getRect().size.width / 2, layout->getRect().size.height / 2));            
            layout->addChild(textButton);
            
            CCSize panel_size = layout->getRect().size;
            layout->setPosition(ccp((listWidth - panel_size.width) / 2,
                                   (listHeight - (panel_size.height + panel_size.height * 0.25)) - i * (panel_size.height + panel_size.height * 0.25)));
            
            listView->addChild(layout);
        }
        listView->addInitChildEvent(this, coco_ListView_InitChild_selector(UIListViewTest_Vertical::initChildEvent));
        listView->addUpdateChildEvent(this, coco_ListView_UpdateChild_selector(UIListViewTest_Vertical::updateChildEvent));
        listView->initChildWithDataLength(m_array->count());
        m_pUiLayer->addWidget(listView);
        
        return true;
    }
    
    return false;
}

void UIListViewTest_Vertical::initChildEvent(CCObject *pSender)
{
    CCString* ccstr = static_cast<CCString*>(m_array->objectAtIndex(m_nCount));
    UIListView* list = dynamic_cast<UIListView*>(pSender);
    
    Layout* layout = dynamic_cast<Layout*>(list->getUpdateChild());
    UITextButton* textButton = dynamic_cast<UITextButton*>(layout->getChildByName("TextButton"));
    textButton->setText(ccstr->getCString());    
    
    m_nCount++;
}

void UIListViewTest_Vertical::updateChildEvent(CCObject *pSender)
{
    UIListView* list = dynamic_cast<UIListView*>(pSender);
    int index = list->getUpdateDataIndex();
    
    if (index < 0 || index >= list->getDataLength())
    {
        list->setUpdateSuccess(false);
    }
    
    CCString* ccstr = static_cast<CCString*>(m_array->objectAtIndex(index));
    Layout* layout = dynamic_cast<Layout*>(list->getUpdateChild());
    UITextButton* textButton = dynamic_cast<UITextButton*>(layout->getChildByName("TextButton"));
    textButton->setText(ccstr->getCString()); 
    list->setUpdateSuccess(true);    
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
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the button events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by vertical direction");
        m_pDisplayValueLabel->setFontName(font_UIListViewTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        UILabel *alert = UILabel::create();
        alert->setText("ListView");
        alert->setFontName(font_UIListViewTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the list view
        m_nCount = 0;
        m_array = CCArray::create();
        m_array->retain();
        for (int i = 0; i < 20; ++i)
        {
            CCString* ccstr = CCString::createWithFormat("object_%d", i);
            m_array->addObject(ccstr);
        }
        
        UIListView *listView = UIListView::create();
        listView->setDirection(LISTVIEW_DIR_HORIZONTAL);
        listView->setTouchEnabled(true);
        listView->setBackGroundImageScale9Enabled(true);
        listView->setBackGroundImage("cocosgui/green_edit.png");
        listView->setSize(CCSizeMake(240, 130));
        CCSize backgroundSize = background->getContentSize();
        listView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                              (backgroundSize.width - listView->getRect().size.width) / 2,
                              (widgetSize.height - backgroundSize.height) / 2 +
                              (backgroundSize.height - listView->getRect().size.height) / 2));
        
        float listHeight = listView->getRect().size.height;
        
        for (int i = 0; i < 3; ++i)
        {
            UITextButton* textButton = UITextButton::create();
            textButton->setName("TextButton");
            textButton->setTouchEnabled(true);
            textButton->loadTextures("cocosgui/backtotoppressed.png", "cocosgui/backtotopnormal.png", "");
            
            Layout *layout = Layout::create();
            layout->setName(CCString::createWithFormat("panel_%i", i)->getCString());
            layout->setSize(CCSizeMake(textButton->getRect().size.width, textButton->getRect().size.height));
            textButton->setPosition(ccp(layout->getRect().size.width / 2, layout->getRect().size.height / 2));
            layout->addChild(textButton);
            
            CCSize layout_size = layout->getRect().size;
            layout->setPosition(ccp(0 + (layout_size.width * 0.2) + i * (layout_size.width + layout_size.width * 0.2),
                                    (listHeight - layout_size.height) / 2));
            
            listView->addChild(layout);
        }
        listView->addInitChildEvent(this, coco_ListView_InitChild_selector(UIListViewTest_Horizontal::initChildEvent));
        listView->addUpdateChildEvent(this, coco_ListView_UpdateChild_selector(UIListViewTest_Horizontal::updateChildEvent));
        listView->initChildWithDataLength(m_array->count());
        m_pUiLayer->addWidget(listView);
        
        return true;
    }
    
    return false;
}

void UIListViewTest_Horizontal::initChildEvent(CCObject *pSender)
{
    CCString* ccstr = static_cast<CCString*>(m_array->objectAtIndex(m_nCount));
    UIListView* list = dynamic_cast<UIListView*>(pSender);
    
    Layout* layout = dynamic_cast<Layout*>(list->getUpdateChild());
    UITextButton* textButton = dynamic_cast<UITextButton*>(layout->getChildByName("TextButton"));
    textButton->setText(ccstr->getCString());
    
    m_nCount++;
}

void UIListViewTest_Horizontal::updateChildEvent(CCObject *pSender)
{
    UIListView* list = dynamic_cast<UIListView*>(pSender);
    int index = list->getUpdateDataIndex();
    
    if (index < 0 || index >= list->getDataLength())
    {
        list->setUpdateSuccess(false);
    }
    
    CCString* ccstr = static_cast<CCString*>(m_array->objectAtIndex(index));
    Layout* layout = dynamic_cast<Layout*>(list->getUpdateChild());
    UITextButton* textButton = dynamic_cast<UITextButton*>(layout->getChildByName("TextButton"));
    textButton->setText(ccstr->getCString());
    list->setUpdateSuccess(true);
}