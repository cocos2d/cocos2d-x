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

#ifndef _SPRITE3D_TEST_H_
#define _SPRITE3D_TEST_H_

#include "BaseTest.h"
#include <string>

namespace cocos2d {
    class Animate3D;
    class Sprite3D;
    class Delay;
    class Ray;
    class DrawNode3D;
    class GLProgramState;
}

DEFINE_TEST_SUITE(Sprite3DTests);

class Sprite3DTestDemo : public TestCase
{
public:
    // overrides
    virtual std::string title() const override;
};

class Sprite3DForceDepthTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DForceDepthTest);
    Sprite3DForceDepthTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class Sprite3DEmptyTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DEmptyTest);
    Sprite3DEmptyTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class Sprite3DBasicTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DBasicTest);
    Sprite3DBasicTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void addNewSpriteWithCoords(cocos2d::Vec2 p);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
};

class Sprite3DUVAnimationTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DUVAnimationTest);
    Sprite3DUVAnimationTest();
    virtual ~Sprite3DUVAnimationTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
protected:
    void cylinderUpdate(float dt);
    
    float _cylinder_texture_offset;
    float _shining_duraion;
    cocos2d::GLProgramState * _state;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    cocos2d::EventListenerCustom* _backToForegroundListener;
#endif
};

class Sprite3DFakeShadowTest : public Sprite3DTestDemo
{
public:
    enum State
    {
        State_None = 0,
        State_Idle = 0x01,
        State_Move = 0x02,
        State_Rotate = 0x04
    };
    CREATE_FUNC(Sprite3DFakeShadowTest);
    Sprite3DFakeShadowTest();
    virtual ~Sprite3DFakeShadowTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void Move(cocos2d::Ref* sender,int value);
    void updateCamera(float fDelta);
    void move3D(float elapsedTime);
    void updateState(float elapsedTime);
    bool isState(unsigned int state,unsigned int bit) const;
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
private:
    cocos2d::Camera * _camera;
    cocos2d::Vec3 _targetPos;
    unsigned int   _curState;
    cocos2d::Sprite3D * _plane;
    cocos2d::Sprite3D * _orc;
    cocos2d::GLProgramState * _state;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    cocos2d::EventListenerCustom* _backToForegroundListener;
#endif
};

class Sprite3DLightMapTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DLightMapTest);
    Sprite3DLightMapTest();
    virtual ~Sprite3DLightMapTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
private:
    cocos2d::Camera * _camera;
};

class Sprite3DBasicToonShaderTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DBasicToonShaderTest);
    Sprite3DBasicToonShaderTest();
    virtual ~Sprite3DBasicToonShaderTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
protected:
    cocos2d::GLProgramState * _state;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    cocos2d::EventListenerCustom* _backToForegroundListener;
#endif

};
class EffectSprite3D;

class Effect3D : public cocos2d::Ref
{
public:
    virtual void draw(const cocos2d::Mat4 &transform) = 0;
    virtual void setTarget(EffectSprite3D *sprite) = 0;
protected:
    Effect3D() : _glProgramState(nullptr) {}
    virtual ~Effect3D()
    {
        CC_SAFE_RELEASE(_glProgramState);
    }
protected:
    cocos2d::GLProgramState* _glProgramState;
};

class Effect3DOutline: public Effect3D
{
public:
    static Effect3DOutline* create();
    
    void setOutlineColor(const cocos2d::Vec3& color);
    
    void setOutlineWidth(float width);
    
    virtual void draw(const cocos2d::Mat4 &transform) override;
    virtual void setTarget(EffectSprite3D *sprite) override;
protected:
    
    Effect3DOutline();
    virtual ~Effect3DOutline();
    
    bool init();
    
    cocos2d::Vec3 _outlineColor;
    float _outlineWidth;
    //weak reference
    EffectSprite3D* _sprite;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    cocos2d::EventListenerCustom* _backToForegroundListener;
#endif
    
protected:
    static const std::string _vertShaderFile;
    static const std::string _fragShaderFile;
    static const std::string _keyInGLProgramCache;
    
