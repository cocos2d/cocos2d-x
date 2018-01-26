#ifndef _TOUCHES_TEST__H_
#define _TOUCHES_TEST__H_

#include "../BaseTest.h"


DEFINE_TEST_SUITE(TouchesTests);

class PongScene : public TestCase
{
public:
    CREATE_FUNC(PongScene);
    
    virtual bool init() override;
};

class Ball;
class Paddle;
class PongLayer : public cocos2d::Layer
{
private:
    Ball*       _ball;
    cocos2d::Vector<Paddle*>    _paddles;
    cocos2d::Vec2     _ballStartingVelocity; 
public:
    CREATE_FUNC(PongLayer);
    PongLayer();
    ~PongLayer();

    void resetAndScoreBallForPlayer(int player);
    void doStep(float delta);
};

class ForceTouchTest : public TestCase
{
public:
    CREATE_FUNC(ForceTouchTest);
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
protected:
    ForceTouchTest();
    virtual ~ForceTouchTest();

    cocos2d::Label * _infoLabel;
};

#endif
