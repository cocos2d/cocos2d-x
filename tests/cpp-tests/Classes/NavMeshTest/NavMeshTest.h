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

#ifndef _NAVMESH_TEST_H_
#define _NAVMESH_TEST_H_

#include "../BaseTest.h"
#include "navmesh/CCNavMesh.h"
#include <string>

DEFINE_TEST_SUITE(NavMeshTests);

#if CC_USE_NAVMESH == 0
class NavMeshDisabled : public TestCase
{
public:
    CREATE_FUNC(NavMeshDisabled);

    virtual void onEnter() override;
};
#else

class NavMeshBaseTestDemo : public TestCase
{
public:
    CREATE_FUNC(NavMeshBaseTestDemo);
    NavMeshBaseTestDemo(void);
    virtual ~NavMeshBaseTestDemo(void);

    // overrides
    virtual bool init() override;
    virtual void update(float delta) override;
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

protected:

    void initScene();
    void createAgent(const cocos2d::Vec3 &pos);
    void createObstacle(const cocos2d::Vec3 &pos);
    void moveAgents(const cocos2d::Vec3 &des);
    virtual void touchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event){};
    virtual void touchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event){};
    virtual void touchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event){};

protected:
    cocos2d::Camera *_camera;
    float _angle;
    std::vector<std::pair<cocos2d::NavMeshAgent *, cocos2d::Animate3D *> > _agents;
    bool _needMoveAgents;
};

class NavMeshBasicTestDemo : public NavMeshBaseTestDemo
{
public:
    CREATE_FUNC(NavMeshBasicTestDemo);
    NavMeshBasicTestDemo(void);
    virtual ~NavMeshBasicTestDemo(void);
    
    // overrides
    virtual bool init() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    virtual void onEnter() override;
    
protected:

    virtual void touchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event){};
    virtual void touchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event){};
    virtual void touchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

protected:
    cocos2d::Label *_debugLabel;
};

class NavMeshAdvanceTestDemo : public NavMeshBaseTestDemo
{
public:
    CREATE_FUNC(NavMeshAdvanceTestDemo);
    NavMeshAdvanceTestDemo(void);
    virtual ~NavMeshAdvanceTestDemo(void);

    // overrides
    virtual bool init() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    virtual void onEnter() override;

protected:

    virtual void touchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event){};
    virtual void touchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event){};
    virtual void touchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

protected:
    cocos2d::Label *_obstacleLabel;
    cocos2d::Label *_agentLabel;
    cocos2d::Label *_debugLabel;
};

#endif

#endif
