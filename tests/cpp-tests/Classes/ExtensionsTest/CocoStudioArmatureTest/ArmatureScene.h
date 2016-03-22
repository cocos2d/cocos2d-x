#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "../../BaseTest.h"
#include "editor-support/cocostudio/CocoStudio.h"

#if ENABLE_PHYSICS_BOX2D_DETECT
#include "../../Box2DTestBed/GLES-Render.h"
#include "Box2D/Box2D.h"
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
#include "chipmunk.h"
#endif

class CocoStudioArmatureTests : public TestSuite
{
public:
    CocoStudioArmatureTests();
    ~CocoStudioArmatureTests();

private:

};

class ArmatureBaseTest : public TestCase
{
public:
	virtual std::string title() const override;
    virtual bool init() override;

protected:
};

class TestAsynchronousLoading : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestAsynchronousLoading);

	virtual void onEnter() override;
	virtual std::string title() const override;
	virtual std::string subtitle() const override;
    virtual void restartTestCallback(cocos2d::Ref* pSender) override;

	void dataLoaded(float percent);
};

class TestDirectLoading : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestDirectLoading);
    virtual void onEnter() override;
    virtual std::string title() const override;
};

class TestCSWithSkeleton : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestCSWithSkeleton);

	virtual void onEnter() override;
	virtual std::string title() const override;
};


class TestDragonBones20 : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestDragonBones20);

	virtual void onEnter() override;
	virtual std::string title() const override;
};


class TestPerformance : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestPerformance);

	~TestPerformance();

	virtual void onEnter() override;
	virtual std::string title() const override;
	virtual std::string subtitle() const override;
    virtual void onIncrease(cocos2d::Ref* pSender);
    virtual void onDecrease(cocos2d::Ref* pSender);
    virtual void addArmature(int number);
    virtual void addArmatureToParent(cocostudio::Armature *armature);
    virtual void removeArmatureFromParent(int tag);
    virtual void refreshTitle();

	int armatureCount;

	int frames;
	float times;
	float lastTimes;
	bool generated;
};

class TestPerformanceBatchNode : public TestPerformance
{
public:
    CREATE_FUNC(TestPerformanceBatchNode);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual void addArmatureToParent(cocostudio::Armature *armature)override;
    virtual void removeArmatureFromParent(int tag)override;

    cocostudio::BatchNode *batchNode;
};

class TestChangeZorder : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestChangeZorder);

	virtual void onEnter() override;
	virtual std::string title() const override;
	void changeZorder(float dt);

	int currentTag;
};


class TestAnimationEvent : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestAnimationEvent);

	virtual void onEnter() override;
	virtual std::string title() const override;
	void animationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);
	void callback1();
	void callback2();

	cocostudio::Armature *armature;
};


class TestFrameEvent : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestFrameEvent);

    virtual void onEnter() override;
    virtual std::string title() const override;
    void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
    void checkAction(float dt);
protected:
    cocos2d::NodeGrid* _gridNode;
};


class TestUseMutiplePicture : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestUseMutiplePicture);

	virtual void onEnter() override;
	virtual void onExit() override;
	virtual std::string title() const override;
	virtual std::string subtitle() const override;
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

	int displayIndex;
	cocostudio::Armature *armature;
};

class TestParticleDisplay : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestParticleDisplay);

	virtual void onEnter() override;
	virtual void onExit() override;
	virtual std::string title() const override;
	virtual std::string subtitle() const override;
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

	int animationID;
	cocostudio::Armature *armature;
};


#if ENABLE_PHYSICS_BOX2D_DETECT

class ContactListener;

class TestColliderDetector : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestColliderDetector);

	~TestColliderDetector();

	virtual void onEnter() override;
	virtual void onExit() override;
	virtual std::string title() const override;
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	virtual void update(float delta);

	void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	void initWorld();


	cocostudio::Armature *armature;
	cocostudio::Armature *armature2;

	cocos2d::extension::PhysicsSprite *bullet;

	b2World *world;
	ContactListener *listener;
	GLESDebugDraw *debugDraw;
};


#elif ENABLE_PHYSICS_CHIPMUNK_DETECT


class TestColliderDetector : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestColliderDetector);

	~TestColliderDetector();

	virtual void onEnter() override;
	virtual void onExit() override;
	virtual std::string title() const override;
	virtual void update(float delta);

	void onFrameEvent(cocostudio::Bone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);

	void initWorld();


	cocostudio::Armature *armature;
	cocostudio::Armature *armature2;

	cocos2d::extension::PhysicsSprite *bullet;


	cpSpace *space;

	static int beginHit(cpArbiter *arb, cpSpace *space, void *unused);
	static void endHit(cpArbiter *arb, cpSpace *space, void *unused);

	void destroyCPBody(cpBody *body);
};
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
class TestColliderDetector : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestColliderDetector);

    ~TestColliderDetector();
    
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual void update(float delta)override;
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
    
    void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
    
    void initWorld() {};
    cocostudio::Armature *armature;
    cocostudio::Armature *armature2;
    
    cocos2d::DrawNode* drawNode;
    cocos2d::Sprite *bullet;
};
#endif


class TestBoundingBox : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestBoundingBox);

	virtual void onEnter() override;
	virtual std::string title() const override;
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

	cocostudio::Armature *armature;
    cocos2d::Rect rect;
    
protected:
    cocos2d::DrawNode* _drawNode;
};

class TestAnchorPoint : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestAnchorPoint);

	virtual void onEnter() override;
	virtual std::string title() const override;
};

class TestArmatureNesting : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestArmatureNesting);

	virtual void onEnter() override;
	virtual void onExit() override;
	virtual std::string title() const override;
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

	cocostudio::Armature *armature;
	int weaponIndex;
};

class Hero : public cocostudio::Armature
{
public:
    static Hero *create(const char *name);
    Hero();

    virtual void changeMount(cocostudio::Armature *armature);
    virtual void playWithIndex(int index);

    CC_SYNTHESIZE(cocostudio::Armature*, m_pMount, Mount);
    CC_SYNTHESIZE(cocos2d::Scene*, _scene, Scene);
};

class TestArmatureNesting2 : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestArmatureNesting2);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

    void changeMountCallback(cocos2d::Ref* pSender);
    virtual cocostudio::Armature *createMount(const char *name, cocos2d::Vec2 position);

private:
    Hero *hero;

    cocostudio::Armature *horse;
    cocostudio::Armature *horse2;
    cocostudio::Armature *bear;


    bool touchedMenu;
};

class TestPlaySeveralMovement : public ArmatureBaseTest
{      
public:
    CREATE_FUNC(TestPlaySeveralMovement);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};


class TestEasing : public ArmatureBaseTest
{      
public:
    CREATE_FUNC(TestEasing);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void updateSubTitle();

    int animationID;
    cocostudio::Armature *armature;
};

class TestChangeAnimationInternal : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestChangeAnimationInternal);

    virtual void onEnter()override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
};


#define BINARYFILECOUNT 6
class TestLoadFromBinary : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestLoadFromBinary);

	virtual void onEnter() override;
    virtual std::string title() const override;
	virtual std::string subtitle() const override;
    
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    
	void dataLoaded(float percent);
    
private:
    cocostudio::Armature *m_armature; // current armature
	static const char*  m_binaryFilesNames[BINARYFILECOUNT];
	static const char*  m_armatureNames[BINARYFILECOUNT];
	int m_armatureIndex;   // index of sync loaded armature, default -1 is none
};

class TestArmatureNode : public ArmatureBaseTest
{
public:
    CREATE_FUNC(TestArmatureNode);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif  // __HELLOWORLD_SCENE_H__
