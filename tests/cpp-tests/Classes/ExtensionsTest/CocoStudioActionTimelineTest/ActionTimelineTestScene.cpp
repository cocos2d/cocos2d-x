#include "ActionTimelineTestScene.h"
#include "../../testResource.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"
#include "VisibleRect.h"
#include "editor-support/cocostudio/CCComExtensionData.h"
#include "ui/CocosGUI.h"


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
    ADD_TEST_CASE(TestActionTimelineSkeleton);
    ADD_TEST_CASE(TestTimelineExtensionData);
    ADD_TEST_CASE(TestActionTimelineBlendFuncFrame);
    ADD_TEST_CASE(TestAnimationClipEndCallBack);
    ADD_TEST_CASE(TestActionTimelinePlayableFrame);
    ADD_TEST_CASE(TestActionTimelineIssueWith2SameActionInOneNode);
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

        setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

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

    Data data = FileUtils::getInstance()->getDataFromFile("ActionTimeline/DemoPlayer.csb");
    Node* node = CSLoader::createNode(data);
    ActionTimeline* action = CSLoader::createTimeline(data, "ActionTimeline/DemoPlayer.csb");
    node->runAction(action);
    action->gotoFrameAndPlay(0);

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

//TestActionTimelineSkeleton
void TestActionTimelineSkeleton::onEnter()
{
    ActionTimelineBaseTest::onEnter();

    _changedDisplays = _changedDisplay = false;
    Node* node = CSLoader::createNode("ActionTimeline/DemoPlayer_skeleton.csb");
    ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/DemoPlayer_skeleton.csb");
    node->runAction(action);
    node->setScale(0.2f);
    node->setPosition(150, 150);
    action->gotoFrameAndPlay(0);
    addChild(node);

    auto skeletonNode = static_cast<SkeletonNode*>(node);
    const std::string weapBoneName = "Layer20";
    auto weaponHandeBone = skeletonNode->getBoneNode(weapBoneName);
    
    /***********   debug draw bones  *************/
    auto boneDrawsBtn = cocos2d::ui::Button::create();
    addChild(boneDrawsBtn);
    boneDrawsBtn->setPosition(Vec2(VisibleRect::right().x - 30, VisibleRect::top().y - 30));
    boneDrawsBtn->setTitleText("Draw bone");

    skeletonNode->setDebugDrawEnabled(true);
    boneDrawsBtn->addClickEventListener([skeletonNode, this](Ref* sender)
    {
        skeletonNode->setDebugDrawEnabled(!skeletonNode->isDebugDrawEnabled());
    });


    /***************** change bone display **************************/

    // add display
    auto weapSkinToAdd = Sprite::create("ActionTimeline/testAnimationResource/girl_arms.png");
    weapSkinToAdd->setName("Knife");
    weapSkinToAdd->setPosition(Vec2(135, 23));
    weapSkinToAdd->setScale(3.0f);
    weapSkinToAdd->setRotation(86);
    weaponHandeBone->addSkin(weapSkinToAdd, false);

    // change display
    auto changeBoneDispBtn = cocos2d::ui::Button::create();
    addChild(changeBoneDispBtn);
    changeBoneDispBtn->setPosition(Vec2(VisibleRect::right().x - 60, VisibleRect::top().y - 60));
    changeBoneDispBtn->setTitleText("change bone display");
    changeBoneDispBtn->addClickEventListener([weapSkinToAdd, weaponHandeBone](Ref* sender)
    {
        // or use skeletonNode->display(bone name, skin name, hide)
        if (weapSkinToAdd->isVisible())
            weaponHandeBone->displaySkin("3", true);
        else
        {
            weaponHandeBone->displaySkin(weapSkinToAdd, true);
        }
    });


    /*************** debug draw boundingbox and transforms ***************/
    auto debugDrawNode = DrawNode::create();
    addChild(debugDrawNode);

    auto drawBoxBtn = cocos2d::ui::Button::create();
    addChild(drawBoxBtn);
    drawBoxBtn->setPosition(Vec2(VisibleRect::right().x - 30, VisibleRect::top().y - 45));
    drawBoxBtn->setTitleText("Draw Box");

    
    drawBoxBtn->addClickEventListener([debugDrawNode](Ref* sender)
    {
        debugDrawNode->setVisible(!debugDrawNode->isVisible());
    });
    skeletonNode->schedule([skeletonNode, weaponHandeBone, debugDrawNode](float interval)
    {
        if (debugDrawNode->isVisible())
        {
            debugDrawNode->clear();
             // skeleton boundingbox
              auto rect = skeletonNode->getBoundingBox();
              cocos2d::Vec2 leftbottom(rect.getMinX(), rect.getMinY());
              cocos2d::Vec2 righttop(rect.getMaxX(), rect.getMaxY());
              debugDrawNode->drawRect(leftbottom, righttop, cocos2d::Color4F::YELLOW);

            // bone boundingbox
            rect = weaponHandeBone->getBoundingBox();
            leftbottom.x = rect.getMinX(); leftbottom.y = rect.getMinY();
            righttop.x = rect.getMaxX(); righttop.y = rect.getMaxY();
            cocos2d::Vec2 lefttop(rect.getMinX(), rect.getMaxY());
            cocos2d::Vec2 rightbottom(rect.getMaxX(), rect.getMinY());
            auto skeletonToP = skeletonNode->getNodeToParentAffineTransform();
            auto bonePtoSkeletonPTrans = AffineTransformConcat(
                static_cast<BoneNode*>((weaponHandeBone->getParent())
                )->getNodeToParentAffineTransform(skeletonNode),
                skeletonToP);
            leftbottom = PointApplyAffineTransform(leftbottom, bonePtoSkeletonPTrans);
            righttop = PointApplyAffineTransform(righttop, bonePtoSkeletonPTrans);
            lefttop = PointApplyAffineTransform(lefttop, bonePtoSkeletonPTrans);
            rightbottom = PointApplyAffineTransform(rightbottom, bonePtoSkeletonPTrans);
            debugDrawNode->drawLine(leftbottom, rightbottom, Color4F::BLUE);
            debugDrawNode->drawLine(rightbottom, righttop, Color4F::BLUE);
            debugDrawNode->drawLine(righttop, lefttop, Color4F::BLUE);
            debugDrawNode->drawLine(lefttop, leftbottom, Color4F::BLUE);

            // skin boundingbox 

             // get displaying nodes
             auto currentskin = weaponHandeBone->getVisibleSkins().front();
             rect = currentskin->getBoundingBox();
             leftbottom.x = rect.getMinX(); leftbottom.y = rect.getMinY();
             righttop.x = rect.getMaxX(); righttop.y = rect.getMaxY();
             lefttop.x = rect.getMinX(); lefttop.y =  rect.getMaxY();
             rightbottom.x = rect.getMaxX(); rightbottom.y = rect.getMinY();
             auto boneToSkeletonParentTrans = AffineTransformConcat(
                 weaponHandeBone->getNodeToParentAffineTransform(skeletonNode), skeletonToP);
             leftbottom = PointApplyAffineTransform(leftbottom, boneToSkeletonParentTrans);
             righttop = PointApplyAffineTransform(righttop, boneToSkeletonParentTrans);
             lefttop = PointApplyAffineTransform(lefttop, boneToSkeletonParentTrans);
             rightbottom = PointApplyAffineTransform(rightbottom, boneToSkeletonParentTrans);
 
             debugDrawNode->drawLine(leftbottom, rightbottom, Color4F::GREEN);
             debugDrawNode->drawLine(rightbottom, righttop, Color4F::GREEN);
             debugDrawNode->drawLine(righttop, lefttop, Color4F::GREEN);
             debugDrawNode->drawLine(lefttop, leftbottom, Color4F::GREEN);
        }
    }, 0, "update debug draw");


    // change displays , can be use for dress up a skeleton
    auto changeBoneDispsBtn = cocos2d::ui::Button::create();
    addChild(changeBoneDispsBtn);
    changeBoneDispsBtn->setPosition(Vec2(VisibleRect::right().x - 60, VisibleRect::top().y - 75));
    changeBoneDispsBtn->setTitleText("change bone displays");

    std::map < std::string, std::string> boneSkinNames;
    boneSkinNames.insert(std::make_pair("Layer20", "fire"));
    boneSkinNames.insert(std::make_pair("Layer14", "fruit"));
    skeletonNode->addSkinGroup("fruitKnife", boneSkinNames);

    std::map < std::string, std::string> boneSkinNames2;
    boneSkinNames2.insert(std::make_pair("Layer20", "3"));
    boneSkinNames2.insert(std::make_pair("Layer14", "hat"));
    skeletonNode->addSkinGroup("cowboy", boneSkinNames2);

    changeBoneDispsBtn->addClickEventListener([skeletonNode, this](Ref* sender)
    {
        if (!_changedDisplays)
        {
            skeletonNode->changeSkins("fruitKnife");
            _changedDisplays = true;
        }
        else
        {
            skeletonNode->changeSkins("cowboy");
            _changedDisplays = false;
        }
    });


    /*********** test cases for bugs        **********/
    // bug: #13060 https://github.com/cocos2d/cocos2d-x/issues/13060
    // bug: bone draw at the other edge when move to outside right edge.
    BoneNode* bugtestBoneNode = BoneNode::create(500);
    bugtestBoneNode->setRotation(-10);
    bugtestBoneNode->retain();
    bugtestBoneNode->setDebugDrawEnabled(true);
    bugtestBoneNode->setPosition(Vec2(1500, VisibleRect::top().y - 90));
    auto bug13060Btn = cocos2d::ui::Button::create();
    bug13060Btn->setPosition(Vec2(VisibleRect::right().x - 30, VisibleRect::top().y - 90));
    bug13060Btn->setTitleText("bug #13060");
    addChild(bug13060Btn);
    bug13060Btn->addClickEventListener([bugtestBoneNode, skeletonNode](Ref* sender)
    {
        if (bugtestBoneNode->getParent() == nullptr)
            skeletonNode->addChild(bugtestBoneNode);
        else
            bugtestBoneNode->removeFromParent();
         // bug fixed while bugtestBoneNode not be drawn at the bottom edge 
    });

    // bug: #13005 https://github.com/cocos2d/cocos2d-x/issues/#13005
    // bug: BoneNode 's debugdraw can not be controlled by ancestor's visible
    auto leftleg = skeletonNode->getBoneNode("Layer26");
    auto bug13005Btn = cocos2d::ui::Button::create();
    addChild(bug13005Btn);
    bug13005Btn->setPosition(Vec2(VisibleRect::right().x - 30, VisibleRect::top().y - 105));
    bug13005Btn->setTitleText("bug #13005");
    bug13005Btn->addClickEventListener([leftleg](Ref* sender)
    {
        leftleg->setVisible(!leftleg->isVisible());
        // bug fixed while leftleg's child hide with leftleg's visible
    });


    /*************    Skeleton nest Skeleton test       *************/
    auto nestSkeletonBtn = cocos2d::ui::Button::create();
    nestSkeletonBtn->setTitleText("Skeleton Nest");
    nestSkeletonBtn->setPosition(Vec2(VisibleRect::right().x - 40, VisibleRect::top().y - 120));
    addChild(nestSkeletonBtn);
    auto nestSkeleton = static_cast<SkeletonNode*>(CSLoader::createNode("ActionTimeline/DemoPlayer_skeleton.csb"));
    nestSkeleton->retain();
    ActionTimeline* nestSkeletonAction = action->clone();
    nestSkeletonAction->retain();
    nestSkeleton->runAction(nestSkeletonAction);
    nestSkeleton->setScale(0.2f);
    nestSkeleton->setPosition(150, 300);
    nestSkeletonAction->gotoFrameAndPlay(0);
    // show debug draws, or comment this for hide bones draws
    for (auto& nestbonechild : nestSkeleton->getAllSubBonesMap())
    {
        nestbonechild.second->setDebugDrawEnabled(true);
    }

    nestSkeletonBtn->addClickEventListener([leftleg, nestSkeleton, nestSkeletonAction](Ref* sender)
    {
        if (nestSkeleton->getParent() == nullptr)
        {
            leftleg->addChild(nestSkeleton);
        }
        else
        {
            nestSkeleton->removeFromParentAndCleanup(false);
        }
    });
}

