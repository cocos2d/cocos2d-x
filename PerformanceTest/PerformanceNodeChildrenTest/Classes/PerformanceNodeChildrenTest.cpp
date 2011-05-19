#include "PerformanceNodeChildrenTest.h"

using namespace cocos2d;

enum {
    kTagInfoLayer = 1,
    kTagMainLayer = 2,
    kTagLabelAtlas = 3,

    kTagBase = 20000,

    TEST_COUNT = 4,
};

static int s_nCurCase = 0;

////////////////////////////////////////////////////////
//
// NodeChildrenMainScene
//
////////////////////////////////////////////////////////
void NodeChildrenMainScene::initWithQuantityOfNodes(unsigned int nNodes)
{
    CCScene::init();
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // Title
    CCLabelTTF *label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 40);
    addChild(label, 1);
    label->setPosition(ccp(s.width/2, s.height-32));
    label->setColor(ccc3(255,255,40));

    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        CCLabelTTF *l = CCLabelTTF::labelWithString(strSubTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(ccp(s.width/2, s.height-80));
    }

    lastRenderedCount = 0;
    currentQuantityOfNodes = 0;
    quantityOfNodes = nNodes;

    CCMenuItemFont::setFontSize(65);
    CCMenuItemFont *decrease = CCMenuItemFont::itemFromString(" - ", this, menu_selector(NodeChildrenMainScene::onDecrease));
    decrease->setColor(ccc3(0,200,20));
    CCMenuItemFont *increase = CCMenuItemFont::itemFromString(" + ", this, menu_selector(NodeChildrenMainScene::onIncrease));
    increase->setColor(ccc3(0,200,20));

    CCMenu *menu = CCMenu::menuWithItems(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(ccp(s.width/2, s.height/2+15));
    addChild(menu, 1);

    CCLabelTTF *infoLabel = CCLabelTTF::labelWithString("0 nodes", "Marker Felt", 30);
    infoLabel->setColor(ccc3(0,200,20));
    infoLabel->setPosition(ccp(s.width/2, s.height/2-15));
    addChild(infoLabel, 1, kTagInfoLayer);

    CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage("Images/b1.png", "Images/b2.png", this, menu_selector(NodeChildrenMainScene::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage("Images/r1.png", "Images/r2.png", this, menu_selector(NodeChildrenMainScene::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage("Images/f1.png", "Images/f2.png", this, menu_selector(NodeChildrenMainScene::nextCallback) );
    CCMenu* pMenu = CCMenu::menuWithItems(item1, item2, item3, NULL);
    addChild(pMenu, 1);
    pMenu->alignItemsHorizontally();
    pMenu-> setPosition(ccp(s.width/2, 30));

    // close menu item
    CCMenuItemImage* pCloseItem = CCMenuItemImage::itemFromNormalImage("CloseNormal.png", "CloseSelected.png", this, menu_selector(NodeChildrenMainScene::menuCloseCallback));
    CCMenu* pCloseMenu = CCMenu::menuWithItems(pCloseItem, NULL);
    addChild(pCloseMenu, 1);
    pCloseMenu->setPosition( CCPointZero );
    pCloseItem->setPosition(CCPointMake( s.width - 30, 30));

    updateQuantityLabel();
    updateQuantityOfNodes();
}

void NodeChildrenMainScene::restartCallback(CCObject* pSender)
{
    showCurrentTest();
}

void NodeChildrenMainScene::nextCallback(CCObject* pSender)
{
    s_nCurCase++;
    s_nCurCase = s_nCurCase % TEST_COUNT;

    showCurrentTest();
}

void NodeChildrenMainScene::backCallback(CCObject* pSender)
{
    s_nCurCase--;
    if( s_nCurCase < 0 )
        s_nCurCase += TEST_COUNT;

    showCurrentTest();
}

void NodeChildrenMainScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
}

void NodeChildrenMainScene::showCurrentTest()
{
    NodeChildrenMainScene* pScene = NULL;

    switch (s_nCurCase)
    {
    case 0:
        pScene = new IterateSpriteSheetCArray();
        break;
    case 1:
        pScene = new AddSpriteSheet();
        break;
    case 2:
        pScene = new RemoveSpriteSheet();
        break;
    case 3:
        pScene = new ReorderSpriteSheet();
        break;
    }

    if (pScene)
    {
        pScene->initWithQuantityOfNodes(quantityOfNodes);

        CCDirector::sharedDirector()->replaceScene(pScene);
        pScene->release();
    }
}

void NodeChildrenMainScene::onDecrease(CCObject* pSender)
{
    quantityOfNodes -= kNodesIncrease;
    if( quantityOfNodes < 0 )
        quantityOfNodes = 0;

    updateQuantityLabel();
    updateQuantityOfNodes();
    CCLog("current sprite number:%d", currentQuantityOfNodes);
}

void NodeChildrenMainScene::onIncrease(CCObject* pSender)
{
    quantityOfNodes += kNodesIncrease;
    if( quantityOfNodes > kMaxNodes )
        quantityOfNodes = kMaxNodes;

    updateQuantityLabel();
    updateQuantityOfNodes();
    CCLog("current sprite number:%d", currentQuantityOfNodes);
}

std::string NodeChildrenMainScene::title()
{
    return "No title";
}

std::string NodeChildrenMainScene::subtitle()
{
    return "";
}

void NodeChildrenMainScene::updateQuantityLabel()
{
    if( quantityOfNodes != lastRenderedCount )
    {
        CCLabelTTF *infoLabel = (CCLabelTTF *) getChildByTag(kTagInfoLayer);
        char str[20] = {0};
        sprintf(str, "%u nodes", quantityOfNodes);
        infoLabel->setString(str);

        lastRenderedCount = quantityOfNodes;
    }
}

////////////////////////////////////////////////////////
//
// IterateSpriteSheet
//
////////////////////////////////////////////////////////
IterateSpriteSheet::~IterateSpriteSheet()
{
    CCProfiler::releaseTimer(_profilingTimer);
    _profilingTimer = NULL;
}

void IterateSpriteSheet::updateQuantityOfNodes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // increase nodes
    if( currentQuantityOfNodes < quantityOfNodes )
    {
        for(int i = 0; i < (quantityOfNodes-currentQuantityOfNodes); i++)
        {
            CCSprite *sprite = CCSprite::spriteWithTexture(batchNode->getTexture(), CCRectMake(0, 0, 32, 32));
            batchNode->addChild(sprite);
            sprite->setPosition(ccp( CCRANDOM_0_1()*s.width, CCRANDOM_0_1()*s.height));
        }
    }

    // decrease nodes
    else if ( currentQuantityOfNodes > quantityOfNodes )
    {
        for(int i = 0; i < (currentQuantityOfNodes-quantityOfNodes); i++)
        {
            int index = currentQuantityOfNodes-i-1;
            batchNode->removeChildAtIndex(index, true);
        }
    }

    currentQuantityOfNodes = quantityOfNodes;
}

void IterateSpriteSheet::initWithQuantityOfNodes(unsigned int nNodes)
{
    batchNode = CCSpriteBatchNode::batchNodeWithFile("Images/spritesheet1.png");
    addChild(batchNode);

    NodeChildrenMainScene::initWithQuantityOfNodes(nNodes);

    _profilingTimer = CCProfiler::timerWithName(profilerName().c_str(), this);

    scheduleUpdate();
}

std::string IterateSpriteSheet::profilerName()
{
    return "none";
}

////////////////////////////////////////////////////////
//
// IterateSpriteSheetCArray
//
////////////////////////////////////////////////////////
void IterateSpriteSheetCArray::update(ccTime dt)
{
    // iterate using fast enumeration protocol
    CCArray* pChildren = batchNode->getChildren();
    CCObject* pObject = NULL;

    CCProfilingBeginTimingBlock(_profilingTimer);

    CCARRAY_FOREACH(pChildren, pObject)
    {
        CCSprite* pSprite = (CCSprite*)pObject;
        pSprite->setIsVisible(false);    }

    CCProfilingEndTimingBlock(_profilingTimer);
}

std::string IterateSpriteSheetCArray::title()
{
    return "B - Iterate SpriteSheet";
}

std::string IterateSpriteSheetCArray::subtitle()
{
    return "Iterate children using C Array API. See console";
}

std::string IterateSpriteSheetCArray::profilerName()
{
    return "iter c-array";
}

////////////////////////////////////////////////////////
//
// AddRemoveSpriteSheet
//
////////////////////////////////////////////////////////
AddRemoveSpriteSheet::~AddRemoveSpriteSheet()
{
    CCProfiler::releaseTimer(_profilingTimer);
    _profilingTimer = NULL;
}

void AddRemoveSpriteSheet::initWithQuantityOfNodes(unsigned int nNodes)
{
    batchNode = CCSpriteBatchNode::batchNodeWithFile("Images/spritesheet1.png");
    addChild(batchNode);

    NodeChildrenMainScene::initWithQuantityOfNodes(nNodes);

    _profilingTimer = CCProfiler::timerWithName(profilerName().c_str(), this);

    scheduleUpdate();
}

void AddRemoveSpriteSheet::updateQuantityOfNodes()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // increase nodes
    if( currentQuantityOfNodes < quantityOfNodes )
    {
        for (int i=0; i < (quantityOfNodes-currentQuantityOfNodes); i++)
        {
            CCSprite *sprite = CCSprite::spriteWithTexture(batchNode->getTexture(), CCRectMake(0, 0, 32, 32));
            batchNode->addChild(sprite);
            sprite->setPosition(ccp( CCRANDOM_0_1()*s.width, CCRANDOM_0_1()*s.height));
            sprite->setIsVisible(false);
        }
    }
    // decrease nodes
    else if ( currentQuantityOfNodes > quantityOfNodes )
    {
        for(int i=0;i < (currentQuantityOfNodes-quantityOfNodes);i++)
        {
            int index = currentQuantityOfNodes-i-1;
            batchNode->removeChildAtIndex(index, true);
        }
    }

    currentQuantityOfNodes = quantityOfNodes;
}

std::string AddRemoveSpriteSheet::profilerName()
{
    return "none";
}

////////////////////////////////////////////////////////
//
// AddSpriteSheet
//
////////////////////////////////////////////////////////
void AddSpriteSheet::update(ccTime dt)
{
    // reset seed
    //srandom(0);

    // 15 percent
    int totalToAdd = currentQuantityOfNodes * 0.15f;

    if( totalToAdd > 0 )
    {
        CCArray* sprites = CCArray::arrayWithCapacity(totalToAdd);
        int		 *zs      = new int[totalToAdd];

        // Don't include the sprite creation time and random as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            CCSprite* pSprite = CCSprite::spriteWithTexture(batchNode->getTexture(), CCRectMake(0,0,32,32));
            sprites->addObject(pSprite);
            zs[i]      = CCRANDOM_MINUS1_1() * 50;
        }

        // add them with random Z (very important!)
        CCProfilingBeginTimingBlock(_profilingTimer);

        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild((CCNode*) (sprites->objectAtIndex(i)), zs[i], kTagBase+i);
        }

        CCProfilingEndTimingBlock(_profilingTimer);

        // remove them
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChildByTag(kTagBase+i, true);
        }

        delete [] zs;
    }
}

