//
// Clipping Demo
// 
//
// by Pierre-David Bélanger
//

#include "ClippingNodeTest.h"
#include "../testResource.h"

enum {
	kTagTitleLabel = 1,
	kTagSubtitleLabel = 2,
	kTagStencilNode = 100,
	kTagClipperNode = 101,
	kTagContentNode = 102,
};

TESTLAYER_CREATE_FUNC(ScrollViewDemo);
TESTLAYER_CREATE_FUNC(HoleDemo);
TESTLAYER_CREATE_FUNC(ShapeTest);
TESTLAYER_CREATE_FUNC(ShapeInvertedTest);
TESTLAYER_CREATE_FUNC(SpriteTest);
TESTLAYER_CREATE_FUNC(SpriteNoAlphaTest);
TESTLAYER_CREATE_FUNC(SpriteInvertedTest);
TESTLAYER_CREATE_FUNC(NestedTest);
TESTLAYER_CREATE_FUNC(RawStencilBufferTest);
TESTLAYER_CREATE_FUNC(RawStencilBufferTest2);
TESTLAYER_CREATE_FUNC(RawStencilBufferTest3);
TESTLAYER_CREATE_FUNC(RawStencilBufferTest4);
TESTLAYER_CREATE_FUNC(RawStencilBufferTest5);
TESTLAYER_CREATE_FUNC(RawStencilBufferTest6);

static NEWTESTFUNC createFunctions[] = {
    CF(ScrollViewDemo),
    CF(HoleDemo),
    CF(ShapeTest),
    CF(ShapeInvertedTest),
    CF(SpriteTest),
    CF(SpriteNoAlphaTest),
    CF(SpriteInvertedTest),
    CF(NestedTest),
    CF(RawStencilBufferTest),
    CF(RawStencilBufferTest2),
    CF(RawStencilBufferTest3),
    CF(RawStencilBufferTest4),
    CF(RawStencilBufferTest5),
    CF(RawStencilBufferTest6)
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static CCLayer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();

    return pLayer;
}

static CCLayer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    

    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();

    return pLayer;
}

static CCLayer* restartAction()
{
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();

    return pLayer;
} 

//#pragma mark Demo examples start here

//@implementation BaseClippingNodeTest

bool BaseClippingNodeTest::init()
{
	if (BaseTest::init()) {
        
        CCSprite *background = CCSprite::create(s_back3);
        background->setAnchorPoint( CCPointZero );
        background->setPosition( CCPointZero );
        this->addChild(background, -1);

        this->setup();
        return true;
	}
	return false;
}