    static const std::string _vertSkinnedShaderFile;
    static const std::string _fragSkinnedShaderFile;
    static const std::string _keySkinnedInGLProgramCache;
    
    static cocos2d::GLProgram* getOrCreateProgram(bool isSkinned = false);
};

class Sprite3DHitTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DHitTest);
    Sprite3DHitTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class EffectSprite3D : public cocos2d::Sprite3D
{
public:
    static EffectSprite3D* createFromObjFileAndTexture(const std::string& objFilePath, const std::string& textureFilePath);
    static EffectSprite3D* create(const std::string& path);
    
    void setEffect3D(Effect3D* effect);
    void addEffect(Effect3DOutline* effect, ssize_t order);
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
protected:
    EffectSprite3D();
    virtual ~EffectSprite3D();
    
    std::vector<std::tuple<ssize_t,Effect3D*, cocos2d::CustomCommand>> _effects;
    Effect3D* _defaultEffect;
    cocos2d::CustomCommand _command;
};

class Sprite3DEffectTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DEffectTest);
    Sprite3DEffectTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void addNewSpriteWithCoords(cocos2d::Vec2 p);
    
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
};

class AsyncLoadSprite3DTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(AsyncLoadSprite3DTest);
    AsyncLoadSprite3DTest();
    virtual ~AsyncLoadSprite3DTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void menuCallback_asyncLoadSprite(cocos2d::Ref* sender);
    
    void asyncLoad_Callback(cocos2d::Sprite3D* sprite, void* param);
    
protected:
    std::vector<std::string> _paths; //model paths to be loaded
};

class Sprite3DWithSkinTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DWithSkinTest);
    Sprite3DWithSkinTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void addNewSpriteWithCoords(cocos2d::Vec2 p);
    
    void switchAnimationQualityCallback(cocos2d::Ref* sender);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    std::string getAnimationQualityMessage() const;
private:
    std::vector<cocos2d::Sprite3D*> _sprits;
    int _animateQuality;
    cocos2d::MenuItemFont* _menuItem;
};

class Sprite3DWithSkinOutlineTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DWithSkinOutlineTest);
    Sprite3DWithSkinOutlineTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void addNewSpriteWithCoords(cocos2d::Vec2 p);
    
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
};

class Animate3DTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Animate3DTest);
    Animate3DTest();
    ~Animate3DTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    virtual void update(float dt) override;
    
protected:
    void addSprite3D();
    
    enum class State
    {
        SWIMMING,
        SWIMMING_TO_HURT,
        HURT,
        HURT_TO_SWIMMING,
    };
    
    void reachEndCallBack();
    
    void renewCallBack();
    
    cocos2d::Sprite3D* _sprite;
    
    cocos2d::Action* _swim;
    cocos2d::Animate3D* _hurt;

    float _elapseTransTime;
    
    State   _state;
    
    cocos2d::MoveTo* _moveAction;
};

class AttachmentTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(AttachmentTest);
    AttachmentTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    void addNewSpriteWithCoords(cocos2d::Vec2 p);
    
protected:
    bool _hasWeapon;
    cocos2d::Sprite3D* _sprite;
};

class Sprite3DReskinTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DReskinTest);
    Sprite3DReskinTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void addNewSpriteWithCoords(cocos2d::Vec2 p);
    
    void menuCallback_reSkin(cocos2d::Ref* sender);
protected:
    void applyCurSkin();
    
    enum class SkinType
    {
        UPPER_BODY = 0,
        PANTS,
        SHOES,
        HAIR,
        FACE,
        HAND,
        GLASSES,
        MAX_TYPE,
    };
    
    std::vector<std::string> _skins[(int)SkinType::MAX_TYPE]; //all skins
    int                      _curSkin[(int)SkinType::MAX_TYPE]; //current skin index
    cocos2d::Sprite3D* _sprite;
};
class Sprite3DWithOBBPerformanceTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DWithOBBPerformanceTest);
    Sprite3DWithOBBPerformanceTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void update(float dt) override;
    void addNewOBBWithCoords(cocos2d::Vec2 p);
    void addNewSpriteWithCoords(cocos2d::Vec2 p);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void addOBBCallback(cocos2d::Ref* sender);
    void delOBBCallback(cocos2d::Ref* sender);
    void addOBBWithCount(float value);
    void delOBBWithCount(float value);
