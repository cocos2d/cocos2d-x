

#include "CocosGUIExamplesMapScene.h"
#include "CocosGUIExamplesWeaponScene.h"
#include "CocosGUIExamplesPageScene.h"

const char* buildPngPaths[5] =
{
    "cocosgui/gui_examples/map_1/image_castle.png",
    "cocosgui/gui_examples/map_1/image_castle.png",
    "cocosgui/gui_examples/map_1/image_castle.png",
    "cocosgui/gui_examples/map_1/image_castle.png",
    "cocosgui/gui_examples/map_1/image_castle.png",
};

const char* buildNames[5] =
{
    "castle 1",
    "castle 2",
    "castle 3",
    "castle 4",
    "castle 5",
};

CocosGUIExamplesMapScene::CocosGUIExamplesMapScene()
{
    CCScene::init();
}

CocosGUIExamplesMapScene::~CocosGUIExamplesMapScene()
{
    
}

void CocosGUIExamplesMapScene::onEnter()
{
    CCScene::onEnter();
    
    m_pUILayer = UILayer::create();
    m_pUILayer->scheduleUpdate();
    addChild(m_pUILayer);
    
    MapInit();
    MapAlertInit();
    
    // left button
    UIButton* left_button = UIButton::create();
    left_button->setTouchEnable(true);
    left_button->loadTextures("cocosgui/UITest/b1.png", "cocosgui/UITest/b2.png", "");
    float left_button_width = left_button->getContentSize().width;
    left_button->setPosition(ccp(left_button_width - left_button_width / 2, m_pUILayer->getContentSize().height / 2));
    left_button->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesMapScene::toCocosGUIExamplesWeaponScene));
    m_pUILayer->addWidget(left_button);
    
    // right button
    UIButton* right_button = UIButton::create();
    right_button->setTouchEnable(true);
    right_button->loadTextures("cocosgui/UITest/f1.png", "cocosgui/UITest/f2.png", "");
    right_button->setPosition(ccp(m_pUILayer->getContentSize().width - right_button->getContentSize().width / 2, m_pUILayer->getContentSize().height / 2));
    right_button->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesMapScene::toCocosGUIExamplesPageScene));
    m_pUILayer->addWidget(right_button);
}

void CocosGUIExamplesMapScene::onExit()
{
    m_pUILayer->removeFromParent();
    
    CCSSceneReader::purgeSceneReader();
    UIHelper::purgeUIHelper();
    UIActionManager::purgeUIActionManager();
    
    CCScene::onExit();
}

void CocosGUIExamplesMapScene::runThisTest()
{
    CCDirector::sharedDirector()->replaceScene(this);
}

void CocosGUIExamplesMapScene::toCocosGUIExamplesWeaponScene(CCObject *pSender)
{
    CocosGUIExamplesWeaponScene* pScene = new CocosGUIExamplesWeaponScene();
    pScene->runThisTest();
    pScene->release();
}

void CocosGUIExamplesMapScene::toCocosGUIExamplesPageScene(CCObject *pSender)
{
    CocosGUIExamplesPageScene* pScene = new CocosGUIExamplesPageScene();
    pScene->runThisTest();
    pScene->release();
}

void CocosGUIExamplesMapScene::MapInit()
{
    // map root from json
    Layout* map_root = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("cocosgui/gui_examples/map_1/map_1.json"));\
    m_pUILayer->addWidget(map_root);    
    
    // build button on map root
    Layout* button_layout = dynamic_cast<Layout*>(map_root->getChildByName("button_Panel"));
    
    for (int i = 0; i < button_layout->getChildren()->count(); ++i)
    {
        UIButton* build_button = dynamic_cast<UIButton*>(button_layout->getChildren()->objectAtIndex(i));
        build_button->setPressedActionEnabled(true);
        build_button->setWidgetTag(MAP_BUTTON_TAG + i);
        build_button->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesMapScene::buildTouchEvent));
    }
}

void CocosGUIExamplesMapScene::buildTouchEvent(CCObject *pSender)
{
    UIButton* build_button = dynamic_cast<UIButton*>(pSender);
    
    Layout* map_alert_root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName("map_alert_root"));
    map_alert_root->setVisible(true);
    
    UIImageView* alert_imageview = dynamic_cast<UIImageView*>(map_alert_root->getChildByName("alert_imageview"));
    alert_imageview->setTexture(buildPngPaths[build_button->getWidgetTag() - MAP_BUTTON_TAG]);
    
    UILabel* alert_label = dynamic_cast<UILabel*>(map_alert_root->getChildByName("text_textarea"));
    alert_label->setColor(ccBLACK);
    alert_label->setTextHorizontalAlignment(kCCTextAlignmentCenter);
    alert_label->setTextVerticalAlignment(kCCVerticalTextAlignmentCenter);
    alert_label->setText(buildNames[build_button->getWidgetTag() - MAP_BUTTON_TAG]);
}

void CocosGUIExamplesMapScene::MapAlertInit()
{
    // map alert from json
    Layout* map_alert_root = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("cocosgui/gui_examples/map_alert_1/map_alert_1.json"));
    map_alert_root->setVisible(false);
    map_alert_root->setPosition(ccp((m_pUILayer->getContentSize().width - map_alert_root->getSize().width) / 2,
                                    (m_pUILayer->getContentSize().height - map_alert_root->getSize().height) / 2));
    m_pUILayer->addWidget(map_alert_root);
    
    UIButton* close_button = dynamic_cast<UIButton*>(map_alert_root->getChildByName("close_button"));
    close_button->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesMapScene::MapAlertClose));
}

void CocosGUIExamplesMapScene::MapAlertClose(CCObject* pSender)
{
    Layout* map_alert_root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName("map_alert_root"));
    map_alert_root->setVisible(false);
}