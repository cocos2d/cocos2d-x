#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class HelloWorld : public cc::LayerColor
{
public:
	HelloWorld();
	~HelloWorld();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, 
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cc::Scene* scene();

	// a selector callback
	virtual void menuCloseCallback(cc::Object* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);

	void spriteMoveFinished(cc::Node* sender);

	void gameLogic(float dt);

	void updateGame(float dt);

	void registerWithTouchDispatcher();
	void ccTouchesEnded(cc::Set* touches, cc::Event* event);
    
    
protected:
	cc::Array *_targets;
	cc::Array *_projectiles;
	int _projectilesDestroyed;

	void addTarget();


};

#endif  // __HELLOWORLD_SCENE_H__