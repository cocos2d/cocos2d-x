/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#include "Sprite3DTest.h"
#include "3d/CCAnimation3D.h"
#include "3d/CCAnimate3D.h"
#include "3d/CCSubMesh.h"
#include "3d/CCAttachNode.h"

#include <algorithm>
#include "../testResource.h"

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1;


static std::function<Layer*()> createFunctions[] =
{
    CL(Sprite3DBasicTest),
    CL(Sprite3DHitTest),
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    // 3DEffect use custom shader which is not supported on WP8/WinRT yet. 
    CL(Sprite3DEffectTest),
#endif
    CL(Sprite3DWithSkinTest),
    CL(Animate3DTest),
    CL(AttachmentTest)
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextSpriteTestAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* backSpriteTestAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* restartSpriteTestAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

//------------------------------------------------------------------
//
// SpriteTestDemo
//
//------------------------------------------------------------------

Sprite3DTestDemo::Sprite3DTestDemo(void)
: BaseTest()
{
}

Sprite3DTestDemo::~Sprite3DTestDemo(void)
{
}

std::string Sprite3DTestDemo::title() const
{
    return "No title";
}

std::string Sprite3DTestDemo::subtitle() const
{
    return "";
}

void Sprite3DTestDemo::onEnter()
{
    BaseTest::onEnter();
}

void Sprite3DTestDemo::restartCallback(Ref* sender)
{
    auto s = new Sprite3DTestScene();
    s->addChild(restartSpriteTestAction());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void Sprite3DTestDemo::nextCallback(Ref* sender)
{
    auto s = new Sprite3DTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void Sprite3DTestDemo::backCallback(Ref* sender)
{
    auto s = new Sprite3DTestScene();
    s->addChild( backSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}


//------------------------------------------------------------------
//
// Sprite3DBasicTest
//
//------------------------------------------------------------------

Sprite3DBasicTest::Sprite3DBasicTest()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(Sprite3DBasicTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto s = Director::getInstance()->getWinSize();
    addNewSpriteWithCoords( Vec2(s.width/2, s.height/2) );
}

void Sprite3DBasicTest::addNewSpriteWithCoords(Vec2 p)
{
    //int idx = (int)(CCRANDOM_0_1() * 1400.0f / 100.0f);
    //int x = (idx%5) * 85;
    //int y = (idx/5) * 121;
    
//    //option 1: load a obj that contain the texture in it
//    auto sprite = Sprite3D::create("sprite3dTest/scene01.obj");
    
    //option 2: load obj and assign the texture
    auto sprite = Sprite3D::create("Sprite3DTest/boss1.obj");
    sprite->setScale(3.f);
    sprite->setTexture("Sprite3DTest/boss.png");
    
    //
    //sprite->setEffect(cocos2d::EFFECT_OUTLINE);
    
    //add to scene
    addChild( sprite );
    
    sprite->setPosition( Vec2( p.x, p.y) );
    
    ActionInterval* action;
    float random = CCRANDOM_0_1();
    
    if( random < 0.20 )
        action = ScaleBy::create(3, 2);
    else if(random < 0.40)
        action = RotateBy::create(3, 360);
    else if( random < 0.60)
        action = Blink::create(1, 3);
    else if( random < 0.8 )
        action = TintBy::create(2, 0, -255, -255);
    else
        action = FadeOut::create(2);
    auto action_back = action->reverse();
    auto seq = Sequence::create( action, action_back, nullptr );
    
    sprite->runAction( RepeatForever::create(seq) );
}

void Sprite3DBasicTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    for (auto touch: touches)
    {
        auto location = touch->getLocation();
        
        addNewSpriteWithCoords( location );
    }
}

std::string Sprite3DBasicTest::title() const
{
    return "Testing Sprite3D";
}

std::string Sprite3DBasicTest::subtitle() const
{
    return "Tap screen to add more sprites";
}

//------------------------------------------------------------------
//
// Sprite3DHitTest
//
//------------------------------------------------------------------


Sprite3DHitTest::Sprite3DHitTest()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto sprite1 = Sprite3D::create("Sprite3DTest/boss1.obj");
    
    sprite1->setScale(4.f);
    sprite1->setTexture("Sprite3DTest/boss.png");
    sprite1->setPosition( Vec2(s.width/2, s.height/2) );
    sprite1->setContentSize(Size(20, 20));
    
    //add to scene
    addChild( sprite1 );
    sprite1->runAction(RepeatForever::create(RotateBy::create(3, 360)));
    
    auto sprite2 = Sprite3D::create("Sprite3DTest/boss1.obj");
    
    sprite2->setScale(4.f);
    sprite2->setTexture("Sprite3DTest/boss.png");
    sprite2->setPosition( Vec2(s.width/2, s.height/2) );
    sprite2->setContentSize(Size(20, 20));
    sprite2->setAnchorPoint(Vec2(0.5, 0.5));
    
    //add to scene
    addChild( sprite2 );
    sprite2->runAction(RepeatForever::create(RotateBy::create(3, -360)));
    
    
    // Make sprite1 touchable
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite3D*>(event->getCurrentTarget());
        
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(-s.width/2, -s.height/2, s.width, s.height);
        
        if (rect.containsPoint(locationInNode))
        {
            log("sprite3d began... x = %f, y = %f", locationInNode.x, locationInNode.y);
            target->setOpacity(100);
            return true;
        }
        return false;
    };
    
    listener1->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite3D*>(event->getCurrentTarget());
        target->setPosition(target->getPosition() + touch->getDelta());
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite3D*>(event->getCurrentTarget());
        log("sprite3d onTouchesEnded.. ");
        target->setOpacity(255);
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
    
}

std::string Sprite3DHitTest::title() const
{
    return "Testing Sprite3D Touch in 2D";
}

std::string Sprite3DHitTest::subtitle() const
{
    return "Tap Sprite3D and Drag";
}

void Sprite3DTestScene::runThisTest()
{
    auto layer = nextSpriteTestAction();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}

static int tuple_sort( const std::tuple<ssize_t,Effect3D*,CustomCommand> &tuple1, const std::tuple<ssize_t,Effect3D*,CustomCommand> &tuple2 )
{
    return std::get<0>(tuple1) < std::get<0>(tuple2);
}

EffectSprite3D* EffectSprite3D::createFromObjFileAndTexture(const std::string &objFilePath, const std::string &textureFilePath)
{
    auto sprite = new EffectSprite3D();
    if (sprite && sprite->initWithFile(objFilePath))
    {
        sprite->autorelease();
        sprite->setTexture(textureFilePath);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

EffectSprite3D::EffectSprite3D()
: _defaultEffect(nullptr)
{
    
}

EffectSprite3D::~EffectSprite3D()
{
    for(auto effect : _effects)
    {
        CC_SAFE_RELEASE_NULL(std::get<1>(effect));
    }
    CC_SAFE_RELEASE(_defaultEffect);
}

void EffectSprite3D::setEffect3D(Effect3D *effect)
{
    if(_defaultEffect == effect) return;
    CC_SAFE_RETAIN(effect);
    CC_SAFE_RELEASE(_defaultEffect);
    _defaultEffect = effect;
}

void EffectSprite3D::addEffect(Effect3DOutline* effect, ssize_t order)
{
    if(nullptr == effect) return;
    effect->retain();
    effect->setTarget(this);
    
    _effects.push_back(std::make_tuple(order,effect,CustomCommand()));

    std::sort(std::begin(_effects), std::end(_effects), tuple_sort);
}

const std::string Effect3DOutline::_vertShaderFile = "Shaders3D/OutLine.vert";
const std::string Effect3DOutline::_fragShaderFile = "Shaders3D/OutLine.frag";
const std::string Effect3DOutline::_keyInGLProgramCache = "Effect3DLibrary_Outline";
GLProgram* Effect3DOutline::getOrCreateProgram()
{
    auto program = GLProgramCache::getInstance()->getGLProgram(_keyInGLProgramCache);
    if(program == nullptr)
    {
        program = GLProgram::createWithFilenames(_vertShaderFile, _fragShaderFile);
        GLProgramCache::getInstance()->addGLProgram(program, _keyInGLProgramCache);
    }
    return program;
}

Effect3DOutline* Effect3DOutline::create()
{
    Effect3DOutline* effect = new Effect3DOutline();
    if(effect && effect->init())
    {
        effect->autorelease();
        return effect;
    }
    else
    {
        CC_SAFE_DELETE(effect);
        return nullptr;
    }
}

bool Effect3DOutline::init()
{

    GLProgram* glprogram = GLProgram::createWithFilenames(_vertShaderFile, _fragShaderFile);
    if(nullptr == glprogram)
    {
        CC_SAFE_DELETE(glprogram);
        return false;
    }
    _glProgramState = GLProgramState::create(glprogram);
    if(nullptr == _glProgramState)
    {
        return false;
    }
    _glProgramState->retain();
    _glProgramState->setUniformVec3("OutLineColor", _outlineColor);
    _glProgramState->setUniformFloat("OutlineWidth", _outlineWidth);
    
    return true;
}

Effect3DOutline::Effect3DOutline()
: _outlineWidth(1.0f)
, _outlineColor(1, 1, 1)
, _sprite(nullptr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                          [this](EventCustom*)
                                                          {
                                                              auto glProgram = _glProgramState->getGLProgram();
                                                              glProgram->reset();
                                                              glProgram->initWithFilenames(_vertShaderFile, _fragShaderFile);
                                                              glProgram->link();
                                                              glProgram->updateUniforms();
                                                          }
                                                          );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

Effect3DOutline::~Effect3DOutline()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

void Effect3DOutline::setOutlineColor(const Vec3& color)
{
    if(_outlineColor != color)
    {
        _outlineColor = color;
        _glProgramState->setUniformVec3("OutLineColor", _outlineColor);
    }
}

void Effect3DOutline::setOutlineWidth(float width)
{
    if(_outlineWidth != width)
    {
        _outlineWidth = width;
        _glProgramState->setUniformFloat("OutlineWidth", _outlineWidth);
    }
}

void Effect3DOutline::setTarget(EffectSprite3D *sprite)
{
    CCASSERT(nullptr != sprite && nullptr != sprite->getMesh(),"Error: Setting a null pointer or a null mesh EffectSprite3D to Effect3D");
    
    if(sprite != _sprite)
    {
        _sprite = sprite;
        
        auto mesh = sprite->getMesh();
        long offset = 0;
        for (auto i = 0; i < mesh->getMeshVertexAttribCount(); i++)
        {
            auto meshvertexattrib = mesh->getMeshVertexAttribute(i);
            
            _glProgramState->setVertexAttribPointer(s_attributeNames[meshvertexattrib.vertexAttrib],
                                                    meshvertexattrib.size,
                                                    meshvertexattrib.type,
                                                    GL_FALSE,
                                                    mesh->getVertexSizeInBytes(),
                                                    (void*)offset);
            offset += meshvertexattrib.attribSizeBytes;
        }
        
        Color4F color(_sprite->getDisplayedColor());
        color.a = _sprite->getDisplayedOpacity() / 255.0f;
        _glProgramState->setUniformVec4("u_color", Vec4(color.r, color.g, color.b, color.a));
    }
    
}

void Effect3DOutline::draw(const Mat4 &transform)
{
    //draw
    Color4F color(_sprite->getDisplayedColor());
    color.a = _sprite->getDisplayedOpacity() / 255.0f;
    _glProgramState->setUniformVec4("u_color", Vec4(color.r, color.g, color.b, color.a));
    if(_sprite && _sprite->getMesh())
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glEnable(GL_DEPTH_TEST);
        
        auto mesh = _sprite->getMesh();
        glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer());
        _glProgramState->apply(transform);
        for (ssize_t i = 0; i < mesh->getSubMeshCount(); i++) {
            auto submesh = mesh->getSubMesh((int)i);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, submesh->getIndexBuffer());
            glDrawElements((GLenum)submesh->getPrimitiveType(), (GLsizei)submesh->getIndexCount(), (GLenum)submesh->getIndexFormat(), 0);
            CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, submesh->getIndexCount());
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glCullFace(GL_BACK);
        glDisable(GL_CULL_FACE);
    }
}

