#ifndef __COMPONENTSTESTSCENE_H__
#define __COMPONENTSTESTSCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

void runComponentsTestLayerTest();

class ComponentsTestLayer : public cocos2d::LayerColor
{
public:
	ComponentsTestLayer();
	~ComponentsTestLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, 
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init() override;
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::Scene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(ComponentsTestLayer);

    // init scene
    cocos2d::Node* createGameScene();
};

#endif  // __HELLOWORLD_SCENE_H__
