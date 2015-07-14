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
#include "DrawNode3D.h"

#include <algorithm>
#include "../testResource.h"

USING_NS_CC;

Sprite3DTests::Sprite3DTests()
{
    ADD_TEST_CASE(Sprite3DBasicTest);
    ADD_TEST_CASE(Sprite3DHitTest);
    ADD_TEST_CASE(AsyncLoadSprite3DTest);
    // 3DEffect use custom shader which is not supported on WP8/WinRT yet. 
    ADD_TEST_CASE(Sprite3DEffectTest);
    ADD_TEST_CASE(Sprite3DUVAnimationTest);
    ADD_TEST_CASE(Sprite3DFakeShadowTest);
    ADD_TEST_CASE(Sprite3DBasicToonShaderTest);
    ADD_TEST_CASE(Sprite3DLightMapTest);
    ADD_TEST_CASE(Sprite3DWithSkinTest);
    ADD_TEST_CASE(Sprite3DWithSkinOutlineTest);
    ADD_TEST_CASE(Animate3DTest);
    ADD_TEST_CASE(AttachmentTest);
    ADD_TEST_CASE(Sprite3DReskinTest);
    ADD_TEST_CASE(Sprite3DWithOBBPerformanceTest);
    ADD_TEST_CASE(Sprite3DMirrorTest);
    ADD_TEST_CASE(QuaternionTest);
    ADD_TEST_CASE(Sprite3DEmptyTest);
    ADD_TEST_CASE(UseCaseSprite3D);
    ADD_TEST_CASE(Sprite3DForceDepthTest);
    ADD_TEST_CASE(Sprite3DCubeMapTest);
    ADD_TEST_CASE(NodeAnimationTest);
    ADD_TEST_CASE(Issue9767);
    ADD_TEST_CASE(Sprite3DClippingTest);
    ADD_TEST_CASE(Sprite3DTestMeshLight);
};

//------------------------------------------------------------------
//
// SpriteTestDemo
//
//------------------------------------------------------------------

std::string Sprite3DTestDemo::title() const
{
    return "No title";
}

//------------------------------------------------------------------
//
// Sprite3DForceDepthTest
//
//------------------------------------------------------------------
Sprite3DForceDepthTest::Sprite3DForceDepthTest()
{
    auto orc = cocos2d::Sprite3D::create("Sprite3DTest/orc.c3b");
    orc->setScale(5);
    orc->setNormalizedPosition(Vec2(.5f,.3f));
    orc->setPositionZ(40);
    orc->setRotation3D(Vec3(0,180,0));
    orc->setGlobalZOrder(-1);
    
    addChild(orc);
    
    auto ship = Sprite3D::create("Sprite3DTest/boss1.obj");
    ship->setScale(5);
    ship->setTexture("Sprite3DTest/boss.png");
    ship->setNormalizedPosition(Vec2(.5,.5));
    ship->setRotation3D(Vec3(90,0,0));
    ship->setForceDepthWrite(true);
    
    addChild(ship);
}

std::string Sprite3DForceDepthTest::title() const
{
    return "Force Depth Write Error Test";
}

std::string Sprite3DForceDepthTest::subtitle() const
{
    return "Ship should always appear behind orc";
}

//------------------------------------------------------------------
//
// Sprite3DEmptyTest
//
//------------------------------------------------------------------
Sprite3DEmptyTest::Sprite3DEmptyTest()
{
    auto s = Sprite3D::create();
    s->setNormalizedPosition(Vec2(.5,.5));
    auto l = Label::create();
    l->setString("Test");
    s->addChild(l);
    addChild(s);
}

std::string Sprite3DEmptyTest::title() const
{
    return "Testing Sprite3D Container";
}

std::string Sprite3DEmptyTest::subtitle() const
{
    return "Sprite3D can act as containers for 2D objects";
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
// Sprite3DUVAnimationTest
//
//------------------------------------------------------------------

Sprite3DUVAnimationTest::Sprite3DUVAnimationTest()
{
    //the offset use to translating texture
    _cylinder_texture_offset = 0;
    _shining_duraion = 0;
    Size visibleSize = Director::getInstance()->getVisibleSize();

    //use custom camera
    auto camera = Camera::createPerspective(60, visibleSize.width/visibleSize.height, 0.1f, 200);
    camera->setCameraFlag(CameraFlag::USER1);

    //create cylinder
    auto cylinder = Sprite3D::create("Sprite3DTest/cylinder.c3b");

    //create and set our custom shader
    auto shader =GLProgram::createWithFilenames("Sprite3DTest/cylinder.vert","Sprite3DTest/cylinder.frag");
    _state = GLProgramState::create(shader);
    cylinder->setGLProgramState(_state);

    _state->setUniformFloat("offset",_cylinder_texture_offset);
    _state->setUniformFloat("duration",_shining_duraion);
    //pass mesh's attribute to shader
    long offset = 0;
    auto attributeCount = cylinder->getMesh()->getMeshVertexAttribCount();
    for (auto i = 0; i < attributeCount; i++) {
        auto meshattribute = cylinder->getMesh()->getMeshVertexAttribute(i);
        _state->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
            meshattribute.size,
            meshattribute.type,
            GL_FALSE,
            cylinder->getMesh()->getVertexSizeInBytes(),
            (GLvoid*)offset);
        offset += meshattribute.attribSizeBytes;
    }

    //create the second texture for cylinder
    auto shining_texture = Director::getInstance()->getTextureCache()->addImage("Sprite3DTest/caustics.png");
    Texture2D::TexParams tRepeatParams;//set texture parameters
    tRepeatParams.magFilter = GL_NEAREST;
    tRepeatParams.minFilter = GL_NEAREST;
    tRepeatParams.wrapS = GL_REPEAT;
    tRepeatParams.wrapT = GL_REPEAT;
    shining_texture->setTexParameters(tRepeatParams); 
    //pass the texture sampler to our custom shader
    _state->setUniformTexture("caustics",shining_texture);


    this->addChild(cylinder);
    this->setCameraMask(2); 
    this->addChild(camera);

    //adjust cylinder's position & rotation
    cylinder->setPosition3D(Vec3(0,-15,-50));
    cylinder->setRotation3D(Vec3(-90,0,0));

    //the callback function update cylinder's texcoord
    schedule(schedule_selector(Sprite3DUVAnimationTest::cylinderUpdate));
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                            [this](EventCustom*)
                                                            {
                                                                auto glProgram = _state->getGLProgram();
                                                                glProgram->reset();
                                                                glProgram->initWithFilenames("Sprite3DTest/cylinder.vert", "Sprite3DTest/cylinder.frag");
                                                                glProgram->link();
                                                                glProgram->updateUniforms();
                                                                auto shining_texture = Director::getInstance()->getTextureCache()->addImage("Sprite3DTest/caustics.png");
                                                                Texture2D::TexParams tRepeatParams;//set texture parameters
                                                                tRepeatParams.magFilter = GL_NEAREST;
                                                                tRepeatParams.minFilter = GL_NEAREST;
                                                                tRepeatParams.wrapS = GL_REPEAT;
                                                                tRepeatParams.wrapT = GL_REPEAT;
                                                                shining_texture->setTexParameters(tRepeatParams); 
                                                                //pass the texture sampler to our custom shader
                                                                _state->setUniformTexture("caustics",shining_texture);
                                                                _state->setUniformFloat("offset",_cylinder_texture_offset);
                                                                _state->setUniformFloat("duration",_shining_duraion);
                                                            }
                                                            );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

