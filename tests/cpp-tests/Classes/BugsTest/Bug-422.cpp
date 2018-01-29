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
// Bug-422 test case by lhunath
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=422
//

#include "Bug-422.h"

USING_NS_CC;

bool Bug422Layer::init()
{
    if (BugsTestBase::init())
    {
        reset();
        return true;
    }

    return false;
}

void Bug422Layer::reset()
{
    static int localtag = 0;
    localtag++;

    // TO TRIGGER THE BUG:
    // remove the itself from parent from an action
    // The menu will be removed, but the instance will be alive
    // and then a new node will be allocated occupying the memory.
    // => CRASH BOOM BANG
    auto node = getChildByTag(localtag-1);
    log("Menu: %p", node);
    removeChild(node, true);
//    [self removeChildByTag:localtag-1 cleanup:NO];

    auto item1 = MenuItemFont::create("One", CC_CALLBACK_1(Bug422Layer::menuCallback, this) );
    log("MenuItemFont: %p", item1);
	MenuItem *item2 = MenuItemFont::create("Two", CC_CALLBACK_1(Bug422Layer::menuCallback, this) );
    auto menu = Menu::create(item1, item2, nullptr);
    menu->alignItemsVertically();

    float x = CCRANDOM_0_1() * 50;
    float y = CCRANDOM_0_1() * 50;
    menu->setPosition(menu->getPosition() + Vec2(x,y));
    addChild(menu, 0, localtag);    

    //[self check:self];
}

void Bug422Layer::check(Node* t)
{
    auto& children = t->getChildren();
    for(const auto &child : children) {
        log("%p, rc: %d", child, child->getReferenceCount());
        check(child);
    }
}

void Bug422Layer::menuCallback(Ref* sender)
{
    reset();
}
