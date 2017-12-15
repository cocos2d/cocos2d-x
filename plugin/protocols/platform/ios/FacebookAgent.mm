#include "AgentManager.h"
#include "FacebookAgent.h"
namespace cocos2d{namespace plugin{
    
    static FacebookAgent* s_sharedFacebookAgent = nullptr;
    static const char*  s_cocos2dxVersion = "3.18.0/cocos2d-x-3.9";
    static const char*  s_cocos2dxLuaVersion = "3.18.0/cocos2d-x-lua-3.9";
    static const char*  s_cocos2dxJsVersion  = "3.18.0/cocos2d-js-3.9";
    
    FacebookAgent* FacebookAgent::getInstance()
    {
        if(nullptr == s_sharedFacebookAgent)
        {
            s_sharedFacebookAgent = new (std::nothrow)FacebookAgent();
            if (nullptr != s_sharedFacebookAgent)
            {
                s_sharedFacebookAgent->setSDKVersion(s_cocos2dxVersion);
            }
        }
        return s_sharedFacebookAgent;
    }
    
    FacebookAgent* FacebookAgent::getInstanceLua()
    {
        if(nullptr == s_sharedFacebookAgent)
        {
            s_sharedFacebookAgent = new (std::nothrow)FacebookAgent();
            if (nullptr != s_sharedFacebookAgent)
            {
                s_sharedFacebookAgent->setSDKVersion(s_cocos2dxLuaVersion);
            }
        }
        return s_sharedFacebookAgent;
    }
    
    FacebookAgent* FacebookAgent::getInstanceJs()
    {
        if(nullptr == s_sharedFacebookAgent)
        {
            s_sharedFacebookAgent = new (std::nothrow)FacebookAgent();
            if (nullptr != s_sharedFacebookAgent)
            {
                s_sharedFacebookAgent->setSDKVersion(s_cocos2dxJsVersion);
            }
        }
        return s_sharedFacebookAgent;
    }
    
    void FacebookAgent::destroyInstance()
    {
        if(s_sharedFacebookAgent)
        {
            delete s_sharedFacebookAgent;
            s_sharedFacebookAgent = nullptr;
        }
    }
    
    FacebookAgent::FacebookAgent()
    {
        agentManager = AgentManager::getInstance();
        std::map<std::string, std::string> facebook = {{"PluginUser", "UserFacebook"}, {"PluginShare", "ShareFacebook"}};
        agentManager->init(facebook);
    }
    
    FacebookAgent::~FacebookAgent()
    {
        requestCallbacks.clear();
        AgentManager::destroyInstance();
    }
    
    void FacebookAgent::login(FBCallback cb)
    {
        agentManager->getUserPlugin()->login(cb);
    }
    void FacebookAgent::login(std::string& permissions, FBCallback cb)
    {
        auto userPlugin = agentManager->getUserPlugin();
        userPlugin->setCallback(cb);
        PluginParam _permissions(permissions.c_str());
        userPlugin->callFuncWithParam("loginWithPermission", &_permissions, NULL);
    }
    void FacebookAgent::logout()
    {
        agentManager->getUserPlugin()->logout();
    }
    bool FacebookAgent::isLoggedIn()
    {
        return agentManager->getUserPlugin()->isLoggedIn();
    }
    std::string FacebookAgent::getAccessToken()
    {
        return agentManager->getUserPlugin()->callStringFuncWithParam("getAccessToken", NULL);
    }
    
