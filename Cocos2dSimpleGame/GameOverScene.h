//
//  GameOverScene.h
//  Cocos2DSimpleGame
//
//  Created by Ray Wenderlich on 2/10/10.
//  Copyright 2010 Ray Wenderlich. All rights reserved.
//

#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "cocos2d.h"

class GameOverLayer : public cocos2d::CCColorLayer
{
public:
	virtual ~GameOverLayer();

	LAYER_NODE_FUNC(GameOverLayer);

	bool init();
	void gameOverDone();

	inline cocos2d::CCLabel* getLabel() { return _label; };
protected:
	cocos2d::CCLabel *_label;
};


class GameOverScene : public cocos2d::CCScene
{
public:
	virtual ~GameOverScene();
	bool init();
	
	SCENE_NODE_FUNC(GameOverScene);

public:
	inline GameOverLayer* getLayer() {return _layer; };
protected:
	GameOverLayer *_layer;
};

#endif // _GAME_OVER_SCENE_H_

/*
#import "cocos2d.h"

@interface GameOverLayer : CCColorLayer {
	CCLabel *_label;
}

@property (nonatomic, retain) CCLabel *label;

@end

@interface GameOverScene : CCScene {
	GameOverLayer *_layer;
}

@property (nonatomic, retain) GameOverLayer *layer;

@end
*/