Sprite3DUVAnimationTest::~Sprite3DUVAnimationTest()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

std::string Sprite3DUVAnimationTest::title() const 
{
    return "Testing UV Animation";
}

std::string Sprite3DUVAnimationTest::subtitle() const 
{
    return "";
}

void Sprite3DUVAnimationTest::cylinderUpdate(float dt)
{
    //callback function to update cylinder's texcoord
    static bool fade_in = true;
    _cylinder_texture_offset += 0.3*dt;
    _cylinder_texture_offset = (_cylinder_texture_offset >1) ? 0 : _cylinder_texture_offset;
    if(fade_in)
    {
        _shining_duraion += 0.5*dt;
        if(_shining_duraion>1) fade_in = false;
    }
    else
    {
        _shining_duraion -= 0.5*dt;
        if(_shining_duraion<0) fade_in = true;
    }

    //pass the result to shader
    _state->setUniformFloat("offset",_cylinder_texture_offset);
    _state->setUniformFloat("duration",_shining_duraion);
}

//------------------------------------------------------------------
//
// Sprite3DFakeShadowTest
//
//------------------------------------------------------------------
Sprite3DFakeShadowTest::Sprite3DFakeShadowTest()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Sprite3DFakeShadowTest::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Sprite3DFakeShadowTest::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Sprite3DFakeShadowTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto layer = Layer::create();
    addChild(layer,0);
    //create Camera
    _camera = Camera::createPerspective(60, visibleSize.width/visibleSize.height, 0.1f, 200);
    _camera->setCameraFlag(CameraFlag::USER1);
    _camera->setPosition3D(Vec3(0,20,25));
    _camera->setRotation3D(Vec3(-60,0,0));

    //create a plane
    _plane = Sprite3D::create("Sprite3DTest/plane.c3t");
    _plane->setRotation3D(Vec3(90,0,0));

    // use custom shader
    auto shader =GLProgram::createWithFilenames("Sprite3DTest/simple_shadow.vert","Sprite3DTest/simple_shadow.frag");
    _state = GLProgramState::create(shader);
    _plane->setGLProgramState(_state);

    //pass mesh's attribute to shader
    long offset = 0; 
    auto attributeCount = _plane->getMesh()->getMeshVertexAttribCount();
    for (auto i = 0; i < attributeCount; i++) {
        auto meshattribute = _plane->getMesh()->getMeshVertexAttribute(i);
        _state->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
            meshattribute.size, 
            meshattribute.type,
            GL_FALSE,
            _plane->getMesh()->getVertexSizeInBytes(),
            (GLvoid*)offset);
        offset += meshattribute.attribSizeBytes;
    } 
    _state->setUniformMat4("u_model_matrix",_plane->getNodeToWorldTransform());

    //create shadow texture
    auto shadowTexture = Director::getInstance()->getTextureCache()->addImage("Sprite3DTest/shadowCircle.png");
    Texture2D::TexParams tRepeatParams;//set texture parameters
    tRepeatParams.magFilter = GL_LINEAR;
    tRepeatParams.minFilter = GL_LINEAR;
    tRepeatParams.wrapS = GL_CLAMP_TO_EDGE;
    tRepeatParams.wrapT = GL_CLAMP_TO_EDGE;
    shadowTexture->setTexParameters(tRepeatParams); 
    _state->setUniformTexture("u_shadowTexture",shadowTexture);
    layer->addChild(_plane); 

    //create the orc
    _orc = Sprite3D::create("Sprite3DTest/orc.c3b");
    _orc->setScale(0.2f);
    _orc->setRotation3D(Vec3(0,180,0));
    _orc->setPosition3D(Vec3(0,0,10));
    _targetPos = _orc->getPosition3D();
    _plane->getGLProgramState()->setUniformVec3("u_target_pos",_orc->getPosition3D());
    layer->addChild(_orc);
    layer->addChild(_camera);
    layer->setCameraMask(2);

    schedule(CC_SCHEDULE_SELECTOR(Sprite3DFakeShadowTest::updateCamera), 0.0f);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                            [this](EventCustom*)
                                                            {
                                                                auto glProgram = _state->getGLProgram();
                                                                glProgram->reset();
                                                                glProgram->initWithFilenames("Sprite3DTest/simple_shadow.vert","Sprite3DTest/simple_shadow.frag");
                                                                glProgram->link();
                                                                glProgram->updateUniforms();
                                                                
                                                                _state->setUniformMat4("u_model_matrix",_plane->getNodeToWorldTransform());
                                                                
                                                                //create shadow texture
                                                                auto shadowTexture = Director::getInstance()->getTextureCache()->addImage("Sprite3DTest/shadowCircle.png");
                                                                Texture2D::TexParams tRepeatParams;//set texture parameters
                                                                tRepeatParams.magFilter = GL_LINEAR;
                                                                tRepeatParams.minFilter = GL_LINEAR;
                                                                tRepeatParams.wrapS = GL_CLAMP_TO_EDGE;
                                                                tRepeatParams.wrapT = GL_CLAMP_TO_EDGE;
                                                                shadowTexture->setTexParameters(tRepeatParams); 
                                                                _state->setUniformTexture("u_shadowTexture",shadowTexture);
                                                            }
                                                            );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

Sprite3DFakeShadowTest::~Sprite3DFakeShadowTest()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

std::string Sprite3DFakeShadowTest::title() const 
{
    return "fake shadow effect";
}

std::string Sprite3DFakeShadowTest::subtitle() const 
{
    return "touch the screen to move around";
}

void Sprite3DFakeShadowTest::Move(cocos2d::Ref* sender,int value)
{
    _orc->setPositionX(_orc->getPositionX()+value);

}

void Sprite3DFakeShadowTest::updateCamera(float fDelta)
{
    updateState(fDelta);
    if(isState(_curState,State_Move))
    {
        move3D(fDelta);
        if(isState(_curState,State_Rotate))
        {
            Vec3 curPos = _orc->getPosition3D();

            Vec3 newFaceDir = _targetPos - curPos;
            newFaceDir.y = 0;
            newFaceDir.normalize();
            Vec3 up;
            _orc->getNodeToWorldTransform().getUpVector(&up);
            up.normalize();
            Vec3 right;
            Vec3::cross(-newFaceDir,up,&right);
            right.normalize();
            Vec3 pos = Vec3(0,0,0);
            Mat4 mat;
            mat.m[0] = right.x;
            mat.m[1] = right.y;
            mat.m[2] = right.z;
            mat.m[3] = 0.0f;

            mat.m[4] = up.x;
            mat.m[5] = up.y;
            mat.m[6] = up.z;
            mat.m[7] = 0.0f;

            mat.m[8]  = newFaceDir.x;
            mat.m[9]  = newFaceDir.y;
            mat.m[10] = newFaceDir.z;
            mat.m[11] = 0.0f;

            mat.m[12] = pos.x;
            mat.m[13] = pos.y;
            mat.m[14] = pos.z;
            mat.m[15] = 1.0f;
            _orc->setAdditionalTransform(&mat);
        }
    }
}