    void FacebookAgent::share(FBInfo& info, FBCallback cb)
    {
        agentManager->getSharePlugin()->share(info, cb);
    }
    std::string FacebookAgent::getPermissionList()
    {
        return agentManager->getUserPlugin()->callStringFuncWithParam("getPermissionList", NULL);
    }
    std::string FacebookAgent::getUserID()
    {
        return  agentManager->getUserPlugin()->callStringFuncWithParam("getUserID", NULL);
    }
    void FacebookAgent::dialog(FBInfo& info, FBCallback cb)
    {
        auto sharePlugin = agentManager->getSharePlugin();
        sharePlugin->setCallback(cb);
        PluginParam params(info);
        sharePlugin->callFuncWithParam("dialog", &params, NULL);
    }
    void FacebookAgent::webDialog(FBInfo &info, FBCallback cb){
        auto sharePlugin = agentManager->getSharePlugin();
        sharePlugin->setCallback(cb);
        PluginParam params(info);
        sharePlugin->callFuncWithParam("webDialog", &params, NULL);
    }
    bool FacebookAgent::canPresentDialogWithParams(FBInfo& info){
        PluginParam params(info);
        bool status = agentManager->getSharePlugin()->callBoolFuncWithParam("canPresentDialogWithParams", &params,NULL);
        return status;
    }
    void FacebookAgent::api(std::string &path, int method, FBInfo &params, FBCallback cb)
    {
        requestCallbacks.push_back(cb);
        
        PluginParam _path(path.c_str());
        PluginParam _method(method);
        PluginParam _params(params);
        PluginParam _cbIndex((int)(requestCallbacks.size() - 1));
        
        agentManager->getUserPlugin()->callFuncWithParam("api", &_path, &_method, &_params, &_cbIndex, NULL);
    }
    void FacebookAgent::appRequest(FBInfo& info, FBCallback cb)
    {
        auto sharePlugin = agentManager->getSharePlugin();
        sharePlugin->setCallback(cb);
        PluginParam params(info);
        sharePlugin->callFuncWithParam("appRequest", &params, NULL);
    }
    FacebookAgent::FBCallback FacebookAgent::getRequestCallback(int index)
    {
        return requestCallbacks[index];
    }
    void FacebookAgent::activateApp()
    {
        agentManager->getUserPlugin()->callFuncWithParam("activateApp", NULL);
    }
    
    void FacebookAgent::logEvent(std::string& eventName)
    {
        PluginParam _eventName(eventName.c_str());
        agentManager->getUserPlugin()->callFuncWithParam("logEventWithName", &_eventName, NULL);
    }
    
    void FacebookAgent::logEvent(std::string& eventName, float valueToSum)
    {
        PluginParam _eventName(eventName.c_str());
        PluginParam _valueToSum(valueToSum);
        agentManager->getUserPlugin()->callFuncWithParam("logEvent", &_eventName, &_valueToSum, NULL);
    }
    
    void FacebookAgent::logEvent(std::string& eventName, FBInfo& parameters)
    {
        PluginParam _eventName(eventName.c_str());
        PluginParam _params(parameters);
        agentManager->getUserPlugin()->callFuncWithParam("logEvent", &_eventName, &_params, NULL);
    }
    void FacebookAgent::logPurchase(float mount, std::string currency){
        PluginParam _mount(mount);
        PluginParam _currency(currency.c_str());
        agentManager->getUserPlugin()->callFuncWithParam("logPurchase", &_mount, &_currency, NULL);
    }
    void FacebookAgent::logPurchase(float mount, std::string currency,FBInfo &params){
        PluginParam _mount(mount);
        PluginParam _currency(currency.c_str());
        PluginParam _params(params);
        agentManager->getUserPlugin()->callFuncWithParam("logPurchase", &_mount, &_currency, &_params, NULL);
    }
    void FacebookAgent::logEvent(std::string& eventName, float valueToSum, FBInfo& parameters)
    {
        PluginParam _eventName(eventName.c_str());
        PluginParam _valueToSum(valueToSum);
        PluginParam _params(parameters);
        agentManager->getUserPlugin()->callFuncWithParam("logEvent", &_eventName, &_valueToSum, &_params, NULL);
    }
    std::string FacebookAgent::getSDKVersion()
    {
        return agentManager->getUserPlugin()->callStringFuncWithParam("getSDKVersion", NULL);
    }

    void FacebookAgent::setSDKVersion(std::string version)
    {
        PluginParam _version(version.c_str());
        agentManager->getUserPlugin()->callFuncWithParam("setSDKVersion", &_version, NULL);
    }

}}
