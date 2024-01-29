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
// Bug-458 test case by nedrafehi
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=458
//

#include "Bug-458.h"
#include "QuestionContainerSprite.h"

USING_NS_CC;

bool Bug458Layer::init()
{
    if(BugsTestBase::init())
    {
        // ask director the the window size
        auto size = Director::getInstance()->getWinSize();

        auto question = new (std::nothrow) QuestionContainerSprite();
        auto question2 = new (std::nothrow) QuestionContainerSprite();
        question->init();
        question2->init();

//        [question setContentSize:CGSizeMake(50,50)];
//        [question2 setContentSize:CGSizeMake(50,50)];
        
        auto sprite = MenuItemSprite::create(question2, question, CC_CALLBACK_1(Bug458Layer::selectAnswer, this) );
        auto layer = LayerColor::create(Color4B(0,0,255,255), 100, 100);
        question->release();
        question2->release();

        auto layer2 = LayerColor::create(Color4B(255,0,0,255), 100, 100);
        auto sprite2 = MenuItemSprite::create(layer, layer2, CC_CALLBACK_1(Bug458Layer::selectAnswer, this) );
        auto menu = Menu::create(sprite, sprite2, nullptr);
        menu->alignItemsVerticallyWithPadding(100);
        menu->setPosition(size.width / 2, size.height / 2);

        // add the label as a child to this Layer
        addChild(menu);

        return true;
    }
    return false;
}

void Bug458Layer::selectAnswer(Ref* sender)
{
    log("Selected");
}