void Sprite3DFakeShadowTest::move3D(float elapsedTime)
{
    Vec3 curPos=  _orc->getPosition3D();
    Vec3 newFaceDir = _targetPos - curPos;
    newFaceDir.y = 0.0f;
    newFaceDir.normalize();
    Vec3 offset = newFaceDir * 25.0f * elapsedTime;
    curPos+=offset;
    _orc->setPosition3D(curPos);
    offset.x=offset.x;
    offset.z=offset.z;
    //pass the newest orc position
    _plane->getGLProgramState()->setUniformVec3("u_target_pos",_orc->getPosition3D());
}

void Sprite3DFakeShadowTest::updateState(float elapsedTime)
{
    Vec3 curPos=  _orc->getPosition3D();
    Vec3 curFaceDir;
    _orc->getNodeToWorldTransform().getForwardVector(&curFaceDir);
    curFaceDir=-curFaceDir;
    curFaceDir.normalize();
    Vec3 newFaceDir = _targetPos - curPos;
    newFaceDir.y = 0.0f;
    newFaceDir.normalize();
    float cosAngle = std::fabs(Vec3::dot(curFaceDir,newFaceDir) - 1.0f);
    float dist = curPos.distanceSquared(_targetPos);
    if(dist<=4.0f)
    {
        if(cosAngle<=0.01f)
            _curState = State_Idle;
        else
            _curState = State_Rotate;
    }
    else
    {
        if(cosAngle>0.01f)
            _curState = State_Rotate | State_Move;
        else
            _curState = State_Move;
    }
}

bool Sprite3DFakeShadowTest::isState(unsigned int state,unsigned int bit) const
{
    return (state & bit) == bit;
}

void Sprite3DFakeShadowTest::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event *event)
{

}

void Sprite3DFakeShadowTest::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event *event)
{
}

void Sprite3DFakeShadowTest::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event *event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        auto location = touch->getLocationInView();
        if(_camera)
        {
            if(_orc )
            {
                Vec3 nearP(location.x, location.y, -1.0f), farP(location.x, location.y, 1.0f);

                auto size = Director::getInstance()->getWinSize();
                nearP = _camera->unproject(nearP);
                farP = _camera->unproject(farP);
                Vec3 dir(farP - nearP);
                float dist=0.0f;
                float ndd = Vec3::dot(Vec3(0,1,0),dir);
                if(ndd == 0)
                    dist=0.0f;
                float ndo = Vec3::dot(Vec3(0,1,0),nearP);
                dist= (0 - ndo) / ndd;
                Vec3 p =   nearP + dist *  dir;

                if( p.x > 100)
                    p.x = 100;
                if( p.x < -100)
                    p.x = -100;
                if( p.z > 100)
                    p.z = 100;
                if( p.z < -100)
                    p.z = -100;

                _targetPos=p;
            }
        }
    }
}

//------------------------------------------------------------------
//
// Sprite3DBasicToonShaderTest
//
//------------------------------------------------------------------
Sprite3DBasicToonShaderTest::Sprite3DBasicToonShaderTest()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto _camera = Camera::createPerspective(60, visibleSize.width/visibleSize.height, 0.1f, 200);
    _camera->setCameraFlag(CameraFlag::USER1);
    // create a teapot
    auto teapot = Sprite3D::create("Sprite3DTest/teapot.c3b"); 
    //create and set our custom shader 
    auto shader =GLProgram::createWithFilenames("Sprite3DTest/toon.vert","Sprite3DTest/toon.frag");
    _state = GLProgramState::create(shader);
    teapot->setGLProgramState(_state);
    teapot->setPosition3D(Vec3(0,-5,-20));
    teapot->setRotation3D(Vec3(-90,180,0)); 
    auto rotate_action = RotateBy::create(1.5,Vec3(0,30,0));
    teapot->runAction(RepeatForever::create(rotate_action)); 
    //pass mesh's attribute to shader
    long offset = 0;
    auto attributeCount = teapot->getMesh()->getMeshVertexAttribCount();
    for (auto i = 0; i < attributeCount; i++) {
        auto meshattribute = teapot->getMesh()->getMeshVertexAttribute(i);
        _state->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
            meshattribute.size,
            meshattribute.type,
            GL_FALSE,
            teapot->getMesh()->getVertexSizeInBytes(),
            (GLvoid*)offset);
        offset += meshattribute.attribSizeBytes;
    }
    addChild(teapot);
    addChild(_camera);
    setCameraMask(2);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                            [this](EventCustom*)
                                                            {
                                                                auto glProgram = _state->getGLProgram();
                                                                glProgram->reset();
                                                                glProgram->initWithFilenames("Sprite3DTest/toon.vert","Sprite3DTest/toon.frag");
                                                                glProgram->link();
                                                                glProgram->updateUniforms();
                                                            }
                                                            );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

Sprite3DBasicToonShaderTest::~Sprite3DBasicToonShaderTest()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

std::string Sprite3DBasicToonShaderTest::title() const 
{
    return "basic toon shader test";
}

std::string Sprite3DBasicToonShaderTest::subtitle() const 
{
    return " ";
}

