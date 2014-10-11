//
// ClippingNodeTest
// 
//
// by Pierre-David Bélanger
//

#include "ClippingNodeTest.h"
#include "../testResource.h"
#include "renderer/CCRenderer.h"

enum {
	kTagTitleLabel = 1,
	kTagSubtitleLabel = 2,
	kTagStencilNode = 100,
	kTagClipperNode = 101,
	kTagContentNode = 102,
};

static std::function<Layer*()> createFunctions[] = {
    CL(ScrollViewDemo),
    CL(HoleDemo),
    CL(ShapeTest),
    CL(ShapeInvertedTest),
    CL(SpriteTest),
    CL(SpriteNoAlphaTest),
    CL(SpriteInvertedTest),
    CL(NestedTest),
    CL(RawStencilBufferTest),
    CL(RawStencilBufferTest2),
    CL(RawStencilBufferTest3),
    CL(RawStencilBufferTest4),
    CL(RawStencilBufferTest5),
    CL(RawStencilBufferTest6),
    CL(ClippingToRenderTextureTest),
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();

    return layer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    

    auto layer = (createFunctions[sceneIdx])();

    return layer;
}

static Layer* restartAction()
{
    auto layer = (createFunctions[sceneIdx])();

    return layer;
} 

//// Demo examples start here

//@implementation BaseClippingNodeTest

bool BaseClippingNodeTest::init()
{
	if (BaseTest::init()) {
        
        auto background = Sprite::create(s_back3);
        background->setAnchorPoint( Vec2::ZERO );
        background->setPosition( Vec2::ZERO );
        this->addChild(background, -1);

        this->setup();
        return true;
	}
	return false;
}

