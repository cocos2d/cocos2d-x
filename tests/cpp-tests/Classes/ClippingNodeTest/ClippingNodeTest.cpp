/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

//
// ClippingNodeTest
// 
//
// by Pierre-David Bélanger
//

#include "ClippingNodeTest.h"
#include "../testResource.h"
#include "renderer/CCRenderer.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/ccShaders.h"

USING_NS_CC;

enum {
	kTagTitleLabel = 1,
	kTagSubtitleLabel = 2,
	kTagStencilNode = 100,
	kTagClipperNode = 101,
	kTagContentNode = 102,
};

ClippingNodeTests::ClippingNodeTests()
{
    ADD_TEST_CASE(ScrollViewDemo);
    ADD_TEST_CASE(HoleDemo);
    ADD_TEST_CASE(ShapeTest);
    ADD_TEST_CASE(ShapeInvertedTest);
    ADD_TEST_CASE(SpriteTest);
    ADD_TEST_CASE(SpriteNoAlphaTest);
    ADD_TEST_CASE(SpriteInvertedTest);
    ADD_TEST_CASE(NestedTest);
    ADD_TEST_CASE(RawStencilBufferTest);
    ADD_TEST_CASE(RawStencilBufferTest2);
    ADD_TEST_CASE(RawStencilBufferTest3);
    ADD_TEST_CASE(RawStencilBufferTest4);
    ADD_TEST_CASE(RawStencilBufferTest5);
    ADD_TEST_CASE(RawStencilBufferTest6);
    ADD_TEST_CASE(ClippingToRenderTextureTest);
    ADD_TEST_CASE(ClippingRectangleNodeTest);
}

//// Demo examples start here

//@implementation BaseClippingNodeTest

