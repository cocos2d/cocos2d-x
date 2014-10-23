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

#include "Camera3DTest.h"
#include <algorithm>
#include "../testResource.h"

////////////DrawLine/////////////////////
DrawLine3D* DrawLine3D::create()
{
    auto ret = new (std::nothrow) DrawLine3D();
    if (ret && ret->init())
        return ret;
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool DrawLine3D::init()
{
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_COLOR));
    return true;
}

void DrawLine3D::drawLine(const Vec3 &from, const Vec3 &to, const Color4F &color)
{
    Color4B col = Color4B(color);
    DrawLine3D::V3F_C4B vertex;
    vertex.vertices = from;
    vertex.colors = col;
    _buffer.push_back(vertex);
    vertex.vertices = to;
    _buffer.push_back(vertex);
}

void DrawLine3D::drawCube(Vec3* vertices, const Color4F &color)
{
    // front face
    drawLine(vertices[0], vertices[1], color);
    drawLine(vertices[1], vertices[2], color);
    drawLine(vertices[2], vertices[3], color);
    drawLine(vertices[3], vertices[0], color);
    
    // back face
    drawLine(vertices[4], vertices[5], color);
    drawLine(vertices[5], vertices[6], color);
    drawLine(vertices[6], vertices[7], color);
    drawLine(vertices[7], vertices[4], color);
    
    // edge
    drawLine(vertices[0], vertices[7], color);
    drawLine(vertices[1], vertices[6], color);
    drawLine(vertices[2], vertices[5], color);
    drawLine(vertices[3], vertices[4], color);
}

void DrawLine3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(DrawLine3D::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void DrawLine3D::onDraw(const Mat4 &transform, uint32_t flags)
{
    auto glProgram = getGLProgram();
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    glEnable(GL_DEPTH_TEST);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B), &(_buffer[0].vertices));
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B), &(_buffer[0].colors));
    glDrawArrays(GL_LINES, 0, static_cast<int>(_buffer.size()));
    glDisable(GL_DEPTH_TEST);
}

////////////////////////////////////////////////////////////////////////////////

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1;