//------------------------------------------------------------------
//
// Sprite3DLightMapTest 
//
//------------------------------------------------------------------
Sprite3DLightMapTest::Sprite3DLightMapTest()
{
    //the assets are from the OpenVR demo
    //get the visible size.
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _camera = Camera::createPerspective(60, visibleSize.width/visibleSize.height, 0.1f, 200);
    _camera->setCameraFlag(CameraFlag::USER1);
    _camera->setPosition3D(Vec3(0,25,15));
    _camera->setRotation3D(Vec3(-35,0,0));
    auto LightMapScene = Sprite3D::create("Sprite3DTest/LightMapScene.c3b"); 
    LightMapScene->setScale(0.1f); 
    addChild(LightMapScene);
    addChild(_camera); 
    setCameraMask(2); 

    //add a point light
    auto light = PointLight::create(Vec3(35,75,-20.5),Color3B(255,255,255),150);
    addChild(light);
    //set the ambient light 
    auto ambient = AmbientLight::create(Color3B(55,55,55));
    addChild(ambient);

    //create a listener
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(Sprite3DLightMapTest::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
Sprite3DLightMapTest::~Sprite3DLightMapTest()
{
    
}
std::string Sprite3DLightMapTest::title() const
{
    return "light map test";
}

std::string Sprite3DLightMapTest::subtitle() const 
{
    return "drag the screen to move around";
}

void Sprite3DLightMapTest::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    if(touches.size()==1)
    {
        float delta = Director::getInstance()->getDeltaTime();
        auto touch = touches[0];
        auto location = touch->getLocation();
        auto PreviousLocation = touch->getPreviousLocation();
        Point newPos = PreviousLocation - location;

        Vec3 cameraDir;
        Vec3 cameraRightDir;
        _camera->getNodeToWorldTransform().getForwardVector(&cameraDir);
        cameraDir.normalize();
        cameraDir.y=0;
        _camera->getNodeToWorldTransform().getRightVector(&cameraRightDir);
        cameraRightDir.normalize();
        cameraRightDir.y=0;
        Vec3 cameraPos=  _camera->getPosition3D();
        cameraPos+=cameraDir*newPos.y*delta;  
        cameraPos+=cameraRightDir*newPos.x*delta;
        _camera->setPosition3D(cameraPos);      
    }
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
: _outlineColor(1, 1, 1)
, _outlineWidth(1.0f)
, _sprite(nullptr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
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
            _glProgramState->setUniformVec4v("u_matrixPalette", skin->getMatrixPaletteSize(), skin->getMatrixPalette());
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

        // Since cocos2d-x v3.7, users should avoid calling GL directly because it will break the internal GL state
        // But if users must call GL directly, they should update the state manually,
        RenderState::StateBlock::_defaultState->setDepthTest(false);
        RenderState::StateBlock::_defaultState->setCullFaceSide(RenderState::CULL_FACE_SIDE_BACK);
        RenderState::StateBlock::_defaultState->setCullFace(false);
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
        _command.init(_globalZOrder, transform, flags);
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

AsyncLoadSprite3DTest::AsyncLoadSprite3DTest()
{
    _paths.push_back("Sprite3DTest/boss.obj");
    _paths.push_back("Sprite3DTest/girl.c3b");
    _paths.push_back("Sprite3DTest/orc.c3b");
    _paths.push_back("Sprite3DTest/ReskinGirl.c3b");
    _paths.push_back("Sprite3DTest/axe.c3b");
    
    TTFConfig ttfConfig("fonts/arial.ttf", 15);
    auto label1 = Label::createWithTTF(ttfConfig,"AsyncLoad Sprite3D");
    auto item1 = MenuItemLabel::create(label1,CC_CALLBACK_1(AsyncLoadSprite3DTest::menuCallback_asyncLoadSprite,this) );
    
    auto s = Director::getInstance()->getWinSize();
    item1->setPosition( s.width * .5f, s.height * .8f);
    
    auto pMenu1 = CCMenu::create(item1, nullptr);
    pMenu1->setPosition(Vec2(0,0));
    this->addChild(pMenu1, 10);
    
    auto node = Node::create();
    node->setTag(101);
    this->addChild(node);
    
    menuCallback_asyncLoadSprite(nullptr);
}

AsyncLoadSprite3DTest::~AsyncLoadSprite3DTest()
{
}

std::string AsyncLoadSprite3DTest::title() const
{
    return "Testing Sprite3D::createAsync";
}
std::string AsyncLoadSprite3DTest::subtitle() const
{
    return "";
}

void AsyncLoadSprite3DTest::menuCallback_asyncLoadSprite(Ref* sender)
{
    //Note that you must stop the tasks before leaving the scene.
    AsyncTaskPool::getInstance()->stopTasks(AsyncTaskPool::TaskType::TASK_IO);
    
    auto node = getChildByTag(101);
    node->removeAllChildren(); //remove all loaded sprite
    
    //remove cache data
    Sprite3DCache::getInstance()->removeAllSprite3DData();
    long index = 0;
    for (const auto& path : _paths) {
        Sprite3D::createAsync(path, CC_CALLBACK_2(AsyncLoadSprite3DTest::asyncLoad_Callback, this), (void*)index++);
    }
}

void AsyncLoadSprite3DTest::asyncLoad_Callback(Sprite3D* sprite, void* param)
{
    long index = (long)param;
    auto node = getChildByTag(101);
    auto s = Director::getInstance()->getWinSize();
    float width = s.width / _paths.size();
    Vec2 point(width * (0.5f + index), s.height / 2.f);
    sprite->setPosition(point);
    node->addChild(sprite);
}


Sprite3DWithSkinTest::Sprite3DWithSkinTest()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(Sprite3DWithSkinTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // swich animation quality. In fact, you can set the sprite3d out of frustum to Animate3DQuality::QUALITY_NONE, it can save a lot of cpu time
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(15);
    _animateQuality = (int)Animate3DQuality::QUALITY_LOW;
    _menuItem = MenuItemFont::create(getAnimationQualityMessage(), CC_CALLBACK_1(Sprite3DWithSkinTest::switchAnimationQualityCallback,this));
    _menuItem->setColor(Color3B(0,200,20));
    auto menu = Menu::create(_menuItem,NULL);
    menu->setPosition(Vec2::ZERO);
    _menuItem->setPosition(VisibleRect::left().x + 50, VisibleRect::top().y -70);
    addChild(menu, 1);

    _sprits.clear();
    
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
    sprite->setPosition( Vec2( p.x, p.y) );
    addChild(sprite);
    _sprits.push_back(sprite);
    
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
        animate->setTag(110);
        animate->setQuality((Animate3DQuality)_animateQuality);
        auto repeate = RepeatForever::create(animate);
        repeate->setTag(110);
        sprite->runAction(repeate);
    }
}

std::string Sprite3DWithSkinTest::getAnimationQualityMessage() const
{
    if (_animateQuality == (int)Animate3DQuality::QUALITY_NONE)
        return "None Quality";
    else if (_animateQuality == (int)Animate3DQuality::QUALITY_LOW)
        return "Low Quality";
    else if (_animateQuality == (int)Animate3DQuality::QUALITY_HIGH)
        return "High Quality";
    
    return "";
}

void Sprite3DWithSkinTest::switchAnimationQualityCallback(Ref* sender)
{
    ++_animateQuality;
    if (_animateQuality > (int)Animate3DQuality::QUALITY_HIGH)
        _animateQuality = (int)Animate3DQuality::QUALITY_NONE;
    
    _menuItem->setString(getAnimationQualityMessage());
    
    for (auto iter: _sprits)
    {
        RepeatForever* repAction = dynamic_cast<RepeatForever*>(iter->getActionByTag(110));
        Animate3D* animate3D = dynamic_cast<Animate3D*>(repAction->getInnerAction());
        animate3D->setQuality((Animate3DQuality)_animateQuality);
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
: _sprite(nullptr)
, _swim(nullptr)
, _hurt(nullptr)
, _elapseTransTime(0.f)
, _moveAction(nullptr)
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
    auto s = Director::getInstance()->getWinSize();
    _sprite->stopActionByTag(100);
    auto inverse = MoveTo::create(4.f, Vec2(s.width - _sprite->getPositionX(), s.height / 2.f));
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
    auto item1 = MenuItemLabel::create(label1,CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin,this) );
    auto label2 = Label::createWithTTF(ttfConfig,"Glasses");
    auto item2 = MenuItemLabel::create(label2,	CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin,this) );
    auto label3 = Label::createWithTTF(ttfConfig,"Coat");
    auto item3 = MenuItemLabel::create(label3,CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin,this) );
    auto label4 = Label::createWithTTF(ttfConfig,"Pants");
    auto item4 = MenuItemLabel::create(label4,	CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin,this) );
    auto label5 = Label::createWithTTF(ttfConfig,"Shoes");
    auto item5 = MenuItemLabel::create(label5,CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin,this) );
    item1->setPosition( Vec2(VisibleRect::left().x+50, VisibleRect::bottom().y+item1->getContentSize().height*4 ) );
    item2->setPosition( Vec2(VisibleRect::left().x+50, VisibleRect::bottom().y+item1->getContentSize().height *5 ) );
    item3->setPosition( Vec2(VisibleRect::left().x+50, VisibleRect::bottom().y+item1->getContentSize().height*6 ) );
    item4->setPosition( Vec2(VisibleRect::left().x+50, VisibleRect::bottom().y+item1->getContentSize().height *7 ) );
    item5->setPosition( Vec2(VisibleRect::left().x+50, VisibleRect::bottom().y+item1->getContentSize().height *8 ) );
    item1->setUserData((void*)SkinType::HAIR);
    item2->setUserData((void*)SkinType::GLASSES);
    item3->setUserData((void*)SkinType::UPPER_BODY);
    item4->setUserData((void*)SkinType::PANTS);
    item5->setUserData((void*)SkinType::SHOES);
    auto pMenu1 = CCMenu::create(item1, item2, item3, item4, item5, nullptr);
    pMenu1->setPosition(Vec2(0,0));
    this->addChild(pMenu1, 10);
    
}
void Sprite3DReskinTest::menuCallback_reSkin(Ref* sender)
{
    long index = (long)(((MenuItemLabel*)sender)->getUserData());
    if (index < (int)SkinType::MAX_TYPE)
    {
        _curSkin[index] = (_curSkin[index] + 1) % _skins[index].size();
        applyCurSkin();
    }
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
    
    auto& body = _skins[(int)SkinType::UPPER_BODY];
    body.push_back("Girl_UpperBody01");
    body.push_back("Girl_UpperBody02");
    
    auto& pants = _skins[(int)SkinType::PANTS];
    pants.push_back("Girl_LowerBody01");
    pants.push_back("Girl_LowerBody02");
    
    auto& shoes = _skins[(int)SkinType::SHOES];
    shoes.push_back("Girl_Shoes01");
    shoes.push_back("Girl_Shoes02");
    
    auto& hair = _skins[(int)SkinType::HAIR];
    hair.push_back("Girl_Hair01");
    hair.push_back("Girl_Hair02");
    
    auto& face = _skins[(int)SkinType::FACE];
    face.push_back("Girl_Face01");
    face.push_back("Girl_Face02");
    
    auto& hand = _skins[(int)SkinType::HAND];
    hand.push_back("Girl_Hand01");
    hand.push_back("Girl_Hand02");
    
    auto& glasses = _skins[(int)SkinType::GLASSES];
    glasses.push_back("");
    glasses.push_back("Girl_Glasses01");
    
    memset(_curSkin, 0, (int)SkinType::MAX_TYPE * sizeof(int));
    
    applyCurSkin();
}

