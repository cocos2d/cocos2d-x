#include "LayoutAlignmentTest.h"
#include "../testResource.h"
#include <ui/UIVBox.h>
#include <ui/UIHBox.h>
#include <ui/UIText.h>

USING_NS_CC;
using namespace cocos2d::ui;

LayoutAlignmentTests::LayoutAlignmentTests()
{
    ADD_TEST_CASE(LayoutAlignmentHBoxTest);
    ADD_TEST_CASE(LayoutAlignmentVBoxTest);
}

static void addTestLabelsToLayout(Layout* layout, const std::string& textString,
                                  LinearLayoutParameter::LinearGravity gravity)
{
    Text* label1 = Text::create("Align", "fonts/Marker Felt.ttf", 12);
    Text* label2 = Text::create(textString, "fonts/Marker Felt.ttf", 12);

    label1->setTextColor(Color4B::WHITE);
    label2->setTextColor(Color4B::WHITE);

    LinearLayoutParameter *layoutParam = LinearLayoutParameter::create();
    layoutParam->setGravity(gravity);

    label1->setLayoutParameter(layoutParam);
    label2->setLayoutParameter(layoutParam);

    layout->addChild(label1);
    layout->addChild(label2);
}

static void drawBoundingBox(DrawNode* drawNode, Node* node) {
    Rect boundingBox = node->getBoundingBox();

    Vec2 a = Vec2(boundingBox.getMinX(), boundingBox.getMinY());
    Vec2 b = Vec2(boundingBox.getMaxX(), boundingBox.getMaxY());

    drawNode->drawRect(a, b, Color4F::WHITE);
}

// HBox alignment

LayoutAlignmentHBoxTest::LayoutAlignmentHBoxTest()
{

}

LayoutAlignmentHBoxTest::~LayoutAlignmentHBoxTest()
{
}

std::string LayoutAlignmentHBoxTest::title() const
{
    return "Layout Alignment Test";
}

void LayoutAlignmentHBoxTest::onEnter()
{
    TestCase::onEnter();

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto drawNode = DrawNode::create();
    drawNode->setPosition(Vec2(0, 0));
    drawNode->setContentSize(visibleSize);
    this->addChild(drawNode);

    Size boxSize(200, 50);
    float boxMargin = 10;
    Size boxOffset(0, boxSize.height + boxMargin);
    Vec2 boxesOrigin((visibleSize.width - boxSize.width) / 2, 60);

    auto hboxAlignedLeft = HBox::create();
    hboxAlignedLeft->setPosition(boxesOrigin + 0 * boxOffset);
    hboxAlignedLeft->setContentSize(boxSize);
    hboxAlignedLeft->setAlignment(Layout::Alignment::LEFT);
    addTestLabelsToLayout(hboxAlignedLeft, "Left",
                          LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
    this->addChild(hboxAlignedLeft);

    auto hboxAlignedCenter = HBox::create();
    hboxAlignedCenter->setPosition(boxesOrigin + 1 * boxOffset);
    hboxAlignedCenter->setContentSize(boxSize);
    hboxAlignedCenter->setAlignment(Layout::Alignment::CENTER);
    addTestLabelsToLayout(hboxAlignedCenter, "Center",
                          LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
    this->addChild(hboxAlignedCenter);

    auto hboxAlignedRight = HBox::create();
    hboxAlignedRight->setPosition(boxesOrigin + 2 * boxOffset);
    hboxAlignedRight->setContentSize(boxSize);
    hboxAlignedRight->setAlignment(Layout::Alignment::RIGHT);
    addTestLabelsToLayout(hboxAlignedRight, "Right",
                          LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
    this->addChild(hboxAlignedRight);

    drawBoundingBox(drawNode, hboxAlignedLeft);
    drawBoundingBox(drawNode, hboxAlignedCenter);
    drawBoundingBox(drawNode, hboxAlignedRight);
}

std::string LayoutAlignmentHBoxTest::subtitle() const
{
    return "Alignment options for HBox";
}


// VBox alignment

LayoutAlignmentVBoxTest::LayoutAlignmentVBoxTest()
{
}

LayoutAlignmentVBoxTest::~LayoutAlignmentVBoxTest()
{
}

std::string LayoutAlignmentVBoxTest::title() const
{
    return "Layout Alignment Test";
}

void LayoutAlignmentVBoxTest::onEnter()
{
    TestCase::onEnter();

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto drawNode = DrawNode::create();
    drawNode->setPosition(Vec2(0, 0));
    drawNode->setContentSize(visibleSize);
    this->addChild(drawNode);

    Size boxSize(50, 180);
    float boxMargin = 10;
    Size boxOffset(boxSize.width + boxMargin, 0);
    Vec2 boxesOrigin((visibleSize.width - (boxSize + boxOffset * 2).width) / 2, 60);

    auto vboxAlignedTop = VBox::create();
    vboxAlignedTop->setPosition(boxesOrigin + 0 * boxOffset);
    vboxAlignedTop->setContentSize(boxSize);
    vboxAlignedTop->setAlignment(Layout::Alignment::TOP);
    addTestLabelsToLayout(vboxAlignedTop, "Top",
                          LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
    this->addChild(vboxAlignedTop);

    auto vboxAlignedCenter = VBox::create();
    vboxAlignedCenter->setPosition(boxesOrigin + 1 * boxOffset);
    vboxAlignedCenter->setContentSize(boxSize);
    vboxAlignedCenter->setAlignment(Layout::Alignment::CENTER);
    addTestLabelsToLayout(vboxAlignedCenter, "Center",
                          LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
    this->addChild(vboxAlignedCenter);

    auto vboxAlignedBottom = VBox::create();
    vboxAlignedBottom->setPosition(boxesOrigin + 2 * boxOffset);
    vboxAlignedBottom->setContentSize(boxSize);
    vboxAlignedBottom->setAlignment(Layout::Alignment::BOTTOM);
    addTestLabelsToLayout(vboxAlignedBottom, "Bottom",
                          LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
    this->addChild(vboxAlignedBottom);

    drawBoundingBox(drawNode, vboxAlignedTop);
    drawBoundingBox(drawNode, vboxAlignedCenter);
    drawBoundingBox(drawNode, vboxAlignedBottom);
}

std::string LayoutAlignmentVBoxTest::subtitle() const
{
    return "Alignment options for VBox";
}
