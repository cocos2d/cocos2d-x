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
#include <string>
#include "base/CCCamera.h"
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
    FreeCamera=0,
    FirstCamera=1,
    ThirdCamera=2,
};
class Camera3DTestDemo : public BaseTest
{
public:
    CREATE_FUNC(Camera3DTestDemo);
    Camera3DTestDemo(void);
    virtual ~Camera3DTestDemo(void);

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
    virtual void onEnter() override;
    virtual void onExit() override;
    // overrides
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
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
protected:
    std::string    _title;
    Layer*         _layer3D;
    Sprite3D*      _sprite3D;
    Vec3           _targetPos;
    CameraType     _cameraType;
    unsigned int   _curState;
    Camera*      _camera;
    MoveTo* _moveAction;
};
class Camera3DTestScene : public TestScene
{
public:
    virtual void runThisTest();
};
#endif
