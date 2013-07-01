//
//  BaseTest.cpp
//  TestCpp
//
//  Created by Ricardo Quesada on 6/6/13.
//
//

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
    LabelTTF* label = LabelTTF::create(pTitle, "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() )
    {
        LabelTTF* l = LabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 60) );
    }

    // add menu
	// CC_CALLBACK_1 == std::bind( function_ptr, instance, std::placeholders::_1, ...)
    MenuItemImage *item1 = MenuItemImage::create(s_pPathB1, s_pPathB2, CC_CALLBACK_1(BaseTest::backCallback, this) );
    MenuItemImage *item2 = MenuItemImage::create(s_pPathR1, s_pPathR2, CC_CALLBACK_1(BaseTest::restartCallback, this) );
    MenuItemImage *item3 = MenuItemImage::create(s_pPathF1, s_pPathF2, CC_CALLBACK_1(BaseTest::nextCallback, this) );

    Menu *menu = Menu::create(item1, item2, item3, NULL);

    menu->setPosition(PointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 1);

}

void BaseTest::onExit()
{
	Layer::onExit();
}

std::string BaseTest::title()
{
	return "";
}

std::string BaseTest::subtitle()
{
	return "";
}

void BaseTest::restartCallback(Object* pSender)
{
	CCLog("override restart!");
}

void BaseTest::nextCallback(Object* pSender)
{
	CCLog("override next!");
}

void BaseTest::backCallback(Object* pSender)
{
	CCLog("override back!");
}
