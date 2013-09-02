

#include "CocosGUIExamplesPageScene.h"
#include "CocosGUIExamplesMapScene.h"

const char* page_image_textures[4] =
{
    "cocosgui/gui_examples/page_1/page_content/CocoStudio_AnimationEditor.png",
    "cocosgui/gui_examples/page_1/page_content/CocoStudio_DataEditor.png",
    "cocosgui/gui_examples/page_1/page_content/CocoStudio_SceneEditor.png",
    "cocosgui/gui_examples/page_1/page_content/CocoStudio_UIEditor.png",
};

CocosGUIExamplesPageScene::CocosGUIExamplesPageScene()
{
    CCScene::init();
}

CocosGUIExamplesPageScene::~CocosGUIExamplesPageScene()
{
    
}

void CocosGUIExamplesPageScene::onEnter()
{
    CCScene::onEnter();
    
    m_pUILayer = UILayer::create();
    m_pUILayer->scheduleUpdate();
    addChild(m_pUILayer);
    
    PageInit();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    UILabel* label = UILabel::create();
    label->setText("Move by horizontal direction");
    label->setFontName("Marker Felt");
    label->setFontSize(32);
    label->setAnchorPoint(ccp(0.5f, -1));
    label->setPosition(ccp(winSize.width / 2.0f, winSize.height / 2.0f + label->getContentSize().height * 1.5));
    m_pUILayer->addWidget(label);
    
    // left button
    UIButton* left_button = UIButton::create();
    left_button->setTouchEnable(true);
    left_button->loadTextures("cocosgui/UITest/b1.png", "cocosgui/UITest/b2.png", "");
    float left_button_width = left_button->getContentSize().width;
    left_button->setPosition(ccp(left_button_width - left_button_width / 2, m_pUILayer->getContentSize().height / 2));
    left_button->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesPageScene::toCocosGUIExamplesMapScene));
    m_pUILayer->addWidget(left_button);
}

void CocosGUIExamplesPageScene::onExit()
{
    m_pUILayer->removeFromParent();
    
    CCSSceneReader::purgeSceneReader();
    UIHelper::purgeUIHelper();
    UIActionManager::purgeUIActionManager();
    
    CCScene::onExit();
}

void CocosGUIExamplesPageScene::runThisTest()
{
    CCDirector::sharedDirector()->replaceScene(this);
}

void CocosGUIExamplesPageScene::toCocosGUIExamplesMapScene(CCObject *pSender)
{
    CocosGUIExamplesMapScene* pScene = new CocosGUIExamplesMapScene();
    pScene->runThisTest();
    pScene->release();    
}

void CocosGUIExamplesPageScene::PageInit()
{
    // page root from json
    Layout* page_root = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("cocosgui/gui_examples/page_1/page_1.json"));
    m_pUILayer->addWidget(page_root);
    
    // page layout
    Layout* page_layout = dynamic_cast<Layout*>(page_root->getChildByName("page_panel"));
    
    // page view add to page layout
    UIPageView* pageView = UIPageView::create();
    pageView->setTouchEnable(true);
    pageView->setSize(page_layout->getContentSize());
    
    // layout add to page view
    for (int i = 0; i < 4; ++i)
    {
        Layout* layout = Layout::create();
        layout->setSize(pageView->getContentSize());
        
        UIImageView* imageView = UIImageView::create();
        imageView->setTouchEnable(true);
        imageView->loadTexture(page_image_textures[i]);
        imageView->setPosition(ccp(layout->getContentSize().width / 2, layout->getContentSize().height / 2));
        layout->addChild(imageView);                
        
        pageView->addPage(layout);
    }    
    pageView->addPageTurningEvent(this, coco_PageView_PageTurning_selector(CocosGUIExamplesPageScene::pageTurningEvent));
    page_layout->addChild(pageView);
}

void CocosGUIExamplesPageScene::pageTurningEvent(CCObject* pSender)
{
    UIPageView* pageView = dynamic_cast<UIPageView*>(pSender);
    int page = pageView->getPage() + 1;
    
    Layout* page_root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName("page_root"));
    
    // set current page number for text
    UILabel* page_alert_label = dynamic_cast<UILabel*>(page_root->getChildByName("page_alert_label"));
    page_alert_label->setText(CCString::createWithFormat("page %d", page)->getCString());
    
    // set current page for image
    Layout* page_alert_bottom_layout = dynamic_cast<Layout*>(page_root->getChildByName("page_alert_bottom_panel"));
    int count = page_alert_bottom_layout->getChildren()->count();
    for (int i = count / 2; i < count; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(page_alert_bottom_layout->getChildren()->objectAtIndex(i));
        child->setVisible(false);
    }    
    UIImageView* page_imageview = dynamic_cast<UIImageView*>(page_root->getChildByName(CCString::createWithFormat("page_%d_imageview", page)->getCString()));
    page_imageview->setVisible(true);
}