BaseClippingNodeTest::~BaseClippingNodeTest()
{
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

std::string BaseClippingNodeTest::title()
{
	return "Clipping Demo";
}

std::string BaseClippingNodeTest::subtitle()
{
	return "";
}

void BaseClippingNodeTest::restartCallback(CCObject* sender)
{
	CCScene *s = new ClippingNodeTestScene();
	s->addChild(restartAction());
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void BaseClippingNodeTest::nextCallback(CCObject* sender)
{
	CCScene *s = new ClippingNodeTestScene();
	s->addChild(nextAction());
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void BaseClippingNodeTest::backCallback(CCObject* sender)
{
	CCScene *s = new ClippingNodeTestScene();
	s->addChild(backAction());
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void BaseClippingNodeTest::setup()
{

}


//#pragma mark - BasicTest

std::string BasicTest::title()
{
	return "Basic Test";
}

std::string BasicTest::subtitle()
{
	return "";
}

void BasicTest::setup()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCNode *stencil = this->stencil();
    stencil->setTag( kTagStencilNode );
    stencil->setPosition( ccp(50, 50) );
    
    CCClippingNode *clipper = this->clipper();
    clipper->setTag( kTagClipperNode );
    clipper->setAnchorPoint(ccp(0.5, 0.5));
    clipper->setPosition( ccp(s.width / 2 - 50, s.height / 2 - 50) );
    clipper->setStencil(stencil);
    this->addChild(clipper);
    
    CCNode *content = this->content();
    content->setPosition( ccp(50, 50) );
    clipper->addChild(content);
}

CCAction* BasicTest::actionRotate()
{
    return CCRepeatForever::create(CCRotateBy::create(1.0f, 90.0f));
}

CCAction* BasicTest::actionScale()
{
    CCScaleBy *scale = CCScaleBy::create(1.33f, 1.5f);
    return CCRepeatForever::create(CCSequence::create(scale, scale->reverse(), NULL));
}

CCDrawNode* BasicTest::shape()
{
    CCDrawNode *shape = CCDrawNode::create();
    static CCPoint triangle[3];
    triangle[0] = ccp(-100, -100);
    triangle[1] = ccp(100, -100);
    triangle[2] = ccp(0, 100);

    static ccColor4F green = {0, 1, 0, 1};
    shape->drawPolygon(triangle, 3, green, 0, green);
    return shape;
}

CCSprite* BasicTest::grossini()
{
    CCSprite *grossini = CCSprite::create(s_pPathGrossini);
    grossini->setScale( 1.5 );
    return grossini;
}

CCNode* BasicTest::stencil()
{
    return NULL;
}

CCClippingNode* BasicTest::clipper()
{
    return CCClippingNode::create();
}

CCNode* BasicTest::content()
{
    return NULL;
}


//#pragma mark - ShapeTest

std::string ShapeTest::title()
{
	return "Shape Basic Test";
}

std::string ShapeTest::subtitle()
{
	return "A DrawNode as stencil and Sprite as content";
}

CCNode* ShapeTest::stencil()
{
    CCNode *node = this->shape();
    node->runAction(this->actionRotate());
    return node;
}

CCNode* ShapeTest::content()
{
    CCNode *node = this->grossini();
    node->runAction(this->actionScale());
    return node;
}


//#pragma mark - ShapeInvertedTest

std::string ShapeInvertedTest::title()
{
	return "Shape Inverted Basic Test";
}

std::string ShapeInvertedTest::subtitle()
{
	return "A DrawNode as stencil and Sprite as content, inverted";
}

CCClippingNode* ShapeInvertedTest::clipper()
{
    CCClippingNode *clipper = ShapeTest::clipper();
    clipper->setInverted(true);
    return clipper;
}

//#pragma mark - SpriteTest

std::string SpriteTest::title()
{
	return "Sprite Basic Test";
}

std::string SpriteTest::subtitle()
{
	return "A Sprite as stencil and DrawNode as content";
}

CCNode* SpriteTest::stencil()
{
    CCNode *node = this->grossini();
    node->runAction(this->actionRotate());
    return node;
}

CCClippingNode* SpriteTest::clipper()
{
    CCClippingNode *clipper = BasicTest::clipper();
    clipper->setAlphaThreshold(0.05f);
    return clipper;
}

CCNode* SpriteTest::content()
{
    CCNode *node = this->shape();
    node->runAction(this->actionScale());
    return node;
}

//#pragma mark - SpriteNoAlphaTest

std::string SpriteNoAlphaTest::title()
{
	return "Sprite No Alpha Basic Test";
}

std::string SpriteNoAlphaTest::subtitle()
{
	return "A Sprite as stencil and DrawNode as content, no alpha";
}

CCClippingNode* SpriteNoAlphaTest::clipper()
{
    CCClippingNode *clipper = SpriteTest::clipper();
    clipper->setAlphaThreshold(1);
    return clipper;
}

//#pragma mark - SpriteInvertedTest

std::string SpriteInvertedTest::title()
{
	return "Sprite Inverted Basic Test";
}

std::string SpriteInvertedTest::subtitle()
{
	return "A Sprite as stencil and DrawNode as content, inverted";
}

CCClippingNode* SpriteInvertedTest::clipper()
{
    CCClippingNode *clipper = SpriteTest::clipper();
    clipper->setAlphaThreshold(0.05f);
    clipper->setInverted(true);
    return clipper;
}

//#pragma mark - NestedTest

std::string NestedTest::title()
{
	return "Nested Test";
}

std::string NestedTest::subtitle()
{
	return "Nest 9 Clipping Nodes, max is usually 8";
}

void NestedTest::setup()
{
    static int depth = 9;
    
    CCNode *parent = this;
    
    for (int i = 0; i < depth; i++) {
                
        int size = 225 - i * (225 / (depth * 2));

        CCClippingNode *clipper = CCClippingNode::create();
        clipper->setContentSize(CCSizeMake(size, size));
        clipper->setAnchorPoint(ccp(0.5, 0.5));
        clipper->setPosition( ccp(parent->getContentSize().width / 2, parent->getContentSize().height / 2) );
        clipper->setAlphaThreshold(0.05f);
        clipper->runAction(CCRepeatForever::create(CCRotateBy::create(i % 3 ? 1.33 : 1.66, i % 2 ? 90 : -90)));
        parent->addChild(clipper);
        
        CCNode *stencil = CCSprite::create(s_pPathGrossini);
        stencil->setScale( 2.5 - (i * (2.5 / depth)) );
        stencil->setAnchorPoint( ccp(0.5, 0.5) );
        stencil->setPosition( ccp(clipper->getContentSize().width / 2, clipper->getContentSize().height / 2) );
        stencil->setVisible(false);
        stencil->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(i), CCShow::create()));
        clipper->setStencil(stencil);

        clipper->addChild(stencil);
        
        parent = clipper;
    }

}

//#pragma mark - HoleDemo

HoleDemo::~HoleDemo()
{
    CC_SAFE_RELEASE(_outerClipper);
    CC_SAFE_RELEASE(_holes);
    CC_SAFE_RELEASE(_holesStencil);
}

std::string HoleDemo::title()
{
	return "Hole Demo";
}

std::string HoleDemo::subtitle()
{
	return "Touch/click to poke holes";
}

void HoleDemo::setup()
{
    CCSprite *target = CCSprite::create(s_pPathBlock);
    target->setAnchorPoint(CCPointZero);
    target->setScale(3);
    
    _outerClipper = CCClippingNode::create();
    _outerClipper->retain();
    CCAffineTransform tranform = CCAffineTransformMakeIdentity();
    tranform = CCAffineTransformScale(tranform, target->getScale(), target->getScale());

    _outerClipper->setContentSize( CCSizeApplyAffineTransform(target->getContentSize(), tranform));
    _outerClipper->setAnchorPoint( ccp(0.5, 0.5) );
    _outerClipper->setPosition( ccpMult(ccpFromSize(this->getContentSize()), 0.5f) );
    _outerClipper->runAction(CCRepeatForever::create(CCRotateBy::create(1, 45)));
    
    _outerClipper->setStencil( target );
    
    CCClippingNode *holesClipper = CCClippingNode::create();
    holesClipper->setInverted(true);
    holesClipper->setAlphaThreshold( 0.05f );
    
    holesClipper->addChild(target);
    
    _holes = CCNode::create();
    _holes->retain();
    
    holesClipper->addChild(_holes);
    
    _holesStencil = CCNode::create();
    _holesStencil->retain();
    
    holesClipper->setStencil( _holesStencil);
    
    _outerClipper->addChild(holesClipper);
    
    this->addChild(_outerClipper);
        
    this->setTouchEnabled(true);
}

void HoleDemo::pokeHoleAtPoint(CCPoint point)
{
    float scale = CCRANDOM_0_1() * 0.2 + 0.9;
    float rotation = CCRANDOM_0_1() * 360;
    
    CCSprite *hole = CCSprite::create("Images/hole_effect.png");
    hole->setPosition( point );
    hole->setRotation( rotation );
    hole->setScale( scale );
    
    _holes->addChild(hole);
    
    CCSprite *holeStencil = CCSprite::create("Images/hole_stencil.png");
    holeStencil->setPosition( point );
    holeStencil->setRotation( rotation );
    holeStencil->setScale( scale );
    
    _holesStencil->addChild(holeStencil);

    _outerClipper->runAction(CCSequence::createWithTwoActions(CCScaleBy::create(0.05f, 0.95f),
                                               CCScaleTo::create(0.125f, 1)));
}


void HoleDemo::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	CCTouch *touch = (CCTouch *)touches->anyObject();
	CCPoint point = _outerClipper->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()));
    CCRect rect = CCRectMake(0, 0, _outerClipper->getContentSize().width, _outerClipper->getContentSize().height);
    if (!rect.containsPoint(point)) return;
    this->pokeHoleAtPoint(point);
}

