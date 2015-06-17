#include "PerformanceLabelTest.h"

USING_NS_CC;

enum {
    kMaxNodes = 200,
    kNodesIncrease = 10,

    TEST_COUNT = 5,
};

enum {
    kTagInfoLayer = 1,
    kTagMainLayer,
    kTagAutoTestMenu,
    kTagMenuLayer = (kMaxNodes + 1000),
};

enum {
    kCaseLabelTTFUpdate = 0,
    kCaseLabelBMFontUpdate,
    kCaseLabelUpdate,
    kCaseLabelBMFontBigLabels,
    kCaseLabelBigLabels
};

#define LongSentencesExample "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."

PerformceLabelTests::PerformceLabelTests()
{
    LabelMainScene::_s_labelCurCase = 0;
    addTestCase("LabelTTF Performance Test", [](){ return LabelMainScene::create(); });
    addTestCase("LabelBMFont Performance Test", [](){ return LabelMainScene::create(); });
    addTestCase("Label Performance Test", [](){ return LabelMainScene::create(); });
    addTestCase("LabelBMFont large text Performance", [](){ return LabelMainScene::create(); });
    addTestCase("Label large text Performance", [](){ return LabelMainScene::create(); });
}

////////////////////////////////////////////////////////
//
// LabelMainScene
//
////////////////////////////////////////////////////////

bool LabelMainScene::_s_autoTest = false;
int  LabelMainScene::_s_labelCurCase = 0;
int LabelMainScene::NODE_TEST_COUNT = AUTO_TEST_NODE_NUM;

bool LabelMainScene::init()
{
    //srandom(0);
    if (!TestCase::init())
    {
        return false;
    }

    auto s = Director::getInstance()->getWinSize();

    _lastRenderedCount = 0;
    _quantityNodes = 0;
    _accumulativeTime = 0.0f;

    _labelContainer = Layer::create();
    addChild(_labelContainer);

    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", CC_CALLBACK_1(LabelMainScene::onDecrease, this));
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", CC_CALLBACK_1(LabelMainScene::onIncrease, this));
    increase->setColor(Color3B(0,200,20));

    auto menu = Menu::create(decrease, increase, nullptr);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(s.width/2, s.height-65));
    addChild(menu, 1);

    auto infoLabel = Label::createWithTTF("0 nodes", "fonts/Marker Felt.ttf", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Vec2(s.width/2, s.height-90));
    addChild(infoLabel, 1, kTagInfoLayer);
    
    /**
     *  auto test menu
     */
    
    auto menuAutoTest = Menu::create();
    menuAutoTest->setPosition( Vec2::ZERO );
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(24);
    
    MenuItemFont* autoTestItem = nullptr;
    if (LabelMainScene::_s_autoTest)
    {
        autoTestItem = MenuItemFont::create("Auto Test On",CC_CALLBACK_1(LabelMainScene::onAutoTest, this));
    }
    else
    {
        autoTestItem = MenuItemFont::create("Auto Test Off",CC_CALLBACK_1(LabelMainScene::onAutoTest, this));
    }
    autoTestItem->setTag(1);
    autoTestItem->setPosition(Vec2( s.width - 90, s.height / 2));
    autoTestItem->setColor(Color3B::RED);
    menuAutoTest->addChild(autoTestItem);
    addChild( menuAutoTest, 3, kTagAutoTestMenu );

    while (_quantityNodes < NODE_TEST_COUNT)
        onIncrease(this);

    return true;
}

std::string LabelMainScene::title() const
{
    switch (_s_labelCurCase)
    {
    case kCaseLabelTTFUpdate:
        return "Testing LabelTTF Update";
    case kCaseLabelBMFontUpdate:
        return "Testing LabelBMFont Update";
    case kCaseLabelUpdate:
        return "Testing Label Update";
    case kCaseLabelBMFontBigLabels:
        return "Testing LabelBMFont Big Labels";
    case kCaseLabelBigLabels:
        return "Testing Label Big Labels";
    default:
        break;
    }
    return "No title";
}

LabelMainScene::~LabelMainScene()
{
    
}

