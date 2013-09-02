#include "PerformanceNodeChildrenTest.h"
#include <stdlib.h>

using namespace cocos2d;

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

enum {
    kTagInfoLayer = 1,
    kTagMainLayer = 2,
    kTagLabelAtlas = 3,

    kTagBase = 20000,

    TEST_COUNT = 10,
};

enum {
    kMaxNodes = 15000,
    kNodesIncrease = 500,
};

static int s_nCurCase = 0;

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
    CCDirector* director = CCDirector::sharedDirector();
    CCScheduler* sched = director->getScheduler();
    
    sched->unscheduleSelector(SEL_SCHEDULE(&NodeChildrenMenuLayer::dumpProfilerInfo), this);
}

void NodeChildrenMenuLayer::onEnterTransitionDidFinish()
{
    CCDirector* director = CCDirector::sharedDirector();
    CCScheduler* sched = director->getScheduler();
    
    CC_PROFILER_PURGE_ALL();
    sched->scheduleSelector(SEL_SCHEDULE(&NodeChildrenMenuLayer::dumpProfilerInfo), this, 2, false);
}

void NodeChildrenMenuLayer::dumpProfilerInfo(float dt)
{
	CC_PROFILER_DISPLAY_TIMERS();
}

void NodeChildrenMenuLayer::showCurrentTest()
{
    int nNodes = ((NodeChildrenMainScene*)getParent())->getQuantityOfNodes();
    NodeChildrenMainScene* pScene = NULL;

    switch (m_nCurCase)
    {
        //case 0:
        //    pScene = new IterateSpriteSheetFastEnum();
        //    break;
        case 0:
            pScene = new IterateSpriteSheetCArray();
            break;
        case 1:
            pScene = new CallFuncsSpriteSheetCMacro();
            break;
        case 2:
            pScene = new AddSprite();
            break;
        case 3:
            pScene = new AddSpriteSheet();
            break;
        case 4:
            pScene = new GetSpriteSheet();
            break;
        case 5:
            pScene = new RemoveSprite();
            break;
        case 6:
            pScene = new RemoveSpriteSheet();
            break;
        case 7:
            pScene = new ReorderSpriteSheet();
            break;
        case 8:
            pScene = new SortAllChildrenSpriteSheet();
            break;
        case 9:
            pScene = new VisitSceneGraph();
            break;
    }
    s_nCurCase = m_nCurCase;

    if (pScene)
    {
        pScene->initWithQuantityOfNodes(nNodes);

        CCDirector::sharedDirector()->replaceScene(pScene);
        pScene->release();
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
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // Title
    CCLabelTTF *label = CCLabelTTF::create(title().c_str(), "Arial", 28);
    addChild(label, 1);
    label->setPosition(ccp(s.width/2, s.height-40));
    label->setColor(ccc3(255,255,40));

    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        CCLabelTTF *l = CCLabelTTF::create(strSubTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(ccp(s.width/2, s.height-80));
    }

    lastRenderedCount = 0;
    currentQuantityOfNodes = 0;
    quantityOfNodes = nNodes;

    CCMenuItemFont::setFontSize(65);
    CCMenuItemFont *decrease = CCMenuItemFont::create(" - ", this, menu_selector(NodeChildrenMainScene::onDecrease));
    decrease->setColor(ccc3(0,200,20));
    CCMenuItemFont *increase = CCMenuItemFont::create(" + ", this, menu_selector(NodeChildrenMainScene::onIncrease));
    increase->setColor(ccc3(0,200,20));

    CCMenu *menu = CCMenu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(ccp(s.width/2, s.height/2+15));
    addChild(menu, 1);

    CCLabelTTF *infoLabel = CCLabelTTF::create("0 nodes", "Marker Felt", 30);
    infoLabel->setColor(ccc3(0,200,20));
    infoLabel->setPosition(ccp(s.width/2, s.height/2-15));
    addChild(infoLabel, 1, kTagInfoLayer);

    NodeChildrenMenuLayer* pMenu = new NodeChildrenMenuLayer(true, TEST_COUNT, s_nCurCase);
    addChild(pMenu);
    pMenu->release();

    updateQuantityLabel();
    updateQuantityOfNodes();
    updateProfilerName();
    srand(0);

    CC_PROFILER_PURGE_ALL();
}

void NodeChildrenMainScene::onDecrease(CCObject* pSender)
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

void NodeChildrenMainScene::onIncrease(CCObject* pSender)
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
        CCLabelTTF *infoLabel = (CCLabelTTF *) getChildByTag(kTagInfoLayer);
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
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // increase nodes
    if( currentQuantityOfNodes < quantityOfNodes )
    {
        for(int i = 0; i < (quantityOfNodes-currentQuantityOfNodes); i++)
        {
            CCSprite *sprite = CCSprite::createWithTexture(batchNode->getTexture(), CCRectMake(0, 0, 32, 32));
            batchNode->addChild(sprite);
            sprite->setVisible(false);
            sprite->setPosition(ccp( CCRANDOM_0_1()*s.width, CCRANDOM_0_1()*s.height));
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
    batchNode = CCSpriteBatchNode::create("Images/spritesheet1.png");
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
// IterateSpriteSheetFastEnum
//
////////////////////////////////////////////////////////
void IterateSpriteSheetFastEnum::update(float dt)
{
    // iterate using fast enumeration protocol
    CCArray* pChildren = batchNode->getChildren();
    CCObject* pObject = NULL;

    CC_PROFILER_START(this->profilerName());

    CCARRAY_FOREACH(pChildren, pObject)
    {
        CCSprite* pSprite = (CCSprite*) pObject;
        pSprite->setVisible(false);
    }

    CC_PROFILER_STOP(this->profilerName());
}

std::string IterateSpriteSheetFastEnum::title()
{
    return "A - Iterate SpriteSheet";
}

std::string IterateSpriteSheetFastEnum::subtitle()
{
    return "Iterate children using Fast Enum API. See console";
}

const char*  IterateSpriteSheetFastEnum::testName()
{
    return "iter fast enum";
}

////////////////////////////////////////////////////////
//
// IterateSpriteSheetCArray
//
////////////////////////////////////////////////////////
void IterateSpriteSheetCArray::update(float dt)
{
    // iterate using fast enumeration protocol
    CCArray* pChildren = batchNode->getChildren();
    CCObject* pObject = NULL;

    CC_PROFILER_START(this->profilerName());

    CCARRAY_FOREACH(pChildren, pObject)
    {
        CCSprite* pSprite = (CCSprite*)pObject;
        pSprite->setVisible(false);
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

const char*  IterateSpriteSheetCArray::testName()
{
    return "CC_ARRAY_FOREACH";
}


////////////////////////////////////////////////////////
//
// CallFuncsSpriteSheetCMacro
//
////////////////////////////////////////////////////////
void CallFuncsSpriteSheetCMacro::update(float dt)
{
    // iterate using fast enumeration protocol
    CCArray* pChildren = batchNode->getChildren();
    
    CC_PROFILER_START(this->profilerName());
    
    arrayMakeObjectsPerformSelector(pChildren, getPosition, CCNode*);
    
    CC_PROFILER_STOP(this->profilerName());
}


std::string CallFuncsSpriteSheetCMacro::title()
{
    return "C - 'map' functional call";
}

std::string CallFuncsSpriteSheetCMacro::subtitle()
{
    return "Using 'arrayMakeObjectsPerformSelector'. See console";
}

const char*  CallFuncsSpriteSheetCMacro::testName()
{
    return "Map: arrayMakeObjectsPerformSelector";
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
    batchNode = CCSpriteBatchNode::create("Images/spritesheet1.png");
    addChild(batchNode);

    NodeChildrenMainScene::initWithQuantityOfNodes(nNodes);

    scheduleUpdate();
}

void AddRemoveSpriteSheet::updateQuantityOfNodes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // increase nodes
    if( currentQuantityOfNodes < quantityOfNodes )
    {
        for (int i=0; i < (quantityOfNodes-currentQuantityOfNodes); i++)
        {
            CCSprite *sprite = CCSprite::createWithTexture(batchNode->getTexture(), CCRectMake(0, 0, 32, 32));
            batchNode->addChild(sprite);
            sprite->setPosition(ccp( CCRANDOM_0_1()*s.width, CCRANDOM_0_1()*s.height));
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
// GetSpriteSheet
//
////////////////////////////////////////////////////////
void GetSpriteSheet::update(float dt)
{
    // reset seed
    //srand(0);
    
    // 100% percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        CCSprite **sprites = new CCSprite*[totalToAdd];
        int *zs = new int[totalToAdd];

        // Don't include the sprite creation time and random as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            sprites[i] = CCSprite::createWithTexture(batchNode->getTexture(), CCRect(0,0,32,32));
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

std::string GetSpriteSheet::title()
{
    return "SpriteBatchNode::getChildByTag()";
}

std::string GetSpriteSheet::subtitle()
{
    return "Get sprites using getChildByTag(). See console";
}

const char*  GetSpriteSheet::testName()
{
    return "SpriteBatchNode::getChildByTag()";
}

////////////////////////////////////////////////////////
//
// AddSprite
//
////////////////////////////////////////////////////////
void AddSprite::update(float dt)
{
    // reset seed
    //srand(0);

    // 100 percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        CCSprite **sprites = new CCSprite*[totalToAdd];
        int *zs = new int[totalToAdd];

        // Don't include the sprite creation time and random as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            sprites[i] = CCSprite::createWithTexture(batchNode->getTexture(), CCRect(0,0,32,32));
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

std::string AddSprite::title()
{
    return "Node::addChild()";
}

std::string AddSprite::subtitle()
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
    //srand(0);

    // 100 percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        CCSprite **sprites = new CCSprite*[totalToAdd];
        int *zs = new int[totalToAdd];

        // Don't include the sprite creation time and random as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            sprites[i] = CCSprite::createWithTexture(batchNode->getTexture(), CCRect(0,0,32,32));
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
    }}

std::string AddSpriteSheet::title()
{
    return "SpriteBatchNode::addChild()";
}

std::string AddSpriteSheet::subtitle()
{
    return "Adds sprites with random z. See console";
}

const char*  AddSpriteSheet::testName()
{
    return "SpriteBatchNode::addChild()";
}

////////////////////////////////////////////////////////
//
// RemoveSprite
//
////////////////////////////////////////////////////////
void RemoveSprite::update(float dt)
{
    //srand(0);

    // 100 percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        CCSprite **sprites = new CCSprite*[totalToAdd];

        // Don't include the sprite creation time as part of the profiling
        for(int i=0;i<totalToAdd;i++)
        {
            sprites[i] = CCSprite::createWithTexture(batchNode->getTexture(), CCRect(0,0,32,32));
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
    }}

std::string RemoveSprite::title()
{
    return "Node::removeChild()";
}

std::string RemoveSprite::subtitle()
{
    return "Removes sprites placed randomly. See console";
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
    //srand(0);

    // 100 percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        CCSprite **sprites = new CCSprite*[totalToAdd];

        // Don't include the sprite creation time as part of the profiling
        for(int i=0;i<totalToAdd;i++)
        {
            sprites[i] = CCSprite::createWithTexture(batchNode->getTexture(), CCRect(0,0,32,32));
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
    }}

std::string RemoveSpriteSheet::title()
{
    return "SpriteBatchNode::removeChild()";
}

std::string RemoveSpriteSheet::subtitle()
{
    return "Removes sprites placed randomly. See console";
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
    //srand(0);

    // 100 percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        CCSprite **sprites = new CCSprite*[totalToAdd];

        // Don't include the sprite creation time as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            sprites[i] = CCSprite::createWithTexture(batchNode->getTexture(), CCRect(0,0,32,32));
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

std::string ReorderSpriteSheet::title()
{
    return "G - Reorder from spritesheet";
}

std::string ReorderSpriteSheet::subtitle()
{
    return "Reorder %10 of total sprites placed randomly. See console";
}

const char*  ReorderSpriteSheet::testName()
{
    return "SpriteBatchNode::reorderChild()";
}

void runNodeChildrenTest()
{
    IterateSpriteSheet* pScene = new IterateSpriteSheetCArray();
    pScene->initWithQuantityOfNodes(kNodesIncrease);

    CCDirector::sharedDirector()->replaceScene(pScene);
    pScene->release();
}



////////////////////////////////////////////////////////
//
// SortAllChildrenSpriteSheet
//
////////////////////////////////////////////////////////
void SortAllChildrenSpriteSheet::update(float dt)
{
    //srand(0);
    
    // 100 percent
    int totalToAdd = currentQuantityOfNodes * 1;

    if( totalToAdd > 0 )
    {
        CCSprite **sprites = new CCSprite*[totalToAdd];

        // Don't include the sprite's creation time as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            sprites[i] = CCSprite::createWithTexture(batchNode->getTexture(), CCRect(0,0,32,32));
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

std::string SortAllChildrenSpriteSheet::title()
{
    return "H - Sort All Children from spritesheet";
}

std::string SortAllChildrenSpriteSheet::subtitle()
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
    // increase nodes
    if( currentQuantityOfNodes < quantityOfNodes )
    {
        for(int i = 0; i < (quantityOfNodes-currentQuantityOfNodes); i++)
        {
            CCNode * node = CCNode::create();
            this->addChild(node);
            node->setVisible(true);
            node->setPosition(CCPoint(-1000,-1000));
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
}

std::string VisitSceneGraph::title()
{
    return "Performance of visiting the scene graph";
}

std::string VisitSceneGraph::subtitle()
{
    return "calls visit() on scene graph. See console";
}

const char*  VisitSceneGraph::testName()
{
    return "visit()";
}
