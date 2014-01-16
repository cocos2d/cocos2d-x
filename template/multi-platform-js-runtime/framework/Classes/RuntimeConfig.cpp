
#include "RuntimeConfig.h"

#include "SimpleAudioEngine.h"
#include "jsb_cocos2dx_auto.hpp"
#include "jsb_cocos2dx_extension_auto.hpp"
#include "jsb_cocos2dx_builder_auto.hpp"
#include "extension/jsb_cocos2dx_extension_manual.h"
#include "cocosbuilder/js_bindings_ccbreader.h"
#include "localstorage/js_bindings_system_registration.h"
#include "chipmunk/js_bindings_chipmunk_registration.h"
#include "jsb_opengl_registration.h"

#include "BrowseDir.h"

static RuntimeConfig *s_SharedRuntime = nullptr;
RuntimeConfig::RuntimeConfig()
{
	_scheduler = CCDirector::sharedDirector()->getScheduler();
}

RuntimeConfig::~RuntimeConfig()
{
	s_SharedRuntime =NULL;
}

void RuntimeConfig::resetRuntime()
{
// 	FileUtils::sharedFileUtils()->purgeCachedEntries();
// 	Director::getInstance()->purgeCachedData();
	ScriptEngineProtocol *engine = ScriptingCore::getInstance();
	ScriptEngineManager::getInstance()->setScriptEngine(engine);
 	ScriptingCore::getInstance()->runScript("cocos2d-jsb.js");
}

RuntimeConfig* RuntimeConfig::getInstance()
{
	if (!s_SharedRuntime)
	{
		s_SharedRuntime = new RuntimeConfig();
	}

	return s_SharedRuntime;
}

void RuntimeConfig::setSearchPath()
{

#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
		extern std::string GetCurAppPath(void);
		_searchPath = GetCurAppPath();
		_searchPath += "/../..";
		string searchPathRes = GetCurAppPath();
		searchPathRes += "/HelloJavascriptRes";
		FileUtils::getInstance()->addSearchPath(_searchPath.c_str());
		FileUtils::getInstance()->addSearchPath(searchPathRes.c_str());
#endif

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	extern std::string getPackageNameJNI();
	_searchPath = "/mnt/sdcard/";
	_searchPath += getPackageNameJNI();
	FileUtils::getInstance()->addSearchPath(_searchPath.c_str());
	//MessageBox(searchPath.c_str(),""); 
#endif

#if (CC_TARGET_PLATFORM==CC_PLATFORM_MAC )
    
    _searchPath = FileUtils::getInstance()->getResPath();
#endif
    
	// /mnt/sdcard/
	// CC_PLATFORM_ANDROID

}
void RuntimeConfig::updateConnect(float delta)
{
	if (!FileUtils::getInstance()->isFileExist(szwaitFile))
	{
		_scheduler->unscheduleSelector(SEL_SCHEDULE(&RuntimeConfig::updateConnect),this);
		resetRuntime();	
	}
}
void RuntimeConfig::waitConnect()
{
	CBrowseDir browseDir;  
	browseDir.setFilter("runtime|framework|","|");
	browseDir.setInitDir(_searchPath.c_str());
	browseDir.beginBrowse("*.js");   

	FileInfoList  fileInfoList=browseDir.getFileInfoList();
	for (int i = 0; i < fileInfoList.size(); i++)
	{
		//string strfile = fileInfoList[i].fileName.c_str();
		ScriptingCore::getInstance()->compileScript(fileInfoList[i].fileName.c_str());
	}

    memset(szwaitFile,0,sizeof(szwaitFile));
	
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	extern std::string GetCurAppPath(void);
	string searchPath = GetCurAppPath();
	sprintf(szwaitFile,"%s/.wait",searchPath.c_str());
#endif

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID )
	extern std::string getPackageNameJNI();
	string searchPath = getPackageNameJNI();
	sprintf(szwaitFile,"/mnt/sdcard/%s/.wait",searchPath.c_str());
#endif	

#if (CC_TARGET_PLATFORM==CC_PLATFORM_MAC )
    
    //FileUtils::getInstance()->
#endif
    
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS )
    
#endif
    
	if (!FileUtils::getInstance()->isFileExist(szwaitFile))
	{
		resetRuntime();
		return;
	}
		
	if (_scheduler)
		_scheduler->scheduleSelector(SEL_SCHEDULE(&RuntimeConfig::updateConnect), this,0.5f, false);


}