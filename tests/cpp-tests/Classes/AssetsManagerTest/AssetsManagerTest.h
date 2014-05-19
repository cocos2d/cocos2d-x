#ifndef __AssetsManager_Test_H__
#define __AssetsManager_Test_H__

#include "extensions/cocos-ext.h"
#include "../testBasic.h"
#include "../BaseTest.h"
#include "extensions/assets-manager/AAssetsManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

class AssetsManagerTestLayer : public BaseTest
{
public:
    AssetsManagerTestLayer(std::string spritePath);
    ~AssetsManagerTestLayer(void);
    
    virtual std::string title() const;
    void onEnter();
    
    virtual void restartCallback(Ref* sender);
    virtual void nextCallback(Ref* sender);
    virtual void backCallback(Ref* sender);
    
private:
    Sprite *_background;
    std::string _spritePath;
};

class AssetsManagerTestScene : public TestScene
{
public:
    AssetsManagerTestScene(std::string background);
    virtual void runThisTest() override;
};

class AssetsManagerLoaderScene : public TestScene
{
public:
    AssetsManagerLoaderScene();
    
    virtual void runThisTest() override;
    
    virtual void onExit() override;
    
    static int currentScene;
    
private:
    AAssetsManager *_am;
};

#endif /* defined(__AssetsManager_Test_H__) */
