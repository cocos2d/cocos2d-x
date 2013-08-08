#ifndef __SCENEEDITORTESTSCENE_H__
#define __SCENEEDITORTESTSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

void runSceneEditorTestLayer();

class SceneEditorTestLayer : public cocos2d::CCLayerColor
{
public:
	SceneEditorTestLayer();
	~SceneEditorTestLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, 
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(SceneEditorTestLayer);

    // init scene
    cocos2d::CCNode* createGameScene();
    
    //back to Extensions Main Layer
    void toExtensionsMainLayer(cocos2d::CCObject *sender);

	//get Fish based on Tag and name of Compoent
	cocos2d::extension::CCArmature* getFish(int nTag, const char *pszName);

private:
	cocos2d::CCNode *m_pCurNode;
};

#endif  // __HELLOWORLD_SCENE_H__