std::string AddSpriteSheet::title()
{
    return "C - Add to spritesheet";
}

std::string AddSpriteSheet::subtitle()
{
    return "Adds %10 of total sprites with random z. See console";
}

std::string AddSpriteSheet::profilerName()
{
    return "add sprites";
}

////////////////////////////////////////////////////////
//
// RemoveSpriteSheet
//
////////////////////////////////////////////////////////
void RemoveSpriteSheet::update(ccTime dt)
{
    //srandom(0);

    // 15 percent
    int totalToAdd = currentQuantityOfNodes * 0.15f;

    if( totalToAdd > 0 )
    {
        CCArray* sprites = CCArray::arrayWithCapacity(totalToAdd);

        // Don't include the sprite creation time as part of the profiling
        for(int i=0;i<totalToAdd;i++)
        {
            CCSprite* pSprite = CCSprite::spriteWithTexture(batchNode->getTexture(), CCRectMake(0,0,32,32));
            sprites->addObject(pSprite);
        }

        // add them with random Z (very important!)
        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild((CCNode*) (sprites->objectAtIndex(i)), CCRANDOM_MINUS1_1() * 50, kTagBase+i);
        }

        // remove them
        CCProfilingBeginTimingBlock(_profilingTimer);

        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChildByTag(kTagBase+i, true);
        }

        CCProfilingEndTimingBlock(_profilingTimer);
    }
}

