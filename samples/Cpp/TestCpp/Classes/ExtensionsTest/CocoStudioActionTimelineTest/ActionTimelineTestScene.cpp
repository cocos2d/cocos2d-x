#include "ActionTimelineTestScene.h"
#include "../../testResource.h"


using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocostudio::timeline;

CCLayer *NextTimelineTest();
CCLayer *BackTimelineTest();
CCLayer *RestartTimelineTest();

static int s_nActionIdx = -1;


CCLayer *CreateTimelineLayer(int index)
{
    CCLayer *pLayer = NULL;
    switch(index)
    {
    case TEST_ACTION_TIMELINE:
        pLayer = new TestActionTimeline();
        break;
    case TEST_CHANGE_PLAY_SECTION:
        pLayer = new TestChangePlaySection();
        break;
    case TEST_TIMELINE_FRAME_EVENT:
        pLayer = new TestTimelineFrameEvent();
        break;
    case TEST_TIMELINE_PERFORMACE:
        pLayer = new TestTimelinePerformance();
        break;
    default:
        break;
    }

    return pLayer;
}


CCLayer *NextTimelineTest()
{
    ++s_nActionIdx;
    s_nActionIdx = s_nActionIdx % TEST_ACTION_LAYER_COUNT;

    CCLayer *pLayer = CreateTimelineLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer *BackTimelineTest()
{
    --s_nActionIdx;
    if( s_nActionIdx < 0 )
        s_nActionIdx += TEST_ACTION_LAYER_COUNT;

    CCLayer *pLayer = CreateTimelineLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer *RestartTimelineTest()
{
    CCLayer *pLayer = CreateTimelineLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}


TimelineTestScene::TimelineTestScene(bool bPortrait)
{
    TestScene::init();

    CCSprite *bg = CCSprite::create("armature/bg.jpg");
    bg->setPosition(VisibleRect::center());

    float scaleX = VisibleRect::getVisibleRect().size.width / bg->getContentSize().width;
    float scaleY = VisibleRect::getVisibleRect().size.height / bg->getContentSize().height;

    bg->setScaleX(scaleX);
    bg->setScaleY(scaleY);

    addChild(bg);
}
void TimelineTestScene::runThisTest()
{
    s_nActionIdx = -1;
    addChild(NextTimelineTest());

    CCDirector::sharedDirector()->replaceScene(this);
}
void TimelineTestScene::MainMenuCallback(CCObject *pSender)
{
    TestScene::MainMenuCallback(pSender);

    removeAllChildren();
    CCArmatureDataManager::purge();
}



void ActionTimelineTestLayer::onEnter()
{
    CCLayer::onEnter();

    // add title and subtitle
    std::string str = title();
    const char *pTitle = str.c_str();
    CCLabelTTF *label = CCLabelTTF::create(pTitle, "Arial", 18);
    label->setColor(ccc3(0, 0, 0));
    addChild(label, 1, 10000);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() )
    {
        CCLabelTTF *l = CCLabelTTF::create(strSubtitle.c_str(), "Arial", 18);
        l->setColor(ccc3(0, 0, 0));
        addChild(l, 1, 10001);
        l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 60) );
    }

    // add menu
    backItem = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(ActionTimelineTestLayer::backCallback) );
    restartItem = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(ActionTimelineTestLayer::restartCallback) );
    nextItem = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(ActionTimelineTestLayer::nextCallback) );

    CCMenu *menu = CCMenu::create(backItem, restartItem, nextItem, NULL);

    menu->setPosition(CCPointZero);
    backItem->setPosition(ccp(VisibleRect::center().x - restartItem->getContentSize().width * 2, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    restartItem->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    nextItem->setPosition(ccp(VisibleRect::center().x + restartItem->getContentSize().width * 2, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));

    addChild(menu, 100);

    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));

}
void ActionTimelineTestLayer::onExit()
{
    removeAllChildren();

    backItem = restartItem = nextItem = NULL;
}

std::string ActionTimelineTestLayer::title()
{
    return "CSArmature Test Bed";
}
std::string ActionTimelineTestLayer::subtitle()
{
    return "";
}