void Sprite3DReskinTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
}

void Sprite3DReskinTest::applyCurSkin()
{
    for (ssize_t i = 0; i < _sprite->getMeshCount(); i++) {
        auto mesh = _sprite->getMeshByIndex(static_cast<int>(i));
        bool isVisible = false;
        for (int j = 0; j < (int)SkinType::MAX_TYPE; j++) {
            if (mesh->getName() == _skins[j].at(_curSkin[j]))
            {
                isVisible = true;
                break;
            }
        }
        _sprite->getMeshByIndex(static_cast<int>(i))->setVisible(isVisible);
    }
}

Sprite3DWithOBBPerformanceTest::Sprite3DWithOBBPerformanceTest()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Sprite3DWithOBBPerformanceTest::onTouchesBegan, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Sprite3DWithOBBPerformanceTest::onTouchesEnded, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Sprite3DWithOBBPerformanceTest::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    auto s = Director::getInstance()->getWinSize();
    initDrawBox();
    
    addNewSpriteWithCoords(Vec2(s.width/2, s.height/2));
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", CC_CALLBACK_1(Sprite3DWithOBBPerformanceTest::delOBBCallback, this));
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", CC_CALLBACK_1(Sprite3DWithOBBPerformanceTest::addOBBCallback, this));
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
std::string Sprite3DWithOBBPerformanceTest::title() const
{
    return "OBB Collison Performance Test";
}
std::string Sprite3DWithOBBPerformanceTest::subtitle() const
{
    return "";
}
void Sprite3DWithOBBPerformanceTest::addNewOBBWithCoords(Vec2 p)
{
    Vec3 extents = Vec3(10, 10, 10);
    AABB aabb(-extents, extents);
    auto obb = OBB(aabb);
    obb._center = Vec3(p.x,p.y,0);
    _obb.push_back(obb);
}

void Sprite3DWithOBBPerformanceTest::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
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

void Sprite3DWithOBBPerformanceTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    
}

void Sprite3DWithOBBPerformanceTest::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
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

void Sprite3DWithOBBPerformanceTest::update(float dt)
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

void Sprite3DWithOBBPerformanceTest::initDrawBox()
{
    _drawOBB = DrawNode3D::create();
    addChild(_drawOBB);
}

void Sprite3DWithOBBPerformanceTest::addNewSpriteWithCoords(Vec2 p)
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
    auto seq = Sequence::create(_moveAction, CallFunc::create(CC_CALLBACK_0(Sprite3DWithOBBPerformanceTest::reachEndCallBack, this)), nullptr);
    seq->setTag(100);
    sprite->runAction(seq);
    
    AABB aabb = _sprite->getAABB();
    _obbt = OBB(aabb);
    
    _drawDebug = DrawNode3D::create();
    addChild(_drawDebug);
}

void Sprite3DWithOBBPerformanceTest::reachEndCallBack()
{
    auto s = Director::getInstance()->getWinSize();
    _sprite->stopActionByTag(100);
    auto inverse = MoveTo::create(4.f, Vec2(s.width - _sprite->getPositionX(), s.height / 2.f));
    inverse->retain();
    _moveAction->release();
    _moveAction = inverse;
    auto rot = RotateBy::create(1.0f, Vec3(0.f, 180.f, 0.f));
    auto seq = Sequence::create(rot, _moveAction, CallFunc::create(CC_CALLBACK_0(Sprite3DWithOBBPerformanceTest::reachEndCallBack, this)), nullptr);
    seq->setTag(100);
    _sprite->runAction(seq);
}

void Sprite3DWithOBBPerformanceTest::addOBBCallback(Ref* sender)
{
    addOBBWithCount(10);
}

void Sprite3DWithOBBPerformanceTest::addOBBWithCount(float value)
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

void Sprite3DWithOBBPerformanceTest::delOBBCallback(Ref* sender)
{
    delOBBWithCount(10);
}

