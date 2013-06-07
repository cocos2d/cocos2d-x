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
	CCLayer::onEnter();

	// add title and subtitle
    std::string str = title();
    const char * pTitle = str.c_str();
    CCLabelTTF* label = CCLabelTTF::create(pTitle, "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() )
    {
        CCLabelTTF* l = CCLabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 60) );
    }

    // add menu
    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, std::bind( &BaseTest::backCallback, this, std::placeholders::_1) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, std::bind( &BaseTest::restartCallback, this, std::placeholders::_1) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, std::bind( &BaseTest::nextCallback, this, std::placeholders::_1) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 1);

}

void BaseTest::onExit()
{
	CCLayer::onExit();
}

std::string BaseTest::title()
{
	return "";
}

std::string BaseTest::subtitle()
{
	return "";
}

void BaseTest::restartCallback(CCObject* pSender)
{
	CCLog("override restart!");
}

void BaseTest::nextCallback(CCObject* pSender)
{
	CCLog("override next!");
}

void BaseTest::backCallback(CCObject* pSender)
{
	CCLog("override back!");
}