void EffectSprite3D::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    for(auto &effect : _effects)
    {
        if(std::get<0>(effect) >=0)
            break;
        CustomCommand &cc = std::get<2>(effect);
        cc.func = CC_CALLBACK_0(Effect3D::draw,std::get<1>(effect),transform);
        renderer->addCommand(&cc);
        
    }
    
    if(!_defaultEffect)
    {
        Sprite3D::draw(renderer, transform, flags);
    }
    else
    {
        _command.init(_globalZOrder);
        _command.func = CC_CALLBACK_0(Effect3D::draw, _defaultEffect, transform);
        renderer->addCommand(&_command);
    }
    
    for(auto &effect : _effects)
    {
        if(std::get<0>(effect) <=0)
            continue;
        CustomCommand &cc = std::get<2>(effect);
        cc.func = CC_CALLBACK_0(Effect3D::draw,std::get<1>(effect),transform);
        renderer->addCommand(&cc);
        
    }
}

Sprite3DEffectTest::Sprite3DEffectTest()
{
    auto s = Director::getInstance()->getWinSize();
    addNewSpriteWithCoords( Vec2(s.width/2, s.height/2) );
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(Sprite3DEffectTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

std::string Sprite3DEffectTest::title() const
{
    return "Testing Sprite3D";
}
std::string Sprite3DEffectTest::subtitle() const
{
    return "Sprite3d with effects";
}

void Sprite3DEffectTest::addNewSpriteWithCoords(Vec2 p)
{
    //option 2: load obj and assign the texture
    auto sprite = EffectSprite3D::createFromObjFileAndTexture("Sprite3DTest/boss1.obj", "Sprite3DTest/boss.png");
    Effect3DOutline* effect = Effect3DOutline::create();
    effect->setOutlineColor(Vec3(1,0,0));
    effect->setOutlineWidth(0.01f);
    sprite->addEffect(effect, -1);
    Effect3DOutline* effect2 = Effect3DOutline::create();
    effect2->setOutlineWidth(0.02f);
    effect2->setOutlineColor(Vec3(1,1,0));
    sprite->addEffect(effect2, -2);
    //sprite->setEffect3D(effect);
    sprite->setScale(6.f);
    
    //add to scene
    addChild( sprite );
    
    sprite->setPosition( Vec2( p.x, p.y) );
    
    ActionInterval* action;
    float random = CCRANDOM_0_1();
    
    if( random < 0.20 )
        action = ScaleBy::create(3, 2);
    else if(random < 0.40)
        action = RotateBy::create(3, 360);
    else if( random < 0.60)
        action = Blink::create(1, 3);
    else if( random < 0.8 )
        action = TintBy::create(2, 0, -255, -255);
    else
        action = FadeOut::create(2);
    auto action_back = action->reverse();
    auto seq = Sequence::create( action, action_back, nullptr );
    
    sprite->runAction( RepeatForever::create(seq) );
}

void Sprite3DEffectTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    for (auto touch: touches)
    {
        auto location = touch->getLocation();
        
        addNewSpriteWithCoords( location );
    }
}

Sprite3DWithSkinTest::Sprite3DWithSkinTest()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(Sprite3DWithSkinTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto s = Director::getInstance()->getWinSize();
    addNewSpriteWithCoords( Vec2(s.width/2, s.height/2) );
}
std::string Sprite3DWithSkinTest::title() const
{
    return "Testing Sprite3D";
}
std::string Sprite3DWithSkinTest::subtitle() const
{
    return "Tap screen to add more sprite3D";
}

void Sprite3DWithSkinTest::addNewSpriteWithCoords(Vec2 p)
{
    std::string fileName = "Sprite3DTest/orc.c3b";
    auto sprite = Sprite3D::create(fileName);
    sprite->setScale(3);
    sprite->setRotation3D(Vec3(0,180,0));
    addChild(sprite);
    sprite->setPosition( Vec2( p.x, p.y) );

    auto animation = Animation3D::create(fileName);
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        bool inverse = (std::rand() % 3 == 0);

        int rand2 = std::rand();
        float speed = 1.0f;
        if(rand2 % 3 == 1)
        {
            speed = animate->getSpeed() + CCRANDOM_0_1();
        }
        else if(rand2 % 3 == 2)
        {
            speed = animate->getSpeed() - 0.5 * CCRANDOM_0_1();
        }
        animate->setSpeed(inverse ? -speed : speed);

        sprite->runAction(RepeatForever::create(animate));
    }
}

