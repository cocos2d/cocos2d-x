/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "../testBasic.h"
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

class Camera3DTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class CameraBaseTest : public BaseTest
{
public:
    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
    
protected:
    BillBoard* bill1;
    BillBoard* bill2;
    Label* l1;
    Label* l2;
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

    Node* _camControlNode;
    Node* _camNode;
    EventListenerTouchOneByOne* _lis;
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
    void addNewSpriteWithCoords(Vec3 p,std::string fileName,bool playAnimation=false,float scale=1.0f,bool bindCamera=false);
    void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void scaleCameraCallback(Ref* sender,float value);
    void rotateCameraCallback(Ref* sender,float value);
    void SwitchViewCallback(Ref* sender,CameraType cameraType);
    void updateCamera(float fDelta);
    void move3D(float elapsedTime);
    void updateState(float elapsedTime);
    bool isState(unsigned int state,unsigned int bit) const;
    void reachEndCallBack();
    
    bool onTouchesZoomOut(Touch* touch, Event* event);
    void onTouchesZoomOutEnd(Touch* touch, Event* event);
    bool onTouchesZoomIn(Touch* touch, Event* event);
    void onTouchesZoomInEnd(Touch* touch, Event* event);
    
    bool onTouchesRotateLeft(Touch* touch, Event* event);
    void onTouchesRotateLeftEnd(Touch* touch, Event* event);
    bool onTouchesRotateRight(Touch* touch, Event* event);
    void onTouchesRotateRightEnd(Touch* touch, Event* event);
protected:
    std::string    _title;
    Layer*         _layer3D;
    Sprite3D*      _sprite3D;
    Vec3           _targetPos;
    CameraType     _cameraType;
    MenuItem*      _incRot;
    MenuItem*      _decRot;
    unsigned int   _curState;
    Camera*      _camera;
    MoveTo* _moveAction;
    bool _bZoomOut;
    bool _bZoomIn;
    bool _bRotateLeft;
    bool _bRotateRight;
    Label* _RotateRightlabel;
    Label* _RotateLeftlabel;
    Label* _ZoomInlabel;
    Label* _ZoomOutlabel;
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
    void switchViewCallback(Ref* sender);
    void addSpriteCallback(Ref* sender);
    void delSpriteCallback(Ref* sender);

    void drawCameraFrustum();
    
protected:
    Label*                  _labelSprite3DCount;
    Layer*                  _layer3D;
    std::vector<Sprite3D*>  _objects;
    CameraType              _cameraType;
    Camera*                 _cameraFirst;
    Camera*                 _cameraThird;
    MoveBy*                 _moveAction;
    DrawNode3D*             _drawAABB;
    DrawNode3D*             _drawFrustum;
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

    void switchOperateCallback(Ref* sender);
    void switchTargetCallback(Ref* sender);
    void onTouchsMoved(const std::vector<cocos2d::Touch*> &touchs, cocos2d::Event *event);
    void updateCameraTransform();
    void calculateArcBall( cocos2d::Vec3 & axis, float & angle, float p1x, float p1y, float p2x, float p2y );//calculate  rotation quaternion parameters
    float projectToSphere( float r, float x, float y );//points on the screen project to arc ball

protected:
    Layer*                  _layer3D;
    CameraType              _cameraType;
    Camera*                 _camera;
    DrawNode3D*             _drawGrid;
    Quaternion              _rotationQuat;      //rotation Quaternion
    float                   _radius;            //arc ball radius
    float                   _distanceZ;
    OperateCamType          _operate;           //switch rotate or zoom
    Vec3                    _center;            //camera look target
    int                     _target;            //switch camera look target
    Sprite3D*               _sprite3D1;
    Sprite3D*               _sprite3D2;
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

    void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);

    void switchTypeCallback(Ref* sender,int type);
    
protected:
    Layer*                  _layer3D;
    CameraType              _cameraType;
    Camera*                 _camera;
    Sprite3D*               _sprite3D1;
    Sprite3D*               _sprite3D2;
    GLProgram*              _shader;
    GLProgramState*         _state;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    EventListenerCustom* _backToForegroundListener;
#endif
};


#endif
