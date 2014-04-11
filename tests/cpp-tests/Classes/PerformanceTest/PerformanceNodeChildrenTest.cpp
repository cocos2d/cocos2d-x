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
    CL(IterateSpriteSheetIterator),
    CL(IterateSpriteSheetForEach),

    CL(CallFuncsSpriteSheetForEach),

    CL(AddSprite),
    CL(AddSpriteSheet),
    CL(GetSpriteSheet),
    CL(RemoveSprite),
    CL(RemoveSpriteSheet),
    CL(ReorderSpriteSheet),
    CL(SortAllChildrenSpriteSheet),

    CL(VisitSceneGraph),
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

    sched->unschedule(schedule_selector(NodeChildrenMenuLayer::dumpProfilerInfo), this);
}

void NodeChildrenMenuLayer::onEnterTransitionDidFinish()
{
    auto director = Director::getInstance();
    auto sched = director->getScheduler();

    CC_PROFILER_PURGE_ALL();
    sched->schedule(schedule_selector(NodeChildrenMenuLayer::dumpProfilerInfo), this, 2, false);
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
    auto label = Label::createWithTTF(title().c_str(), "fonts/arial.ttf", 32);
    addChild(label, 1);
    label->setPosition(Point(s.width/2, s.height-50));

    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        auto l = Label::createWithTTF(strSubTitle.c_str(), "fonts/Thonburi.ttf", 16);
        addChild(l, 1);
        l->setPosition(Point(s.width/2, s.height-80));
    }

    lastRenderedCount = 0;
    currentQuantityOfNodes = 0;
    quantityOfNodes = nNodes;

    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", [&](Ref *sender) {
		quantityOfNodes -= kNodesIncrease;
		if( quantityOfNodes < 0 )
			quantityOfNodes = 0;

		updateQuantityLabel();
		updateQuantityOfNodes();
        updateProfilerName();
        CC_PROFILER_PURGE_ALL();
        srand(0);
	});
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", [&](Ref *sender) {
		quantityOfNodes += kNodesIncrease;
		if( quantityOfNodes > kMaxNodes )
			quantityOfNodes = kMaxNodes;

		updateQuantityLabel();
		updateQuantityOfNodes();
        updateProfilerName();
        CC_PROFILER_PURGE_ALL();
        srand(0);        
	});
    increase->setColor(Color3B(0,200,20));

    auto menu = Menu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(Point(s.width/2, s.height/2+15));
    addChild(menu, 1);

    auto infoLabel = Label::createWithTTF("0 nodes", "fonts/Marker Felt.ttf", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Point(s.width/2, s.height/2-15));
    addChild(infoLabel, 1, kTagInfoLayer);

    auto menuLayer = new NodeChildrenMenuLayer(true, MAX_LAYER, g_curCase);
    addChild(menuLayer);
    menuLayer->release();

    updateQuantityLabel();
    updateQuantityOfNodes();
    updateProfilerName();
    srand(0);
}

std::string NodeChildrenMainScene::title() const
{
    return "No title";
}

std::string NodeChildrenMainScene::subtitle() const
{
    return "";
}

void NodeChildrenMainScene::updateQuantityLabel()
{
    if( quantityOfNodes != lastRenderedCount )
    {
        auto infoLabel = static_cast<Label*>( getChildByTag(kTagInfoLayer) );
        char str[20] = {0};
        sprintf(str, "%u nodes", quantityOfNodes);
        infoLabel->setString(str);

        lastRenderedCount = quantityOfNodes;
    }
}

const char * NodeChildrenMainScene::profilerName()
{
    return _profilerName;
}

void NodeChildrenMainScene::updateProfilerName()
{
    snprintf(_profilerName, sizeof(_profilerName)-1, "%s(%d)", testName(), quantityOfNodes);
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

const char*  IterateSpriteSheet::testName()
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
    auto& children = batchNode->getChildren();

    CC_PROFILER_START(this->profilerName());

    for( const auto &object : children )
    {
        auto o = static_cast<Ref*>(object);
        auto sprite = static_cast<Sprite*>(o);
        sprite->setVisible(false);
    }

    CC_PROFILER_STOP(this->profilerName());
}

std::string IterateSpriteSheetForLoop::title() const
{
    return "Iterate SpriteSheet";
}