std::string RemoveSpriteSheet::title()
{
    return "D - Del from spritesheet";
}

std::string RemoveSpriteSheet::subtitle()
{
    return "Remove %10 of total sprites placed randomly. See console";
}

std::string RemoveSpriteSheet::profilerName()
{
    return "remove sprites";
}

////////////////////////////////////////////////////////
//
// ReorderSpriteSheet
//
////////////////////////////////////////////////////////
void ReorderSpriteSheet::update(ccTime dt)
{
    //srandom(0);

    // 15 percent
    int totalToAdd = currentQuantityOfNodes * 0.15f;

    if( totalToAdd > 0 )
    {
        CCArray* sprites = CCArray::arrayWithCapacity(totalToAdd);

        // Don't include the sprite creation time as part of the profiling
        for(int i=0;i<totalToAdd;i++)
        {
            CCSprite* pSprite = CCSprite::spriteWithTexture(batchNode->getTexture(), CCRectMake(0,0,32,32));
            sprites->addObject(pSprite);
        }

        // add them with random Z (very important!)
        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild((CCNode*) (sprites->objectAtIndex(i)), CCRANDOM_MINUS1_1() * 50, kTagBase+i);
        }

        //		[batchNode sortAllChildren];

        // reorder them
        CCProfilingBeginTimingBlock(_profilingTimer);

        for( int i=0;i <  totalToAdd;i++)
        {
            CCNode* pNode = (CCNode*) (batchNode->getChildren()->objectAtIndex(i));
            batchNode->reorderChild(pNode, CCRANDOM_MINUS1_1() * 50);
        }

        CCProfilingEndTimingBlock(_profilingTimer);

        // remove them
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChildByTag(kTagBase+i, true);
        }
    }
}

std::string ReorderSpriteSheet::title()
{
    return "E - Reorder from spritesheet";
}

std::string ReorderSpriteSheet::subtitle()
{
    return "Reorder %10 of total sprites placed randomly. See console";
}

std::string ReorderSpriteSheet::profilerName()
{
    return "reorder sprites";
}
