#ifndef __AssetsManagerEx_Test_H__
#define __AssetsManagerEx_Test_H__

#include "extensions/cocos-ext.h"
#include "../../BaseTest.h"

DEFINE_TEST_SUITE(AssetsManagerExTests);

class AssetsManagerExLoaderScene : public TestCase
{
public:
    static AssetsManagerExLoaderScene* create(int testIndex);

    AssetsManagerExLoaderScene(int testIndex);
    
    void startDownloadCallback(cocos2d::Ref* sender);

    virtual std::string title() const;

    virtual bool init() override;
    virtual void onExit() override;
    
private:
    int _testIndex;
    cocos2d::Layer* _loadLayer;
    cocos2d::Menu* _downloadMenu;

    cocos2d::extension::AssetsManagerEx* _am;
    cocos2d::Label* _progress;
    cocos2d::extension::EventListenerAssetsManagerEx* _amListener;

    void onLoadEnd();
};

#endif /* defined(__AssetsManagerEx_Test_H__) */
