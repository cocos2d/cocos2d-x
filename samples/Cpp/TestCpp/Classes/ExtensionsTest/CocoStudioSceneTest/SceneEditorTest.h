#ifndef __SCENEEDITORTESTSCENE_H__
#define __SCENEEDITORTESTSCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

void runSceneEditorTestLayer();

class SceneEditorTestLayer : public cocos2d::Layer
{
public:
	SceneEditorTestLayer();
	~SceneEditorTestLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, 
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();
        
    // callback of Scene Enter
	virtual void onEnter();
    
    // callback of Scene Exit
	virtual void onExit();
    
	// default implements are used to call script callback if exist
	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

	// update of game
	void gameLogic(float dt);
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::Scene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(SceneEditorTestLayer);

    // init scene
    cocos2d::Node* createGameScene();
    
    //back to Extensions Main Layer
    void toExtensionsMainLayer(cocos2d::Object *sender);

private:
	cocos2d::Node *_curNode;
    cocos2d::EventListener* _touchListener;
};

#endif  // __HELLOWORLD_SCENE_H__
