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

#include "Bug-1159.h"

USING_NS_CC;

bool Bug1159Layer::init()
{
    if (BugsTestBase::init())
    {
        auto s = Director::getInstance()->getWinSize();

        auto background = LayerColor::create(Color4B(255, 0, 255, 255));
        addChild(background);

        auto sprite_a = LayerColor::create(Color4B(255, 0, 0, 255), 700, 700);
        sprite_a->setAnchorPoint(Vec2(0.5f, 0.5f));
        sprite_a->setIgnoreAnchorPointForPosition(false);
        sprite_a->setPosition(0.0f, s.height/2);
        addChild(sprite_a);

        sprite_a->runAction(RepeatForever::create(Sequence::create(
                                                        MoveTo::create(1.0f, Vec2(1024.0f, 384.0f)),
                                                        MoveTo::create(1.0f, Vec2(0.0f, 384.0f)),
                                                        nullptr)));

        auto sprite_b = LayerColor::create(Color4B(0, 0, 255, 255), 400, 400);
        sprite_b->setAnchorPoint(Vec2(0.5f, 0.5f));
        sprite_b->setIgnoreAnchorPointForPosition(false);
        sprite_b->setPosition(s.width/2, s.height/2);
        addChild(sprite_b);

        auto label = MenuItemLabel::create(Label::createWithSystemFont("Flip Me", "Helvetica", 24), CC_CALLBACK_1(Bug1159Layer::callBack, this) );
        auto menu = Menu::create(label, nullptr);
        menu->setPosition(s.width - 200.0f, 50.0f);
        addChild(menu);

        return true;
    }

    return false;
}

void Bug1159Layer::callBack(Ref* sender)
{
    Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0f, Bug1159Layer::create(), false));
}

void Bug1159Layer::onExit()
{
    BugsTestBase::onExit();
}