std::string IterateSpriteSheetForLoop::subtitle() const
{
    return "Iterate children using C++11 range-based for loop. See console";
}

const char*  IterateSpriteSheetForLoop::testName()
{
    return "Iterator: C++11 for loop";
}


////////////////////////////////////////////////////////
//
// IterateSpriteSheetIterator
//
////////////////////////////////////////////////////////
void IterateSpriteSheetIterator::update(float dt)
{
    // iterate using fast enumeration protocol
    auto& children = batchNode->getChildren();

    CC_PROFILER_START(this->profilerName());

    for( auto it=std::begin(children); it != std::end(children); ++it)
    {
        auto sprite = static_cast<Sprite*>(*it);
        sprite->setVisible(false);
    }

    CC_PROFILER_STOP(this->profilerName());
}


std::string IterateSpriteSheetIterator::title() const
{
    return "Iterate SpriteSheet";
}

std::string IterateSpriteSheetIterator::subtitle() const
{
    return "Iterate children using begin() / end(). See console";
}

const char*  IterateSpriteSheetIterator::testName()
{
    return "Iterator: begin(), end()";
}

////////////////////////////////////////////////////////
//
// IterateSpriteSheetForEach
//
////////////////////////////////////////////////////////
void IterateSpriteSheetForEach::update(float dt)
{
    // iterate using fast enumeration protocol
    auto& children = batchNode->getChildren();

    CC_PROFILER_START(this->profilerName());

    std::for_each(std::begin(children), std::end(children), [](Node *child) {
        auto sprite = static_cast<Sprite*>(child);
        sprite->setVisible(false);
    });

    CC_PROFILER_STOP(this->profilerName());
}


std::string IterateSpriteSheetForEach::title() const
{
    return "Iterate SpriteSheet";
}

std::string IterateSpriteSheetForEach::subtitle() const
{
    return "Iterate children using std::for_each(). See console";
}

const char*  IterateSpriteSheetForEach::testName()
{
    return "Iterator: std::for_each()";
}


////////////////////////////////////////////////////////
//
// CallFuncsSpriteSheetForEach
//
////////////////////////////////////////////////////////
void CallFuncsSpriteSheetForEach::update(float dt)
{
    // iterate using fast enumeration protocol
    auto& children = batchNode->getChildren();

    CC_PROFILER_START(this->profilerName());

    std::for_each(std::begin(children), std::end(children), [](Node* obj) {
        obj->getPosition();
    });

    CC_PROFILER_STOP(this->profilerName());
}


std::string CallFuncsSpriteSheetForEach::title() const
{
    return "'map' functional call";
}

std::string CallFuncsSpriteSheetForEach::subtitle() const
{
    return "Using 'std::for_each()'. See console";
}

const char*  CallFuncsSpriteSheetForEach::testName()
{
    return "Map: std::for_each";
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

const char*  AddRemoveSpriteSheet::testName()
{
    return "none";
}

////////////////////////////////////////////////////////
//
// AddSprite
//
////////////////////////////////////////////////////////
void AddSprite::update(float dt)
{
    // reset seed
    //srandom(0);

    // 100 percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        Sprite **sprites = new Sprite*[totalToAdd];
        int *zs = new int[totalToAdd];

        // Don't include the sprite creation time and random as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            sprites[i] = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
            zs[i] = CCRANDOM_MINUS1_1() * 50;
        }

        // add them with random Z (very important!)
        CC_PROFILER_START( this->profilerName() );

        for( int i=0; i < totalToAdd;i++ )
        {
            this->addChild( sprites[i], zs[i], kTagBase+i);
        }
        CC_PROFILER_STOP(this->profilerName());


        batchNode->sortAllChildren();

        // remove them
        for( int i=0;i <  totalToAdd;i++)
        {
            this->removeChild( sprites[i], true);
        }

        delete [] sprites;
        delete [] zs;
    }
}

std::string AddSprite::title() const
{
    return "Node::addChild()";
}

std::string AddSprite::subtitle() const
{
    return "Adds sprites with random z. See console";
}

