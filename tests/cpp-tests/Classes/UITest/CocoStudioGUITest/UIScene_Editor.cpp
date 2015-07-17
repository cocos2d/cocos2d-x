#include "UIScene_Editor.h"
#include "GUIEditorTest.h"
#include "ui/CocosGUI.h"
#include "UISceneManager_Editor.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIScene_Editor::UIScene_Editor()
:  _touchGroup(nullptr)
, _layout(nullptr)
, _sceneTitle(nullptr)
{
    
}

UIScene_Editor::~UIScene_Editor()
{
    
}

bool UIScene_Editor::init()
{
    if (TestCase::init())
    {
        _touchGroup = Layer::create();
        addChild(_touchGroup);

        return true;
    }
    
    return false;
}

void UIScene_Editor::onEnter()
{
    TestCase::onEnter();

    if (_sceneTitle)
    {
        _sceneTitle->setString(getTestCaseName());
    }
}

void UIScene_Editor::onExit()
{
    cocostudio::destroyCocosStudio();

    TestCase::onExit();
}

void UIScene_Editor::configureGUIScene()
{
    if (_touchGroup)
    {
        Size screenSize = Director::getInstance()->getWinSize();
        Size rootSize = _layout->getContentSize();
        _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
            (screenSize.height - rootSize.height) / 2));
    }

    if (_layout)
    {
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
    }
}