bool BaseClippingNodeTest::init()
{
	if (TestCase::init()) {
        
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
    clipper->setAnchorPoint(Vec2(0.5f, 0.5f));
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
        clipper->setAnchorPoint(Vec2(0.5f, 0.5f));
        clipper->setPosition(parent->getContentSize().width / 2, parent->getContentSize().height / 2);
        clipper->setAlphaThreshold(0.05f);
        clipper->runAction(RepeatForever::create(RotateBy::create(i % 3 ? 1.33f : 1.66f, i % 2 ? 90.0f : -90.0f)));
        parent->addChild(clipper);
        
        auto stencil = Sprite::create(s_pathGrossini);
        stencil->setScale( 2.5f - (i * (2.5f / depth)) );
        stencil->setAnchorPoint( Vec2(0.5f, 0.5f) );
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
    AffineTransform transform = AffineTransform::IDENTITY;
    transform = AffineTransformScale(transform, target->getScale(), target->getScale());

    _outerClipper->setContentSize(SizeApplyAffineTransform(target->getContentSize(), transform));
    _outerClipper->setAnchorPoint( Vec2(0.5f, 0.5f) );
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
    clipper->setContentSize(  Size(200.0f, 200.0f) );
    clipper->setAnchorPoint(  Vec2(0.5f, 0.5f) );
    clipper->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
    clipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
    this->addChild(clipper);

    auto stencil = DrawNode::create();
    Vec2 rectangle[4];
    rectangle[0] = Vec2(0.0f, 0.0f);
    rectangle[1] = Vec2(clipper->getContentSize().width, 0.0f);
    rectangle[2] = Vec2(clipper->getContentSize().width, clipper->getContentSize().height);
    rectangle[3] = Vec2(0.0f, clipper->getContentSize().height);
    
    Color4F white(1, 1, 1, 1);
    stencil->drawPolygon(rectangle, 4, white, 1, white);
    clipper->setStencil(stencil);

    auto content = Sprite::create(s_back2);
    content->setTag( kTagContentNode );
    content->setAnchorPoint(  Vec2(0.5f, 0.5f) );
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

static const float _alphaThreshold = 0.05f;

static const int _planeCount = 8;
static const float _planeColor[][4] = {
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

    initCommands();
}

void RawStencilBufferTest::initCommands()
{
    auto renderer = Director::getInstance()->getRenderer();
    _enableStencilCallback.func = [=](){
        renderer->setStencilTest(true);
    };
    _enableStencilCallback.init(_globalZOrder);

    _disableStencilCallback.func = [=](){
        renderer->setStencilTest(false);
    };
    _disableStencilCallback.init(_globalZOrder);

    auto program = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_UCOLOR);
    _programState = new (std::nothrow) backend::ProgramState(program);
    _locColor = _programState->getProgram()->getUniformLocation("u_color");
    _locMVPMatrix = _programState->getProgram()->getUniformLocation("u_MVPMatrix");
    const auto& projectionMat = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    _programState->setUniform(_locMVPMatrix, projectionMat.m, sizeof(projectionMat.m));

    size_t neededCmdSize = _planeCount * 2;
    _renderCmds.resize(neededCmdSize);
    auto winPoint = Vec2(Director::getInstance()->getWinSize());
    auto planeSize = winPoint * (1.0 / _planeCount);
    BlendFunc blend;
    blend.src = backend::BlendFactor::ONE;
    blend.dst = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
    for (int i = 0, cmdIndex = 0; i < _planeCount; i++)
    {
        auto stencilPoint = planeSize * (_planeCount - i);
        stencilPoint.x = winPoint.x;

        auto& cmd = _renderCmds[cmdIndex];
        cmdIndex++;
        cmd.init(_globalZOrder, blend);
        cmd.setBeforeCallback( CC_CALLBACK_0(RawStencilBufferTest::onBeforeDrawClip, this, i) );
        Vec2 vertices[] = {
            Vec2::ZERO,
            Vec2(stencilPoint.x, 0.0f),
            stencilPoint,
            Vec2(0.0f, stencilPoint.y)
        };
        unsigned short indices[] = {0, 2, 1, 0, 3, 2};
        cmd.createVertexBuffer(sizeof(Vec2), 4, backend::BufferUsage::STATIC);
        cmd.updateVertexBuffer(vertices, sizeof(vertices));
        cmd.createIndexBuffer(backend::IndexFormat::U_SHORT, 6, backend::BufferUsage::STATIC);
        cmd.updateIndexBuffer(indices, sizeof(indices));
        cmd.getPipelineDescriptor().programState = _programState;
        auto vertexLayout = _programState->getVertexLayout();
        auto& attributes = _programState->getProgram()->getActiveAttributes();
        auto iter = attributes.find("a_position");
        if (iter != attributes.end())
            vertexLayout->setAttribute("a_position", iter->second.location, backend::VertexFormat::FLOAT2, 0, false);
        vertexLayout->setLayout(sizeof(Vec2));


        auto& cmd2 = _renderCmds[cmdIndex];
        cmdIndex++;
        cmd2.init(_globalZOrder, blend);
        cmd2.setBeforeCallback(CC_CALLBACK_0(RawStencilBufferTest::onBeforeDrawSprite, this, i));
        Vec2 vertices2[] = {
            Vec2::ZERO,
            Vec2(winPoint.x, 0.0f),
            winPoint,
            Vec2(0.0f, winPoint.y)
        };
        cmd2.createVertexBuffer(sizeof(Vec2), 4, backend::BufferUsage::STATIC);
        cmd2.updateVertexBuffer(vertices2, sizeof(vertices2));
        cmd2.createIndexBuffer(backend::IndexFormat::U_SHORT, 6, backend::BufferUsage::STATIC);
        cmd2.updateIndexBuffer(indices, sizeof(indices));
        cmd2.getPipelineDescriptor().programState = _programState;
    }
}

void RawStencilBufferTest::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{    
    auto winPoint = Vec2(Director::getInstance()->getWinSize());
    auto planeSize = winPoint * (1.0 / _planeCount);

    renderer->addCommand(&_enableStencilCallback);

    for (int i = 0, cmdIndex = 0; i < _planeCount; i++)
    {
        auto spritePoint = planeSize * i;
        spritePoint.x += planeSize.x / 2;
        spritePoint.y = 0;
        _sprites.at(i)->setPosition( spritePoint );
        _spritesStencil.at(i)->setPosition( spritePoint );

        renderer->clear(ClearFlag::STENCIL, Color4F::BLACK, 0.f, 0x0, _globalZOrder);

        renderer->addCommand(&_renderCmds[cmdIndex]);
        cmdIndex++;
        
        Director* director = Director::getInstance();
        CCASSERT(nullptr != director, "Director is null when setting matrix stack");
        director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
        
        _modelViewTransform = this->transform(transform);
        _spritesStencil.at(i)->visit(renderer, _modelViewTransform, flags);
        director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
                
        renderer->addCommand(&_renderCmds[cmdIndex]);
        cmdIndex++;
        
        director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
        _modelViewTransform = this->transform(transform);
        _sprites.at(i)->visit(renderer, _modelViewTransform, flags);
        director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    }

    renderer->addCommand(&_disableStencilCallback);
}

void RawStencilBufferTest::onBeforeDrawClip(int planeIndex)
{
    this->setupStencilForClippingOnPlane(planeIndex);
    float color[4] = {1.f, 1.f, 1.f, 1.f};
    _programState->setUniform(_locColor, color, sizeof(color));
}

void RawStencilBufferTest::onBeforeDrawSprite(int planeIndex)
{
    this->setupStencilForDrawingOnPlane(planeIndex);
    auto& color = _planeColor[planeIndex];
    _programState->setUniform(_locColor, (void*)color, sizeof(color));
}

void RawStencilBufferTest::setupStencilForClippingOnPlane(int plane)
{
    auto renderer = Director::getInstance()->getRenderer();
    unsigned int planeMask = 0x1 << plane;
    renderer->setStencilWriteMask(planeMask);
    renderer->setStencilCompareFunction(backend::CompareFunction::NEVER, planeMask, planeMask);
    renderer->setStencilOperation(backend::StencilOperation::REPLACE, backend::StencilOperation::KEEP, backend::StencilOperation::KEEP);
}

void RawStencilBufferTest::setupStencilForDrawingOnPlane(int plane)
{
    auto renderer = Director::getInstance()->getRenderer();
    unsigned int planeMask = 0x1 << plane;
    renderer->setStencilCompareFunction(backend::CompareFunction::EQUAL, planeMask, planeMask);
    renderer->setStencilOperation(backend::StencilOperation::KEEP, backend::StencilOperation::KEEP, backend::StencilOperation::KEEP);
}

//@implementation RawStencilBufferTest2

std::string RawStencilBufferTest2::subtitle() const
{
	return "2:DepthMask:FALSE";
}

void RawStencilBufferTest2::setupStencilForClippingOnPlane(int plane)
{
    RawStencilBufferTest::setupStencilForClippingOnPlane(plane);
    Director::getInstance()->getRenderer()->setDepthWrite(false);
}

void RawStencilBufferTest2::setupStencilForDrawingOnPlane(int plane)
{
    Director::getInstance()->getRenderer()->setDepthWrite(true);
    RawStencilBufferTest::setupStencilForDrawingOnPlane(plane);
}

//@implementation RawStencilBufferTest3

std::string RawStencilBufferTest3::subtitle() const
{
	return "3:DepthTest:DISABLE,DepthMask:FALSE";
}

void RawStencilBufferTest3::setupStencilForClippingOnPlane(int plane)
{
    RawStencilBufferTest::setupStencilForClippingOnPlane(plane);
    auto renderer = Director::getInstance()->getRenderer();
    renderer->setDepthTest(false);
    renderer->setDepthWrite(false);
}

void RawStencilBufferTest3::setupStencilForDrawingOnPlane(int plane)
{
    Director::getInstance()->getRenderer()->setDepthWrite(true);
    RawStencilBufferTest::setupStencilForDrawingOnPlane(plane);
}

void RawStencilBufferTestAlphaTest::setup()
{
    RawStencilBufferTest::setup();
    for(int i = 0; i < _planeCount; ++i)
    {
        auto program = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_TEXTURE_COLOR_ALPHA_TEST);
        auto programState = new backend::ProgramState(program);
        programState->setUniform(programState->getUniformLocation("u_alpha_value"), &_alphaThreshold, sizeof(_alphaThreshold));
        _spritesStencil.at(i)->setProgramState(programState);
    }
}
//@implementation RawStencilBufferTest4

