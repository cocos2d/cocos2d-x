#ifndef __INTRO_H__
#define __INTRO_H__

// items from the engine
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

// standard c++
#include <iostream>

class Intro
{
public:
    Intro();
    
    cocos2d::Scene* createScene();
    
    void init();
    
    inline std::vector<cocos2d::Sprite*>& getAliens() { return _vAliens; };
    inline const std::vector<cocos2d::Sprite*>& getAliens() const { return _vAliens; }
    
    void makeAliensMove(const std::vector<cocos2d::Sprite*> _aliens, const float& _screenWidth, const float& _screenHeight);
    
    void makeAliensJump(const std::vector<cocos2d::Sprite*> _aliens, const float& _screenWidth, const float& _screenHeight);
    
    void playMusic();
    
private:
    cocos2d::Scene* scene;
    cocos2d::Node* labelNode;
    cocos2d::Label* player1Coins;
    
    std::vector<cocos2d::Sprite*> _vAliens;
};

#endif // __INTRO_H__
