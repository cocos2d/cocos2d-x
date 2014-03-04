/*
 *
 */
#include "PerformanceAllocTest.h"

#include <algorithm>

// Enable profiles for this file
#undef CC_PROFILER_DISPLAY_TIMERS
#define CC_PROFILER_DISPLAY_TIMERS() CCProfiler::sharedProfiler()->displayTimers()
#undef CC_PROFILER_PURGE_ALL
#define CC_PROFILER_PURGE_ALL() CCProfiler::sharedProfiler()->releaseAllTimers()

#undef CC_PROFILER_START
#define CC_PROFILER_START(__name__) CCProfilingBeginTimingBlock(__name__)
#undef CC_PROFILER_STOP
#define CC_PROFILER_STOP(__name__) CCProfilingEndTimingBlock(__name__)
#undef CC_PROFILER_RESET
#define CC_PROFILER_RESET(__name__) CCProfilingResetTimingBlock(__name__)

#undef CC_PROFILER_START_CATEGORY
#define CC_PROFILER_START_CATEGORY(__cat__, __name__) do{ if(__cat__) CCProfilingBeginTimingBlock(__name__); } while(0)
#undef CC_PROFILER_STOP_CATEGORY
#define CC_PROFILER_STOP_CATEGORY(__cat__, __name__) do{ if(__cat__) CCProfilingEndTimingBlock(__name__); } while(0)
#undef CC_PROFILER_RESET_CATEGORY
#define CC_PROFILER_RESET_CATEGORY(__cat__, __name__) do{ if(__cat__) CCProfilingResetTimingBlock(__name__); } while(0)

#undef CC_PROFILER_START_INSTANCE
#define CC_PROFILER_START_INSTANCE(__id__, __name__) do{ CCProfilingBeginTimingBlock( CCString::createWithFormat("%08X - %s", __id__, __name__)->getCString() ); } while(0)
#undef CC_PROFILER_STOP_INSTANCE
#define CC_PROFILER_STOP_INSTANCE(__id__, __name__) do{ CCProfilingEndTimingBlock(    CCString::createWithFormat("%08X - %s", __id__, __name__)->getCString() ); } while(0)
#undef CC_PROFILER_RESET_INSTANCE
#define CC_PROFILER_RESET_INSTANCE(__id__, __name__) do{ CCProfilingResetTimingBlock( CCString::createWithFormat("%08X - %s", __id__, __name__)->getCString() ); } while(0)

#define MAX_LAYER  5

enum {
    kTagInfoLayer = 1,

    kTagBase = 20000,
};

enum {
    kMaxNodes = 15000,
    kNodesIncrease = 500,
};

static int s_nCurCase = 0;

////////////////////////////////////////////////////////
//
// AllocBasicLayer
//
////////////////////////////////////////////////////////

AllocBasicLayer::AllocBasicLayer(bool bControlMenuVisible, int nMaxCases, int nCurCase)
: PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
{
}

void AllocBasicLayer::showCurrentTest()
{
    PerformceAllocScene* scene = NULL;
    switch (m_nCurCase) {
        case 0:
            scene = new NodeCreateTest;
            break;
        case 1:
            scene = new NodeDeallocTest;
            break;
        case 2:
            scene = new SpriteCreateEmptyTest;
            break;
        case 3:
            scene = new SpriteCreateTest;
            break;
        case 4:
            scene = new SpriteDeallocTest;
            break;
        default:
            scene = NULL;
    }

    s_nCurCase = m_nCurCase;

    int nodes = ((PerformceAllocScene*)getParent())->getQuantityOfNodes();

    if (scene)
    {
        scene->initWithQuantityOfNodes(nodes);

        CCDirector::sharedDirector()->replaceScene(scene);
        scene->release();
    }
}

////////////////////////////////////////////////////////
//
// PerformceAllocScene
//
////////////////////////////////////////////////////////
void PerformceAllocScene::initWithQuantityOfNodes(unsigned int nNodes)
{
    //srand(time());
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // Title
    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 40);
    addChild(label, 1);
    label->setPosition(CCPoint(s.width/2, s.height-32));
    label->setColor(ccc3(255,255,40));

    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        CCLabelTTF* l = CCLabelTTF::create(strSubTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(CCPoint(s.width/2, s.height-80));
    }

    lastRenderedCount = 0;
    currentQuantityOfNodes = 0;
    quantityOfNodes = nNodes;

    CCMenuItemFont::setFontSize(65);
    CCMenuItem* decrease = CCMenuItemFont::create(" - ", this, menu_selector(PerformceAllocScene::onDecrease));
    decrease->setColor(ccc3(0,200,20));
    CCMenuItem* increase = CCMenuItemFont::create(" + ", this, menu_selector(PerformceAllocScene::onIncrease));
    increase->setColor(ccc3(0,200,20));

    CCMenu* menu = CCMenu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(CCPoint(s.width/2, s.height/2+15));
    addChild(menu, 1);

    CCLabelTTF* infoLabel = CCLabelTTF::create("0 nodes", "Marker Felt", 30);
    infoLabel->setColor(ccc3(0,200,20));
    infoLabel->setPosition(CCPoint(s.width/2, s.height/2-15));
    addChild(infoLabel, 1, kTagInfoLayer);

    AllocBasicLayer* menuLayer = new AllocBasicLayer(true, MAX_LAYER, s_nCurCase);
    addChild(menuLayer);
    menuLayer->release();

    updateQuantityLabel();
    updateQuantityOfNodes();
    updateProfilerName();
    srand(0);
}

