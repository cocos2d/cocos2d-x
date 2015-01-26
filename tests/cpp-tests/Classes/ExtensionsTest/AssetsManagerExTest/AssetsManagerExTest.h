#ifndef __AssetsManagerEx_Test_H__
#define __AssetsManagerEx_Test_H__

#include "extensions/cocos-ext.h"
#include "../../testBasic.h"
#include "../../BaseTest.h"

USING_NS_CC;
USING_NS_CC_EXT;

class AssetsManagerExTestLayer : public BaseTest
{
public:
    AssetsManagerExTestLayer(const std::string& spritePath);
    ~AssetsManagerExTestLayer(void);
    
    virtual std::string title() const;
    void onEnter();
    
    virtual void restartCallback(Ref* sender);
    virtual void nextCallback(Ref* sender);
    virtual void backCallback(Ref* sender);
    
private:
    Sprite *_background;
    std::string _spritePath;
};

class AssetsManagerExTestScene : public TestScene
{
public:
    AssetsManagerExTestScene(std::string background);
    virtual void runThisTest() override;
};

class AssetsManagerExLoaderScene : public TestScene
{
public:
    AssetsManagerExLoaderScene();
    
    virtual void runThisTest() override;
    
    virtual void onExit() override;
    
    static int currentScene;
    
private:
    AssetsManagerEx *_am;
    Label *_progress;
    EventListenerAssetsManagerEx* _amListener;
};

#endif /* defined(__AssetsManagerEx_Test_H__) */
