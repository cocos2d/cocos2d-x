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

#include "../testBasic.h"
#include "../BaseTest.h"
#include <string>

namespace cocos2d {
    class BillBoard;
    class Camera;
}



class BillBoardTest : public BaseTest
{
public:
    virtual ~BillBoardTest(void);
    CREATE_FUNC(BillBoardTest);
    BillBoardTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void update(float dt) override;
    void addNewBillBoradWithCoords(Vec3 p);
    void addNewAniBillBoradWithCoords(Vec3 p);
    void rotateCameraCallback(Ref* sender,float value);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    
    void menuCallback_orientedPoint(Ref* sender);
    void menuCallback_orientedPlane(Ref* sender);

protected:
    Camera*           _camera;
    Layer*            _layerBillBorad;

    std::vector<BillBoard*> _billboards;
};

class BillBoardTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
