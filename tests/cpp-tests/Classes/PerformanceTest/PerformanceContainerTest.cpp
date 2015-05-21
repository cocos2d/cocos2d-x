/*
 *
 */
#include "PerformanceContainerTest.h"
#include <algorithm>

USING_NS_CC;

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

PerformceContainerTests::PerformceContainerTests()
{
    ADD_TEST_CASE(TemplateVectorPerfTest);
    ADD_TEST_CASE(ArrayPerfTest);
    ADD_TEST_CASE(TemplateMapStringKeyPerfTest);
    ADD_TEST_CASE(DictionaryStringKeyPerfTest);
    ADD_TEST_CASE(TemplateMapIntKeyPerfTest);
    ADD_TEST_CASE(DictionaryIntKeyPerfTest);
}

enum {
    kTagInfoLayer = 1,

    kTagBase = 20000,
};

enum {
    kMaxNodes = 15000,
    kNodesIncrease = 500,
};

int PerformanceContainerScene::quantityOfNodes = kNodesIncrease;

////////////////////////////////////////////////////////
//
// PerformanceContainerScene
//
////////////////////////////////////////////////////////
bool PerformanceContainerScene::init()
{
    if (TestCase::init())
    {
        initWithQuantityOfNodes(quantityOfNodes);
        return true;
    }

    return false;
}

