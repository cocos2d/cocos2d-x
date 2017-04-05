#include "extensions/cocos-ext.h"
#include "UIScene.h"
#include "UISceneManager.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "CocosGUIScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIScene::UIScene()
: _uiLayer(nullptr)
, _sceneTitle(nullptr)
{
    
}

UIScene::~UIScene()
{
	
}

bool UIScene::init()
{
    if (TestCase::init())
    {
        _uiLayer = Layer::create();
        addChild(_uiLayer);
        
        _widget = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UITest/UITest.json"));
        _uiLayer->addChild(_widget);
        
        Size screenSize = Director::getInstance()->getWinSize();
        Size rootSize = _widget->getContentSize();
        _uiLayer->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                    (screenSize.height - rootSize.height) / 2));
        
        // disable these widgets because they are conflict with menu items created in `TestCase`
        
        auto restartButton = Helper::seekWidgetByName(_widget, "middle_Button");
        restartButton->setVisible(false);
        restartButton->setEnabled(false);
        
        auto leftButton = Helper::seekWidgetByName(_widget, "left_Button");
        leftButton->setVisible(false);
        leftButton->setEnabled(false);
        
        auto rightButton = Helper::seekWidgetByName(_widget, "right_Button");
        rightButton->setVisible(false);
        rightButton->setEnabled(false);

        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));

        _sceneTitle = dynamic_cast<Text*>(root->getChildByName("UItest"));
        return true;
    }
    return false;
}

void UIScene::onEnter()
{
    TestCase::onEnter();

    if (_sceneTitle)
    {
        _sceneTitle->setString(getTestCaseName());
    }
}
