#include "LayerTest.h"
#include "../testResource.h"

enum 
{
	kTagLayer = 1,
};

CCLayer* nextTestAction();
CCLayer* backTestAction();
CCLayer* restartTestAction();

static int sceneIdx = -1; 

#define MAX_LAYER	4

CCLayer* createTestLayer(int nIndex)
{
	switch(nIndex)
	{
		case 0: return new LayerTest1();
		case 1: return new LayerTest2();
		case 2: return new LayerTestBlend();
        case 3: return new LayerGradient();
	}

	return NULL;
}

CCLayer* nextTestAction()
{
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	CCLayer* pLayer = createTestLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* backTestAction()
{
	sceneIdx--;
	int total = MAX_LAYER;
	if( sceneIdx < 0 )
		sceneIdx += total;	
	
	CCLayer* pLayer = createTestLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* restartTestAction()
{
	CCLayer* pLayer = createTestLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
} 

//------------------------------------------------------------------
//
// LayerTest
//
//------------------------------------------------------------------

LayerTest::LayerTest(void)
{
}

LayerTest::~LayerTest(void)
{
}

string LayerTest::subtitle()
{
	return "";
}

std::string LayerTest::title()
{
	return "No title";
}

void LayerTest::onEnter()
{
	CCLayer::onEnter();

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 32);
	addChild(label, 1);
	label->setPosition( CCPointMake(s.width/2, s.height-50) );

	string subtitle_ = subtitle();
	if (subtitle_.size() > 0)
	{
		CCLabelTTF *l = CCLabelTTF::labelWithString(subtitle_.c_str(), "Thonburi", 16);
		addChild(l, 1);
		l->setPosition(ccp(s.width / 2, s.height - 80));
	}

	CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(LayerTest::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(LayerTest::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(LayerTest::nextCallback) );

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition( CCPointZero );
	item1->setPosition( CCPointMake( s.width/2 - 100,30) );
	item2->setPosition( CCPointMake( s.width/2, 30) );
	item3->setPosition( CCPointMake( s.width/2 + 100,30) );
	
	addChild(menu, 1);	
}

void LayerTest::restartCallback(CCObject* pSender)
{
	CCScene* s = new LayerTestScene();
	s->addChild(restartTestAction()); 

	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void LayerTest::nextCallback(CCObject* pSender)
{
	CCScene* s = new LayerTestScene();
	s->addChild( nextTestAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void LayerTest::backCallback(CCObject* pSender)
{
	CCScene* s = new LayerTestScene();
	s->addChild( backTestAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 

//------------------------------------------------------------------
//
// LayerTest1
//
//------------------------------------------------------------------
void LayerTest1::onEnter()
{
	LayerTest::onEnter();

	setIsTouchEnabled(true);
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor* layer = CCLayerColor::layerWithColorWidthHeight( ccc4(0xFF, 0x00, 0x00, 0x80), 200, 200); 
	
	layer->setIsRelativeAnchorPoint(true);
	layer->setPosition( CCPointMake(s.width/2, s.height/2) );
	addChild(layer, 1, kTagLayer);
}

void LayerTest1::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority + 1, true);
}

void LayerTest1::updateSize(CCTouch*touch)
{
	CCPoint touchLocation = touch->locationInView(touch->view());
	touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	CCSize newSize = CCSizeMake( fabs(touchLocation.x - s.width/2)*2, fabs(touchLocation.y - s.height/2)*2);
	
	CCLayerColor* l = (CCLayerColor*) getChildByTag(kTagLayer);

	l->setContentSize( newSize );
}

bool LayerTest1::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	updateSize(touch);

	return true;
}

void LayerTest1::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	updateSize(touch);
}

void LayerTest1::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	updateSize(touch);
}

std::string LayerTest1::title()
{
	return "ColorLayer resize (tap & move)";
}

//------------------------------------------------------------------
//
// LayerTest2
//
//------------------------------------------------------------------
void LayerTest2::onEnter()
{
	LayerTest::onEnter();

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor* layer1 = CCLayerColor::layerWithColorWidthHeight( ccc4(255, 255, 0, 80), 100, 300);
	layer1->setPosition(CCPointMake(s.width/3, s.height/2));
	layer1->setIsRelativeAnchorPoint(true);
	addChild(layer1, 1);
	
	CCLayerColor* layer2 = CCLayerColor::layerWithColorWidthHeight( ccc4(0, 0, 255, 255), 100, 300);
	layer2->setPosition(CCPointMake((s.width/3)*2, s.height/2));
	layer2->setIsRelativeAnchorPoint(true);
	addChild(layer2, 1);
	
	CCActionInterval* actionTint = CCTintBy::actionWithDuration(2, -255, -127, 0);
	CCActionInterval* actionTintBack = actionTint->reverse();
	CCActionInterval* seq1 = (CCActionInterval*)CCSequence::actions( actionTint, actionTintBack, NULL);
	layer1->runAction(seq1);

	CCActionInterval* actionFade = CCFadeOut::actionWithDuration(2.0f);
	CCActionInterval* actionFadeBack = actionFade->reverse();
	CCActionInterval* seq2 = (CCActionInterval*)CCSequence::actions(actionFade, actionFadeBack, NULL);		
	layer2->runAction(seq2);
}

std::string LayerTest2::title()
{
	return "ColorLayer: fade and tint";
}

//------------------------------------------------------------------
//
// LayerTestBlend
//
//------------------------------------------------------------------

LayerTestBlend::LayerTestBlend()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor* layer1 = CCLayerColor::layerWithColor( ccc4(255, 255, 255, 80) );
	
	CCSprite* sister1 = CCSprite::spriteWithFile(s_pPathSister1);
	CCSprite* sister2 = CCSprite::spriteWithFile(s_pPathSister2);
	
	addChild(sister1);
	addChild(sister2);
	addChild(layer1, 100, kTagLayer);
	
	sister1->setPosition( CCPointMake( 160, s.height/2) );
	sister2->setPosition( CCPointMake( 320, s.height/2) );

	schedule( schedule_selector(LayerTestBlend::newBlend), 1.0f);
}

void LayerTestBlend::newBlend(ccTime dt)
{
 	CCLayerColor *layer = (CCLayerColor*)getChildByTag(kTagLayer);

    GLenum src;
    GLenum dst;

	if( layer->getBlendFunc().dst == GL_ZERO )
    {
        src = CC_BLEND_SRC;
        dst = CC_BLEND_DST;
    }
	else
    {
        src = GL_ONE_MINUS_DST_COLOR;
        dst = GL_ZERO;
    }

    ccBlendFunc bf = {src, dst};
    layer->setBlendFunc( bf );
}


std::string LayerTestBlend::title()
{
	return "ColorLayer: blend";
}

//------------------------------------------------------------------
//
// LayerGradient
//
//------------------------------------------------------------------
LayerGradient::LayerGradient()
{
    CCLayerGradient* layer1 = CCLayerGradient::layerWithColor(ccc4(255,0,0,255), ccc4(0,255,0,255), ccp(0.9f, 0.9f));
    addChild(layer1, 0, kTagLayer);

    setIsTouchEnabled(true);

	CCLabelTTF *label1 = CCLabelTTF::labelWithString("Compressed Interpolation: Enabled", "Marker Felt", 26);
	CCLabelTTF *label2 = CCLabelTTF::labelWithString("Compressed Interpolation: Disabled", "Marker Felt", 26);
	CCMenuItemLabel *item1 = CCMenuItemLabel::itemWithLabel(label1);
	CCMenuItemLabel *item2 = CCMenuItemLabel::itemWithLabel(label2);
	CCMenuItemToggle *item = CCMenuItemToggle::itemWithTarget(this, menu_selector(LayerGradient::toggleItem), item1, item2, NULL);

	CCMenu *menu = CCMenu::menuWithItems(item, NULL);
	addChild(menu);
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	menu->setPosition(ccp(s.width / 2, 100));
}

void LayerGradient::toggleItem(CCObject *sender)
{
	CCLayerGradient *gradient = (CCLayerGradient*)getChildByTag(kTagLayer);
	gradient->setIsCompressedInterpolation(! gradient->getIsCompressedInterpolation());
}

void LayerGradient::ccTouchesMoved(CCSet * touches, CCEvent *event)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSetIterator it = touches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint start = touch->locationInView(touch->view());	
    start = CCDirector::sharedDirector()->convertToGL(start);

    CCPoint diff = ccpSub( ccp(s.width/2,s.height/2), start);	
    diff = ccpNormalize(diff);

    CCLayerGradient *gradient = (CCLayerGradient*) getChildByTag(1);
    gradient->setVector(diff);
}

std::string LayerGradient::title()
{
    return "LayerGradient";
}

string LayerGradient::subtitle()
{
	return "Touch the screen and move your finger";
}

void LayerTestScene::runThisTest()
{
    CCLayer* pLayer = nextTestAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
