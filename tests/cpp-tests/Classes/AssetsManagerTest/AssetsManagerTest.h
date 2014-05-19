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
    virtual void onEnter() override;
    
private:
    Sprite *_background;
    std::string _spritePath;
};

class AssetsManagerTestScene : public TestScene
{
public:
    virtual void runThisTest() override;
    void onLoad();
private:
    std::string _background;
};

class AssetsManagerLoaderScene : public Scene
{
public:
    AssetsManagerLoaderScene(std::string managerId, std::string manifestPath, std::string storagePath, AssetsManagerTestScene *scene);
    
    static int currentScene;
private:
    AssetsManagerTestScene *_scene;
};

#endif /* defined(__AssetsManager_Test_H__) */