void ActionTimelineTestLayer::restartCallback(CCObject *pSender)
{
    CCScene *s = new TimelineTestScene();
    s->addChild( RestartTimelineTest() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}
void ActionTimelineTestLayer::nextCallback(CCObject *pSender)
{
    CCScene *s = new TimelineTestScene();
    s->addChild( NextTimelineTest() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}
void ActionTimelineTestLayer::backCallback(CCObject *pSender)
{
    CCScene *s = new TimelineTestScene();
    s->addChild( BackTimelineTest() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}
void ActionTimelineTestLayer::draw()
{
    CCLayer::draw();
}

// TestActionTimeline
void TestActionTimeline::onEnter()
{
    ActionTimelineTestLayer::onEnter();

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("armature/Cowboy0.plist", "armature/Cowboy0.png");

    CCNode* node = NodeReader::getInstance()->createNode("ActionTimeline/boy_1.ExportJson");
    ActionTimeline* action = ActionTimelineCache::getInstance()->createAction("ActionTimeline/boy_1.ExportJson");

    node->runAction(action);
    action->gotoFrameAndPlay(0, 60, true);

    node->setScale(0.4f);
    node->setPosition(0,0);

    addChild(node);
}

std::string TestActionTimeline::title()
{
    return "Test ActionTimeline";
}


// TestChangePlaySection
void TestChangePlaySection::onEnter()
{
    ActionTimelineTestLayer::onEnter();
    setTouchEnabled(true);

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("armature/Cowboy0.plist", "armature/Cowboy0.png");

    CCNode* node = NodeReader::getInstance()->createNode("ActionTimeline/boy_1.ExportJson");
    action = ActionTimelineCache::getInstance()->createAction("ActionTimeline/boy_1.ExportJson");

    node->runAction(action);
    action->gotoFrameAndPlay(70, action->getDuration(), true);

    node->setScale(0.2f);
    node->setPosition(150,100);

    addChild(node);
}

void TestChangePlaySection::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    ActionTimelineTestLayer::onExit();
}

std::string TestChangePlaySection::title()
{
    return "Test Change Play Section";
}

bool TestChangePlaySection::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if(action->getStartFrame() == 0)
        action->gotoFrameAndPlay(70, action->getDuration(), true);
    else
        action->gotoFrameAndPlay(0, 60, true);

    return false;
}
void TestChangePlaySection::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN + 1, true);
}


// TestFrameEvent
void TestTimelineFrameEvent::onEnter()
{
    ActionTimelineTestLayer::onEnter();

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("armature/Cowboy0.plist", "armature/Cowboy0.png");

    CCNode* node = NodeReader::getInstance()->createNode("ActionTimeline/boy_1.ExportJson");
    ActionTimeline* action = ActionTimelineCache::getInstance()->createAction("ActionTimeline/boy_1.ExportJson");

    node->runAction(action);
    action->gotoFrameAndPlay(0, 60, true);

    node->setScale(0.2f);
    node->setPosition(150,100);
    addChild(node);

    action->setFrameEventCallFunc(this, timelineFrameEvent_selector(TestTimelineFrameEvent::onFrameEvent));
}

std::string TestTimelineFrameEvent::title()
{
    return "Test Frame Event";
}

void TestTimelineFrameEvent::onFrameEvent(Frame* frame)
{
    EventFrame* evnt = dynamic_cast<EventFrame*>(frame);
    if(!evnt)
        return;

    std::string str = evnt->getEvent();
    CCSprite* sprite = dynamic_cast<CCSprite*>(evnt->getNode());

    if (sprite && str == "changeColor")
    {
        sprite->setColor(ccc3(0,0,0));
    }
    else if(sprite && str == "endChangeColor")
    {
        sprite->setColor(ccc3(255,255,255));
    }
}



// TestTimelinePerformance
void TestTimelinePerformance::onEnter()
{
    ActionTimelineTestLayer::onEnter();

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("armature/Cowboy0.plist", "armature/Cowboy0.png");

    for (int i = 0; i< 100; i++)
    {
        CCNode* node = NodeReader::getInstance()->createNode("ActionTimeline/boy_1.ExportJson");
        ActionTimeline* action = ActionTimelineCache::getInstance()->createAction("ActionTimeline/boy_1.ExportJson");

        node->runAction(action);
        action->gotoFrameAndPlay(70, action->getDuration(), true);

        node->setScale(0.1f);
        node->setPosition(i*2,100);
        addChild(node);
    }
}

std::string TestTimelinePerformance::title() 
{
    return "Test ActionTimeline performance";
}
