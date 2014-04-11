/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "controller.h"
#include "testResource.h"
#include "tests.h"

#define LINE_SPACE          40

static CCPoint s_tCurPos = CCPointZero;

static TestScene* CreateTestScene(int nIdx)
{
    CCDirector::sharedDirector()->purgeCachedData();

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
        pScene = new ActionsEaseTestScene(); break;
    case TEST_MOTION_STREAK:
        pScene = new MotionStreakTestScene(); break;
    case TEST_DRAW_PRIMITIVES:
        pScene = new DrawPrimitivesTestScene(); break;
    case TEST_COCOSNODE:
        pScene = new CocosNodeTestScene(); break;
    case TEST_TOUCHES:
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
    case TEST_LABEL:
        pScene = new AtlasTestScene(); break;
    case TEST_TEXT_INPUT:
        pScene = new TextInputTestScene(); break;
    case TEST_SPRITE:
        pScene = new SpriteTestScene(); break;
    case TEST_SCHEDULER:
        pScene = new SchedulerTestScene(); break;
    case TEST_RENDERTEXTURE:
        pScene = new RenderTextureScene(); break;
    case TEST_TEXTURE2D:
        pScene = new TextureTestScene(); break;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
    case TEST_CHIPMUNK:
        pScene = new ChipmunkAccelTouchTestScene(); break;
#endif
    case TEST_BOX2D:
        pScene = new Box2DTestScene(); break;
    case TEST_BOX2DBED:
        pScene = new Box2dTestBedScene(); break;
    case TEST_EFFECT_ADVANCE:
        pScene = new EffectAdvanceScene(); break;
    case TEST_ACCELEROMRTER:
        pScene = new AccelerometerTestScene(); break;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_BADA)
    case TEST_KEYPAD:
        pScene = new KeypadTestScene(); break;
#endif
    case TEST_COCOSDENSHION:
        pScene = new CocosDenshionTestScene(); break;
    case TEST_PERFORMANCE:
        pScene = new PerformanceTestScene(); break;
    case TEST_ZWOPTEX:
        pScene = new ZwoptexTestScene(); break;
// bada don't support libcurl
#if (CC_TARGET_PLATFORM != CC_PLATFORM_BADA && CC_TARGET_PLATFORM != CC_PLATFORM_NACL && CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE && CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN && CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    case TEST_CURL:
        pScene = new CurlTestScene(); break;
#endif
    case TEST_USERDEFAULT:
        pScene = new UserDefaultTestScene(); break;
    case TEST_BUGS:
        pScene = new BugsTestScene(); break;
    case TEST_FONTS:
        pScene = new FontTestScene(); break;
    case TEST_CURRENT_LANGUAGE:
        pScene = new CurrentLanguageTestScene(); break;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
    case TEST_TEXTURECACHE: pScene = new TextureCacheTestScene(); break;
#endif
    case TEST_EXTENSIONS:
        pScene = new ExtensionsTestScene();
        break;
    case TEST_SHADER:
       pScene = new ShaderTestScene();
    break;

    case TEST_MUTITOUCH:
        pScene = new MutiTouchTestScene();
        break;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
    case TEST_CLIPPINGNODE:
        pScene = new ClippingNodeTestScene();
        break;
#endif
    case TEST_FILEUTILS:
        pScene = new FileUtilsTestScene();
        break;
    case TEST_SPINE:
        pScene = new SpineTestScene();
        break;
    case TEST_TEXTUREPACKER_ENCRYPTION:
        pScene = new TextureAtlasEncryptionTestScene();
        break;
    case TEST_DATAVISTOR:
        pScene = new DataVisitorTestScene();
        break;
	case TEST_CONFIGURATION:
		pScene = new ConfigurationTestScene();
		break;
	default:
        break;
    }

    return pScene;
}

TestController::TestController()
: m_tBeginPos(CCPointZero)
{
    // add close menu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathClose, s_pPathClose, this, menu_selector(TestController::closeCallback) );
    CCMenu* pMenu =CCMenu::create(pCloseItem, NULL);

    pMenu->setPosition( CCPointZero );
    pCloseItem->setPosition(ccp( VisibleRect::right().x - 30, VisibleRect::top().y - 30));

    // add menu items for tests
    m_pItemMenu = CCMenu::create();
    for (int i = 0; i < TESTS_COUNT; ++i)
    {
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//         CCLabelBMFont* label = CCLabelBMFont::create(g_aTestNames[i].c_str(),  "fonts/arial16.fnt");
// #else
        CCLabelTTF* label = CCLabelTTF::create(g_aTestNames[i].c_str(), "Arial", 24);
// #endif        
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(TestController::menuCallback));

        m_pItemMenu->addChild(pMenuItem, i + 10000);
        pMenuItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - (i + 1) * LINE_SPACE) ));
    }

    m_pItemMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, (TESTS_COUNT + 1) * (LINE_SPACE)));
    m_pItemMenu->setPosition(s_tCurPos);
    addChild(m_pItemMenu);

    setTouchEnabled(true);

    addChild(pMenu, 1);

#if (MSC_VER < 1800) && defined(DEBUG) && (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//#define CC_PLATFORM_WINRT_SAVE_SHADERS
#if defined(CC_PLATFORM_WINRT_SAVE_SHADERS)
    ShaderTestDemo::precompileShaders();
    CCPrecompiledShaders::sharedPrecompiledShaders()->savePrecompiledShaders();
#endif
#endif

}

TestController::~TestController()
{
}

void TestController::menuCallback(CCObject * pSender)
{
    // get the userdata, it's the index of the menu item clicked
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
    int nIdx = pMenuItem->getZOrder() - 10000;

    // create the test scene and run it
    TestScene* pScene = CreateTestScene(nIdx);
    if (pScene)
    {
        pScene->runThisTest();
        pScene->release();
    }
}

void TestController::closeCallback(CCObject * pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");

	#else
		CCDirector::sharedDirector()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
#endif
}

void TestController::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    m_tBeginPos = touch->getLocation();    
}

void TestController::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    CCPoint touchLocation = touch->getLocation();    
    float nMoveY = touchLocation.y - m_tBeginPos.y;

    CCPoint curPos  = m_pItemMenu->getPosition();
    CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);

    if (nextPos.y < 0.0f)
    {
        m_pItemMenu->setPosition(CCPointZero);
        return;
    }

    if (nextPos.y > ((TESTS_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        m_pItemMenu->setPosition(ccp(0, ((TESTS_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }

    m_pItemMenu->setPosition(nextPos);
    m_tBeginPos = touchLocation;
    s_tCurPos   = nextPos;
}
