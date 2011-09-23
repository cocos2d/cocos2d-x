#include "CCConfiguration.h"
#include "RenderTextureTest.h"

// Test #1 by Jason Booth (slipster216)
// Test #3 by David Deaco (ddeaco)

static int sceneIdx = -1; 

#define MAX_LAYER    4

CCLayer* createTestCase(int nIndex)
{

    switch(nIndex)
    {
    case 0: return new RenderTextureTest();
    case 1: return new RenderTextureIssue937();
	case 2: return new RenderTextureZbuffer();
	case 3: return new RenderTextureSave();
    }

    return NULL;
}

CCLayer* nextTestCase()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = createTestCase(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backTestCase()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    

    CCLayer* pLayer = createTestCase(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartTestCase()
{
    CCLayer* pLayer = createTestCase(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

void RenderTextureTestDemo::onEnter()
{
    CCLayer::onEnter();
	CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
    addChild(label, 1);
    label->setPosition( ccp(s.width/2, s.height-50) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() ) 
    {
        CCLabelTTF* l = CCLabelTTF::labelWithString(strSubtitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition( ccp(s.width/2, s.height-80) );
    }    

    CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage("Images/b1.png", "Images/b2.png", this, menu_selector(RenderTextureTestDemo::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage("Images/r1.png","Images/r2.png", this, menu_selector(RenderTextureTestDemo::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage("Images/f1.png", "Images/f2.png", this, menu_selector(RenderTextureTestDemo::nextCallback) );

    CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

    menu->setPosition( CCPointZero );
    item1->setPosition( ccp( s.width/2 - 100,30) );
    item2->setPosition( ccp( s.width/2, 30) );
    item3->setPosition( ccp( s.width/2 + 100,30) );

    addChild(menu, 1);
}

void RenderTextureTestDemo::restartCallback(CCObject* pSender)
{
    CCScene* s = new RenderTextureScene();
    s->addChild(restartTestCase()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void RenderTextureTestDemo::nextCallback(CCObject* pSender)
{
    CCScene* s = new RenderTextureScene();
    s->addChild( nextTestCase() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void RenderTextureTestDemo::backCallback(CCObject* pSender)
{
    CCScene* s = new RenderTextureScene();
    s->addChild( backTestCase() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 

std::string RenderTextureTestDemo::title()
{
    return "Render Texture Test";
}

std::string RenderTextureTestDemo::subtitle()
{
    return "";
}

RenderTextureTest::RenderTextureTest()
: m_brush(NULL)
{
	if (CCConfiguration::sharedConfiguration()->getGlesVersion() <= GLES_VER_1_0)
	{
		CCMessageBox("The Opengl ES version is lower than 1.1, and the test may not run correctly.", "Cocos2d-x Hint");
		return;
	}

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // create a render texture, this is what we're going to draw into
    m_target = CCRenderTexture::renderTextureWithWidthAndHeight(s.width, s.height);

	if (NULL == m_target)
	{
		return;
	}
	
    m_target->setPosition(ccp(s.width/2, s.height/2));

    // note that the render texture is a cocosnode, and contains a sprite of it's texture for convience,
    // so we can just parent it to the scene like any other cocos node
    addChild(m_target, 1);

    // create a brush image to draw into the texture with
    m_brush = CCSprite::spriteWithFile("Images/stars.png");
    m_brush->retain();

    ccBlendFunc bf = { GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
    m_brush->setBlendFunc( bf);
    m_brush->setOpacity(20);
    setIsTouchEnabled(true);
}

RenderTextureTest::~RenderTextureTest()
{
	if (NULL != m_brush)
	{
		m_brush->release();
		m_brush = NULL;
	}
}

void RenderTextureTest::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    CCSetIterator it = touches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint start = touch->locationInView( touch->view() );	
    start = CCDirector::sharedDirector()->convertToGL( start );
    CCPoint end = touch->previousLocationInView( touch->view() );
    end = CCDirector::sharedDirector()->convertToGL(end);

    // begin drawing to the render texture
    m_target->begin();

    // for extra points, we'll draw this smoothly from the last position and vary the sprite's
    // scale/rotation/offset
    float distance = ccpDistance(start, end);
    if (distance > 1)
    {
        int d = (int)distance;
        for (int i = 0; i < d; i++)
        {
            float difx = end.x - start.x;
            float dify = end.y - start.y;
            float delta = (float)i / distance;
            m_brush->setPosition(ccp(start.x + (difx * delta), start.y + (dify * delta)) );
            m_brush->setRotation( rand()%360 );
            float r = ((float)(rand()%50)/50.f) + 0.25f;
            m_brush->setScale( r );
            // Call visit to draw the brush, don't call draw..
            m_brush->visit();
        }
    }
    // finish drawing and return context back to the screen
    m_target->end(false);
}

void RenderTextureTest::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
#if CC_ENABLE_CACHE_TEXTTURE_DATA

	CCSetIterator it;
	CCTouch* touch;

	for( it = touches->begin(); it != touches->end(); it++) 
	{
		touch = (CCTouch*)(*it);

		if(!touch)
			break;

		CCPoint location = touch->locationInView(touch->view());

		location = CCDirector::sharedDirector()->convertToGL(location);

		m_brush->setPosition(location);
		m_brush->setRotation( rand()%360 );
	}

	m_target->begin();
	m_brush->visit();
	m_target->end(true);
#endif
}

/**
* Impelmentation of RenderTextureSave
*/
RenderTextureSave::RenderTextureSave()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	// create a render texture, this is what we are going to draw into
	m_pTarget = CCRenderTexture::renderTextureWithWidthAndHeight(s.width, s.height);
	m_pTarget->retain();
	m_pTarget->setPosition(ccp(s.width / 2, s.height / 2));

	// note that the render texture is a CCNode, and contains a sprite of its texture for convience,
	// so we can just parent it to the scene like any other CCNode
	this->addChild(m_pTarget, -1);

	// create a brush image to draw into the texture with
	m_pBrush = CCSprite::spriteWithFile("Images/fire.png");
	m_pBrush->retain();
	m_pBrush->setOpacity(20);
	this->setIsTouchEnabled(true);

	// Save Image menu
	CCMenuItemFont::setFontSize(16);
	CCMenuItem *item1 = CCMenuItemFont::itemFromString("Save Image", this, menu_selector(RenderTextureSave::saveImage));
	CCMenuItem *item2 = CCMenuItemFont::itemFromString("Clear", this, menu_selector(RenderTextureSave::clearImage));
	CCMenu *menu = CCMenu::menuWithItems(item1, item2, NULL);
	this->addChild(menu);
	menu->alignItemsVertically();
	menu->setPosition(ccp(s.width - 80, s.height - 30));
}

string RenderTextureSave::title()
{
	return "Touch the screen";
}

string RenderTextureSave::subtitle()
{
	return "Press 'Save Image' to create an snapshot of the render texture";
}

void RenderTextureSave::clearImage(cocos2d::CCObject *pSender)
{
	m_pTarget->clear(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1());
}

void RenderTextureSave::saveImage(cocos2d::CCObject *pSender)
{
	static int counter = 0;

	char str[20];
	sprintf(str, "image-%d.png", counter);
	m_pTarget->saveBuffer(kCCImageFormatPNG, str);
	CCLOG("Image saved %s", str);

	counter++;
}

RenderTextureSave::~RenderTextureSave()
{
	m_pBrush->release();
	m_pTarget->release();
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void RenderTextureSave::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
	CCTouch *touch = (CCTouch *)touches->anyObject();
	CCPoint start = touch->locationInView(touch->view());
	start = CCDirector::sharedDirector()->convertToGL(start);
	CCPoint end = touch->previousLocationInView(touch->view());

	// begin drawing to the render texture
	m_pTarget->begin();

	// for extra points, we'll draw this smoothly from the last position and vary the sprite's
	// scale/rotation/offset
	float distance = ccpDistance(start, end);
	if (distance > 1)
	{
		int d = (int)distance;
		for (int i = 0; i < d; i++)
		{
			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float)i / distance;
			m_pBrush->setPosition(ccp(start.x + (difx * delta), start.y + (dify * delta)));
			m_pBrush->setRotation(rand() % 360);
			float r = (float)(rand() % 50 / 50.f) + 0.25f;
			m_pBrush->setScale(r);
			/*m_pBrush->setColor(ccc3(CCRANDOM_0_1() * 127 + 128, 255, 255));*/
			// Use CCRANDOM_0_1() will cause error when loading libtests.so on android, I don't know why.
			m_pBrush->setColor(ccc3(rand() % 127 + 128, 255, 255));
			// Call visit to draw the brush, don't call draw..
			m_pBrush->visit();
		}
	}

	// finish drawing and return context back to the screen
	m_pTarget->end();
}

/**
 * Impelmentation of RenderTextureIssue937
 */

RenderTextureIssue937::RenderTextureIssue937()
{
    /*
    *     1    2
    * A: A1   A2
    *
    * B: B1   B2
    *
    *  A1: premulti sprite
    *  A2: premulti render
    *
    *  B1: non-premulti sprite
    *  B2: non-premulti render
    */
    CCLayerColor *background = CCLayerColor::layerWithColor(ccc4(200,200,200,255));
    addChild(background);

    CCSprite *spr_premulti = CCSprite::spriteWithFile("Images/fire.png");
    spr_premulti->setPosition(ccp(16,48));

    CCSprite *spr_nonpremulti = CCSprite::spriteWithFile("Images/fire.png");
    spr_nonpremulti->setPosition(ccp(16,16));


    /* A2 & B2 setup */
    CCRenderTexture *rend = CCRenderTexture::renderTextureWithWidthAndHeight(32, 64);

	if (NULL == rend)
	{
		return;
	}

    // It's possible to modify the RenderTexture blending function by
    //		[[rend sprite] setBlendFunc:(ccBlendFunc) {GL_ONE, GL_ONE_MINUS_SRC_ALPHA}];

    rend->begin();
    spr_premulti->visit();
    spr_nonpremulti->visit();
    rend->end(); 

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    /* A1: setup */
    spr_premulti->setPosition(ccp(s.width/2-16, s.height/2+16));
    /* B1: setup */
    spr_nonpremulti->setPosition(ccp(s.width/2-16, s.height/2-16));

    rend->setPosition(ccp(s.width/2+16, s.height/2));

    addChild(spr_nonpremulti);
    addChild(spr_premulti);
    addChild(rend);
}

std::string RenderTextureIssue937::title()
{
    return "Testing issue #937";
}

std::string RenderTextureIssue937::subtitle()
{
    return "All images should be equal...";
}

void RenderTextureScene::runThisTest()
{
    CCLayer* pLayer = nextTestCase();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}

/**
* Impelmentation of RenderTextureZbuffer
*/

RenderTextureZbuffer::RenderTextureZbuffer()
{
	this->setIsTouchEnabled(true);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF *label = CCLabelTTF::labelWithString("vertexZ = 50", "Marker Felt", 64);
	label->setPosition(ccp(size.width / 2, size.height * 0.25f));
	this->addChild(label);

	CCLabelTTF *label2 = CCLabelTTF::labelWithString("vertexZ = 0", "Marker Felt", 64);
	label2->setPosition(ccp(size.width / 2, size.height * 0.5f));
	this->addChild(label2);

	CCLabelTTF *label3 = CCLabelTTF::labelWithString("vertexZ = -50", "Marker Felt", 64);
	label3->setPosition(ccp(size.width / 2, size.height * 0.75f));
	this->addChild(label3);

	label->setVertexZ(50);
	label2->setVertexZ(0);
	label3->setVertexZ(-50);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Images/bugs/circle.plist");
	mgr = CCSpriteBatchNode::batchNodeWithFile("Images/bugs/circle.png", 9);
	this->addChild(mgr);
	sp1 = CCSprite::spriteWithSpriteFrameName("circle.png");
	sp2 = CCSprite::spriteWithSpriteFrameName("circle.png");
	sp3 = CCSprite::spriteWithSpriteFrameName("circle.png");
	sp4 = CCSprite::spriteWithSpriteFrameName("circle.png");
	sp5 = CCSprite::spriteWithSpriteFrameName("circle.png");
	sp6 = CCSprite::spriteWithSpriteFrameName("circle.png");
	sp7 = CCSprite::spriteWithSpriteFrameName("circle.png");
	sp8 = CCSprite::spriteWithSpriteFrameName("circle.png");
	sp9 = CCSprite::spriteWithSpriteFrameName("circle.png");

	mgr->addChild(sp1, 9);
	mgr->addChild(sp2, 8);
	mgr->addChild(sp3, 7);
	mgr->addChild(sp4, 6);
	mgr->addChild(sp5, 5);
	mgr->addChild(sp6, 4);
	mgr->addChild(sp7, 3);
	mgr->addChild(sp8, 2);
	mgr->addChild(sp9, 1);

	sp1->setVertexZ(400);
	sp2->setVertexZ(300);
	sp3->setVertexZ(200);
	sp4->setVertexZ(100);
	sp5->setVertexZ(0);
	sp6->setVertexZ(-100);
	sp7->setVertexZ(-200);
	sp8->setVertexZ(-300);
	sp9->setVertexZ(-400);

	sp9->setScale(2);
	sp9->setColor(ccYELLOW);
}

string RenderTextureZbuffer::title()
{
	return "Testing Z Buffer in Render Texture";
}

string RenderTextureZbuffer::subtitle()
{
	return "Touch screen. It should be green";
}

void RenderTextureZbuffer::ccTouchesBegan(cocos2d::CCSet *touches, cocos2d::CCEvent *event)
{
	CCSetIterator iter;
	CCTouch *touch;
	for (iter = touches->begin(); iter != touches->end(); ++iter)
	{
		touch = (CCTouch *)(*iter);
		CCPoint location = touch->locationInView(touch->view());

		location = CCDirector::sharedDirector()->convertToGL(location);
		sp1->setPosition(location);
		sp2->setPosition(location);
		sp3->setPosition(location);
		sp4->setPosition(location);
		sp5->setPosition(location);
		sp6->setPosition(location);
		sp7->setPosition(location);
		sp8->setPosition(location);
		sp9->setPosition(location);
	}
}

void RenderTextureZbuffer::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
	CCSetIterator iter;
	CCTouch *touch;
	for (iter = touches->begin(); iter != touches->end(); ++iter)
	{
		touch = (CCTouch *)(*iter);
		CCPoint location = touch->locationInView(touch->view());

		location = CCDirector::sharedDirector()->convertToGL(location);
		sp1->setPosition(location);
		sp2->setPosition(location);
		sp3->setPosition(location);
		sp4->setPosition(location);
		sp5->setPosition(location);
		sp6->setPosition(location);
		sp7->setPosition(location);
		sp8->setPosition(location);
		sp9->setPosition(location);
	}
}

void RenderTextureZbuffer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	this->renderScreenShot();
}

void RenderTextureZbuffer::renderScreenShot()
{
	CCRenderTexture *texture = CCRenderTexture::renderTextureWithWidthAndHeight(512, 512);
	if (NULL == texture)
	{
		return;
	}
	texture->setAnchorPoint(ccp(0, 0));
	texture->begin();

	this->visit();

	texture->end();

	CCSprite *sprite = CCSprite::spriteWithTexture(texture->getSprite()->getTexture());

	sprite->setPosition(ccp(256, 256));
	sprite->setOpacity(182);
	sprite->setFlipY(1);
	this->addChild(sprite, 999999);
	sprite->setColor(ccGREEN);

	sprite->runAction(CCSequence::actions(CCFadeTo::actionWithDuration(2, 0),
		                                  CCHide::action(),
		                                  NULL));
}

