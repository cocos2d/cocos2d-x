//
// Created by NiTe Luo on 11/1/13.
//



#ifndef __NewRendererTest_H_
#define __NewRendererTest_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

class NewRendererTest : public Layer
{
public:
    NewRendererTest();
    ~NewRendererTest();

    void createSpriteTest();
    void createNewSpriteTest();
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);

protected:

};

class NewRendererTestScene : public TestScene
{
public:
    virtual void runThisTest();
};


#endif //__NewRendererTest_H_
