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

// Import the interfaces
#include"Bug-914.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool Bug914Layer::init()
{
    // always call "super" init
    // Apple recommends to re-assign "self" with the "super" return value
    if (BugsTestBase::init())
    {
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(Bug914Layer::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(Bug914Layer::onTouchesMoved, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        // ask director the the window size
        auto size = Director::getInstance()->getWinSize();
        LayerColor *layer;
        for( int i=0;i < 5;i++)
        {
            layer = LayerColor::create(Color4B(i*20, i*20, i*20,255));
            layer->setContentSize(Size(i*100.0f, i*100.0f));
            layer->setPosition(size.width/2, size.height/2);
            layer->setAnchorPoint(Vec2(0.5f, 0.5f));
            layer->setIgnoreAnchorPointForPosition(false);
            addChild(layer, -1-i);
        }

        // create and initialize a Label
        auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 64.0f);
        auto item1 = MenuItemFont::create("restart", CC_CALLBACK_1(Bug914Layer::restart, this));

        auto menu = Menu::create(item1, nullptr);
        menu->alignItemsVertically();
        menu->setPosition(size.width/2, 100);
        addChild(menu);

        // position the label on the center of the screen
        label->setPosition(size.width /2 , size.height/2);

        // add the label as a child to this Layer
        addChild(label);
        return true;
    }
    return false;
}

void Bug914Layer::onTouchesMoved(const std::vector<Touch*>& touches, Event * event)
{
    log("Number of touches: %d", (int)touches.size());
}

void Bug914Layer::onTouchesBegan(const std::vector<Touch*>& touches, Event * event)
{
    onTouchesMoved(touches, event);
}

void Bug914Layer::restart(Ref* sender)
{
    Director::getInstance()->replaceScene(Bug914Layer::create());
}
