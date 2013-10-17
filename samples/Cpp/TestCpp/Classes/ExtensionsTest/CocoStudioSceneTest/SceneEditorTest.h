#ifndef __SCENEEDITORTESTSCENE_H__
#define __SCENEEDITORTESTSCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

void runSceneEditorTestLayer();

class SceneEditorTestLayer : public cocos2d::LayerColor
{
public:
	SceneEditorTestLayer();
	~SceneEditorTestLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, 
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
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
};

#endif  // __HELLOWORLD_SCENE_H__
