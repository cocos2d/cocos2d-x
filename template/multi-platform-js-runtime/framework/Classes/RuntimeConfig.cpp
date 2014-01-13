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
		string searchPathRes = GetCurAppPath();
		searchPathRes += "/HelloJavascriptRes";
		FileUtils::getInstance()->addSearchPath(searchPath.c_str());
		FileUtils::getInstance()->addSearchPath(searchPathRes.c_str());
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
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)

	char szwaitFile[512]={0};
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

	if (!FileUtils::getInstance()->isFileExist(szwaitFile))
		return;

	while (true)
	{
		if (!FileUtils::getInstance()->isFileExist(szwaitFile))
			break;
		Usleep(10);
	}	

#endif

}