#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../VisibleRect.h"
#include "../../testBasic.h"

#if ENABLE_PHYSICS_BOX2D_DETECT
#include "../../Box2DTestBed/GLES-Render.h"
#include "Box2D/Box2D.h"
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
#include "chipmunk.h"
#endif

class ArmatureTestScene : public TestScene
{
public: 
	ArmatureTestScene(bool bPortrait = false);

	virtual void runThisTest();

	// The CallBack for back to the main menu scene
	virtual void MainMenuCallback(CCObject* pSender);
};

enum {
	TEST_ASYNCHRONOUS_LOADING = 0,
    TEST_DIRECT_LOADING,
	TEST_COCOSTUDIO_WITH_SKELETON,
	TEST_DRAGON_BONES_2_0,
	TEST_PERFORMANCE,
    TEST_PERFORMANCE_BATCHNODE,
	TEST_CHANGE_ZORDER,
	TEST_ANIMATION_EVENT,
    TEST_FRAME_EVENT,
	TEST_PARTICLE_DISPLAY,
	TEST_USE_DIFFERENT_PICTURE,
	TEST_COLLIDER_DETECTOR,
	TEST_BOUDINGBOX,
	TEST_ANCHORPOINT,
	TEST_ARMATURE_NESTING,
    TEST_ARMATURE_NESTING_2,
    TEST_PLAY_SEVERAL_MOVEMENT,
    TEST_EASING,
    TEST_CHANGE_ANIMATION_INTERNAL,
	TEST_DIRECT_FROM_BINARY,

	TEST_LAYER_COUNT
};

class ArmatureTestLayer : public CCLayer
{
public:
	virtual void onEnter();
	virtual void onExit();

	virtual std::string title();
	virtual std::string subtitle();

	virtual void restartCallback(CCObject* pSender);
	virtual void nextCallback(CCObject* pSender);
	virtual void backCallback(CCObject* pSender);

	virtual void draw();

protected:
	CCMenuItemImage *restartItem;
	CCMenuItemImage *nextItem;
	CCMenuItemImage *backItem;
};


class TestAsynchronousLoading : public ArmatureTestLayer
{
public:
	virtual void onEnter();
	virtual std::string title();
	virtual std::string subtitle();
    virtual void restartCallback(CCObject* pSender);

	void dataLoaded(float percent);
};

class TestDirectLoading : public ArmatureTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class TestCSWithSkeleton : public ArmatureTestLayer
{
	virtual void onEnter();
	virtual std::string title();
};


class TestDragonBones20 : public ArmatureTestLayer
{
public:
	virtual void onEnter();
	virtual std::string title();
};


class TestPerformance : public ArmatureTestLayer
{
public:
	~TestPerformance();

	virtual void onEnter();
	virtual std::string title();
	virtual std::string subtitle();
    virtual void onIncrease(CCObject* pSender);
    virtual void onDecrease(CCObject* pSender);
	virtual void addArmature(int number);
    virtual void addArmatureToParent(cocos2d::extension::CCArmature *armature);
    virtual void removeArmatureFromParent(int tag);
    virtual void refreshTitile();

	int armatureCount;

	int frames;
	float times;
	float lastTimes;
	bool generated;
};

class TestPerformanceBatchNode : public TestPerformance
{
    virtual void onEnter();
    virtual std::string title();
    virtual void addArmatureToParent(cocos2d::extension::CCArmature *armature);
    virtual void removeArmatureFromParent(int tag);

    cocos2d::extension::CCBatchNode *batchNode;
};


class TestChangeZorder : public ArmatureTestLayer
{
	virtual void onEnter();
	virtual std::string title();
	void changeZorder(float dt);

	int currentTag;
};


class TestAnimationEvent : public ArmatureTestLayer
{
public:

	virtual void onEnter();
	virtual std::string title();
	void animationEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
	void callback1();
	void callback2();

	cocos2d::extension::CCArmature *armature;
};


class TestFrameEvent : public ArmatureTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    void onFrameEvent(cocos2d::extension::CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);
    void checkAction(float dt);
};


class TestUseMutiplePicture : public ArmatureTestLayer
{
	virtual void onEnter();
	virtual void onExit();
	virtual std::string title();
	virtual std::string subtitle();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher();

	int displayIndex;
	cocos2d::extension::CCArmature *armature;
};

class TestParticleDisplay : public ArmatureTestLayer
{
	virtual void onEnter();
	virtual void onExit();
	virtual std::string title();
	virtual std::string subtitle();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher();