void Sprite3DWithOBBPerformanceTest::delOBBWithCount(float value)
{
    if(_obb.size() >= 10)
    {
        _obb.erase(_obb.begin(),_obb.begin() + value);
        _drawOBB->clear();
    }
    else
        return;
}
void Sprite3DWithOBBPerformanceTest::unproject(const Mat4& viewProjection, const Size* viewport, Vec3* src, Vec3* dst)
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

void Sprite3DWithOBBPerformanceTest::calculateRayByLocationInView(Ray* ray, const Vec2& location)
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

QuaternionTest::QuaternionTest()
: _arcSpeed(CC_DEGREES_TO_RADIANS(90))
, _radius(100.f)
, _accAngle(0.f)
{
    auto s = Director::getInstance()->getWinSize();
    addNewSpriteWithCoords(Vec2(s.width / 2.f, s.height / 2.f));
    scheduleUpdate();
}
std::string QuaternionTest::title() const
{
    return "Test Rotation With Quaternion";
}
std::string QuaternionTest::subtitle() const
{
    return "";
}

void QuaternionTest::addNewSpriteWithCoords(Vec2 p)
{
    std::string fileName = "Sprite3DTest/tortoise.c3b";
    auto sprite = Sprite3D::create(fileName);
    sprite->setScale(0.1f);
    auto s = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(s.width / 2.f + _radius * cosf(_accAngle), s.height / 2.f + _radius * sinf(_accAngle)));
    addChild(sprite);
    _sprite = sprite;
    auto animation = Animation3D::create(fileName);
    if (animation)
    {
        auto animate = Animate3D::create(animation, 0.f, 1.933f);
        sprite->runAction(RepeatForever::create(animate));
    }
}

void QuaternionTest::update(float delta)
{
    _accAngle += delta * _arcSpeed;
    const float pi = (float)M_PI;
    if (_accAngle >= 2 * pi)
        _accAngle -= 2 * pi;
    
    auto s = Director::getInstance()->getWinSize();
    _sprite->setPosition(Vec2(s.width / 2.f + _radius * cosf(_accAngle), s.height / 2.f + _radius * sinf(_accAngle)));
    
    Quaternion quat;
    Quaternion::createFromAxisAngle(Vec3(0.f, 0.f, 1.f), _accAngle - pi * 0.5f, &quat);
    _sprite->setRotationQuat(quat);
}

UseCaseSprite3D::UseCaseSprite3D()
: _caseIdx(0)
{
    auto s = Director::getInstance()->getWinSize();
    
    _useCaseTitles[0] = "transparent 3d sprite and 2d sprite";
    _useCaseTitles[1] = "ui - 3d - ui";
    
    auto itemPrev = MenuItemImage::create("Images/b1.png", "Images/b2.png",
                                          [&](Ref *sender) {
                                              _caseIdx--;
                                              if (_caseIdx < 0)
                                                  _caseIdx = (int)USECASE::MAX_CASE_NUM - 1;
                                              this->switchCase();
                                          });
    
    auto itemNext = MenuItemImage::create("Images/f1.png", "Images/f2.png",
                                          [&](Ref *sender) {
                                              _caseIdx++;
                                              if (_caseIdx >= (int)USECASE::MAX_CASE_NUM)
                                                  _caseIdx = 0;
                                              this->switchCase();
                                          });
    
    auto menu = Menu::create(itemPrev, itemNext, nullptr);
    menu->alignItemsHorizontally();
    menu->setScale(0.5);
    menu->setAnchorPoint(Vec2(0,0));
    menu->setPosition(Vec2(s.width/2,70));
    
    _label = Label::create();
    _label->setPosition(s.width * 0.5f, s.height * 0.8f);
    addChild(_label);
    
    addChild(menu);
    
    //setup camera
    auto camera = Camera::createPerspective(40, s.width / s.height, 0.01f, 1000.f);
    camera->setCameraFlag(CameraFlag::USER1);
    camera->setPosition3D(Vec3(0.f, 30.f, 100.f));
    camera->lookAt(Vec3(0.f, 0.f, 0.f));
    addChild(camera);
    
    switchCase();
}

std::string UseCaseSprite3D::title() const
{
    return "Use Case For 2D + 3D";
}

std::string UseCaseSprite3D::subtitle() const
{
    return "";
}

void UseCaseSprite3D::switchCase()
{
    removeChildByTag(101);
    
    auto s = Director::getInstance()->getWinSize();
    _label->setString(_useCaseTitles[_caseIdx]);
    if (_caseIdx == 0) // use case 1, 3d transparent sprite + 2d sprite
    {
        std::string filename = "Sprite3DTest/girl.c3b";
        auto sprite = Sprite3D::create(filename);
        sprite->setScale(0.15f);
        auto animation = Animation3D::create(filename);
        if (animation)
        {
            auto animate = Animate3D::create(animation);
            
            sprite->runAction(RepeatForever::create(animate));
        }
        
        auto circleBack = Sprite3D::create();
        auto circle = Sprite::create("Sprite3DTest/circle.png");
        circleBack->setScale(0.5f);
        circleBack->addChild(circle);
        circle->runAction(RepeatForever::create(RotateBy::create(3, Vec3(0.f, 0.f, 360.f))));

        circleBack->setRotation3D(Vec3(90, 90, 0));
        
        auto pos = sprite->getPosition3D();
        circleBack->setPosition3D(Vec3(pos.x, pos.y, pos.z - 1));
        
        sprite->setOpacity(250);
        sprite->setCameraMask(2);
        circleBack->setCameraMask(2);
        sprite->setTag(3);
        circleBack->setTag(2);
        
        auto node = Node::create();
        node->addChild(sprite);
        node->addChild(circleBack);
        node->setTag(101);
        addChild(node);
        
        scheduleUpdate();
        update(0.f);
    }
    else if (_caseIdx == 1) // use case 2, ui - 3d - ui, last ui should on the top
    {
        auto layer = LayerColor::create(Color4B(0, 0, 100, 255), s.width / 2.f, s.height / 2.f);
        layer->setPosition(s.width * 0.25f, s.height * 0.25f);
        layer->setGlobalZOrder(-1);
        addChild(layer);
        
        std::string filename = "Sprite3DTest/girl.c3b";
        auto sprite = Sprite3D::create(filename);
        sprite->setScale(0.5f);
        auto animation = Animation3D::create(filename);
        if (animation)
        {
            auto animate = Animate3D::create(animation);
            sprite->runAction(RepeatForever::create(animate));
        }
        sprite->setPosition(s.width * 0.25f, s.height * 0.125f);
        layer->addChild(sprite);
        
        TTFConfig ttfConfig("fonts/arial.ttf", 15);
        auto label1 = Label::createWithTTF(ttfConfig,"Message");
        auto item1 = MenuItemLabel::create(label1,CC_CALLBACK_1(UseCaseSprite3D::menuCallback_Message,this) );
        auto label2 = Label::createWithTTF(ttfConfig,"Message");
        auto item2 = MenuItemLabel::create(label2,	CC_CALLBACK_1(UseCaseSprite3D::menuCallback_Message,this) );
        
        item1->setPosition( Vec2(s.width * 0.5f - item1->getContentSize().width * 0.5f, s.height * 0.5f - item1->getContentSize().height ) );
        item2->setPosition( Vec2(s.width * 0.5f - item1->getContentSize().width * 0.5f, s.height * 0.5f - item1->getContentSize().height * 2.f ) );
        
        auto pMenu1 = CCMenu::create(item1, item2, nullptr);
        pMenu1->setPosition(Vec2(0,0));
        layer->addChild(pMenu1);
        
        layer->setTag(101);
    }
}

