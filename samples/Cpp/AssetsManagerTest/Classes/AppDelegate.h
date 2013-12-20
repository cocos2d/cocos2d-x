//
//  AssetsManagerTestAppDelegate.h
//  AssetsManagerTest
//
//  Created by minggo on 2/5/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCApplication.h"
#include "cocos2d.h"
#include "extensions/assets-manager/AssetsManager.h"

/**
@brief    The cocos2d Application.

The reason to implement with private inheritance is to hide some interface details of Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function is called when the application enters the background
    @param  the pointer of the application instance
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function is called when the application enters the foreground
    @param  the pointer of the application instance
    */
    virtual void applicationWillEnterForeground();
};

class UpdateLayer : public cocos2d::Layer, public cocos2d::extension::AssetsManagerDelegateProtocol
{
public:
    UpdateLayer();
    ~UpdateLayer();
    virtual bool init();
    
    void enter(cocos2d::Object *pSender);
    void reset(cocos2d::Object *pSender);
    void update(cocos2d::Object *pSender);

    virtual void onError(cocos2d::extension::AssetsManager::ErrorCode errorCode);
    virtual void onProgress(int percent);
    virtual void onSuccess();
    
private:
    cocos2d::extension::AssetsManager* pAssetsManager;
    void createDownloadedDir();
    
    cocos2d::MenuItemFont *pItemEnter;
    cocos2d::MenuItemFont *pItemReset;
    cocos2d::MenuItemFont *pItemUpdate;
    cocos2d::LabelTTF *pProgressLabel;
    std::string pathToSave;
    bool isUpdateItemClicked;
};

#endif // _APP_DELEGATE_H_

