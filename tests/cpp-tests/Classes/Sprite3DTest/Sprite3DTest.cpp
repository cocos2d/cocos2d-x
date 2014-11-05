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
#include "3d/CCAttachNode.h"
#include "3d/CCRay.h"
#include "3d/CCSprite3D.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "DrawNode3D.h"

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
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    CL(Sprite3DWithSkinOutlineTest),
#endif
    CL(Animate3DTest),
    CL(AttachmentTest),
    CL(Sprite3DReskinTest),
    CL(Sprite3DWithOBBPerfromanceTest),
    CL(Sprite3DMirrorTest)
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
    auto s = new (std::nothrow) Sprite3DTestScene();
    s->addChild(restartSpriteTestAction());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void Sprite3DTestDemo::nextCallback(Ref* sender)
{
    auto s = new (std::nothrow) Sprite3DTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void Sprite3DTestDemo::backCallback(Ref* sender)
{
    auto s = new (std::nothrow) Sprite3DTestScene();
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
    
    //add to scene
    addChild( sprite1 );
    sprite1->runAction(RepeatForever::create(RotateBy::create(3, 360)));
    
    auto sprite2 = Sprite3D::create("Sprite3DTest/boss1.obj");
    
    sprite2->setScale(4.f);
    sprite2->setTexture("Sprite3DTest/boss.png");
    sprite2->setPosition( Vec2(s.width/2, s.height/2) );
    sprite2->setAnchorPoint(Vec2(0.5, 0.5));
    
    //add to scene
    addChild( sprite2 );
    sprite2->runAction(RepeatForever::create(RotateBy::create(3, -360)));
    
    
    // Make sprite1 touchable
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite3D*>(event->getCurrentTarget());
      
        Rect rect = target->getBoundingBox();        
        if (rect.containsPoint(touch->getLocation()))
        {
            log("sprite3d began... x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
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

Sprite3DTestScene::Sprite3DTestScene()
{
    
}

static int tuple_sort( const std::tuple<ssize_t,Effect3D*,CustomCommand> &tuple1, const std::tuple<ssize_t,Effect3D*,CustomCommand> &tuple2 )
{
    return std::get<0>(tuple1) < std::get<0>(tuple2);
}

EffectSprite3D* EffectSprite3D::createFromObjFileAndTexture(const std::string &objFilePath, const std::string &textureFilePath)
{
    auto sprite = new (std::nothrow) EffectSprite3D();
    if (sprite && sprite->initWithFile(objFilePath))
    {
        sprite->autorelease();
        if(textureFilePath.size() > 0)
            sprite->setTexture(textureFilePath);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

EffectSprite3D* EffectSprite3D::create(const std::string &path)
{
    if (path.length() < 4)
        CCASSERT(false, "improper name specified when creating Sprite3D");
    
    auto sprite = new (std::nothrow) EffectSprite3D();
    if (sprite && sprite->initWithFile(path))
    {
        sprite->autorelease();
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

const std::string Effect3DOutline::_vertSkinnedShaderFile = "Shaders3D/SkinnedOutline.vert";
const std::string Effect3DOutline::_fragSkinnedShaderFile = "Shaders3D/OutLine.frag";
const std::string Effect3DOutline::_keySkinnedInGLProgramCache = "Effect3DLibrary_Outline";
GLProgram* Effect3DOutline::getOrCreateProgram(bool isSkinned /* = false */ )
{
    if(isSkinned)
    {
        auto program = GLProgramCache::getInstance()->getGLProgram(_keySkinnedInGLProgramCache);
        if(program == nullptr)
        {
            program = GLProgram::createWithFilenames(_vertSkinnedShaderFile, _fragSkinnedShaderFile);
            GLProgramCache::getInstance()->addGLProgram(program, _keySkinnedInGLProgramCache);
        }
        return program;
    }
    else
    {
        auto program = GLProgramCache::getInstance()->getGLProgram(_keyInGLProgramCache);
        if(program == nullptr)
        {
            program = GLProgram::createWithFilenames(_vertShaderFile, _fragShaderFile);
            GLProgramCache::getInstance()->addGLProgram(program, _keyInGLProgramCache);
        }
        return program;
    }

}

Effect3DOutline* Effect3DOutline::create()
{
    Effect3DOutline* effect = new (std::nothrow) Effect3DOutline();
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
        if(_glProgramState)
            _glProgramState->setUniformVec3("OutLineColor", _outlineColor);
    }
}

void Effect3DOutline::setOutlineWidth(float width)
{
    if(_outlineWidth != width)
    {
        _outlineWidth = width;
        if(_glProgramState)
            _glProgramState->setUniformFloat("OutlineWidth", _outlineWidth);
    }
}

void Effect3DOutline::setTarget(EffectSprite3D *sprite)
{
    CCASSERT(nullptr != sprite && nullptr != sprite->getMesh(),"Error: Setting a null pointer or a null mesh EffectSprite3D to Effect3D");
    
    if(sprite != _sprite)
    {
        GLProgram* glprogram;
        if(!sprite->getMesh()->getSkin())
            glprogram = GLProgram::createWithFilenames(_vertShaderFile, _fragShaderFile);
        else
            glprogram = GLProgram::createWithFilenames(_vertSkinnedShaderFile, _fragSkinnedShaderFile);

        _glProgramState = GLProgramState::create(glprogram);

        _glProgramState->retain();
        _glProgramState->setUniformVec3("OutLineColor", _outlineColor);
        _glProgramState->setUniformFloat("OutlineWidth", _outlineWidth);
    
        
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

static void MatrixPalleteCallBack( GLProgram* glProgram, Uniform* uniform, int paletteSize, const float* palette)
{
    glUniform4fv( uniform->location, (GLsizei)paletteSize, (const float*)palette );
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
        
        auto skin = _sprite->getMesh()->getSkin();
        if(_sprite && skin)
        {
            auto function = std::bind(MatrixPalleteCallBack, std::placeholders::_1, std::placeholders::_2,
                                      skin->getMatrixPaletteSize(), (float*)skin->getMatrixPalette());
            _glProgramState->setUniformCallback("u_matrixPalette", function);
        }
        
        if(_sprite)
            _glProgramState->apply(transform);
 
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexBuffer());
        glDrawElements(mesh->getPrimitiveType(), (GLsizei)mesh->getIndexCount(), mesh->getIndexFormat(), 0);
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, mesh->getIndexCount());
        
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
    sprite->addEffect(effect, -1);
    effect->setOutlineColor(Vec3(1,0,0));
    effect->setOutlineWidth(0.01f);
    
    Effect3DOutline* effect2 = Effect3DOutline::create();
    sprite->addEffect(effect2, -2);
    effect2->setOutlineWidth(0.02f);
    effect2->setOutlineColor(Vec3(1,1,0));
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
    auto sprite = EffectSprite3D::create(fileName);
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

Sprite3DWithSkinOutlineTest::Sprite3DWithSkinOutlineTest()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(Sprite3DWithSkinOutlineTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto s = Director::getInstance()->getWinSize();
    addNewSpriteWithCoords( Vec2(s.width/2, s.height/2) );
}
std::string Sprite3DWithSkinOutlineTest::title() const
{
    return "Testing Sprite3D for skinned outline";
}
std::string Sprite3DWithSkinOutlineTest::subtitle() const
{
    return "Tap screen to add more sprite3D";
}

void Sprite3DWithSkinOutlineTest::addNewSpriteWithCoords(Vec2 p)
{
    
    std::string fileName = "Sprite3DTest/orc.c3b";
    auto sprite = EffectSprite3D::create(fileName);
    
    Effect3DOutline* effect = Effect3DOutline::create();
    effect->setOutlineColor(Vec3(1,0,0));
    effect->setOutlineWidth(0.01f);
    sprite->addEffect(effect, -1);

    
    Effect3DOutline* effect2 = Effect3DOutline::create();
    effect2->setOutlineWidth(0.02f);
    effect2->setOutlineColor(Vec3(1,1,0));
    sprite->addEffect(effect2, -2);

    
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

void Sprite3DWithSkinOutlineTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
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
        
        if (_elapseTransTime >= Animate3D::getTransitionTime())
        {
            _sprite->stopAction(_hurt);
            _state = State::SWIMMING;
        }
    }
    else if (_state == State::SWIMMING_TO_HURT)
    {
        _elapseTransTime += dt;
        if (_elapseTransTime >= Animate3D::getTransitionTime())
        {
            _sprite->stopAction(_swim);
            _state = State::HURT;
        }
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
        _swim = RepeatForever::create(animate);
        sprite->runAction(_swim);
        
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
    //rerun swim action
    _sprite->runAction(_swim);
    _state = State::HURT_TO_SWIMMING;
    _elapseTransTime = 0.0f;
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
                    _elapseTransTime = 0.0f;
                    _state = State::SWIMMING_TO_HURT;
                    _sprite->stopAction(_hurt);
                    _sprite->runAction(_hurt);
                    auto delay = DelayTime::create(_hurt->getDuration() - Animate3D::getTransitionTime());
                    auto seq = Sequence::create(delay, CallFunc::create(CC_CALLBACK_0(Animate3DTest::renewCallBack, this)), nullptr);
                    seq->setTag(101);
                    _sprite->runAction(seq);
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
Sprite3DReskinTest::Sprite3DReskinTest()
: _sprite(nullptr)
{
    auto s = Director::getInstance()->getWinSize();
    addNewSpriteWithCoords( Vec2(s.width/2, s.height/2) );
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(Sprite3DReskinTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    TTFConfig ttfConfig("fonts/arial.ttf", 20);
    auto label1 = Label::createWithTTF(ttfConfig,"Hair");
    auto item1 = MenuItemLabel::create(label1,CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_switchHair,this) );
    auto label2 = Label::createWithTTF(ttfConfig,"Glasses");
    auto item2 = MenuItemLabel::create(label2,	CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_switchGlasses,this) );
    auto label3 = Label::createWithTTF(ttfConfig,"Coat");
    auto item3 = MenuItemLabel::create(label3,CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_switchCoat,this) );
    auto label4 = Label::createWithTTF(ttfConfig,"Pants");
    auto item4 = MenuItemLabel::create(label4,	CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_switchPants,this) );
    auto label5 = Label::createWithTTF(ttfConfig,"Shoes");
    auto item5 = MenuItemLabel::create(label5,CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_switchShoes,this) );
    item1->setPosition( Vec2(VisibleRect::left().x+50, VisibleRect::bottom().y+item1->getContentSize().height*4 ) );
    item2->setPosition( Vec2(VisibleRect::left().x+50, VisibleRect::bottom().y+item1->getContentSize().height *5 ) );
    item3->setPosition( Vec2(VisibleRect::left().x+50, VisibleRect::bottom().y+item1->getContentSize().height*6 ) );
    item4->setPosition( Vec2(VisibleRect::left().x+50, VisibleRect::bottom().y+item1->getContentSize().height *7 ) );
    item5->setPosition( Vec2(VisibleRect::left().x+50, VisibleRect::bottom().y+item1->getContentSize().height *8 ) );
    auto pMenu1 = CCMenu::create(item1, item2, item3, item4, item5, nullptr);
    pMenu1->setPosition(Vec2(0,0));
    this->addChild(pMenu1, 10);
    
}
void Sprite3DReskinTest::menuCallback_switchHair(Ref* sender)
{
    std::string str = _curSkin[SkinType::HAIR];
    if (str == "Girl_Hair01")
        _curSkin[SkinType::HAIR] = "Girl_Hair02";
    else
        _curSkin[SkinType::HAIR] = "Girl_Hair01";
    applyCurSkin();
}
void Sprite3DReskinTest::menuCallback_switchGlasses(Ref* sender)
{
    std::string str = _curSkin[SkinType::GLASSES];
    if (str == "Girl_Glasses01")
        _curSkin[SkinType::GLASSES] = "";
    else
        _curSkin[SkinType::GLASSES] = "Girl_Glasses01";
    applyCurSkin();
}
void Sprite3DReskinTest::menuCallback_switchCoat(Ref* sender)
{
    std::string str = _curSkin[SkinType::UPPER_BODY];
    if (str == "Girl_UpperBody01")
        _curSkin[SkinType::UPPER_BODY] = "Girl_UpperBody02";
    else
        _curSkin[SkinType::UPPER_BODY] = "Girl_UpperBody01";
    applyCurSkin();
}
void Sprite3DReskinTest::menuCallback_switchPants(Ref* sender)
{
    std::string str = _curSkin[SkinType::PANTS];
    if (str == "Girl_LowerBody01")
        _curSkin[SkinType::PANTS] = "Girl_LowerBody02";
    else
        _curSkin[SkinType::PANTS] = "Girl_LowerBody01";
    applyCurSkin();
}
void Sprite3DReskinTest::menuCallback_switchShoes(Ref* sender)
{
    std::string strShoes = _curSkin[SkinType::SHOES];
    if (strShoes == "Girl_Shoes01")
        _curSkin[SkinType::SHOES] = "Girl_Shoes02";
    else
        _curSkin[SkinType::SHOES] = "Girl_Shoes01";
    applyCurSkin();
}

std::string Sprite3DReskinTest::title() const
{
    return "Testing Sprite3D Reskin";
}
std::string Sprite3DReskinTest::subtitle() const
{
    return "";
}

void Sprite3DReskinTest::addNewSpriteWithCoords(Vec2 p)
{
    std::string fileName = "Sprite3DTest/ReskinGirl.c3b";
    auto sprite = Sprite3D::create(fileName);
    sprite->setScale(4);
    sprite->setRotation3D(Vec3(0,0,0));
    addChild(sprite);
    sprite->setPosition( Vec2( p.x, p.y-60) );
    auto animation = Animation3D::create(fileName);
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        
        sprite->runAction(RepeatForever::create(animate));
    }
    _sprite = sprite;
    
    _curSkin[SkinType::UPPER_BODY] = "Girl_UpperBody01";
    _curSkin[SkinType::PANTS] = "Girl_LowerBody01";
    _curSkin[SkinType::SHOES] = "Girl_Shoes01";
    _curSkin[SkinType::HAIR] = "Girl_Hair01";
    _curSkin[SkinType::FACE] = "Girl_Face01";
    _curSkin[SkinType::HAND] = "Girl_Hand01";
    _curSkin[SkinType::GLASSES] = "";
    applyCurSkin();
}

void Sprite3DReskinTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
}

void Sprite3DReskinTest::applyCurSkin()
{
    for (ssize_t i = 0; i < _sprite->getMeshCount(); i++) {
        auto mesh = _sprite->getMeshByIndex(i);
        bool isVisible = false;
        for (auto& it : _curSkin) {
            if (mesh->getName() == it.second)
            {
                isVisible = true;
                break;
            }
        }
        _sprite->getMeshByIndex(i)->setVisible(isVisible);
    }
}

Sprite3DWithOBBPerfromanceTest::Sprite3DWithOBBPerfromanceTest()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Sprite3DWithOBBPerfromanceTest::onTouchesBegan, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Sprite3DWithOBBPerfromanceTest::onTouchesEnded, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Sprite3DWithOBBPerfromanceTest::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    auto s = Director::getInstance()->getWinSize();
    initDrawBox();
    
    addNewSpriteWithCoords(Vec2(s.width/2, s.height/2));
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", CC_CALLBACK_1(Sprite3DWithOBBPerfromanceTest::delOBBCallback, this));
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", CC_CALLBACK_1(Sprite3DWithOBBPerfromanceTest::addOBBCallback, this));
    increase->setColor(Color3B(0,200,20));
    
    auto menu = Menu::create(decrease, increase, nullptr);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(s.width/2, s.height-65));
    addChild(menu, 1);
    
    TTFConfig ttfCount("fonts/Marker Felt.ttf", 30);
    _labelCubeCount = Label::createWithTTF(ttfCount,"0 cubes");
    _labelCubeCount->setColor(Color3B(0,200,20));
    _labelCubeCount->setPosition(Vec2(s.width/2, s.height-90));
    addChild(_labelCubeCount);
    _hasCollider = false;
    addOBBCallback(nullptr);
    scheduleUpdate();
}
std::string Sprite3DWithOBBPerfromanceTest::title() const
{
    return "OBB Collison Perfromance Test";
}
std::string Sprite3DWithOBBPerfromanceTest::subtitle() const
{
    return "";
}
void Sprite3DWithOBBPerfromanceTest::addNewOBBWithCoords(Vec2 p)
{
    Vec3 extents = Vec3(10, 10, 10);
    AABB aabb(-extents, extents);
    auto obb = OBB(aabb);
    obb._center = Vec3(p.x,p.y,0);
    _obb.push_back(obb);
}

void Sprite3DWithOBBPerfromanceTest::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    for (const auto& touch: touches)
    {
        auto location = touch->getLocationInView();
        auto obbSize = _obb.size();
        if(obbSize)
        {
            _intersetList.clear();
            Ray ray;
            calculateRayByLocationInView(&ray,location);
            for(decltype(obbSize) i = 0; i < obbSize; i++)
            {
                if(ray.intersects(_obb[i]))
                {
                    _intersetList.insert((int)i);
                    return;
                }
            }
        }
    }
}

void Sprite3DWithOBBPerfromanceTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    
}

void Sprite3DWithOBBPerfromanceTest::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    for (const auto& touch: touches)
    {
        auto location = touch->getLocation();       
        auto obbSize = _obb.size();

        for(decltype(obbSize) i = 0; i < obbSize; i++)
        {
            if(_intersetList.find((int)i) != _intersetList.end())
                _obb[i]._center = Vec3(location.x,location.y,0);
        }
    }
}

void Sprite3DWithOBBPerfromanceTest::update(float dt)
{
    char szText[16];
    sprintf(szText,"%lu cubes",_obb.size());
    _labelCubeCount->setString(szText);
    
    if (_drawDebug)
    {
        _drawDebug->clear();
        
        Mat4 mat = _sprite->getNodeToWorldTransform();
        mat.getRightVector(&_obbt._xAxis);
        _obbt._xAxis.normalize();
        
        mat.getUpVector(&_obbt._yAxis);
        _obbt._yAxis.normalize();
        
        mat.getForwardVector(&_obbt._zAxis);
        _obbt._zAxis.normalize();
        
        _obbt._center = _sprite->getPosition3D();
        
        Vec3 corners[8] = {};
        _obbt.getCorners(corners);
        _drawDebug->drawCube(corners, Color4F(0,0,1,1));
    }
    if(_obb.size() > 0)
    {
        _drawOBB->clear();
        auto obbSize = _obb.size();
        for(decltype(obbSize) i =0; i < obbSize; i++)
        {
            Vec3 corners[8] = {};
            _obb[i].getCorners(corners);
            _drawOBB->drawCube(corners, _obbt.intersects(_obb[i])?Color4F(1,0,0,1):Color4F(0,1,0,1));
        }
    }
}

