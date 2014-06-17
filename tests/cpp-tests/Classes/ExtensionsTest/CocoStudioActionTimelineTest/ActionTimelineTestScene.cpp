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
        pLayer = new TestActionTimeline();
        break;
    case TEST_TIMELINE_PERFORMACE:
        pLayer = new TestTimelinePerformance();
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
    const char *pTitle = str.c_str();
    LabelTTF *label = LabelTTF::create(pTitle, "Arial", 18);
    label->setColor(Color3B(0, 0, 0));
    addChild(label, 1, 10000);
    label->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() )
    {
        LabelTTF *l = LabelTTF::create(strSubtitle.c_str(), "Arial", 18);
        l->setColor(Color3B(0, 0, 0));
        addChild(l, 1, 10001);
        l->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - 60) );
    }

    // add menu
    backItem = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(ActionTimelineTestLayer::backCallback, this) );
    restartItem = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(ActionTimelineTestLayer::restartCallback, this) );
    nextItem = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(ActionTimelineTestLayer::nextCallback, this) );

    Menu *menu = Menu::create(backItem, restartItem, nextItem, nullptr);

    menu->setPosition(Point::ZERO);
    backItem->setPosition(Point(VisibleRect::center().x - restartItem->getContentSize().width * 2, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    restartItem->setPosition(Point(VisibleRect::center().x, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    nextItem->setPosition(Point(VisibleRect::center().x + restartItem->getContentSize().width * 2, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));

    addChild(menu, 100);

    setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

}
void ActionTimelineTestLayer::onExit()
{
    removeAllChildren();

    backItem = restartItem = nextItem = nullptr;

    ActionTimelineCache::getInstance()->purge();
    NodeReader::getInstance()->purge();

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
    Scene *s = new ActionTimelineTestScene();
    s->addChild( RestartAnimationTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ActionTimelineTestLayer::nextCallback(Ref *pSender)
{
    Scene *s = new ActionTimelineTestScene();
    s->addChild( NextAnimationTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}
void ActionTimelineTestLayer::backCallback(Ref *pSender)
{
    Scene *s = new ActionTimelineTestScene();
    s->addChild( BackAnimationTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

// TestActionTimeline
void TestActionTimeline::onEnter()
{
    ActionTimelineTestLayer::onEnter();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("armature/Cowboy0.plist", "armature/Cowboy0.png");

    Node* node = NodeReader::getInstance()->createNode("ActionTimeline/boy_1.ExportJson");
    ActionTimeline* action = ActionTimelineCache::getInstance()->createAction("ActionTimeline/boy_1.ExportJson");

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


// TestTimelinePerformance
void TestTimelinePerformance::onEnter()
{
    ActionTimelineTestLayer::onEnter();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("armature/Cowboy0.plist", "armature/Cowboy0.png");

    for (int i = 0; i< 100; i++)
    {
        Node* node = NodeReader::getInstance()->createNode("ActionTimeline/boy_1.ExportJson");
        ActionTimeline* action = ActionTimelineCache::getInstance()->createAction("ActionTimeline/boy_1.ExportJson");

        node->runAction(action);
        action->gotoFrameAndPlay(0, 60, true);

        node->setScale(0.2f);
        node->setPosition(-50+i*2,100);
        addChild(node);
    }
}

std::string TestTimelinePerformance::title() const
{
    return "Test ActionTimeline performance";
}