void LabelMainScene::updateNodes()
{
    if( _quantityNodes != _lastRenderedCount )
    {
        auto infoLabel = (Label *) getChildByTag(kTagInfoLayer);
        char str[16] = {0};
        sprintf(str, "%u nodes", _quantityNodes);
        infoLabel->setString(str);

        _lastRenderedCount = _quantityNodes;
    }
}

void LabelMainScene::onIncrease(Ref* sender)
{    
    if( _quantityNodes >= kMaxNodes)
        return;

    auto size = Director::getInstance()->getWinSize();
    switch (_s_labelCurCase)
    {
    case kCaseLabelTTFUpdate:
        for( int i=0;i< kNodesIncrease;i++)
        {
            auto label = Label::createWithSystemFont("LabelTTF", "Marker Felt", 30);
            label->setPosition(Vec2((size.width/2 + rand() % 50), ((int)size.height/2 + rand() % 50)));
            _labelContainer->addChild(label, 1, _quantityNodes);

            _quantityNodes++;
        }
        break;
    case kCaseLabelBMFontUpdate:
        for( int i=0;i< kNodesIncrease;i++)
        {
            auto label = Label::createWithBMFont("fonts/bitmapFontTest3.fnt","LabelBMFont");
            label->setPosition(Vec2((size.width/2 + rand() % 50), ((int)size.height/2 + rand() % 50)));
            _labelContainer->addChild(label, 1, _quantityNodes);

            _quantityNodes++;
        }
        break;
    case kCaseLabelUpdate:
        {
            TTFConfig ttfConfig("fonts/arial.ttf", 60, GlyphCollection::DYNAMIC);
            for( int i=0;i< kNodesIncrease;i++)
            {
                auto label = Label::createWithTTF(ttfConfig, "Label", TextHAlignment::LEFT);
                label->setPosition(Vec2((size.width/2 + rand() % 50), ((int)size.height/2 + rand() % 50)));
                _labelContainer->addChild(label, 1, _quantityNodes);

                _quantityNodes++;
            }
            break;
        }        
    case kCaseLabelBMFontBigLabels:
        for( int i=0;i< kNodesIncrease;i++)
        {
            auto label = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", LongSentencesExample);
            label->setPosition(Vec2((size.width/2 + rand() % 50), ((int)size.height/2 + rand() % 50)));
            _labelContainer->addChild(label, 1, _quantityNodes);

            _quantityNodes++;
        }
        break;
    case kCaseLabelBigLabels:
        {
            TTFConfig ttfConfig("fonts/arial.ttf", 60, GlyphCollection::DYNAMIC);
            for( int i=0;i< kNodesIncrease;i++)
            {
                auto label = Label::createWithTTF(ttfConfig, LongSentencesExample, TextHAlignment::CENTER, size.width);
                label->setPosition(Vec2((rand() % 50), rand()%((int)size.height/3)));
                _labelContainer->addChild(label, 1, _quantityNodes);

                _quantityNodes++;
            }
            break;
        }        
    default:
        break;
    }

    updateNodes();
}

void LabelMainScene::onDecrease(Ref* sender)
{
    if( _quantityNodes <= 0 )
        return;

    for( int i = 0;i < kNodesIncrease;i++)
    {
        _quantityNodes--;
        _labelContainer->removeChildByTag(_quantityNodes);
    }

    updateNodes();
}

void  LabelMainScene::dumpProfilerFPS()
{
    if (_vecFPS.empty())
    {
        log("Error: the FPS vector is empty");
        return;
    }
    
    auto iter = _vecFPS.begin();
    float minFPS = *iter;
    float maxFPS = *iter;
    float totalFPS = 0.0f;
    float averagerFPS = 0.0f;
    for (auto fps : _vecFPS)
    {
        CCLOG("fps is :%f\n",fps);
        minFPS = std::min(minFPS, fps);
        maxFPS = std::max(maxFPS, fps);
        totalFPS += fps;
    }
    
    averagerFPS = totalFPS / _vecFPS.size();
    log("Cur test: %d, cur label nums:%d, the min FPS value is %.1f,the max FPS value is %.1f,the averager FPS is %.1f", LabelMainScene::_s_labelCurCase, _quantityNodes, minFPS, maxFPS, averagerFPS);
    
}

