#include "tests.h"
#include "controller.h"
#include "testResource.h"

#define LINE_SPACE          40

static int s_nPageIndex = 0;

static TestScene* CreateTestScene(int nIdx)
{
    TestScene* pScene = NULL;

    switch (nIdx)
    {
    case TEST_ACTIONS:
        pScene = new ActionsTestScene(); break;
    case TEST_TRANSITIONS:
        pScene = new TransitionsTestScene(); break;
    case TEST_PROGRESS_ACTIONS:
        pScene = new ProgressActionsTestScene(); break;
    case TEST_EFFECTS:
        pScene = new EffectTestScene(); break;
    case TEST_CLICK_AND_MOVE:
        pScene = new ClickAndMoveTestScene(); break;
    case TEST_ROTATE_WORLD:
        pScene = new RotateWorldTestScene(); break;
    case TEST_PARTICLE:
        pScene = new ParticleTestScene(); break;
    case TEST_EASE_ACTIONS:
        pScene = new EaseActionsTestScene(); break;
    case TEST_MOTION_STREAK:
        pScene = new MotionStreakTestScene(); break;
    case TEST_DRAW_PRIMITIVES:
        pScene = new DrawPrimitivesTestScene(); break;
    case TEST_COCOSNODE:
        pScene = new CocosNodeTestScene(); break;
    case TEST_TOUCHES:
        CCDirector::sharedDirector()->setDeviceOrientation(CCDeviceOrientationPortrait);
        pScene = new PongScene(); break;
    case TEST_MENU:
        pScene = new MenuTestScene(); break;
    case TEST_ACTION_MANAGER:
        pScene = new ActionManagerTestScene(); break;
    case TEST_LAYER:
        pScene = new LayerTestScene(); break;
    case TEST_SCENE:
        pScene = new SceneTestScene(); break;
    case TEST_PARALLAX:
        pScene = new ParallaxTestScene(); break;
    case TEST_TILE_MAP:
        pScene = new TileMapTestScene(); break;
    case TEST_INTERVAL:
        pScene = new IntervalTestScene(); break;
    case TEST_CHIPMUNK:
		CCDirector::sharedDirector()->setDeviceOrientation(CCDeviceOrientationPortrait);
        pScene = new ChipmunkTestScene(); break;
    case TEST_ATLAS:
        pScene = new AtlasTestScene(); break;
    case TEST_SPRITE:
        pScene = new SpriteTestScene(); break;
    case TEST_SCHEDULER:
        pScene = new SchedulerTestScene(); break;
    case TEST_RENDERTEXTURE:
        pScene = new RenderTextureScene(); break;
    case TEST_BOX2D:
        pScene = new Box2DTestScene(); break;
    case TEST_BOX2DBED:
        pScene = new Box2dTestBedScene(); break;
    case TEST_EFFECT_ADVANCE:
        pScene = new EffectAdvanceScene(); break;
    case TEST_HIRES:
        pScene = new HiResTestScene(); break;
#ifndef _WIN32
	case TEST_ACCELEROMRTER:
        pScene = new AccelerometerTestScene(); break;
#endif
    case TEST_KEYPAD:
        pScene = new KeypadTestScene(); break;
    default:
        break;
    }

    return pScene;
}

