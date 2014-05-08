
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
        /*
        cc_timeval startval, endval;
        double del = 0;
        
        CCTime::gettimeofdayCocos2d(&startval, NULL);
         */
        
        
        
        m_pUiLayer = UILayer::create();
        addChild(m_pUiLayer);
        
        m_pWidget = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UITest/UITest.json"));
        m_pUiLayer->addWidget(m_pWidget);

        
        
        
        /*
        CCTime::gettimeofdayCocos2d(&endval, NULL);
        del = CCTime::timersubCocos2d(&startval,&endval);
        CCLOG("first %f",del);
         */
        
        
        
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        CCSize rootSize = m_pWidget->getSize();
        m_pUiLayer->setPosition(CCPoint((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        m_pSceneTitle = static_cast<ui::Label*>(UIHelper::seekWidgetByName(m_pWidget, "UItest"));
        
        ui::Label* back_label = static_cast<ui::Label*>(UIHelper::seekWidgetByName(m_pWidget, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene::toCocosGUITestScene));
        
        Button* left_button = static_cast<Button*>(UIHelper::seekWidgetByName(m_pWidget, "left_Button"));
        left_button->addTouchEventListener(this, toucheventselector(UIScene::previousCallback));
        
        Button* middle_button = static_cast<Button*>(UIHelper::seekWidgetByName(m_pWidget, "middle_Button"));
        middle_button->addTouchEventListener(this, toucheventselector(UIScene::restartCallback));
        
        Button* right_button = static_cast<Button*>(UIHelper::seekWidgetByName(m_pWidget, "right_Button"));
        right_button->addTouchEventListener(this, toucheventselector(UIScene::nextCallback));
        

        
        
        
        
        
        /*
        CCTime::gettimeofdayCocos2d(&startval, NULL);
        for (int i = 0; i < 10; i++)
        {
            m_pWidget->clone();
        }
        CCTime::gettimeofdayCocos2d(&endval, NULL);
        del = CCTime::timersubCocos2d(&startval,&endval);
        CCLOG("clone %f",del);
        CCTime::gettimeofdayCocos2d(&startval, NULL);
        for (int i = 0; i < 10; i++)
        {
            GUIReader::shareReader()->widgetFromJsonFile("cocosui/UITest/UITest.json");
        }
        CCTime::gettimeofdayCocos2d(&endval, NULL);
        del = CCTime::timersubCocos2d(&startval,&endval);
        CCLOG("create %f",del);
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