//#pragma mark - ScrollViewDemo

std::string ScrollViewDemo::title()
{
	return "Scroll View Demo";
}

std::string ScrollViewDemo::subtitle()
{
	return "Move/drag to scroll the content";
}

void ScrollViewDemo::setup()
{
    CCClippingNode *clipper = CCClippingNode::create();
    clipper->setTag( kTagClipperNode );
    clipper->setContentSize(  CCSizeMake(200, 200) );
    clipper->setAnchorPoint(  ccp(0.5, 0.5) );
    clipper->setPosition( ccp(this->getContentSize().width / 2, this->getContentSize().height / 2) );
    clipper->runAction(CCRepeatForever::create(CCRotateBy::create(1, 45)));
    this->addChild(clipper);

    CCDrawNode *stencil = CCDrawNode::create();
    CCPoint rectangle[4];
    rectangle[0] = ccp(0, 0);
    rectangle[1] = ccp(clipper->getContentSize().width, 0);
    rectangle[2] = ccp(clipper->getContentSize().width, clipper->getContentSize().height);
    rectangle[3] = ccp(0, clipper->getContentSize().height);
    
    ccColor4F white = {1, 1, 1, 1};
    stencil->drawPolygon(rectangle, 4, white, 1, white);
    clipper->setStencil(stencil);

    CCSprite *content = CCSprite::create(s_back2);
    content->setTag( kTagContentNode );
    content->setAnchorPoint(  ccp(0.5, 0.5) );
    content->setPosition( ccp(clipper->getContentSize().width / 2, clipper->getContentSize().height / 2) );
    clipper->addChild(content);
    
    _scrolling = false;

    this->setTouchEnabled(true);
}

