
#include "cocos-ext.h"
#include "UIScene.h"
#include "UISceneManager.h"
#include "../ExtensionsTest.h"
#include "CocosGUIScene.h"

UIScene::UIScene()
: m_pSceneTitle(NULL)
, m_pUiLayer(NULL)
{
    
}

UIScene::~UIScene()
{
	
}

bool UIScene::init()
{
    if (CCLayer::init())
    {
        m_pUiLayer = UILayer::create();
        addChild(m_pUiLayer);
        
        m_pWidget = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosgui/UITest/UITest.json"));
        m_pUiLayer->addWidget(m_pWidget);
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        CCSize rootSize = m_pWidget->getSize();
        m_pUiLayer->setPosition(CCPoint((screenSize.width - rootSize.width) / 2,
                                    (screenSize.height - rootSize.height) / 2));
        m_pSceneTitle = dynamic_cast<UILabel*>(m_pUiLayer->getWidgetByName("UItest"));
        
        UILabel* back_label = dynamic_cast<UILabel*>(m_pUiLayer->getWidgetByName("back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene::toCocosGUITestScene));
        
        UIButton* left_button = dynamic_cast<UIButton*>(m_pUiLayer->getWidgetByName("left_Button"));
        left_button->addTouchEventListener(this, toucheventselector(UIScene::previousCallback));
        
        UIButton* middle_button = dynamic_cast<UIButton*>(m_pUiLayer->getWidgetByName("middle_Button"));
        middle_button->addTouchEventListener(this, toucheventselector(UIScene::restartCallback));
        
        UIButton* right_button = dynamic_cast<UIButton*>(m_pUiLayer->getWidgetByName("right_Button"));
        right_button->addTouchEventListener(this, toucheventselector(UIScene::nextCallback));
        
        /*
        for (int i = 0; i < 4; ++i)
        {
            CCNode* node = CCNode::create();
            node->setPosition(VisibleRect::center());
            CCNode* sprite = CCSprite::create();
            dynamic_cast<CCSprite*>(sprite)->initWithFile("Hello.png");
//            dynamic_cast<CCSprite*>(sprite)->initWithFile("cocosgui/UITest/background.png");
//            sprite->setPosition(VisibleRect::center());
            node->addChild(sprite);
            m_pUiLayer->addChild(node);
        }
         */
        
        return true;
    }
    return false;
}

void UIScene::toCocosGUITestScene(CCObject* sender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
        {
            UISceneManager::purgeUISceneManager();
            ActionManager::purge();
            
            CocosGUITestScene* pScene = new CocosGUITestScene();
            pScene->runThisTest();
            pScene->release();
        }
            break;
            
        default:
            break;
    }
  
}

void UIScene::previousCallback(CCObject* sender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
            CCDirector::sharedDirector()->replaceScene(UISceneManager::sharedUISceneManager()->previousUIScene());
            break;
            
        default:
            break;
    }
}

void UIScene::restartCallback(CCObject* sender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
            CCDirector::sharedDirector()->replaceScene(UISceneManager::sharedUISceneManager()->currentUIScene());
            break;
            
        default:
            break;
    }
}

void UIScene::nextCallback(CCObject* sender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
            CCDirector::sharedDirector()->replaceScene(UISceneManager::sharedUISceneManager()->nextUIScene());
            break;
            
        default:
            break;
    }
}
