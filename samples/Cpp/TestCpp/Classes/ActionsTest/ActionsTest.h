#ifndef _ActionsTest_H_
#define _ActionsTest_H_

#include "../testBasic.h"
#include "../BaseTest.h"
////----#include "cocos2d.h"

USING_NS_CC;


// the class inherit from TestScene
// every Scene each test used must inherit from TestScene,
// make sure the test have the menu item for back to main menu
class ActionsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class ActionsDemo : public BaseTest
{
protected:
    Sprite*    _grossini;
    Sprite*    _tamara;
    Sprite*    _kathia;
public:
    virtual void onEnter();
    virtual void onExit();

    void centerSprites(unsigned int numberOfSprites);
    void alignSpritesLeft(unsigned int numberOfSprites);
    virtual std::string title();
    virtual std::string subtitle();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
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
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionRotationalSkew : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionRotationalSkewVSStandardSkew : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionSkewRotateScale : public ActionsDemo
{
public:
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
    virtual void onExit();
    virtual std::string title();
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
    void callback2(Node* sender);
    void callback3(Node* sender, long data);
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

class ActionRemoveSelf : public ActionsDemo
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

    void repeatForever(Node* pTarget);
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

class ActionCallFuncN : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    void callback(Node* sender);
};

class ActionCallFuncND : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    void doRemoveFromParentAndCleanup(Node* sender, bool cleanup);
};

class ActionCallFuncO : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    void callback(Node* object, bool cleanup);
};

class ActionCallFunction : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();

    void callback1();
    void callback2(Node* pTarget);
    void callback3(Node* pTarget, long data);
};


class ActionFollow : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual void draw();
    virtual std::string subtitle();
};

class ActionTargeted : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class ActionStacked : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    virtual void addNewSpriteWithCoords(Point p);
    virtual void runActionsInSprite(Sprite* sprite);
    virtual void ccTouchesEnded(Set* touches, Event* event);
};

class ActionMoveStacked : public ActionStacked
{
public:
    virtual std::string title();
    virtual void runActionsInSprite(Sprite* sprite);
};

class ActionMoveJumpStacked : public ActionStacked
{
public:
    virtual std::string title();
    virtual void runActionsInSprite(Sprite* sprite);
};

class ActionMoveBezierStacked : public ActionStacked
{
public:
    virtual std::string title();
    virtual void runActionsInSprite(Sprite* sprite);
};

class ActionCatmullRomStacked : public ActionsDemo
{
public:
    virtual ~ActionCatmullRomStacked();
    virtual void draw();
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
private:
    PointArray* _array1;
    PointArray* _array2;
};

class ActionCardinalSplineStacked : public ActionsDemo
{
public:
    virtual ~ActionCardinalSplineStacked();
    virtual void draw();
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
private:
    PointArray* _array;
};

class Issue1305 : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual void onExit();
    void log(Node* sender);
    void addSprite(float dt);
    virtual std::string title();
    virtual std::string subtitle();
private:
    Sprite* _spriteTmp;
};

class Issue1305_2 : public ActionsDemo
{
public:
    virtual void onEnter();
    void printLog1();
    void printLog2();
    void printLog3();
    void printLog4();
    virtual std::string title();
    virtual std::string subtitle();
};

class Issue1288 : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class Issue1288_2 : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class Issue1327 : public ActionsDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
    virtual std::string title();
    void logSprRotation(Sprite* sender);
};

class Issue1398 : public ActionsDemo
{
public:
    void incrementInteger();
    void incrementIntegerCallback(void* data);
    virtual void onEnter();
    virtual std::string subtitle();
    virtual std::string title();
private:
    int _testInteger;
};

class ActionCatmullRom : public ActionsDemo
{
public:
    ~ActionCatmullRom();
    
    virtual void onEnter();
    virtual void draw();
    virtual std::string subtitle();
    virtual std::string title();
private:
    PointArray *_array1;
    PointArray *_array2;
};

class ActionCardinalSpline : public ActionsDemo
{
public:
    ~ActionCardinalSpline();
    
    virtual void onEnter();
    virtual void draw();
    virtual std::string subtitle();
    virtual std::string title();
private:
    PointArray *_array;
};

class PauseResumeActions : public ActionsDemo
{
public:
    PauseResumeActions();
    virtual ~PauseResumeActions();
    virtual void onEnter();
    virtual std::string subtitle();
    virtual std::string title();
    
    void pause(float dt);
    void resume(float dt);
private:
    Set *_pausedTargets;
};

#endif
