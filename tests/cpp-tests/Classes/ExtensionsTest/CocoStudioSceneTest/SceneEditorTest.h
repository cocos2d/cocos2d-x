#ifndef __SCENEEDITORTESTSCENE_H__
#define __SCENEEDITORTESTSCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"

class SceneEditorTestScene : public TestScene
{
public: 
	SceneEditorTestScene(bool bPortrait = false);

	virtual void runThisTest();

	// The CallBack for back to the main menu scene
	virtual void MainMenuCallback(cocos2d::Ref* pSender);
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

class SceneEditorTestLayer : public cocos2d::Layer
{
public:
	virtual void onEnter() override;
	virtual void onExit() override;

	virtual std::string title();
	virtual std::string subtitle();

	virtual void restartCallback(cocos2d::Ref* pSender);
	virtual void nextCallback(cocos2d::Ref* pSender);
	virtual void backCallback(cocos2d::Ref* pSender);

	virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;

protected:
	MenuItemImage *restartItem;
	MenuItemImage *nextItem;
	MenuItemImage *backItem;
};

class LoadSceneEdtiorFileTest : public SceneEditorTestLayer
{
public:
	LoadSceneEdtiorFileTest();
	~LoadSceneEdtiorFileTest();

    virtual std::string title();
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();
};


class SpriteComponentTest : public SceneEditorTestLayer
{
public:
	SpriteComponentTest();
	~SpriteComponentTest();

    virtual std::string title();
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();

};

class ArmatureComponentTest : public SceneEditorTestLayer
{
public:
	ArmatureComponentTest();
	~ArmatureComponentTest();

    virtual std::string title();
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();

};

class UIComponentTest : public SceneEditorTestLayer
{
public:
	UIComponentTest();
	~UIComponentTest();

    virtual std::string title();
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();
	void touchEvent(cocos2d::Ref *pSender, ui::Widget::TouchEventType type);
private:
	cocos2d::Node* _node;
};

class TmxMapComponentTest : public SceneEditorTestLayer
{
public:
	TmxMapComponentTest();
	~TmxMapComponentTest();

    virtual std::string title();
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();

};

class ParticleComponentTest : public SceneEditorTestLayer
{
public:
	ParticleComponentTest();
	~ParticleComponentTest();

    virtual std::string title();
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();
};

class EffectComponentTest : public SceneEditorTestLayer
{
public:
	EffectComponentTest();
	~EffectComponentTest();

    virtual std::string title();
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();
    void animationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);
private:
	cocos2d::Node* _node;
};

class BackgroundComponentTest : public SceneEditorTestLayer
{
public:
	BackgroundComponentTest();
	~BackgroundComponentTest();

    virtual std::string title();
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();
};

class AttributeComponentTest : public SceneEditorTestLayer
{
public:
	AttributeComponentTest();
	~AttributeComponentTest();

    virtual std::string title();
	virtual void onEnter() override;
    virtual void onExit() override;
	bool initData();
    cocos2d::Node* createGameScene();
private:
	cocos2d::Node* _node;
};

class TriggerTest : public SceneEditorTestLayer
{
public:
	TriggerTest();
	~TriggerTest();

    virtual std::string title();
    virtual void onEnter() override;
    virtual void onExit() override;
    
	// default implements are used to call script callback if exist
	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

	// update of game
	void gameLogic(float dt);
    
    // create scene
    cocos2d::Node* createGameScene();
  
private:
	cocos2d::Node *_node;
    cocos2d::EventListener* _touchListener;
};

#endif  // __HELLOWORLD_SCENE_H__
