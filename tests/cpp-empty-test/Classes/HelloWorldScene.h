#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include <string>

namespace creator
{
    class CreatorReader;
}

namespace cocos2d
{
    namespace ui
    {
        class Button;
    }
}

class HelloWorld
{
public:
    static cocos2d::Scene* scene();
    
private:
    
    static cocos2d::Scene* createScene(const std::string& ccreatorPath);
    static cocos2d::ui::Button* createBackButton();
    static void repalceScene(const std::string& ccreatorPath);
    static void handleButtonClick(cocos2d::Scene* scene, const std::string& buttonName, const std::string& ccreatorPath);
    static void handleButtonsClick(cocos2d::Scene* scene);
    static void handleColliderButtonClick(cocos2d::Scene* scene);
    static void handleVideoButtonClick(cocos2d::Scene* scene);
    static void handleAnimationButtonClick(cocos2d::Scene* scene);
    static void handleDragonbones(cocos2d::Scene* scene);
    
    static cocos2d::Scene* g_currentScene;
    static creator::CreatorReader* g_reader;
};

#endif // __HELLOWORLD_SCENE_H__
