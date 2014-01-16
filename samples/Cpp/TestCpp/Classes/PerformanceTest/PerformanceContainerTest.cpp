/*
 *
 */
#include "PerformanceContainerTest.h"

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

static std::function<PerformanceContainerScene*()> createFunctions[] =
{
    CL(TemplateVectorPerfTest),
    CL(ArrayPerfTest)
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
// ContainerBasicLayer
//
////////////////////////////////////////////////////////

ContainerBasicLayer::ContainerBasicLayer(bool bControlMenuVisible, int nMaxCases, int nCurCase)
: PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
{
}

void ContainerBasicLayer::showCurrentTest()
{
    int nodes = ((PerformanceContainerScene*)getParent())->getQuantityOfNodes();

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
// PerformanceContainerScene
//
////////////////////////////////////////////////////////
void PerformanceContainerScene::initWithQuantityOfNodes(unsigned int nNodes)
{
    _type = 0;
    //srand(time());
    auto s = Director::getInstance()->getWinSize();

    // Title
    auto label = LabelTTF::create(title().c_str(), "Arial", 40);
    addChild(label, 1, TAG_TITLE);
    label->setPosition(Point(s.width/2, s.height-32));
    label->setColor(Color3B(255,255,40));

    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        auto l = LabelTTF::create(strSubTitle.c_str(), "Thonburi", 16);
        addChild(l, 1, TAG_SUBTITLE);
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
        updateProfilerName();
        CC_PROFILER_PURGE_ALL();
        srand(0);
	});
    decrease->setColor(Color3B(0,200,20));
    _decrease = decrease;
    
    auto increase = MenuItemFont::create(" + ", [&](Object *sender) {
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
    _increase = increase;

    auto menu = Menu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(Point(s.width/2, s.height/2+15));
    addChild(menu, 1);

    auto infoLabel = LabelTTF::create("0 nodes", "Marker Felt", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Point(s.width/2, s.height/2-15));
    addChild(infoLabel, 1, kTagInfoLayer);

    auto menuLayer = new ContainerBasicLayer(true, MAX_LAYER, g_curCase);
    addChild(menuLayer);
    menuLayer->release();

    printf("Size of Node: %lu\n", sizeof(Node));
    
    int oldFontSize = MenuItemFont::getFontSize();
    MenuItemFont::setFontSize(24);
    
    Vector<cocos2d::MenuItem *> toggleItems;
    
    generateTestFunctions();
    
    CCASSERT(!_testFunctions.empty(), "Should not be empty after generate test functions");

    
    for (const auto& f : _testFunctions)
    {
        toggleItems.pushBack(MenuItemFont::create(f.name));
    }
    
    auto toggle = MenuItemToggle::createWithCallback([this](Object* sender){
        auto toggle = static_cast<MenuItemToggle*>(sender);
        this->_type = toggle->getSelectedIndex();
        auto label = static_cast<LabelTTF*>(this->getChildByTag(TAG_SUBTITLE));
        label->setString(StringUtils::format("Test '%s', See console", this->_testFunctions[this->_type].name));
        this->updateProfilerName();
    }, toggleItems);
    
    toggle->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    toggle->setPosition(VisibleRect::left());
    _toggle = toggle;
    
    auto start = MenuItemFont::create("start", [this](Object* sender){
        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        
        CC_PROFILER_PURGE_ALL();
        sched->scheduleSelector(schedule_selector(PerformanceContainerScene::dumpProfilerInfo), this, 2, false);
        
        this->unscheduleUpdate();
        this->scheduleUpdate();
        this->_startItem->setEnabled(false);
        this->_stopItem->setEnabled(true);
        this->_toggle->setEnabled(false);
        this->_increase->setEnabled(false);
        this->_decrease->setEnabled(false);
    });
    start->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    start->setPosition(VisibleRect::right() + Point(0, 40));
    _startItem = start;
    
    auto stop = MenuItemFont::create("stop", [this](Object* sender){
        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        
        sched->unscheduleSelector(schedule_selector(PerformanceContainerScene::dumpProfilerInfo), this);
        
        this->unscheduleUpdate();
        this->_startItem->setEnabled(true);
        this->_stopItem->setEnabled(false);
        this->_toggle->setEnabled(true);
        this->_increase->setEnabled(true);
        this->_decrease->setEnabled(true);
    });
    
    stop->setEnabled(false);
    stop->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    stop->setPosition(VisibleRect::right() + Point(0, -40));
    _stopItem = stop;
    
    auto menu2 = Menu::create(toggle, start, stop, NULL);
    menu2->setPosition(Point::ZERO);
    addChild(menu2);
    
    MenuItemFont::setFontSize(oldFontSize);

    updateQuantityLabel();
    updateQuantityOfNodes();
    updateProfilerName();
}

std::string PerformanceContainerScene::title() const
{
    return "No title";
}

std::string PerformanceContainerScene::subtitle() const
{
    return "";
}

void PerformanceContainerScene::updateQuantityLabel()
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

const char * PerformanceContainerScene::profilerName()
{
    return _profilerName;
}

void PerformanceContainerScene::updateProfilerName()
{
    snprintf(_profilerName, sizeof(_profilerName)-1, "%s(%d)", testName(), quantityOfNodes);
}

void PerformanceContainerScene::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
    
    auto director = Director::getInstance();
    auto sched = director->getScheduler();

    sched->unscheduleSelector(schedule_selector(PerformanceContainerScene::dumpProfilerInfo), this);
}

void PerformanceContainerScene::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();

    auto director = Director::getInstance();
    auto sched = director->getScheduler();

    CC_PROFILER_PURGE_ALL();
    sched->scheduleSelector(schedule_selector(PerformanceContainerScene::dumpProfilerInfo), this, 2, false);
}

