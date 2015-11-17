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

#ifndef _COCOSSTUDIO3D_TEST_H_
#define _COCOSSTUDIO3D_TEST_H_

#include "../BaseTest.h"
#include <string>

DEFINE_TEST_SUITE(CocosStudio3DTests);

class CocosStudio3DTestDemo : public TestCase
{
public:
    CocosStudio3DTestDemo(void);
    virtual ~CocosStudio3DTestDemo(void);
    
    // overrides
    virtual std::string title() const override;
    virtual void onExit() override;
};

class CSNode3DTest : public CocosStudio3DTestDemo
{
public:
    CREATE_FUNC(CSNode3DTest);
    CSNode3DTest();
    virtual std::string title() const override;
};

class CSSprite3DTest : public CocosStudio3DTestDemo
{
public:
    CREATE_FUNC(CSSprite3DTest);
    CSSprite3DTest();
    virtual std::string title() const override;
};

class CSUserCameraTest : public CocosStudio3DTestDemo
{
public:
    CREATE_FUNC(CSUserCameraTest);
    CSUserCameraTest();
    virtual std::string title() const override;
};

class CSParticle3DTest : public CocosStudio3DTestDemo
{
public:
    CREATE_FUNC(CSParticle3DTest);
    CSParticle3DTest();
    virtual std::string title() const override;
};

class CSSceneSkyBoxTest : public CocosStudio3DTestDemo
{
private:
    cocos2d::Camera *_camera;
public:
    CREATE_FUNC(CSSceneSkyBoxTest);
    CSSceneSkyBoxTest();
    virtual std::string title() const override;
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
};

class CSSceneLight3DTest : public CocosStudio3DTestDemo
{
public:
    CREATE_FUNC(CSSceneLight3DTest);
    CSSceneLight3DTest();
    virtual std::string title() const override;
};


#endif
