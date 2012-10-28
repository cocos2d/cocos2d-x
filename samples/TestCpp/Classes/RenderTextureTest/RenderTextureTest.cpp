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
    case 0: return new RenderTextureSave();
    case 1: return new RenderTextureIssue937();
    case 2: return new RenderTextureZbuffer();    
    case 3: return new RenderTextureTestDepthStencil();
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
    CCRenderTexture *rend = CCRenderTexture::create(s.width, s.height, kCCTexture2DPixelFormat_RGBA4444, CC_GL_DEPTH24_STENCIL8);

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