std::string RawStencilBufferTest4::subtitle() const
{
	return "4:DepthMask:FALSE,AlphaTest:ENABLE";
}

void RawStencilBufferTest4::setupStencilForClippingOnPlane(int plane)
{
    RawStencilBufferTest::setupStencilForClippingOnPlane(plane);
    auto renderer = Director::getInstance()->getRenderer();
    renderer->setDepthWrite(false);
}

void RawStencilBufferTest4::setupStencilForDrawingOnPlane(int plane)
{
    Director::getInstance()->getRenderer()->setDepthWrite(true);
    RawStencilBufferTest::setupStencilForDrawingOnPlane(plane);
}

//@implementation RawStencilBufferTest5

std::string RawStencilBufferTest5::subtitle() const
{
	return "5:DepthTest:DISABLE,DepthMask:FALSE,AlphaTest:ENABLE";
}

void RawStencilBufferTest5::setupStencilForClippingOnPlane(int plane)
{
    RawStencilBufferTest::setupStencilForClippingOnPlane(plane);
    auto renderer = Director::getInstance()->getRenderer();
    renderer->setDepthWrite(false);
    renderer->setDepthTest(false);
}

void RawStencilBufferTest5::setupStencilForDrawingOnPlane(int plane)
{
    auto renderer = Director::getInstance()->getRenderer();
    renderer->setDepthWrite(false);
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
    Director::getInstance()->getRenderer()->setStencilWriteMask(~0);
}

