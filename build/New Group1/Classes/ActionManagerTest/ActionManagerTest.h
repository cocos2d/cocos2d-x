/****************************************************************************
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

#ifndef _ACTION_MANAGER_TEST_H_
#define _ACTION_MANAGER_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ActionManagerTests);

class ActionManagerTest : public TestCase
{
protected:
    cocos2d::TextureAtlas* _atlas;

    std::string    _title;

public:
    ActionManagerTest();
    ~ActionManagerTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class CrashTest : public ActionManagerTest
{
public:
    CREATE_FUNC(CrashTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void removeThis();
};

class LogicTest : public ActionManagerTest
{
public:
    CREATE_FUNC(LogicTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void bugMe(Node* node);
};

class PauseTest : public ActionManagerTest
{
public:
    CREATE_FUNC(PauseTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void unpause(float dt);
};

class StopActionTest : public ActionManagerTest
{
public:
    CREATE_FUNC(StopActionTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void stopAction();
};

class StopAllActionsTest : public ActionManagerTest
{
public:
    CREATE_FUNC(StopAllActionsTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void stopAction(float time);
};

class ResumeTest : public ActionManagerTest
{
public:
    CREATE_FUNC(ResumeTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void resumeGrossini(float time);
};

class StopActionsByFlagsTest : public ActionManagerTest
{
public:
    CREATE_FUNC(StopActionsByFlagsTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void stopAction(float time);
protected:
    const unsigned int kMoveFlag = 0x01;
    const unsigned int kScaleFlag = 0x02;
    const unsigned int kRotateFlag = 0x04;
    const unsigned int kRepeatForeverFlag = 0x08; // You don't need this for the test, but it's for demonstration how to activate several flags on an action.
};

class Issue14050Test : public ActionManagerTest
{
public:
    CREATE_FUNC(Issue14050Test);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
protected:
};

#endif
