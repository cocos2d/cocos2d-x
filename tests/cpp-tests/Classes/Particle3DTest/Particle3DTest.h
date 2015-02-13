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

#ifndef _PARTICLE3D_TEST_H_
#define _PARTICLE3D_TEST_H_

#include "../testBasic.h"
#include "../BaseTest.h"
#include "Particle3D/CCParticleSystem3D.h"
#include <string>
class Particle3DTestDemo : public BaseTest
{
public:
    CREATE_FUNC(Particle3DTestDemo);
    Particle3DTestDemo(void);
    virtual ~Particle3DTestDemo(void);
    
    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
    
    // overrides
    virtual bool init() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void update(float delta) override;
    
    void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);

protected:
    std::string    _title;
    cocos2d::Camera *_camera;
    cocos2d::Label *_particleLab;
    float _angle;
};

class Particle3DAdvancedLodSystemDemo : public Particle3DTestDemo
{
public:

    CREATE_FUNC(Particle3DAdvancedLodSystemDemo);
    Particle3DAdvancedLodSystemDemo(){};
    virtual ~Particle3DAdvancedLodSystemDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;
};

class Particle3DBlackHoleDemo : public Particle3DTestDemo
{
public:

    CREATE_FUNC(Particle3DBlackHoleDemo);
    Particle3DBlackHoleDemo(){};
    virtual ~Particle3DBlackHoleDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;
};

class Particle3DHypnoDemo : public Particle3DTestDemo
{
public:

    CREATE_FUNC(Particle3DHypnoDemo);
    Particle3DHypnoDemo(){};
    virtual ~Particle3DHypnoDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;
};

class Particle3DTimeShiftDemo : public Particle3DTestDemo
{
public:

    CREATE_FUNC(Particle3DTimeShiftDemo);
    Particle3DTimeShiftDemo(){};
    virtual ~Particle3DTimeShiftDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;
};


class Particle3DUVAnimDemo : public Particle3DTestDemo
{
public:

    CREATE_FUNC(Particle3DUVAnimDemo);
    Particle3DUVAnimDemo(){};
    virtual ~Particle3DUVAnimDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;
};

class Particle3DFirePlaceDemo : public Particle3DTestDemo
{
public:

    CREATE_FUNC(Particle3DFirePlaceDemo);
    Particle3DFirePlaceDemo(){};
    virtual ~Particle3DFirePlaceDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;
};

class Particle3DLineStreakDemo : public Particle3DTestDemo
{
public:

    CREATE_FUNC(Particle3DLineStreakDemo);
    Particle3DLineStreakDemo(){};
    virtual ~Particle3DLineStreakDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;
};

class Particle3DElectricBeamSystemDemo : public Particle3DTestDemo
{
public:

    CREATE_FUNC(Particle3DElectricBeamSystemDemo);
    Particle3DElectricBeamSystemDemo(){};
    virtual ~Particle3DElectricBeamSystemDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;
};

class Particle3DExplosionBlueDemo : public Particle3DTestDemo
{
public:

    CREATE_FUNC(Particle3DExplosionBlueDemo);
    Particle3DExplosionBlueDemo(){};
    virtual ~Particle3DExplosionBlueDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;
};

class Particle3DTestScene : public TestScene
{
public:
    Particle3DTestScene(){};
    virtual void runThisTest();
};

#endif