BaseClippingNodeTest::~BaseClippingNodeTest()
{
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

std::string BaseClippingNodeTest::title() const
{
	return "Clipping Demo";
}

std::string BaseClippingNodeTest::subtitle() const
{
	return "";
}

void BaseClippingNodeTest::restartCallback(Ref* sender)
{
	Scene *s = new (std::nothrow) ClippingNodeTestScene();
	s->addChild(restartAction());
	Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseClippingNodeTest::nextCallback(Ref* sender)
{
	Scene *s = new (std::nothrow) ClippingNodeTestScene();
	s->addChild(nextAction());
	Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseClippingNodeTest::backCallback(Ref* sender)
{
	Scene *s = new (std::nothrow) ClippingNodeTestScene();
	s->addChild(backAction());
	Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseClippingNodeTest::setup()
{

}


// BasicTest

std::string BasicTest::title() const
{
	return "Basic Test";
}

std::string BasicTest::subtitle() const
{
	return "";
}

void BasicTest::setup()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto stencil = this->stencil();
    stencil->setTag( kTagStencilNode );
    stencil->setPosition(50, 50);
    
    auto clipper = this->clipper();
    clipper->setTag( kTagClipperNode );
    clipper->setAnchorPoint(Vec2(0.5, 0.5));
    clipper->setPosition(s.width / 2 - 50, s.height / 2 - 50);
    clipper->setStencil(stencil);
    this->addChild(clipper);
    
    auto content = this->content();
    content->setPosition(50, 50);
    clipper->addChild(content);
}

Action* BasicTest::actionRotate()
{
    return RepeatForever::create(RotateBy::create(1.0f, 90.0f));
}

Action* BasicTest::actionScale()
{
    auto scale = ScaleBy::create(1.33f, 1.5f);
    return RepeatForever::create(Sequence::create(scale, scale->reverse(), nullptr));
}

DrawNode* BasicTest::shape()
{
    auto shape = DrawNode::create();
    static Vec2 triangle[3];
    triangle[0] = Vec2(-100, -100);
    triangle[1] = Vec2(100, -100);
    triangle[2] = Vec2(0, 100);

    static Color4F green(0, 1, 0, 1);
    shape->drawPolygon(triangle, 3, green, 0, green);
    return shape;
}

Sprite* BasicTest::grossini()
{
    auto grossini = Sprite::create(s_pathGrossini);
    grossini->setScale( 1.5 );
    return grossini;
}

Node* BasicTest::stencil()
{
    return nullptr;
}

ClippingNode* BasicTest::clipper()
{
    return ClippingNode::create();
}

Node* BasicTest::content()
{
    return nullptr;
}


// ShapeTest

std::string ShapeTest::title() const
{
	return "Shape Basic Test";
}

std::string ShapeTest::subtitle() const
{
	return "A DrawNode as stencil and Sprite as content";
}

Node* ShapeTest::stencil()
{
    auto node = this->shape();
    node->runAction(this->actionRotate());
    return node;
}

Node* ShapeTest::content()
{
    auto node = this->grossini();
    node->runAction(this->actionScale());
    return node;
}


// ShapeInvertedTest

std::string ShapeInvertedTest::title() const
{
	return "Shape Inverted Basic Test";
}

std::string ShapeInvertedTest::subtitle() const
{
	return "A DrawNode as stencil and Sprite as content, inverted";
}

ClippingNode* ShapeInvertedTest::clipper()
{
    auto clipper = ShapeTest::clipper();
    clipper->setInverted(true);
    return clipper;
}

// SpriteTest

std::string SpriteTest::title() const
{
	return "Sprite Basic Test";
}

std::string SpriteTest::subtitle() const
{
	return "A Sprite as stencil and DrawNode as content";
}

Node* SpriteTest::stencil()
{
    auto node = this->grossini();
    node->runAction(this->actionRotate());
    return node;
}

ClippingNode* SpriteTest::clipper()
{
    auto clipper = BasicTest::clipper();
    clipper->setAlphaThreshold(0.05f);
    return clipper;
}

Node* SpriteTest::content()
{
    auto node = this->shape();
    node->runAction(this->actionScale());
    return node;
}

// SpriteNoAlphaTest

std::string SpriteNoAlphaTest::title() const
{
	return "Sprite No Alpha Basic Test";
}

std::string SpriteNoAlphaTest::subtitle() const
{
	return "A Sprite as stencil and DrawNode as content, no alpha";
}

ClippingNode* SpriteNoAlphaTest::clipper()
{
    auto clipper = SpriteTest::clipper();
    clipper->setAlphaThreshold(1);
    return clipper;
}

// SpriteInvertedTest

std::string SpriteInvertedTest::title() const
{
	return "Sprite Inverted Basic Test";
}

std::string SpriteInvertedTest::subtitle() const
{
	return "A Sprite as stencil and DrawNode as content, inverted";
}

ClippingNode* SpriteInvertedTest::clipper()
{
    auto clipper = SpriteTest::clipper();
    clipper->setAlphaThreshold(0.05f);
    clipper->setInverted(true);
    return clipper;
}

// NestedTest

std::string NestedTest::title() const
{
	return "Nested Test";
}

std::string NestedTest::subtitle() const
{
	return "Nest 9 Clipping Nodes, max is usually 8";
}

void NestedTest::setup()
{
    static int depth = 9;
    
    Node* parent = this;
    
    for (int i = 0; i < depth; i++) {
                
        int size = 225 - i * (225 / (depth * 2));

        auto clipper = ClippingNode::create();
        clipper->setContentSize(Size(size, size));
        clipper->setAnchorPoint(Vec2(0.5, 0.5));
        clipper->setPosition(parent->getContentSize().width / 2, parent->getContentSize().height / 2);
        clipper->setAlphaThreshold(0.05f);
        clipper->runAction(RepeatForever::create(RotateBy::create(i % 3 ? 1.33 : 1.66, i % 2 ? 90 : -90)));
        parent->addChild(clipper);
        
        auto stencil = Sprite::create(s_pathGrossini);
        stencil->setScale( 2.5 - (i * (2.5 / depth)) );
        stencil->setAnchorPoint( Vec2(0.5, 0.5) );
        stencil->setPosition(clipper->getContentSize().width / 2, clipper->getContentSize().height / 2);
        stencil->setVisible(false);
        stencil->runAction(Sequence::createWithTwoActions(DelayTime::create(i), Show::create()));
        clipper->setStencil(stencil);

        clipper->addChild(stencil);
        
        parent = clipper;
    }

}

// HoleDemo

HoleDemo::~HoleDemo()
{
    CC_SAFE_RELEASE(_outerClipper);
    CC_SAFE_RELEASE(_holes);
    CC_SAFE_RELEASE(_holesStencil);
}

std::string HoleDemo::title() const
{
	return "Hole Demo";
}

std::string HoleDemo::subtitle() const
{
	return "Touch/click to poke holes";
}

void HoleDemo::setup()
{
    auto target = Sprite::create(s_pathBlock);
    target->setAnchorPoint(Vec2::ZERO);
    target->setScale(3);
    
    _outerClipper = ClippingNode::create();
    _outerClipper->retain();
    AffineTransform tranform = AffineTransform::IDENTITY;
    tranform = AffineTransformScale(tranform, target->getScale(), target->getScale());

    _outerClipper->setContentSize( SizeApplyAffineTransform(target->getContentSize(), tranform));
    _outerClipper->setAnchorPoint( Vec2(0.5, 0.5) );
    _outerClipper->setPosition(Vec2(this->getContentSize()) * 0.5f);
    _outerClipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
    
    _outerClipper->setStencil( target );
    
    auto holesClipper = ClippingNode::create();
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
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(HoleDemo::onTouchesBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HoleDemo::pokeHoleAtPoint(Vec2 point)
{
    float scale = CCRANDOM_0_1() * 0.2 + 0.9;
    float rotation = CCRANDOM_0_1() * 360;
    
    auto hole = Sprite::create("Images/hole_effect.png");
    hole->setPosition( point );
    hole->setRotation( rotation );
    hole->setScale( scale );
    
    _holes->addChild(hole);
    
    auto holeStencil = Sprite::create("Images/hole_stencil.png");
    holeStencil->setPosition( point );
    holeStencil->setRotation( rotation );
    holeStencil->setScale( scale );
    
    _holesStencil->addChild(holeStencil);

    _outerClipper->runAction(Sequence::createWithTwoActions(ScaleBy::create(0.05f, 0.95f),
                                               ScaleTo::create(0.125f, 1)));
}


void HoleDemo::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
	Touch *touch = (Touch *)touches[0];
	Vec2 point = _outerClipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
    auto rect = Rect(0, 0, _outerClipper->getContentSize().width, _outerClipper->getContentSize().height);
    if (!rect.containsPoint(point)) return;
    this->pokeHoleAtPoint(point);
}

// ScrollViewDemo

std::string ScrollViewDemo::title() const
{
	return "Scroll View Demo";
}

std::string ScrollViewDemo::subtitle() const
{
	return "Move/drag to scroll the content";
}

void ScrollViewDemo::setup()
{
    auto clipper = ClippingNode::create();
    clipper->setTag( kTagClipperNode );
    clipper->setContentSize(  Size(200, 200) );
    clipper->setAnchorPoint(  Vec2(0.5, 0.5) );
    clipper->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
    clipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
    this->addChild(clipper);

    auto stencil = DrawNode::create();
    Vec2 rectangle[4];
    rectangle[0] = Vec2(0, 0);
    rectangle[1] = Vec2(clipper->getContentSize().width, 0);
    rectangle[2] = Vec2(clipper->getContentSize().width, clipper->getContentSize().height);
    rectangle[3] = Vec2(0, clipper->getContentSize().height);
    
    Color4F white(1, 1, 1, 1);
    stencil->drawPolygon(rectangle, 4, white, 1, white);
    clipper->setStencil(stencil);

    auto content = Sprite::create(s_back2);
    content->setTag( kTagContentNode );
    content->setAnchorPoint(  Vec2(0.5, 0.5) );
    content->setPosition(clipper->getContentSize().width / 2, clipper->getContentSize().height / 2);
    clipper->addChild(content);
    
    _scrolling = false;

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(ScrollViewDemo::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(ScrollViewDemo::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(ScrollViewDemo::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void ScrollViewDemo::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
	Touch *touch = touches[0];
    auto clipper = this->getChildByTag(kTagClipperNode);
	Vec2 point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
    auto rect = Rect(0, 0, clipper->getContentSize().width, clipper->getContentSize().height);
    _scrolling = rect.containsPoint(point);
    _lastPoint = point;
}

void ScrollViewDemo::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    if (!_scrolling) return;
	Touch *touch = touches[0];
    auto clipper = this->getChildByTag(kTagClipperNode);
    auto point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
	Vec2 diff = point - _lastPoint;
    auto content = clipper->getChildByTag(kTagContentNode);
    content->setPosition(content->getPosition() + diff);
    _lastPoint = point;
}

void ScrollViewDemo::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
    if (!_scrolling) return;
    _scrolling = false;
}

// RawStencilBufferTests

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

}

std::string RawStencilBufferTest::title() const
{
	return "Raw Stencil Tests";
}

std::string RawStencilBufferTest::subtitle() const
{
	return "1:Default";
}

void RawStencilBufferTest::setup()
{
    glGetIntegerv(GL_STENCIL_BITS, &_stencilBits);
    if (_stencilBits < 3) {
        CCLOGWARN("Stencil must be enabled for the current GLView.");
    }
    
    for(int i = 0; i < _planeCount; ++i)
    {
        Sprite* sprite = Sprite::create(s_pathGrossini);
        sprite->setAnchorPoint(  Vec2(0.5, 0) );
        sprite->setScale( 2.5f );
        _sprites.pushBack(sprite);

        Sprite* sprite2 = Sprite::create(s_pathGrossini);
        sprite2->setAnchorPoint(  Vec2(0.5, 0) );
        sprite2->setScale( 2.5f );
        _spritesStencil.pushBack(sprite2);
    }

    Director::getInstance()->setAlphaBlending(true);
}

void RawStencilBufferTest::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{    
    auto winPoint = Vec2(Director::getInstance()->getWinSize());
    
    auto planeSize = winPoint * (1.0 / _planeCount);
    
    size_t neededCmdSize = _planeCount * 2 + 2;
    if(_renderCmds.size() != neededCmdSize)
    {
        _renderCmds.resize(neededCmdSize);
    }
    
    auto iter = _renderCmds.begin();
    
    iter->init(_globalZOrder);
    iter->func = CC_CALLBACK_0(RawStencilBufferTest::onEnableStencil, this);
    renderer->addCommand(&(*iter));
    ++iter;

    for (int i = 0; i < _planeCount; i++) {
        
        auto stencilPoint = planeSize * (_planeCount - i);
        stencilPoint.x = winPoint.x;
        
        auto spritePoint = planeSize * i;
        spritePoint.x += planeSize.x / 2;
        spritePoint.y = 0;
        _sprites.at(i)->setPosition( spritePoint );
        _spritesStencil.at(i)->setPosition( spritePoint );

        iter->init(_globalZOrder);
        iter->func = CC_CALLBACK_0(RawStencilBufferTest::onBeforeDrawClip, this, i, stencilPoint);
        renderer->addCommand(&(*iter));
        ++iter;
        
        Director* director = Director::getInstance();
        CCASSERT(nullptr != director, "Director is null when seting matrix stack");
        director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
        
        _modelViewTransform = this->transform(transform);
        _spritesStencil.at(i)->visit(renderer, _modelViewTransform, flags);
        director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
                
        iter->init(_globalZOrder);
        iter->func = CC_CALLBACK_0(RawStencilBufferTest::onBeforeDrawSprite, this, i, winPoint);
        renderer->addCommand(&(*iter));
        ++iter;
        
        director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
        _modelViewTransform = this->transform(transform);
        _sprites.at(i)->visit(renderer, _modelViewTransform, flags);
        director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    }
    
    iter->init(_globalZOrder);
    iter->func = CC_CALLBACK_0(RawStencilBufferTest::onDisableStencil, this);
    renderer->addCommand(&(*iter));
}

void RawStencilBufferTest::onEnableStencil()
{
    glEnable(GL_STENCIL_TEST);
    CHECK_GL_ERROR_DEBUG();
}

void RawStencilBufferTest::onDisableStencil()
{
    glDisable(GL_STENCIL_TEST);
    CHECK_GL_ERROR_DEBUG();
}

void RawStencilBufferTest::onBeforeDrawClip(int planeIndex, const Vec2& pt)
{
    this->setupStencilForClippingOnPlane(planeIndex);
    CHECK_GL_ERROR_DEBUG();

    Vec2 vertices[] = {
        Vec2::ZERO,
        Vec2(pt.x, 0),
        pt,
        Vec2(0, pt.y)
    };
    
    auto glProgram= GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
    
    int colorLocation = glProgram->getUniformLocation("u_color");
    CHECK_GL_ERROR_DEBUG();

    Color4F color(1, 1, 1, 1);
    
    glProgram->use();
    glProgram->setUniformsForBuiltins();
    glProgram->setUniformLocationWith4fv(colorLocation, (GLfloat*) &color.r, 1);
    
    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION );
    
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
}

void RawStencilBufferTest::onBeforeDrawSprite(int planeIndex, const Vec2& pt)
{
    this->setupStencilForDrawingOnPlane(planeIndex);
    CHECK_GL_ERROR_DEBUG();

    Vec2 vertices[] = {
        Vec2::ZERO,
        Vec2(pt.x, 0),
        pt,
        Vec2(0, pt.y)
    };

    auto glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);

    int colorLocation = glProgram->getUniformLocation("u_color");
    CHECK_GL_ERROR_DEBUG();

    Color4F color = _planeColor[planeIndex];
    glProgram->use();
    glProgram->setUniformsForBuiltins();
    glProgram->setUniformLocationWith4fv(colorLocation, (GLfloat*) &color.r, 1);

    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION );

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
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

std::string RawStencilBufferTest2::subtitle() const
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

std::string RawStencilBufferTest3::subtitle() const
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

void RawStencilBufferTestAlphaTest::setup()
{
    RawStencilBufferTest::setup();
    auto programState = GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV);
    for(int i = 0; i < _planeCount; ++i)
    {
        _spritesStencil.at(i)->setGLProgramState(programState);
    }
}
//@implementation RawStencilBufferTest4

std::string RawStencilBufferTest4::subtitle() const
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
    auto program = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV);
    GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);
    program->use();
    program->setUniformLocationWith1f(alphaValueLocation, _alphaThreshold);
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