void LabelMainScene::updateAutoTest(float dt)
{
    if (LabelMainScene::_s_autoTest)
    {
        _executeTimes += 1;
        _vecFPS.push_back(Director::getInstance()->getFrameRate());
        if ( _executeTimes >= LabelMainScene::MAX_AUTO_TEST_TIMES )
        {
            dumpProfilerFPS();
            nextAutoTest();
        }
    }
}

void LabelMainScene::updateText(float dt)
{
    if(_s_labelCurCase > kCaseLabelUpdate)
        return;

    _accumulativeTime += dt;
    char text[20];
    sprintf(text,"%.2f",_accumulativeTime);

    auto& children = _labelContainer->getChildren();
    
    switch (_s_labelCurCase)
    {
    case kCaseLabelTTFUpdate:
        for(const auto &child : children) {
            Label* label = (Label*)child;
            label->setString(text);
        }
        break;
    case kCaseLabelBMFontUpdate:
        for(const auto &child : children) {
            auto label = (Label*)child;
            label->setString(text);
        }
        break;
    case kCaseLabelUpdate:
        for(const auto &child : children) {
            Label* label = (Label*)child;
            label->setString(text);
        }
        break;
    default:
        break;
    }
}

void LabelMainScene::onEnter()
{
    Scene::onEnter();
    
    auto director = Director::getInstance();
    auto sched = director->getScheduler();
    sched->schedule(CC_SCHEDULE_SELECTOR(LabelMainScene::updateText), this, 0.0f, false);

    _vecFPS.clear();
    _executeTimes = 0;
    sched->schedule(CC_SCHEDULE_SELECTOR(LabelMainScene::updateAutoTest), this, 0.2f, false);
}

void LabelMainScene::onExit()
{
    auto director = Director::getInstance();
    auto sched = director->getScheduler();
    sched->unschedule(CC_SCHEDULE_SELECTOR(LabelMainScene::updateText), this );
    sched->unschedule(CC_SCHEDULE_SELECTOR(LabelMainScene::updateAutoTest), this );
    
    Scene::onExit();
}

void  LabelMainScene::endAutoTest()
{
    LabelMainScene::_s_autoTest = false;
    
    _vecFPS.clear();
    _executeTimes = 0;
}

void  LabelMainScene::nextAutoTest()
{
    if ( LabelMainScene::_s_labelCurCase + 1 < LabelMainScene::MAX_SUB_TEST_NUMS )
    {
        nextTestCallback(nullptr);
    }
    else
    {
        finishAutoTest();
    }
}

void  LabelMainScene::finishAutoTest()
{
    LabelMainScene::_s_autoTest = false;
    _vecFPS.clear();
    _executeTimes = 0;

    auto autoTestMenu = dynamic_cast<Menu*>(getChildByTag(kTagAutoTestMenu));
    if (nullptr != autoTestMenu)
    {
        auto menuItemFont = dynamic_cast<MenuItemFont*>(autoTestMenu->getChildByTag(1));
        if (nullptr != menuItemFont)
        {
            menuItemFont->setString("Auto Test finish");
        }
    }
    
    log("Label performance test is  finish ");
}

void  LabelMainScene::onAutoTest(Ref* sender)
{
    LabelMainScene::_s_autoTest = !LabelMainScene::_s_autoTest;
    _vecFPS.clear();
    _executeTimes = 0;
    MenuItemFont* menuItem = dynamic_cast<MenuItemFont*>(sender);
    if (nullptr != menuItem)
    {
        if (LabelMainScene::_s_autoTest)
        {
            menuItem->setString("Auto Test On");
        }
        else
        {
            menuItem->setString("Auto Test Off");
            endAutoTest();
        }
    }
}

void LabelMainScene::nextTestCallback(cocos2d::Ref* sender)
{
    NODE_TEST_COUNT = _quantityNodes;
    _s_labelCurCase = (_s_labelCurCase + 1) % MAX_SUB_TEST_NUMS;
    TestCase::nextTestCallback(sender);
}

void LabelMainScene::priorTestCallback(cocos2d::Ref* sender)
{
    NODE_TEST_COUNT = _quantityNodes;
    if (_s_labelCurCase > 0)
    {
        _s_labelCurCase -= 1;
    } 
    else
    {
        _s_labelCurCase = MAX_SUB_TEST_NUMS - 1;
    }
    TestCase::priorTestCallback(sender);
}