static std::function<Layer*()> createFunctions[] =
{
    CL(Camera3DTestDemo),
    CL(CameraClipDemo)
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

Camera3DTestDemo::Camera3DTestDemo(void)
: BaseTest()
, _camera(nullptr)
, _incRot(nullptr)
, _decRot(nullptr)
,_bZoomOut(false)
,_bZoomIn(false)
,_bRotateLeft(false)
,_bRotateRight(false)
{
}
Camera3DTestDemo::~Camera3DTestDemo(void)
{
}
void Camera3DTestDemo::reachEndCallBack()
{
}
std::string Camera3DTestDemo::title() const
{
    return "Testing Camera";
}

std::string Camera3DTestDemo::subtitle() const
{
    return "";
}
void Camera3DTestDemo::scaleCameraCallback(Ref* sender,float value)
{
    if(_camera&& _cameraType!=CameraType::FirstCamera)
    {
        Vec3 cameraPos=  _camera->getPosition3D();
        cameraPos+= cameraPos.getNormalized()*value;
        _camera->setPosition3D(cameraPos);
    }
}
void Camera3DTestDemo::rotateCameraCallback(Ref* sender,float value)
{
    if(_cameraType==CameraType::FreeCamera || _cameraType==CameraType::FirstCamera)
    {
        Vec3  rotation3D= _camera->getRotation3D();
        rotation3D.y+= value;
        _camera->setRotation3D(rotation3D);
    }
}
void Camera3DTestDemo::SwitchViewCallback(Ref* sender, CameraType cameraType)
{
    if(_cameraType==cameraType)
    {
        return ;
    }
    _cameraType = cameraType;
    if(_cameraType==CameraType::FreeCamera)
    {
        _camera->setPosition3D(Vec3(0, 130, 130) + _sprite3D->getPosition3D());
        _camera->lookAt(_sprite3D->getPosition3D(), Vec3(0,1,0));
        
        _RotateRightlabel->setColor(Color3B::WHITE);
        _RotateLeftlabel->setColor(Color3B::WHITE);
        _ZoomInlabel->setColor(Color3B::WHITE);
        _ZoomOutlabel->setColor(Color3B::WHITE);
    }
    else if(_cameraType==CameraType::FirstCamera)
    {
        Vec3 newFaceDir;
        _sprite3D->getWorldToNodeTransform().getForwardVector(&newFaceDir);
        newFaceDir.normalize();
        _camera->setPosition3D(Vec3(0,35,0) + _sprite3D->getPosition3D());
        _camera->lookAt(_sprite3D->getPosition3D() + newFaceDir*50, Vec3(0, 1, 0));
        
        _RotateRightlabel->setColor(Color3B::WHITE);
        _RotateLeftlabel->setColor(Color3B::WHITE);
        _ZoomInlabel->setColor(Color3B::GRAY);
        _ZoomOutlabel->setColor(Color3B::GRAY);
    }
    else if(_cameraType==CameraType::ThirdCamera)
    {
        _camera->setPosition3D(Vec3(0, 130, 130) + _sprite3D->getPosition3D());
        _camera->lookAt(_sprite3D->getPosition3D(), Vec3(0,1,0));
        
        _RotateRightlabel->setColor(Color3B::GRAY);
        _RotateLeftlabel->setColor(Color3B::GRAY);
        _ZoomInlabel->setColor(Color3B::WHITE);
        _ZoomOutlabel->setColor(Color3B::WHITE);
    }
}
void Camera3DTestDemo::onEnter()
{
    BaseTest::onEnter();
    _sprite3D=nullptr;
    auto s = Director::getInstance()->getWinSize();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Camera3DTestDemo::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Camera3DTestDemo::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Camera3DTestDemo::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    auto layer3D=Layer::create();
    addChild(layer3D,0);
    _layer3D=layer3D;
    _curState=State_None;
    addNewSpriteWithCoords( Vec3(0,0,0),"Sprite3DTest/girl.c3b",true,0.2f,true);
    TTFConfig ttfConfig("fonts/arial.ttf", 20);
    
    auto containerForLabel1 = Node::create();
    _ZoomOutlabel = Label::createWithTTF(ttfConfig,"zoom out");
    _ZoomOutlabel->setPosition(s.width-50, VisibleRect::top().y-30);
    containerForLabel1->addChild(_ZoomOutlabel);
    addChild(containerForLabel1, 10);
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = CC_CALLBACK_2(Camera3DTestDemo::onTouchesZoomOut, this);
    listener1->onTouchEnded = CC_CALLBACK_2(Camera3DTestDemo::onTouchesZoomOutEnd, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, _ZoomOutlabel);
    
    auto containerForLabel2 = Node::create();
    _ZoomInlabel = Label::createWithTTF(ttfConfig,"zoom in");
    _ZoomInlabel->setPosition(s.width-50, VisibleRect::top().y-100);
    containerForLabel2->addChild(_ZoomInlabel);
    addChild(containerForLabel2, 10);
    
    auto listener2 = EventListenerTouchOneByOne::create();
    listener2->setSwallowTouches(true);
    
    listener2->onTouchBegan = CC_CALLBACK_2(Camera3DTestDemo::onTouchesZoomIn, this);
    listener2->onTouchEnded = CC_CALLBACK_2(Camera3DTestDemo::onTouchesZoomInEnd, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, _ZoomInlabel);
    
    auto containerForLabel3 = Node::create();
    _RotateLeftlabel = Label::createWithTTF(ttfConfig,"rotate left");
    _RotateLeftlabel->setPosition(s.width-50, VisibleRect::top().y-170);
    containerForLabel3->addChild(_RotateLeftlabel);
    addChild(containerForLabel3, 10);
    
    auto listener3 = EventListenerTouchOneByOne::create();
    listener3->setSwallowTouches(true);
    
    listener3->onTouchBegan = CC_CALLBACK_2(Camera3DTestDemo::onTouchesRotateLeft, this);
    listener3->onTouchEnded = CC_CALLBACK_2(Camera3DTestDemo::onTouchesRotateLeftEnd, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener3, _RotateLeftlabel);
    
    auto containerForLabel4 = Node::create();
    _RotateRightlabel = Label::createWithTTF(ttfConfig,"rotate right");
    _RotateRightlabel->setPosition(s.width-50, VisibleRect::top().y-240);
    containerForLabel4->addChild(_RotateRightlabel);
    addChild(containerForLabel4, 10);
    
    auto listener4 = EventListenerTouchOneByOne::create();
    listener4->setSwallowTouches(true);
    
    listener4->onTouchBegan = CC_CALLBACK_2(Camera3DTestDemo::onTouchesRotateRight, this);
    listener4->onTouchEnded = CC_CALLBACK_2(Camera3DTestDemo::onTouchesRotateRightEnd, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener4, _RotateRightlabel);
    
    auto label1 = Label::createWithTTF(ttfConfig,"free ");
    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(Camera3DTestDemo::SwitchViewCallback,this,CameraType::FreeCamera));
    auto label2 = Label::createWithTTF(ttfConfig,"third person");
    auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(Camera3DTestDemo::SwitchViewCallback,this,CameraType::ThirdCamera));
    auto label3 = Label::createWithTTF(ttfConfig,"first person");
    auto menuItem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(Camera3DTestDemo::SwitchViewCallback,this,CameraType::FirstCamera));
    auto menu = Menu::create(menuItem1, menuItem2, menuItem3, nullptr);
    
    menu->setPosition(Vec2::ZERO);
    
    menuItem1->setPosition(VisibleRect::left().x+100, VisibleRect::top().y-50);
    menuItem2->setPosition(VisibleRect::left().x+100, VisibleRect::top().y -100);
    menuItem3->setPosition(VisibleRect::left().x+100, VisibleRect::top().y -150);
    addChild(menu, 0);
    schedule(CC_SCHEDULE_SELECTOR(Camera3DTestDemo::updateCamera), 0.0f);
    if (_camera == nullptr)
    {
        _camera=Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 1000);
        _camera->setCameraFlag(CameraFlag::USER1);
        _layer3D->addChild(_camera);
    }
    SwitchViewCallback(this,CameraType::ThirdCamera);
    DrawLine3D* line =DrawLine3D::create();
    //draw x
    for( int j =-20; j<=20 ;j++)
    {
        line->drawLine(Vec3(-100, 0, 5*j),Vec3(100,0,5*j),Color4F(1,0,0,1));
    }
    //draw z
    for( int j =-20; j<=20 ;j++)
    {
        line->drawLine(Vec3(5*j, 0, -100),Vec3(5*j,0,100),Color4F(0,0,1,1));
    }
    //draw y
    line->drawLine(Vec3(0, -50, 0),Vec3(0,0,0),Color4F(0,0.5,0,1));
    line->drawLine(Vec3(0, 0, 0),Vec3(0,50,0),Color4F(0,1,0,1));
    _layer3D->addChild(line);
    _layer3D->setCameraMask(2);
}
void Camera3DTestDemo::onExit()
{
    BaseTest::onExit();
    if (_camera)
    {
        _camera = nullptr;
    }
}

