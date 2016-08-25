/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "BaseTest.h"
#include "testResource.h"
#include "controller.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define TABEL_LABEL_TAG 1024

TestBase::TestBase()
: _parentTest(nullptr)
, _isTestList(false)
{

}

TestBase::~TestBase()
{

}

void TestBase::backsUpOneLevel()
{
    if (_parentTest)
    {
        _parentTest->runThisTest();
        this->release();
    }
}

//TestList
class TestCustomTableView : public TableView
{
public:
    static TestCustomTableView* create(TableViewDataSource* dataSource, Size size)
    {
        auto table = new (std::nothrow) TestCustomTableView();
        table->initWithViewSize(size, nullptr);
        table->autorelease();
        table->setDataSource(dataSource);
        table->_updateCellPositions();
        table->_updateContentSize();

        return table;
    }
   
    virtual void onTouchEnded(Touch *touch, Event *event) override
    {
        if (!this->isVisible())
        {
            return;
        }

        if (_touchedCell)
        {
            auto label = (Label*)_touchedCell->getChildByTag(TABEL_LABEL_TAG);

            Rect bbox = label->getBoundingBox();
            bbox.origin = _touchedCell->convertToWorldSpace(bbox.origin);

            if (bbox.containsPoint(touch->getLocation()) && _tableViewDelegate != nullptr)
            {
                _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
                _tableViewDelegate->tableCellTouched(this, _touchedCell);
            }

            _touchedCell = nullptr;
        }

        ScrollView::onTouchEnded(touch, event);
    }

    void onMouseScroll(Event *event)
    {
        auto mouseEvent = static_cast<EventMouse*>(event);
        float moveY = mouseEvent->getScrollY() * 20;

        auto minOffset = this->minContainerOffset();
        auto maxOffset = this->maxContainerOffset();

        auto offset = this->getContentOffset();
        offset.y += moveY;

        if (offset.y < minOffset.y)
        {
            offset.y = minOffset.y;
        }
        else if (offset.y > maxOffset.y)
        {
            offset.y = maxOffset.y;
        }
        this->setContentOffset(offset);
    }

protected:
    TestCustomTableView()
    {
        auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseScroll = CC_CALLBACK_1(TestCustomTableView::onMouseScroll, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    }
};

TestList::TestList()
{
    _isTestList = true;
    _shouldRestoreTableOffset = false;
}

void TestList::addTest(const std::string& testName, std::function<TestBase*()> callback)
{
    if (!testName.empty())
    {
        _childTestNames.emplace_back(StringUtils::format("%d", static_cast<int>(_childTestNames.size() + 1)) + ":" + testName);
        _testCallbacks.emplace_back(callback);
    }
}

void TestList::runThisTest()
{
    _cellTouchEnabled = true;
    auto director = Director::getInstance();
    auto scene = Scene::create();

    auto visibleSize = director->getVisibleSize();
    auto origin = director->getVisibleOrigin();

    auto tableView = TestCustomTableView::create(this, Size(400, visibleSize.height));
    tableView->setPosition(origin.x + (visibleSize.width - 400) / 2, origin.y);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setDelegate(this);
    scene->addChild(tableView);
    tableView->reloadData();

    if (_shouldRestoreTableOffset)
    {
        tableView->setContentOffset(_tableOffset);
    }

    if (_parentTest)
    {
        //Add back button.
        TTFConfig ttfConfig("fonts/arial.ttf", 20);
        auto label = Label::createWithTTF(ttfConfig, "Back");

        auto menuItem = MenuItemLabel::create(label, std::bind(&TestBase::backsUpOneLevel, this));
        auto menu = Menu::create(menuItem, nullptr);

        menu->setPosition(Vec2::ZERO);
        menuItem->setPosition(Vec2(VisibleRect::right().x - 50, VisibleRect::bottom().y + 25));

        scene->addChild(menu, 1);
    }
    else
    {
        //Add close and "Start AutoTest" button.
        auto closeItem = MenuItemImage::create(s_pathClose, s_pathClose, [](Ref* sender){
            TestController::getInstance()->stopAutoTest();
            TestController::destroyInstance();
            Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
        });
        closeItem->setPosition(VisibleRect::right().x - 30, VisibleRect::top().y - 30);

        auto autoTestLabel = Label::createWithTTF("Start AutoTest","fonts/arial.ttf",16);
        auto autoTestItem = MenuItemLabel::create(autoTestLabel, [&](Ref* sender){
            TestController::getInstance()->startAutoTest();
        });
        autoTestItem->setPosition(Vec2(VisibleRect::left().x + 60, VisibleRect::bottom().y + 50));

        auto menu = Menu::create(closeItem, autoTestItem, nullptr);
        menu->setPosition(Vec2::ZERO);
        scene->addChild(menu, 1);
    }

    director->replaceScene(scene);
}

void TestList::tableCellTouched(TableView* table, TableViewCell* cell)
{
    if (_cellTouchEnabled)
    {
        auto index = cell->getIdx();
        if (_testCallbacks[index])
        {
            auto test = _testCallbacks[index]();
            if (test->getChildTestCount() > 0)
            {
                _tableOffset = table->getContentOffset();
                _shouldRestoreTableOffset = true;
                _cellTouchEnabled = false;
                test->setTestParent(this);
                test->runThisTest();
            }
            else
            {
                delete test;
            }
        }
    }
}

TableViewCell* TestList::tableCellAtIndex(TableView *table, ssize_t idx)
{
    auto cell = table->dequeueCell();
    if (!cell)
    {
        cell = TableViewCell::create();
        auto label = Label::createWithTTF(_childTestNames[idx], "fonts/arial.ttf", 20.0f);
        label->setTag(TABEL_LABEL_TAG);
        label->setPosition(200, 15);
        cell->addChild(label);
    }
    else
    {
        auto label = (Label*)cell->getChildByTag(TABEL_LABEL_TAG);
        label->setString(_childTestNames[idx]);
    }

    return cell;
}

Size TestList::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(400, 30);
}

