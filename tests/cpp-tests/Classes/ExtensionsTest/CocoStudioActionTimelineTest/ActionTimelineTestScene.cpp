#include "ActionTimelineTestScene.h"
#include "../../testResource.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"


using namespace cocos2d;
using namespace cocostudio;

Layer *NextAnimationTest();
Layer *BackAnimationTest();
Layer *RestartAnimationTest();

static int s_nActionIdx = -1;


Layer *CreateAnimationLayer(int index)
{
    Layer *pLayer = nullptr;
    switch(index)
    {
    case TEST_ANIMATIONELEMENT:
        pLayer = new (std::nothrow) TestActionTimeline();
        break;
    case TEST_CHANGE_PLAY_SECTION:
        pLayer = new (std::nothrow) TestChangePlaySection();
        break;
    case TEST_TIMELINE_FRAME_EVENT:
        pLayer = new (std::nothrow) TestTimelineFrameEvent();
        break;
    case TEST_TIMELINE_PERFORMACE:
        pLayer = new (std::nothrow) TestTimelinePerformance();
        break;
    default:
        break;
    }

    return pLayer;
}


Layer *NextAnimationTest()
{
    ++s_nActionIdx;
    s_nActionIdx = s_nActionIdx % TEST_ANIMATION_LAYER_COUNT;

    Layer *pLayer = CreateAnimationLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer *BackAnimationTest()
{
    --s_nActionIdx;
    if( s_nActionIdx < 0 )
        s_nActionIdx += TEST_ANIMATION_LAYER_COUNT;

    Layer *pLayer = CreateAnimationLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer *RestartAnimationTest()
{
    Layer *pLayer = CreateAnimationLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}


ActionTimelineTestScene::ActionTimelineTestScene(bool bPortrait)
{
    TestScene::init();

    Sprite *bg = Sprite::create("armature/bg.jpg");
    bg->setPosition(VisibleRect::center());

    float scaleX = VisibleRect::getVisibleRect().size.width / bg->getContentSize().width;
    float scaleY = VisibleRect::getVisibleRect().size.height / bg->getContentSize().height;

    bg->setScaleX(scaleX);
    bg->setScaleY(scaleY);

    addChild(bg);
}

void ActionTimelineTestScene::runThisTest()
{
    s_nActionIdx = -1;
    addChild(NextAnimationTest());

    Director::getInstance()->replaceScene(this);
}

void ActionTimelineTestScene::MainMenuCallback(Ref *pSender)
{
    //TestScene::MainMenuCallback(pSender);

    removeAllChildren();
}



void ActionTimelineTestLayer::onEnter()
{

    Layer::onEnter();

    // add title and subtitle
    std::string str = title();
    const char *title = str.c_str();
    auto label = Label::createWithSystemFont(title, "Arial", 18);
    label->setColor(Color3B(0, 0, 0));
    addChild(label, 1, 10000);
    label->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() )
    {
        auto l = Label::createWithSystemFont(strSubtitle.c_str(), "Arial", 18);
        l->setColor(Color3B(0, 0, 0));
        addChild(l, 1, 10001);
        l->setPosition(VisibleRect::center().x, VisibleRect::top().y - 60);
    }

    // add menu
    backItem = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(ActionTimelineTestLayer::backCallback, this) );
    restartItem = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(ActionTimelineTestLayer::restartCallback, this) );
    nextItem = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(ActionTimelineTestLayer::nextCallback, this) );

    Menu *menu = Menu::create(backItem, restartItem, nextItem, nullptr);

    menu->setPosition(Point::ZERO);
    backItem->setPosition(VisibleRect::center().x - restartItem->getContentSize().width * 2, VisibleRect::bottom().y + restartItem->getContentSize().height / 2);
    restartItem->setPosition(VisibleRect::center().x, VisibleRect::bottom().y + restartItem->getContentSize().height / 2);
    nextItem->setPosition(VisibleRect::center().x + restartItem->getContentSize().width * 2, VisibleRect::bottom().y + restartItem->getContentSize().height / 2);

    addChild(menu, 100);

    setGLProgram(ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

}
void ActionTimelineTestLayer::onExit()
{
    removeAllChildren();

    backItem = restartItem = nextItem = nullptr;

    ActionTimelineCache::getInstance()->purge();
    CSLoader::getInstance()->purge();

    Layer::onExit();
}