std::string PerformceAllocScene::title()
{
    return "No title";
}

std::string PerformceAllocScene::subtitle()
{
    return "";
}

void PerformceAllocScene::onDecrease(CCObject* pSender)
{
    quantityOfNodes -= kNodesIncrease;
    if( quantityOfNodes < 0 )
        quantityOfNodes = 0;

    updateQuantityLabel();
    updateQuantityOfNodes();
    updateProfilerName();
    srand(0);

    CC_PROFILER_PURGE_ALL();
}

void PerformceAllocScene::onIncrease(CCObject* pSender)
{
    quantityOfNodes += kNodesIncrease;
    if( quantityOfNodes > kMaxNodes )
        quantityOfNodes = kMaxNodes;

    updateQuantityLabel();
    updateQuantityOfNodes();
    updateProfilerName();
    srand(0);

    CC_PROFILER_PURGE_ALL();
}

void PerformceAllocScene::updateQuantityLabel()
{
    if( quantityOfNodes != lastRenderedCount )
    {
        CCLabelTTF* infoLabel = static_cast<CCLabelTTF*>( getChildByTag(kTagInfoLayer) );
        char str[20] = {0};
        sprintf(str, "%u nodes", quantityOfNodes);
        infoLabel->setString(str);

        lastRenderedCount = quantityOfNodes;
    }
}

const char * PerformceAllocScene::profilerName()
{
    return _profilerName;
}

void PerformceAllocScene::updateProfilerName()
{
    snprintf(_profilerName, sizeof(_profilerName)-1, "%s(%d)", testName(), quantityOfNodes);
}

void PerformceAllocScene::onExitTransitionDidStart()
{
    CCScene::onExitTransitionDidStart();
    
    CCDirector* director = CCDirector::sharedDirector();
    CCScheduler* sched = director->getScheduler();

    sched->unscheduleSelector(SEL_SCHEDULE(&PerformceAllocScene::dumpProfilerInfo), this);
}

void PerformceAllocScene::onEnterTransitionDidFinish()
{
    CCScene::onEnterTransitionDidFinish();

    CCDirector* director = CCDirector::sharedDirector();
    CCScheduler* sched = director->getScheduler();

    CC_PROFILER_PURGE_ALL();
    sched->scheduleSelector(SEL_SCHEDULE(&PerformceAllocScene::dumpProfilerInfo), this, 2, false);
}

void PerformceAllocScene::dumpProfilerInfo(float dt)
{
	CC_PROFILER_DISPLAY_TIMERS();
}

////////////////////////////////////////////////////////
//
// NodeCreateTest
//
////////////////////////////////////////////////////////
void NodeCreateTest::updateQuantityOfNodes()
{
    currentQuantityOfNodes = quantityOfNodes;
}

void NodeCreateTest::initWithQuantityOfNodes(unsigned int nNodes)
{
    PerformceAllocScene::initWithQuantityOfNodes(nNodes);

    printf("Size of Node: %d\n", static_cast<int>(sizeof(CCNode)));

    scheduleUpdate();
}

void NodeCreateTest::update(float dt)
{
    // iterate using fast enumeration protocol

    CCNode **nodes = new CCNode*[quantityOfNodes];

    CC_PROFILER_START(this->profilerName());
    for( int i=0; i<quantityOfNodes; ++i)
        nodes[i] = CCNode::create();
    CC_PROFILER_STOP(this->profilerName());

    delete [] nodes;
}

std::string NodeCreateTest::title()
{
    return "Node Create Perf test.";
}

std::string NodeCreateTest::subtitle()
{
    return "Node Create Perf test. See console";
}

const char*  NodeCreateTest::testName()
{
    return "Node::create()";
}

////////////////////////////////////////////////////////
//
// NodeDeallocTest
//
////////////////////////////////////////////////////////
void NodeDeallocTest::updateQuantityOfNodes()
{
    currentQuantityOfNodes = quantityOfNodes;
}

void NodeDeallocTest::initWithQuantityOfNodes(unsigned int nNodes)
{
    PerformceAllocScene::initWithQuantityOfNodes(nNodes);

    printf("Size of Node: %d\n", static_cast<int>(sizeof(CCNode)));

    scheduleUpdate();
}

