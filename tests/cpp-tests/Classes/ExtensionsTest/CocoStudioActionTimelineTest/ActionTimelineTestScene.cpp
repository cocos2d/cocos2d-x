#include "ActionTimelineTestScene.h"
#include "../../testResource.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"
#include "VisibleRect.h"


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
    /*
    case TEST_TIMELINE_FRAME_EVENT:
        pLayer = new (std::nothrow) TestTimelineFrameEvent();
        break;
     */
    case TEST_TIMELINE_PERFORMACE:
        pLayer = new (std::nothrow) TestTimelinePerformance();
        break;
    case TEST_TIMELINEACTION_ANIMATIONLIST:
        pLayer = new (std::nothrow) TestTimelineAnimationList();
        break;
    case TEST_TIMELINEPROJECTNODE:
        pLayer = new (std::nothrow) TestTimelineProjectNode();
        break;
    case TEST_PROJECTNODEFORSIMALATOR:
        pLayer = new (std::nothrow) TestProjectNodeForSimulator;
        break;
    case TEST_NODELOADEDCALLBACK:
        pLayer = new (std::nothrow)TestTimelineNodeLoadedCallback;
        break;
    default:
        CCLOG("NONE OF THIS TEST LAYER");
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
    auto a = BackAnimationTest();
    s->addChild( a);
    Director::getInstance()->replaceScene(s);
    s->release();
}



// TestActionTimeline
void TestActionTimeline::onEnter()
{
    ActionTimelineTestLayer::onEnter();

    Node* node = CSLoader::createNode("ActionTimeline/DemoPlayer.csb");
    ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/DemoPlayer.csb");
    node->runAction(action);
    action->gotoFrameAndPlay(0);
//    ActionTimelineNode* node = CSLoader::createActionTimelineNode("ActionTimeline/DemoPlayer.csb", 0, 40, true);

    node->setScale(0.2f);
    node->setPosition(VisibleRect::center());

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

    Node* node = CSLoader::createNode("ActionTimeline/DemoPlayer.csb");
    action = CSLoader::createTimeline("ActionTimeline/DemoPlayer.csb");
    node->runAction(action);
    action->gotoFrameAndPlay(41);
    /*
    ActionTimelineNode* node = CSLoader::createActionTimelineNode("ActionTimeline/DemoPlayer.csb", 41, 81, true);
    action = node->getActionTimeline();
     */

    node->setScale(0.2f);
    node->setPosition(VisibleRect::center());

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
        action->gotoFrameAndPlay(41, 81, true);
    else
        action->gotoFrameAndPlay(0, 40, true);
}

// TestFrameEvent
void TestTimelineFrameEvent::onEnter()
{
    ActionTimelineTestLayer::onEnter();

    Node* node = CSLoader::createNode("ActionTimeline/DemoPlayer.csb");
    ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/DemoPlayer.csb");
    node->runAction(action);
    action->gotoFrameAndPlay(0);
    /*
    ActionTimelineNode* node = CSLoader::createActionTimelineNode("ActionTimeline/DemoPlayer.csb", 0, 40, true);
    ActionTimeline* action = node->getActionTimeline();
     */

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

    for (int i = 0; i< 100; i++)
    {
        Node* node = CSLoader::createNode("ActionTimeline/DemoPlayer.csb");
        ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/DemoPlayer.csb");
        node->runAction(action);
        action->gotoFrameAndPlay(41);
//        ActionTimelineNode* node = CSLoader::createActionTimelineNode("ActionTimeline/DemoPlayer.csb", 41, 81, true);

        node->setScale(0.1f);
        node->setPosition(i*2,100);
        addChild(node);
    }
}

std::string TestTimelinePerformance::title() const
{
    return "Test ActionTimeline performance";
}

