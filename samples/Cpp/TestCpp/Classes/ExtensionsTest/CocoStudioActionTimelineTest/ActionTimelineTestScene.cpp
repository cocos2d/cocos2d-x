#include "ActionTimelineTestScene.h"
#include "../../testResource.h"

using namespace cocos2d;
using namespace cocos2d::extension;

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



void TimelineTestLayer::onEnter()
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
    backItem = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(TimelineTestLayer::backCallback) );
    restartItem = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(TimelineTestLayer::restartCallback) );
    nextItem = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(TimelineTestLayer::nextCallback) );

    CCMenu *menu = CCMenu::create(backItem, restartItem, nextItem, NULL);

    menu->setPosition(CCPointZero);
    backItem->setPosition(ccp(VisibleRect::center().x - restartItem->getContentSize().width * 2, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    restartItem->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    nextItem->setPosition(ccp(VisibleRect::center().x + restartItem->getContentSize().width * 2, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));

    addChild(menu, 100);

    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));

}
void TimelineTestLayer::onExit()
{
    removeAllChildren();

    backItem = restartItem = nextItem = NULL;
}

std::string TimelineTestLayer::title()
{
    return "CSArmature Test Bed";
}
std::string TimelineTestLayer::subtitle()
{
    return "";
}

void TimelineTestLayer::restartCallback(CCObject *pSender)
{
    CCScene *s = new TimelineTestScene();
    s->addChild( RestartTimelineTest() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}
void TimelineTestLayer::nextCallback(CCObject *pSender)
{
    CCScene *s = new TimelineTestScene();
    s->addChild( NextTimelineTest() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}
void TimelineTestLayer::backCallback(CCObject *pSender)
{
    CCScene *s = new TimelineTestScene();
    s->addChild( BackTimelineTest() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}
void TimelineTestLayer::draw()
{
    CCLayer::draw();
}


void TestActionTimeline::onEnter()
{
    TimelineTestLayer::onEnter();

}

std::string TestActionTimeline::title()
{
    return "Test Asynchronous Loading";
}