protected:
    cocos2d::Sprite3D*        _sprite;
    std::vector<cocos2d::OBB>          _obb;
    cocos2d::DrawNode3D*               _drawOBB;
    cocos2d::Label*                    _labelCubeCount;
    cocos2d::MoveTo*                   _moveAction;
    cocos2d::OBB                       _obbt;
    cocos2d::DrawNode3D*               _drawDebug;
    bool                      _hasCollider;
    std::set<int>             _intersetList;
    void initDrawBox();
    void reachEndCallBack();
    
    void unproject(const cocos2d::Mat4& viewProjection, const cocos2d::Size* viewport, cocos2d::Vec3* src, cocos2d::Vec3* dst);
    void calculateRayByLocationInView(cocos2d::Ray* ray, const cocos2d::Vec2& location);
};

class Sprite3DMirrorTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DMirrorTest);
    Sprite3DMirrorTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void addNewSpriteWithCoords(cocos2d::Vec2 p);
    
protected:
    bool _hasWeapon;
    cocos2d::Sprite3D* _sprite;
    cocos2d::Sprite3D* _mirrorSprite;
};

class QuaternionTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(QuaternionTest);
    QuaternionTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void addNewSpriteWithCoords(cocos2d::Vec2 p);
    virtual void update(float delta) override;
    
protected:
    cocos2d::Sprite3D* _sprite;
    float              _arcSpeed;
    float              _radius;
    float              _accAngle;
};

// 3d + 2d use case
class UseCaseSprite3D : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(UseCaseSprite3D);
    UseCaseSprite3D();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    virtual void update(float delta) override;
    
    void menuCallback_Message(cocos2d::Ref* sender);
    
protected:
    
    void switchCase();
    
    enum class USECASE{
        _3D_WITH_2D,
        _UI_3D_UI,
        MAX_CASE_NUM,
    };
    cocos2d::Label*      _label;
    int                  _caseIdx; // use case index
    std::string          _useCaseTitles[(int)USECASE::MAX_CASE_NUM];
};

// node animation test, cocos2d-x supports both skeletal animation and node animation
class NodeAnimationTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(NodeAnimationTest);
    NodeAnimationTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void addNewSpriteWithCoords(cocos2d::Vec2 p);
protected:
    std::vector<cocos2d::Sprite3D*> _sprites;
    int _vectorIndex;
};

namespace cocos2d
{
class TextureCube;
class Skybox;
}
class Sprite3DCubeMapTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DCubeMapTest);
    Sprite3DCubeMapTest();
    ~Sprite3DCubeMapTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void addNewSpriteWithCoords(cocos2d::Vec2);

    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

protected:
    cocos2d::TextureCube* _textureCube;
    cocos2d::Skybox* _skyBox;
    cocos2d::Sprite3D* _teapot;
    cocos2d::Camera *_camera;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    cocos2d::EventListenerCustom* _backToForegroundListener;
#endif
};

/// issue 9767 setGLProgram
class Issue9767 : public Sprite3DTestDemo
{
    enum class ShaderType
    {
        SHADER_TEX,
        SHADER_COLOR,
    };
public:
    CREATE_FUNC(Issue9767);
    Issue9767();
    ~Issue9767();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void menuCallback_SwitchShader(cocos2d::Ref* sender);
    
protected:
    ShaderType          _shaderType;
    cocos2d::Sprite3D*  _sprite;
};

/// Clipping Sprite3D
class Sprite3DClippingTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DClippingTest);
    Sprite3DClippingTest();
    ~Sprite3DClippingTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class Sprite3DTestMeshLight : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DTestMeshLight);
    Sprite3DTestMeshLight();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    cocos2d::Sprite3D* _sprite;
};

#endif