void Sprite3DWithOBBPerfromanceTest::initDrawBox()
{
    _drawOBB = DrawNode3D::create();
    addChild(_drawOBB);
}

void Sprite3DWithOBBPerfromanceTest::addNewSpriteWithCoords(Vec2 p)
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
    }
    
    _moveAction = MoveTo::create(4.f, Vec2(s.width / 5.f, s.height / 2.f));
    _moveAction->retain();
    auto seq = Sequence::create(_moveAction, CallFunc::create(CC_CALLBACK_0(Sprite3DWithOBBPerfromanceTest::reachEndCallBack, this)), nullptr);
    seq->setTag(100);
    sprite->runAction(seq);
    
    AABB aabb = _sprite->getAABB();
    _obbt = OBB(aabb);
    
    _drawDebug = DrawNode3D::create();
    addChild(_drawDebug);
}

void Sprite3DWithOBBPerfromanceTest::reachEndCallBack()
{
    _sprite->stopActionByTag(100);
    auto inverse = (MoveTo*)_moveAction->reverse();
    inverse->retain();
    _moveAction->release();
    _moveAction = inverse;
    auto rot = RotateBy::create(1.0f, Vec3(0.f, 180.f, 0.f));
    auto seq = Sequence::create(rot, _moveAction, CallFunc::create(CC_CALLBACK_0(Sprite3DWithOBBPerfromanceTest::reachEndCallBack, this)), nullptr);
    seq->setTag(100);
    _sprite->runAction(seq);
}