void Sprite3DWithSkinTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    for (auto touch: touches)
    {
        auto location = touch->getLocation();
        
        addNewSpriteWithCoords( location );
    }
}

Animate3DTest::Animate3DTest()
: _hurt(nullptr)
, _swim(nullptr)
, _sprite(nullptr)
, _moveAction(nullptr)
, _transTime(0.1f)
, _elapseTransTime(0.f)
{
    addSprite3D();
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(Animate3DTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    scheduleUpdate();
}

Animate3DTest::~Animate3DTest()
{
    CC_SAFE_RELEASE(_moveAction);
    CC_SAFE_RELEASE(_hurt);
    CC_SAFE_RELEASE(_swim);
}

std::string Animate3DTest::title() const
{
    return "Testing Animate3D";
}

std::string Animate3DTest::subtitle() const
{
    return "Touch to beat the tortoise";
}

void Animate3DTest::update(float dt)
{
    if (_state == State::HURT_TO_SWIMMING)
    {
        _elapseTransTime += dt;
        float t = _elapseTransTime / _transTime;
        
        if (t >= 1.f)
        {
            t = 1.f;
            _sprite->stopAction(_hurt);
            _state = State::SWIMMING;
        }
        _swim->setWeight(t);
        _hurt->setWeight(1.f - t);
    }
    else if (_state == State::SWIMMING_TO_HURT)
    {
        _elapseTransTime += dt;
        float t = _elapseTransTime / _transTime;
        if (t >= 1.f)
        {
            t = 1.f;
            _state = State::HURT;
        }
        _swim->setWeight(1.f - t);
        _hurt->setWeight(t);
    }
}

void Animate3DTest::addSprite3D()
{
    std::string fileName = "Sprite3DTest/tortoise.c3b";
    auto sprite = Sprite3D::create(fileName);
    sprite->setScale(0.1f);
    auto s = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(s.width * 4.f / 5.f, s.height / 2.f));
    addChild(sprite);
    _sprite = sprite;
    auto animation = Animation3D::create(fileName);
    if (animation)
    {
        auto animate = Animate3D::create(animation, 0.f, 1.933f);
        sprite->runAction(RepeatForever::create(animate));
        _swim = animate;
        _swim->retain();
        _hurt = Animate3D::create(animation, 1.933f, 2.8f);
        _hurt->retain();
        _state = State::SWIMMING;
    }
    
    _moveAction = MoveTo::create(4.f, Vec2(s.width / 5.f, s.height / 2.f));
    _moveAction->retain();
    auto seq = Sequence::create(_moveAction, CallFunc::create(CC_CALLBACK_0(Animate3DTest::reachEndCallBack, this)), nullptr);
    seq->setTag(100);
    sprite->runAction(seq);
}