const char*  AddSprite::testName()
{
    return "Node::addChild()";
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

    // 100 percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        Sprite **sprites = new Sprite*[totalToAdd];
        int *zs = new int[totalToAdd];

        // Don't include the sprite creation time and random as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            sprites[i] = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
            zs[i] = CCRANDOM_MINUS1_1() * 50;
        }

        // add them with random Z (very important!)
        CC_PROFILER_START( this->profilerName() );

        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild( sprites[i], zs[i], kTagBase+i);
        }
        CC_PROFILER_STOP(this->profilerName());


        batchNode->sortAllChildren();

        // remove them
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChild( sprites[i], true);
        }

        delete [] sprites;
        delete [] zs;
    }
}

std::string AddSpriteSheet::title() const
{
    return "SpriteBatchNode::addChild()";
}

std::string AddSpriteSheet::subtitle() const
{
    return "Adds sprites with random z. See console";
}

const char*  AddSpriteSheet::testName()
{
    return "SpriteBatchNode::addChild()";
}

////////////////////////////////////////////////////////
//
// GetSpriteSheet
//
////////////////////////////////////////////////////////
void GetSpriteSheet::update(float dt)
{
    // reset seed
    //srandom(0);

    // 100% percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        Sprite **sprites = new Sprite*[totalToAdd];
        int *zs = new int[totalToAdd];

        // Don't include the sprite creation time and random as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            sprites[i] = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
            zs[i]      = CCRANDOM_MINUS1_1() * 50;
        }

        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild( sprites[i], zs[i], kTagBase+i);
        }

        batchNode->sortAllChildren();

        CC_PROFILER_START( this->profilerName() );
        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->getChildByTag(kTagBase+1);
        }
        CC_PROFILER_STOP(this->profilerName());

        // remove them
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChild( sprites[i], true);
        }

        delete [] sprites;
        delete [] zs;
    }
}

std::string GetSpriteSheet::title() const
{
    return "getChildByTag from spritesheet";
}

std::string GetSpriteSheet::subtitle() const
{
    return "Get sprites using getChildByTag(). See console";
}

const char*  GetSpriteSheet::testName()
{
    return "SpriteBatchNode::getChildByTag()";
}


////////////////////////////////////////////////////////
//
// RemoveSprite
//
////////////////////////////////////////////////////////
void RemoveSprite::update(float dt)
{
    //srandom(0);

    // 100 percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        Sprite **sprites = new Sprite*[totalToAdd];

        // Don't include the sprite creation time as part of the profiling
        for(int i=0;i<totalToAdd;i++)
        {
            sprites[i] = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
        }

        // add them with random Z (very important!)
        for( int i=0; i < totalToAdd;i++ )
        {
            this->addChild( sprites[i], CCRANDOM_MINUS1_1() * 50, kTagBase+i);
        }

        // remove them
        CC_PROFILER_START( this->profilerName() );
        for( int i=0;i <  totalToAdd;i++)
        {
            this->removeChild( sprites[i], true);
        }
        CC_PROFILER_STOP( this->profilerName() );

        delete [] sprites;
    }
}

std::string RemoveSprite::title() const
{
    return "Node::removeChild()";
}

std::string RemoveSprite::subtitle() const
{
    return "Remove sprites. See console";
}

const char*  RemoveSprite::testName()
{
    return "Node::removeChild()";
}

////////////////////////////////////////////////////////
//
// RemoveSpriteSheet
//
////////////////////////////////////////////////////////
void RemoveSpriteSheet::update(float dt)
{
    //srandom(0);

    // 100 percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        Sprite **sprites = new Sprite*[totalToAdd];

        // Don't include the sprite creation time as part of the profiling
        for(int i=0;i<totalToAdd;i++)
        {
            sprites[i] = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
        }

        // add them with random Z (very important!)
        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild( sprites[i], CCRANDOM_MINUS1_1() * 50, kTagBase+i);
        }

        // remove them
        CC_PROFILER_START( this->profilerName() );
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChild( sprites[i], true);
        }
        CC_PROFILER_STOP( this->profilerName() );

        delete [] sprites;
    }
}

std::string RemoveSpriteSheet::title() const
{
    return "SpriteBatchNode::removeChild()";
}

std::string RemoveSpriteSheet::subtitle() const
{
    return "Remove sprites. See console";
}

const char*  RemoveSpriteSheet::testName()
{
    return "SpriteBatchNode::removeChild()";
}