void Camera3DTestDemo::restartCallback(Ref* sender)
{
    auto s = new (std::nothrow) Camera3DTestScene();
    s->addChild(restartSpriteTestAction());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void Camera3DTestDemo::nextCallback(Ref* sender)
{
    auto s = new (std::nothrow) Camera3DTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}
void Camera3DTestDemo::backCallback(Ref* sender)
{
    auto s = new (std::nothrow) Camera3DTestScene();
    s->addChild( backSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}
void Camera3DTestDemo::addNewSpriteWithCoords(Vec3 p,std::string fileName,bool playAnimation,float scale,bool bindCamera)
{
    
    auto sprite = Sprite3D::create(fileName);
    _layer3D->addChild(sprite);
    float globalZOrder=sprite->getGlobalZOrder();
    sprite->setPosition3D( Vec3( p.x, p.y,p.z) );
    sprite->setGlobalZOrder(globalZOrder);
    if(playAnimation)
    {
        auto animation = Animation3D::create(fileName,"Take 001");
        if (animation)
        {
            auto animate = Animate3D::create(animation);
            sprite->runAction(RepeatForever::create(animate));
        }
    }
    if(bindCamera)
    {
        _sprite3D=sprite;
    }
    sprite->setScale(scale);
    
}
void Camera3DTestDemo::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        auto location = touch->getLocation();
    }
}
void Camera3DTestDemo::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if(touches.size()==1)
    {
        auto touch = touches[0];
        auto location = touch->getLocation();
        Point newPos = touch->getPreviousLocation()-location;
        if(_cameraType==CameraType::FreeCamera || _cameraType==CameraType::FirstCamera)
        {
            Vec3 cameraDir;
            Vec3 cameraRightDir;
            _camera->getNodeToWorldTransform().getForwardVector(&cameraDir);
            cameraDir.normalize();
            cameraDir.y=0;
            _camera->getNodeToWorldTransform().getRightVector(&cameraRightDir);
            cameraRightDir.normalize();
            cameraRightDir.y=0;
            Vec3 cameraPos=  _camera->getPosition3D();
            cameraPos+=cameraDir*newPos.y*0.1f;
            cameraPos+=cameraRightDir*newPos.x*0.1f;
            _camera->setPosition3D(cameraPos);
            if(_sprite3D &&  _cameraType==CameraType::FirstCamera)
            {
                _sprite3D->setPosition3D(Vec3(_camera->getPositionX(),0,_camera->getPositionZ()));
                _targetPos=_sprite3D->getPosition3D();
            }
        }
    }
}
void Camera3DTestDemo::move3D(float elapsedTime)
{
    if(_sprite3D)
    {
        Vec3 curPos=  _sprite3D->getPosition3D();
        Vec3 newFaceDir = _targetPos - curPos;
        newFaceDir.y = 0.0f;
        newFaceDir.normalize();
        Vec3 offset = newFaceDir * 25.0f * elapsedTime;
        curPos+=offset;
        _sprite3D->setPosition3D(curPos);
        offset.x=offset.x;
        offset.z=offset.z;
        if(_cameraType==CameraType::ThirdCamera)
        {
            Vec3 cameraPos= _camera->getPosition3D();
            cameraPos.x+=offset.x;
            cameraPos.z+=offset.z;
            _camera->setPosition3D(cameraPos);
        }
    }
}
void Camera3DTestDemo::updateState(float elapsedTime)
{
    if(_sprite3D)
    {
        Vec3 curPos=  _sprite3D->getPosition3D();
        Vec3 curFaceDir;
        _sprite3D->getNodeToWorldTransform().getForwardVector(&curFaceDir);
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
}
void Camera3DTestDemo::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        auto location = touch->getLocationInView();
        if(_camera)
        {
            if(_sprite3D && _cameraType==CameraType::ThirdCamera && _bZoomOut == false && _bZoomIn == false && _bRotateLeft == false && _bRotateRight == false)
            {
                Vec3 nearP(location.x, location.y, -1.0f), farP(location.x, location.y, 1.0f);
                
                auto size = Director::getInstance()->getWinSize();
                _camera->unproject(size, &nearP, &nearP);
                _camera->unproject(size, &farP, &farP);
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
void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
}
void Camera3DTestDemo::updateCamera(float fDelta)
{
    if(_sprite3D)
    {
        if( _cameraType==CameraType::ThirdCamera)
        {
            updateState(fDelta);
            if(isState(_curState,State_Move))
            {
                move3D(fDelta);
                if(isState(_curState,State_Rotate))
                {
                    Vec3 curPos = _sprite3D->getPosition3D();
                    
                    Vec3 newFaceDir = _targetPos - curPos;
                    newFaceDir.y = 0;
                    newFaceDir.normalize();
                    Vec3 up;
                    _sprite3D->getNodeToWorldTransform().getUpVector(&up);
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
                    _sprite3D->setAdditionalTransform(&mat);
                }
            }
        }
        if(_bZoomOut == true)
        {
            if(_camera)
            {
                if(_cameraType == CameraType::ThirdCamera)
                {
                    Vec3 lookDir = _camera->getPosition3D() - _sprite3D->getPosition3D();
                    Vec3 cameraPos = _camera->getPosition3D();
                    if(lookDir.length() <= 300)
                    {
                        cameraPos += lookDir.getNormalized();
                        _camera->setPosition3D(cameraPos);
                    }
                }
                else if(_cameraType == CameraType::FreeCamera)
                {
                    Vec3 cameraPos = _camera->getPosition3D();
                    if(cameraPos.length() <= 300)
                    {
                        cameraPos += cameraPos.getNormalized();
                        _camera->setPosition3D(cameraPos);
                    }
                }
            }
        }
        if(_bZoomIn == true)
        {
            if(_camera)
            {
                if(_cameraType == CameraType::ThirdCamera)
                {
                    Vec3 lookDir = _camera->getPosition3D() - _sprite3D->getPosition3D();
                    Vec3 cameraPos = _camera->getPosition3D();
                    if(lookDir.length() >= 50)
                    {
                        cameraPos -= lookDir.getNormalized();
                        _camera->setPosition3D(cameraPos);
                    }
                }
                else if(_cameraType == CameraType::FreeCamera)
                {
                    Vec3 cameraPos = _camera->getPosition3D();
                    if(cameraPos.length() >= 50)
                    {
                        cameraPos -= cameraPos.getNormalized();
                        _camera->setPosition3D(cameraPos);
                    }
                }
            }
        }
        if(_bRotateLeft == true)
        {
            if(_cameraType==CameraType::FreeCamera || _cameraType==CameraType::FirstCamera)
            {
                Vec3  rotation3D= _camera->getRotation3D();
                rotation3D.y+= 1;
                _camera->setRotation3D(rotation3D);
            }
        }
        if(_bRotateRight == true)
        {
            if(_cameraType==CameraType::FreeCamera || _cameraType==CameraType::FirstCamera)
            {
                Vec3  rotation3D= _camera->getRotation3D();
                rotation3D.y-= 1;
                _camera->setRotation3D(rotation3D);
            }
        }
    }
}
bool Camera3DTestDemo::isState(unsigned int state,unsigned int bit) const
{
    return (state & bit) == bit;
}
bool Camera3DTestDemo::onTouchesZoomOut(Touch* touch, Event* event)
{
    auto target = static_cast<Label*>(event->getCurrentTarget());
    
    Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode))
    {
        _bZoomOut = true;
        return true;
    }
    return false;
}
void Camera3DTestDemo::onTouchesZoomOutEnd(Touch* touch, Event* event)
{
    _bZoomOut = false;
}
bool Camera3DTestDemo::onTouchesZoomIn(Touch* touch, Event* event)
{
    auto target = static_cast<Label*>(event->getCurrentTarget());
    
    Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode))
    {
        _bZoomIn = true;
        return true;
    }
    return false;
}
void Camera3DTestDemo::onTouchesZoomInEnd(Touch* touch, Event* event)
{
    _bZoomIn = false;
}
bool Camera3DTestDemo::onTouchesRotateLeft(Touch* touch, Event* event)
{
    auto target = static_cast<Label*>(event->getCurrentTarget());
    
    Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode))
    {
        _bRotateLeft = true;
        return true;
    }
    return false;
}
void Camera3DTestDemo::onTouchesRotateLeftEnd(Touch* touch, Event* event)
{
    _bRotateLeft = false;
}
bool Camera3DTestDemo::onTouchesRotateRight(Touch* touch, Event* event)
{
    auto target = static_cast<Label*>(event->getCurrentTarget());
    
    Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode))
    {
        _bRotateRight = true;
        return true;
    }
    return false;
}
void Camera3DTestDemo::onTouchesRotateRightEnd(Touch* touch, Event* event)
{
    _bRotateRight = false;
}