// TestTimelineAnimationList
void TestTimelineAnimationList::onEnter()
{
    ActionTimelineTestLayer::onEnter();
    Node* node = CSLoader::createNode("ActionTimeline/DemoPlayer.csb");
    ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/DemoPlayer.csb");
    cocostudio::timeline::AnimationInfo standinfo("stand", 0, 40);
    cocostudio::timeline::AnimationInfo walkinfo("walk", 41, 81);
    action->addAnimationInfo(standinfo);
    action->addAnimationInfo(walkinfo);
    node->runAction(action);
    action->play("walk", true);
    
    node->setScale(0.2f);
    node->setPosition(150,100);
    addChild(node);
}

std::string TestTimelineAnimationList::title() const
{
    return "Test ActionTimeline AnimationList";
}


//TestTimelineProjectNode
//InnerActionFrame make InnerAction Play until action's duration or next InnerActionFrame
void TestTimelineProjectNode::onEnter()
{
    ActionTimelineTestLayer::onEnter();
    Node* node = CSLoader::createNode("ActionTimeline/TestAnimation.csb");
    ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/TestAnimation.csb");
    
    node->runAction(action);
    action->gotoFrameAndPlay(0, true);
    
    node->setPosition(-300, -300);
    addChild(node);
}

std::string TestTimelineProjectNode::title() const
{
    return "Test ActionTimeline ProjectNode";
}

//TestProjectNodeForSimulator
//InnerActionFrame make InnerAction Play until action's duration or next InnerActionFrame
void TestProjectNodeForSimulator::onEnter()
{
    ActionTimelineTestLayer::onEnter();
    Node* node = CSLoader::getInstance()->createNodeWithFlatBuffersForSimulator("ActionTimeline/TestAnimation.csd");
    ActionTimeline* action = cocostudio::timeline::ActionTimelineCache::getInstance()->createActionWithFlatBuffersForSimulator("ActionTimeline/TestAnimation.csd");
    
    node->runAction(action);
    action->gotoFrameAndPlay(0, true);
    
    node->setPosition(-300, -300);
    addChild(node);
    
    // test for when ProjectNode file lost
    Node* lackProjectNodefileNode = CSLoader::getInstance()->createNodeWithFlatBuffersForSimulator("ActionTimeline/TestNullProjectNode.csd");
    ActionTimeline* lackProjectNodefileAction = cocostudio::timeline::ActionTimelineCache::getInstance()->createActionWithFlatBuffersForSimulator("ActionTimeline/TestNullProjectNode.csd");
    lackProjectNodefileNode->runAction(lackProjectNodefileAction);
    lackProjectNodefileAction->gotoFrameAndPlay(0);
    addChild(lackProjectNodefileNode);
}

std::string TestProjectNodeForSimulator::title() const
{
    return "Test ProjectNode for Simalator";
}

//TestTimelineNodeLoadedCallback
void TestTimelineNodeLoadedCallback::onEnter()
{
    ActionTimelineTestLayer::onEnter();
    
    Node* node = CSLoader::createNode("ActionTimeline/DemoPlayer.csb", CC_CALLBACK_1(TestTimelineNodeLoadedCallback::nodeLoadedCallback,
                                                                                     this));
    ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/DemoPlayer.csb");
    node->runAction(action);
    action->gotoFrameAndPlay(0);
    //    ActionTimelineNode* node = CSLoader::createActionTimelineNode("ActionTimeline/DemoPlayer.csb", 0, 40, true);
    
    node->setScale(0.2f);
    node->setPosition(VisibleRect::center());
    
    addChild(node);
}

std::string TestTimelineNodeLoadedCallback::title() const
{
    return "Test node loaded call back";
}

void TestTimelineNodeLoadedCallback::nodeLoadedCallback(cocos2d::Ref *sender)
{
    Node* node = static_cast<Node*>(sender);
    if (node)
    {
        CCLOG("node name = %s", node->getName().c_str());
        CCLOG("node parent name = %s", node->getParent()->getName().c_str());
    }
}