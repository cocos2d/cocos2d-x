#include "RenderTextureTest.h"

static int sceneIdx = -1; 

#define MAX_LAYER    2

CCLayer* createTestCase(int nIndex)
{

    switch(nIndex)
    {
    case 0: return new RenderTextureTest();
    case 1: return new RenderTextureIssue937();
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
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

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
    m_target->end();
}

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