void UseCaseSprite3D::menuCallback_Message(Ref* sender)
{
    auto layer = getChildByTag(101);
    auto message = layer->getChildByTag(102); // message layer
    if (message)
        layer->removeChild(message);
    else
    {
        // create a new message layer on the top
        auto s = layer->getContentSize();
        auto messagelayer = LayerColor::create(Color4B(100, 100, 0, 255));
        messagelayer->setContentSize(Size(s.width * 0.5f, s.height * 0.5f));
        messagelayer->setPosition(Vec2(s.width * 0.25f, s.height * 0.25f));
        auto label = Label::create();
        label->setString("This Message Layer \n Should Be On Top");
        label->setPosition(Vec2(s.width * 0.25f, s.height * 0.25f));
        messagelayer->addChild(label);
        messagelayer->setTag(102);
        layer->addChild(messagelayer);
    }
}

void UseCaseSprite3D::update(float delta)
{
    if (_caseIdx == 0)
    {
        static float accAngle = 0.f;
        accAngle += delta * CC_DEGREES_TO_RADIANS(60);
        
        float radius = 30.f;
        float x = cosf(accAngle) * radius, z = sinf(accAngle) * radius;
        
        auto node = getChildByTag(101);
        auto sprite3d = node->getChildByTag(3);
        auto circle = node->getChildByTag(2);
        
        sprite3d->setPositionX(x);
        sprite3d->setPositionZ(z);
        circle->setPositionX(x);
        circle->setPositionZ(z);
    }
}

/////////////////////////////////////////////
// Node Frame Animation
NodeAnimationTest::NodeAnimationTest()
:_vectorIndex(0)
{
    auto s = Director::getInstance()->getWinSize();
    
    auto itemPrev = MenuItemImage::create("Images/b1.png", "Images/b2.png",
                                          [&](Ref *sender) {
                                              _sprites[_vectorIndex]->setVisible(false);
                                              
                                              int tIndex = _vectorIndex - 1;
                                              if(tIndex < 0)
                                                  _vectorIndex = (int)_sprites.size()-1;
                                              else
                                                  _vectorIndex--;
                                              
                                              _sprites[_vectorIndex]->setVisible(true);
                                          });
    
    auto itemNext = MenuItemImage::create("Images/f1.png", "Images/f2.png",
                                          [&](Ref *sender) {
                                              _sprites[_vectorIndex]->setVisible(false);
                                              
                                              int tIndex = _vectorIndex + 1;
                                              if(tIndex >= _sprites.size())
                                                  _vectorIndex = 0;
                                              else
                                                  _vectorIndex++;
                                              
                                              _sprites[_vectorIndex]->setVisible(true);
                                          });
    
    auto menu = Menu::create(itemPrev, itemNext, nullptr);
    menu->alignItemsHorizontally();
    menu->setScale(0.5);
    menu->setAnchorPoint(Vec2(0,0));
    menu->setPosition(Vec2(s.width/2,70));
    addChild(menu);
    
    addNewSpriteWithCoords(Vec2(s.width / 2.f, s.height / 2.f));
}
std::string NodeAnimationTest::title() const
{
    return "Node Animation Test";
}
std::string NodeAnimationTest::subtitle() const
{
    return "Jumping animation";
}

void NodeAnimationTest::addNewSpriteWithCoords(Vec2 p)
{
    auto s = Director::getInstance()->getWinSize();
    
    // add jumping ball
    std::string fileName = "Sprite3DTest/ball.c3b";
    auto sprite = Sprite3D::create(fileName);
    sprite->setRotation3D(Vec3(0, 180, 0));
    sprite->setScale(3);
    sprite->setPosition(Vec2(s.width / 2.f, s.height / 3.f));
    sprite->setTexture("Sprite3DTest/teapot.png");
    
    auto light1 = PointLight::create(Vec3(s.width * 0.2f, s.height * 0.8f, 100.0f), Color3B(200, 200, 200), 10000.0f);
    addChild(light1);
    auto light2 = AmbientLight::create(Color3B(100, 100, 100));
    addChild(light2);
    
    auto animation = Animation3D::create(fileName);
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        auto act = RepeatForever::create(animate);
        act->setTag(0);
        sprite->runAction(act);
    }
    addChild(sprite);
    _sprites.push_back(sprite);
    
    // add jumping orc
    fileName = "Sprite3DTest/orc_jump.c3t";
    sprite = Sprite3D::create(fileName);
    sprite->setRotation3D(Vec3(0, 180, 0));
    sprite->setScale(3);
    sprite->setPosition(Vec2(s.width / 2.f, s.height / 3.f));
    sprite->setVisible(false);
    animation = Animation3D::create(fileName);
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        auto act = RepeatForever::create(animate);
        act->setTag(0);
        sprite->runAction(act);
    }
    addChild(sprite);
    _sprites.push_back(sprite);
}

Sprite3DCubeMapTest::Sprite3DCubeMapTest() :
    _textureCube(nullptr),
    _skyBox(nullptr),
    _teapot(nullptr)
{
    auto s = Director::getInstance()->getWinSize();
    addNewSpriteWithCoords(Vec2(s.width / 2, s.height / 2));
}

Sprite3DCubeMapTest::~Sprite3DCubeMapTest()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif

    _teapot->release();
    _skyBox->release();
    _textureCube->release();
}

std::string Sprite3DCubeMapTest::title() const
{
    return "CubeMap & Skybox Test";
}

std::string Sprite3DCubeMapTest::subtitle() const
{
    return "";
}