void NodeDeallocTest::update(float dt)
{
    // iterate using fast enumeration protocol

    CCNode **nodes = new CCNode*[quantityOfNodes];

    for( int i=0; i<quantityOfNodes; ++i) {
        nodes[i] = new CCNode;
        nodes[i]->init();
    }

    CC_PROFILER_START(this->profilerName());
    for( int i=0; i<quantityOfNodes; ++i)
        nodes[i]->release();
    CC_PROFILER_STOP(this->profilerName());

    delete [] nodes;
}

std::string NodeDeallocTest::title()
{
    return "Node Dealloc Perf test.";
}

std::string NodeDeallocTest::subtitle()
{
    return "Node Dealloc Perf test. See console";
}

const char*  NodeDeallocTest::testName()
{
    return "Node::~Node()";
}

////////////////////////////////////////////////////////
//
// SpriteCreateEmptyTest
//
////////////////////////////////////////////////////////
void SpriteCreateEmptyTest::updateQuantityOfNodes()
{
    currentQuantityOfNodes = quantityOfNodes;
}

void SpriteCreateEmptyTest::initWithQuantityOfNodes(unsigned int nNodes)
{
    PerformceAllocScene::initWithQuantityOfNodes(nNodes);

    printf("Size of Node: %d\n", static_cast<int>(sizeof(CCSprite)));

    scheduleUpdate();
}

void SpriteCreateEmptyTest::update(float dt)
{
    // iterate using fast enumeration protocol

    CCSprite **sprites = new CCSprite*[quantityOfNodes];

    CCSprite::create("Images/grossini.png");

    CC_PROFILER_START(this->profilerName());
    for( int i=0; i<quantityOfNodes; ++i)
        sprites[i] = CCSprite::create();
    CC_PROFILER_STOP(this->profilerName());

    delete [] sprites;
}

std::string SpriteCreateEmptyTest::title()
{
    return "Create Empty Sprite";
}

std::string SpriteCreateEmptyTest::subtitle()
{
    return "Create Empty Sprite Perf test. See console";
}

const char*  SpriteCreateEmptyTest::testName()
{
    return "Sprite::create(void)";
}

////////////////////////////////////////////////////////
//
// SpriteCreateTest
//
////////////////////////////////////////////////////////
void SpriteCreateTest::updateQuantityOfNodes()
{
    currentQuantityOfNodes = quantityOfNodes;
}

void SpriteCreateTest::initWithQuantityOfNodes(unsigned int nNodes)
{
    PerformceAllocScene::initWithQuantityOfNodes(nNodes);

    printf("Size of Node: %d\n", static_cast<int>(sizeof(CCSprite)));

    scheduleUpdate();
}

void SpriteCreateTest::update(float dt)
{
    // iterate using fast enumeration protocol

    CCSprite **sprites = new CCSprite*[quantityOfNodes];

    CCSprite::create("Images/grossini.png");
    
    CC_PROFILER_START(this->profilerName());
    for( int i=0; i<quantityOfNodes; ++i)
        sprites[i] = CCSprite::create("Images/grossini.png");
    CC_PROFILER_STOP(this->profilerName());

    delete [] sprites;
}

std::string SpriteCreateTest::title()
{
    return "Create Sprite";
}

std::string SpriteCreateTest::subtitle()
{
    return "Create Empty Sprite. See console";
}

const char*  SpriteCreateTest::testName()
{
    return "Sprite::create(\"image\")";
}

////////////////////////////////////////////////////////
//
// SpriteDeallocTest
//
////////////////////////////////////////////////////////
void SpriteDeallocTest::updateQuantityOfNodes()
{
    currentQuantityOfNodes = quantityOfNodes;
}

void SpriteDeallocTest::initWithQuantityOfNodes(unsigned int nNodes)
{
    PerformceAllocScene::initWithQuantityOfNodes(nNodes);

    printf("Size of Node: %d\n", static_cast<int>(sizeof(CCSprite)));

    scheduleUpdate();
}

void SpriteDeallocTest::update(float dt)
{
    // iterate using fast enumeration protocol

    CCSprite **sprites = new CCSprite*[quantityOfNodes];

    for( int i=0; i<quantityOfNodes; ++i) {
        sprites[i] = new CCSprite;
        sprites[i]->init();
    }

    CC_PROFILER_START(this->profilerName());
    for( int i=0; i<quantityOfNodes; ++i)
        sprites[i]->release();
    CC_PROFILER_STOP(this->profilerName());

    delete [] sprites;
}

std::string SpriteDeallocTest::title()
{
    return "Sprite Dealloc Perf test.";
}

std::string SpriteDeallocTest::subtitle()
{
    return "Sprite Dealloc Perf test. See console";
}

const char*  SpriteDeallocTest::testName()
{
    return "Sprite::~Sprite()";
}

///----------------------------------------
void runAllocPerformanceTest()
{
    PerformceAllocScene* scene = new NodeCreateTest;
    scene->initWithQuantityOfNodes(kNodesIncrease);
    
    CCDirector::sharedDirector()->replaceScene(scene);
    scene->release();
}