void ScrollViewDemo::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCNode *clipper = this->getChildByTag(kTagClipperNode);
	CCPoint point = clipper->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()));
    CCRect rect = CCRectMake(0, 0, clipper->getContentSize().width, clipper->getContentSize().height);
    _scrolling = rect.containsPoint(point);
    _lastPoint = point;
}

void ScrollViewDemo::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if (!_scrolling) return;
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCNode *clipper = this->getChildByTag(kTagClipperNode);
    CCPoint point = clipper->convertToNodeSpace(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()));
	CCPoint diff = ccpSub(point, _lastPoint);
    CCNode *content = clipper->getChildByTag(kTagContentNode);
    content->setPosition( ccpAdd(content->getPosition(), diff) );
    _lastPoint = point;
}

void ScrollViewDemo::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    if (!_scrolling) return;
    _scrolling = false;
}

//#pragma mark - RawStencilBufferTests

//#if COCOS2D_DEBUG > 1

static GLint _stencilBits = -1;

static const GLfloat _alphaThreshold = 0.05f;

static const int _planeCount = 8;
static const ccColor4F _planeColor[] = {
    {0, 0, 0, 0.65f},
    {0.7f, 0, 0, 0.6f},
    {0, 0.7f, 0, 0.55f},
    {0, 0, 0.7f, 0.5f},
    {0.7f, 0.7f, 0, 0.45f},
    {0, 0.7f, 0.7f, 0.4f},
    {0.7f, 0, 0.7f, 0.35f},
    {0.7f, 0.7f, 0.7f, 0.3f},
};

RawStencilBufferTest::~RawStencilBufferTest()
{
    CC_SAFE_RELEASE(_sprite);
}

std::string RawStencilBufferTest::title()
{
	return "Raw Stencil Tests";
}

std::string RawStencilBufferTest::subtitle()
{
	return "1:Default";
}

void RawStencilBufferTest::setup()
{
    glGetIntegerv(GL_STENCIL_BITS, &_stencilBits);
    if (_stencilBits < 3) {
        CCLOGWARN("Stencil must be enabled for the current CCGLView.");
    }
    _sprite = CCSprite::create(s_pPathGrossini);
    _sprite->retain();
    _sprite->setAnchorPoint(  ccp(0.5, 0) );
    _sprite->setScale( 2.5f );
    CCDirector::sharedDirector()->setAlphaBlending(true);
}

