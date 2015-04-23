#include "ActionTimelineTestScene.h"
#include "../../testResource.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"
#include "VisibleRect.h"


USING_NS_CC;
using namespace cocostudio;
using namespace cocostudio::timeline;

CocoStudioActionTimelineTests::CocoStudioActionTimelineTests()
{
    ADD_TEST_CASE(TestActionTimeline);
    ADD_TEST_CASE(TestChangePlaySection);
    ADD_TEST_CASE(TestTimelineFrameEvent);
    ADD_TEST_CASE(TestTimelinePerformance);
    ADD_TEST_CASE(TestTimelineAnimationList);
    ADD_TEST_CASE(TestTimelineProjectNode);
    ADD_TEST_CASE(TestProjectNodeForSimulator);
    ADD_TEST_CASE(TestTimelineNodeLoadedCallback);
    ADD_TEST_CASE(TestActionTimelineEase);
}

CocoStudioActionTimelineTests::~CocoStudioActionTimelineTests()
{

}

bool ActionTimelineBaseTest::init()
{
    if (TestCase::init())
    {
        Sprite *bg = Sprite::create("armature/bg.jpg");
        bg->setPosition(VisibleRect::center());

        float scaleX = VisibleRect::getVisibleRect().size.width / bg->getContentSize().width;
        float scaleY = VisibleRect::getVisibleRect().size.height / bg->getContentSize().height;

        bg->setScaleX(scaleX);
        bg->setScaleY(scaleY);

        addChild(bg);

        setGLProgram(ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

        return true;
    }
    return false;
}

void ActionTimelineBaseTest::onExit()
{
    cocostudio::destroyCocosStudio();

    TestCase::onExit();
}

std::string ActionTimelineBaseTest::title() const
{
    return "Armature Test Bed";
}

// TestActionTimeline
void TestActionTimeline::onEnter()
{
    ActionTimelineBaseTest::onEnter();

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
    ActionTimelineBaseTest::onEnter();

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
    ActionTimelineBaseTest::onEnter();

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
    ActionTimelineBaseTest::onEnter();

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
    ActionTimelineBaseTest::onEnter();
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
    ActionTimelineBaseTest::onEnter();
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
    ActionTimelineBaseTest::onEnter();
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
    ActionTimelineBaseTest::onEnter();
    
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


// TestActionTimelineEase
void TestActionTimelineEase::onEnter()
{
    ActionTimelineBaseTest::onEnter();
    
    Node* node = CSLoader::createNode("ActionTimeline/ActionTimelineEase.csb");
    ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/ActionTimelineEase.csb");
    node->runAction(action);
    action->gotoFrameAndPlay(0);
    
    addChild(node);
}

std::string TestActionTimelineEase::title() const
{
    return "Test ActionTimelineEase";
}