void Animate3DTest::reachEndCallBack()
{
    _sprite->stopActionByTag(100);
    auto inverse = (MoveTo*)_moveAction->reverse();
    inverse->retain();
    _moveAction->release();
    _moveAction = inverse;
    auto rot = RotateBy::create(1.f, Vec3(0.f, 180.f, 0.f));
    auto seq = Sequence::create(rot, _moveAction, CallFunc::create(CC_CALLBACK_0(Animate3DTest::reachEndCallBack, this)), nullptr);
    seq->setTag(100);
    _sprite->runAction(seq);
}

void Animate3DTest::renewCallBack()
{
    _sprite->stopActionByTag(101);
    _state = State::HURT_TO_SWIMMING;
}

void Animate3DTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    for (auto touch: touches)
    {
        auto location = touch->getLocation();
        
        if (_sprite)
        {
            float len = (_sprite->getPosition() - location).length();
            if (len < 40)
            {
                //hurt the tortoise
                if (_state == State::SWIMMING)
                {
                    _sprite->runAction(_hurt);
                    auto delay = DelayTime::create(_hurt->getDuration() - 0.1f);
                    auto seq = Sequence::create(delay, CallFunc::create(CC_CALLBACK_0(Animate3DTest::renewCallBack, this)), nullptr);
                    seq->setTag(101);
                    _sprite->runAction(seq);
                    _state = State::SWIMMING_TO_HURT;
                }
                return;
            }
        }
    }
}

