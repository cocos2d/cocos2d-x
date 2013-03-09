#include "CCConfiguration.h"
#include "RenderTextureTest.h"
#include "../testBasic.h"

// Test #1 by Jason Booth (slipster216)
// Test #3 by David Deaco (ddeaco)



TESTLAYER_CREATE_FUNC(RenderTextureSave);
TESTLAYER_CREATE_FUNC(RenderTextureIssue937);
TESTLAYER_CREATE_FUNC(RenderTextureZbuffer);
TESTLAYER_CREATE_FUNC(RenderTextureTestDepthStencil);
TESTLAYER_CREATE_FUNC(RenderTextureTargetNode);
TESTLAYER_CREATE_FUNC(SpriteRenderTextureBug);

static NEWTESTFUNC createFunctions[] = {
    CF(RenderTextureSave),
    CF(RenderTextureIssue937),
    CF(RenderTextureZbuffer),
    CF(RenderTextureTestDepthStencil),
    CF(RenderTextureTargetNode),
    CF(SpriteRenderTextureBug),
};

#define MAX_LAYER   (sizeof(createFunctions)/sizeof(createFunctions[0]))
static int sceneIdx = -1; 

static CCLayer* nextTestCase()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->autorelease();

    return pLayer;
}

static CCLayer* backTestCase()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    

    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->autorelease();

    return pLayer;
}

static CCLayer* restartTestCase()
{
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->autorelease();

    return pLayer;
}

