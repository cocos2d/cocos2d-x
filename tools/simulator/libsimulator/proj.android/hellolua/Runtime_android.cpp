#include <jni.h>
#include <android/log.h>
#include "jni/JniHelper.h"
#include <string>
#include <vector>
using namespace std;
using namespace cocos2d;

static std::string className = "org/cocos2dx/lua/AppActivity";

void setActivityPathForAndroid(const std::string& path)
{
    className = path;
}

string getIPAddress()
{
    return JniHelper::callStaticStringMethod(className, "getLocalIpAddress");
}
