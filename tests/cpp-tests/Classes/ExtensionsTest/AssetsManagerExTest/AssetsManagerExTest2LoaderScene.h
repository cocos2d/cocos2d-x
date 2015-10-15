#ifndef __AssetsManagerEx_Test2LoaderScene_H__
#define __AssetsManagerEx_Test2LoaderScene_H__

#include "extensions/cocos-ext.h"
#include "../../BaseTest.h"

DEFINE_TEST_SUITE(AssetsManagerExTestSimple);

class AssetsManagerExTest2LoaderScene : public TestCase
{
public:
    static AssetsManagerExTest2LoaderScene* create();

    AssetsManagerExTest2LoaderScene();

	~AssetsManagerExTest2LoaderScene();
    
    void startDownloadYesCallback(cocos2d::Ref* sender);
	
    void startDownloadNoCallback(cocos2d::Ref* sender);

    virtual std::string title() const;

    virtual bool init() override;

    virtual void onExit() override;
    
private:

	cocos2d::Menu	* _downloadMenu_Yes;

	cocos2d::Menu	* _downloadMenu_No;

    cocos2d::Layer	* _loadLayer;

    cocos2d::Label	* _progress;

    void onLoadEnd();
};

#endif /* defined(__AssetsManagerEx_Test2LoaderScene_H__) */
