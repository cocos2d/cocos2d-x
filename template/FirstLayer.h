
#ifndef _HELLOWORLD_LAYER_H_
#define _HELLOWORLD_LAYER_H_

#include "cocos2d.h"

class FirstLayer : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	
	// a selector callback
	virtual void menuCloseCallback(NSObject* pSender);
};

#endif // _HELLOWORLD_SCENE_H_