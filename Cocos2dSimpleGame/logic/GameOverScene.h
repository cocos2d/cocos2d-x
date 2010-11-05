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
	GameOverLayer():_label(NULL) {};
	virtual ~GameOverLayer();
	bool init();
	LAYER_NODE_FUNC(GameOverLayer);

	void gameOverDone();

	CCX_SYNTHESIZE_READONLY(cocos2d::CCLabel*, _label, Label);
};

class GameOverScene : public cocos2d::CCScene
{
public:
	GameOverScene():_layer(NULL) {};
	~GameOverScene();
	bool init();
	SCENE_NODE_FUNC(GameOverScene);

	CCX_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);
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