ssize_t TestList::numberOfCellsInTableView(TableView *table)
{
    return _childTestNames.size();
}

//TestSuite
void TestSuite::addTestCase(const std::string& testName, std::function<Scene*()> callback)
{
    if (!testName.empty() && callback)
    {
        _childTestNames.emplace_back(testName);
        _testCallbacks.emplace_back(callback);
    }
}

static TestCase* getTestCase(Scene* scene)
{
    auto transitionScene = dynamic_cast<TransitionScene*>(scene);
    TestCase* testCase = nullptr;
    if (transitionScene)
    {
        testCase = dynamic_cast<TestCase*>(transitionScene->getInScene());
    }
    else
    {
        testCase = dynamic_cast<TestCase*>(scene);
    }

    return testCase;
}

void TestSuite::runThisTest()
{
    if (!_childTestNames.empty())
    {
        TestController::getInstance()->setCurrTestSuite(this);

        _currTestIndex = 0;
        auto scene = _testCallbacks[0]();
        auto testCase = getTestCase(scene);
        testCase->setTestSuite(this);
        testCase->setTestCaseName(_childTestNames[_currTestIndex]);
        Director::getInstance()->replaceScene(scene);
    }
}

void TestSuite::restartCurrTest()
{
    auto scene = _testCallbacks[_currTestIndex]();
    auto testCase = getTestCase(scene);
    testCase->setTestSuite(this);
    testCase->setTestCaseName(_childTestNames[_currTestIndex]);

    Director::getInstance()->replaceScene(scene);
}

void TestSuite::enterNextTest()
{
    _currTestIndex = (_currTestIndex + 1) % _childTestNames.size();

    auto scene = _testCallbacks[_currTestIndex]();
    auto testCase = getTestCase(scene);
    testCase->setTestSuite(this);
    testCase->setTestCaseName(_childTestNames[_currTestIndex]);

    Director::getInstance()->replaceScene(scene);
}

void TestSuite::enterPreviousTest()
{
    if (_currTestIndex > 0)
    {
        _currTestIndex -= 1;
    }
    else
    {
        _currTestIndex = (int)_childTestNames.size() - 1;
    }

    auto scene = _testCallbacks[_currTestIndex]();
    auto testCase = getTestCase(scene);
    testCase->setTestSuite(this);
    testCase->setTestCaseName(_childTestNames[_currTestIndex]);

    Director::getInstance()->replaceScene(scene);
}