TestController::TestController()
{
    CCDirector::sharedDirector()->setDeviceOrientation(CCDeviceOrientationLandscapeLeft);

    // add close menu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(s_pPathClose, s_pPathClose, this, menu_selector(TestController::closeCallback) );
    CCMenu* pMenu =CCMenu::menuWithItems(pCloseItem, NULL);

    CGSize s = CCDirector::sharedDirector()->getWinSize();
    pMenu->setPosition( CGPointZero );
    pCloseItem->setPosition(CGPointMake( s.width - 30, s.height - 30));

    // add menu items for tests
    for (int i = 0; i < ITEM_EVERYPAGE; ++i)
    {
        CCLabel* label = CCLabel::labelWithString("For Test", "Arial", 24);
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(TestController::menuCallback));
        pMenu->addChild(pMenuItem, i + 2);
        pMenuItem->setPosition( CGPointMake( s.width / 2, (s.height - (i + 1) * LINE_SPACE) ));

        // record the pointer of the menu item
        m_pMenuItems[i] = pMenuItem;

        // record the value of i as userdata
        int * nIdx = new int;
        *nIdx = i;
        pMenuItem->setUserData((void *) nIdx);
    }

    // update menu items text
    updateItemsText();

    // add menu item to change the page-number
    CCLabel* pPreLabel = CCLabel::labelWithString("PrePage", "Arial", 22);
    CCMenuItemLabel* pPreItem = CCMenuItemLabel::itemWithLabel(pPreLabel, this, menu_selector(TestController::prePageCallback));
    pMenu->addChild(pPreItem, ITEM_EVERYPAGE + 2);
    pPreItem->setPosition(CGPointMake(s.width - 150, 20));

    CCLabel* pNextLabel = CCLabel::labelWithString("NextPage", "Arial", 22);
    CCMenuItemLabel* pNextItem = CCMenuItemLabel::itemWithLabel(pNextLabel, this, menu_selector(TestController::nextPageCallback));
    pMenu->addChild(pNextItem, ITEM_EVERYPAGE + 3);
    pNextItem->setPosition(CGPointMake(s.width - 50, 20));

    addChild(pMenu, 1);
}

TestController::~TestController()
{
    for (int i = 0; i < ITEM_EVERYPAGE; ++i)
    {
        if (m_pMenuItems[i])
        {
            // delete the userdata have recorded
            if (m_pMenuItems[i]->getUserData())
            {
                delete m_pMenuItems[i]->getUserData();
                m_pMenuItems[i]->setUserData(NULL);
            }
        }
    }

    removeAllChildrenWithCleanup(true);
}

void TestController::menuCallback(NSObject * pSender)
{
    // get the userdata, it's the index of the menu item clicked
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
    void * pUserData = pMenuItem->getUserData();
    int  * nIdx = (int *) pUserData;

    // create the test scene and run it
    TestScene* pScene = CreateTestScene(s_nPageIndex * ITEM_EVERYPAGE + (*nIdx));
    if (pScene)
    {
        pScene->runThisTest();
        pScene->release();
    }
}

void TestController::closeCallback(NSObject * pSender)
{
    CCDirector::sharedDirector()->end();
}

void TestController::nextPageCallback(NSObject * pSender)
{
    int nPageCount = TESTS_COUNT / ITEM_EVERYPAGE;
    if (TESTS_COUNT % ITEM_EVERYPAGE != 0)
    {
        nPageCount += 1;
    }

    // compute the current page number
    s_nPageIndex = (s_nPageIndex + 1) % nPageCount;

    // update menu items text
    updateItemsText();
}

void TestController::prePageCallback(NSObject * pSender)
{
    int nPageCount = TESTS_COUNT / ITEM_EVERYPAGE;
    if (TESTS_COUNT % ITEM_EVERYPAGE != 0)
    {
        nPageCount += 1;
    }

    // compute the current page number
    s_nPageIndex -= 1;
    if (s_nPageIndex < 0)
    {
        s_nPageIndex = nPageCount - 1;
    }

    // update menu items text
    updateItemsText();
}

void TestController::updateItemsText()
{
    int nStartIndex = s_nPageIndex * ITEM_EVERYPAGE;

    for (int i = 0; i < ITEM_EVERYPAGE; ++i)
    {
        m_pMenuItems[i]->setIsVisible(false);
        int nIdx = nStartIndex + i;
        if (nIdx < TESTS_COUNT)
        {
            std::string menuText = g_aTestNames[nIdx];

            if (! menuText.empty())
            {
                m_pMenuItems[i]->setString(menuText.c_str());
                m_pMenuItems[i]->setIsVisible(true);
            }
        }
    }
}