std::string RawStencilBufferTest5::subtitle() const
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
    auto program = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV);
    GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);
    program->use();
    program->setUniformLocationWith1f(alphaValueLocation, _alphaThreshold);
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

std::string RawStencilBufferTest6::subtitle() const
{
	return "6:ManualClear,AlphaTest:ENABLE";
}

void RawStencilBufferTest6::setup()
{
    RawStencilBufferTestAlphaTest::setup();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    auto winPoint = Vec2(Director::getInstance()->getWinSize());
    //by default, glReadPixels will pack data with 4 bytes allignment
    unsigned char bits[4] = {0,0,0,0};
    glStencilMask(~0);
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);
    glFlush();
    glReadPixels(0, 0, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &bits);
    auto clearToZeroLabel = Label::createWithTTF(String::createWithFormat("00=%02x", bits[0])->getCString(), "fonts/arial.ttf", 20);
    clearToZeroLabel->setPosition((winPoint.x / 3) * 1, winPoint.y - 10);
    this->addChild(clearToZeroLabel);
    glStencilMask(0x0F);
    glClearStencil(0xAA);
    glClear(GL_STENCIL_BUFFER_BIT);
    glFlush();
    glReadPixels(0, 0, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &bits);
    auto clearToMaskLabel = Label::createWithTTF(String::createWithFormat("0a=%02x", bits[0])->getCString(), "fonts/arial.ttf", 20);
    clearToMaskLabel->setPosition((winPoint.x / 3) * 2, winPoint.y - 10);
    this->addChild(clearToMaskLabel);
