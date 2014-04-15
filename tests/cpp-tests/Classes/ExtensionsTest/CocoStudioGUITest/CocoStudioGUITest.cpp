

#include "CocoStudioGUITest.h"
#include "../../ExtensionsTest/ExtensionsTest.h"
#include "CocosGUIScene.h"
#include "GUIEditorTest.h"
#include "CustomGUIScene.h"


enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

static struct
{
	const char *name;
	std::function<void(Ref* sender)> callback;
}
g_guisTests[] =
{
	{
        "GUI Dynamic Create Test",
        [](Ref* sender)
        {
            CocosGUITestScene *pScene = new CocosGUITestScene();
			pScene->runThisTest();
			pScene->release();
        }
	},
    {
        "GUI Editor Test",
        [](Ref* sender)
        {
            GUIEditorTestScene* pScene = new GUIEditorTestScene();
            pScene->runThisTest();
            pScene->release();
        }
	},
    {
        "Custom GUI Test",
        [](Ref* sender)
        {
            CustomGUITestScene* pScene = new CustomGUITestScene();
            pScene->runThisTest();
            pScene->release();
        }
	},
};

static const int g_maxTests = sizeof(g_guisTests) / sizeof(g_guisTests[0]);

////////////////////////////////////////////////////////
//
// CocoStudioGUIMainLayer
//
////////////////////////////////////////////////////////

static Vector2 _curPos = Vector2::ZERO;

void CocoStudioGUIMainLayer::onEnter()
{
    using namespace ui;
    
    CCLayer::onEnter();
    
    Size s = Director::getInstance()->getWinSize();
    
    _itemMenu = CCMenu::create();
    _itemMenu->setPosition(Vector2::ZERO);
    CCMenuItemFont::setFontName("fonts/arial.ttf");
    CCMenuItemFont::setFontSize(24);
    for (int i = 0; i < g_maxTests; ++i)
    {
        auto pItem = MenuItemFont::create(g_guisTests[i].name, g_guisTests[i].callback);
        pItem->setPosition(Vector2(s.width / 2, s.height / 4 * 3 - (i + 1) * LINE_SPACE));
        _itemMenu->addChild(pItem, kItemTagBasic + i);
    }
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(CocoStudioGUIMainLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(CocoStudioGUIMainLayer::onTouchesMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    addChild(_itemMenu);
}

void CocoStudioGUIMainLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    auto touch = static_cast<Touch*>(touches[0]);
    
    _beginPos = touch->getLocation();
}

/*
void CocoStudioGUIMainLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    auto touch = static_cast<Touch*>(touches[0]);
    
    auto touchLocation = touch->getLocation();
    float nMoveY = touchLocation.y - _beginPos.y;
    
    auto curPos  = _itemMenu->getPosition();
    auto nextPos = Vector2(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Vector2::ZERO);
        return;
    }
    
    float y = (g_maxTests + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height;
    if (nextPos.y > y)
    {
        _itemMenu->setPosition(Vector2(0, y));
        return;
    }
    
    _itemMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    _curPos   = nextPos;
}
 */

////////////////////////////////////////////////////////
//
// CocoStudioGUITestScene
//
////////////////////////////////////////////////////////

void CocoStudioGUITestScene::onEnter()
{
    CCScene::onEnter();
    
    auto label = Label::createWithTTF("Back", "fonts/arial.ttf", 20);
    //#endif
    MenuItemLabel* pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(CocoStudioGUITestScene::BackCallback, this));
    
    Menu* pMenu = Menu::create(pMenuItem, NULL);
    
    pMenu->setPosition( Vector2::ZERO );
    pMenuItem->setPosition( Vector2( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CocoStudioGUITestScene::runThisTest()
{
    Layer* pLayer = new CocoStudioGUIMainLayer();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::getInstance()->replaceScene(this);
}

void CocoStudioGUITestScene::BackCallback(Ref* pSender)
{
    ExtensionsTestScene* pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}