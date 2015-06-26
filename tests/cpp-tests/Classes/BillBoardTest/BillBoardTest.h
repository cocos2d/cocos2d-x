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

#ifndef _BILLBOARD_TEST_H_
#define _BILLBOARD_TEST_H_

#include "../BaseTest.h"
#include <string>

namespace cocos2d {
    class BillBoard;
    class Camera;
}

class BillBoardRotationTest : public TestCase
{
public:
    CREATE_FUNC(BillBoardRotationTest);
    BillBoardRotationTest();
    virtual ~BillBoardRotationTest(void);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
protected:
};

class BillBoardTest : public TestCase
{
public:
    virtual ~BillBoardTest(void);
    CREATE_FUNC(BillBoardTest);
    BillBoardTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void update(float dt) override;
    void addNewBillBoradWithCoords(cocos2d::Vec3 p);
    void addNewAniBillBoradWithCoords(cocos2d::Vec3 p);
    void rotateCameraCallback(cocos2d::Ref* sender,float value);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    void menuCallback_orientedPoint(cocos2d::Ref* sender);
    void menuCallback_orientedPlane(cocos2d::Ref* sender);
    
protected:
    cocos2d::Camera*           _camera;
    cocos2d::Layer*            _layerBillBorad;

    std::vector<cocos2d::BillBoard*> _billboards;
};

DEFINE_TEST_SUITE(BillBoardTests);

#endif
