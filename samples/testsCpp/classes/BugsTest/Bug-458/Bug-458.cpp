//
// Bug-458 test case by nedrafehi
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=458
//

#include "Bug-458.h"
#include "QuestionContainerSprite.h"

bool Bug458Layer::init()
{
    if(BugsTestBaseLayer::init())
    {
        // ask director the the window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();

        QuestionContainerSprite* question = new QuestionContainerSprite();
        QuestionContainerSprite* question2 = new QuestionContainerSprite();
        question->init();
        question2->init();

//        [question setContentSize:CGSizeMake(50,50)];
//        [question2 setContentSize:CGSizeMake(50,50)];
        
        CCMenuItemSprite* sprite = CCMenuItemSprite::create(question2, question, this, menu_selector(Bug458Layer::selectAnswer));
        CCLayerColor* layer = CCLayerColor::create(ccc4(0,0,255,255), 100, 100);
        question->release();
        question2->release();

        CCLayerColor* layer2 = CCLayerColor::create(ccc4(255,0,0,255), 100, 100);
        CCMenuItemSprite* sprite2 = CCMenuItemSprite::create(layer, layer2, this, menu_selector(Bug458Layer::selectAnswer));        
        CCMenu* menu = CCMenu::create(sprite, sprite2, NULL);
        menu->alignItemsVerticallyWithPadding(100);
        menu->setPosition(ccp(size.width / 2, size.height / 2));

        // add the label as a child to this Layer
        addChild(menu);

        return true;
    }
    return false;
}

void Bug458Layer::selectAnswer(CCObject* sender)
{
    CCLog("Selected");
}
