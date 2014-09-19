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

#include "../testBasic.h"
#include "../BaseTest.h"
#include <string>

namespace cocos2d {
    class Animate3D;
    class Sprite3D;
    class Delay;
    class Ray;
    class DrawNode3D;
}

class Sprite3DTestDemo : public BaseTest
{
public:
    Sprite3DTestDemo(void);
    virtual ~Sprite3DTestDemo(void);
    
    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
    
    // overrides
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;

protected:
    std::string    _title;
};

class Sprite3DBasicTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DBasicTest);
    Sprite3DBasicTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void addNewSpriteWithCoords(Vec2 p);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
};

class EffectSprite3D;

class Effect3D : public Ref
{
public:
    virtual void draw(const Mat4 &transform) = 0;
    virtual void setTarget(EffectSprite3D *sprite) = 0;
protected:
    Effect3D() : _glProgramState(nullptr) {}
    virtual ~Effect3D()
    {
        CC_SAFE_RELEASE(_glProgramState);
    }
protected:
    GLProgramState* _glProgramState;
};

class Effect3DOutline: public Effect3D
{
public:
    static Effect3DOutline* create();
    
    void setOutlineColor(const Vec3& color);
    
    void setOutlineWidth(float width);
    
    virtual void draw(const Mat4 &transform) override;
    virtual void setTarget(EffectSprite3D *sprite) override;
protected:
    
    Effect3DOutline();
    virtual ~Effect3DOutline();
    
    bool init();
    
    Vec3 _outlineColor;
    float _outlineWidth;
    //weak reference
    EffectSprite3D* _sprite;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    EventListenerCustom* _backToForegroundListener;
#endif
    
protected:
    static const std::string _vertShaderFile;
    static const std::string _fragShaderFile;
    static const std::string _keyInGLProgramCache;
    
    static const std::string _vertSkinnedShaderFile;
    static const std::string _fragSkinnedShaderFile;
    static const std::string _keySkinnedInGLProgramCache;
    
    static GLProgram* getOrCreateProgram(bool isSkinned = false);
};

class Sprite3DHitTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DHitTest);
    Sprite3DHitTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class EffectSprite3D : public Sprite3D
{
public:
    static EffectSprite3D* createFromObjFileAndTexture(const std::string& objFilePath, const std::string& textureFilePath);
    static EffectSprite3D* create(const std::string& path);
    
    void setEffect3D(Effect3D* effect);
    void addEffect(Effect3DOutline* effect, ssize_t order);
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
protected:
    EffectSprite3D();
    virtual ~EffectSprite3D();
    
    std::vector<std::tuple<ssize_t,Effect3D*,CustomCommand>> _effects;
    Effect3D* _defaultEffect;
    CustomCommand _command;
};

class Sprite3DEffectTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DEffectTest);
    Sprite3DEffectTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void addNewSpriteWithCoords(Vec2 p);
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
};

class Sprite3DWithSkinTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DWithSkinTest);
    Sprite3DWithSkinTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void addNewSpriteWithCoords(Vec2 p);
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
};

class Sprite3DWithSkinOutlineTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DWithSkinOutlineTest);
    Sprite3DWithSkinOutlineTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void addNewSpriteWithCoords(Vec2 p);
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
};

class Animate3DTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Animate3DTest);
    Animate3DTest();
    ~Animate3DTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    
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
    
    MoveTo* _moveAction;
};

class AttachmentTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(AttachmentTest);
    AttachmentTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    
    void addNewSpriteWithCoords(Vec2 p);
    
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
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    void addNewSpriteWithCoords(Vec2 p);
    void menuCallback_switchHair(Ref* sender);
    void menuCallback_switchGlasses(Ref* sender);
    void menuCallback_switchCoat(Ref* sender);
    void menuCallback_switchPants(Ref* sender);
    void menuCallback_switchShoes(Ref* sender);
protected:
    std::string  _girlPants[2];
    int _usePantsId;
    std::string  _girlUpperBody[2];
    int _useUpBodyId;
    std::string  _girlShoes[2];
    int _useShoesId;
    std::string  _girlHair[2];
    int _useHairId;
    cocos2d::Sprite3D* _sprite;
};
class Sprite3DWithOBBPerfromanceTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DWithOBBPerfromanceTest);
    Sprite3DWithOBBPerfromanceTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void update(float dt) override;
    void addNewOBBWithCoords(Vec2 p);
    void addNewSpriteWithCoords(Vec2 p);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    void addOBBCallback(Ref* sender);
    void delOBBCallback(Ref* sender);
    void addOBBWithCount(float value);
    void delOBBWithCount(float value);
protected:
    cocos2d::Sprite3D*        _sprite;
    std::vector<OBB>          _obb;
    DrawNode3D*               _drawOBB;
    Label*                    _labelCubeCount;
    MoveTo*                   _moveAction;
    OBB                       _obbt;
    DrawNode3D*               _drawDebug;
    bool                      _hasCollider;
    std::set<int>             _intersetList;
    void initDrawBox();
    void reachEndCallBack();
    
    void unproject(const Mat4& viewProjection, const Size* viewport, Vec3* src, Vec3* dst);
    void calculateRayByLocationInView(Ray* ray, const Vec2& location);
};

class Sprite3DMirrorTest : public Sprite3DTestDemo
{
public:
    CREATE_FUNC(Sprite3DMirrorTest);
    Sprite3DMirrorTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void addNewSpriteWithCoords(Vec2 p);
    
protected:
    bool _hasWeapon;
    cocos2d::Sprite3D* _sprite;
    cocos2d::Sprite3D* _mirrorSprite;
};

class Sprite3DTestScene : public TestScene
{
public:
    Sprite3DTestScene();
    virtual void runThisTest();
};

#endif