std::string TestActionTimelineSkeleton::title() const
{
    return "Test ActionTimeline Skeleton";
}

// TestTimelineExtensionData
void TestTimelineExtensionData::onEnter()
{
    ActionTimelineBaseTest::onEnter();

    Node* node = CSLoader::createNode("ActionTimeline/TestAnimation.csb");
    ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/TestAnimation.csb");
    node->runAction(action);
    action->gotoFrameAndPlay(0);

    auto projectNode = node->getChildByTag(29);
    auto userdata = ((ComExtensionData*)(projectNode->getComponent("ComExtensionData")))->getCustomProperty();

    auto size = Director::getInstance()->getWinSize();
    auto label = Label::create();
    label->setString(userdata);
    label->setPosition(size.width / 2 + 300, size.height / 2 + 300);
    label->setTextColor(Color4B::ORANGE);
    node->addChild(label);
    node->setPosition(-300, -300);

    addChild(node);

}

std::string TestTimelineExtensionData::title() const
{
    return "Test Timeline extension data";
}

// TestActionTimelineBlendFuncFrame
void TestActionTimelineBlendFuncFrame::onEnter()
{
    ActionTimelineBaseTest::onEnter();
    Node* node = CSLoader::createNode("ActionTimeline/skeletonBlendFuncFrame.csb");
    ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/skeletonBlendFuncFrame.csb");
    node->runAction(action);
    node->setScale(0.2f);
    node->setPosition(VisibleRect::center());
    this->addChild(node);
    action->gotoFrameAndPlay(0);
}

