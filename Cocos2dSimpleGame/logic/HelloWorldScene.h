
#ifndef _HELLOWORLD_LAYER_H_
#define _HELLOWORLD_LAYER_H_

#include "cocos2d.h"


class HelloWorld : public cocos2d::CCColorLayer
{
protected:
	cocos2d::NSMutableArray<cocos2d::CCSprite*> *_targets;
	cocos2d::NSMutableArray<cocos2d::CCSprite*> *_projectiles;
	int _projectilesDestroyed;

public:
	HelloWorld();
	virtual ~HelloWorld();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	void addTarget();

	void ccTouchesEnded(cocos2d::NSSet* touches, cocos2d::UIEvent* event);

	// callfunc callback
	void spriteMoveFinished(cocos2d::CCNode* sender);

	// scehdule selector, timer
	void gameLogic(cocos2d::ccTime dt);

	// update
	void update(cocos2d::ccTime dt);

	// a selector callback
	void menuCloseCallback(cocos2d::NSObject* pSender);

    LAYER_NODE_FUNC(HelloWorld);
    
	static cocos2d::CCScene* scene();
};

#endif // _HELLOWORLD_SCENE_H_