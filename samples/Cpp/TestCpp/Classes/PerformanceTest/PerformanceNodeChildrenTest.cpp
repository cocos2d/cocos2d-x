#include "PerformanceNodeChildrenTest.h"

#include <algorithm>

// Enable profiles for this file
#undef CC_PROFILER_DISPLAY_TIMERS
#define CC_PROFILER_DISPLAY_TIMERS() Profiler::getInstance()->displayTimers()
#undef CC_PROFILER_PURGE_ALL
#define CC_PROFILER_PURGE_ALL() Profiler::getInstance()->releaseAllTimers()

#undef CC_PROFILER_START
#define CC_PROFILER_START(__name__) ProfilingBeginTimingBlock(__name__)
#undef CC_PROFILER_STOP
#define CC_PROFILER_STOP(__name__) ProfilingEndTimingBlock(__name__)
#undef CC_PROFILER_RESET
#define CC_PROFILER_RESET(__name__) ProfilingResetTimingBlock(__name__)

#undef CC_PROFILER_START_CATEGORY
#define CC_PROFILER_START_CATEGORY(__cat__, __name__) do{ if(__cat__) ProfilingBeginTimingBlock(__name__); } while(0)
#undef CC_PROFILER_STOP_CATEGORY
#define CC_PROFILER_STOP_CATEGORY(__cat__, __name__) do{ if(__cat__) ProfilingEndTimingBlock(__name__); } while(0)
#undef CC_PROFILER_RESET_CATEGORY
#define CC_PROFILER_RESET_CATEGORY(__cat__, __name__) do{ if(__cat__) ProfilingResetTimingBlock(__name__); } while(0)

#undef CC_PROFILER_START_INSTANCE
#define CC_PROFILER_START_INSTANCE(__id__, __name__) do{ ProfilingBeginTimingBlock( String::createWithFormat("%08X - %s", __id__, __name__)->getCString() ); } while(0)
#undef CC_PROFILER_STOP_INSTANCE
#define CC_PROFILER_STOP_INSTANCE(__id__, __name__) do{ ProfilingEndTimingBlock(    String::createWithFormat("%08X - %s", __id__, __name__)->getCString() ); } while(0)
#undef CC_PROFILER_RESET_INSTANCE
#define CC_PROFILER_RESET_INSTANCE(__id__, __name__) do{ ProfilingResetTimingBlock( String::createWithFormat("%08X - %s", __id__, __name__)->getCString() ); } while(0)

static std::function<NodeChildrenMainScene*()> createFunctions[] =
{
    CL(IterateSpriteSheetForLoop),
    CL(IterateSpriteSheetCArray),
    CL(IterateSpriteSheetIterator),

    CL(CallFuncsSpriteSheetForEach),
    CL(CallFuncsSpriteSheetCMacro),

    CL(AddSpriteSheet),
    CL(RemoveSpriteSheet),
    CL(ReorderSpriteSheet),
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

enum {
    kTagInfoLayer = 1,

    kTagBase = 20000,
};

enum {
    kMaxNodes = 15000,
    kNodesIncrease = 500,
};

static int g_curCase = 0;

////////////////////////////////////////////////////////
//
// NodeChildrenMenuLayer
//
////////////////////////////////////////////////////////
NodeChildrenMenuLayer::NodeChildrenMenuLayer(bool bControlMenuVisible, int nMaxCases, int nCurCase)
: PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
{
}

void NodeChildrenMenuLayer::onExitTransitionDidStart()
{
    auto director = Director::getInstance();
    auto sched = director->getScheduler();

    sched->unscheduleSelector(SEL_SCHEDULE(&NodeChildrenMenuLayer::dumpProfilerInfo), this);
}

void NodeChildrenMenuLayer::onEnterTransitionDidFinish()
{
    auto director = Director::getInstance();
    auto sched = director->getScheduler();

    CC_PROFILER_PURGE_ALL();
    sched->scheduleSelector(SEL_SCHEDULE(&NodeChildrenMenuLayer::dumpProfilerInfo), this, 2, false);
}


void NodeChildrenMenuLayer::dumpProfilerInfo(float dt)
{
	CC_PROFILER_DISPLAY_TIMERS();
}

void NodeChildrenMenuLayer::showCurrentTest()
{
    int nodes = ((NodeChildrenMainScene*)getParent())->getQuantityOfNodes();

    auto scene = createFunctions[_curCase]();

    g_curCase = _curCase;

    if (scene)
    {
        scene->initWithQuantityOfNodes(nodes);

        Director::getInstance()->replaceScene(scene);
        scene->release();
    }
}

////////////////////////////////////////////////////////
//
// NodeChildrenMainScene
//
////////////////////////////////////////////////////////
void NodeChildrenMainScene::initWithQuantityOfNodes(unsigned int nNodes)
{
    //srand(time());
    auto s = Director::getInstance()->getWinSize();

    // Title
    auto label = LabelTTF::create(title().c_str(), "Arial", 40);
    addChild(label, 1);
    label->setPosition(Point(s.width/2, s.height-32));
    label->setColor(Color3B(255,255,40));

    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        auto l = LabelTTF::create(strSubTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(Point(s.width/2, s.height-80));
    }

    lastRenderedCount = 0;
    currentQuantityOfNodes = 0;
    quantityOfNodes = nNodes;

    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", [&](Object *sender) {
		quantityOfNodes -= kNodesIncrease;
		if( quantityOfNodes < 0 )
			quantityOfNodes = 0;

		updateQuantityLabel();
		updateQuantityOfNodes();

        CC_PROFILER_PURGE_ALL();
	});
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", [&](Object *sender) {
		quantityOfNodes += kNodesIncrease;
		if( quantityOfNodes > kMaxNodes )
			quantityOfNodes = kMaxNodes;

		updateQuantityLabel();
		updateQuantityOfNodes();

        CC_PROFILER_PURGE_ALL();
	});
    increase->setColor(Color3B(0,200,20));

    auto menu = Menu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(Point(s.width/2, s.height/2+15));
    addChild(menu, 1);

    auto infoLabel = LabelTTF::create("0 nodes", "Marker Felt", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Point(s.width/2, s.height/2-15));
    addChild(infoLabel, 1, kTagInfoLayer);

    auto menuLayer = new NodeChildrenMenuLayer(true, MAX_LAYER, g_curCase);
    addChild(menuLayer);
    menuLayer->release();

    updateQuantityLabel();
    updateQuantityOfNodes();
}