AttachmentTest::AttachmentTest()
: _hasWeapon(false)
, _sprite(nullptr)
{
    auto s = Director::getInstance()->getWinSize();
    addNewSpriteWithCoords( Vec2(s.width/2, s.height/2) );
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(AttachmentTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
std::string AttachmentTest::title() const
{
    return "Testing Sprite3D Attachment";
}
std::string AttachmentTest::subtitle() const
{
    return "touch to switch weapon";
}

void AttachmentTest::addNewSpriteWithCoords(Vec2 p)
{
    std::string fileName = "Sprite3DTest/orc.c3b";
    auto sprite = Sprite3D::create(fileName);
    sprite->setScale(5);
    sprite->setRotation3D(Vec3(0,180,0));
    addChild(sprite);
    sprite->setPosition( Vec2( p.x, p.y) );
    
    //test attach
    auto sp = Sprite3D::create("Sprite3DTest/axe.c3b");
    sprite->getAttachNode("Bip001 R Hand")->addChild(sp);
    
    auto animation = Animation3D::create(fileName);
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        
        sprite->runAction(RepeatForever::create(animate));
    }
    _sprite = sprite;
    _hasWeapon = true;
}

void AttachmentTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    if (_hasWeapon)
    {
        _sprite->removeAllAttachNode();
    }
    else
    {
        auto sp = Sprite3D::create("Sprite3DTest/axe.c3b");
        _sprite->getAttachNode("Bip001 R Hand")->addChild(sp);
    }
    _hasWeapon = !_hasWeapon;
}
