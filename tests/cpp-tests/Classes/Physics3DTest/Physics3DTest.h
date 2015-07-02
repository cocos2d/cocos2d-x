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

#ifndef _PHYSICS3D_TEST_H_
#define _PHYSICS3D_TEST_H_

#include "../BaseTest.h"
#include <string>

namespace cocos2d {
    class Physics3DConstraint;
}

DEFINE_TEST_SUITE(Physics3DTests);

#if CC_USE_3D_PHYSICS == 0
class Physics3DDemoDisabled : public TestCase
{
public:
	CREATE_FUNC(Physics3DDemoDisabled);

	virtual void onEnter() override;
};
#else

class Physics3DTestDemo : public TestCase
{
public:
    CREATE_FUNC(Physics3DTestDemo);
    Physics3DTestDemo(void);
    virtual ~Physics3DTestDemo(void);
    
    // overrides
    virtual bool init() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void update(float delta) override;
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

protected:

    void shootBox(const cocos2d::Vec3 &des);

protected:
    std::string    _title;
    cocos2d::Camera *_camera;
    float _angle;
    bool _needShootBox;
};

class BasicPhysics3DDemo : public Physics3DTestDemo
{
public:

    CREATE_FUNC(BasicPhysics3DDemo);
    BasicPhysics3DDemo(){};
    virtual ~BasicPhysics3DDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;
};

class Physics3DConstraintDemo : public Physics3DTestDemo
{
public:
    
    CREATE_FUNC(Physics3DConstraintDemo);
    Physics3DConstraintDemo():_constraint(nullptr), _pickingDistance(0.f){};
    virtual ~Physics3DConstraintDemo(){};
    
    virtual std::string subtitle() const override;
    
    virtual bool init() override;
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event) override;
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event) override;
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event) override;
    
protected:
    cocos2d::Physics3DConstraint*     _constraint; //for picking
    float                             _pickingDistance; //picking distance
};

class Physics3DKinematicDemo : public Physics3DTestDemo
{
public:

    CREATE_FUNC(Physics3DKinematicDemo);
    Physics3DKinematicDemo(){};
    virtual ~Physics3DKinematicDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;
};

class Physics3DCollisionCallbackDemo : public Physics3DTestDemo
{
public:

    CREATE_FUNC(Physics3DCollisionCallbackDemo);
    Physics3DCollisionCallbackDemo(){};
    virtual ~Physics3DCollisionCallbackDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;
};

class Physics3DTerrainDemo : public Physics3DTestDemo
{
public:

    CREATE_FUNC(Physics3DTerrainDemo);
    Physics3DTerrainDemo(){};
    virtual ~Physics3DTerrainDemo(){};

    virtual std::string subtitle() const override;

    virtual bool init() override;

private:
};

#endif

#endif