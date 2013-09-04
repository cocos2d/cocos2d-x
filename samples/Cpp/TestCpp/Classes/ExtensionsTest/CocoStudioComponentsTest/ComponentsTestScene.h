#ifndef __COMPONENTSTESTSCENE_H__
#define __COMPONENTSTESTSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

void runComponentsTestLayerTest();

class ComponentsTestLayer : public cocos2d::CCLayerColor
{
public:
	ComponentsTestLayer();
	~ComponentsTestLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, 
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(ComponentsTestLayer);

    // init scene
    cocos2d::CCNode* createGameScene();
    
    //back to Extensions Main Layer
    void toExtensionsMainLayer(cocos2d::CCObject *sender);
};

#endif  // __HELLOWORLD_SCENE_H__