void RawStencilBufferTest::draw()
{    
    CCPoint winPoint = ccpFromSize(CCDirector::sharedDirector()->getWinSize());
    
    CCPoint planeSize = ccpMult(winPoint, 1.0 / _planeCount);
    
    glEnable(GL_STENCIL_TEST);
    CHECK_GL_ERROR_DEBUG();
        
    for (int i = 0; i < _planeCount; i++) {
        
        CCPoint stencilPoint = ccpMult(planeSize, _planeCount - i);
        stencilPoint.x = winPoint.x;
        
        CCPoint spritePoint = ccpMult(planeSize, i);
        spritePoint.x += planeSize.x / 2;
        spritePoint.y = 0;
        _sprite->setPosition( spritePoint );

        this->setupStencilForClippingOnPlane(i);
        CHECK_GL_ERROR_DEBUG();

        ccDrawSolidRect(CCPointZero, stencilPoint, ccc4f(1, 1, 1, 1));
        
        kmGLPushMatrix();
        this->transform();
        _sprite->visit();
        kmGLPopMatrix();
        
        this->setupStencilForDrawingOnPlane(i);
        CHECK_GL_ERROR_DEBUG();
        
        ccDrawSolidRect(CCPointZero, winPoint, _planeColor[i]);
        
        kmGLPushMatrix();
        this->transform();
        _sprite->visit();
        kmGLPopMatrix();
    }
    
    glDisable(GL_STENCIL_TEST);
    CHECK_GL_ERROR_DEBUG();
}

void RawStencilBufferTest::setupStencilForClippingOnPlane(GLint plane)
{
    GLint planeMask = 0x1 << plane;
    glStencilMask(planeMask);
    glClearStencil(0x0);
    glClear(GL_STENCIL_BUFFER_BIT);
    glFlush();
    glStencilFunc(GL_NEVER, planeMask, planeMask);
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
}

void RawStencilBufferTest::setupStencilForDrawingOnPlane(GLint plane)
{
    GLint planeMask = 0x1 << plane;
    GLint equalOrLessPlanesMask = planeMask | (planeMask - 1);
    glStencilFunc(GL_EQUAL, equalOrLessPlanesMask, equalOrLessPlanesMask);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}

//@implementation RawStencilBufferTest2

std::string RawStencilBufferTest2::subtitle()
{
	return "2:DepthMask:FALSE";
}

void RawStencilBufferTest2::setupStencilForClippingOnPlane(GLint plane)
{
    RawStencilBufferTest::setupStencilForClippingOnPlane(plane);
    glDepthMask(GL_FALSE);
}

void RawStencilBufferTest2::setupStencilForDrawingOnPlane(GLint plane)
{
    glDepthMask(GL_TRUE);
    RawStencilBufferTest::setupStencilForDrawingOnPlane(plane);
}

//@implementation RawStencilBufferTest3

std::string RawStencilBufferTest3::subtitle()
{
	return "3:DepthTest:DISABLE,DepthMask:FALSE";
}

void RawStencilBufferTest3::setupStencilForClippingOnPlane(GLint plane)
{
    RawStencilBufferTest::setupStencilForClippingOnPlane(plane);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
}

void RawStencilBufferTest3::setupStencilForDrawingOnPlane(GLint plane)
{
    glDepthMask(GL_TRUE);
    //glEnable(GL_DEPTH_TEST);
    RawStencilBufferTest::setupStencilForDrawingOnPlane(plane);
}

//@implementation RawStencilBufferTest4

std::string RawStencilBufferTest4::subtitle()
{
	return "4:DepthMask:FALSE,AlphaTest:ENABLE";
}

void RawStencilBufferTest4::setupStencilForClippingOnPlane(GLint plane)
{
    RawStencilBufferTest::setupStencilForClippingOnPlane(plane);
    glDepthMask(GL_FALSE);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, _alphaThreshold);
