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
    CREATE_FUNC(ActionManual);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionMove : public ActionsDemo
{
public:
    CREATE_FUNC(ActionMove);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionScale : public ActionsDemo
{
public:
    CREATE_FUNC(ActionScale);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionSkew : public ActionsDemo
{
public:
    CREATE_FUNC(ActionSkew);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionRotationalSkew : public ActionsDemo
{
public:
    CREATE_FUNC(ActionRotationalSkew);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionRotationalSkewVSStandardSkew : public ActionsDemo
{
public:
    CREATE_FUNC(ActionRotationalSkewVSStandardSkew);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionSkewRotateScale : public ActionsDemo
{
public:
    CREATE_FUNC(ActionSkewRotateScale);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionRotate : public ActionsDemo
{
public:
    CREATE_FUNC(ActionRotate);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionJump : public ActionsDemo
{
public:
    CREATE_FUNC(ActionJump);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionBezier : public ActionsDemo
{
public:
    CREATE_FUNC(ActionBezier);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionBlink : public ActionsDemo
{
public:
    CREATE_FUNC(ActionBlink);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionFade : public ActionsDemo
{
public:
    CREATE_FUNC(ActionFade);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionTint : public ActionsDemo
{
public:
    CREATE_FUNC(ActionTint);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionAnimate : public ActionsDemo
{
public:
    CREATE_FUNC(ActionAnimate);

    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();
};

class ActionSequence : public ActionsDemo
{
public:
    CREATE_FUNC(ActionSequence);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionSequence2 : public ActionsDemo
{
public:
    CREATE_FUNC(ActionSequence2);

    virtual void onEnter();
    virtual std::string subtitle();

    void callback1();
    void callback2(Node* sender);
    void callback3(Node* sender, long data);
};

class ActionSpawn : public ActionsDemo
{
public:
    CREATE_FUNC(ActionSpawn);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionReverse : public ActionsDemo
{
public:
    CREATE_FUNC(ActionReverse);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionRepeat : public ActionsDemo
{
public:
    CREATE_FUNC(ActionRepeat);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionDelayTime : public ActionsDemo
{
public:
    CREATE_FUNC(ActionDelayTime);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionReverseSequence : public ActionsDemo
{
public:
    CREATE_FUNC(ActionReverseSequence);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionReverseSequence2 : public ActionsDemo
{
public:
    CREATE_FUNC(ActionReverseSequence2);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionOrbit : public ActionsDemo
{
public:
    CREATE_FUNC(ActionOrbit);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionRemoveSelf : public ActionsDemo
{
public:
    CREATE_FUNC(ActionRemoveSelf);

	virtual void onEnter();
	virtual std::string subtitle();
};

class ActionRepeatForever : public ActionsDemo
{
public:
    CREATE_FUNC(ActionRepeatForever);

    virtual void onEnter();
    virtual std::string subtitle();

    void repeatForever(Node* pTarget);
};

class ActionRotateToRepeat : public ActionsDemo
{
public:
    CREATE_FUNC(ActionRotateToRepeat);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionRotateJerk : public ActionsDemo
{
public:
    CREATE_FUNC(ActionRotateJerk);

    virtual void onEnter();
    virtual std::string subtitle();
};

class ActionCallFuncN : public ActionsDemo
{
public:
    CREATE_FUNC(ActionCallFuncN);

    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    void callback(Node* sender);
};

class ActionCallFuncND : public ActionsDemo
{
public:
    CREATE_FUNC(ActionCallFuncND);

    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    void doRemoveFromParentAndCleanup(Node* sender, bool cleanup);
};

class ActionCallFuncO : public ActionsDemo
{
public:
    CREATE_FUNC(ActionCallFuncO);

    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    void callback(Node* object, bool cleanup);
};

class ActionCallFunction : public ActionsDemo
{
public:
    CREATE_FUNC(ActionCallFunction);

    virtual void onEnter();
    virtual std::string subtitle();

    void callback1();
    void callback2(Node* pTarget);
    void callback3(Node* pTarget, long data);
};


class ActionFollow : public ActionsDemo
{
public:
    CREATE_FUNC(ActionFollow);

    virtual void onEnter();
    virtual void draw();
    virtual std::string subtitle();
};

class ActionTargeted : public ActionsDemo
{
public:
    CREATE_FUNC(ActionTargeted);

    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class ActionTargetedReverse : public ActionsDemo
{
public:
    CREATE_FUNC(ActionTargetedReverse);

    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class ActionStacked : public ActionsDemo
{
public:
    CREATE_FUNC(ActionStacked);

    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    virtual void addNewSpriteWithCoords(Point p);
    virtual void runActionsInSprite(Sprite* sprite);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
};

class ActionMoveStacked : public ActionStacked
{
public:
    CREATE_FUNC(ActionMoveStacked);

    virtual std::string title();
    virtual void runActionsInSprite(Sprite* sprite);
};

class ActionMoveJumpStacked : public ActionStacked
{
public:
    CREATE_FUNC(ActionMoveJumpStacked);

    virtual std::string title();
    virtual void runActionsInSprite(Sprite* sprite);
};

class ActionMoveBezierStacked : public ActionStacked
{
public:
    CREATE_FUNC(ActionMoveBezierStacked);

    virtual std::string title();
    virtual void runActionsInSprite(Sprite* sprite);
};

class ActionCatmullRomStacked : public ActionsDemo
{
public:
    CREATE_FUNC(ActionCatmullRomStacked);

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
    CREATE_FUNC(ActionCardinalSplineStacked);

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
    CREATE_FUNC(Issue1305);

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
    CREATE_FUNC(Issue1305_2);

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
    CREATE_FUNC(Issue1288);

    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class Issue1288_2 : public ActionsDemo
{
public:
    CREATE_FUNC(Issue1288_2);

    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class Issue1327 : public ActionsDemo
{
public:
    CREATE_FUNC(Issue1327);

    virtual void onEnter();
    virtual std::string subtitle();
    virtual std::string title();
    void logSprRotation(Sprite* sender);
};

class Issue1398 : public ActionsDemo
{
public:
    CREATE_FUNC(Issue1398);

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
    CREATE_FUNC(ActionCatmullRom);

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
    CREATE_FUNC(ActionCardinalSpline);

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
    CREATE_FUNC(PauseResumeActions);

    PauseResumeActions();
    virtual ~PauseResumeActions();
    virtual void onEnter();
    virtual std::string subtitle();
    virtual std::string title();
    
    void pause(float dt);
    void resume(float dt);
private:
    Vector<Node*> _pausedTargets;
};

#endif