void Sprite3DWithOBBPerfromanceTest::addOBBCallback(Ref* sender)
{
    addOBBWithCount(10);
}

void Sprite3DWithOBBPerfromanceTest::addOBBWithCount(float value)
{
    for(int i = 0; i < value; i++)
    {
        Vec2 randompos = Vec2(CCRANDOM_0_1() * Director::getInstance()->getWinSize().width,CCRANDOM_0_1() * Director::getInstance()->getWinSize().height);
        Vec3 extents = Vec3(10, 10, 10);
        AABB aabb(-extents, extents);
        auto obb = OBB(aabb);
        obb._center = Vec3(randompos.x,randompos.y,0);
        _obb.push_back(obb);
    }
}

void Sprite3DWithOBBPerfromanceTest::delOBBCallback(Ref* sender)
{
    delOBBWithCount(10);
}

void Sprite3DWithOBBPerfromanceTest::delOBBWithCount(float value)
{
    if(_obb.size() >= 10)
    {
        _obb.erase(_obb.begin(),_obb.begin() + value);
        _drawOBB->clear();
    }
    else
        return;
}
void Sprite3DWithOBBPerfromanceTest::unproject(const Mat4& viewProjection, const Size* viewport, Vec3* src, Vec3* dst)
{
    assert(dst);
    
    assert(viewport->width != 0.0f && viewport->height != 0.0f);
    Vec4 screen(src->x / viewport->width, ((viewport->height - src->y)) / viewport->height, src->z, 1.0f);
    
    screen.x = screen.x * 2.0f - 1.0f;
    screen.y = screen.y * 2.0f - 1.0f;
    screen.z = screen.z * 2.0f - 1.0f;
    
    viewProjection.getInversed().transformVector(screen, &screen);
    
    if (screen.w != 0.0f)
    {
        screen.x /= screen.w;
        screen.y /= screen.w;
        screen.z /= screen.w;
    }
    
    dst->set(screen.x, screen.y, screen.z);
}

