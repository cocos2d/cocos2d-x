#ifndef __SCENEEDITORTESTSCENE_H__
#define __SCENEEDITORTESTSCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "BaseTest.h"

DEFINE_TEST_SUITE(CocoStudioSceneEditTests);

class SceneEditorTestBase : public TestCase
{
public:
	virtual bool init() override;

	virtual std::string title() const override;

protected:
    cocos2d::MenuItemImage* restartItem;
    cocos2d::MenuItemImage* nextItem;
    cocos2d::MenuItemImage* backItem;
    
protected:
	virtual void changeLoadTypeCallback(cocos2d::Ref *pSender);
	virtual void defaultPlay() = 0; // must to be overrided
	void loadFileChangeHelper(std::string& filePathName );  // switch json& csb

private:
	bool _isCsbLoad;   // default is false
    cocos2d::Label* _loadtypelb;
	static const char* _loadtypeStr[2];
    
protected:
    cocos2d::Node* _rootNode;
    std::string _filePath;
};

class LoadSceneEdtiorFileTest : public SceneEditorTestBase
{
public:
    CREATE_FUNC(LoadSceneEdtiorFileTest);

	LoadSceneEdtiorFileTest();
	~LoadSceneEdtiorFileTest();

    virtual std::string title() const override;
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();
private:
	void defaultPlay();
};


class SpriteComponentTest : public SceneEditorTestBase
{
public:
    CREATE_FUNC(SpriteComponentTest);

	SpriteComponentTest();
	~SpriteComponentTest();

    virtual std::string title() const override;
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();

private:
	void defaultPlay();
};

class ArmatureComponentTest : public SceneEditorTestBase
{
public:
    CREATE_FUNC(ArmatureComponentTest);

	ArmatureComponentTest();
	~ArmatureComponentTest();

    virtual std::string title() const override;
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();

private:
	void defaultPlay();
};

class UIComponentTest : public SceneEditorTestBase
{
public:
    CREATE_FUNC(UIComponentTest);

	UIComponentTest();
	~UIComponentTest();

    virtual std::string title() const override;
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();
	void touchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
private:
	void defaultPlay();
};

class TmxMapComponentTest : public SceneEditorTestBase
{
public:
    CREATE_FUNC(TmxMapComponentTest);

	TmxMapComponentTest();
	~TmxMapComponentTest();

    virtual std::string title() const override;
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();
private:
	void defaultPlay();

};

class ParticleComponentTest : public SceneEditorTestBase
{
public:
    CREATE_FUNC(ParticleComponentTest);

	ParticleComponentTest();
	~ParticleComponentTest();

    virtual std::string title() const override;
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();
protected:
	void defaultPlay();
};

class EffectComponentTest : public SceneEditorTestBase
{
public:
    CREATE_FUNC(EffectComponentTest);

	EffectComponentTest();
	~EffectComponentTest();

    virtual std::string title() const override;
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();
    void animationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);
private:
	void defaultPlay();
	
};

class BackgroundComponentTest : public SceneEditorTestBase
{
public:
    CREATE_FUNC(BackgroundComponentTest);

	BackgroundComponentTest();
	~BackgroundComponentTest();

    virtual std::string title() const override;
	virtual void onEnter() override;
    virtual void onExit() override;
    cocos2d::Node* createGameScene();
private:
	void defaultPlay();
};

class AttributeComponentTest : public SceneEditorTestBase
{
public:
    CREATE_FUNC(AttributeComponentTest);

	AttributeComponentTest();
	~AttributeComponentTest();

    virtual std::string title() const override;
	virtual void onEnter() override;
    virtual void onExit() override;
	bool initData();
    cocos2d::Node* createGameScene();
    
private:
	void defaultPlay();
};

class TriggerTest : public SceneEditorTestBase
{
public:
    CREATE_FUNC(TriggerTest);

	TriggerTest();
	~TriggerTest();

    virtual std::string title() const override;
    virtual void onEnter() override;
    virtual void onExit() override;
    
	// default implements are used to call script callback if exist
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event); 
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event); 
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event); 
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	// update of game
	void gameLogic(float dt);
    
    // create scene
    cocos2d::Node* createGameScene();
  
private:
    void defaultPlay();

    cocos2d::EventListener* _touchListener;
};

#endif  // __HELLOWORLD_SCENE_H__