std::string NodeChildrenMainScene::title()
{
    return "No title";
}

std::string NodeChildrenMainScene::subtitle()
{
    return "";
}

void NodeChildrenMainScene::updateQuantityLabel()
{
    if( quantityOfNodes != lastRenderedCount )
    {
        auto infoLabel = static_cast<LabelTTF*>( getChildByTag(kTagInfoLayer) );
        char str[20] = {0};
        sprintf(str, "%u nodes", quantityOfNodes);
        infoLabel->setString(str);

        lastRenderedCount = quantityOfNodes;
    }
}

////////////////////////////////////////////////////////
//
// IterateSpriteSheet
//
////////////////////////////////////////////////////////
IterateSpriteSheet::~IterateSpriteSheet()
{

}

void IterateSpriteSheet::updateQuantityOfNodes()
{
    auto s = Director::getInstance()->getWinSize();

    // increase nodes
    if( currentQuantityOfNodes < quantityOfNodes )
    {
        for(int i = 0; i < (quantityOfNodes-currentQuantityOfNodes); i++)
        {
            auto sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(0, 0, 32, 32));
            batchNode->addChild(sprite);
            sprite->setVisible(false);
            sprite->setPosition(Point(-1000,-1000));
        }
    }

    // decrease nodes
    else if ( currentQuantityOfNodes > quantityOfNodes )
    {
        for(int i = 0; i < (currentQuantityOfNodes-quantityOfNodes); i++)
        {
            int index = currentQuantityOfNodes-i-1;
            batchNode->removeChildAtIndex(index, true);
        }
    }

    currentQuantityOfNodes = quantityOfNodes;
}

void IterateSpriteSheet::initWithQuantityOfNodes(unsigned int nNodes)
{
    batchNode = SpriteBatchNode::create("Images/spritesheet1.png");
    addChild(batchNode);
    
    NodeChildrenMainScene::initWithQuantityOfNodes(nNodes);

    scheduleUpdate();
}

const char*  IterateSpriteSheet::profilerName()
{
    return "none";
}

////////////////////////////////////////////////////////
//
// IterateSpriteSheetForLoop
//
////////////////////////////////////////////////////////
void IterateSpriteSheetForLoop::update(float dt)
{
    // iterate using fast enumeration protocol
    auto children = batchNode->getChildren();

    CC_PROFILER_START(this->profilerName());

    for( const auto &object : *children )
    {
        auto o = static_cast<Object*>(object);
        auto sprite = static_cast<Sprite*>(o);
        sprite->setVisible(false);
    }

    CC_PROFILER_STOP(this->profilerName());
}

std::string IterateSpriteSheetForLoop::title()
{
    return "A - Iterate SpriteSheet";
}

std::string IterateSpriteSheetForLoop::subtitle()
{
    return "Iterate children using C++11 range-based for loop. See console";
}

const char*  IterateSpriteSheetForLoop::profilerName()
{
    return "Iterator: C++11 for loop";
}