void Sprite3DCubeMapTest::addNewSpriteWithCoords(Vec2 p)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _camera = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 10, 1000);
    _camera->setPosition3D(Vec3(0.f, 0.f, 50.f));
    _camera->setCameraFlag(CameraFlag::USER1);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(Sprite3DCubeMapTest::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // create a teapot
    _teapot = Sprite3D::create("Sprite3DTest/teapot.c3b");
    _teapot->retain();

    //create and set our custom shader
    auto shader = GLProgram::createWithFilenames("Sprite3DTest/cube_map.vert", "Sprite3DTest/cube_map.frag");
    auto state = GLProgramState::create(shader);

    // create the second texture for cylinder
    _textureCube = TextureCube::create("Sprite3DTest/skybox/left.jpg", "Sprite3DTest/skybox/right.jpg",
        "Sprite3DTest/skybox/top.jpg", "Sprite3DTest/skybox/bottom.jpg",
        "Sprite3DTest/skybox/front.jpg", "Sprite3DTest/skybox/back.jpg");

    _textureCube->retain();

    //set texture parameters
    Texture2D::TexParams tRepeatParams;
    tRepeatParams.magFilter = GL_LINEAR;
    tRepeatParams.minFilter = GL_LINEAR;
    tRepeatParams.wrapS = GL_CLAMP_TO_EDGE;
    tRepeatParams.wrapT = GL_CLAMP_TO_EDGE;
    _textureCube->setTexParameters(tRepeatParams);

    // pass the texture sampler to our custom shader
    state->setUniformTexture("u_cubeTex", _textureCube);

    _teapot->setGLProgramState(state);
    _teapot->setPosition3D(Vec3(0, -5, 0));
    _teapot->setRotation3D(Vec3(-90, 180, 0));

    auto rotate_action = RotateBy::create(1.5, Vec3(0, 30, 0));
    _teapot->runAction(RepeatForever::create(rotate_action));

    //pass mesh's attribute to shader
    long offset = 0;
    auto attributeCount = _teapot->getMesh()->getMeshVertexAttribCount();
    for (auto i = 0; i < attributeCount; i++)
    {
        auto meshattribute = _teapot->getMesh()->getMeshVertexAttribute(i);
        state->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
            meshattribute.size,
            meshattribute.type,
            GL_FALSE,
            _teapot->getMesh()->getVertexSizeInBytes(),
            (GLvoid*)offset);

        offset += meshattribute.attribSizeBytes;
    }
    addChild(_teapot);

    {
        // config skybox
        _skyBox = Skybox::create();
        _skyBox->retain();

        _skyBox->setTexture(_textureCube);
        addChild(_skyBox);
    }

    addChild(_camera);
    setCameraMask(2);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                [this](EventCustom*)
    {
        auto state = _teapot->getGLProgramState();
        auto glProgram = state->getGLProgram();
        glProgram->reset();
        glProgram->initWithFilenames("Sprite3DTest/cube_map.vert", "Sprite3DTest/cube_map.frag");
        glProgram->link();
        glProgram->updateUniforms();

        _textureCube->reloadTexture();

        Texture2D::TexParams tRepeatParams;
        tRepeatParams.magFilter = GL_NEAREST;
        tRepeatParams.minFilter = GL_NEAREST;
        tRepeatParams.wrapS = GL_CLAMP_TO_EDGE;
        tRepeatParams.wrapT = GL_CLAMP_TO_EDGE;
        _textureCube->setTexParameters(tRepeatParams);
        state->setUniformTexture("u_cubeTex", _textureCube);

        _skyBox->reload();
        _skyBox->setTexture(_textureCube);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, 1);
#endif
}

void Sprite3DCubeMapTest::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (touches.size())
    {
        auto touch = touches[0];
        auto delta = touch->getDelta();

        static float _angle = 0.f;
        _angle -= CC_DEGREES_TO_RADIANS(delta.x);
        _camera->setPosition3D(Vec3(50.0f * sinf(_angle), 0.0f, 50.0f * cosf(_angle)));
        _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    }
}

Issue9767::Issue9767()
{
    _shaderType = Issue9767::ShaderType::SHADER_TEX;
    
    auto s = Director::getInstance()->getWinSize();
    auto sprite = Sprite3D::create("Sprite3DTest/boss1.obj");
    sprite->setScale(3.f);
    sprite->setTexture("Sprite3DTest/boss.png");
    addChild( sprite );
    sprite->setPosition(Vec2(s.width/2, s.height/2));
    _sprite = sprite;
    
    TTFConfig ttfConfig("fonts/arial.ttf", 15);
    auto label1 = Label::createWithTTF(ttfConfig,"switch shader");
    auto item1 = MenuItemLabel::create(label1,CC_CALLBACK_1(Issue9767::menuCallback_SwitchShader,this) );
    
    item1->setPosition( Vec2(s.width * 0.9f - item1->getContentSize().width * 0.5f, s.height * 0.5f - item1->getContentSize().height ) );
    
    auto pMenu1 = CCMenu::create(item1, nullptr);
    pMenu1->setPosition(Vec2(0,0));
    addChild(pMenu1);
}

Issue9767::~Issue9767()
{
    
}

void Issue9767::menuCallback_SwitchShader(cocos2d::Ref* sender)
{
    GLProgram* glProgram = nullptr;
    if (_shaderType == Issue9767::ShaderType::SHADER_TEX)
    {
        _shaderType = Issue9767::ShaderType::SHADER_COLOR;
        glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION);
    }
    else
    {
        _shaderType = Issue9767::ShaderType::SHADER_TEX;
        glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION_TEXTURE);
    }
    _sprite->setGLProgram(glProgram);
}

std::string Issue9767::title() const
{
    return "Issue9767: test setGLProgram";
}

std::string Issue9767::subtitle() const
{
    return "";
}

Sprite3DClippingTest::Sprite3DClippingTest()
{
    auto size = Director::getInstance()->getWinSize();
    auto stencil = Sprite::create("Images/close.png");
    auto clipSprite3D = ClippingNode::create();
    clipSprite3D->setStencil(stencil);
    this->addChild(clipSprite3D);
    clipSprite3D->setScale(3.0f);
    
    auto sprite3D = Sprite3D::create("Sprite3DTest/orc.c3b");
    sprite3D->setScale(1.0f);
    sprite3D->setRotation3D(Vec3(0.0f, 180.0f, 0.0f));
    clipSprite3D->addChild(sprite3D);//5
    
    clipSprite3D->setPosition(Vec2(size.width / 2, size.height / 2));
    
    auto seq = Sequence::create(ScaleTo::create(2.f, 3), ScaleTo::create(2.f, 0.5f), NULL);
    sprite3D->runAction(RepeatForever::create(seq));
    auto animation = Animation3D::create("Sprite3DTest/orc.c3b");
    auto animate = Animate3D::create(animation);
    sprite3D->runAction(RepeatForever::create(animate));
    sprite3D->setForce2DQueue(true);
}

Sprite3DClippingTest::~Sprite3DClippingTest()
{
    
}

std::string Sprite3DClippingTest::title() const
{
    return "Sprite3D Clipping Test";
}

std::string Sprite3DClippingTest::subtitle() const
{
    return "";
}

Sprite3DTestMeshLight::Sprite3DTestMeshLight()
{
    auto s = Director::getInstance()->getWinSize();

    auto _sprite = Sprite3D::create("Sprite3DTest/mesh_model.c3b");
    _sprite->setPosition(Vec2(0, 0));
    _sprite->setScale(0.05f);
    _sprite->setCameraMask(2);

    PointLight * light = PointLight::create(Vec3(0, 0, 400), Color3B(255, 255, 255), 1000.0f);

    //setup camera
    auto camera = Camera::createPerspective(40, s.width / s.height, 0.01f, 1000.f);
    camera->setCameraFlag(CameraFlag::USER1);
    camera->setPosition3D(Vec3(0.f, 30.f, 100.f));
    camera->lookAt(Vec3(0.f, 0.f, 0.f));
    addChild(camera);

    addChild(_sprite);
    addChild(light);
}

std::string Sprite3DTestMeshLight::title() const
{
    return "3D mesh with light without texture";
}

std::string Sprite3DTestMeshLight::subtitle() const
{
    return "";
}