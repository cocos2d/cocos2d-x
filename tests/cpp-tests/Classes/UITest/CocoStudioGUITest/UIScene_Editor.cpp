

#include "UIScene_Editor.h"
#include "GUIEditorTest.h"
#include "ui/CocosGUI.h"
#include "UISceneManager_Editor.h"


UIScene_Editor::UIScene_Editor()
: _sceneTitle(nullptr)
, _touchGroup(nullptr)
, _layout(nullptr)
{
    
}

UIScene_Editor::~UIScene_Editor()
{
    
}

bool UIScene_Editor::init()
{
    if (CCLayer::init())
    {
        _touchGroup = Layer::create();
        addChild(_touchGroup);                
        
        //add switch
        MenuItem* pLoadJsonItem = MenuItemFont::create("Switch to Windows Json Load");
        MenuItem* pLoadBinaryItem = MenuItemFont::create("Switch to Windows Binary Load");
        MenuItem* pLoadJsonItemCrossPlatForm = MenuItemFont::create("Switch to Cross PlatForm Json Load");
        MenuItem* pLoadBinaryItemCrossPlatForm = MenuItemFont::create("Switch to Cross PlatForm Binary Load");
        
        pLoadJsonItem->setTag(1);
        pLoadBinaryItem->setTag(2);
        pLoadJsonItemCrossPlatForm->setTag(3);
        pLoadBinaryItemCrossPlatForm->setTag(4);
        
        
        Vector<MenuItem*> array;;
        array.pushBack(pLoadBinaryItem);
        array.pushBack(pLoadJsonItemCrossPlatForm);
        array.pushBack(pLoadBinaryItemCrossPlatForm);
        array.pushBack(pLoadJsonItem);
        
        MenuItemToggle *pToggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(UIScene_Editor::switchLoadMethod,this), array);
        
        pToggleItem->setTag(1);
        
        MenuItem* selectedItem = pToggleItem->getSelectedItem();
        pToggleItem->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y - selectedItem->getContentSize().height * 3.75f));
        
        Menu* pMenu =Menu::create(pToggleItem, nullptr);
        pMenu->setPosition( Vec2::ZERO );
        
//        addChild(pMenu, 1, 1);

        return true;
    }
    
    return false;
}

void UIScene_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    //subclass should override this method
}

void UIScene_Editor::previousCallback(Ref* sender, Widget::TouchEventType event)
{
    switch (event)
    {
        case Widget::TouchEventType::ENDED:
            CCDirector::getInstance()->replaceScene(UISceneManager_Editor::sharedUISceneManager_Editor()->previousUIScene());
            break;
            
        default:
            break;
    }
}

void UIScene_Editor::nextCallback(Ref* sender, Widget::TouchEventType event)
{
    switch (event)
    {
        case Widget::TouchEventType::ENDED:
            CCDirector::getInstance()->replaceScene(UISceneManager_Editor::sharedUISceneManager_Editor()->nextUIScene());
            break;
            
        default:
            break;
    }
}

void UIScene_Editor::toGUIEditorTestScene(Ref* sender, Widget::TouchEventType event)
{
    switch (event)
    {
        case Widget::TouchEventType::ENDED:
        {
            UISceneManager_Editor::sharedUISceneManager_Editor()->purge();
            
            GUIEditorTestScene* pScene = new (std::nothrow) GUIEditorTestScene();
            pScene->runThisTest();
            pScene->release();
        }
            break;
            
        default:
            break;
    }
}