////////////////////////////////////////////////////////
//
// ReorderSpriteSheet
//
////////////////////////////////////////////////////////
void ReorderSpriteSheet::update(float dt)
{
    //srandom(0);

    // 100 percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        Sprite **sprites = new Sprite*[totalToAdd];

        // Don't include the sprite creation time as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            sprites[i] = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
        }

        // add them with random Z (very important!)
        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild( sprites[i], CCRANDOM_MINUS1_1() * 50, kTagBase+i);
        }

        batchNode->sortAllChildren();

        // reorder them
        CC_PROFILER_START( this->profilerName() );
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->reorderChild(sprites[i], CCRANDOM_MINUS1_1() * 50);
        }
        CC_PROFILER_STOP( this->profilerName() );

        // remove them
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChild( sprites[i], true);
        }

        delete [] sprites;
    }
}

std::string ReorderSpriteSheet::title() const
{
    return "SpriteBatchNode::reorderChild()";
}

std::string ReorderSpriteSheet::subtitle() const
{
    return "Reorder sprites. See console";
}

const char*  ReorderSpriteSheet::testName()
{
    return "SpriteBatchNode::reorderChild()";
}

////////////////////////////////////////////////////////
//
// SortAllChildrenSpriteSheet
//
////////////////////////////////////////////////////////
void SortAllChildrenSpriteSheet::update(float dt)
{
    //srandom(0);

    // 100 percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        Sprite **sprites = new Sprite*[totalToAdd];

        // Don't include the sprite's creation time as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            sprites[i] = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
        }

        // add them with random Z (very important!)
        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild( sprites[i], CCRANDOM_MINUS1_1() * 50, kTagBase+i);
        }

        batchNode->sortAllChildren();

        // reorder them
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->reorderChild(sprites[i], CCRANDOM_MINUS1_1() * 50);
        }

        CC_PROFILER_START( this->profilerName() );
        batchNode->sortAllChildren();
        CC_PROFILER_STOP( this->profilerName() );

        // remove them
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChild( sprites[i], true);
        }

        delete [] sprites;
    }
}

std::string SortAllChildrenSpriteSheet::title() const
{
    return "SpriteBatchNode::sortAllChildren()";
}

std::string SortAllChildrenSpriteSheet::subtitle() const
{
    return "Calls sortOfChildren(). See console";
}

const char*  SortAllChildrenSpriteSheet::testName()
{
    return "SpriteBatchNode::sortAllChildren()";
}


////////////////////////////////////////////////////////
//
// VisitSceneGraph
//
////////////////////////////////////////////////////////
void VisitSceneGraph::initWithQuantityOfNodes(unsigned int nodes)
{
    NodeChildrenMainScene::initWithQuantityOfNodes(nodes);
    scheduleUpdate();
}

void VisitSceneGraph::updateQuantityOfNodes()
{
    auto s = Director::getInstance()->getWinSize();

    // increase nodes
    if( currentQuantityOfNodes < quantityOfNodes )
    {
        for(int i = 0; i < (quantityOfNodes-currentQuantityOfNodes); i++)
        {
            auto node = Node::create();
            this->addChild(node);
            node->setVisible(true);
            node->setPosition(Point(-1000,-1000));
            node->setTag(1000 + currentQuantityOfNodes + i );
        }
    }

    // decrease nodes
    else if ( currentQuantityOfNodes > quantityOfNodes )
    {
        for(int i = 0; i < (currentQuantityOfNodes-quantityOfNodes); i++)
        {
            this->removeChildByTag(1000 + currentQuantityOfNodes - i -1 );
        }
    }

    currentQuantityOfNodes = quantityOfNodes;
}
void VisitSceneGraph::update(float dt)
{
    CC_PROFILER_START( this->profilerName() );
    this->visit();
    CC_PROFILER_STOP( this->profilerName() );

    // Call `Renderer::clean` to prevent crash if current scene is destroyed.
    // The render commands associated with current scene should be cleaned.
    Director::getInstance()->getRenderer()->clean();
}

std::string VisitSceneGraph::title() const
{
    return "Performance of visiting the scene graph";
}

std::string VisitSceneGraph::subtitle() const
{
    return "calls visit() on scene graph. See console";
}

const char*  VisitSceneGraph::testName()
{
    return "visit()";
}

///----------------------------------------
void runNodeChildrenTest()
{
    auto scene = createFunctions[g_curCase]();
    scene->initWithQuantityOfNodes(kNodesIncrease);

    Director::getInstance()->replaceScene(scene);
}