void RenderTextureTest::onEnter()
{
    CCLayer::onEnter();
    CCSize s = CCDirector::sharedDirector()->getWinSize();


    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 26);
    addChild(label, 1);
    label->setPosition( ccp(s.width/2, s.height-50) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() ) 
    {
        CCLabelTTF* l = CCLabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition( ccp(s.width/2, s.height-80) );
    }    

    CCMenuItemImage *item1 = CCMenuItemImage::create("Images/b1.png", "Images/b2.png", this, menu_selector(RenderTextureTest::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create("Images/r1.png","Images/r2.png", this, menu_selector(RenderTextureTest::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create("Images/f1.png", "Images/f2.png", this, menu_selector(RenderTextureTest::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition( CCPointZero );
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 1);
}

void RenderTextureTest::restartCallback(CCObject* pSender)
{
    CCScene* s = new RenderTextureScene();
    s->addChild(restartTestCase()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void RenderTextureTest::nextCallback(CCObject* pSender)
{
    CCScene* s = new RenderTextureScene();
    s->addChild( nextTestCase() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void RenderTextureTest::backCallback(CCObject* pSender)
{
    CCScene* s = new RenderTextureScene();
    s->addChild( backTestCase() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 

std::string RenderTextureTest::title()
{
    return "No title";
}

std::string RenderTextureTest::subtitle()
{
    return "";
}

/**
* Impelmentation of RenderTextureSave
*/
RenderTextureSave::RenderTextureSave()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // create a render texture, this is what we are going to draw into
    m_pTarget = CCRenderTexture::create(s.width, s.height, kCCTexture2DPixelFormat_RGBA8888);
    m_pTarget->retain();
    m_pTarget->setPosition(ccp(s.width / 2, s.height / 2));

    // note that the render texture is a CCNode, and contains a sprite of its texture for convience,
    // so we can just parent it to the scene like any other CCNode
    this->addChild(m_pTarget, -1);

    // create a brush image to draw into the texture with
    m_pBrush = CCSprite::create("Images/fire.png");
    m_pBrush->retain();
    m_pBrush->setColor(ccRED);
    m_pBrush->setOpacity(20);
    this->setTouchEnabled(true);

    // Save Image menu
    CCMenuItemFont::setFontSize(16);
    CCMenuItem *item1 = CCMenuItemFont::create("Save Image", this, menu_selector(RenderTextureSave::saveImage));
    CCMenuItem *item2 = CCMenuItemFont::create("Clear", this, menu_selector(RenderTextureSave::clearImage));
    CCMenu *menu = CCMenu::create(item1, item2, NULL);
    this->addChild(menu);
    menu->alignItemsVertically();
    menu->setPosition(ccp(VisibleRect::rightTop().x - 80, VisibleRect::rightTop().y - 30));
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

    char png[20];
    sprintf(png, "image-%d.png", counter);
    char jpg[20];
    sprintf(jpg, "image-%d.jpg", counter);

    m_pTarget->saveToFile(png, kCCImageFormatPNG);
    m_pTarget->saveToFile(jpg, kCCImageFormatJPEG);
    

    CCImage *pImage = m_pTarget->newCCImage();

    CCTexture2D *tex = CCTextureCache::sharedTextureCache()->addUIImage(pImage, png);

    CC_SAFE_DELETE(pImage);

    CCSprite *sprite = CCSprite::createWithTexture(tex);

    sprite->setScale(0.3f);
    addChild(sprite);
    sprite->setPosition(ccp(40, 40));
    sprite->setRotation(counter * 3);

    CCLOG("Image saved %s and %s", png, jpg);

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
    CCPoint start = touch->getLocation();
    CCPoint end = touch->getPreviousLocation();

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
    CCLayerColor *background = CCLayerColor::create(ccc4(200,200,200,255));
    addChild(background);

    CCSprite *spr_premulti = CCSprite::create("Images/fire.png");
    spr_premulti->setPosition(ccp(16,48));

    CCSprite *spr_nonpremulti = CCSprite::create("Images/fire.png");
    spr_nonpremulti->setPosition(ccp(16,16));


    
    
    /* A2 & B2 setup */
    CCRenderTexture *rend = CCRenderTexture::create(32, 64, kCCTexture2DPixelFormat_RGBA8888);

    if (NULL == rend)
    {
        return;
    }

    // It's possible to modify the RenderTexture blending function by
    //        [[rend sprite] setBlendFunc:(ccBlendFunc) {GL_ONE, GL_ONE_MINUS_SRC_ALPHA}];

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
    this->setTouchEnabled(true);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *label = CCLabelTTF::create("vertexZ = 50", "Marker Felt", 64);
    label->setPosition(ccp(size.width / 2, size.height * 0.25f));
    this->addChild(label);

    CCLabelTTF *label2 = CCLabelTTF::create("vertexZ = 0", "Marker Felt", 64);
    label2->setPosition(ccp(size.width / 2, size.height * 0.5f));
    this->addChild(label2);

    CCLabelTTF *label3 = CCLabelTTF::create("vertexZ = -50", "Marker Felt", 64);
    label3->setPosition(ccp(size.width / 2, size.height * 0.75f));
    this->addChild(label3);

    label->setVertexZ(50);
    label2->setVertexZ(0);
    label3->setVertexZ(-50);

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Images/bugs/circle.plist");
    mgr = CCSpriteBatchNode::create("Images/bugs/circle.png", 9);
    this->addChild(mgr);
    sp1 = CCSprite::createWithSpriteFrameName("circle.png");
    sp2 = CCSprite::createWithSpriteFrameName("circle.png");
    sp3 = CCSprite::createWithSpriteFrameName("circle.png");
    sp4 = CCSprite::createWithSpriteFrameName("circle.png");
    sp5 = CCSprite::createWithSpriteFrameName("circle.png");
    sp6 = CCSprite::createWithSpriteFrameName("circle.png");
    sp7 = CCSprite::createWithSpriteFrameName("circle.png");
    sp8 = CCSprite::createWithSpriteFrameName("circle.png");
    sp9 = CCSprite::createWithSpriteFrameName("circle.png");

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
        CCPoint location = touch->getLocation();

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
        CCPoint location = touch->getLocation();

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
    CCRenderTexture *texture = CCRenderTexture::create(512, 512);
    if (NULL == texture)
    {
        return;
    }
    texture->setAnchorPoint(ccp(0, 0));
    texture->begin();

    this->visit();

    texture->end();

    CCSprite *sprite = CCSprite::createWithTexture(texture->getSprite()->getTexture());

    sprite->setPosition(ccp(256, 256));
    sprite->setOpacity(182);
    sprite->setFlipY(1);
    this->addChild(sprite, 999999);
    sprite->setColor(ccGREEN);

    sprite->runAction(CCSequence::create(CCFadeTo::create(2, 0),
                                          CCHide::create(),
                                          NULL));
}

// RenderTextureTestDepthStencil

RenderTextureTestDepthStencil::RenderTextureTestDepthStencil()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSprite *sprite = CCSprite::create("Images/fire.png");
    sprite->setPosition(ccp(s.width * 0.25f, 0));
    sprite->setScale(10);
    CCRenderTexture *rend = CCRenderTexture::create(s.width, s.height, kCCTexture2DPixelFormat_RGBA4444, GL_DEPTH24_STENCIL8);

    glStencilMask(0xFF);
    rend->beginWithClear(0, 0, 0, 0, 0, 0);

    //! mark sprite quad into stencil buffer
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glColorMask(0, 0, 0, 1);
    sprite->visit();

    //! move sprite half width and height, and draw only where not marked
    sprite->setPosition(ccpAdd(sprite->getPosition(), ccpMult(ccp(sprite->getContentSize().width * sprite->getScale(), sprite->getContentSize().height * sprite->getScale()), 0.5)));
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glColorMask(1, 1, 1, 1);
    sprite->visit();

    rend->end();

    glDisable(GL_STENCIL_TEST);

    rend->setPosition(ccp(s.width * 0.5f, s.height * 0.5f));

    this->addChild(rend);
}

std::string RenderTextureTestDepthStencil::title()
{
    return "Testing depthStencil attachment";
}

std::string RenderTextureTestDepthStencil::subtitle()
{
    return "Circle should be missing 1/4 of its region";
}

// RenderTextureTest
RenderTextureTargetNode::RenderTextureTargetNode()
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
    CCLayerColor *background = CCLayerColor::create(ccc4(40,40,40,255));
    addChild(background);
    
    // sprite 1
    sprite1 = CCSprite::create("Images/fire.png");
    
    // sprite 2
    sprite2 = CCSprite::create("Images/fire_rgba8888.pvr");
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    /* Create the render texture */
    CCRenderTexture *renderTexture = CCRenderTexture::create(s.width, s.height, kCCTexture2DPixelFormat_RGBA4444);
    this->renderTexture = renderTexture;
    
    renderTexture->setPosition(ccp(s.width/2, s.height/2));
    //		[renderTexture setPosition:ccp(s.width, s.height)];
    //		renderTexture.scale = 2;
    
    /* add the sprites to the render texture */
    renderTexture->addChild(sprite1);
    renderTexture->addChild(sprite2);
    renderTexture->setClearColor(ccc4f(0, 0, 0, 0));
    renderTexture->setClearFlags(GL_COLOR_BUFFER_BIT);
    
    /* add the render texture to the scene */
    addChild(renderTexture);
    
    renderTexture->setAutoDraw(true);
    
    scheduleUpdate();
    
    // Toggle clear on / off
    CCMenuItemFont *item = CCMenuItemFont::create("Clear On/Off", this, menu_selector(RenderTextureTargetNode::touched));
    CCMenu *menu = CCMenu::create(item, NULL);
    addChild(menu);

    menu->setPosition(ccp(s.width/2, s.height/2));
}

void RenderTextureTargetNode::touched(CCObject* sender)
{
    if (renderTexture->getClearFlags() == 0)
    {
        renderTexture->setClearFlags(GL_COLOR_BUFFER_BIT);
    }
    else
    {
        renderTexture->setClearFlags(0);
        renderTexture->setClearColor(ccc4f( CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    }
}

void RenderTextureTargetNode::update(float dt)
{
    static float time = 0;
    float r = 80;
    sprite1->setPosition(ccp(cosf(time * 2) * r, sinf(time * 2) * r));
    sprite2->setPosition(ccp(sinf(time * 2) * r, cosf(time * 2) * r));
    
    time += dt;
}

string RenderTextureTargetNode::title()
{
    return "Testing Render Target Node";
}

string RenderTextureTargetNode::subtitle()
{
    return "Sprites should be equal and move with each frame";
}

// SpriteRenderTextureBug

SpriteRenderTextureBug::SimpleSprite::SimpleSprite() : rt(NULL) {}

SpriteRenderTextureBug::SimpleSprite* SpriteRenderTextureBug::SimpleSprite::create(const char* filename, const CCRect &rect)
{
    SimpleSprite *sprite = new SimpleSprite();
    if (sprite && sprite->initWithFile(filename, rect))
    {
        sprite->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(sprite);
    }
    
    return sprite;
}

void SpriteRenderTextureBug::SimpleSprite::draw()
{
    if (rt == NULL)
    {
		CCSize s = CCDirector::sharedDirector()->getWinSize();
        rt = new CCRenderTexture();
        rt->initWithWidthAndHeight(s.width, s.height, kCCTexture2DPixelFormat_RGBA8888);
	}
	rt->beginWithClear(0.0f, 0.0f, 0.0f, 1.0f);
	rt->end();
    
	CC_NODE_DRAW_SETUP();
    
	ccBlendFunc blend = getBlendFunc();
	ccGLBlendFunc(blend.src, blend.dst);
    
    ccGLBindTexture2D(getTexture()->getName());
    
	//
	// Attributes
	//
    
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
    
#define kQuadSize sizeof(m_sQuad.bl)
	long offset = (long)&m_sQuad;
    
	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

SpriteRenderTextureBug::SpriteRenderTextureBug()
{
    setTouchEnabled(true);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    addNewSpriteWithCoords(ccp(s.width/2, s.height/2));
}

SpriteRenderTextureBug::SimpleSprite* SpriteRenderTextureBug::addNewSpriteWithCoords(const CCPoint& p)
{
    int idx = CCRANDOM_0_1() * 1400 / 100;
	int x = (idx%5) * 85;
	int y = (idx/5) * 121;
    
    SpriteRenderTextureBug::SimpleSprite *sprite = SpriteRenderTextureBug::SimpleSprite::create("Images/grossini_dance_atlas.png",
                                                                                                CCRectMake(x,y,85,121));
    addChild(sprite);
    
    sprite->setPosition(p);
    
	CCFiniteTimeAction *action = NULL;
	float rd = CCRANDOM_0_1();
    
	if (rd < 0.20)
        action = CCScaleBy::create(3, 2);
	else if (rd < 0.40)
		action = CCRotateBy::create(3, 360);
	else if (rd < 0.60)
		action = CCBlink::create(1, 3);
	else if (rd < 0.8 )
		action = CCTintBy::create(2, 0, -255, -255);
	else
		action = CCFadeOut::create(2);
    
    CCFiniteTimeAction *action_back = action->reverse();
    CCSequence *seq = CCSequence::create(action, action_back, NULL);
    
    sprite->runAction(CCRepeatForever::create(seq));
    
    //return sprite;
    return NULL;
}

void SpriteRenderTextureBug::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSetIterator iter = touches->begin();
    for(; iter != touches->end(); ++iter)
    {
        CCPoint location = ((CCTouch*)(*iter))->getLocation();
        addNewSpriteWithCoords(location);
    }
}

std::string SpriteRenderTextureBug::title()
{
    return "SpriteRenderTextureBug";
}

std::string SpriteRenderTextureBug::subtitle()
{
    return "Touch the screen. Sprite should appear on under the touch";
}