void RawStencilBufferTest6::setupStencilForClippingOnPlane(int plane)
{
    int planeMask = 0x1 << plane;
    auto renderer = Director::getInstance()->getRenderer();
    renderer->setStencilCompareFunction(backend::CompareFunction::NEVER, planeMask, planeMask);
    renderer->setStencilOperation(backend::StencilOperation::REPLACE, backend::StencilOperation::KEEP, backend::StencilOperation::KEEP);
    renderer->setDepthTest(false);
    renderer->setDepthWrite(false);
}

void RawStencilBufferTest6::setupStencilForDrawingOnPlane(int plane)
{
    auto renderer = Director::getInstance()->getRenderer();
    renderer->setDepthWrite(true);
    RawStencilBufferTest::setupStencilForDrawingOnPlane(plane);
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
        std::vector<Node*> nodes;
        enumerateChildren("remove me [0-9]", [&](Node *node) {
            nodes.push_back(node);
            return false;
        });
        for (auto node : nodes)
        {
            this->removeChild(node);
        }
        this->reproduceBug();
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
    clipper->setAnchorPoint(Point(0.5f, 0.5f));
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
    clipper->setAnchorPoint(Point(0.5f, 0.5f));
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

    // container rendered on Texture the size of the screen and because Clipping node use stencil buffer so we need to
    // create RenderTexture with depthStencil format parameter
    RenderTexture* rt = RenderTexture::create(visibleSize.width, visibleSize.height, backend::PixelFormat::RGBA8888, PixelFormat::D24S8);
    rt->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(rt);

    rt->begin();
    container->visit();
    rt->end();
}

// ClippingRectangleNodeDemo

std::string ClippingRectangleNodeTest::title() const
{
	return "ClippingRectangleNode Test";
}

std::string ClippingRectangleNodeTest::subtitle() const
{
	return "more effectively";
}

void ClippingRectangleNodeTest::setup()
{
    auto clipper = ClippingRectangleNode::create();
    clipper->setClippingRegion(Rect(this->getContentSize().width / 2 - 100, this->getContentSize().height / 2 - 100, 200.0f, 200.0f));
    clipper->setTag( kTagClipperNode );
    this->addChild(clipper);
    
    auto content = Sprite::create(s_back2);
    content->setTag( kTagContentNode );
    content->setAnchorPoint(  Vec2(0.5f, 0.5f) );
    content->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
    clipper->addChild(content);
}