////////////////////////////////////////////////////////
//
// IterateSpriteSheetCArray
//
////////////////////////////////////////////////////////
void IterateSpriteSheetCArray::update(float dt)
{
    // iterate using fast enumeration protocol
    auto children = batchNode->getChildren();
    Object* object = NULL;

    CC_PROFILER_START(this->profilerName());

    CCARRAY_FOREACH(children, object)
    {
        auto sprite = static_cast<Sprite*>(object);
        sprite->setVisible(false);
    }

    CC_PROFILER_STOP(this->profilerName());
}


std::string IterateSpriteSheetCArray::title()
{
    return "B - Iterate SpriteSheet";
}

std::string IterateSpriteSheetCArray::subtitle()
{
    return "Iterate children using C Array API. See console";
}

const char*  IterateSpriteSheetCArray::profilerName()
{
    return "Iterator: CC_ARRAY_FOREACH";
}

////////////////////////////////////////////////////////
//
// IterateSpriteSheetIterator
//
////////////////////////////////////////////////////////
void IterateSpriteSheetIterator::update(float dt)
{
    // iterate using fast enumeration protocol
    auto children = batchNode->getChildren();

    CC_PROFILER_START(this->profilerName());

    for( auto it=std::begin(*children); it != std::end(*children); ++it)
    {
        auto obj = static_cast<Object*>(*it);
        auto sprite = static_cast<Sprite*>(obj);
        sprite->setVisible(false);
    }

    CC_PROFILER_STOP(this->profilerName());
}


std::string IterateSpriteSheetIterator::title()
{
    return "C - Iterate SpriteSheet";
}

std::string IterateSpriteSheetIterator::subtitle()
{
    return "Iterate children using begin() / end(). See console";
}

const char*  IterateSpriteSheetIterator::profilerName()
{
    return "Iterator: begin(), end()";
}

////////////////////////////////////////////////////////
//
// CallFuncsSpriteSheetForEach
//
////////////////////////////////////////////////////////
void CallFuncsSpriteSheetForEach::update(float dt)
{
    // iterate using fast enumeration protocol
    auto children = batchNode->getChildren();

    CC_PROFILER_START(this->profilerName());

    std::for_each(std::begin(*children), std::end(*children), [](Object* obj) {
        static_cast<Node*>(obj)->getPosition();
    });

    CC_PROFILER_STOP(this->profilerName());
}


std::string CallFuncsSpriteSheetForEach::title()
{
    return "D - 'map' functional call";
}

std::string CallFuncsSpriteSheetForEach::subtitle()
{
    return "Using 'std::for_each()'. See console";
}

const char*  CallFuncsSpriteSheetForEach::profilerName()
{
    static char _name[256];
    snprintf(_name, sizeof(_name)-1, "Map: std::for_each(%d)", quantityOfNodes);
    return _name;

}

////////////////////////////////////////////////////////
//
// CallFuncsSpriteSheetCMacro
//
////////////////////////////////////////////////////////
void CallFuncsSpriteSheetCMacro::update(float dt)
{
    // iterate using fast enumeration protocol
    auto children = batchNode->getChildren();

    CC_PROFILER_START(this->profilerName());

    arrayMakeObjectsPerformSelector(children, getPosition, Node*);

    CC_PROFILER_STOP(this->profilerName());
}


std::string CallFuncsSpriteSheetCMacro::title()
{
    return "E - 'map' functional call";
}

std::string CallFuncsSpriteSheetCMacro::subtitle()
{
    return "Using 'arrayMakeObjectsPerformSelector'. See console";
}

const char*  CallFuncsSpriteSheetCMacro::profilerName()
{
    static char _name[256];
    snprintf(_name, sizeof(_name)-1, "Map: arrayMakeObjectsPerformSelector(%d)", quantityOfNodes);
    return _name;
}
////////////////////////////////////////////////////////
//
// AddRemoveSpriteSheet
//
////////////////////////////////////////////////////////
AddRemoveSpriteSheet::~AddRemoveSpriteSheet()
{

}

void AddRemoveSpriteSheet::initWithQuantityOfNodes(unsigned int nNodes)
{
    batchNode = SpriteBatchNode::create("Images/spritesheet1.png");
    addChild(batchNode);

    NodeChildrenMainScene::initWithQuantityOfNodes(nNodes);

    scheduleUpdate();
}

void AddRemoveSpriteSheet::updateQuantityOfNodes()
{
    auto s = Director::getInstance()->getWinSize();

    // increase nodes
    if( currentQuantityOfNodes < quantityOfNodes )
    {
        for (int i=0; i < (quantityOfNodes-currentQuantityOfNodes); i++)
        {
            auto sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(0, 0, 32, 32));
            batchNode->addChild(sprite);
            sprite->setPosition(Point( CCRANDOM_0_1()*s.width, CCRANDOM_0_1()*s.height));
            sprite->setVisible(false);
        }
    }
    // decrease nodes
    else if ( currentQuantityOfNodes > quantityOfNodes )
    {
        for(int i=0;i < (currentQuantityOfNodes-quantityOfNodes);i++)
        {
            int index = currentQuantityOfNodes-i-1;
            batchNode->removeChildAtIndex(index, true);
        }
    }

    currentQuantityOfNodes = quantityOfNodes;
}

