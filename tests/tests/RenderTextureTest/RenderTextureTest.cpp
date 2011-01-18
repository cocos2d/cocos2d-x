#include "RenderTextureTest.h"

RenderTextureTest::RenderTextureTest()
{
	CGSize s = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* label = CCLabelTTF::labelWithString("Render Texture Test", "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );

	// create a render texture, this is what we're going to draw into
	m_target = CCRenderTexture::renderTextureWithWidthAndHeight(s.width, s.height);
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
	m_brush->release();
}

void RenderTextureTest::ccTouchesMoved(NSSet* touches, UIEvent* event)
{
    NSSetIterator it = touches->begin();
    CCTouch* touch = (CCTouch*)(*it);
	CGPoint start = touch->locationInView( touch->view() );	
	start = CCDirector::sharedDirector()->convertToGL( start );
	CGPoint end = touch->previousLocationInView( touch->view() );
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
	m_target->end();
}

void RenderTextureScene::runThisTest()
{
    CCLayer* pLayer = new RenderTextureTest();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}
