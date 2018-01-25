/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
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

#ifndef _CAMERA3D_TEST_H_
#define _CAMERA3D_TEST_H_

#include "../BaseTest.h"
#include "../Sprite3DTest/DrawNode3D.h"
#include <string>

namespace cocos2d {
    class Sprite3D;
    class Delay;
}

enum State
{
    State_None = 0,
    State_Idle = 0x01,
    State_Move = 0x02,
    State_Rotate = 0x04,
    State_Speak = 0x08,
    State_MeleeAttack = 0x10,
    State_RemoteAttack = 0x20,
    State_Attack = 0x40,
};
enum class CameraType
{
    Free = 0,
    FirstPerson = 1,
    ThirdPerson = 2,
};

enum class OperateCamType
{
    MoveCamera=0,
    RotateCamera=1,
};

DEFINE_TEST_SUITE(Camera3DTests);

class CameraBaseTest : public TestCase
{
public:
    
protected:
    cocos2d::BillBoard* bill1;
    cocos2d::BillBoard* bill2;
    cocos2d::Label* l1;
    cocos2d::Label* l2;
};

class CameraRotationTest : public CameraBaseTest {

public:
    CREATE_FUNC(CameraRotationTest);
    CameraRotationTest(void);
    virtual ~CameraRotationTest(void);

    virtual void onEnter() override;
    virtual void onExit() override;

    virtual void update(float dt) override;

    // overrides
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:

    cocos2d::Node* _camControlNode;
    cocos2d::Node* _camNode;
    cocos2d::EventListenerTouchOneByOne* _lis;
};

class Camera3DTestDemo : public CameraBaseTest
{
public:
    CREATE_FUNC(Camera3DTestDemo);
    Camera3DTestDemo(void);
    virtual ~Camera3DTestDemo(void);

    virtual void onEnter() override;
    virtual void onExit() override;
    // overrides
    virtual std::string title() const override;
    void addNewSpriteWithCoords(cocos2d::Vec3 p,std::string fileName,bool playAnimation=false,float scale=1.0f,bool bindCamera=false);

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

    void scaleCameraCallback(cocos2d::Ref* sender,float value);
    void rotateCameraCallback(cocos2d::Ref* sender,float value);
    void SwitchViewCallback(cocos2d::Ref* sender,CameraType cameraType);
    void updateCamera(float fDelta);
    void move3D(float elapsedTime);
    void updateState(float elapsedTime);
    bool isState(unsigned int state,unsigned int bit) const;
    void reachEndCallBack();
    
    bool onTouchesCommon(cocos2d::Touch* touch, cocos2d::Event* event, bool* touchProperty);
    bool onTouchesZoomOut(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchesZoomOutEnd(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onTouchesZoomIn(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchesZoomInEnd(cocos2d::Touch* touch, cocos2d::Event* event);
    
    bool onTouchesRotateLeft(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchesRotateLeftEnd(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onTouchesRotateRight(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchesRotateRightEnd(cocos2d::Touch* touch, cocos2d::Event* event);
protected:
    std::string    _title;
    cocos2d::Layer*         _layer3D;
    cocos2d::Sprite3D*      _sprite3D;
    cocos2d::Vec3           _targetPos;
    CameraType     _cameraType;
    cocos2d::MenuItem*      _incRot;
    cocos2d::MenuItem*      _decRot;
    unsigned int   _curState;
    cocos2d::Camera*      _camera;
    cocos2d::MoveTo* _moveAction;
    bool _bZoomOut;
    bool _bZoomIn;
    bool _bRotateLeft;
    bool _bRotateRight;
    cocos2d::Label* _RotateRightlabel;
    cocos2d::Label* _RotateLeftlabel;
    cocos2d::Label* _ZoomInlabel;
    cocos2d::Label* _ZoomOutlabel;
};

class CameraCullingDemo : public CameraBaseTest
{
public:
    CREATE_FUNC(CameraCullingDemo);
    CameraCullingDemo(void);
    virtual ~CameraCullingDemo(void);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual void update(float dt) override;
    
    // overrides
    virtual std::string title() const override;
    void reachEndCallBack();
    void switchViewCallback(cocos2d::Ref* sender);
    void addSpriteCallback(cocos2d::Ref* sender);
    void delSpriteCallback(cocos2d::Ref* sender);

    void drawCameraFrustum();
    
protected:
    cocos2d::Label*                  _labelSprite3DCount;
    cocos2d::Layer*                  _layer3D;
    std::vector<cocos2d::Sprite3D*>  _objects;
    CameraType                       _cameraType;
    cocos2d::Camera*                 _cameraFirst;
    cocos2d::Camera*                 _cameraThird;
    cocos2d::MoveBy*                 _moveAction;
    cocos2d::DrawNode3D*             _drawAABB;
    cocos2d::DrawNode3D*             _drawFrustum;
    int                     _row;
};

class CameraArcBallDemo : public CameraBaseTest
{
public:
    CREATE_FUNC(CameraArcBallDemo);
    CameraArcBallDemo(void);
    virtual ~CameraArcBallDemo(void);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual void update(float dt) override;
    
    // overrides
    virtual std::string title() const override;

    void switchOperateCallback(cocos2d::Ref* sender);
    void switchTargetCallback(cocos2d::Ref* sender);
    void onTouchsMoved(const std::vector<cocos2d::Touch*> &touchs, cocos2d::Event *event);
    void updateCameraTransform();
    void calculateArcBall( cocos2d::Vec3 & axis, float & angle, float p1x, float p1y, float p2x, float p2y );//calculate  rotation quaternion parameters
    float projectToSphere( float r, float x, float y );//points on the screen project to arc ball

protected:
    cocos2d::Layer*                  _layer3D;
    CameraType                       _cameraType;
    cocos2d::Camera*                 _camera;
    cocos2d::DrawNode3D*             _drawGrid;
    cocos2d::Quaternion              _rotationQuat;      //rotation Quaternion
    float                            _radius;            //arc ball radius
    float                            _distanceZ;
    OperateCamType                   _operate;           //switch rotate or zoom
    cocos2d::Vec3                    _center;            //camera look target
    int                              _target;            //switch camera look target
    cocos2d::Sprite3D*               _sprite3D1;
    cocos2d::Sprite3D*               _sprite3D2;
};

class FogTestDemo : public CameraBaseTest
{
public:
    CREATE_FUNC(FogTestDemo);
    FogTestDemo(void);
    virtual ~FogTestDemo(void);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual void update(float dt) override;
    
    // overrides
    virtual std::string title() const override;

    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

    void switchTypeCallback(cocos2d::Ref* sender,int type);
    
protected:
    cocos2d::Layer*                  _layer3D;
    CameraType              _cameraType;
    cocos2d::Camera*                 _camera;
    cocos2d::Sprite3D*               _sprite3D1;
    cocos2d::Sprite3D*               _sprite3D2;
    cocos2d::GLProgram*              _shader;
    cocos2d::GLProgramState*         _state;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    cocos2d::EventListenerCustom* _backToForegroundListener;
#endif
};

class CameraFrameBufferTest : public CameraBaseTest
{
public:
    CREATE_FUNC(CameraFrameBufferTest);
    CameraFrameBufferTest(void);
    virtual ~CameraFrameBufferTest(void);
    // overrides
    virtual std::string title() const override;
    
    virtual void onEnter() override;
};

class BackgroundColorBrushTest : public CameraBaseTest
{
public:
    CREATE_FUNC(BackgroundColorBrushTest);
    BackgroundColorBrushTest(void);
    virtual ~BackgroundColorBrushTest(void);
    
    // overrides
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    virtual void onEnter() override;
};

#endif