#else
    CCGLProgram *program = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest);
    GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), kCCUniformAlphaTestValue);
    program->setUniformLocationWith1f(alphaValueLocation, _alphaThreshold);
    _sprite->setShaderProgram(program );
#endif
}

void RawStencilBufferTest4::setupStencilForDrawingOnPlane(GLint plane)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    glDisable(GL_ALPHA_TEST);
#endif
    glDepthMask(GL_TRUE);
    RawStencilBufferTest::setupStencilForDrawingOnPlane(plane);
}

//@implementation RawStencilBufferTest5

std::string RawStencilBufferTest5::subtitle()
{
	return "5:DepthTest:DISABLE,DepthMask:FALSE,AlphaTest:ENABLE";
}

void RawStencilBufferTest5::setupStencilForClippingOnPlane(GLint plane)
{
    RawStencilBufferTest::setupStencilForClippingOnPlane(plane);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, _alphaThreshold);
#else
    CCGLProgram *program = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest);
    GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), kCCUniformAlphaTestValue);
    program->setUniformLocationWith1f(alphaValueLocation, _alphaThreshold);
    _sprite->setShaderProgram( program );
#endif
}

void RawStencilBufferTest5::setupStencilForDrawingOnPlane(GLint plane)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    glDisable(GL_ALPHA_TEST);
#endif
    glDepthMask(GL_TRUE);
    //glEnable(GL_DEPTH_TEST);
    RawStencilBufferTest::setupStencilForDrawingOnPlane(plane);
}

//@implementation RawStencilBufferTest6

std::string RawStencilBufferTest6::subtitle()
{
	return "6:ManualClear,AlphaTest:ENABLE";
}

void RawStencilBufferTest6::setup()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    CCPoint winPoint = ccpFromSize(CCDirector::sharedDirector()->getWinSize());
    unsigned char bits = 0;
    glStencilMask(~0);
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);
    glFlush();
    glReadPixels(0, 0, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &bits);
    CCLabelTTF *clearToZeroLabel = CCLabelTTF::create(CCString::createWithFormat("00=%02x", bits)->getCString(), "Arial", 20);
    clearToZeroLabel->setPosition( ccp((winPoint.x / 3) * 1, winPoint.y - 10) );
    this->addChild(clearToZeroLabel);
    glStencilMask(0x0F);
    glClearStencil(0xAA);
    glClear(GL_STENCIL_BUFFER_BIT);
    glFlush();
    glReadPixels(0, 0, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &bits);
    CCLabelTTF *clearToMaskLabel = CCLabelTTF::create(CCString::createWithFormat("0a=%02x", bits)->getCString(), "Arial", 20);
    clearToMaskLabel->setPosition( ccp((winPoint.x / 3) * 2, winPoint.y - 10) );
    this->addChild(clearToMaskLabel);
#endif
    glStencilMask(~0);
    RawStencilBufferTest::setup();
}

void RawStencilBufferTest6::setupStencilForClippingOnPlane(GLint plane)
{
    GLint planeMask = 0x1 << plane;
    glStencilMask(planeMask);
    glStencilFunc(GL_NEVER, 0, planeMask);
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
    ccDrawSolidRect(CCPointZero, ccpFromSize(CCDirector::sharedDirector()->getWinSize()), ccc4f(1, 1, 1, 1));
    glStencilFunc(GL_NEVER, planeMask, planeMask);
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, _alphaThreshold);
#else
    CCGLProgram *program = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest);
    GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), kCCUniformAlphaTestValue);
    program->setUniformLocationWith1f(alphaValueLocation, _alphaThreshold);
    _sprite->setShaderProgram(program);
#endif
    glFlush();
}

void RawStencilBufferTest6::setupStencilForDrawingOnPlane(GLint plane)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    glDisable(GL_ALPHA_TEST);
#endif
    glDepthMask(GL_TRUE);
    //glEnable(GL_DEPTH_TEST);
    RawStencilBufferTest::setupStencilForDrawingOnPlane(plane);
    glFlush();
}

//#endif // COCOS2D_DEBUG > 1

void ClippingNodeTestScene::runThisTest()
{
    CCLayer* pLayer = nextAction();
    addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(this);
}