const char*  AddRemoveSpriteSheet::profilerName()
{
    return "none";
}

////////////////////////////////////////////////////////
//
// AddSpriteSheet
//
////////////////////////////////////////////////////////
void AddSpriteSheet::update(float dt)
{
    // reset seed
    //srandom(0);

    // 15 percent
    int totalToAdd = currentQuantityOfNodes * 0.15f;

    if( totalToAdd > 0 )
    {
        auto sprites = Array::createWithCapacity(totalToAdd);
        int *zs = new int[totalToAdd];

        // Don't include the sprite creation time and random as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            auto sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
            sprites->addObject(sprite);
            zs[i]      = CCRANDOM_MINUS1_1() * 50;
        }

        // add them with random Z (very important!)
        CC_PROFILER_START( this->profilerName() );

        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild((Node*) (sprites->getObjectAtIndex(i)), zs[i], kTagBase+i);
        }
        
        batchNode->sortAllChildren();
        
        CC_PROFILER_STOP(this->profilerName());

        // remove them
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChildByTag(kTagBase+i, true);
        }

        delete [] zs;
    }
}

std::string AddSpriteSheet::title()
{
    return "D - Add to spritesheet";
}

std::string AddSpriteSheet::subtitle()
{
    return "Adds %10 of total sprites with random z. See console";
}

const char*  AddSpriteSheet::profilerName()
{
    return "add sprites";
}

////////////////////////////////////////////////////////
//
// RemoveSpriteSheet
//
////////////////////////////////////////////////////////
void RemoveSpriteSheet::update(float dt)
{
    //srandom(0);

    // 15 percent
    int totalToAdd = currentQuantityOfNodes * 0.15f;

    if( totalToAdd > 0 )
    {
        auto sprites = Array::createWithCapacity(totalToAdd);

        // Don't include the sprite creation time as part of the profiling
        for(int i=0;i<totalToAdd;i++)
        {
            auto sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
            sprites->addObject(sprite);
        }

        // add them with random Z (very important!)
        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild((Node*) (sprites->getObjectAtIndex(i)), CCRANDOM_MINUS1_1() * 50, kTagBase+i);
        }

        // remove them
        CC_PROFILER_START( this->profilerName() );

        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChildByTag(kTagBase+i, true);
        }

        CC_PROFILER_STOP( this->profilerName() );
    }
}

std::string RemoveSpriteSheet::title()
{
    return "E - Del from spritesheet";
}

std::string RemoveSpriteSheet::subtitle()
{
    return "Remove %10 of total sprites placed randomly. See console";
}

const char*  RemoveSpriteSheet::profilerName()
{
    return "remove sprites";
}

////////////////////////////////////////////////////////
//
// ReorderSpriteSheet
//
////////////////////////////////////////////////////////
void ReorderSpriteSheet::update(float dt)
{
    //srandom(0);

    // 15 percent
    int totalToAdd = currentQuantityOfNodes * 0.15f;

    if( totalToAdd > 0 )
    {
        auto sprites = Array::createWithCapacity(totalToAdd);

        // Don't include the sprite creation time as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            auto sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
            sprites->addObject(sprite);
        }

        // add them with random Z (very important!)
        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild((Node*) (sprites->getObjectAtIndex(i)), CCRANDOM_MINUS1_1() * 50, kTagBase+i);
        }

        batchNode->sortAllChildren();

        // reorder them
        CC_PROFILER_START( this->profilerName() );

        for( int i=0;i <  totalToAdd;i++)
        {
            auto node = (Node*) (batchNode->getChildren()->getObjectAtIndex(i));
            batchNode->reorderChild(node, CCRANDOM_MINUS1_1() * 50);
        }
        
        batchNode->sortAllChildren();
        CC_PROFILER_STOP( this->profilerName() );

        // remove them
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChildByTag(kTagBase+i, true);
        }
    }
}

std::string ReorderSpriteSheet::title()
{
    return "F - Reorder from spritesheet";
}

std::string ReorderSpriteSheet::subtitle()
{
    return "Reorder %10 of total sprites placed randomly. See console";
}

const char*  ReorderSpriteSheet::profilerName()
{
    return "reorder sprites";
}

void runNodeChildrenTest()
{
    auto scene = createFunctions[g_curCase]();
    scene->initWithQuantityOfNodes(kNodesIncrease);

    Director::getInstance()->replaceScene(scene);
    scene->release();
}
