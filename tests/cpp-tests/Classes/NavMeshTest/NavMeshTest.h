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

#include "../testBasic.h"
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
class NavMeshTestDemo : public TestCase
{
public:
    CREATE_FUNC(NavMeshTestDemo);
    NavMeshTestDemo(void);
    virtual ~NavMeshTestDemo(void);
    
    // overrides
    virtual bool init() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void update(float delta) override;
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

protected:

    void initScene();
    void createAgent(const cocos2d::Vec3 &pos);
    void createObstacle(const cocos2d::Vec3 &pos);
    void moveAgents(const cocos2d::Vec3 &des);
    void switchState();

protected:
    std::string    _title;
    cocos2d::Camera *_camera;
    std::vector<std::pair<cocos2d::NavMeshAgent *, cocos2d::Animate3D *> > _agents;
    float _angle;
    cocos2d::Label *_stateLabel;
	cocos2d::Label *_debugLabel;
};

#endif

#endif