void PerformanceContainerScene::dumpProfilerInfo(float dt)
{
	CC_PROFILER_DISPLAY_TIMERS();
}

void PerformanceContainerScene::update(float dt)
{
    _testFunctions[_type].func();
}

void PerformanceContainerScene::updateQuantityOfNodes()
{
    currentQuantityOfNodes = quantityOfNodes;
}

const char*  PerformanceContainerScene::testName()
{
    return _testFunctions[_type].name;
}

////////////////////////////////////////////////////////
//
// TemplateVectorPerfTest
//
////////////////////////////////////////////////////////

void TemplateVectorPerfTest::generateTestFunctions()
{
    auto createVector = [this](){
        Vector<Node*> ret;
        
        for( int i=0; i<quantityOfNodes; ++i)
        {
            auto node = Node::create();
            node->setTag(i);
            ret.pushBack(node);
        }
        return ret;
    };
    
    TestFunction nameCBs[] = {
        { "pushBack",    [=](){
            Vector<Node*> nodeVector;
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector.pushBack(Node::create());
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "insert",      [=](){
            Vector<Node*> nodeVector;
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector.insert(0, Node::create());
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "replace",     [=](){
            Vector<Node*> nodeVector = createVector();
            
            srand(time(nullptr));
            ssize_t index = rand() % quantityOfNodes;
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector.replace(index, Node::create());
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "getIndex",    [=](){
            
            Vector<Node*> nodeVector = createVector();
            Node* objToGet = nodeVector.at(quantityOfNodes/3);
            ssize_t index = 0;
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                index = nodeVector.getIndex(objToGet);
            CC_PROFILER_STOP(this->profilerName());
            
            // Uses `index` to avoids `getIndex` invoking was optimized in release mode
            if (index == quantityOfNodes/3)
            {
                nodeVector.clear();
            }
        } } ,
        { "find",        [=](){
            Vector<Node*> nodeVector = createVector();
            Node* objToGet = nodeVector.at(quantityOfNodes/3);
            Vector<Node*>::iterator iter;
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                iter = nodeVector.find(objToGet);
            CC_PROFILER_STOP(this->profilerName());
            
            // Uses `iter` to avoids `find` invoking was optimized in release mode
            if (*iter == objToGet)
            {
                nodeVector.clear();
            }
            
        } } ,
        { "at",          [=](){
            Vector<Node*> nodeVector = createVector();
            Node* objToGet = nullptr;
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                objToGet = nodeVector.at(quantityOfNodes/3);
            CC_PROFILER_STOP(this->profilerName());
            
            // Uses `objToGet` to avoids `at` invoking was optimized in release mode
            if (nodeVector.getIndex(objToGet) == quantityOfNodes/3)
            {
                nodeVector.clear();
            }
        } } ,
        { "contains",    [=](){
            Vector<Node*> nodeVector = createVector();
            Node* objToGet = nodeVector.at(quantityOfNodes/3);
            
            bool ret = false;
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                ret = nodeVector.contains(objToGet);
            CC_PROFILER_STOP(this->profilerName());
            
            // Uses `ret` to avoids `contains` invoking was optimized in release mode
            if (ret)
            {
                nodeVector.clear();
            }
        } } ,
        { "eraseObject", [=](){
            Vector<Node*> nodeVector = createVector();
            Node** nodes = (Node**)malloc(sizeof(Node*) * quantityOfNodes);
            
            for (int i = 0; i < quantityOfNodes; ++i)
            {
                nodes[i] = nodeVector.at(i);
            }
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector.eraseObject(nodes[i]);
            CC_PROFILER_STOP(this->profilerName());
            
            CCASSERT(nodeVector.empty(), "nodeVector was not empty.");
            
            free(nodes);
        } } ,
        { "erase",       [=](){
            Vector<Node*> nodeVector = createVector();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector.erase(nodeVector.begin());
            CC_PROFILER_STOP(this->profilerName());
            
            CCASSERT(nodeVector.empty(), "nodeVector was not empty.");

        } } ,
        { "clear",       [=](){
            Vector<Node*> nodeVector = createVector();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector.clear();
            CC_PROFILER_STOP(this->profilerName());
            
            CCASSERT(nodeVector.empty(), "nodeVector was not empty.");
        } } ,
        { "swap by index",        [=](){
            Vector<Node*> nodeVector = createVector();
            
            int swapIndex1 = quantityOfNodes / 3;
            int swapIndex2 = quantityOfNodes / 3 * 2;
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector.swap(swapIndex1, swapIndex2);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "swap by object",        [=](){
            Vector<Node*> nodeVector = createVector();
            
            Node* swapNode1 = nodeVector.at(quantityOfNodes / 3);
            Node* swapNode2 = nodeVector.at(quantityOfNodes / 3 * 2);
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector.swap(swapNode1, swapNode2);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "reverse",     [=](){
            Vector<Node*> nodeVector = createVector();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector.reverse();
            CC_PROFILER_STOP(this->profilerName());
        } } ,
    };
    
    for (const auto& nameCB : nameCBs)
    {
        _testFunctions.push_back(nameCB);
    }
}



std::string TemplateVectorPerfTest::title() const
{
    return "Vector<T> Perf test";
}

std::string TemplateVectorPerfTest::subtitle() const
{
    return "Test 'pushBack', See console";
}



////////////////////////////////////////////////////////
//
// ArrayPerfTest
//
////////////////////////////////////////////////////////

std::string ArrayPerfTest::title() const
{
    return "Array Perf test";
}

std::string ArrayPerfTest::subtitle() const
{
    return "Test `addObject`, See console";
}

void ArrayPerfTest::generateTestFunctions()
{
    auto createArray = [this](){
        Array* ret = Array::create();
        
        for( int i=0; i<quantityOfNodes; ++i)
        {
            auto node = Node::create();
            node->setTag(i);
            ret->addObject(node);
        }
        return ret;
    };
    
    TestFunction nameCBs[] = {
        { "addObject",    [=](){
            Array* nodeVector = Array::create();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->addObject(Node::create());
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "insertObject",      [=](){
            Array* nodeVector = Array::create();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->insertObject(Node::create(), 0);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "setObject",     [=](){
            Array* nodeVector = createArray();
            
            srand(time(nullptr));
            ssize_t index = rand() % quantityOfNodes;
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->setObject(Node::create(), index);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "getIndexOfObject",    [=](){
            Array* nodeVector = createArray();
            Object* objToGet = nodeVector->getObjectAtIndex(quantityOfNodes/3);
            ssize_t index = 0;
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                index = nodeVector->getIndexOfObject(objToGet);
            CC_PROFILER_STOP(this->profilerName());
            // Uses `index` to avoids `getIndex` invoking was optimized in release mode
            if (index == quantityOfNodes/3)
            {
                nodeVector->removeAllObjects();
            }
        } } ,
        { "getObjectAtIndex",          [=](){
            Array* nodeVector = createArray();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->getObjectAtIndex(quantityOfNodes/3);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "containsObject",    [=](){
            Array* nodeVector = createArray();
            Object* objToGet = nodeVector->getObjectAtIndex(quantityOfNodes/3);
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->containsObject(objToGet);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "removeObject", [=](){
            Array* nodeVector = createArray();
            Node** nodes = (Node**)malloc(sizeof(Node*) * quantityOfNodes);
            
            for (int i = 0; i < quantityOfNodes; ++i)
            {
                nodes[i] = static_cast<Node*>(nodeVector->getObjectAtIndex(i));
            }
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->removeObject(nodes[i]);
            CC_PROFILER_STOP(this->profilerName());
            
            CCASSERT(nodeVector->count() == 0, "nodeVector was not empty.");
            
            free(nodes);
        } } ,
        { "removeObjectAtIndex",       [=](){
            Array* nodeVector = createArray();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->removeObjectAtIndex(0);
            CC_PROFILER_STOP(this->profilerName());
            
            CCASSERT(nodeVector->count() == 0, "nodeVector was not empty.");
            
        } } ,
        { "removeAllObjects",       [=](){
            Array* nodeVector = createArray();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->removeAllObjects();
            CC_PROFILER_STOP(this->profilerName());
            
            CCASSERT(nodeVector->count() == 0, "nodeVector was not empty.");
        } } ,
        { "swap by index",        [=](){
            Array* nodeVector = createArray();
            
            int swapIndex1 = quantityOfNodes / 3;
            int swapIndex2 = quantityOfNodes / 3 * 2;
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->swap(swapIndex1, swapIndex2);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "swap by object",        [=](){
            Array* nodeVector = createArray();
            
            Object* swapNode1 = nodeVector->getObjectAtIndex(quantityOfNodes / 3);
            Object* swapNode2 = nodeVector->getObjectAtIndex(quantityOfNodes / 3 * 2);
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->exchangeObject(swapNode1, swapNode2);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "reverseObjects",     [=](){
            Array* nodeVector = createArray();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->reverseObjects();
            CC_PROFILER_STOP(this->profilerName());
        } } ,
    };
    
    for (const auto& nameCB : nameCBs)
    {
        _testFunctions.push_back(nameCB);
    }
}

///----------------------------------------
void runContainerPerformanceTest()
{
    auto scene = createFunctions[g_curCase]();
    scene->initWithQuantityOfNodes(kNodesIncrease);
    
    Director::getInstance()->replaceScene(scene);
}
