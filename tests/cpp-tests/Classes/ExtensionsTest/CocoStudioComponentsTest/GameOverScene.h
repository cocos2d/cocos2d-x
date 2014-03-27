#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "cocos2d.h"

class GameOverLayer : public cocos2d::LayerColor
{
public:
    GameOverLayer():_label(nullptr) {};
    virtual ~GameOverLayer();
    bool init();
    CREATE_FUNC(GameOverLayer);

    void gameOverDone();

    CC_SYNTHESIZE_READONLY(cocos2d::Label*, _label, Label);
};

class GameOverScene : public cocos2d::Scene
{
public:
    GameOverScene():_layer(nullptr) {};
    ~GameOverScene();
    bool init();
    CREATE_FUNC(GameOverScene);
  
    CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);
};

#endif // _GAME_OVER_SCENE_H_
