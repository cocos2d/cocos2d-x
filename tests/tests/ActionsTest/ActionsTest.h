#ifndef _ActionsTest_H_
#define _ActionsTest_H_

#include "../testBasic.h"
////----#include "cocos2d.h"

using namespace cocos2d;

enum
{
    ACTION_MANUAL_LAYER = 0,
    ACTION_MOVE_LAYER,
    ACTION_SCALE_LAYER,
    ACTION_ROTATE_LAYER,
	ACTION_SKEW_LAYER,
	ACTION_SKEWROTATE_LAYER,
    ACTION_JUMP_LAYER,
    ACTION_BEZIER_LAYER,
    ACTION_BLINK_LAYER,
    ACTION_FADE_LAYER,
    ACTION_TINT_LAYER,
    ACTION_ANIMATE_LAYER,
    ACTION_SEQUENCE_LAYER,
    ACTION_SEQUENCE2_LAYER,
    ACTION_SPAWN_LAYER,
    ACTION_REVERSE,
    ACTION_DELAYTIME_LAYER,
    ACTION_REPEAT_LAYER,
    ACTION_REPEATEFOREVER_LAYER,
    ACTION_ROTATETOREPEATE_LAYER,
    ACTION_ROTATEJERK_LAYER,
    ACTION_CALLFUNC_LAYER,
    ACTION_CALLFUNCND_LAYER,
    ACTION_REVERSESEQUENCE_LAYER,
    ACTION_REVERSESEQUENCE2_LAYER,
    ACTION_ORBIT_LAYER,
    ACTION_FLLOW_LAYER,
    ACTION_LAYER_COUNT,
};


// the class inherit from TestScene
// every Scene each test used must inherit from TestScene,
// make sure the test have the menu item for back to main menu
class ActionsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class ActionsDemo : public CCLayer
{
protected:
    CCSprite*	m_grossini;
    CCSprite*	m_tamara;
    CCSprite*	m_kathia;public:
    virtual void onEnter();
    virtual void onExit();

    void centerSprites(unsigned int numberOfSprites);
    void alignSpritesLeft(unsigned int numberOfSprites);
    virtual std::string title();
    virtual std::string subtitle();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
};

class ActionManual : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionMove : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionScale : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionSkew : public ActionsDemo
{
	virtual void onEnter();
	virtual std::string subtitle();
};

class ActionSkewRotateScale : public ActionsDemo
{
	virtual void onEnter();
	virtual std::string subtitle();
};

class ActionRotate : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionJump : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionBezier : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionBlink : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionFade : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionTint : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionAnimate : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionSequence : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionSequence2 : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();

    void callback1();
    void callback2(CCNode* sender);
    void callback3(CCNode* sender, void* data);
};

class ActionSpawn : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionReverse : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionRepeat : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionDelayTime : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionReverseSequence : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionReverseSequence2 : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionOrbit : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionRepeatForever : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();

    void repeatForever(CCNode* pTarget);
};

class ActionRotateToRepeat : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionRotateJerk : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionCallFunc : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();

    void callback1();
    void callback2(CCNode* pTarget);
    void callback3(CCNode* pTarget, void* data);
};

class ActionCallFuncND : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class ActionFollow : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

#endif