void PerformanceContainerScene::initWithQuantityOfNodes(unsigned int nNodes)
{
    _type = 0;
    //srand(time());
    auto s = Director::getInstance()->getWinSize();

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
    _decrease = decrease;
    
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
    _increase = increase;

    auto menu = Menu::create(decrease, increase, nullptr);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(s.width/2, s.height/2+15));
    addChild(menu, 1);

    auto infoLabel = Label::createWithTTF("0 nodes", "fonts/Marker Felt.ttf", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Vec2(s.width/2, s.height/2-15));
    addChild(infoLabel, 1, kTagInfoLayer);

    log("Size of Node: %d\n", (int)sizeof(Node));
    
    int oldFontSize = MenuItemFont::getFontSize();
    MenuItemFont::setFontSize(24);
    
    Vector<cocos2d::MenuItem *> toggleItems;
    
    generateTestFunctions();
    
    CCASSERT(!_testFunctions.empty(), "Should not be empty after generate test functions");

    
    for (const auto& f : _testFunctions)
    {
        toggleItems.pushBack(MenuItemFont::create(f.name));
    }
    
    auto toggle = MenuItemToggle::createWithCallback([this](Ref* sender){
        auto toggle = static_cast<MenuItemToggle*>(sender);
        this->_type = toggle->getSelectedIndex();
        _subtitleLabel->setString(StringUtils::format("Test '%s', See console", this->_testFunctions[this->_type].name));
        this->updateProfilerName();
    }, toggleItems);
    
    toggle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    toggle->setPosition(VisibleRect::left());
    _toggle = toggle;
    
    auto start = MenuItemFont::create("start", [this](Ref* sender){
        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        
        CC_PROFILER_PURGE_ALL();
        sched->schedule(CC_SCHEDULE_SELECTOR(PerformanceContainerScene::dumpProfilerInfo), this, 2, false);
        
        this->unscheduleUpdate();
        this->scheduleUpdate();
        this->_startItem->setEnabled(false);
        this->_stopItem->setEnabled(true);
        this->_toggle->setEnabled(false);
        this->_increase->setEnabled(false);
        this->_decrease->setEnabled(false);
    });
    start->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    start->setPosition(VisibleRect::right() + Vec2(0, 40));
    _startItem = start;
    
    auto stop = MenuItemFont::create("stop", [this](Ref* sender){
        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        
        sched->unschedule(CC_SCHEDULE_SELECTOR(PerformanceContainerScene::dumpProfilerInfo), this);
        
        this->unscheduleUpdate();
        this->_startItem->setEnabled(true);
        this->_stopItem->setEnabled(false);
        this->_toggle->setEnabled(true);
        this->_increase->setEnabled(true);
        this->_decrease->setEnabled(true);
    });
    
    stop->setEnabled(false);
    stop->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    stop->setPosition(VisibleRect::right() + Vec2(0, -40));
    _stopItem = stop;
    
    auto menu2 = Menu::create(toggle, start, stop, nullptr);
    menu2->setPosition(Vec2::ZERO);
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
        auto infoLabel = static_cast<Label*>( getChildByTag(kTagInfoLayer) );
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
    
    TestFunction testFunctions[] = {
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
            
            srand((unsigned)time(nullptr));
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
        
        { "c++11 Range Loop",     [=](){
            Vector<Node*> nodeVector = createVector();
            
            CC_PROFILER_START(this->profilerName());
            for (const auto& e : nodeVector)
            {
                e->setTag(111);
            }
            CC_PROFILER_STOP(this->profilerName());
        } } ,
    };
    
    for (const auto& func : testFunctions)
    {
        _testFunctions.push_back(func);
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
        __Array* ret = Array::create();
        
        for( int i=0; i<quantityOfNodes; ++i)
        {
            auto node = Node::create();
            node->setTag(i);
            ret->addObject(node);
        }
        return ret;
    };
    
    TestFunction testFunctions[] = {
        { "addObject",    [=](){
            __Array* nodeVector = Array::create();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->addObject(Node::create());
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "insertObject",      [=](){
            __Array* nodeVector = Array::create();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->insertObject(Node::create(), 0);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "setObject",     [=](){
            __Array* nodeVector = createArray();
            
            srand((unsigned)time(nullptr));
            ssize_t index = rand() % quantityOfNodes;
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->setObject(Node::create(), index);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "getIndexOfObject",    [=](){
            __Array* nodeVector = createArray();
            Ref* objToGet = nodeVector->getObjectAtIndex(quantityOfNodes/3);
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
            __Array* nodeVector = createArray();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->getObjectAtIndex(quantityOfNodes/3);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "containsObject",    [=](){
            __Array* nodeVector = createArray();
            Ref* objToGet = nodeVector->getObjectAtIndex(quantityOfNodes/3);
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->containsObject(objToGet);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        { "removeObject", [=](){
            __Array* nodeVector = createArray();
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
            __Array* nodeVector = createArray();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->removeObjectAtIndex(0);
            CC_PROFILER_STOP(this->profilerName());
            
            CCASSERT(nodeVector->count() == 0, "nodeVector was not empty.");
            
        } } ,
        { "removeAllObjects",       [=](){
            __Array* nodeVector = createArray();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->removeAllObjects();
            CC_PROFILER_STOP(this->profilerName());
            
            CCASSERT(nodeVector->count() == 0, "nodeVector was not empty.");
        } } ,
        { "swap by index",        [=](){
            __Array* nodeVector = createArray();
            
            int swapIndex1 = quantityOfNodes / 3;
            int swapIndex2 = quantityOfNodes / 3 * 2;
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->swap(swapIndex1, swapIndex2);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "swap by object",        [=](){
            __Array* nodeVector = createArray();
            
            Ref* swapNode1 = nodeVector->getObjectAtIndex(quantityOfNodes / 3);
            Ref* swapNode2 = nodeVector->getObjectAtIndex(quantityOfNodes / 3 * 2);
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->exchangeObject(swapNode1, swapNode2);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "reverseObjects",     [=](){
            __Array* nodeVector = createArray();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodeVector->reverseObjects();
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "CCARRAY_FOREACH",     [=](){
            __Array* nodeVector = createArray();
            Ref* obj;
            CC_PROFILER_START(this->profilerName());
            
            CCARRAY_FOREACH(nodeVector, obj)
            {
                static_cast<Node*>(obj)->setTag(111);
            }
            CC_PROFILER_STOP(this->profilerName());
        } } ,
    };
    
    for (const auto& func : testFunctions)
    {
        _testFunctions.push_back(func);
    }
}

////////////////////////////////////////////////////////
//
// TemplateMapStringKeyPerfTest
//
////////////////////////////////////////////////////////

void TemplateMapStringKeyPerfTest::generateTestFunctions()
{
    auto createMap = [this](){
        Map<std::string, Node*> ret;
        
        for( int i=0; i<quantityOfNodes; ++i)
        {
            auto node = Node::create();
            node->setTag(i);
            ret.insert(StringUtils::format("key_%d", i), node);
        }
        return ret;
    };
    
    TestFunction testFunctions[] = {
        { "insert",    [=](){
            Map<std::string, Node*> map;
            
            std::string* keys = new std::string[quantityOfNodes];
            
            for (int i = 0; i < quantityOfNodes; ++i)
            {
                keys[i] = StringUtils::format("key_%d", i);
            }
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                map.insert(keys[i], Node::create());
            CC_PROFILER_STOP(this->profilerName());
            
            CC_SAFE_DELETE_ARRAY(keys);
        } } ,

        { "at",    [=](){
            Map<std::string, Node*> map = createMap();
            
            std::string* keys = new std::string[quantityOfNodes];
            Node** nodes = (Node**)malloc(sizeof(Node*) * quantityOfNodes);
            for (int i = 0; i < quantityOfNodes; ++i)
            {
                keys[i] = StringUtils::format("key_%d", i);
            }
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodes[i] = map.at(keys[i]);
            CC_PROFILER_STOP(this->profilerName());
            
            CC_SAFE_DELETE_ARRAY(keys);
            
            for (int i = 0; i < quantityOfNodes; ++i)
            {
                nodes[i]->setTag(100);
            }
            
            CC_SAFE_FREE(nodes);
        } } ,
        
        { "erase",    [=](){
            auto map = createMap();
            
            std::string* keys = new std::string[quantityOfNodes];
            Node** nodes = (Node**)malloc(sizeof(Node*) * quantityOfNodes);
            for (int i = 0; i < quantityOfNodes; ++i)
            {
                keys[i] = StringUtils::format("key_%d", i);
            }
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                map.erase(keys[i]);
            CC_PROFILER_STOP(this->profilerName());
            
            CC_SAFE_DELETE_ARRAY(keys);
            
            CC_SAFE_FREE(nodes);
        } } ,
        
        { "clear",    [=](){
            auto map = createMap();
            
            CC_PROFILER_START(this->profilerName());
            map.clear();
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "size",    [=](){
            auto map = createMap();
            
            ssize_t size = 0;
            CC_PROFILER_START(this->profilerName());
            size = map.size();
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "keys(all)",    [=](){
            auto map = createMap();
            
            CC_PROFILER_START(this->profilerName());
            auto keys = map.keys();
            CC_PROFILER_STOP(this->profilerName());
            
            std::string allKeysString;
            for (const auto& key : keys)
            {
                allKeysString += "_" + key;
            }
        } } ,
        
        { "keys(object)",    [=](){
            Map<std::string, Node*> map;
            
            Node** nodes = (Node**) malloc(sizeof(Node*) * quantityOfNodes);
            Node* sameNode = Node::create();
            
            for( int i=0; i<quantityOfNodes; ++i)
            {
                if (quantityOfNodes % 100 == 0)
                {
                    map.insert(StringUtils::format("key_%d", i), sameNode);
                }
                else
                {
                    auto node = Node::create();
                    node->setTag(i);
                    map.insert(StringUtils::format("key_%d", i), node);
                }
            }
            
            CC_PROFILER_START(this->profilerName());
            auto keys = map.keys(sameNode);
            CC_PROFILER_STOP(this->profilerName());
            
            std::string allKeysString;
            for (const auto& key : keys)
            {
                allKeysString += "_" + key;
            }
            
            CC_SAFE_FREE(nodes);
        } } ,
        
        { "c++11 range loop",    [=](){
            auto map = createMap();
            
            CC_PROFILER_START(this->profilerName());
            
            for (const auto& e : map)
            {
                e.second->setTag(100);
            }
            
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
    };
    
    for (const auto& func : testFunctions)
    {
        _testFunctions.push_back(func);
    }
}

std::string TemplateMapStringKeyPerfTest::title() const
{
    return "Map<T> String Key Perf test";
}

std::string TemplateMapStringKeyPerfTest::subtitle() const
{
    return "Test 'insert', See console";
}

////////////////////////////////////////////////////////
//
// DictionaryStringKeyPerfTest
//
////////////////////////////////////////////////////////

void DictionaryStringKeyPerfTest::generateTestFunctions()
{
    auto createDict = [this](){
        __Dictionary* ret = __Dictionary::create();
        
        for( int i=0; i<quantityOfNodes; ++i)
        {
            auto node = Node::create();
            node->setTag(i);
            ret->setObject(node, StringUtils::format("key_%d", i));
        }
        return ret;
    };
    
    TestFunction testFunctions[] = {
        { "setObject",    [=](){
            __Dictionary* dict = __Dictionary::create();
            
            std::string* keys = new std::string[quantityOfNodes];
            
            for (int i = 0; i < quantityOfNodes; ++i)
            {
                keys[i] = StringUtils::format("key_%d", i);
            }
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                dict->setObject(Node::create(), keys[i]);
            CC_PROFILER_STOP(this->profilerName());
            
            CC_SAFE_DELETE_ARRAY(keys);
        } } ,
        
        { "objectForKey",    [=](){
            auto dict = createDict();
            
            std::string* keys = new std::string[quantityOfNodes];
            Node** nodes = (Node**)malloc(sizeof(Node*) * quantityOfNodes);
            for (int i = 0; i < quantityOfNodes; ++i)
            {
                keys[i] = StringUtils::format("key_%d", i);
            }
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodes[i] = static_cast<Node*>(dict->objectForKey(keys[i]));
            CC_PROFILER_STOP(this->profilerName());
            
            CC_SAFE_DELETE_ARRAY(keys);
            
            for (int i = 0; i < quantityOfNodes; ++i)
            {
                nodes[i]->setTag(100);
            }
            
            CC_SAFE_FREE(nodes);
        } } ,
        
        { "removeObjectForKey",    [=](){
            auto dict = createDict();
            
            std::string* keys = new std::string[quantityOfNodes];
            Node** nodes = (Node**)malloc(sizeof(Node*) * quantityOfNodes);
            for (int i = 0; i < quantityOfNodes; ++i)
            {
                keys[i] = StringUtils::format("key_%d", i);
            }
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                dict->removeObjectForKey(keys[i]);
            CC_PROFILER_STOP(this->profilerName());
            
            CC_SAFE_DELETE_ARRAY(keys);
            
            CC_SAFE_FREE(nodes);
        } } ,
        
        { "removeAllObjects",    [=](){
            auto dict = createDict();
            
            CC_PROFILER_START(this->profilerName());
            dict->removeAllObjects();
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "count",    [=](){
            auto dict = createDict();
            
            ssize_t size = 0;
            CC_PROFILER_START(this->profilerName());
            size = dict->count();
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "allKeys",    [=](){
            auto dict = createDict();
            
            CC_PROFILER_START(this->profilerName());
            auto keys = dict->allKeys();
            CC_PROFILER_STOP(this->profilerName());
            
            std::string allKeysString;
            Ref* obj;
            CCARRAY_FOREACH(keys, obj)
            {
                auto key = static_cast<__String*>(obj);
                allKeysString += (std::string("_") + key->getCString());
            }
        } } ,
        
        { "allKeysForObject",    [=](){
            __Dictionary* dict = Dictionary::create();
            
            Node** nodes = (Node**) malloc(sizeof(Node*) * quantityOfNodes);
            Node* sameNode = Node::create();
            
            for( int i=0; i<quantityOfNodes; ++i)
            {
                if (quantityOfNodes % 100 == 0)
                {
                    dict->setObject(sameNode, StringUtils::format("key_%d", i));
                }
                else
                {
                    auto node = Node::create();
                    node->setTag(i);
                    dict->setObject(node, StringUtils::format("key_%d", i));
                }
            }
            
            CC_PROFILER_START(this->profilerName());
            auto keys = dict->allKeysForObject(sameNode);
            CC_PROFILER_STOP(this->profilerName());
            
            std::string allKeysString;
            Ref* obj;
            CCARRAY_FOREACH(keys, obj)
            {
                auto key = static_cast<__String*>(obj);
                allKeysString += (std::string("_") + key->getCString());
            }
            
            CC_SAFE_FREE(nodes);
        } } ,
        
        { "CCDICT_FOREACH",    [=](){
            auto dict = createDict();
            
            CC_PROFILER_START(this->profilerName());
            
            DictElement* e = nullptr;
            CCDICT_FOREACH(dict, e)
            {
                static_cast<Node*>(e->getObject())->setTag(100);
            }
            
            CC_PROFILER_STOP(this->profilerName());
        } } ,
    };
    
    for (const auto& func : testFunctions)
    {
        _testFunctions.push_back(func);
    }
}

std::string DictionaryStringKeyPerfTest::title() const
{
    return "Dictionary String Key Perf test";
}

std::string DictionaryStringKeyPerfTest::subtitle() const
{
    return "Test `setObject`, See console";
}


////////////////////////////////////////////////////////
//
// TemplateMapIntKeyPerfTest
//
////////////////////////////////////////////////////////

void TemplateMapIntKeyPerfTest::generateTestFunctions()
{
    auto createMap = [this](){
        Map<int, Node*> ret;
        
        for( int i=0; i<quantityOfNodes; ++i)
        {
            auto node = Node::create();
            node->setTag(i);
            ret.insert(100+i, node);
        }
        return ret;
    };
    
    TestFunction testFunctions[] = {
        { "insert",    [=](){
            Map<int, Node*> map;
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                map.insert(100 + i, Node::create());
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "at",    [=](){
            auto map = createMap();
            Node** nodes = (Node**)malloc(sizeof(Node*) * quantityOfNodes);
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodes[i] = map.at(100 + i);
            CC_PROFILER_STOP(this->profilerName());
            
            for (int i = 0; i < quantityOfNodes; ++i)
            {
                nodes[i]->setTag(100);
            }
            
            CC_SAFE_FREE(nodes);
        } } ,
        
        { "erase",    [=](){
            auto map = createMap();
            
            Node** nodes = (Node**)malloc(sizeof(Node*) * quantityOfNodes);
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                map.erase(100 + i);
            CC_PROFILER_STOP(this->profilerName());
            
            CC_SAFE_FREE(nodes);
        } } ,
        
        { "clear",    [=](){
            auto map = createMap();
            
            CC_PROFILER_START(this->profilerName());
            map.clear();
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "size",    [=](){
            auto map = createMap();
            
            ssize_t size = 0;
            CC_PROFILER_START(this->profilerName());
            size = map.size();
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "keys(all)",    [=](){
            auto map = createMap();
            
            CC_PROFILER_START(this->profilerName());
            auto keys = map.keys();
            CC_PROFILER_STOP(this->profilerName());
            
            int allKeysInt = 0;
            for (const auto& key : keys)
            {
                allKeysInt += key;
            }
        } } ,
        
        { "keys(object)",    [=](){
            Map<int, Node*> map;
            
            Node** nodes = (Node**) malloc(sizeof(Node*) * quantityOfNodes);
            Node* sameNode = Node::create();
            
            for( int i=0; i<quantityOfNodes; ++i)
            {
                if (quantityOfNodes % 100 == 0)
                {
                    map.insert(100 + i, sameNode);
                }
                else
                {
                    auto node = Node::create();
                    node->setTag(i);
                    map.insert(100 + i, node);
                }
            }
            
            CC_PROFILER_START(this->profilerName());
            auto keys = map.keys(sameNode);
            CC_PROFILER_STOP(this->profilerName());
            
            int allKeysInt = 0;
            for (const auto& key : keys)
            {
                allKeysInt += key;
            }
            
            CC_SAFE_FREE(nodes);
        } } ,
        
        { "c++11 range loop",    [=](){
            auto map = createMap();
            
            CC_PROFILER_START(this->profilerName());
            
            for (const auto& e : map)
            {
                e.second->setTag(100);
            }
            
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
    };
    
    for (const auto& func : testFunctions)
    {
        _testFunctions.push_back(func);
    }
}

std::string TemplateMapIntKeyPerfTest::title() const
{
    return "Map<T> Integer Key Perf test";
}

std::string TemplateMapIntKeyPerfTest::subtitle() const
{
    return "Test 'insert', See console";
}

////////////////////////////////////////////////////////
//
// DictionaryIntKeyPerfTest
//
////////////////////////////////////////////////////////

void DictionaryIntKeyPerfTest::generateTestFunctions()
{
    auto createDict = [this](){
        __Dictionary* ret = Dictionary::create();
        
        for( int i=0; i<quantityOfNodes; ++i)
        {
            auto node = Node::create();
            node->setTag(i);
            ret->setObject(node, 100 + i);
        }
        return ret;
    };
    
    TestFunction testFunctions[] = {
        { "setObject",    [=](){
            __Dictionary* dict = Dictionary::create();
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                dict->setObject(Node::create(), 100 + i);
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "objectForKey",    [=](){
            auto dict = createDict();
            
            Node** nodes = (Node**)malloc(sizeof(Node*) * quantityOfNodes);
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                nodes[i] = static_cast<Node*>(dict->objectForKey(100 + i));
            CC_PROFILER_STOP(this->profilerName());
            
            for (int i = 0; i < quantityOfNodes; ++i)
            {
                nodes[i]->setTag(100);
            }
            
            CC_SAFE_FREE(nodes);
        } } ,
        
        { "removeObjectForKey",    [=](){
            auto dict = createDict();
            
            Node** nodes = (Node**)malloc(sizeof(Node*) * quantityOfNodes);
            
            CC_PROFILER_START(this->profilerName());
            for( int i=0; i<quantityOfNodes; ++i)
                dict->removeObjectForKey(100 + i);
            CC_PROFILER_STOP(this->profilerName());
            
            CC_SAFE_FREE(nodes);
        } } ,
        
        { "removeAllObjects",    [=](){
            auto dict = createDict();
            
            CC_PROFILER_START(this->profilerName());
            dict->removeAllObjects();
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "count",    [=](){
            auto dict = createDict();
            
            unsigned int size = 0;
            CC_PROFILER_START(this->profilerName());
            size = dict->count();
            CC_PROFILER_STOP(this->profilerName());
        } } ,
        
        { "allKeys",    [=](){
            auto dict = createDict();
            
            CC_PROFILER_START(this->profilerName());
            auto keys = dict->allKeys();
            CC_PROFILER_STOP(this->profilerName());
            
            int allKeysInt = 0;
            Ref* obj;
            CCARRAY_FOREACH(keys, obj)
            {
                auto key = static_cast<__Integer*>(obj);
                allKeysInt += key->getValue();
            }
        } } ,
        
        { "allKeysForObject",    [=](){
            __Dictionary* dict = Dictionary::create();
            
            Node** nodes = (Node**) malloc(sizeof(Node*) * quantityOfNodes);
            Node* sameNode = Node::create();
            
            for( int i=0; i<quantityOfNodes; ++i)
            {
                if (quantityOfNodes % 100 == 0)
                {
                    dict->setObject(sameNode, 100 + i);
                }
                else
                {
                    auto node = Node::create();
                    node->setTag(i);
                    dict->setObject(node, 100 + i);
                }
            }
            
            CC_PROFILER_START(this->profilerName());
            auto keys = dict->allKeysForObject(sameNode);
            CC_PROFILER_STOP(this->profilerName());
            
            int allKeysInt = 0;
            Ref* obj;
            CCARRAY_FOREACH(keys, obj)
            {
                auto key = static_cast<__Integer*>(obj);
                allKeysInt += key->getValue();
            }
            
            CC_SAFE_FREE(nodes);
        } } ,
        
        { "CCDICT_FOREACH",    [=](){
            auto dict = createDict();
            
            CC_PROFILER_START(this->profilerName());
            
            DictElement* e = nullptr;
            CCDICT_FOREACH(dict, e)
            {
                static_cast<Node*>(e->getObject())->setTag(100);
            }
            
            CC_PROFILER_STOP(this->profilerName());
        } } ,
    };
    
    for (const auto& func : testFunctions)
    {
        _testFunctions.push_back(func);
    }
}

std::string DictionaryIntKeyPerfTest::title() const
{
    return "Dictionary Integer Key Perf test";
}

std::string DictionaryIntKeyPerfTest::subtitle() const
{
    return "Test `setObject`, See console";
}