std::string TestActionTimelineBlendFuncFrame::title() const
{
    return "Test ActionTimeline BlendFunc Frame";
}

//TestAnimationClipEndCallBack
void TestAnimationClipEndCallBack::onEnter()
{
    ActionTimelineBaseTest::onEnter();
    Node* node = CSLoader::createNode("ActionTimeline/DemoPlayer_skeleton.csb");
    ActionTimeline* action = CSLoader::createTimeline("ActionTimeline/DemoPlayer_skeleton.csb");
    node->runAction(action);
    node->setScale(0.2f);
    node->setPosition(150, 150);

     // test for frame end call back
     action->addFrameEndCallFunc(5, "CallBackAfterFifthFrame", [this]{
          auto text = ui::Text::create();
          text->setString("CallBackAfterFifthFrame");
          text->setPosition(Vec2(100, 40));
          text->setLocalZOrder(1000);
          this->runAction(Sequence::create(
              CallFunc::create([this, text]{this->addChild(text); }),
              DelayTime::create(3),
              CallFunc::create([text]{text->removeFromParent(); }),
              nullptr));
     });
     action->addFrameEndCallFunc(5, "AnotherCallBackAfterFifthFrame", [this]{
         auto text = ui::Text::create();
         text->setString("AnotherCallBackAfterFifthFrame");
         text->setPosition(Vec2(100, 70));
         this->runAction(Sequence::create(
             CallFunc::create([this, text]{this->addChild(text); }),
             DelayTime::create(3),
             CallFunc::create([text]{text->removeFromParent(); }),
             nullptr));
     });
     action->addFrameEndCallFunc(7, "CallBackAfterSenvnthFrame", [this]{
         auto text = ui::Text::create();
         text->setString("CallBackAfterSenvnthFrame");
         text->setPosition(Vec2(100, 100));
         this->runAction(Sequence::create(
             CallFunc::create([this, text]{this->addChild(text); }),
             DelayTime::create(3),
             CallFunc::create([text]{text->removeFromParent(); }),
             nullptr));
     });
     
     // test for animation clip end call back
     action->setAnimationEndCallFunc("stand", [this]{
         auto text = ui::Text::create();
         text->setString("CallBackAfterStandAnimationClip");
         text->setPosition(Vec2(100, 130));
         this->runAction(Sequence::create(
             CallFunc::create([this, text]{this->addChild(text); }),
             DelayTime::create(3),
             CallFunc::create([text]{text->removeFromParent(); }),
             nullptr));
     });
 
     AnimationClip animClip("testClip", 3, 13);
     animClip.clipEndCallBack = ([this,node]{
         auto text = ui::Text::create();
         text->setString("testClip");
         text->setPosition(Vec2(100, 140));
         this->runAction(Sequence::create(
             CallFunc::create([this, text]{this->addChild(text); }),
             DelayTime::create(3),
             CallFunc::create([text]{text->removeFromParent(); }),
             nullptr));
     });
     action->addAnimationInfo(animClip);

    action->setTimeSpeed(0.2f);
    addChild(node);
    action->gotoFrameAndPlay(0);
}

