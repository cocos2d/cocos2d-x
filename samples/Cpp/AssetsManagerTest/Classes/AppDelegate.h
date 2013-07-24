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
#include "AssetsManager/AssetsManager.h"

/**
@brief    The cocos2d Application.

The reason to implement with private inheritance is to hide some interface details of Director.
*/
class  AppDelegate : private cc::Application
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

class UpdateLayer : public cc::Layer, public cc::extension::AssetsManagerDelegateProtocol
{
public:
    UpdateLayer();
    ~UpdateLayer();
    virtual bool init();
    
    void enter(cc::Object *pSender);
    void reset(cc::Object *pSender);
    void update(cc::Object *pSender);

    virtual void onError(cc::extension::AssetsManager::ErrorCode errorCode);
    virtual void onProgress(int percent);
    virtual void onSuccess();
    
private:
    cc::extension::AssetsManager* getAssetsManager();
    void createDownloadedDir();
    
    cc::MenuItemFont *pItemEnter;
    cc::MenuItemFont *pItemReset;
    cc::MenuItemFont *pItemUpdate;
    cc::LabelTTF *pProgressLabel;
    std::string pathToSave;
    bool isUpdateItemClicked;
};

#endif // _APP_DELEGATE_H_

