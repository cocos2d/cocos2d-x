#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "cocos2d.h"
#include "BaseTest.h"

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

class GameOverScene : public TestCase
{
public:
    CREATE_FUNC(GameOverScene);

    GameOverScene():_layer(nullptr) {}
    ~GameOverScene();

    virtual bool init() override;
  
    CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);
};

#endif // _GAME_OVER_SCENE_H_
