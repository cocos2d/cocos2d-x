/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

//
// CCDrawNode::onDrawGLPoint & CCDrawNode::onDrawGLLine miss
//  calling GL::blendFunc, so when a sprite set blendFunc, these
//  function will get a wrong result.
// In this test, see a red line when bug resolved.
//

#include "Bug-CCDrawNode.h"
#include "renderer/backend/Types.h"

USING_NS_CC;

bool BugDrawNodeLayer::init()
{
    if (BugsTestBase::init())
    {
        auto size = Director::getInstance()->getWinSize();
        auto testSprite = Sprite::create("Images/close.png");
        BlendFunc blend;
        blend.src = backend::BlendFactor::ZERO;
        blend.dst = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
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