//TestCase
TestCase::TestCase()
: _priorTestItem(nullptr)
, _restartTestItem(nullptr)
, _nextTestItem(nullptr)
, _titleLabel(nullptr)
, _subtitleLabel(nullptr)
, _testSuite(nullptr)
, _runTime(0.0f)
{
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();

    this->schedule([&](float dt){
        _runTime += dt;
    }, "AccumulatedTimeUse");
}

TestCase::~TestCase()
{
    if (_testSuite)
    {
        _testSuite->release();
        _testSuite = nullptr;
    }
}

void TestCase::setTestSuite(TestSuite* testSuite)
{
    if (_testSuite != testSuite)
    {
        testSuite->retain();
        if (_testSuite)
        {
            _testSuite->release();
        }
        _testSuite = testSuite;
    }
}

TestCase::Type TestCase::getTestType() const
{
    return Type::ROBUSTNESS;
}

float TestCase::getDuration() const
{
    return 0.2f;
}

bool TestCase::init()
{
    if (Scene::init())
    {
        // add title and subtitle
        TTFConfig ttfConfig("fonts/arial.ttf", 26);
        _titleLabel = Label::createWithTTF(ttfConfig, title());
        addChild(_titleLabel, 9999);
        _titleLabel->setPosition(VisibleRect::center().x, VisibleRect::top().y - 30);
        
        ttfConfig.fontSize = 16;
        _subtitleLabel = Label::createWithTTF(ttfConfig, subtitle());
        _subtitleLabel->setMaxLineWidth(VisibleRect::getVisibleRect().size.width);
        addChild(_subtitleLabel, 9999);
        _subtitleLabel->setPosition(VisibleRect::center().x, VisibleRect::top().y - 60);
        
        _priorTestItem = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(TestCase::priorTestCallback, this));
        _restartTestItem = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(TestCase::restartTestCallback, this));
        _nextTestItem = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(TestCase::nextTestCallback, this));
        
        ttfConfig.fontSize = 20;
        auto backLabel = Label::createWithTTF(ttfConfig, "Back");
        auto backItem = MenuItemLabel::create(backLabel, CC_CALLBACK_1(TestCase::onBackCallback, this));

        auto menu = Menu::create(_priorTestItem, _restartTestItem, _nextTestItem, backItem, nullptr);

        menu->setPosition(Vec2::ZERO);
        _priorTestItem->setPosition(VisibleRect::center().x - _restartTestItem->getContentSize().width * 2, VisibleRect::bottom().y + _restartTestItem->getContentSize().height / 2);
        _restartTestItem->setPosition(VisibleRect::center().x, VisibleRect::bottom().y + _restartTestItem->getContentSize().height / 2);
        _nextTestItem->setPosition(VisibleRect::center().x + _restartTestItem->getContentSize().width * 2, VisibleRect::bottom().y + _restartTestItem->getContentSize().height / 2);
        backItem->setPosition(Vec2(VisibleRect::right().x - 50, VisibleRect::bottom().y + 25));

        addChild(menu, 9999);

        return true;
    }

    return false;
}

void TestCase::onEnter()
{
    Scene::onEnter();

    if (_testSuite == nullptr)
    {
        setTestSuite(TestController::getInstance()->getCurrTestSuite());
    }

    if (_testSuite)
    {
        _titleLabel->setString(StringUtils::format("%d", static_cast<int>(_testSuite->getCurrTestIndex() + 1)) + ":" + title());
    }
    else
    {
        _titleLabel->setString(title());
    }
    _subtitleLabel->setString(subtitle());

    if (_testSuite && _testSuite->getChildTestCount() < 2)
    {
        _priorTestItem->setVisible(false);
        _nextTestItem->setVisible(false);
        _restartTestItem->setVisible(false);
    }
}

void TestCase::restartTestCallback(Ref* sender)
{
    if (_testSuite)
    {
        _testSuite->restartCurrTest();
    }
}

void TestCase::nextTestCallback(Ref* sender)
{
    if (_testSuite)
    {
        _testSuite->enterNextTest();
    }
}

void TestCase::priorTestCallback(Ref* sender)
{
    if (_testSuite)
    {
        _testSuite->enterPreviousTest();
    }
}

void TestCase::onBackCallback(Ref* sender)
{
    if (_testSuite)
    {
        _testSuite->backsUpOneLevel();
    }
}