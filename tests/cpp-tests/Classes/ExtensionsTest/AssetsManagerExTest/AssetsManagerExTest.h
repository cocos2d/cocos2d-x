#ifndef __AssetsManagerEx_Test_H__
#define __AssetsManagerEx_Test_H__

#include "extensions/cocos-ext.h"
#include "../../BaseTest.h"

USING_NS_CC;
USING_NS_CC_EXT;

DEFINE_TEST_SUITE(AssetsManagerExTests);

class AssetsManagerExLoaderScene : public TestCase
{
public:
    static AssetsManagerExLoaderScene* create(int testIndex);

    AssetsManagerExLoaderScene(int testIndex);
    
    void startDownloadCallback(Ref* sender);

    virtual std::string title() const;

    virtual bool init() override;
    virtual void onExit() override;
    
private:
    int _testIndex;
    Layer* _loadLayer;
    Menu* _downloadMenu;

    AssetsManagerEx *_am;
    Label *_progress;
    EventListenerAssetsManagerEx* _amListener;

    void onLoadEnd();
};

#endif /* defined(__AssetsManagerEx_Test_H__) */
