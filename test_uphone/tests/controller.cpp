#include "tests.h"
#include "controller.h"

#define LINE_SPACE          30

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
    default:
        break;
    }

    return pScene;
}

TestController::TestController()
{
    // add close menu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
                                                        "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/close.png",
                                                        "/NEWPLUS/TDA_DATA/Data/cocos2d_tests/Images/close.png",
                                                        this, menu_selector(TestController::closeCallback) );
    CCMenu* pMenu =CCMenu::menuWithItems(pCloseItem, NULL);

    CGSize s = CCDirector::getSharedDirector()->getWinSize();
    pMenu->setPosition( CGPointZero );
    pCloseItem->setPosition(CGPointMake( s.width - 30, s.height - 30));

    // add menu items for tests
    for (int i = 0; i < ITEM_EVERYPAGE; ++i)
    {
        CCLabel* label = CCLabel::labelWithString("For Test", "Arial", 22);
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
    CCMenuItem* pMenuItem = dynamic_cast<CCMenuItem *> (pSender);
    void * pUserData = pMenuItem->getUserData();
    int  * nIdx = (int *) pUserData;

    // create the test scene and run it
    TestScene* pScene = CreateTestScene(s_nPageIndex * ITEM_EVERYPAGE + (*nIdx));
    if (pScene)
    {
        pScene->runThisTest();
        pScene->autorelease();
    }
}

void TestController::closeCallback(NSObject * pSender)
{
    CCDirector::getSharedDirector()->end();
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
            m_pMenuItems[i]->setString(menuText.c_str());
            m_pMenuItems[i]->setIsVisible(true);
        }
    }
}