std::string ActionTimelineTestLayer::title() const
{
    return "Armature Test Bed";
}
std::string ActionTimelineTestLayer::subtitle() const
{
    return "";
}

void ActionTimelineTestLayer::restartCallback(Ref *pSender)
{
    Scene *s = new (std::nothrow) ActionTimelineTestScene();
    s->addChild( RestartAnimationTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ActionTimelineTestLayer::nextCallback(Ref *pSender)
{
    Scene *s = new (std::nothrow) ActionTimelineTestScene();
    s->addChild( NextAnimationTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}
void ActionTimelineTestLayer::backCallback(Ref *pSender)
{
    Scene *s = new (std::nothrow) ActionTimelineTestScene();
    s->addChild( BackAnimationTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}



// TestActionTimeline
void TestActionTimeline::onEnter()
{
    ActionTimelineTestLayer::onEnter();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("armature/Cowboy0.plist", "armature/Cowboy0.png");

    Node* node = CSLoader::createNode("ActionTimeline/boy_1.csb");
    ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/boy_1.csb");

    node->runAction(action);
    action->gotoFrameAndPlay(0, 60, true);

    node->setScale(0.2f);
    node->setPosition(150,100);

    addChild(node);
}

std::string TestActionTimeline::title() const
{
    return "Test ActionTimeline";
}



// TestActionTimeline
void TestChangePlaySection::onEnter()
{
    ActionTimelineTestLayer::onEnter();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("armature/Cowboy0.plist", "armature/Cowboy0.png");

    Node* node = CSLoader::createNode("ActionTimeline/boy_1.csb");
    action = CSLoader::createTimeline("ActionTimeline/boy_1.csb");

    node->runAction(action);
    action->gotoFrameAndPlay(70, action->getDuration(), true);

    node->setScale(0.2f);
    node->setPosition(150,100);

    // add touch event listener
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(TestChangePlaySection::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    addChild(node);
}

std::string TestChangePlaySection::title() const
{
    return "Test Change Play Section";
}

void TestChangePlaySection::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    if(action->getStartFrame() == 0)
        action->gotoFrameAndPlay(70, action->getDuration(), true);
    else
        action->gotoFrameAndPlay(0, 60, true);
}

// TestFrameEvent
void TestTimelineFrameEvent::onEnter()
{
    ActionTimelineTestLayer::onEnter();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("armature/Cowboy0.plist", "armature/Cowboy0.png");

    Node* node = CSLoader::createNode("ActionTimeline/boy_1.csb");
    ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/boy_1.csb");

    node->runAction(action);
    action->gotoFrameAndPlay(0, 60, true);

    node->setScale(0.2f);
    node->setPosition(150,100);
    addChild(node);

    action->setFrameEventCallFunc(CC_CALLBACK_1(TestTimelineFrameEvent::onFrameEvent, this));
}

std::string TestTimelineFrameEvent::title() const
{
    return "Test Frame Event";
}

void TestTimelineFrameEvent::onFrameEvent(Frame* frame)
{
    EventFrame* evnt = dynamic_cast<EventFrame*>(frame);
    if(!evnt)
        return;

    std::string str = evnt->getEvent();

    if (str == "changeColor")
    {
        evnt->getNode()->setColor(Color3B(0,0,0));
    }
    else if(str == "endChangeColor")
    {
        evnt->getNode()->setColor(Color3B(255,255,255));
    }
}


// TestTimelinePerformance
void TestTimelinePerformance::onEnter()
{
    ActionTimelineTestLayer::onEnter();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("armature/Cowboy0.plist", "armature/Cowboy0.png");

    for (int i = 0; i< 100; i++)
    {
        Node* node = CSLoader::createNode("ActionTimeline/boy_1.csb");
        ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/boy_1.csb");

        node->runAction(action);
        action->gotoFrameAndPlay(70, action->getDuration(), true);

        node->setScale(0.1f);
        node->setPosition(i*2,100);
        addChild(node);
    }
}

std::string TestTimelinePerformance::title() const
{
    return "Test ActionTimeline performance";
}