	int animationID;
	cocos2d::extension::CCArmature *armature;
};




#if ENABLE_PHYSICS_BOX2D_DETECT

class ContactListener;

class TestColliderDetector : public ArmatureTestLayer
{
public:
	~TestColliderDetector();

	virtual void onEnter();
	virtual void onExit();
	virtual std::string title();
	virtual void draw();
	virtual void update(float delta);

	void onFrameEvent(cocos2d::extension::CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);

	void initWorld();


	cocos2d::extension::CCArmature *armature;
	cocos2d::extension::CCArmature *armature2;

	cocos2d::extension::CCPhysicsSprite *bullet;

	b2World *world;
	ContactListener *listener;
	GLESDebugDraw *debugDraw;
};


#elif ENABLE_PHYSICS_CHIPMUNK_DETECT


class TestColliderDetector : public ArmatureTestLayer
{
public:
	~TestColliderDetector();

	virtual void onEnter();
	virtual void onExit();
	virtual std::string title();
	virtual void update(float delta);

	void onFrameEvent(cocos2d::extension::CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);

	void initWorld();


	cocos2d::extension::CCArmature *armature;
	cocos2d::extension::CCArmature *armature2;

	cocos2d::extension::CCPhysicsSprite *bullet;


	cpSpace *space;

	static int beginHit(cpArbiter *arb, cpSpace *space, void *unused);
	static void endHit(cpArbiter *arb, cpSpace *space, void *unused);

	void destroyCPBody(cpBody *body);
};
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
class TestColliderDetector : public ArmatureTestLayer
{
public:
    ~TestColliderDetector();

    virtual void onEnter();
    virtual std::string title();
    virtual void update(float delta);
    virtual void draw();

    void onFrameEvent(cocos2d::extension::CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);

    void initWorld() {};

    cocos2d::extension::CCArmature *armature;
    cocos2d::extension::CCArmature *armature2;

    cocos2d::CCSprite *bullet;
};
#endif





class TestBoundingBox : public ArmatureTestLayer
{
public:
	virtual void onEnter();
	virtual std::string title();
	virtual void draw();

	cocos2d::extension::CCArmature *armature;
	CCRect rect;
};

class TestAnchorPoint : public ArmatureTestLayer
{
public:
	virtual void onEnter();
	virtual std::string title();
};

class TestArmatureNesting : public ArmatureTestLayer
{
public:
	virtual void onEnter();
	virtual void onExit();
	virtual std::string title();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher();

	cocos2d::extension::CCArmature *armature;
	int weaponIndex;
};

class Hero : public cocos2d::extension::CCArmature
{
public:
    static Hero *create(const char *name);
    Hero();

    virtual void changeMount(cocos2d::extension::CCArmature *armature);
    virtual void playWithIndex(int index);

    CC_SYNTHESIZE(cocos2d::extension::CCArmature*, m_pMount, Mount);
    CC_SYNTHESIZE(cocos2d::CCLayer*, m_pLayer, Layer);
};

class TestArmatureNesting2 : public ArmatureTestLayer
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher();

    virtual void ChangeMountCallback(CCObject* pSender);
    virtual cocos2d::extension::CCArmature *createMount(const char *name, CCPoint position);

    Hero *hero;

    cocos2d::extension::CCArmature *horse;
    cocos2d::extension::CCArmature *horse2;
    cocos2d::extension::CCArmature *bear;


    bool touchedMenu;
};

class TestPlaySeveralMovement : public ArmatureTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class TestEasing : public ArmatureTestLayer
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher();

    virtual void updateSubTitle();

    cocos2d::extension::CCArmature *armature;
    int animationID;
};


class TestChangeAnimationInternal : public ArmatureTestLayer
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher();
};



#define BINARYFILECOUNT 6
class TestLoadFromBinary : public ArmatureTestLayer
{
public:
	virtual void onEnter();
	virtual void onExit();
	virtual std::string title();
	virtual std::string subtitle();

	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEnvent);
	virtual void registerWithTouchDispatcher();


	void dataLoaded(float percent);

private:
	cocos2d::extension::CCArmature *m_armature; // current armature
	static const char*  m_binaryFilesNames[BINARYFILECOUNT];
	static const char*  m_armatureNames[BINARYFILECOUNT];
	int m_armatureIndex;   // index of sync loaded armature, default -1 is none
};
#endif  // __HELLOWORLD_SCENE_H__