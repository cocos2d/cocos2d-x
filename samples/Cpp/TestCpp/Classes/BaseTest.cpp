/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include "VisibleRect.h"
#include "testResource.h"


USING_NS_CC;

void BaseTest::onEnter()
{
	Layer::onEnter();

	// add title and subtitle
    std::string str = title();
    const char * pTitle = str.c_str();
    auto label = LabelTTF::create(pTitle, "Arial", 32);
    addChild(label, 9999);
    label->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() )
    {
        auto l = LabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        addChild(l, 9999);
        l->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - 60) );
    }

    // add menu
	// CC_CALLBACK_1 == std::bind( function_ptr, instance, std::placeholders::_1, ...)
    auto item1 = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(BaseTest::backCallback, this) );
    auto item2 = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(BaseTest::restartCallback, this) );
    auto item3 = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(BaseTest::nextCallback, this) );

    auto menu = Menu::create(item1, item2, item3, NULL);

    menu->setPosition(Point::ZERO);
    item1->setPosition(Point(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(Point(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(Point(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 9999);

}

void BaseTest::onExit()
{
	Layer::onExit();
}

std::string BaseTest::title() const
{
	return "";
}

std::string BaseTest::subtitle() const
{
	return "";
}

void BaseTest::restartCallback(Object* sender)
{
	log("override restart!");
}

void BaseTest::nextCallback(Object* sender)
{
	log("override next!");
}

void BaseTest::backCallback(Object* sender)
{
	log("override back!");
}
