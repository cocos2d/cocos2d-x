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

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* layer = (createFunctions[sceneIdx])();
    layer->init();
    layer->autorelease();

    return layer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    

    Layer* layer = (createFunctions[sceneIdx])();
    layer->init();
    layer->autorelease();

    return layer;
}

static Layer* restartAction()
{
    Layer* layer = (createFunctions[sceneIdx])();
    layer->init();
    layer->autorelease();

    return layer;
} 

//#pragma mark Demo examples start here

//@implementation BaseClippingNodeTest

bool BaseClippingNodeTest::init()
{
	if (BaseTest::init()) {
        
        Sprite *background = Sprite::create(s_back3);
        background->setAnchorPoint( Point::ZERO );
        background->setPosition( Point::ZERO );
        this->addChild(background, -1);

        this->setup();
        return true;
	}
	return false;
}

BaseClippingNodeTest::~BaseClippingNodeTest()
{
	TextureCache::getInstance()->removeUnusedTextures();
}

std::string BaseClippingNodeTest::title()
{
	return "Clipping Demo";
}

std::string BaseClippingNodeTest::subtitle()
{
	return "";
}

void BaseClippingNodeTest::restartCallback(Object* sender)
{
	Scene *s = new ClippingNodeTestScene();
	s->addChild(restartAction());
	Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseClippingNodeTest::nextCallback(Object* sender)
{
	Scene *s = new ClippingNodeTestScene();
	s->addChild(nextAction());
	Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseClippingNodeTest::backCallback(Object* sender)
{
	Scene *s = new ClippingNodeTestScene();
	s->addChild(backAction());
	Director::getInstance()->replaceScene(s);
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
    Size s = Director::getInstance()->getWinSize();
    
    Node *stencil = this->stencil();
    stencil->setTag( kTagStencilNode );
    stencil->setPosition( Point(50, 50) );
    
    ClippingNode *clipper = this->clipper();
    clipper->setTag( kTagClipperNode );
    clipper->setAnchorPoint(Point(0.5, 0.5));
    clipper->setPosition( Point(s.width / 2 - 50, s.height / 2 - 50) );
    clipper->setStencil(stencil);
    this->addChild(clipper);
    
    Node *content = this->content();
    content->setPosition( Point(50, 50) );
    clipper->addChild(content);
}

Action* BasicTest::actionRotate()
{
    return RepeatForever::create(RotateBy::create(1.0f, 90.0f));
}

Action* BasicTest::actionScale()
{
    ScaleBy *scale = ScaleBy::create(1.33f, 1.5f);
    return RepeatForever::create(Sequence::create(scale, scale->reverse(), NULL));
}

DrawNode* BasicTest::shape()
{
    DrawNode *shape = DrawNode::create();
    static Point triangle[3];
    triangle[0] = Point(-100, -100);
    triangle[1] = Point(100, -100);
    triangle[2] = Point(0, 100);

    static Color4F green(0, 1, 0, 1);
    shape->drawPolygon(triangle, 3, green, 0, green);
    return shape;
}

Sprite* BasicTest::grossini()
{
    Sprite *grossini = Sprite::create(s_pathGrossini);
    grossini->setScale( 1.5 );
    return grossini;
}

Node* BasicTest::stencil()
{
    return NULL;
}

ClippingNode* BasicTest::clipper()
{
    return ClippingNode::create();
}

Node* BasicTest::content()
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

Node* ShapeTest::stencil()
{
    Node *node = this->shape();
    node->runAction(this->actionRotate());
    return node;
}

Node* ShapeTest::content()
{
    Node *node = this->grossini();
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

ClippingNode* ShapeInvertedTest::clipper()
{
    ClippingNode *clipper = ShapeTest::clipper();
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

Node* SpriteTest::stencil()
{
    Node *node = this->grossini();
    node->runAction(this->actionRotate());
    return node;
}

ClippingNode* SpriteTest::clipper()
{
    ClippingNode *clipper = BasicTest::clipper();
    clipper->setAlphaThreshold(0.05f);
    return clipper;
}

Node* SpriteTest::content()
{
    Node *node = this->shape();
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

ClippingNode* SpriteNoAlphaTest::clipper()
{
    ClippingNode *clipper = SpriteTest::clipper();
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

ClippingNode* SpriteInvertedTest::clipper()
{
    ClippingNode *clipper = SpriteTest::clipper();
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
    
    Node *parent = this;
    
    for (int i = 0; i < depth; i++) {
                
        int size = 225 - i * (225 / (depth * 2));

        ClippingNode *clipper = ClippingNode::create();
        clipper->setContentSize(Size(size, size));
        clipper->setAnchorPoint(Point(0.5, 0.5));
        clipper->setPosition( Point(parent->getContentSize().width / 2, parent->getContentSize().height / 2) );
        clipper->setAlphaThreshold(0.05f);
        clipper->runAction(RepeatForever::create(RotateBy::create(i % 3 ? 1.33 : 1.66, i % 2 ? 90 : -90)));
        parent->addChild(clipper);
        
        Node *stencil = Sprite::create(s_pathGrossini);
        stencil->setScale( 2.5 - (i * (2.5 / depth)) );
        stencil->setAnchorPoint( Point(0.5, 0.5) );
        stencil->setPosition( Point(clipper->getContentSize().width / 2, clipper->getContentSize().height / 2) );
        stencil->setVisible(false);
        stencil->runAction(Sequence::createWithTwoActions(DelayTime::create(i), Show::create()));
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
    Sprite *target = Sprite::create(s_pathBlock);
    target->setAnchorPoint(Point::ZERO);
    target->setScale(3);
    
    _outerClipper = ClippingNode::create();
    _outerClipper->retain();
    AffineTransform tranform = AffineTransformMakeIdentity();
    tranform = AffineTransformScale(tranform, target->getScale(), target->getScale());

    _outerClipper->setContentSize( SizeApplyAffineTransform(target->getContentSize(), tranform));
    _outerClipper->setAnchorPoint( Point(0.5, 0.5) );
    _outerClipper->setPosition(Point(this->getContentSize()) * 0.5f);
    _outerClipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
    
    _outerClipper->setStencil( target );
    
    ClippingNode *holesClipper = ClippingNode::create();
    holesClipper->setInverted(true);
    holesClipper->setAlphaThreshold( 0.05f );
    
    holesClipper->addChild(target);
    
    _holes = Node::create();
    _holes->retain();
    
    holesClipper->addChild(_holes);
    
    _holesStencil = Node::create();
    _holesStencil->retain();
    
    holesClipper->setStencil( _holesStencil);
    
    _outerClipper->addChild(holesClipper);
    
    this->addChild(_outerClipper);
        
    this->setTouchEnabled(true);
}

void HoleDemo::pokeHoleAtPoint(Point point)
{
    float scale = CCRANDOM_0_1() * 0.2 + 0.9;
    float rotation = CCRANDOM_0_1() * 360;
    
    Sprite *hole = Sprite::create("Images/hole_effect.png");
    hole->setPosition( point );
    hole->setRotation( rotation );
    hole->setScale( scale );
    
    _holes->addChild(hole);
    
    Sprite *holeStencil = Sprite::create("Images/hole_stencil.png");
    holeStencil->setPosition( point );
    holeStencil->setRotation( rotation );
    holeStencil->setScale( scale );
    
    _holesStencil->addChild(holeStencil);

    _outerClipper->runAction(Sequence::createWithTwoActions(ScaleBy::create(0.05f, 0.95f),
                                               ScaleTo::create(0.125f, 1)));
}


void HoleDemo::ccTouchesBegan(Set* touches, Event* event)
{
	Touch *touch = (Touch *)touches->anyObject();
	Point point = _outerClipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
    Rect rect = Rect(0, 0, _outerClipper->getContentSize().width, _outerClipper->getContentSize().height);
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
    ClippingNode *clipper = ClippingNode::create();
    clipper->setTag( kTagClipperNode );
    clipper->setContentSize(  Size(200, 200) );
    clipper->setAnchorPoint(  Point(0.5, 0.5) );
    clipper->setPosition( Point(this->getContentSize().width / 2, this->getContentSize().height / 2) );
    clipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
    this->addChild(clipper);

    DrawNode *stencil = DrawNode::create();
    Point rectangle[4];
    rectangle[0] = Point(0, 0);
    rectangle[1] = Point(clipper->getContentSize().width, 0);
    rectangle[2] = Point(clipper->getContentSize().width, clipper->getContentSize().height);
    rectangle[3] = Point(0, clipper->getContentSize().height);
    
    Color4F white(1, 1, 1, 1);
    stencil->drawPolygon(rectangle, 4, white, 1, white);
    clipper->setStencil(stencil);

    Sprite *content = Sprite::create(s_back2);
    content->setTag( kTagContentNode );
    content->setAnchorPoint(  Point(0.5, 0.5) );
    content->setPosition( Point(clipper->getContentSize().width / 2, clipper->getContentSize().height / 2) );
    clipper->addChild(content);
    
    _scrolling = false;

    this->setTouchEnabled(true);
}

void ScrollViewDemo::ccTouchesBegan(Set  *touches, Event  *event)
{
	Touch *touch = static_cast<Touch*>(touches->anyObject());
    Node *clipper = this->getChildByTag(kTagClipperNode);
	Point point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
    Rect rect = Rect(0, 0, clipper->getContentSize().width, clipper->getContentSize().height);
    _scrolling = rect.containsPoint(point);
    _lastPoint = point;
}

void ScrollViewDemo::ccTouchesMoved(Set  *touches, Event  *event)
{
    if (!_scrolling) return;
	Touch *touch = static_cast<Touch*>(touches->anyObject());
    Node *clipper = this->getChildByTag(kTagClipperNode);
    Point point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
	Point diff = point - _lastPoint;
    Node *content = clipper->getChildByTag(kTagContentNode);
    content->setPosition(content->getPosition() + diff);
    _lastPoint = point;
}

void ScrollViewDemo::ccTouchesEnded(Set  *touches, Event  *event)
{
    if (!_scrolling) return;
    _scrolling = false;
}

//#pragma mark - RawStencilBufferTests

//#if COCOS2D_DEBUG > 1

static GLint _stencilBits = -1;

static const GLfloat _alphaThreshold = 0.05f;

static const int _planeCount = 8;
static const Color4F _planeColor[] = {
    Color4F(0, 0, 0, 0.65f),
    Color4F(0.7f, 0, 0, 0.6f),
    Color4F(0, 0.7f, 0, 0.55f),
    Color4F(0, 0, 0.7f, 0.5f),
    Color4F(0.7f, 0.7f, 0, 0.45f),
    Color4F(0, 0.7f, 0.7f, 0.4f),
    Color4F(0.7f, 0, 0.7f, 0.35f),
    Color4F(0.7f, 0.7f, 0.7f, 0.3f),
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
        CCLOGWARN("Stencil must be enabled for the current GLView.");
    }
    _sprite = Sprite::create(s_pathGrossini);
    _sprite->retain();
    _sprite->setAnchorPoint(  Point(0.5, 0) );
    _sprite->setScale( 2.5f );
    Director::getInstance()->setAlphaBlending(true);
}

void RawStencilBufferTest::draw()
{    
    Point winPoint = Point(Director::getInstance()->getWinSize());
    
    Point planeSize = winPoint * (1.0 / _planeCount);
    
    glEnable(GL_STENCIL_TEST);
    CHECK_GL_ERROR_DEBUG();
        
    for (int i = 0; i < _planeCount; i++) {
        
        Point stencilPoint = planeSize * (_planeCount - i);
        stencilPoint.x = winPoint.x;
        
        Point spritePoint = planeSize * i;
        spritePoint.x += planeSize.x / 2;
        spritePoint.y = 0;
        _sprite->setPosition( spritePoint );

        this->setupStencilForClippingOnPlane(i);
        CHECK_GL_ERROR_DEBUG();

        DrawPrimitives::drawSolidRect(Point::ZERO, stencilPoint, Color4F(1, 1, 1, 1));
        
        kmGLPushMatrix();
        this->transform();
        _sprite->visit();
        kmGLPopMatrix();
        
        this->setupStencilForDrawingOnPlane(i);
        CHECK_GL_ERROR_DEBUG();
        
        DrawPrimitives::drawSolidRect(Point::ZERO, winPoint, _planeColor[i]);
        
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
    glStencilFunc(GL_EQUAL, planeMask, planeMask);
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
    GLProgram *program = ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST);
    GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);
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
    GLProgram *program = ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST);
    GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);
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
    Point winPoint = Point(Director::getInstance()->getWinSize());
    unsigned char bits = 0;
    glStencilMask(~0);
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);
    glFlush();
    glReadPixels(0, 0, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &bits);
    LabelTTF *clearToZeroLabel = LabelTTF::create(String::createWithFormat("00=%02x", bits)->getCString(), "Arial", 20);
    clearToZeroLabel->setPosition( Point((winPoint.x / 3) * 1, winPoint.y - 10) );
    this->addChild(clearToZeroLabel);
    glStencilMask(0x0F);
    glClearStencil(0xAA);
    glClear(GL_STENCIL_BUFFER_BIT);
    glFlush();
    glReadPixels(0, 0, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &bits);
    LabelTTF *clearToMaskLabel = LabelTTF::create(String::createWithFormat("0a=%02x", bits)->getCString(), "Arial", 20);
    clearToMaskLabel->setPosition( Point((winPoint.x / 3) * 2, winPoint.y - 10) );
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
    DrawPrimitives::drawSolidRect(Point::ZERO, Point(Director::getInstance()->getWinSize()), Color4F(1, 1, 1, 1));
    glStencilFunc(GL_NEVER, planeMask, planeMask);
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, _alphaThreshold);
#else
    GLProgram *program = ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST);
    GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);
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
    Layer* layer = nextAction();
    addChild(layer);
    Director::getInstance()->replaceScene(this);
}