#endif
    glStencilMask(~0);
}

void RawStencilBufferTest6::setupStencilForClippingOnPlane(GLint plane)
{
    GLint planeMask = 0x1 << plane;
    glStencilMask(planeMask);
    glStencilFunc(GL_NEVER, 0, planeMask);
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
  
    Vec2 pt = Director::getInstance()->getWinSize();
    Vec2 vertices[] = {
        Vec2::ZERO,
        Vec2(pt.x, 0),
        pt,
        Vec2(0, pt.y)
    };

    auto glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);

    int colorLocation = glProgram->getUniformLocation("u_color");
    CHECK_GL_ERROR_DEBUG();

    Color4F color(1, 1, 1, 1);

    glProgram->use();
    glProgram->setUniformsForBuiltins();
    glProgram->setUniformLocationWith4fv(colorLocation, (GLfloat*) &color.r, 1);

    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION );

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
    
    glStencilFunc(GL_NEVER, planeMask, planeMask);
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, _alphaThreshold);
#else
    auto program = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV);
    GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);
    program->use();
    program->setUniformLocationWith1f(alphaValueLocation, _alphaThreshold);
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

//ClippingToRenderTextureTest

std::string ClippingToRenderTextureTest::title() const
{
    return "Clipping to RenderTexture";
}

