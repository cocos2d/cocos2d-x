

#include "CocosGUIExamplesRegisterScene.h"
#include "CocosGUIExamplesEquipScene.h"
#include "CocosGUIScene.h"

CocosGUIExamplesRegisterScene::CocosGUIExamplesRegisterScene(bool bPortrait)
: m_pUILayer(NULL)
, m_pLayout(NULL)
{
    CCScene::init();
}

CocosGUIExamplesRegisterScene::~CocosGUIExamplesRegisterScene()
{
    
}

void CocosGUIExamplesRegisterScene::onEnter()
{
    CCScene::onEnter();
    
    m_pUILayer = UILayer::create();
    m_pUILayer->scheduleUpdate();
    addChild(m_pUILayer);
    
    // register root from json
    m_pLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("cocosgui/gui_examples/register_1/register_1.json"));
    m_pUILayer->addWidget(m_pLayout);
    
    
    // e-mail layout
    Layout* eMail_layout = dynamic_cast<Layout*>(m_pLayout->getChildByName("e-mail_Panel"));
    
    // ui node container add to e-mail layout
    UINodeContainer* nodeContainer = UINodeContainer::create();
    nodeContainer->setPosition(ccp(eMail_layout->getContentSize().width / 2, eMail_layout->getContentSize().height / 2));
    
    // CCEditBox add to ui node container
    CCSize editBoxSize = eMail_layout->getContentSize();
    CCEditBox* email_editBox = CCEditBox::create(editBoxSize, CCScale9Sprite::create("cocosgui/gui_examples/register_1/e-mail.png"));
    email_editBox->setFontName("SongTypeFont");
    email_editBox->setFontSize(20);
    email_editBox->setPlaceholderFontColor(ccc3(127, 127, 127));
    email_editBox->setPlaceHolder("Email");
    email_editBox->setInputMode(kEditBoxInputModeEmailAddr);
    nodeContainer->addCCNode(email_editBox);
    
    // add ui node container to layout
    eMail_layout->addChild(nodeContainer);
    
    // content panel
    Layout* content_panel = dynamic_cast<Layout*>(m_pLayout->getChildByName("content_Panel"));
    
    // password textfield add event
    UITextField* passwordAgin_textfield = dynamic_cast<UITextField*>(content_panel->getChildByName("password agin_TextField"));
    passwordAgin_textfield->addAttachWithIMEEvent(this, coco_TextField_AttachWithIME_selector(CocosGUIExamplesRegisterScene::attachWithIMEEvent));
    passwordAgin_textfield->addDetachWithIMEEvent(this, coco_TextField_DetachWithIME_selector(CocosGUIExamplesRegisterScene::detachWithIMEEvent));
    
    
    // register button
    Layout* register_button_panel = dynamic_cast<Layout*>(m_pLayout->getChildByName("register button_Panel"));
    
    UIButton* button = dynamic_cast<UIButton*>(register_button_panel->getChildByName("register_Button"));
    button->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesRegisterScene::toCocosGUIExamplesEquipScene));
    
    // back button
    UIButton* back_button = UIButton::create();
    back_button->setTouchEnable(true);
    back_button->loadTextures("cocosgui/UITest/b1.png", "cocosgui/UITest/b2.png", "");
    back_button->setPosition(ccp(back_button->getContentSize().width, back_button->getContentSize().height));
    back_button->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesRegisterScene::toCocosGUIScene));
//    back_button->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesRegisterScene::toCocosGUIExamplesStartScene));
    m_pUILayer->addWidget(back_button);
}

void CocosGUIExamplesRegisterScene::onExit()
{
    m_pUILayer->removeFromParent();
    
    CCSSceneReader::purgeSceneReader();
    UIHelper::purgeUIHelper();
	UIActionManager::shareManager()->purgeUIActionManager();
    
    CCScene::onExit();
}

void CocosGUIExamplesRegisterScene::runThisTest()
{
    CCDirector::sharedDirector()->replaceScene(this);
}

void CocosGUIExamplesRegisterScene::toCocosGUIScene(CCObject *pSender)
{
    CocosGUITestScene* pScene = new CocosGUITestScene();
    pScene->runThisTest();
    pScene->release();
}

void CocosGUIExamplesRegisterScene::toCocosGUIExamplesEquipScene(CCObject *pSender)
{
    CocosGUIExamplesEquipScene* pScene = new CocosGUIExamplesEquipScene();
    pScene->runThisTest();
    pScene->release();
}

void CocosGUIExamplesRegisterScene::attachWithIMEEvent(CCObject* pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);
        
    if (strcmp(textField->getName(), "password agin_TextField") == 0)
    {
        CCMoveBy* moveBy = CCMoveBy::create(0.1f, ccp(0, textField->getContentSize().height));
        m_pLayout->runAction(moveBy);
    }    
}

void CocosGUIExamplesRegisterScene::detachWithIMEEvent(CCObject *pSender)
{
    UITextField* textField = dynamic_cast<UITextField*>(pSender);    
    
    if (strcmp(textField->getName(), "password agin_TextField") == 0)
    {
        CCMoveBy* moveBy = CCMoveBy::create(0.1f, ccp(0, -textField->getContentSize().height));
        m_pLayout->runAction(moveBy);
    }
}