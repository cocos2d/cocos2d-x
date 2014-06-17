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
    CL(Sprite3DEffectTest),
    CL(Sprite3DWithSkinTest)
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
    auto seq = Sequence::create( action, action_back, NULL );
    
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
    _backToForegroundListener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND,
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
    CC_SAFE_RELEASE_NULL(_sprite);
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
        CC_SAFE_RETAIN(sprite);
        CC_SAFE_RELEASE_NULL(_sprite);
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
    if(_sprite && _sprite->getMesh())
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glEnable(GL_DEPTH_TEST);
        
        auto mesh = _sprite->getMesh();
        glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer());
        _glProgramState->apply(transform);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexBuffer());
        glDrawElements((GLenum)mesh->getPrimitiveType(), (GLsizei)mesh->getIndexCount(), (GLenum)mesh->getIndexFormat(), 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glCullFace(GL_BACK);
        glDisable(GL_CULL_FACE);
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, mesh->getIndexCount());
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
    auto seq = Sequence::create( action, action_back, NULL );
    
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
    return "Testing Sprite3D for animation from c3t";
}
std::string Sprite3DWithSkinTest::subtitle() const
{
    return "Tap screen to add more sprite3D";
}

void Sprite3DWithSkinTest::addNewSpriteWithCoords(Vec2 p)
{
    auto sprite = Sprite3D::create("Sprite3DTest/girl.c3t");
    addChild(sprite);
    sprite->setRotation3D(Vec3(-90.f, 0.f, 0.f));
    sprite->setPosition( Vec2( p.x, p.y) );

    auto animation = Animation3D::getOrCreate("Sprite3DTest/girl.c3t");
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        if(std::rand() %3 == 0)
        {
            animate->setPlayBack(true);
        }

        int rand2 = std::rand();
        if(rand2 % 3 == 1)
        {
            animate->setSpeed(animate->getSpeed() + CCRANDOM_0_1());
        }
        else if(rand2 % 3 == 2)
        {
            animate->setSpeed(animate->getSpeed() - 0.5 * CCRANDOM_0_1());
        }

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
