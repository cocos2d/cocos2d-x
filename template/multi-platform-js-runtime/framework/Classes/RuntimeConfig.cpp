#include "RuntimeConfig.h"

#include "cocos2d.h"
#include <vector>
#include <string>

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include <unistd.h>
#define Usleep usleep
#elif (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32) 
#define Usleep Sleep
#endif

USING_NS_CC;
using namespace std;

static RuntimeConfig *s_SharedRuntime = nullptr;
RuntimeConfig::RuntimeConfig()
{
	s_SharedRuntime =NULL;
}

RuntimeConfig::~RuntimeConfig()
{
	s_SharedRuntime =NULL;
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
		string searchPath = GetCurAppPath();
		searchPath += "/../..";
		FileUtils::getInstance()->addSearchPath(searchPath.c_str());
		FileUtils::getInstance()->addSearchPath("HelloJavascriptRes");
#endif

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	extern std::string getPackageNameJNI();
	string searchPath = "/mnt/sdcard/";
	searchPath += getPackageNameJNI();
	FileUtils::getInstance()->addSearchPath(searchPath.c_str());
	//MessageBox(searchPath.c_str(),""); 
#endif

	// /mnt/sdcard/
	// CC_PLATFORM_ANDROID

}

void RuntimeConfig::waitConnect()
{

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)

	extern std::string getPackageNameJNI();
	string searchPath = getPackageNameJNI();
	char szwaitFile[512]={0};
	char szwaitEndFile[512] ={0};
	sprintf(szwaitFile,"/mnt/sdcard/%s/wait",searchPath.c_str());
	sprintf(szwaitEndFile,"/mnt/sdcard/%s/waitend",searchPath.c_str());
	if (!FileUtils::getInstance()->isFileExist(szwaitFile))
		return;

	while (true)
	{
		if (FileUtils::getInstance()->isFileExist(szwaitEndFile))
			break;
		Usleep(10);
	}	
#endif

}