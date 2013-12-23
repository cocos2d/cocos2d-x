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
    
    // callback of Scene Enter
	virtual void onEnter();
    
    // callback of Scene Exit
	virtual void onExit();
    
	// default implements are used to call script callback if exist
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	// update of game
	void gameLogic(float dt);

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
