#include "RuntimeConfig.h"

#include "cocos2d.h"
#include <vector>
#include <string>

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