void Sprite3DWithOBBPerfromanceTest::calculateRayByLocationInView(Ray* ray, const Vec2& location)
{
    auto dir = Director::getInstance();
    auto view = dir->getWinSize();
    auto mat = dir->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    Vec3 src = Vec3(location.x, location.y, -1);
    Vec3 nearPoint;
    unproject(mat, &view, &src, &nearPoint);
    
    src = Vec3(location.x, location.y, 1);
    Vec3 farPoint;
    unproject(mat, &view, &src, &farPoint);
    
    Vec3 direction;
    Vec3::subtract(farPoint, nearPoint, &direction);
    direction.normalize();
    
    ray->_origin = nearPoint;
    ray->_direction = direction;
}

Sprite3DMirrorTest::Sprite3DMirrorTest()
: _sprite(nullptr)
, _mirrorSprite(nullptr)
{
    auto s = Director::getInstance()->getWinSize();
    addNewSpriteWithCoords( Vec2(s.width/2, s.height/2) );
}
std::string Sprite3DMirrorTest::title() const
{
    return "Sprite3D Mirror Test";
}
std::string Sprite3DMirrorTest::subtitle() const
{
    return "";
}

void Sprite3DMirrorTest::addNewSpriteWithCoords(Vec2 p)
{
    std::string fileName = "Sprite3DTest/orc.c3b";
    auto sprite = Sprite3D::create(fileName);
    sprite->setScale(5);
    sprite->setRotation3D(Vec3(0,180,0));
    addChild(sprite);
    sprite->setPosition( Vec2( p.x - 80, p.y) );
    
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
    
    //create mirror Sprite3D
    sprite = Sprite3D::create(fileName);
    sprite->setScale(5);
    sprite->setScaleX(-5);
    sprite->setCullFace(GL_FRONT);
    sprite->setRotation3D(Vec3(0,180,0));
    addChild(sprite);
    sprite->setPosition( Vec2( p.x + 80, p.y) );
    
    //test attach
    sp = Sprite3D::create("Sprite3DTest/axe.c3b");
    sprite->getAttachNode("Bip001 R Hand")->addChild(sp);
    
    animation = Animation3D::create(fileName);
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        
        sprite->runAction(RepeatForever::create(animate));
    }
    _mirrorSprite = sprite;
}