////////////////////////////////////////////////////////////
// CameraClipDemo
CameraClipDemo::CameraClipDemo(void)
: BaseTest()
, _labelDrawCall(nullptr)
, _layer3D(nullptr)
, _cameraFirst(nullptr)
, _cameraThird(nullptr)
, _moveAction(nullptr)
, _drawAABB(nullptr)
, _drawFrustum(nullptr)
{
}
CameraClipDemo::~CameraClipDemo(void)
{
}

std::string CameraClipDemo::title() const
{
    return "Testing Camera";
}

std::string CameraClipDemo::subtitle() const
{
    return "Camera Frustum Clipping";
}

void CameraClipDemo::switchViewCallback(Ref* sender, CameraType cameraType)
{
    if(_cameraType==cameraType)
    {
        return ;
    }
    _cameraType = cameraType;
    if(_cameraType==CameraType::FirstCamera)
    {
        _drawFrustum->clear();
        _cameraFirst->setCameraFlag(CameraFlag::USER1);
        _cameraThird->setCameraFlag(CameraFlag::USER8);
        _cameraFirst->enableFrustumCull(true, true);
    }
    else if(_cameraType==CameraType::ThirdCamera)
    {
        _cameraThird->setCameraFlag(CameraFlag::USER1);
        _cameraFirst->setCameraFlag(CameraFlag::USER8);
        _cameraThird->enableFrustumCull(false, false);
    }
}
void CameraClipDemo::onEnter()
{
    BaseTest::onEnter();
    auto s = Director::getInstance()->getWinSize();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(CameraClipDemo::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(CameraClipDemo::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(CameraClipDemo::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    auto layer3D=Layer::create();
    addChild(layer3D,0);
    _layer3D=layer3D;
    
    TTFConfig ttfConfig("fonts/arial.ttf", 20);
    auto label1 = Label::createWithTTF(ttfConfig,"third person");
    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(CameraClipDemo::switchViewCallback,this,CameraType::ThirdCamera));
    auto label2 = Label::createWithTTF(ttfConfig,"first person");
    auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(CameraClipDemo::switchViewCallback,this,CameraType::FirstCamera));
    auto menu = Menu::create(menuItem1,menuItem2,NULL);
    
    menu->setPosition(Vec2::ZERO);
    menuItem1->setPosition(VisibleRect::left().x+70, VisibleRect::top().y -50);
    menuItem2->setPosition(VisibleRect::left().x+70, VisibleRect::top().y -80);
    addChild(menu, 0);
    
    _labelDrawCall = Label::createWithTTF(ttfConfig,"In Frustum Num: ");
    _labelDrawCall->setPosition(VisibleRect::rightTop().x-80, VisibleRect::rightTop().y -50);
    addChild(_labelDrawCall, 0);
    
    schedule(schedule_selector(CameraClipDemo::update), 0.0f);
    
    if (_cameraFirst == nullptr)
    {
        _cameraFirst=Camera::createPerspective(30, (GLfloat)s.width/s.height, 10, 200);
        _layer3D->addChild(_cameraFirst);
    }
    if (_cameraThird == nullptr)
    {
        _cameraThird=Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 1000);
        _layer3D->addChild(_cameraThird);
    }
    
    DrawLine3D* line =DrawLine3D::create();
    const int gridNum = 30;
    const int girdSize = 5;
    //draw x
    for( int j =-gridNum; j<=gridNum ;j++)
    {
        line->drawLine(Vec3(-gridNum*girdSize, 0, 5*j),Vec3(gridNum*girdSize,0,5*j),Color4F(1,0,0,1));
    }
    //draw z
    for( int j =-gridNum; j<=gridNum ;j++)
    {
        line->drawLine(Vec3(5*j, 0, -gridNum*girdSize),Vec3(5*j,0,gridNum*girdSize),Color4F(0,0,1,1));
    }
    
    _layer3D->addChild(line);
    
    _drawAABB = DrawLine3D::create();
    _layer3D->addChild(_drawAABB);
    
    // add some objects to 3d layer
    int num = 5;
    objects.clear();
    for (int x = -num; x < num; x++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int z = -num; z < num; z++) {
                auto sprite = Sprite3D::create("Sprite3DTest/boss.c3b");
                sprite->setPosition3D( Vec3( x*30, j*30, z*30) );
                objects.push_back(sprite);
                _layer3D->addChild(sprite);
                
                Vec3 corners[8];
                sprite->getAABB().getCorners(corners);
                _drawAABB->drawCube(corners, Color4F(0, 1, 0, 1));
            }
        }
    }
    
    _drawFrustum = DrawLine3D::create();
    _layer3D->addChild(_drawFrustum);
    
    switchViewCallback(this,CameraType::FirstCamera);
    initCamera();
    _layer3D->setCameraMask(2);
}