std::string ClippingToRenderTextureTest::subtitle() const
{
    return "Both should look the same";
}

void ClippingToRenderTextureTest::setup()
{
    auto button = MenuItemFont::create("Reproduce bug", [&](Ref *sender) {
        enumerateChildren("remove me [0-9]", [&](Node *node) {
            this->removeChild(node);
            this->reproduceBug();
            return false;
        }
                          );
    });

    auto s = Director::getInstance()->getWinSize();
    // create menu, it's an autorelease object
    auto menu = Menu::create(button, nullptr);
    menu->setPosition(Point(s.width/2, s.height/2));
    this->addChild(menu, 1);

    expectedBehaviour();
}

void ClippingToRenderTextureTest::expectedBehaviour()
{
    auto director = Director::getInstance();
    Size visibleSize = director->getVisibleSize();
    Point origin = director->getVisibleOrigin();


    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("Images/grossini.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    sprite->setName("remove me 0");

    // container node that will contain the clippingNode
    auto container = Node::create();
    this->addChild(container);
    container->setName("remove me 1");

    auto stencil = DrawNode::create();
    Point triangle[3];
    triangle[0] = Point(-50, -50);
    triangle[1] = Point(50, -50);
    triangle[2] = Point(0, 50);
    Color4F green(0, 1, 0, 1);
    stencil->drawPolygon(triangle, 3, green, 0, green);

    auto clipper = ClippingNode::create();
    clipper->setAnchorPoint(Point(0.5, 0.5));
    clipper->setPosition( Point(visibleSize.width/2, visibleSize.height/2) );
    clipper->setStencil(stencil);
    clipper->setInverted(true);
    container->addChild(clipper, 1);


    auto img = DrawNode::create();
    triangle[0] = Point(-200, -200);
    triangle[1] = Point(200, -200);
    triangle[2] = Point(0, 200);
    Color4F red(1, 0, 0, 1);
    img->drawPolygon(triangle, 3, red, 0, red);
    clipper->addChild(img);
}

void ClippingToRenderTextureTest::reproduceBug()
{
    auto director = Director::getInstance();
    Size visibleSize = director->getVisibleSize();
    Point origin = director->getVisibleOrigin();


    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("Images/grossini.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);


    // container node that will contain the clippingNode
    auto container = Node::create();
    container->retain();

    auto stencil = DrawNode::create();
    Point triangle[3];
    triangle[0] = Point(-50, -50);
    triangle[1] = Point(50, -50);
    triangle[2] = Point(0, 50);
    Color4F green(0, 1, 0, 1);
    stencil->drawPolygon(triangle, 3, green, 0, green);

    auto clipper = ClippingNode::create();
    clipper->setAnchorPoint(Point(0.5, 0.5));
    clipper->setPosition( Point(visibleSize.width/2, visibleSize.height/2) );
    clipper->setStencil(stencil);
    clipper->setInverted(true);
    container->addChild(clipper, 1);


    auto img = DrawNode::create();
    triangle[0] = Point(-200, -200);
    triangle[1] = Point(200, -200);
    triangle[2] = Point(0, 200);
    Color4F red(1, 0, 0, 1);
    img->drawPolygon(triangle, 3, red, 0, red);
    clipper->addChild(img);

    // container rendered on Texture the size of the screen
    RenderTexture* rt = RenderTexture::create(visibleSize.width, visibleSize.height);
    rt->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(rt);

    rt->beginWithClear(0.3f, 0, 0, 1);
    container->visit();
    rt->end();
}


// main entry point

void ClippingNodeTestScene::runThisTest()
{
    auto layer = nextAction();
    addChild(layer);
    Director::getInstance()->replaceScene(this);
}
