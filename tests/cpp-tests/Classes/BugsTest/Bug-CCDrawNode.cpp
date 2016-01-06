//
// CCDrawNode::onDrawGLPoint & CCDrawNode::onDrawGLLine miss
//  calling GL::blendFunc, so when a sprite set blendFunc, these
//  function will get a wrong result.
// In this test, see a red line when bug resolved.
//

#include "Bug-CCDrawNode.h"

USING_NS_CC;

bool BugDrawNodeLayer::init()
{
    if (BugsTestBase::init())
    {
        auto size = Director::getInstance()->getWinSize();
        auto testSprite = Sprite::create("cocosui/CloseNormal.png");
        BlendFunc blend;
        blend.src = GL_ZERO;
        blend.dst = GL_ONE_MINUS_SRC_ALPHA;
        testSprite->setBlendFunc(blend);
        testSprite->setPosition(Vec2(size.width / 2, size.height / 2));
        testSprite->setScale(10);
        addChild(testSprite);

        auto drawNode = DrawNode::create();
        drawNode->drawLine(Vec2(0, 0), Vec2(size.width, size.height), Color4F(1, 0, 0, 0.5f));
        Vec2 point = Vec2(size.width / 2, size.height / 2);
        drawNode->drawPoint(point, 8, Color4F(1, 0, 0, 0.5f));
        addChild(drawNode);

        auto label = Label::create();
        label->setString(std::string("If you see a red line with a block at center, the bug is fixed!"));
        label->setPosition(size.width / 2, size.height / 4);
        label->setTextColor(Color4B::ORANGE);
        addChild(label);

        return true;
    }

    return false;
}