std::string TestAnimationClipEndCallBack::title() const
{
    return "Test ActionTimeline Frame End Call Back\n and Animation Clip End Call Back";
}

//TestActionTimelinePlayableFrame
void TestActionTimelinePlayableFrame::onEnter()
{
    ActionTimelineBaseTest::onEnter();

    Node* node = Node::create();
    auto action = ActionTimeline::create();

    auto particle = ParticleSystemQuad::create("Particles/Comet.plist");
    particle->setPosition(VisibleRect::center());
    ComExtensionData* extensionData_p = ComExtensionData::create();
    extensionData_p->setActionTag(890890);
    extensionData_p->setName(ComExtensionData::COMPONENT_NAME);
    particle->addComponent(extensionData_p);
    node->addChild(particle);

    auto audio = ComAudio::create();
    audio->setFile("audio/LuckyDay.mp3");
    audio->start();
    auto audioNode = Node::create();
    audio->setName(PlayableFrame::PLAYABLE_EXTENTION);
    audioNode->addComponent(audio);
    ComExtensionData* extensionData_a = ComExtensionData::create();
    extensionData_a->setActionTag(123123);
    extensionData_a->setName(ComExtensionData::COMPONENT_NAME);
    audioNode->addComponent(extensionData_a);
    node->addChild(audioNode);

    auto frame_a1 = PlayableFrame::create();
    frame_a1->setFrameIndex(0);
    frame_a1->setPlayableAct("start");
    auto frame_a2 = PlayableFrame::create();
    frame_a2->setFrameIndex(50);
    frame_a2->setPlayableAct("stop");
    auto timeline_a = Timeline::create();
    timeline_a->setActionTag(123123);
    timeline_a->addFrame(frame_a1);
    timeline_a->addFrame(frame_a2);
    action->addTimeline(timeline_a);

    auto timeline_p = Timeline::create();
    auto frame_p1 = PlayableFrame::create();
    frame_p1->setFrameIndex(0);
    frame_p1->setPlayableAct("start");
    auto frame_p2 = PlayableFrame::create();
    frame_p2->setFrameIndex(50);
    frame_p2->setPlayableAct("stop");
    timeline_p->setActionTag(890890);
    timeline_p->addFrame(frame_p1);
    timeline_p->addFrame(frame_p2);
    action->addTimeline(timeline_p);

    action->setTimeSpeed(0.2);
    action->setDuration(65);
    node->runAction(action);
    action->gotoFrameAndPlay(0);
    this->addChild(node);
}

std::string TestActionTimelinePlayableFrame::title() const
{
    return "Test Action Timeline PlayableFrame\n particle and audio";
}

void TestActionTimelineIssueWith2SameActionInOneNode::onEnter()
{
    CCFileUtils::getInstance()->addSearchPath("ActionTimeline");
    ActionTimelineBaseTest::onEnter();

    Node* node = CSLoader::createNode("ani2.csb");
    ActionTimeline* action = CSLoader::createTimeline("ani2.csb");
    node->setPosition(Vec2(150, 100));
    node->runAction(action);
    action->gotoFrameAndPlay(0);
    this->addChild(node);
}

std::string TestActionTimelineIssueWith2SameActionInOneNode::title() const
{
    return "Add multi same action in one node issue\n  These two actions should play async.";
}