void CameraClipDemo::onExit()
{
    BaseTest::onExit();
    if (_cameraFirst)
    {
        _cameraFirst = nullptr;
    }
    if (_cameraThird)
    {
        _cameraThird = nullptr;
    }
}

void CameraClipDemo::restartCallback(Ref* sender)
{
    auto s = new (std::nothrow) Camera3DTestScene();
    s->addChild(restartSpriteTestAction());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void CameraClipDemo::nextCallback(Ref* sender)
{
    auto s = new (std::nothrow) Camera3DTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}
void CameraClipDemo::backCallback(Ref* sender)
{
    auto s = new (std::nothrow) Camera3DTestScene();
    s->addChild( backSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void CameraClipDemo::reachEndCallBack()
{
    _cameraFirst->stopActionByTag(100);
    auto inverse = (MoveTo*)_moveAction->reverse();
    inverse->retain();
    _moveAction->release();
    _moveAction = inverse;
    auto rot = RotateBy::create(1.f, Vec3(0.f, 180.f, 0.f));
    auto seq = Sequence::create(rot, _moveAction, CallFunc::create(CC_CALLBACK_0(CameraClipDemo::reachEndCallBack, this)), nullptr);
    seq->setTag(100);
    _cameraFirst->runAction(seq);
}

void CameraClipDemo::drawCameraFrustum()
{
    _drawFrustum->clear();
    auto size = Director::getInstance()->getWinSize();
    
    Color4F color(1.f, 1.f, 0.f, 1);
    
    // top-left
    Vec3 tl_0,tl_1;
    Vec3 src(0,0,0);
    _cameraFirst->unproject(size, &src, &tl_0);
    src = Vec3(0,0,1);
    _cameraFirst->unproject(size, &src, &tl_1);
    
    // top-right
    Vec3 tr_0,tr_1;
    src = Vec3(size.width,0,0);
    _cameraFirst->unproject(size, &src, &tr_0);
    src = Vec3(size.width,0,1);
    _cameraFirst->unproject(size, &src, &tr_1);
    
    // bottom-left
    Vec3 bl_0,bl_1;
    src = Vec3(0,size.height,0);
    _cameraFirst->unproject(size, &src, &bl_0);
    src = Vec3(0,size.height,1);
    _cameraFirst->unproject(size, &src, &bl_1);
    
    // bottom-right
    Vec3 br_0,br_1;
    src = Vec3(size.width,size.height,0);
    _cameraFirst->unproject(size, &src, &br_0);
    src = Vec3(size.width,size.height,1);
    _cameraFirst->unproject(size, &src, &br_1);
    
    _drawFrustum->drawLine(tl_0, tl_1, color);
    _drawFrustum->drawLine(tr_0, tr_1, color);
    _drawFrustum->drawLine(bl_0, bl_1, color);
    _drawFrustum->drawLine(br_0, br_1, color);
    
    _drawFrustum->drawLine(tl_0, tr_0, color);
    _drawFrustum->drawLine(tr_0, br_0, color);
    _drawFrustum->drawLine(br_0, bl_0, color);
    _drawFrustum->drawLine(bl_0, tl_0, color);
    
    _drawFrustum->drawLine(tl_1, tr_1, color);
    _drawFrustum->drawLine(tr_1, br_1, color);
    _drawFrustum->drawLine(br_1, bl_1, color);
    _drawFrustum->drawLine(bl_1, tl_1, color);
}

void CameraClipDemo::initCamera()
{
    if (_cameraThird)
    {
        _cameraFirst->setPosition3D(Vec3(-100,0,0));
        _cameraFirst->lookAt(Vec3(1000,0,0), Vec3(0, 1, 0));
        _moveAction = MoveTo::create(4.f, Vec2(100, 0));
        _moveAction->retain();
        auto seq = Sequence::create(_moveAction, CallFunc::create(CC_CALLBACK_0(CameraClipDemo::reachEndCallBack, this)), nullptr);
        seq->setTag(100);
        _cameraFirst->runAction(seq);
    }
    
    if (_cameraThird)
    {
        _cameraThird->setPosition3D(Vec3(0, 130, 130));
        _cameraThird->lookAt(Vec3(0,0,0), Vec3(0, 1, 0));
    }
}


void CameraClipDemo::update(float fDelta)
{
    static unsigned long prevCalls = 0;
    unsigned long drawCall = Director::getInstance()->getRenderer()->getDrawnBatches() - 10;
    if( drawCall != prevCalls )
    {
        char szDrawCall[255];
        sprintf(szDrawCall, "In Frustum Num: %6lu", drawCall);
        _labelDrawCall->setString(szDrawCall);
    }
    if( _cameraType==CameraType::ThirdCamera)
    {
        drawCameraFrustum();
    }
}

void Camera3DTestScene::runThisTest()
{
    auto layer = nextSpriteTestAction();
    addChild(layer);
    Director::getInstance()->replaceScene(this);
}
