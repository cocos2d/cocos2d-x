

#include "UIListViewTest.h"

// UIListViewTest

UIListViewTest::UIListViewTest()
: m_pDisplayValueLabel(NULL)
, m_nCount(0)
, array(NULL)
{
}

UIListViewTest::~UIListViewTest()
{   
}

bool UIListViewTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the button events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by vertical direction");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        UILabel *alert = UILabel::create();
        alert->setText("ListView");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UIPanel *background = dynamic_cast<UIPanel*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the list view
        m_nCount = 0;
        array = CCArray::create();
        array->retain();
        for (int i = 0; i < 20; ++i)
        {
            CCString* ccstr = CCString::createWithFormat("object_%d", i);
            array->addObject(ccstr);
        }
        
        UIListView *list = UIListView::create();
        list->setClippingEnable(true);
        list->setTouchEnable(true);
        list->setBackGroundImageScale9Enable(true);
        list->setBackGroundImage("cocosgui/green_edit.png");
        list->setSize(CCSizeMake(240, 130));
        CCSize backgroundSize = background->getContentSize();
        list->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                              (backgroundSize.width - list->getRect().size.width) / 2,
                              (widgetSize.height - backgroundSize.height) / 2 +
                              (backgroundSize.height - list->getRect().size.height) / 2));                
        
        float listWidth = list->getRect().size.width;
        float listHeight = list->getRect().size.height;                
         
        for (int i = 0; i < 5; ++i)
        {
            UITextButton* textButton = UITextButton::create();
            textButton->setName("TextButton");
            textButton->setTouchEnable(true);
            textButton->setTextures("cocosgui/backtotoppressed.png", "cocosgui/backtotopnormal.png", "");
            
            UIPanel *panel = UIPanel::create();
            panel->setSize(CCSizeMake(textButton->getRect().size.width, textButton->getRect().size.height));
            textButton->setPosition(ccp(panel->getRect().size.width / 2, panel->getRect().size.height / 2));
            panel->setBackGroundColorType(PANEL_COLOR_SOLID);
            panel->setBackGroundColor(ccc3(255, 0, 0));
            panel->addChild(textButton);
            
            CCSize panel_size = panel->getRect().size;
            panel->setPosition(ccp((listWidth - panel_size.width) / 2,
                                   (listHeight - (panel_size.height + panel_size.height * 0.25)) - i * (panel_size.height + panel_size.height * 0.25)));
            
            list->addChild(panel);
        }
        list->addInitChildEvent(this, coco_ListView_InitChild_selector(UIListViewTest::initChildEvent));
        list->addUpdateChildEvent(this, coco_ListView_UpdateChild_selector(UIListViewTest::updateChildEvent));
        list->initChildWithDataLength(array->count());
        m_pUiLayer->addWidget(list);     
        
        return true;
    }
    
    return false;
}

void UIListViewTest::initChildEvent(CCObject *pSender)
{
    CCString* ccstr = static_cast<CCString*>(array->objectAtIndex(m_nCount));
    UIListView* list = dynamic_cast<UIListView*>(pSender);
    
    UIPanel* panel = dynamic_cast<UIPanel*>(list->getUpdateChild());
    UITextButton* textButton = dynamic_cast<UITextButton*>(panel->getChildByName("TextButton"));
    textButton->setText(ccstr->getCString());    
    
    m_nCount++;
}

void UIListViewTest::updateChildEvent(CCObject *pSender)
{
    UIListView* list = dynamic_cast<UIListView*>(pSender);
    int index = list->getUpdateDataIndex();
    
    if (index < 0 || index >= list->getDataLength())
    {
        list->setUpdateSuccess(false);
    }
    
    CCString* ccstr = static_cast<CCString*>(array->objectAtIndex(index));
    UIPanel* panel = dynamic_cast<UIPanel*>(list->getUpdateChild());
    UITextButton* textButton = dynamic_cast<UITextButton*>(panel->getChildByName("TextButton"));
    textButton->setText(ccstr->getCString()); 
    list->setUpdateSuccess(true);    
}