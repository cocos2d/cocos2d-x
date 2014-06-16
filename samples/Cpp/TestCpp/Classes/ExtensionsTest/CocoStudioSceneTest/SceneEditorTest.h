#ifndef __SCENEEDITORTESTSCENE_H__
#define __SCENEEDITORTESTSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class SceneEditorTestScene : public TestScene
{
public: 
	SceneEditorTestScene(bool bPortrait = false);

	virtual void runThisTest();

	// The CallBack for back to the main menu scene
	virtual void MainMenuCallback(CCObject* pSender);
};

enum {
	TEST_LOADSCENEEDITORFILE = 0,
    TEST_SPIRTECOMPONENT,
    TEST_ARMATURECOMPONENT,
    TEST_UICOMPONENT,
    TEST_TMXMAPCOMPONENT,
    TEST_PARTICLECOMPONENT,
    TEST_EFEECTCOMPONENT,
    TEST_BACKGROUNDCOMPONENT,
    TEST_ATTRIBUTECOMPONENT,
    TEST_TRIGGER,
	TEST_SCENEEDITOR_COUNT
};

class SceneEditorTestLayer : public CCLayer
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

protected:
	virtual void changeLoadTypeCallback(CCObject *pSender);
	virtual void defaultPlay() = 0; // must to be overrided
	void loadFileChangeHelper(string& filePathName );  // switch json& csb
private:
	bool m_isCsbLoad;   // default is false
	CCLabelTTF* m_loadtypelb;
	static const char* m_loadtypeStr[2];
protected:
	CCNode* m_rootNode;
	string m_filePathName;
};

class LoadSceneEdtiorFileTest : public SceneEditorTestLayer
{
public:
	LoadSceneEdtiorFileTest();
	~LoadSceneEdtiorFileTest();

    virtual std::string title();
	virtual void onEnter();
    virtual void onExit();
    cocos2d::CCNode* createGameScene();
//protected:
//	void changeLoadTypeCallback(CCObject *pSender);
private:
	void defaultPlay();
};


class SpriteComponentTest : public SceneEditorTestLayer
{
public:
	SpriteComponentTest();
	~SpriteComponentTest();

    virtual std::string title();
	virtual void onEnter();
    virtual void onExit();
    cocos2d::CCNode* createGameScene();
//protected:
//	void changeLoadTypeCallback(CCObject *pSender);
private:
	void defaultPlay();
};

class ArmatureComponentTest : public SceneEditorTestLayer
{
public:
	ArmatureComponentTest();
	~ArmatureComponentTest();

    virtual std::string title();
	virtual void onEnter();
    virtual void onExit();
    cocos2d::CCNode* createGameScene();
//protected:
//	void changeLoadTypeCallback(CCObject *pSender);
private:
	void defaultPlay();
};

class UIComponentTest : public SceneEditorTestLayer
{
public:
	UIComponentTest();
	~UIComponentTest();

    virtual std::string title();
	virtual void onEnter();
    virtual void onExit();
    cocos2d::CCNode* createGameScene();
	void touchEvent(CCObject *pSender, cocos2d::ui::TouchEventType type);
//protected:
//	void changeLoadTypeCallback(CCObject *pSender);
private:
	void defaultPlay();
};

class TmxMapComponentTest : public SceneEditorTestLayer
{
public:
	TmxMapComponentTest();
	~TmxMapComponentTest();

    virtual std::string title();
	virtual void onEnter();
    virtual void onExit();
    cocos2d::CCNode* createGameScene();
private:
	void defaultPlay();

};

class ParticleComponentTest : public SceneEditorTestLayer
{
public:
	ParticleComponentTest();
	~ParticleComponentTest();

    virtual std::string title();
	virtual void onEnter();
    virtual void onExit();
    cocos2d::CCNode* createGameScene();
protected:
	void defaultPlay();
};

class EffectComponentTest : public SceneEditorTestLayer
{
public:
	EffectComponentTest();
	~EffectComponentTest();

    virtual std::string title();
	virtual void onEnter();
    virtual void onExit();
    cocos2d::CCNode* createGameScene();
	void animationEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
private:
	void defaultPlay();
};

class BackgroundComponentTest : public SceneEditorTestLayer
{
public:
	BackgroundComponentTest();
	~BackgroundComponentTest();

    virtual std::string title();
	virtual void onEnter();
    virtual void onExit();
    cocos2d::CCNode* createGameScene();
private:
	void defaultPlay();
};

class AttributeComponentTest : public SceneEditorTestLayer
{
public:
	AttributeComponentTest();
	~AttributeComponentTest();

    virtual std::string title();
	virtual void onEnter();
    virtual void onExit();
	bool initData();
    cocos2d::CCNode* createGameScene();
private:
	void defaultPlay();
};


class TriggerTest : public SceneEditorTestLayer
{
public:
	TriggerTest();
	~TriggerTest();

    virtual std::string title();
	virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void gameLogic(float dt);
    cocos2d::CCNode* createGameScene();
private:
	void defaultPlay();
};

#endif  // __HELLOWORLD_SCENE_H__
